import React from "react";
import EventHandler from "../utilities/eventHandler";
import BookmarksEvent from "../contentScripts/bookmarks/bookmarksEvent";
import { BookmarkData } from "../contentScripts/bookmarks/bookmarksTypes";
import BookmarkOption from "./bookmarkOption";

export type ButtonData = {
  text: string;
  className?: string;
  action: () => void;
};

type State = {
  activeButtonIndex: number;
};

type Props = {
  open: boolean;
  bookmarkData: BookmarkData;
  bookmarkActions?: (() => void)[];
};

export default abstract class BookmarkDialog extends React.Component<Props, State> {
  public state = { activeButtonIndex: 0 };

  private readonly dialogTitle: string;
  private readonly buttons: ButtonData[];
  private lastOpeningTime = 0;
  private eventHandlers: EventHandler[] = [];

  constructor(props, dialogTitle: string, buttons: ButtonData[]) {
    super(props);
    this.dialogTitle = dialogTitle;
    this.buttons = buttons;
  }

  render(): React.ReactNode {
    return (
      this.props.open && (
        <div className="ep-bookmark-dialog">
          <h2>{this.dialogTitle}</h2>
          <div className="ep-bookmark-dialog-body">
            <BookmarkOption data={this.props.bookmarkData} selected={true} />
            <div className="ep-bookmark-dialog-btns">
              {this.buttons.map((button, index) => {
                return (
                  <button key={index} className={this.getButtonCssClasses(index, button.className)}>
                    {button.text}
                  </button>
                );
              })}
            </div>
          </div>
        </div>
      )
    );
  }

  componentDidMount(): void {
    this.setUpEventHandlers();
  }

  componentWillUnmount(): void {
    this.removeEventHandlers();
  }

  componentDidUpdate(prevProps: Readonly<Props>): void {
    if (!prevProps.open) {
      if (Date.now() - this.lastOpeningTime > 100) {
        this.lastOpeningTime = Date.now();
        this.setState({ activeButtonIndex: 0 });
      }
    }
  }

  protected addEventHandler(eventHandler: EventHandler): void {
    this.eventHandlers.push(eventHandler);
  }

  private setUpEventHandlers(): void {
    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SCROLL_DOWN, () => {
        if (this.props.open) {
          this.goToNextButton(true);
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SCROLL_UP, () => {
        if (this.props.open) {
          this.goToNextButton(false);
        }
      })
    );

    this.eventHandlers.push(
      new EventHandler(BookmarksEvent.SELECT_OPTION, () => {
        if (this.props.open) {
          this.selectOption();
        }
      })
    );
  }

  private removeEventHandlers(): void {
    this.eventHandlers.forEach((eventHandler) => {
      eventHandler.unsubscribe();
    });
  }

  private getButtonCssClasses(buttonIndex: number, extraClass: string = ""): string {
    let classes = `ep-btn ${extraClass ? extraClass : ""}`;
    if (buttonIndex == this.state.activeButtonIndex) {
      classes += " ep-active-btn";
    }
    return classes;
  }

  private goToNextButton(goingDown: boolean): void {
    if (goingDown) {
      if (this.state.activeButtonIndex + 1 === this.buttons.length) {
        this.setState({ activeButtonIndex: 0 });
      } else {
        this.setState({ activeButtonIndex: this.state.activeButtonIndex + 1 });
      }
    } else {
      if (this.state.activeButtonIndex - 1 < 0) {
        this.setState({ activeButtonIndex: this.buttons.length - 1 });
      } else {
        this.setState({ activeButtonIndex: this.state.activeButtonIndex - 1 });
      }
    }
  }

  private selectOption(): void {
    this.buttons.forEach((button, index) => {
      if (index != this.state.activeButtonIndex) {
        return;
      }
      button.action();
    });
  }
}
