import { NotificationData } from "./notificationData";
import * as ReactDOM from "react-dom/client";
import React from "react";
import CircularQueue from "../../utilities/circularQueue";
import NotificationPopup from "../../reactComponents/notificationPopup";

export default class NotificationsHandler {
  private static popupIsSetUp = false;
  private static queue = new CircularQueue(3);

  static notify(data: NotificationData): void {
    if (!this.popupIsSetUp) {
      console.error("Can't send notification, because popup is not set up");
      return;
    }
    this.queue.push(data);
  }

  static setUpPopup(): void {
    if (this.popupIsSetUp) {
      console.warn("Notification popup is already set up");
      return;
    }
    const popupRoot = document.createElement("div");
    popupRoot.id = "ep-notification-popup-root";
    popupRoot.className = "ep-root";
    document.body.append(popupRoot);

    ReactDOM.createRoot(popupRoot).render(React.createElement(NotificationPopup, { notificationsQueue: this.queue }));
    this.popupIsSetUp = true;
  }
}
