import ContentScriptHandler from "../backgroundScripts/contentScriptHandler";
import EventHandler from "../utilities/eventHandler";
import BookmarksEvent from "./bookmarks/bookmarksEvent";
import BookmarksHandler from "./bookmarks/bookmarksHandler";
import DeviceButton from "./deviceButton";
import NotificationsHandler from "./notifications/notificationsHandler";
import VideoSpeed from "./videoSpeed";

// TODO: create classes for handling YouTube and Echo360

export default class VideoHandler {
  private videoContainer: HTMLElement;
  private video: HTMLVideoElement;
  private videoSpeed = VideoSpeed.NORMAL;
  private bookmarksHandler: BookmarksHandler;

  constructor() {
    this.setYouTubeElements();
    this.setUpBookmarksHandler();
    this.setDeviceButtonsLights();
    this.handleMessages();
    this.addEventHandlers();
    NotificationsHandler.setUpPopup();
  }

  private setYouTubeElements(): void {
    this.videoContainer = document.getElementById("movie_player");
    if (!this.videoContainer) {
      console.error("Can't retrieve YouTube video container HTML element");
      return;
    }
    this.video = this.videoContainer.querySelector("video");
    if (!this.video) {
      console.error("Can't retrieve YouTube video HTML element");
      return;
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
