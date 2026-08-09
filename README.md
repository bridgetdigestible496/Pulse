<div align="center">

<img src="docs/assets/banner.png" width="100%">

<h1> Pulse </h1>

[![Version](https://img.shields.io/badge/Version-0.1-blue.svg)](#)
[![Platform](https://img.shields.io/badge/Platform-Windows-0078D6?logo=windows&logoColor=white)](#)
[![Qt](https://img.shields.io/badge/Qt-6.11.1-41CD52?logo=qt&logoColor=white)](https://www.qt.io/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](#license)

**A lightweight application launcher for Windows**

</div>
<h2> Overview </h2>

Pulse is a lightweight application launcher for Windows.

It provides a simple search interface for quickly finding and launching applications without navigating through the Start Menu.

The project is focused on being fast, minimal, and unobtrusive.

---

<h2> Features </h2>

- Fast application search — quickly find applications by name.
- Instant launching — launch the selected application directly from Pulse.
- Application icons — displays icons for detected applications when available.
- Global hotkey — open and hide Pulse without switching windows.
- Lightweight — designed to stay simple and use minimal resources.
- Keyboard-focused — search and launch without relying on the mouse.

---

<h2> How it works </h2>

Press the global hotkey (Alt + Space) to open Pulse and start typing the name of an application.

Pulse searches the applications available on the system and displays the closest match.

Select the result and launch it directly.

> [!Note]
> Application discovery in v0.1 currently uses Windows Start Menu shortcuts. This is a temporary implementation and will be improved in future releases.

---

<h2> Roadmap </h2>

**0.1**

- [x] Application launcher
- [x] Application search
- [x] Application icons
- [x] Global hotkey
- [x] Basic Windows integration

**0.2**

- [ ] Improved application discovery
- [ ] Better search and matching
- [ ] Improved icon detection

**0.3**

- [ ] Website launching
- [ ] Calculator directly from the search bar

**1.0**

- [ ] Custom application aliases
- [ ] User-defined shortcuts
- [ ] More launcher customization

---

<h2> Installation </h2>

Download the latest release and run Pulse-Setup.exe.

> [!IMPORTANT]
> Pulse is currently intended for Windows.

---

<h2> Building </h2>

Pulse is written in C++ using Qt 6 and built with CMake.

Requirements:

- Windows
- Qt 6
- CMake
- MinGW or another supported C++ compiler

Build the project with:

```
mkdir build
cd build
```
```
cmake ..
cmake --build .
```
---

<h2> Usage </h2>

> [!WARNING]
> The program currently doesn't have a welcome screen. After launching, use the **Alt + Space** key combination to display the panel.

1. Launch Pulse.
2. Use the global hotkey to open the launcher.
3. Type the name of an application.
4. Launch the displayed result.

That's it.

*«Pulse is designed to stay out of your way.»*

---

<h2> License </h2>

This project is licensed under the MIT License.

See the [LICENSE](LICENSE) file for details.
