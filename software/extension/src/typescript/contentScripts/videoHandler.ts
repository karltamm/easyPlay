import ContentScriptHandler from "../backgroundScripts/contentScriptHandler";
import EventHandler from "../utilities/eventHandler";
import BookmarksEvent from "./bookmarks/bookmarksEvent";
import BookmarksHandler from "./bookmarks/bookmarksHandler";
import DeviceButton from "./deviceButton";
import NotificationsHandler from "./notifications/notificationsHandler";
import VideoSpeed from "./videoSpeed";

class Status {
  static readonly UNFINISHED = 0;
  static readonly UNDERWAY = 1;
  static readonly DONE = 2;
}

export default class VideoHandler {
  private static readonly VIDEO_FINDER_INTERVAL_MS = 250;
  private static readonly VIDEO_FINDER_MAX_CYCLES = 30000 / VideoHandler.VIDEO_FINDER_INTERVAL_MS;

  private videoElementPath: string;
  private video: HTMLVideoElement;
  private videoSpeed: VideoSpeed;
  private bookmarksHandler: BookmarksHandler;
  private setupStatus: number;

  constructor(videoElementPath: string) {
    this.videoElementPath = videoElementPath;
    this.setupStatus = Status.UNFINISHED;
    this.handleTabUpdate();
  }

  public async setUp() {
    switch (this.setupStatus) {
      case Status.DONE:
        console.warn("VideoHandler is already set up");
        return;
      case Status.UNDERWAY:
        console.warn("VideoHandler setup is underway");
        return;
    }
    this.setupStatus = Status.UNDERWAY;
    console.info("\nSetting up VideoHandler");
    if (!(await this.findVideoElement())) {
      console.error("Couldn't set up VideoHandler, because didn't find video element");
      this.setupStatus = Status.UNFINISHED;
      return;
    }
    this.setUpBookmarksHandler();
    this.setVideoSpeed(VideoSpeed.NORMAL);
    this.addEventHandlers();
    NotificationsHandler.setUpPopup();
    this.setupStatus = Status.DONE;
    console.info("VideoHandler setup complete");
  }

  private handleTabUpdate(): void {
    browser.runtime.onMessage.addListener(async (message) => {
      if (message != ContentScriptHandler.TAB_UPDATE_EVENT) {
        return;
      }
      console.info("\nHandling tab update");
      if (this.setupStatus == Status.UNFINISHED) {
        await this.setUp();
      } else if (this.setupStatus == Status.DONE) {
        await this.resetBrowserTab();
      }
      console.info("Tab update finished");
    });
  }

  private async resetBrowserTab() {
    console.info("Resetting browser tab");
    if (!(await this.findVideoElement())) {
      console.error("Couldn't find video element");
      return;
    }
    this.setVideoSpeed(VideoSpeed.NORMAL);
    EventHandler.emit(ContentScriptHandler.TAB_UPDATE_EVENT);
    console.info("Browser tab reset done");
  }

  private async findVideoElement(): Promise<boolean> {
    let cycleCount = 0;

    while (true) {
      if ((this.video = document.querySelector(this.videoElementPath))) {
        if (this.video.getBoundingClientRect().width) {
          return true;
        }
      }
      await new Promise((r) => window.setTimeout(r, VideoHandler.VIDEO_FINDER_INTERVAL_MS));
      if (++cycleCount == VideoHandler.VIDEO_FINDER_MAX_CYCLES) {
        return false;
      }
    }
  }

  private setUpBookmarksHandler(): void {
    if (this.bookmarksHandler) {
      console.warn("BookmarksHandler is already set up");
      return;
    }
    this.bookmarksHandler = new BookmarksHandler(this.video);
  }

  private addEventHandlers() {
    browser.runtime.onMessage.addListener(this.parseMessage.bind(this));
    new EventHandler(BookmarksEvent.CLOSE_MENU, () => {
      this.setDeviceButtonsLights();
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
