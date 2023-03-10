import React from "react";
import "../../sass/reactComponents/bookmarksMenu.scss";
import BookmarksEvent from "../contentScripts/bookmarks/bookmarksEvent";
import EventHandler from "../utilities/eventHandler";
import { BookmarkData } from "../contentScripts/bookmarks/bookmarksTypes";
import BookmarkCreationDialog from "./bookmarkCreationDialog";
import BookmarksList from "./bookmarksList";
import CheatSheet from "./cheatSheet";
import KeycapIcons from "../contentScripts/keycapIcons";

type State = {
  menuOpen: boolean;
  listOpen: boolean;
  selectionDialogOpen: boolean;
  creationDialogOpen: boolean;
};

type Props = {
  bookmarks: BookmarkData[];
  videoSnapshot: BookmarkData;
  playBookmark: (bookmarkIndex: number) => void;
  deleteBookmark: (bookmarkIndex: number) => void;
};

export default class BookmarksMenu extends React.Component<Props, State> {
  public state = { menuOpen: false, listOpen: false, selectionDialogOpen: false, creationDialogOpen: false };
  private eventHandlers: EventHandler[] = [];

  render(): React.ReactNode {
    return (
      this.state.menuOpen && (
        <div id="ep-bookmarks-menu">
          <BookmarksList
            bookmarks={this.props.bookmarks} //
            listOpen={this.state.listOpen} //
            selectionDialogOpen={this.state.selectionDialogOpen} //
            playBookmark={this.props.playBookmark} //
            deleteBookmark={this.props.deleteBookmark}
          />
          <BookmarkCreationDialog open={this.state.creationDialogOpen} bookmarkData={this.props.videoSnapshot} />
          <CheatSheet
            open={!this.state.selectionDialogOpen && !this.state.creationDialogOpen}
            items={[
              { icon: KeycapIcons.f1, text: "Add bookmark" },
              { icon: KeycapIcons.f2, text: "Scroll 10 up" },
              { icon: KeycapIcons.f3, text: "Scroll 10 down" },
            ]}
          />
        </div>
      )
    );
  }

  componentDidMount(): void {
    this.addEventHandlers();
  }

  componentWillUnmount(): void {
    this.removeEventHandlers();
  }

  private addEventHandlers(): void {
    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.OPEN_MENU, () => {
        this.setState({ menuOpen: true, listOpen: true, creationDialogOpen: false, selectionDialogOpen: false });
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.CLOSE_MENU, () => {
        this.setState({ menuOpen: false });
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.TOGGLE_CREATION_DIALOG, () => {
        if (!this.state.selectionDialogOpen) {
          this.toggleCreationDialog();
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.ADD_BOOKMARK, () => {
        this.toggleCreationDialog();
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.ADD_BOOKMARK_AND_PLAY, () => {
        this.toggleCreationDialog();
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SELECT_OPTION, () => {
        if (!this.state.creationDialogOpen && this.props.bookmarks.length) {
          this.setState({ selectionDialogOpen: true });
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.CLOSE_SELECTION_DIALOG, () => {
        this.setState({ selectionDialogOpen: false });
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.DELETE_BOOKMARK, () => {
        this.setState({ selectionDialogOpen: false });
      })
    );
  }

  private removeEventHandlers(): void {
    this.eventHandlers.forEach((eventHandler) => {
      eventHandler.unsubscribe();
    });
  }

  private toggleCreationDialog(): void {
    if (!this.state.creationDialogOpen) {
      this.setState({ creationDialogOpen: true, listOpen: false });
    } else {
      this.setState({ creationDialogOpen: false, listOpen: true });
    }
  }
}
