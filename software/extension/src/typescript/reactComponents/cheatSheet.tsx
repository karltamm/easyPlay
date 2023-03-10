import React from "react";
import "../../sass/reactComponents/cheatSheet.scss";

type CheatSheetItem = {
  icon: string;
  text: string;
};

type Props = {
  open: boolean;
  items: CheatSheetItem[];
};

export default class CheatSheet extends React.Component<Props> {
  render(): React.ReactNode {
    return this.props.open && <div id="ep-cheat-sheet">{this.getItems()}</div>;
  }

  private getItems(): JSX.Element[] {
    return this.props.items.map((item, index) => {
      return (
        <div className="ep-cheat-sheet-item" key={index}>
          <img className="ep-keycap-icon" src={item.icon} />
          <span>{item.text}</span>
        </div>
      );
    });
  }
}
