# EasyPlay

The aim of this project was to create a gadget that facilitates watching recorded lectures that are in a form of HTML5 video.

As a result of this, a custom-built hardware was designed and manufactured that communicates with a browser extension (_currently only on Firefox_) to control playback of HTML5 video and to
manage video bookmarks using graphical user interface (GUI).

[Demo video](https://www.youtube.com/watch?v=7g4fje1Z-I4)

# Hardware

- STM32F042C6T6 microcontroller (Arm Cortex-M0)
- Illuminated mechanical switches (Cherry MX) and knob (incremental rotary encoder)
- USB Type-C connector for communication (USB 2.0) and power
- Custom designed [printed circuit board](https://raw.githubusercontent.com/karltamm/EasyPlay/main/hardware/Outputs/PCB%203D%20Print/PCB%203D%20model%20top.png?token=GHSAT0AAAAAACCQFEIQWMR4IBDYY7HIEUHOZC5LKQA) (PCB) and enclosure

# Firmware

- Written in C
- Software based debounce for buttons and knob
- Simple task manager

# Driver

- Written in Java
- Uses [jSerialComm](https://fazecast.github.io/jSerialComm/) to communicate with the firmware
- Communicates with the browser extension using [native messaging protocol](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/Native_messaging)

# Browser extension

- Written in TypeScript
- Controls HTML5 video playback
- Allows to use video bookmarks using GUI (built with React)

# Installer

- Written in Qt
- Copies driver to chosen location
- Sets up [app manifest](https://developer.mozilla.org/en-US/docs/Mozilla/Add-ons/WebExtensions/Native_messaging#app_manifest) to use native messaging
