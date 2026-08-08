<div align="center"><img src="docs/assets/banner.png" width="100%"><h1>Pulse</h1>""Version" (https://img.shields.io/badge/Version-0.1-blue.svg)" (#)
""Platform" (https://img.shields.io/badge/Platform-Windows-0078D6.svg)" (#)
""Qt" (https://img.shields.io/badge/Qt-6.11-41CD52.svg)" (#)
""License" (https://img.shields.io/badge/License-MIT-yellow.svg)" (#license)

A fast and lightweight application launcher for Windows

</div>Overview

Pulse is a lightweight application launcher for Windows.

It provides a simple search interface for quickly finding and launching applications without navigating through the Start Menu.

The project is focused on being fast, minimal, and unobtrusive.

---

Features

- Fast application search — quickly find applications by name.
- Instant launching — launch the selected application directly from Pulse.
- Application icons — displays icons for detected applications when available.
- Global hotkey — open and hide Pulse without switching windows.
- Lightweight — designed to stay simple and use minimal resources.
- Keyboard-focused — search and launch without relying on the mouse.

---

How it works

Press the global hotkey to open Pulse and start typing the name of an application.

Pulse searches the applications available on the system and displays the closest match.

Select the result and launch it directly.

«Note: Application discovery in v0.1 currently uses Windows Start Menu shortcuts. This is a temporary implementation and will be improved in future releases.»

---

Roadmap

0.1

- [x] Application launcher
- [x] Application search
- [x] Application icons
- [x] Global hotkey
- [x] Basic Windows integration

0.2

- [ ] Improved application discovery
- [ ] Better search and matching
- [ ] Improved icon detection

0.3

- [ ] Website launching
- [ ] Calculator directly from the search bar

1.0

- [ ] Custom application aliases
- [ ] User-defined shortcuts
- [ ] More launcher customization

---

Installation

Download the latest release and run Pulse-Setup.exe.

Pulse is currently intended for Windows.

---

Building

Pulse is written in C++ using Qt 6 and built with CMake.

Requirements:

- Windows
- Qt 6
- CMake
- MinGW or another supported C++ compiler

Build the project with:

mkdir build
cd build

cmake ..
cmake --build .

---

Usage

1. Launch Pulse.
2. Use the global hotkey to open the launcher.
3. Type the name of an application.
4. Launch the displayed result.

That's it.

«Pulse is designed to stay out of your way.»

---

License

This project is licensed under the MIT License.

See the "LICENSE" (LICENSE) file for details.
