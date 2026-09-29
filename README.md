# pi-agent-mp3-player

> **AI-Driven, Voice-Enabled Embedded Audio Station on Raspberry Pi 3**  
> Qt 6 • GStreamer • Yocto Linux • Google AIY Voice Kit v1 • Pi Agent • UNIX IPC • MQTT

[![Yocto](https://img.shields.io/badge/Yocto-Scarthgap-blue.svg)](https://www.yoctoproject.org/)
[![Ubuntu](https://img.shields.io/badge/Development-Ubuntu%2026.04%20LTS-orange.svg)](https://ubuntu.com/)
[![Qt](https://img.shields.io/badge/UI-Qt%206-green.svg)](https://www.qt.io/)
[![GStreamer](https://img.shields.io/badge/Audio-GStreamer-red.svg)](https://gstreamer.freedesktop.org/)
[![Hardware](https://img.shields.io/badge/Hardware-Raspberry%20Pi%203-orange.svg)](https://www.raspberrypi.com/)
[![Voice HAT](https://img.shields.io/badge/Audio-Google%20AIY%20Voice%20v1-purple.svg)](https://aiyprojects.withgoogle.com/voice-v1/)
[![Agent](https://img.shields.io/badge/Agent-Pi%20Agent-blueviolet.svg)](https://pi.dev)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

---

## Overview

**`pi-agent-mp3-player`** is an embedded, voice-enabled music player designed around the **Raspberry Pi 3**.

The project combines a lightweight Yocto Linux system with a native Qt 6 touch interface, GStreamer audio playback, Google AIY Voice Kit v1 hardware, and an external agent control layer.

The system is designed to behave like an **AI appliance rather than a traditional Linux desktop**.

```text
                    ┌───────────────────────────────┐
                    │          Pi Agent             │
                    │       Voice / LLM / Tools     │
                    └───────────────┬───────────────┘
                                    │
                              UNIX IPC / MQTT
                                    │
                    ┌───────────────▼───────────────┐
                    │       Player Controller       │
                    │       Qt 6 / C++              │
                    └───────────────┬───────────────┘
                                    │
                         ┌──────────▼──────────┐
                         │     GStreamer       │
                         │    Audio Engine     │
                         └──────────┬──────────┘
                                    │
                                  ALSA
                                    │
                    ┌───────────────▼───────────────┐
                    │     Google AIY Voice HAT      │
                    │   Microphones / Speaker /     │
                    │       Button / LED           │
                    └───────────────────────────────┘
```

---

# ✨ Features

## 🎵 Music Player

The Qt application provides a lightweight touch-oriented interface for:

- MP3 playback
- Play / pause
- Previous / next track
- Volume control
- Playback status
- Album artwork
- ID3 metadata visualization
- Default/fallback album artwork
- External agent control

---

## 🎙️ Google AIY Voice Kit v1

The Google AIY Voice Kit v1 provides the physical voice interface.

Supported hardware integration includes:

- Dual microphone array
- I2S audio capture
- Speaker output
- GPIO push button
- LED activity/status feedback
- AIY Voice HAT ALSA soundcard

The intended interaction model is deliberately simple:

```text
Press Button
     │
     ▼
Speak
     │
     ▼
Agent interprets request
     │
     ▼
Player executes command
     │
     ▼
Audio / UI response
```

---

# 🧠 Agent Architecture

The player is controlled through a small command interface rather than tightly coupling the Qt application to a specific AI implementation.

This allows the agent to be:

- Python
- Pi Agent
- Google AIY service
- Local LLM
- Cloud LLM
- Another embedded device
- Home automation controller

Example commands:

```text
"Play some classical music."

"Set the volume to 80 percent."

"Skip this song."

"Pause the music."

"Play Queen."

"What song is playing?"
```

The agent converts natural-language intent into structured player operations.

```text
Natural Language
       │
       ▼
┌──────────────┐
│   AI Agent   │
└──────┬───────┘
       │
       ▼
Tool / Function Call
       │
       ▼
Structured Command
       │
       ▼
┌────────────────────┐
│ PlayerController   │
└─────────┬──────────┘
          │
          ├──────► GStreamer
          │
          └──────► Qt UI
```

---

# 🔌 IPC Architecture

The Qt player exposes a **UNIX Domain Socket** for local agent communication:

```text
/tmp/pi_agent_mp3.sock
```

This provides a lightweight local IPC mechanism without requiring a network connection.

```text
Python Agent
     │
     │ UNIX Domain Socket
     │
     ▼
/tmp/pi_agent_mp3.sock
     │
     ▼
PlayerController
     │
     ├── Play
     ├── Pause
     ├── Next
     ├── Previous
     ├── Volume
     └── Status
```

This separation keeps the UI and agent independent.

The Qt application does not need to know whether a command originated from:

- a Python script,
- an LLM,
- the AIY voice service,
- MQTT,
- or another local process.

---

# 🖥️ Qt 6 Application

The Qt application is implemented in C++ and QML.

The application is designed to run in two environments:

### Development

Ubuntu 26.04 LTS:

```text
Ubuntu 26.04
     │
     ├── Qt 6
     ├── CMake
     ├── GStreamer
     └── GCC
            │
            ▼
      pi_agent_mp3_ui
```

### Production

Raspberry Pi 3:

```text
Yocto Linux
     │
     ├── Qt 6
     ├── EGLFS
     ├── GStreamer
     ├── ALSA
     └── AIY Voice HAT
```

The same application architecture is therefore usable during desktop development and embedded deployment.

---

# 📂 Project Structure

```text
pi-agent-mp3-player/
│
├── app/
│   └── qt_ui/
│       ├── .vscode/
│       │   ├── launch.json
│       │   ├── tasks.json
│       │   └── settings.json
│       │
│       ├── src/
│       │   ├── CMakeLists.txt
│       │   ├── main.cpp
│       │   ├── PlayerController.h
│       │   ├── PlayerController.cpp
│       │   ├── resources.qrc
│       │   │
│       │   └── qml/
│       │       ├── main.qml
│       │       └── default_cover.svg
│       │
│       ├── test_agent_control.py
│       └── README.md
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
│       │   └── # Qt 6 application recipe
│       │
│       └── pi-agent-daemon/
│           └── # Agent service recipe
│
├── docs/
│   ├── architecture/
│   ├── hardware/
│   └── wiring/
│
├── build/
│   └── # Yocto build environment
│
├── LICENSE
└── README.md
```

---

# 🛠️ Ubuntu 26.04 Development Environment

The Qt application can be developed and tested directly on **Ubuntu 26.04 LTS** before deploying it to the Raspberry Pi.

## Prerequisites

Install the required development packages:

```bash
sudo apt update

sudo apt install -y \
    build-essential \
    cmake \
    qt6-base-dev \
    qt6-declarative-dev \
    qt6-multimedia-dev \
    qml6-module-qtmultimedia \
    qml6-module-qtquick-controls \
    qml6-module-qtquick-layouts \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-plugins-bad \
    gstreamer1.0-alsa
```

---

# 🔨 Build the Qt Application

Enter the Qt application directory:

```bash
cd ~/workplace/pi-agent-mp3-player/app/qt_ui
```

Create the build directory:

```bash
mkdir -p build
cd build
```

Configure with CMake:

```bash
cmake ../src
```

Build:

```bash
make -j$(nproc)
```

The resulting executable should be:

```text
pi_agent_mp3_ui
```

Run it:

```bash
./pi_agent_mp3_ui
```

---

# 🧪 Agent IPC Test

The repository includes:

```text
app/qt_ui/test_agent_control.py
```

This script acts as a simple external agent and communicates with the Qt player through:

```text
/tmp/pi_agent_mp3.sock
```

## Run the Player

Terminal 1:

```bash
cd ~/workplace/pi-agent-mp3-player/app/qt_ui/build

./pi_agent_mp3_ui
```

## Run the Agent Test

Terminal 2:

```bash
cd ~/workplace/pi-agent-mp3-player/app/qt_ui

python3 test_agent_control.py
```

The test script demonstrates:

1. Adding a track
2. Starting playback
3. Setting volume
4. Querying player status
5. Toggling play/pause

The default track path can be modified inside the test script.

---

# 🧰 VS Code Development

The project includes a `.vscode/` configuration for CMake-based development.

Open the application:

```bash
cd ~/workplace/pi-agent-mp3-player/app/qt_ui

code .
```

Select the GCC/CMake kit provided by Ubuntu.

The development workflow is:

```text
        VS Code
           │
           ▼
      CMake Tools
           │
           ▼
        CMake
           │
           ▼
        GCC / G++
           │
           ▼
   pi_agent_mp3_ui
```

The project can be launched under GDB for interactive debugging.

---

# 🏗️ Yocto Production Build

The production system is built with **Yocto Project Scarthgap**.

The target machine is:

```bitbake
MACHINE = "raspberrypi3-64"
```

Expected layer stack:

```text
poky
meta-raspberrypi
meta-qt6
meta-pi-agent-player
```

---

## Clone Yocto

```bash
git clone -b scarthgap https://git.yoctoproject.org/poky

cd poky

git clone -b scarthgap \
    https://git.yoctoproject.org/meta-raspberrypi

git clone -b scarthgap \
    https://github.com/qt/meta-qt6.git

git clone \
    https://github.com/your-username/pi-agent-mp3-player.git
```

Initialize the build environment:

```bash
source oe-init-build-env
```

Add the layers:

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

# ⚙️ Yocto Configuration

Example `conf/local.conf`:

```bitbake
MACHINE = "raspberrypi3-64"

ENABLE_UART = "1"

# Google AIY Voice HAT
KERNEL_DEVICETREE:append = " overlays/googlevoicehat-soundcard.dtbo"

DTOVERLAY_PARAM = "i2s=on"

# Audio
IMAGE_INSTALL:append = " \
    alsa-utils \
    alsa-tools \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-ugly \
    gstreamer1.0-alsa \
    i2c-tools \
"

# Qt 6
IMAGE_INSTALL:append = " \
    qtbase \
    qtdeclarative \
    qtmultimedia \
"

# Application / Agent
IMAGE_INSTALL:append = " \
    pi-agent-service \
"
```

> Device-tree overlay names and package names may vary depending on the exact kernel and Yocto layer revisions used by the project.

---

# 🔊 ALSA Configuration

The production image should route the default ALSA device to the AIY Voice HAT.

Example:

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

Verify the actual device name on the target:

```bash
aplay -l
```

```bash
arecord -l
```

---

# 🧪 Raspberry Pi Audio Diagnostics

Test speaker output:

```bash
speaker-test -D hw:voicehat -c 1
```

Test microphone capture:

```bash
arecord \
    -D hw:voicehat \
    -f S16_LE \
    -r 48000 \
    -c 2 \
    test.wav
```

Inspect kernel messages:

```bash
dmesg | grep -i voice
```

```bash
dmesg | grep -i i2s
```

Check the agent service:

```bash
systemctl status pi-agent-service
```

Follow its logs:

```bash
journalctl -u pi-agent-service -f
```

---

# 📡 MQTT / Remote Control

Local UNIX IPC provides fast host-local control.

MQTT provides a path toward distributed control.

Conceptual topics:

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

This allows multiple Pi-based players to become networked audio endpoints.

---

# 🧱 System Architecture

The complete system can be viewed as four layers:

```text
┌─────────────────────────────────────────────────────────────┐
│                     AGENT LAYER                            │
│                                                             │
│       Pi Agent / LLM / Voice / Python / MQTT               │
└──────────────────────────┬──────────────────────────────────┘
                           │
                    IPC / Commands
                           │
┌──────────────────────────▼──────────────────────────────────┐
│                   APPLICATION LAYER                         │
│                                                             │
│              Qt 6 / QML / PlayerController                 │
└──────────────────────────┬──────────────────────────────────┘
                           │
                    Media Pipeline
                           │
┌──────────────────────────▼──────────────────────────────────┐
│                     MEDIA LAYER                             │
│                                                             │
│                   GStreamer / ALSA                         │
└──────────────────────────┬──────────────────────────────────┘
                           │
                      Hardware I/O
                           │
┌──────────────────────────▼──────────────────────────────────┐
│                     HARDWARE LAYER                          │
│                                                             │
│ Raspberry Pi 3 │ AIY Voice HAT │ GPIO │ I2S │ DRM/KMS      │
└─────────────────────────────────────────────────────────────┘
```

---

# 🔄 Complete Control Flow

```text
                         USER
                          │
                    Press AIY Button
                          │
                          ▼
                    GPIO / LED
                          │
                          ▼
                  Microphone Capture
                          │
                          ▼
                    Speech-to-Text
                          │
                          ▼
                     Pi Agent
                          │
                          ▼
                  Intent / Tool Call
                          │
                          ▼
                 UNIX Socket / MQTT
                          │
                          ▼
                PlayerController
                    ┌─────┴─────┐
                    │           │
                    ▼           ▼
               GStreamer      Qt/QML
                    │           │
                    ▼           ▼
                 Speaker       Touch UI
```

---

# 🎨 UI Responsibilities

The Qt application intentionally remains focused on **presentation and media control**.

```text
Qt/QML
  │
  ├── Current Track
  ├── Album Artwork
  ├── Artist
  ├── Album
  ├── Track Title
  ├── Playback Progress
  ├── Volume
  └── Player State
```

The agent remains responsible for interpreting natural language.

This separation prevents the UI from becoming coupled to a particular AI model or voice framework.

---

# 🧭 Development Philosophy

The project follows a simple principle:

> **The device should feel like an appliance, not a computer.**

That means:

- No traditional desktop environment
- Fast boot
- Direct hardware access
- Native Qt interface
- Dedicated media pipeline
- Local IPC
- Optional network control
- Agent-driven interaction

The architecture is intentionally modular:

```text
Minimal Linux
      +
Native Qt
      +
GStreamer
      +
Hardware I/O
      +
Agent Interface
      =
Embedded AI Audio Appliance
```

---

# 🛣️ Roadmap

## Phase 1 — Core Player

- [x] Yocto-based Raspberry Pi image
- [x] Qt 6 application
- [x] Qt Quick / QML interface
- [x] GStreamer integration
- [x] Basic player controls
- [x] UNIX Domain Socket IPC
- [x] Python IPC test client
- [ ] Persistent playback state
- [ ] Expanded music library management

## Phase 2 — AIY Voice Interface

- [x] AIY Voice HAT hardware integration
- [x] ALSA soundcard support
- [x] GPIO button integration
- [x] LED status feedback
- [ ] Production voice capture service
- [ ] Speech-to-text integration

## Phase 3 — Agentic Voice Control

- [ ] Local speech-to-text
- [ ] Embedded Whisper-based STT
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

# 🔮 Future Vision

The long-term goal is to turn each Raspberry Pi audio station into a **physical endpoint for an AI agent**.

```text
                         HOME AI
                           │
                         MQTT
                           │
          ┌────────────────┼────────────────┐
          │                │                │
          ▼                ▼                ▼
     ┌──────────┐     ┌──────────┐     ┌──────────┐
     │ Player 1 │     │ Player 2 │     │ Player 3 │
     │ Pi + AIY │     │ Pi + AIY │     │ Pi + AIY │
     └──────────┘     └──────────┘     └──────────┘
```

Each node can provide:

- Physical audio output
- Voice input
- Touch interface
- Local agent endpoint
- Network control
- Distributed playback

The result is not simply an MP3 player.

It is a small **agent-native computing appliance with a physical voice, display, and speaker**.

---

# 🤝 Contributing

Contributions are welcome.

Areas of interest include:

- Yocto recipes
- Raspberry Pi device-tree integration
- Google AIY Voice HAT support
- Qt/QML development
- GStreamer pipelines
- UNIX IPC protocol
- Agent tool definitions
- MQTT protocols
- Embedded speech recognition
- TTS integration
- Hardware documentation

For major architectural changes, please open an issue first.

---

# 📜 License

This project is distributed under the **MIT License**.

See [`LICENSE`](LICENSE) for details.

---

# 🙏 Acknowledgements

This project builds upon the work of:

- [Yocto Project](https://www.yoctoproject.org/)
- [Raspberry Pi](https://www.raspberrypi.com/)
- [Qt](https://www.qt.io/)
- [GStreamer](https://gstreamer.freedesktop.org/)
- [Google AIY Projects](https://aiyprojects.withgoogle.com/)
- [Pi Agent](https://pi.dev)

---

> **Build small. Boot fast. Speak naturally. Let the agent handle the rest.**
