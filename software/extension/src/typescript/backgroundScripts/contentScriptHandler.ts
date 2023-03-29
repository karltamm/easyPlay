export default class ContentScriptHandler {
  public static readonly TAB_UPDATE_EVENT = "tab-updated";

  private static readonly YOUTUBE_URL_REGEX = /^(http(s)??\:\/\/)?(www\.)?((youtube\.com\/watch\?v=)|(youtu.be\/))([a-zA-Z0-9\-_])+/;
  private static readonly COURSERA_URL_REGEX = /https?:\/\/(www\.)?coursera\.org\/.*/;

  private currentUrl: string;

  constructor() {
    this.setUpEventHandlers();
  }

  private setUpEventHandlers(): void {
    browser.webNavigation.onCompleted.addListener(this.handlePageLoad.bind(this));
    browser.tabs.onUpdated.addListener(this.handleTabUpdate.bind(this));
  }

  private handlePageLoad(e: browser.webNavigation._OnDOMContentLoadedDetails): void {
    console.info("Handling page load");
    if (this.urlMatch(e.url, ContentScriptHandler.YOUTUBE_URL_REGEX)) {
      this.currentUrl = e.url;
      console.info("Loading YouTube content script");
      browser.scripting.executeScript({ files: ["dist/youtubeHandler.js"], target: { tabId: e.tabId } });
    } else if (this.urlMatch(e.url, ContentScriptHandler.COURSERA_URL_REGEX)) {
      this.currentUrl = e.url;
      console.info("Loading Coursera content script");
      browser.scripting.executeScript({ files: ["dist/courseraHandler.js"], target: { tabId: e.tabId } });
    }
  }

  private handleTabUpdate(tabId: number, changeInfo: browser.tabs._OnUpdatedChangeInfo): void {
    console.info("Handling tab update");
    if (!changeInfo?.url) {
      return;
    }
    if (!this.isSupportedSite(changeInfo.url)) {
      return;
    }
    if (changeInfo.url === this.currentUrl) {
      return;
    }
    this.currentUrl = changeInfo.url;
    browser.tabs.sendMessage(tabId, ContentScriptHandler.TAB_UPDATE_EVENT);
    console.info("Notified tabs about tab update");
  }

  private urlMatch(url: string, regex: RegExp): boolean {
    if (url === undefined) {
      return false;
    }
    if (!regex.exec(url)?.length) {
      return false;
    }
    return true;
  }

  private isSupportedSite(url: string): boolean {
    return (
      this.urlMatch(url, ContentScriptHandler.YOUTUBE_URL_REGEX) || //
      this.urlMatch(url, ContentScriptHandler.COURSERA_URL_REGEX)
    );
  }
}
