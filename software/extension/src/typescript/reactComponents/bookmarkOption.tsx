import React from "react";
import { BookmarkData } from "../contentScripts/bookmarks/bookmarksTypes";

type Props = {
  data: BookmarkData;
  selected: boolean;
  bookmarkRef?: React.RefObject<HTMLDivElement>;
};

export default class BookmarkOption extends React.Component<Props> {
  private static readonly HOUR_IN_SECONDS = 3600;
  private static readonly MINUTE_IN_SECONDS = 60;

  render(): React.ReactNode {
    let className = "ep-bookmark";
    if (this.props.selected) {
      className += " ep-selected-bookmark";
    }
    return (
      <div className={className} ref={this.props.bookmarkRef}>
        <img className="ep-bookmark-img" src={this.props.data.img} />
        <div className="ep-bookmark-time">{this.formatTime()}</div>
      </div>
    );
  }

  private formatTime(): string {
    const hours = Math.floor(this.props.data.time / BookmarkOption.HOUR_IN_SECONDS);
    const minutes = Math.floor((this.props.data.time % BookmarkOption.HOUR_IN_SECONDS) / BookmarkOption.MINUTE_IN_SECONDS);
    const seconds = this.props.data.time % BookmarkOption.MINUTE_IN_SECONDS;

    return `${String(hours).padStart(3, "0")}:${String(minutes).padStart(2, "0")}:${String(seconds).padStart(2, "0")}`;
  }
}
