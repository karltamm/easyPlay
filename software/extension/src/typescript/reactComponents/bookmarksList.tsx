import React from "react";
import { BookmarkData } from "../contentScripts/bookmarks/bookmarksTypes";
import BookmarkOption from "./bookmarkOption";
import BookmarksEvent from "../contentScripts/bookmarks/bookmarksEvent";
import EventHandler from "../utilities/eventHandler";
import BookmarkSelectionDialog from "./bookmarkSelectionDialog";

type Props = {
  listOpen: boolean;
  selectionDialogOpen: boolean;
  bookmarks: BookmarkData[];
  playBookmark: (bookmarkIndex: number) => void;
  deleteBookmark: (bookmarkIndex: number) => void;
};

type State = {
  selectedBookmarkIndex: number;
};

export default class BookmarksList extends React.Component<Props, State> {
  private static selectedBookmarkIndex: number;

  public state = { selectedBookmarkIndex: 0 };

  private bookmarksRefs: React.RefObject<HTMLDivElement>[] = [];
  private listRef = React.createRef<HTMLDivElement>();
  private listHeaderRef = React.createRef<HTMLDivElement>();
  private eventHandlers: EventHandler[] = [];

  render(): React.ReactNode {
    return (
      this.props.listOpen && (
        <React.Fragment>
          {!this.props.selectionDialogOpen && (
            <div id="ep-bookmarks-list-box">
              <div id="ep-bookmarks-list-header" ref={this.listHeaderRef}>
                {this.getBookmarkCounter()}
              </div>
              <div id="ep-bookmarks-list" ref={this.listRef}>
                {this.getBookmarks()}
              </div>
            </div>
          )}
          <BookmarkSelectionDialog
            open={this.props.selectionDialogOpen}
            bookmarkData={this.props.bookmarks[this.state.selectedBookmarkIndex]}
            bookmarkActions={[
              () => {
                this.props.playBookmark(this.state.selectedBookmarkIndex);
              },
              () => {
                this.props.deleteBookmark(this.state.selectedBookmarkIndex);
              },
            ]}
          />
        </React.Fragment>
      )
    );
  }

  componentDidMount(): void {
    this.setSelectedBookmarkIndex(BookmarksList.selectedBookmarkIndex || 0);
    this.setListHeight();
    this.addEventHandlers();
    this.goToSelectedBookmark();
    this.updateListHeightOnResize();
  }

  componentWillUnmount(): void {
    this.removeEventHandlers();
  }

  componentDidUpdate(prevProps: Readonly<Props>, prevState: Readonly<State>): void {
    if (!prevProps.listOpen || (prevProps.listOpen && prevProps.selectionDialogOpen)) {
      this.setListHeight();
      this.goToSelectedBookmark();
    }
  }

  public static resetSelectedBookmarkIndex(): void {
    BookmarksList.selectedBookmarkIndex = 0;
  }

  private getBookmarkCounter(): JSX.Element {
    if (this.props.bookmarks.length) {
      return (
        <div id="ep-bookmarks-list-selection-info">
          <span id="ep-bookmarks-list-selected-bookmark-index">{this.state.selectedBookmarkIndex + 1}</span>
          <span> / {this.props.bookmarks.length}</span>
        </div>
      );
    } else {
      return <React.Fragment></React.Fragment>;
    }
  }

  private setListHeight(): void {
    const bookmarksMenu = document.getElementById("ep-bookmarks-menu");
    if (!bookmarksMenu || !this.listHeaderRef.current || !this.listRef.current) {
      console.warn("Can't set bookmarks list height because needed HTML element is not accessible");
      return;
    }
    const bookmarkMenuHeight = bookmarksMenu.offsetHeight;
    const listHeaderHeight = this.listHeaderRef.current.offsetHeight;
    const padding = 20;
    const listHeight = bookmarkMenuHeight - listHeaderHeight - padding;
    this.listRef.current.style.height = `${listHeight}px`;
  }

  private updateListHeightOnResize(): void {
    window.addEventListener("resize", this.setListHeight.bind(this));
  }

  private goToSelectedBookmark(): void {
    if (this.bookmarksRefs.length === 0) {
      return;
    }
    setTimeout(() => {
      const bookmark = this.bookmarksRefs[this.state.selectedBookmarkIndex].current;
      this.scrollToBookmark(bookmark);
    }, 25);
  }

