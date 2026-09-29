# 🎵 Smart Embedded MP3 Player with Yocto, Qt & Agentic Control

An ultra-lightweight, high-performance embedded MP3 media player powered by **Raspberry Pi 3**, built using a custom **Yocto Linux distribution**, featuring a hardware-accelerated **Qt GUI**, and driven by an **autonomous AI Coding / Control Agent**.

---

## 📌 Executive Summary

Modern smart media playback devices often rely on heavy OS stacks, resulting in long boot times, high memory consumption, and potential privacy issues from cloud dependency. 

This project demonstrates an end-to-end embedded system proposal that converts a budget-friendly **Raspberry Pi 3** into an **industrial-grade IoT audio node**. By combining Yocto Linux for bare-minimum OS overhead, Qt running directly on EGLFS for direct GPU-accelerated graphics, and an onboard/edge AI Agent, this player enables local natural language control and dynamic agentic script creation.

---

## 🏛️ System Architecture

```
+-------------------------------------------------------------------------------+
|                       Raspberry Pi 3 Model B (Yocto Linux)                    |
|                                                                               |
|   +--------------------------+               +----------------------------+   |
|   |  Qt 6 / QML Front-end    |  Unix Domain  |  Local AI Coding Agent     |   |
|   |  (EGLFS / Direct DRM)    |<-- Socket --->|  (Python / Node.js Runner) |   |
|   +------------+-------------+     / DBus    +--------------+-------------+   |
|                |                                            |                 |
|   +------------v-------------+               +--------------v-------------+   |
|   |  GStreamer / ALSA Core   |               |   IoT Bridge (MQTT / REST) |   |
|   +--------------------------+               +----------------------------+   |
+-------------------------------------------------------------------------------+
```

---

## 🚀 Key Features

* **Custom Minimal Yocto OS:** Stripped of unnecessary services and bloat, booting directly into the media interface in seconds.
* **Direct EGLFS Graphics:** Qt 6 QML rendered directly to the screen via GPU hardware acceleration without requiring heavy display servers like X11.
* **Agentic Automation & Control:** Integrated local AI Agent capabilities that can receive natural language requests, parse tool-calling commands, and dynamically execute playlist logic via local IPC sockets or MQTT.
* **IoT Interoperability:** Remote monitoring, telemetry (playback state, temperature, hardware usage), and command reception over standard IoT protocols (MQTT, WebSockets).

---

## 🛠️ Tech Stack & Hardware Specs

### Hardware
* **Board:** Raspberry Pi 3 Model B (Cortex-A53 64-bit, 1GB RAM)
* **Audio Output:** 3.5mm Headphone Jack or external I2S Audio DAC (e.g., HiFiBerry)
* **Display:** 3.5" to 7" Touchscreen (SPI or HDMI)

### Software & Build Environment
* **Build Framework:** Yocto Project (Poky - Scarthgap/Kirkstone)
* **BSP Layer:** `meta-raspberrypi`
* **GUI Framework:** Qt 6 / Qt 5 (`meta-qt5` / `meta-qt6`)
* **Audio Engine:** GStreamer 1.0 / ALSA
* **IoT & Networking:** `mosquitto` (MQTT), WebSocket, Node.js/Python Runtime
* **Agent Runtime:** Lightweight Local LLM runner / OpenAI API integration wrapper

---

## 📂 Project Structure Plan

```text
├── build-yocto/            # Yocto build configuration directory
│   ├── conf/local.conf     # Target MACHINE, PACKAGECONFIG, IMAGE_INSTALL
│   └── conf/bblayers.conf  # Active layer definitions
├── meta-smartplayer/       # Custom Yocto layer for this project
│   ├── recipes-apps/       # Build recipes for Qt App and Agent Daemon
│   └── recipes-core/       # Systemd boot units and auto-start configurations
├── src/
│   ├── qt-player/          # Qt C++ & QML UI source code
│   └── agent-daemon/       # Python/Node.js script runner & IoT connector
└── docs/                   # Hardware wiring diagrams and API docs
```

---

## ⚙️ Development Roadmap

- [ ] **Phase 1: Yocto BSP & OS Customization**
  - Configure `raspberrypi3-64` image with GStreamer, ALSA, and Qt dependencies.
  - Optimize system boot time under 8 seconds.
- [ ] **Phase 2: Qt Audio UI Application**
  - Design touchscreen-friendly QML media controls.
  - Integrate `QMediaPlayer` with GStreamer audio pipeline.
- [ ] **Phase 3: IoT & Agent Bridge Integration**
  - Set up local IPC (Socket/DBus) between Qt Application and Agent runner.
  - Implement MQTT client for external smart home telemetry/control.
- [ ] **Phase 4: Optimization & Deployment**
  - Implement systemd auto-start for seamless boot-to-UI experience.
  - Run stability tests under resource-constrained scenarios.

---

## 🤝 Contributing & License

Contributions, feedback, and feature requests are welcome! Feel free to open an issue or submit a pull request.

This project is licensed under the **MIT License**.