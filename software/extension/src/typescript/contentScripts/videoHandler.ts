import ContentScriptHandler from "../backgroundScripts/contentScriptHandler";
import EventHandler from "../utilities/eventHandler";
import BookmarksEvent from "./bookmarks/bookmarksEvent";
import BookmarksHandler from "./bookmarks/bookmarksHandler";
import DeviceButton from "./deviceButton";
import NotificationsHandler from "./notifications/notificationsHandler";
import VideoSpeed from "./videoSpeed";

// TODO: reset video speed on page load
// TODO: use custom font

export default class VideoHandler {
  private static readonly VIDEO_FINDER_INTERVAL_MS = 250;
  private static readonly VIDEO_FINDER_MAX_CYCLES = 30000 / VideoHandler.VIDEO_FINDER_INTERVAL_MS;

  private videoElementPath: string;
  private video: HTMLVideoElement;
  private videoSpeed = VideoSpeed.NORMAL;
  private bookmarksHandler: BookmarksHandler;

  constructor(videoElementPath: string) {
    this.videoElementPath = videoElementPath;
  }

  public async setUp() {
    console.info("Setting up video handler");
    if (!(await this.findVideoElement())) {
      console.error("Couldn't set up VideoHandler");
      return;
    }
    this.setUpBookmarksHandler();
    this.setDeviceButtonsLights();
    this.handleMessages();
    this.addEventHandlers();
    NotificationsHandler.setUpPopup();
    console.info("video handler setup complete");
  }

  private async findVideoElement(): Promise<boolean> {
    let cycleCount = 0;
    while (true) {
      if ((this.video = document.querySelector(this.videoElementPath))) {
        return true;
      }
      await new Promise((r) => window.setTimeout(r, VideoHandler.VIDEO_FINDER_INTERVAL_MS));
      if (++cycleCount == VideoHandler.VIDEO_FINDER_MAX_CYCLES) {
        return false;
      }
    }
  }

  private setUpBookmarksHandler(): void {
    this.bookmarksHandler = new BookmarksHandler(this.video);
  }

  private addEventHandlers() {
    new EventHandler(BookmarksEvent.CLOSE_MENU, () => {
      this.setDeviceButtonsLights();
    });
  }

  private handleMessages(): void {
    browser.runtime.onMessage.addListener((message) => {
      this.parseMessage(message);
      return Promise.resolve("Message received from background script");
    });
  }

  private parseMessage(message: string): void {
    switch (message) {
      case "KNOB_PRESS":
        if (this.bookmarksHandler.isMenuOpen()) {
          EventHandler.emit(BookmarksEvent.SELECT_OPTION);
        } else {
          this.playOrPauseVideo();
        }
        break;
      case "KNOB_CW":
        if (this.bookmarksHandler.isMenuOpen()) {
          EventHandler.emit(BookmarksEvent.SCROLL_DOWN);
        } else {
          this.fastForwardVideo();
        }
        break;
      case "KNOB_CCW":
        if (this.bookmarksHandler.isMenuOpen()) {
          EventHandler.emit(BookmarksEvent.SCROLL_UP);
        } else {
          this.rewindVideo();
        }
        break;
      case "BTN_A_PRESS":
        if (this.bookmarksHandler.isMenuOpen()) {
          EventHandler.emit(BookmarksEvent.TOGGLE_CREATION_DIALOG);
        } else {
          this.setVideoSpeed(VideoSpeed.NORMAL);
        }
        break;
      case "BTN_B_PRESS":
        if (this.bookmarksHandler.isMenuOpen()) {
          EventHandler.emit(BookmarksEvent.SCROLL_10_UP);
        } else {
          this.setVideoSpeed(VideoSpeed.FAST);
        }
        break;
      case "BTN_C_PRESS":
        if (this.bookmarksHandler.isMenuOpen()) {
          EventHandler.emit(BookmarksEvent.SCROLL_10_DOWN);
        } else {
          this.setVideoSpeed(VideoSpeed.FASTEST);
        }
        break;
      case "BTN_D_PRESS":
        this.bookmarksHandler.toggleMenu();
        this.setDeviceButtonsLights();
        break;
      case "DEVICE_CONNECTED":
        this.setDeviceButtonsLights();
        break;
      case ContentScriptHandler.TAB_UPDATE_EVENT:
        EventHandler.emit(ContentScriptHandler.TAB_UPDATE_EVENT);
        break;
    }
  }

  private playOrPauseVideo(): void {
    if (this.video.paused) {
      this.video.play();
    } else {
      this.video.pause();
    }
  }

  private fastForwardVideo(): void {
    this.video.currentTime += 1;
  }

  private rewindVideo(): void {
    this.video.currentTime -= 1;
  }

  private setVideoSpeed(speedId: number): void {
    this.videoSpeed = speedId;
    switch (speedId) {
      case VideoSpeed.NORMAL:
        this.video.playbackRate = 1;
        break;
      case VideoSpeed.FAST:
        this.video.playbackRate = 1.5;
        break;
      case VideoSpeed.FASTEST:
        this.video.playbackRate = 2;
        break;
    }
    this.setDeviceButtonsLights();
  }

  private setDeviceButtonsLights(): void {
    const ledConfiguration = new Uint8Array(DeviceButton.COUNT);

    switch (this.videoSpeed) {
      case VideoSpeed.NORMAL:
        ledConfiguration[DeviceButton.A_ID] = 1;
        break;
      case VideoSpeed.FAST:
        ledConfiguration[DeviceButton.B_ID] = 1;
        break;
      case VideoSpeed.FASTEST:
        ledConfiguration[DeviceButton.C_ID] = 1;
        break;
    }

    if (this.bookmarksHandler.isMenuOpen()) {
      ledConfiguration[DeviceButton.A_ID] = 1;
      ledConfiguration[DeviceButton.B_ID] = 1;
      ledConfiguration[DeviceButton.C_ID] = 1;
      ledConfiguration[DeviceButton.D_ID] = 1;
    }

    this.sendMessageToDevice(`BTN_LED_${ledConfiguration.join("")}`);
  }

  private sendMessageToDevice(msg: string): void {
    browser.runtime.sendMessage(msg);
  }
}
