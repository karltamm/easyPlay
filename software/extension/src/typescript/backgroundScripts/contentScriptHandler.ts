export default class ContentScriptHandler {
  public static readonly TAB_UPDATE_EVENT = "tab-updated";
  public static TAB_ACTIVATED_EVENT = "tab-activated";

  constructor() {
    this.handleTabUpdate();
    this.handleTabActivation();
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

  private handleTabActivation(): void {
    browser.tabs.onActivated.addListener((activeInfo) => {
      browser.tabs.sendMessage(activeInfo.tabId, ContentScriptHandler.TAB_ACTIVATED_EVENT);
    });
  }
}
