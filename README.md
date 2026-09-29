# pi-agent-mp3-player

> **AI-Driven, Voice-Enabled Embedded Audio Station on Raspberry Pi 3**  
> Powered by Yocto Linux, Qt 6 EGLFS, Google AIY Voice Kit v1, GStreamer, and Pi Agent.

[![Yocto](https://img.shields.io/badge/Yocto-Scarthgap-blue.svg)](https://www.yoctoproject.org/)
[![UI](https://img.shields.io/badge/UI-Qt%206%20EGLFS-green.svg)](https://www.qt.io/)
[![Hardware](https://img.shields.io/badge/Hardware-Raspberry%20Pi%203-orange.svg)](https://www.raspberrypi.com/)
[![Voice HAT](https://img.shields.io/badge/Audio-Google%20AIY%20Voice%20v1-red.svg)](https://aiyprojects.withgoogle.com/voice-v1/)
[![Agent](https://img.shields.io/badge/Agent-Pi%20Agent-purple.svg)](https://pi.dev)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

## Overview

**`pi-agent-mp3-player`** is an embedded, voice-controlled audio player built around the **Raspberry Pi 3**.

The project combines:

- **Yocto Linux** for a minimal, purpose-built embedded operating system
- **Qt 6 / Qt Quick / EGLFS** for a direct-rendered touchscreen interface
- **GStreamer** for audio playback
- **Google AIY Voice Kit v1** for microphone, speaker, button, and LED integration
- **Pi Agent** for voice-driven commands and LLM tool calling
- **MQTT** for remote and networked control

The goal is to create a small, fast-booting appliance that behaves less like a traditional Linux desktop and more like an **agent-native embedded device**.

```text
                 ┌──────────────────────────────────────┐
                 │        Google AIY Voice Kit v1       │
                 │                                      │
                 │  Dual Mic Array   Speaker   Button  │
                 │       │              │         │     │
                 └───────┼──────────────┼─────────┼─────┘
                         │ I2S           │ GPIO
                         │               │
                 ┌───────▼───────────────▼─────────────┐
                 │           Raspberry Pi 3 B+          │
                 │                                      │
                 │  ┌──────────────┐  ┌─────────────┐ │
                 │  │ Qt 6 / QML   │  │ Pi Agent    │ │
                 │  │ EGLFS / DRM  │  │ Service     │ │
                 │  └──────┬───────┘  └──────┬──────┘ │
                 │         │                  │        │
                 │         └───────┬──────────┘        │
                 │                 │ IPC               │
                 │         ┌───────▼────────┐          │
                 │         │   GStreamer    │          │
                 │         │ Audio Engine   │          │
                 │         └────────────────┘          │
                 │                                      │
                 │              Yocto Linux             │
                 └──────────────────────────────────────┘
```

---

## ✨ Features

### 🎙️ Google AIY Voice Kit Integration

The AIY Voice Kit v1 provides the physical voice interface for the system.

- Dual-microphone array
- I2S audio capture
- Speaker output
- GPIO arcade-style push button
- LED status feedback
- AIY Voice HAT ALSA soundcard support
- Push-to-talk interaction model

The physical button provides a simple interaction model:

> **Press → Speak → Agent interprets → Player responds**

---

### 🧠 Agent-Driven Audio Control

The player is designed around an **agent-first control architecture** rather than a collection of hard-coded voice commands.

Example requests:

```text
"Play some classical music."

"Set the volume to 80 percent."

"Skip this song."

"Pause the music."

"Play Queen."

"What song is playing?"
```

The agent converts natural-language requests into structured actions that can be consumed by the player service.

Conceptually:

```text
Natural Language
       │
       ▼
   Pi Agent
       │
       ▼
 Tool / Function Call
       │
       ▼
 JSON Command
       │
       ▼
 Player Service
       │
       ├──────────► Qt UI
       │
       └──────────► GStreamer
```

---

## 🖥️ Qt 6 EGLFS Interface

The graphical interface runs directly through **Qt 6 EGLFS**, avoiding a conventional desktop environment.

This provides:

- Qt Quick / QML UI
- Full-screen appliance mode
- DRM/KMS-based rendering
- GPU-accelerated graphics where supported
- Touchscreen-oriented interaction
- Minimal system overhead

The intended boot experience is:

```text
Power On
   │
   ▼
Yocto Linux
   │
   ▼
System Initialization
   │
   ▼
Agent + Audio Services
   │
   ▼
Qt EGLFS Application
   │
   ▼
Ready
```

The system is intended to boot directly into the player rather than exposing a general-purpose desktop.

---

## 🔊 Audio Architecture

Audio is handled through **ALSA + GStreamer**, with the Google AIY Voice HAT providing the primary audio hardware interface.

```text
                ┌───────────────┐
Microphones ───►│               │
                │  AIY Voice    │
Speaker    ◄────│     HAT       │
                │               │
Button     ────►│ GPIO          │
LED        ◄────│ GPIO          │
                └───────┬───────┘
                        │
                       I2S
                        │
                ┌───────▼───────┐
                │ Raspberry Pi  │
                │     ALSA      │
                └───────┬───────┘
                        │
                ┌───────▼───────┐
                │  GStreamer    │
                └───────┬───────┘
                        │
                ┌───────▼───────┐
                │  Qt / Agent   │
                └───────────────┘
```

### ALSA Configuration

Example `/etc/asound.conf`:

```conf
pcm.!default {
    type hw
    card voicehat
}

ctl.!default {
    type hw
    card voicehat
}
```

> The exact ALSA card name should be verified on the target image with `aplay -l` and `arecord -l`, as hardware enumeration can vary depending on the kernel/device-tree configuration.

---

## 🏗️ Hardware Architecture

### Target Hardware

| Component | Role |
|---|---|
| Raspberry Pi 3 B+ | Main embedded computer |
| Google AIY Voice Kit v1 | Voice/audio interface |
| Dual microphone array | Voice capture |
| AIY speaker driver | Audio playback |
| Arcade button | Push-to-talk control |
| AIY LED | Status / activity feedback |
| Touchscreen | Qt user interface |
| microSD card | Yocto boot/storage |

### Hardware Interface

```text
Google AIY Voice Kit v1
        │
        ├── I2S ───────► Audio Input
        │
        ├── I2S/PWM ───► Audio Output
        │
        └── GPIO ──────► Button / LED
                              │
                              ▼
                       Raspberry Pi 3 B+
```

---

## 🧩 Software Architecture

```text
┌─────────────────────────────────────────────────────────────┐
│                         Application                         │
│                                                             │
│  ┌──────────────────┐          ┌─────────────────────────┐ │
│  │   Qt 6 / QML     │◄────────►│     Pi Agent Service    │ │
│  │   Player UI      │   IPC    │ Voice / LLM / Commands  │ │
│  └────────┬─────────┘          └───────────┬─────────────┘ │
│           │                                │               │
│           │                                │ MQTT          │
│           │                                ▼               │
│           │                        Remote Control         │
│           │                                                │
│  ┌────────▼──────────────────────────────────────────────┐ │
│  │                    GStreamer                           │ │
│  │                 Audio Playback                         │ │
│  └────────────────────────┬──────────────────────────────┘ │
│                           │                                │
├───────────────────────────┼────────────────────────────────┤
│                           │                                │
│                      ALSA / I2S                           │
│                           │                                │
├───────────────────────────┼────────────────────────────────┤
│                    Yocto Linux                            │
│              Systemd / Kernel / DRM-KMS                   │
└─────────────────────────────────────────────────────────────┘
```

---

## 🔄 Voice & Agent Control Flow

```text
[ User presses AIY button ]
              │
              ▼
[ GPIO event detected ]
              │
              ▼
[ LED begins activity indication ]
              │
              ▼
[ Dual microphone captures speech ]
              │
              ▼
[ Speech-to-Text ]
              │
              ▼
[ Pi Agent interprets request ]
              │
        ┌─────┴─────┐
        │           │
        ▼           ▼
[ Tool Call ]   [ Conversational
        │          Response ]
        ▼           │
[ Player / MQTT ]   │
        │           │
        ▼           ▼
[ Qt UI Update ]  [ TTS ]
        │           │
        └─────┬─────┘
              ▼
       [ AIY Speaker ]
```

---

## 📡 Remote Control

In addition to physical interaction, the system can expose player controls through MQTT.

Example conceptual topics:

```text
pi-agent/player/play
pi-agent/player/pause
pi-agent/player/next
pi-agent/player/previous
pi-agent/player/volume
pi-agent/player/status
```

Example command:

```json
{
  "command": "volume",
  "value": 80
}
```

This allows the player to become part of a larger **home-agent or multi-room audio network**.

---

# 🛠️ Yocto Configuration

The target distribution is based on **Yocto Project Scarthgap**.

## Required Layers

The expected layer stack includes:

```text
poky
meta-raspberrypi
meta-qt6
meta-pi-agent-player
```

> The project uses Qt 6, so `meta-qt6` should be used rather than the older `meta-qt5` layer.

---

## Machine Configuration

Example `conf/local.conf`:

```bitbake
MACHINE = "raspberrypi3-64"

ENABLE_UART = "1"

# Google AIY Voice HAT
KERNEL_DEVICETREE:append = " overlays/googlevoicehat-soundcard.dtbo"

DTOVERLAY_PARAM = "i2s=on"

# Audio / Multimedia
IMAGE_INSTALL:append = " \
    alsa-utils \
    alsa-tools \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-ugly \
    i2c-tools \
"

# Qt
IMAGE_INSTALL:append = " \
    qtbase \
    qtdeclarative \
"

# Agent
IMAGE_INSTALL:append = " \
    pi-agent-service \
"
```

> Device-tree overlay names and package names may need adjustment to match the exact kernel, Yocto layer revisions, and AIY driver implementation used by the build.

---

# 📂 Project Structure

```text
pi-agent-mp3-player/
│
├── build/
│   └── # Yocto build environment
│
├── meta-pi-agent-player/
│   ├── conf/
│   │   └── layer.conf
│   │
│   ├── recipes-core/
│   │   └── images/
│   │       └── core-image-pi-agent-player.bb
│   │
│   ├── recipes-kernel/
│   │   └── # AIY Voice HAT / device-tree integration
│   │
│   └── recipes-apps/
│       ├── qt-mp3-app/
│       │   └── # Qt 6 / QML player
│       │
│       └── pi-agent-daemon/
│           └── # Pi Agent integration
│
├── src/
│   ├── qt_ui/
│   │   ├── qml/
│   │   └── # C++ / GStreamer integration
│   │
│   └── agent_service/
│       ├── # AIY GPIO interface
│       ├── # Voice interface
│       └── # Agent tool handlers
│
├── docs/
│   ├── hardware/
│   ├── wiring/
│   └── architecture/
│
├── LICENSE
└── README.md
```

---

# 🚀 Quick Start

## 1. Clone Yocto

```bash
git clone -b scarthgap https://git.yoctoproject.org/poky
cd poky
```

Clone the Raspberry Pi BSP layer:

```bash
git clone -b scarthgap https://git.yoctoproject.org/meta-raspberrypi
```

Clone the Qt 6 layer:

```bash
git clone -b scarthgap https://github.com/qt/meta-qt6.git
```

Clone this project:

```bash
git clone https://github.com/your-username/pi-agent-mp3-player.git
```

---

## 2. Initialize the Build Environment

```bash
source oe-init-build-env
```

Add the required layers:

```bash
bitbake-layers add-layer \
    ../meta-raspberrypi \
    ../meta-qt6 \
    ../pi-agent-mp3-player/meta-pi-agent-player
```

Verify:

```bash
bitbake-layers show-layers
```

---

## 3. Build the Image

```bash
bitbake core-image-pi-agent-player
```

The resulting image should be generated under:

```text
tmp/deploy/images/raspberrypi3-64/
```

---

## 4. Flash the SD Card

Identify the target block device carefully:

```bash
lsblk
```

Then flash the image:

```bash
sudo dd \
    if=tmp/deploy/images/raspberrypi3-64/core-image-pi-agent-player-raspberrypi3-64.wic \
    of=/dev/sdX \
    bs=4M \
    status=progress \
    conv=fsync
```

> **Warning:** Replace `/dev/sdX` with the correct SD-card device. Verify it with `lsblk` before running `dd`.

---

# 🔧 Development & Debugging

Useful commands on the target device:

### Check audio devices

```bash
aplay -l
```

```bash
arecord -l
```

### Test speaker output

```bash
speaker-test -D hw:voicehat -c 1
```

### Test microphone input

```bash
arecord \
    -D hw:voicehat \
    -f S16_LE \
    -r 48000 \
    -c 2 \
    test.wav
```

### Check GPIO / I2C

```bash
i2cdetect -l
```

```bash
i2cdetect -y 1
```

### Inspect services

```bash
systemctl status pi-agent-service
```

```bash
journalctl -u pi-agent-service -f
```

### Check kernel messages

```bash
dmesg | grep -i voice
```

```bash
dmesg | grep -i i2s
```

---

# 🛣️ Roadmap

## Phase 1 — Embedded Player

- [x] Yocto-based Raspberry Pi image
- [x] Qt 6 application framework
- [x] EGLFS direct rendering
- [x] GStreamer audio pipeline
- [ ] Production MP3 library management
- [ ] Persistent playback state

## Phase 2 — AIY Voice Interface

- [x] AIY Voice HAT hardware integration
- [x] ALSA soundcard support
- [x] GPIO button integration
- [x] LED status feedback
- [ ] Robust voice capture service
- [ ] Production speech pipeline

## Phase 3 — Agentic Voice Control

- [ ] Local speech-to-text
- [ ] Whisper-based embedded STT
- [ ] Pi Agent tool integration
- [ ] Structured player commands
- [ ] TTS response pipeline
- [ ] Context-aware music control

## Phase 4 — Networked Audio

- [ ] MQTT player control
- [ ] Multi-room synchronization
- [ ] Distributed playback state
- [ ] Network discovery
- [ ] Home-agent integration

---

# 🎯 Design Philosophy

The project follows a simple principle:

> **The device should feel like an appliance, not a computer.**

There is no need for a conventional desktop environment when the device has one clear purpose.

The architecture therefore favors:

```text
Minimal Linux
     +
Direct Hardware Access
     +
Native Qt UI
     +
GStreamer
     +
Agent Interface
     =
Embedded AI Appliance
```

The Raspberry Pi provides the computing platform, Yocto provides the operating-system foundation, Qt provides the interface, GStreamer handles media, and the agent provides the natural-language control layer.

---

# 🔮 Future Architecture

The long-term direction is to evolve the player from a standalone MP3 device into an **agent-native household audio node**.

```text
                    ┌───────────────────────┐
                    │      Home AI Agent    │
                    └───────────┬───────────┘
                                │
                              MQTT
                                │
              ┌─────────────────┼─────────────────┐
              │                 │                 │
              ▼                 ▼                 ▼
       ┌────────────┐    ┌────────────┐    ┌────────────┐
       │ Player #1  │    │ Player #2  │    │ Player #3  │
       │ Raspberry  │    │ Raspberry  │    │ Raspberry  │
       │ Pi + AIY   │    │ Pi + AIY   │    │ Pi + AIY   │
       └────────────┘    └────────────┘    └────────────┘
```

This architecture makes each Raspberry Pi audio station a **physical endpoint for an AI agent**.

---

# 🤝 Contributing

Contributions are welcome.

Areas where contributions are especially useful:

- Yocto recipes
- Raspberry Pi device-tree integration
- AIY Voice HAT support
- Qt/QML UI
- GStreamer pipelines
- Agent tool definitions
- MQTT protocols
- Embedded speech recognition
- Hardware documentation

Please open an issue before major architectural changes.

---

# 📜 License

This project is distributed under the **MIT License**.

See [`LICENSE`](LICENSE) for details.

---

## Acknowledgements

This project builds upon the work of:

- [Yocto Project](https://www.yoctoproject.org/)
- [Raspberry Pi](https://www.raspberrypi.com/)
- [Qt](https://www.qt.io/)
- [GStreamer](https://gstreamer.freedesktop.org/)
- [Google AIY Projects](https://aiyprojects.withgoogle.com/)
- [Pi Agent](https://pi.dev)

---

> **Build small. Boot fast. Speak naturally. Let the agent handle the rest.**