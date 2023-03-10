export default class ContentScriptHandler {
  public static readonly TAB_UPDATE_EVENT = "tab-updated";

  private static readonly YOUTUBE_URL_REGEX = /^(http(s)??\:\/\/)?(www\.)?((youtube\.com\/watch\?v=)|(youtu.be\/))([a-zA-Z0-9\-_])+/;

  private currentUrl: string;

  constructor() {
    this.setUpEventHandlers();
  }

  private setUpEventHandlers(): void {
    browser.webNavigation.onDOMContentLoaded.addListener(this.handlePageLoad.bind(this));
    browser.tabs.onUpdated.addListener(this.handleTabUpdate.bind(this));
  }

  private handlePageLoad(e: browser.webNavigation._OnDOMContentLoadedDetails): void {
    if (!this.isYoutubeVideo(e.url)) {
      return;
    }
    browser.scripting.executeScript({ files: ["dist/content.js"], target: { tabId: e.tabId } });
  }

  private handleTabUpdate(tabId: number, changeInfo: browser.tabs._OnUpdatedChangeInfo): void {
    if (!changeInfo?.url) {
      return;
    }
    if (!this.isYoutubeVideo(changeInfo.url)) {
      return;
    }
    if (changeInfo.url === this.currentUrl) {
      return;
    }
    this.currentUrl = changeInfo.url;
    browser.tabs.sendMessage(tabId, ContentScriptHandler.TAB_UPDATE_EVENT);
  }

  private isYoutubeVideo(url: string): boolean {
    if (!url) {
      return false;
    }
    return url.match(ContentScriptHandler.YOUTUBE_URL_REGEX).length > 0;
  }
}
