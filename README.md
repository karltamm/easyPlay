# EasyPlay

The aim of this project was to create a gadget that facilitates watching recorded lectures that are in a form of HTML5 video.

As a result of this, a custom-built hardware was designed and manufactured that communicates with a browser extension (_currently only on Firefox_) to control playback of HTML5 video and to manage video bookmarks using graphical user interface (GUI).

## Demo Clips

- [Adding Bookmark](https://www.youtube.com/watch?v=zyzYwxNeeDU&list=PLD5j9DIB91if8dvnZOE8TOlPMy7ZPZOXh&index=4)
- [Bookmark List](https://www.youtube.com/watch?v=o9xNbJMG1ok&list=PLD5j9DIB91if8dvnZOE8TOlPMy7ZPZOXh&index=4)
- [Playing Bookmark](https://www.youtube.com/watch?v=D4asH7l5GT0&list=PLD5j9DIB91if8dvnZOE8TOlPMy7ZPZOXh&index=5)
- [Deleting Bookmark](https://www.youtube.com/watch?v=MK7uui3cbB4&list=PLD5j9DIB91if8dvnZOE8TOlPMy7ZPZOXh&index=6)
- [Choosing Playback Speed](https://www.youtube.com/watch?v=vUmaLGZ5vVY&list=PLD5j9DIB91if8dvnZOE8TOlPMy7ZPZOXh&index=1)
- [Rewinding & Fast-Forwarding](https://www.youtube.com/watch?v=-IeWby0tvKw&list=PLD5j9DIB91if8dvnZOE8TOlPMy7ZPZOXh&index=2)

## Hardware

- STM32F042C6T6 microcontroller (ARM Cortex-M0)
- Illuminated mechanical switches (Cherry MX) and knob (incremental rotary encoder)
- USB Type-C connector for communication and power delivery
- Custom designed [printed circuit board](https://raw.githubusercontent.com/karltamm/EasyPlay/main/hardware/Outputs/PCB%203D%20Print/PCB%203D%20model%20top.png?token=GHSAT0AAAAAACCQFEIQWMR4IBDYY7HIEUHOZC5LKQA) (PCB) and enclosure ([exploded rendering](https://github.com/karltamm/EasyPlay/blob/main/enclosure/images/device-exploded-view.png) & [finished](https://github.com/karltamm/EasyPlay/blob/main/enclosure/images/assembled-device.png))

## Device Firmware

- Written in C
- Software based debounce for buttons and knob
- Simple task manager

## Device Client

- Written in C++
- Uses [Qt framework](https://www.qt.io/product/framework)
- Communicates with the device firmware using serial port
- Communicates with the browser extension using [native messaging protocol](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/Native_messaging)
- Uses Google Test library for unit tests

## Browser Extension

- Written in TypeScript
- Controls HTML5 video playback
- Allows to use video bookmarks using GUI (built with React)

## Client Installer

- Written in C++
- Uses [Qt framework](https://www.qt.io/product/framework)
- Copies client to chosen location
- Sets up [app manifest](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/Native_messaging#app_manifest) to use browser native messaging for communication between the device client and browser extension
