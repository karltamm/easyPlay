import BookmarksEvent from "../contentScripts/bookmarks/bookmarksEvent";
import EventHandler from "../utilities/eventHandler";
import BookmarkDialog from "./bookmarkDialog";

export default class BookmarkSelectionDialog extends BookmarkDialog {
  constructor(props) {
    super(props, "Selected bookmark", [
      {
        text: "Back",
        className: "ep-yellow-btn",
        action: () => {
          EventHandler.emit(BookmarksEvent.CLOSE_SELECTION_DIALOG);
        },
      },
      {
        text: "Play",
        action: () => {
          EventHandler.emit(BookmarksEvent.PLAY_BOOKMARK);
          this.props.bookmarkActions[0]();
        },
      },
      {
        text: "Delete",
        className: "ep-red-btn",
        action: () => {
          EventHandler.emit(BookmarksEvent.DELETE_BOOKMARK);
          this.props.bookmarkActions[1]();
        },
      },
    ]);
  }
}
