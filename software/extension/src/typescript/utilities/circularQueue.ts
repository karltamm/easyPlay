export default class CircularQueue {
  private items: any[];
  private out: number;
  private in: number;
  private size: number;
  private maxSize: number;

  constructor(maxSize: number) {
    if (maxSize <= 0) {
      console.error("Queue max size can't be less or equal to 0");
      return;
    }
    this.maxSize = maxSize;
    this.items = Array(maxSize);
    this.out = 0;
    this.in = 0;
    this.size = 0;
  }

  push(item: any): void {
    this.items[this.in++] = item;
    if (this.in == this.maxSize) {
      this.in = 0;
    }
    this.size++;
  }

  pop(): any {
    if (this.size == 0) {
      return;
    }
    const item = this.items[this.out++];
    if (this.out == this.maxSize) {
      this.out = 0;
    }
    this.size--;
    return item;
  }

  getSize(): number {
    return this.size;
  }
}
