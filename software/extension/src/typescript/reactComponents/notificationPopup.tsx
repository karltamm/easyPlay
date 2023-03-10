import React from "react";
import "../../sass/reactComponents/notificationPopup.scss";
import { NotificationData } from "../contentScripts/notifications/notificationData";
import CircularQueue from "../utilities/circularQueue";

type Props = {
  notificationsQueue: CircularQueue;
};

type State = {
  visible: boolean;
};

export default class NotificationPopup extends React.Component<Props, State> {
  public state = { visible: false };

  private visibleStateTimeout: number;
  private notificationCheckInterval: number;

  render(): React.ReactNode {
    this.startVisibleStateTimeout();
    return this.state.visible && this.getListOfNotifications();
  }

  componentDidMount(): void {
    this.checkForNotifications();
  }

  componentWillUnmount(): void {
    window.clearTimeout(this.visibleStateTimeout);
    window.clearInterval(this.notificationCheckInterval);
  }

  private checkForNotifications(): void {
    this.notificationCheckInterval = window.setInterval(() => {
      if (this.props.notificationsQueue.getSize()) {
        this.forceUpdate();
        this.setState({ visible: true });
      }
    }, 100);
  }

  private startVisibleStateTimeout(): void {
    if (this.visibleStateTimeout) {
      window.clearInterval(this.visibleStateTimeout);
    }
    this.visibleStateTimeout = window.setTimeout(() => {
      this.setState({ visible: false });
    }, 5000);
  }

  private getListOfNotifications(): JSX.Element {
    const notifications: NotificationData[] = [];
    while (this.props.notificationsQueue.getSize()) {
      notifications.push(this.props.notificationsQueue.pop());
    }
    return (
      <ul id="ep-notifications-list">
        {notifications.map((notification, index) => {
          let className = "ep-notification";
          className += notification.error ? " ep-error-notification" : "";
          return (
            <li key={index} className={className}>
              {notification.text}
            </li>
          );
        })}
      </ul>
    );
  }
}
