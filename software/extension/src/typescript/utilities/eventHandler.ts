export default class EventHandler {
  private eventName: string;
  private listener: EventListener;

  constructor(eventName: string, listener = () => {}) {
    this.eventName = eventName;
    this.listener = listener;
    this.subscribe();
  }

  setListener(listener: () => void): void {
    this.listener = listener;
  }

  subscribe(): void {
    EventHandler.subscribe(this.eventName, this.listener);
  }

  unsubscribe(): void {
    EventHandler.unsubscribe(this.eventName, this.listener);
  }

  emit(): void {
    EventHandler.emit(this.eventName);
  }

  static subscribe(eventName: string, listener: EventListener): void {
    document.addEventListener(eventName, listener);
  }

  static unsubscribe(eventName: string, listener: EventListener): void {
    document.removeEventListener(eventName, listener);
  }

  static emit(eventName: string): void {
    const event = new CustomEvent(eventName);
    document.dispatchEvent(event);
  }
}
