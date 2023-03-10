export default class DeviceCommunicator {
  private nativeApp: browser.runtime.Port;

  constructor(appName: string) {
    this.nativeApp = browser.runtime.connectNative(appName);

    this.handleMessageFromDevice();
    this.handleMessagesFromTabs();

    this.nativeApp.onDisconnect.addListener(() => {
      console.info("Native app is disconnected");
    });
  }

  private handleMessageFromDevice(): void {
    this.nativeApp.onMessage.addListener((data) => {
      if (!data["message"]) {
        console.error("Message from native app doesn't have 'message' key");
        return;
      }
      this.sendMessageToYouTubeTab(data["message"]);
    });
  }

  private sendMessageToYouTubeTab(message: string): void {
    browser.tabs.query({ active: true, currentWindow: true, url: "https://www.youtube.com/watch*" }).then((tabs) => {
      if (!tabs[0]?.id) {
        console.info("YouTube tab is not open to send message");
        return;
      }
      browser.tabs.sendMessage(tabs[0].id, message);
    });
  }

  private handleMessagesFromTabs(): void {
    browser.runtime.onMessage.addListener((message) => {
      this.nativeApp.postMessage({ message: message });
      return Promise.resolve("Message received from tab");
    });
  }
}
