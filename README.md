# pi-agent-mp3-player

> **AI-Driven, Voice-Enabled Embedded Audio Station on Raspberry Pi 3**
> Powered by Yocto Linux, Qt 6 EGLFS, Google AIY Voice Kit v1, and Pi Agent.

[![Build Status](https://img.shields.io/badge/Yocto-Scarthgap-blue.svg)](https://www.yoctoproject.org/)
[![Framework](https://img.shields.io/badge/UI-Qt%206%20EGLFS-green.svg)](https://www.qt.io/)
[![Hardware](https://img.shields.io/badge/Hardware-RPi%203%20%2B%20AIY%20Voice%20v1-orange.svg)](https://aiyprojects.withgoogle.com/voice-v1/)
[![Agent Engine](https://img.shields.io/badge/Agent-Pi%20Agent-purple.svg)](https://pi.dev)

---

## 📌 Executive Summary

**`pi-agent-mp3-player`** is an enterprise-grade embedded IoT music player that turns a **Raspberry Pi 3** into a multi-modal, agent-driven smart audio workstation. 

By integrating the **Google AIY Voice Kit (v1) HAT**, the project leverages hardware-accelerated dual-microphone array audio capture, custom ALSA driver support, and physical push-button LED feedback. The system bypasses heavy desktop environments using a lightweight **Yocto Custom Distro**, running **Qt 6 (EGLFS)** directly on top of DRM/KMS GPU acceleration, and exposes control planes to local **Pi Agent** instances and remote MQTT networks.

---

## 🏗️ Hardware Architecture & Integration

+-------------------------------------------------------------------------------+
|                        Google AIY Voice Kit v1 (Voice HAT)                    |
|  +-------------------------+  +--------------------------+  +--------------+  |
|  | Dual Mic Array (I2S)    |  | Speaker Driver (3W Mono) |  | Arcade Button|  |
|  | (Voice Capture)         |  | (Audio Playback Output)  |  | (LED Light)  |  |
|  +------------+------------+  +------------+-------------+  +-------+------+  |
+---------------|----------------------------|------------------------|---------+
| I2S                        | I2S/PWM                | GPIO
+---------------v----------------------------v------------------------v---------+
|                               Raspberry Pi 3 B+                               |
|                                                                               |
|  +------------------------+  +------------------------+  +-----------------+  |
|  |    Qt 6 Application    |  |  Voice & Agent Daemon  |  |   Systemd Core  |  |
|  |   (EGLFS / Touch UI)   |  | (Pi Agent + AIY Driver)|  | (Fast-boot init)|  |
|  +-----------+------------+  +-----------+------------+  +-----------------+  |
|              |                           |                                    |
|              +---------> D-Bus / IPC <---+                                    |
|                                  |                                            |
|                        +---------v---------+                                  |
|                        | GStreamer Engine  |                                  |
|                        +-------------------+                                  |
+-------------------------------------------------------------------------------+


---

## ✨ Key Features

1. **Google AIY Voice HAT Hardware Integration:**
   * **I2S Audio Codec Driver (`snd_rpi_googlevoicehat_soundcard`):** High-fidelity audio input/output routed through AIY Voice HAT instead of standard 3.5mm jack.
   * **GPIO Arcade Button & Pulsing LED:** Hardware push-to-talk activation and glowing LED indicator during agent speech processing.
2. **Minimalist Yocto OS (Custom Distro):**
   * Instant boot-to-app (< 6 seconds) powered by Systemd.
   * Tailored layer stack: `meta-raspberrypi` + `meta-qt6` + custom `meta-aiy-voice`.
3. **Hardware Acceleration GUI (Qt 6 EGLFS):**
   * Frameless, lightweight Qt Quick touch interface direct-rendered on VC4 GPU.
4. **Agentic Voice & IoT Control (Pi Agent):**
   * Local or cloud LLM function calling ("Play classical music", "Set volume to 80%", "Skip song").
   * Dual Control Protocols: Physical AIY button voice trigger + Remote MQTT broker topics.

---

## 🛠️ Yocto Board Support Package (BSP) Configuration

To support the Google AIY Voice Kit (v1) soundcard and GPIO peripherals, add the following layer directives to your `meta-customer-layer`:

### 1. Device Tree & Kernel Modules (`conf/local.conf`)
```bitbake
MACHINE = "raspberrypi3-64"
ENABLE_UART = "1"

# Enable Google AIY Voice HAT Soundcard Overlays
KERNEL_DEVICETREE:append = " overlays/googlevoicehat-soundcard.dtbo"
DTOVERLAY_PARAM = "i2s=on"

# Include Necessary GStreamer & Audio Drivers
IMAGE_INSTALL:append = " \
    alsa-utils \
    alsa-tools \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-ugly \
    i2c-tools \
    rpio \
    qtbase \
    qtdeclarative \
    pi-agent-service \
"
2. Audio Output Routing (/etc/asound.conf)
Ensure ALSA routes sound directly through the AIY Voice HAT hardware:

Ini, TOML
pcm.!default {
    type hw
    card voicehat
}
ctl.!default {
    type hw
    card voicehat
}
📂 Project Directory Structure
Plaintext
pi-agent-mp3-player/
├── build/                      # Yocto Build Output Environment
├── meta-pi-agent-player/       # Custom Yocto Layer
│   ├── recipes-core/
│   │   └── images/             # Custom Core Image Specification
│   ├── recipes-kernel/         # AIY Voice HAT Device Tree Patches
│   └── recipes-apps/
│       ├── qt-mp3-app/         # Qt 6 EGLFS GUI Source Code
│       └── pi-agent-daemon/    # Node.js/Python Pi Agent Integration
├── docs/                       # Wiring Diagrams & Hardware Schematics
├── src/
│   ├── qt_ui/                  # QML & C++ GStreamer Wrapper
│   └── agent_service/          # AIY Button Listener & Speech Function Calling
└── README.md
🔄 Voice & Agent Control Loop Flow
[ User Presses AIY Arcade Button ]
                │
                ▼
[ GPIO Interrupt Triggers AIY LED to Pulse ]
                │
                ▼
[ Dual Mic Captures Voice Input (I2S) ]
                │
                ▼
[ Pi Agent Service Parses Intent via LLM Tool Call ]
                │
    ┌───────────┴───────────┐
    ▼                       ▼
[ Exec JSON Command ]   [ Speech Response (TTS) ]
    │                       │
    ▼                       ▼
[ Qt Player UI Update ] [ Speaker Output via AIY HAT ]
🚀 Quick Start Guide
Step 1: Clone and Set Up Yocto Layers
Bash
git clone -b scarthgap git://git.yoctoproject.org/poky
cd poky
git clone -b scarthgap git://git.yoctoproject.org/meta-raspberrypi
git clone -b scarthgap [https://github.com/meta-qt5/meta-qt5.git](https://github.com/meta-qt5/meta-qt5.git)
git clone [https://github.com/your-username/pi-agent-mp3-player.git](https://github.com/your-username/pi-agent-mp3-player.git)
Step 2: Build the Image
Bash
source oe-init-build-env
bitbake-layers add-layer ../meta-raspberrypi ../meta-qt5 ../pi-agent-mp3-player/meta-pi-agent-player
bitbake core-image-pi-agent-player
Step 3: Flash SD Card
Bash
sudo dd if=tmp/deploy/images/raspberrypi3-64/core-image-pi-agent-player-raspberrypi3-64.wic of=/dev/sdX bs=4M status=progress
🛣️ Roadmap & Future Enhancements
[x] Phase 1: Core Yocto Layer + Qt 6 EGLFS GStreamer Integration.

[x] Phase 2: AIY Voice HAT (v1) ALSA Driver & GPIO Button/LED Bindings.

[ ] Phase 3: On-Device Speech-to-Text (STT) using Whisper-Embedded / Local Model.

[ ] Phase 4: Multi-room Synchronization over MQTT Mesh Network.

📜 License
Distributed under the MIT License. See LICENSE for more information.

## 🏗️ Hardware Architecture & Integration