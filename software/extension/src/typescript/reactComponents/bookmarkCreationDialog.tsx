import EventHandler from "../utilities/eventHandler";
import BookmarksEvent from "../contentScripts/bookmarks/bookmarksEvent";
import BookmarkDialog from "./bookmarkDialog";

export default class BookmarkCreationDialog extends BookmarkDialog {
  constructor(props) {
    super(props, "Add bookmark", [
      {
        text: "Back",
        className: "ep-yellow-btn",
        action: () => {
          EventHandler.emit(BookmarksEvent.TOGGLE_CREATION_DIALOG);
        },
      },
      {
        text: "Add & continue video",
        action: () => {
          EventHandler.emit(BookmarksEvent.ADD_BOOKMARK_AND_PLAY);
        },
      },
      {
        text: "Add",
        action: () => {
          EventHandler.emit(BookmarksEvent.ADD_BOOKMARK);
        },
      },
    ]);
  }
}
