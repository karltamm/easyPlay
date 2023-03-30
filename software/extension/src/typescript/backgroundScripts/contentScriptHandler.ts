export default class ContentScriptHandler {
  public static readonly TAB_UPDATE_EVENT = "tab-updated";

  constructor() {
    this.handleTabUpdate();
  }

  private handleTabUpdate(): void {
    browser.tabs.onUpdated.addListener((tabId, changeInfo) => {
      if (!changeInfo?.url) {
        return;
      }
      browser.tabs.sendMessage(tabId, ContentScriptHandler.TAB_UPDATE_EVENT);
      console.info("Notified tabs about tab update");
    });
  }
}