  private getBookmarks(): JSX.Element[] {
    this.bookmarksRefs.length = 0;
    let index = -1;

    if (this.props.bookmarks.length == 0) {
      return [
        <div key={0} id="ep-no-bookmarks-message">
          No bookmarks added
        </div>,
      ];
    }

    return this.props.bookmarks.map((bookmark) => {
      index++;
      const bookmarkRef = React.createRef<HTMLDivElement>();
      this.bookmarksRefs.push(bookmarkRef);

      return (
        <BookmarkOption
          key={index} //
          data={bookmark} //
          bookmarkRef={bookmarkRef} //
          selected={index === this.state.selectedBookmarkIndex}
        />
      );
    });
  }

  private addEventHandlers(): void {
    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SCROLL_DOWN, () => {
        if (this.props.listOpen && !this.props.selectionDialogOpen) {
          this.goToNextBookmark(true);
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SCROLL_UP, () => {
        if (this.props.listOpen && !this.props.selectionDialogOpen) {
          this.goToNextBookmark(false);
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SCROLL_10_DOWN, () => {
        if (this.props.listOpen && !this.props.selectionDialogOpen) {
          if (this.state.selectedBookmarkIndex + 10 < this.props.bookmarks.length) {
            this.setSelectedBookmarkIndex(this.state.selectedBookmarkIndex + 10);
          } else {
            this.setSelectedBookmarkIndex(this.props.bookmarks.length - 1);
          }
          this.goToSelectedBookmark();
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SCROLL_10_UP, () => {
        if (this.props.listOpen && !this.props.selectionDialogOpen) {
          if (this.state.selectedBookmarkIndex - 10 >= 0) {
            this.setSelectedBookmarkIndex(this.state.selectedBookmarkIndex - 10);
          } else {
            this.setSelectedBookmarkIndex(0);
          }
          this.goToSelectedBookmark();
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.DELETE_BOOKMARK, () => {
        if (this.props.listOpen) {
          if (this.state.selectedBookmarkIndex > 0) {
            this.setSelectedBookmarkIndex(this.state.selectedBookmarkIndex - 1);
          }
        }
      })
    );
  }

  private removeEventHandlers(): void {
    this.eventHandlers.forEach((eventHandler) => {
      eventHandler.unsubscribe();
    });
  }

  private goToNextBookmark(goingDown: boolean): void {
    let nextIndex: number;
    if (goingDown) {
      if (this.state.selectedBookmarkIndex + 1 === this.props.bookmarks.length) {
        nextIndex = 0;
      } else {
        nextIndex = this.state.selectedBookmarkIndex + 1;
      }
    } else {
      if (this.state.selectedBookmarkIndex - 1 < 0) {
        nextIndex = this.props.bookmarks.length - 1;
      } else {
        nextIndex = this.state.selectedBookmarkIndex - 1;
      }
    }
    this.scrollToBookmark(this.bookmarksRefs[nextIndex].current);
    this.setSelectedBookmarkIndex(nextIndex);
  }

  private setSelectedBookmarkIndex(index): void {
    if (index != 0 && !this.props.bookmarks.length) {
      this.setSelectedBookmarkIndex(0);
      return;
    }
    BookmarksList.selectedBookmarkIndex = index; // Preserve selected bookmark index when bookmarks menu is closed
    this.setState({ selectedBookmarkIndex: index });
  }

  private scrollToBookmark(bookmark: HTMLDivElement): void {
    const distanceToBottom = this.getBookmarkBottomPosition(bookmark) - this.getBoxBottomPosition();
    if (distanceToBottom > 0) {
      this.listRef.current.scrollTop += distanceToBottom;
      return;
    }
    const distanceToTop = bookmark.offsetTop - this.getBoxTopPosition();
    if (distanceToTop < 0) {
      this.listRef.current.scrollTop += distanceToTop;
    }
  }

  private getBoxBottomPosition(): number {
    const boxHeight = this.listRef.current.getBoundingClientRect().height;
    return this.getBoxTopPosition() + boxHeight;
  }

  private getBoxTopPosition(): number {
    return this.listRef.current.scrollTop;
  }

  private getBookmarkBottomPosition(bookmark: HTMLDivElement): number {
    return bookmark.offsetHeight + bookmark.offsetTop;
  }
}
