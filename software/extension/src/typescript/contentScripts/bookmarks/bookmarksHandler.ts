import { BookmarkData } from "./bookmarksTypes";
import EventHandler from "../../utilities/eventHandler";
import BookmarksEvent from "./bookmarksEvent";
import React from "react";
import * as ReactDOM from "react-dom/client";
import BookmarksMenu from "../../reactComponents/bookmarksMenu";
import NotificationsHandler from "../notifications/notificationsHandler";
import ContentScriptHandler from "../../backgroundScripts/contentScriptHandler";
import BookmarksList from "../../reactComponents/bookmarksList";

export default class BookmarksHandler {
  private static readonly THUMBNAIL_WIDTH_PX = 300;

  private video: HTMLVideoElement;
  private bookmarks: BookmarkData[] = [];
  private menuRoot: HTMLElement;
  private menuOpen: boolean;
  private videoSnapshot: BookmarkData = { img: "", time: 0 };
  private thumbnailCanvas: HTMLCanvasElement;
  private thumbnailCanvasContext: CanvasRenderingContext2D;

  constructor(video: HTMLVideoElement) {
    this.video = video;
    this.createMenu();
    this.setUpThumbnailCanvas();
    this.loadBookmarks();
    this.handleEvents();
  }

  public isMenuOpen(): boolean {
    return this.menuOpen;
  }

  public toggleMenu(): void {
    this.setMenuState(!this.menuOpen);
  }

  private createMenu(): void {
    this.createMenuRoot();
    this.setMenuState(false);
    ReactDOM.createRoot(this.menuRoot).render(
      React.createElement(BookmarksMenu, {
        bookmarks: this.bookmarks,
        videoSnapshot: this.videoSnapshot,
        playBookmark: (bookmarkIndex: number) => {
          this.playBookmark(bookmarkIndex);
        },
        deleteBookmark: (bookmarkIndex: number) => {
          this.deleteBookmark(bookmarkIndex);
        },
      })
    );
  }

  private createMenuRoot(): void {
    this.menuRoot = document.createElement("div");
    this.menuRoot.id = "ep-bookmarks-menu-root";
    this.menuRoot.className = "ep-root";
    document.body.append(this.menuRoot);
  }

  private setUpThumbnailCanvas(): void {
    if (this.thumbnailCanvas != undefined) {
      console.warn("Canvas for thumbnails is already set up");
      return;
    }
    this.thumbnailCanvas = document.createElement("canvas");
    this.thumbnailCanvas.id = "ep-canvas";
    document.body.append(this.thumbnailCanvas);
    this.thumbnailCanvasContext = this.thumbnailCanvas.getContext("2d");
  }

  private loadBookmarks(): void {
    browser.storage.local.get(document.URL).then((data: object) => {
      this.bookmarks.length = 0; // Clear array without changing reference (pointer)
      if (!(data instanceof Object)) {
        return;
      }
      const bookmarks: BookmarkData[] = data[document.URL];
      if (!(bookmarks instanceof Array)) {
        return;
      }
      if (!bookmarks.length) {
        return;
      }
      this.bookmarks.push(...bookmarks);
    });
  }

  private handleEvents(): void {
    new EventHandler(BookmarksEvent.ADD_BOOKMARK_AND_PLAY, () => {
      this.addBookmark();
      this.setMenuState(false);
    });

    new EventHandler(BookmarksEvent.ADD_BOOKMARK, () => {
      this.addBookmark();
    });

    new EventHandler(ContentScriptHandler.TAB_UPDATE_EVENT, () => {
      this.loadBookmarks();
      BookmarksList.resetSelectedBookmarkIndex();
    });
  }

  private setVideoSnapshot(): void {
    this.videoSnapshot.time = Math.floor(this.video.currentTime);
    this.videoSnapshot.img = this.getVideoSnapshotThumbnail();
  }

  private getVideoSnapshotThumbnail(): string {
    const widthRatio = BookmarksHandler.THUMBNAIL_WIDTH_PX / this.video.videoWidth;
    const thumbnailHeight = widthRatio * this.video.videoHeight;

    this.thumbnailCanvas.width = BookmarksHandler.THUMBNAIL_WIDTH_PX;
    this.thumbnailCanvas.height = thumbnailHeight;

    this.thumbnailCanvasContext.drawImage(this.video, 0, 0, BookmarksHandler.THUMBNAIL_WIDTH_PX, thumbnailHeight);
    try {
      return this.thumbnailCanvas.toDataURL();
    } catch (error) {
      // Probably because of cross origin security problem
      console.warn("Couldn't create bookmark thumbnail:", error);
      return "";
    }
  }

  private addBookmark(): boolean {
    if (this.doesBookmarkExist(this.videoSnapshot.time)) {
      NotificationsHandler.notify({ text: "Bookmark already exists", error: true });
      return false;
    }
    this.bookmarks.push({
      img: this.videoSnapshot.img,
      time: this.videoSnapshot.time,
    });
    this.sortBookmarks();
    this.updateStorage();
    NotificationsHandler.notify({ text: "Bookmark added" });
    return true;
  }

  private doesBookmarkExist(time: number): boolean {
    for (let i = 0; i < this.bookmarks.length; i++) {
      if (this.bookmarks[i].time === time) {
        return true;
      }
    }
    return false;
  }

  private sortBookmarks(): void {
    this.bookmarks.sort((a: BookmarkData, b: BookmarkData) => {
      if (a.time > b.time) {
        return 1;
      }
      if (a.time < b.time) {
        return -1;
      }
      return 0;
    });
  }

  private updateStorage(): void {
    browser.storage.local.set({ [document.URL]: this.bookmarks });
  }

  private playBookmark(bookmarkIndex: number): void {
    this.video.currentTime = this.bookmarks[bookmarkIndex].time;
    this.setMenuState(false);
  }

  private deleteBookmark(bookmarkIndex: number): void {
    if (bookmarkIndex >= this.bookmarks.length) {
      console.error("Deleted bookmark index is too large");
      NotificationsHandler.notify({ text: "Bookmark couldn't be deleted", error: true });
      return;
    }
    this.bookmarks[bookmarkIndex] = { time: -1, img: "" };
    this.sortBookmarks(); // Deleted bookmark will become the first is array
    if (this.bookmarks.shift() === undefined) {
      NotificationsHandler.notify({ text: "Bookmark couldn't be deleted", error: true });
      return;
    }
    // Deleted bookmark is shifted out of array
    this.updateStorage();
    NotificationsHandler.notify({ text: "Bookmark deleted" });
  }

  private setMenuState(open: boolean): void {
    this.menuOpen = open;
    if (open) {
      this.video.pause();
      this.setVideoSnapshot();
      EventHandler.emit(BookmarksEvent.OPEN_MENU);
    } else {
      this.video.play();
      EventHandler.emit(BookmarksEvent.CLOSE_MENU);
    }
  }
}
