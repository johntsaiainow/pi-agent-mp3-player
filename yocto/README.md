# Pi Agent Embedded Audio Station

**Yocto-based Embedded Linux + Qt 6 Platform for Google AIY Voice Kit v1**

> A lightweight, touch-first embedded audio platform for Raspberry Pi 3 B+, built with Yocto Linux, Qt 6, GStreamer, and a local UNIX Domain Socket API for AI-agent integration.

---

## Project Status

**Status:** Proposed / In Development  
**Target Hardware:** Raspberry Pi 3 B+ + Google AIY Voice Kit v1 (Voice HAT)  
**Yocto Release:** Scarthgap (LTS)  
**UI Framework:** Qt 6 / QML  
**Graphics Backend:** EGLFS / DRM/KMS  
**Audio Stack:** GStreamer + ALSA  
**IPC:** UNIX Domain Socket + JSON  
**Init System:** systemd

---

## 1. Overview

The **Pi Agent Embedded Audio Station** is a dedicated Embedded Linux platform designed for the **Google AIY Voice Kit v1** running on a Raspberry Pi 3 B+.

Instead of relying on a traditional desktop environment such as Raspberry Pi OS Desktop, the system provides a minimal embedded image containing only the components required for:

- Touch-based music playback
- High-performance Qt 6 rendering
- Audio playback through the AIY Voice HAT
- ID3 metadata and album-art visualization
- Physical button and LED control
- Local IPC control
- Future voice-assistant and AI-agent integration

The goal is to create a small, fast, deterministic audio appliance where the **Qt application is the primary user interface** and external AI agents can operate the player through a simple local API.

---

## 2. Design Goals

### Primary Goals

- Build a minimal Yocto Linux image for Raspberry Pi 3 B+
- Boot directly into the Qt 6 application
- Avoid X11 and Wayland
- Use DRM/KMS + EGLFS for direct rendering
- Integrate the Google AIY Voice HAT audio hardware
- Provide physical button and LED integration
- Support MP3 playback and metadata visualization
- Provide a stable local IPC interface
- Prepare the platform for AI-agent control

### Non-Goals

This project is **not** intended to provide:

- A general-purpose desktop Linux environment
- A full web browser or desktop GUI
- A conventional window manager
- Cloud-dependent playback control
- A large multimedia framework beyond the requirements of the device

---

# 3. System Architecture

```text
┌────────────────────────────────────────────────────────────────────────┐
│                         USER & HARDWARE                                │
│                                                                        │
│   ┌───────────────────────────┐    ┌──────────────────────────────┐    │
│   │     Qt 6 / QML GUI        │    │     AIY Physical Button     │    │
│   │                           │    │          + LED               │    │
│   │  • Touch UI               │    │                              │    │
│   │  • Playlist               │    │  GPIO 23 → Button            │    │
│   │  • Album Art              │    │  GPIO 25 → LED               │    │
│   │  • Playback Controls      │    │                              │    │
│   └─────────────┬─────────────┘    └──────────────┬───────────────┘    │
│                 │                                 │                    │
└─────────────────┼─────────────────────────────────┼────────────────────┘
                  │ Qt Property Bindings            │ GPIO / gpiod
                  │                                 │
┌─────────────────▼─────────────────────────────────▼────────────────────┐
│                      APPLICATION & BRIDGE LAYER                        │
│                                                                        │
│   ┌───────────────────────────────────────────────────────────────┐    │
│   │                     pi-agent-mp3-ui                            │    │
│   │                                                               │    │
│   │  C++ / Qt 6                                                    │    │
│   │  ├── QMediaPlayer                                              │    │
│   │  ├── PlayerController                                          │    │
│   │  ├── ID3 Metadata                                               │    │
│   │  ├── Album Art / Base64 Data URI                               │    │
│   │  └── UNIX Domain Socket Server                                │    │
│   │                                                               │    │
│   │      /tmp/pi_agent_mp3.sock                                    │    │
│   └──────────────────────────────┬────────────────────────────────┘    │
│                                  │                                     │
│                           JSON IPC Messages                            │
│                                  │                                     │
│   ┌──────────────────────────────▼────────────────────────────────┐    │
│   │                    aiy-button-service                          │    │
│   │                                                               │    │
│   │  Python + systemd                                              │    │
│   │  ├── Monitor GPIO 23                                           │    │
│   │  └── Control GPIO 25 LED                                      │    │
│   └──────────────────────────────┬────────────────────────────────┘    │
│                                  │                                     │
└──────────────────────────────────┼─────────────────────────────────────┘
                                   │
                            GStreamer / ALSA
                                   │
┌──────────────────────────────────▼─────────────────────────────────────┐
│                         LINUX / HARDWARE                              │
│                                                                        │
│   ┌───────────────────────────┐    ┌──────────────────────────────┐    │
│   │   AIY Voice HAT ALSA      │    │      Raspberry Pi VC4        │    │
│   │   Sound Card / I2S        │    │      DRM/KMS GPU Driver      │    │
│   │                           │    │                              │    │
│   │   googlevoicehat-         │    │   Direct EGLFS Rendering     │    │
│   │   soundcard               │    │                              │    │
│   └───────────────────────────┘    └──────────────────────────────┘    │
│                                                                        │
└────────────────────────────────────────────────────────────────────────┘
```

---

# 4. Technology Stack

| Component | Technology |
|---|---|
| Embedded Linux | Yocto Project |
| Yocto Release | Scarthgap LTS |
| Target | Raspberry Pi 3 B+ |
| BSP | `meta-raspberrypi` |
| UI | Qt 6 / QML |
| Rendering | EGLFS + DRM/KMS |
| Multimedia | Qt Multimedia |
| Audio | GStreamer + ALSA |
| Hardware GPIO | libgpiod |
| Init | systemd |
| IPC | UNIX Domain Socket |
| IPC Format | JSON |
| Language | C++, Python, QML |
| Build System | CMake + BitBake |
| Audio Hardware | Google AIY Voice HAT v1 |

---

# 5. Qt 6 Embedded GUI

The graphical interface runs directly on the framebuffer through Qt's **EGLFS** platform plugin.

```text
Qt 6 / QML
     │
     ▼
Qt Platform Abstraction
     │
     ▼
EGLFS
     │
     ▼
DRM/KMS
     │
     ▼
Raspberry Pi VC4 GPU
     │
     ▼
Display
```

This eliminates the need for:

- X11
- Wayland compositor
- Desktop environment
- Window manager

The resulting architecture is intended to reduce system overhead and simplify the runtime environment.

### UI Features

- Touch-oriented controls
- Music playlist navigation
- Play / pause / stop
- Previous / next track
- Volume control
- Album artwork
- ID3 metadata
- Animated album-cover presentation
- Hardware-button interaction
- Agent-controlled playback state

---

# 6. Audio Architecture

Audio playback is handled by **Qt Multimedia**, with the underlying Linux audio stack using GStreamer and ALSA.

```text
QMediaPlayer
     │
     ▼
Qt Multimedia
     │
     ▼
GStreamer
     │
     ▼
ALSA
     │
     ▼
AIY Voice HAT
     │
     ▼
DAC / Amplifier
     │
     ▼
Speaker
```

The Yocto image will provide the required ALSA configuration so that the AIY Voice HAT becomes the default audio device.

Example configuration:

```text
/etc/asound.conf
```

The Raspberry Pi device tree configuration will enable the Voice HAT sound card through the appropriate overlay.

---

# 7. AIY Voice Kit v1 Integration

The Google AIY Voice Kit v1 provides several hardware interfaces that are useful for this platform.

### Audio

The Voice HAT is integrated into the Linux audio subsystem and exposed through ALSA.

The target configuration includes:

```text
dtoverlay=googlevoicehat-soundcard
```

The exact device-tree configuration will be validated against the selected Yocto `meta-raspberrypi` and kernel versions during hardware integration.

### Physical Button

The dedicated button service monitors:

```text
GPIO 23
```

Button events can then be translated into application commands.

### LED

The service controls:

```text
GPIO 25
```

The LED can provide visual feedback for:

- Idle state
- Playback
- Button interaction
- Agent activity
- Error conditions

---

# 8. GPIO Service

The hardware interface is intentionally separated from the Qt application.

```text
AIY Button
    │
    ▼
GPIO 23
    │
    ▼
aiy-button-service
    │
    ├── Event Detection
    ├── Debouncing
    └── LED Control
             │
             ▼
          GPIO 25
```

The service runs under `systemd`.

This separation keeps hardware event handling independent from the graphical application and makes the system easier to debug and extend.

---

# 9. Agent / IPC Architecture

One of the central design goals is to make the audio player controllable by external agents.

The Qt/C++ application exposes a UNIX Domain Socket:

```text
/tmp/pi_agent_mp3.sock
```

External applications can communicate with the player using JSON messages.

```text
┌───────────────────────┐
│ Local AI Agent        │
│ Python Script         │
│ Voice Assistant       │
│ Google AIY Pipeline   │
└──────────┬────────────┘
           │
           │ JSON
           ▼
┌─────────────────────────────┐
│ /tmp/pi_agent_mp3.sock      │
└─────────────┬───────────────┘
              │
              ▼
┌─────────────────────────────┐
│     pi-agent-mp3-ui         │
│                             │
│     PlayerController        │
└─────────────────────────────┘
```

### Example Commands

A future IPC schema can support operations such as:

```json
{
  "command": "play",
  "path": "/music/example.mp3"
}
```

```json
{
  "command": "pause"
}
```

```json
{
  "command": "next"
}
```

```json
{
  "command": "set_volume",
  "value": 0.75
}
```

```json
{
  "command": "get_metadata"
}
```

The protocol should remain deliberately small so that it can be implemented easily by Python agents, shell utilities, or future AI-agent frameworks.

---

# 10. Metadata & Album Art

The player extracts metadata from supported audio files and exposes it to the QML interface.

Typical metadata includes:

- Title
- Artist
- Album
- Track number
- Genre
- Duration
- Embedded album artwork

Album artwork can be converted into a Base64 Data URI for direct use by QML.

```text
MP3
 │
 ├── ID3 Metadata
 │
 └── Embedded Artwork
          │
          ▼
     Base64 Data URI
          │
          ▼
       Qt / QML
```

This avoids requiring a separate HTTP server solely for local artwork delivery.

---

# 11. Yocto Layer

The project will provide a dedicated Yocto layer:

```text
meta-pi-agent/
├── conf/
│   └── layer.conf
│
├── recipes-bsp/
│   └── alsa-state/
│       ├── alsa-state.bbappend
│       └── files/
│           └── asound.conf
│
├── recipes-core/
│   └── images/
│       └── pi-agent-image.bb
│
├── recipes-qt/
│   └── pi-agent-mp3-ui/
│       └── pi-agent-mp3-ui_1.0.bb
│
└── recipes-support/
    └── aiy-service/
        ├── aiy-service_1.0.bb
        └── files/
            ├── aiy_button_service.py
            └── aiy-button.service
```

The layer is responsible for integrating the application, hardware services, system configuration, and final image.

---

# 12. Image Composition

The target image is based on:

```text
core-image-minimal
```

with `systemd` as the init system.

The image will include the minimum required packages for the audio station.

### Core

```text
systemd
bash
```

### Qt

```text
qtbase
qtdeclarative
qtmultimedia
qtmultimedia-plugins
```

### Multimedia

```text
gstreamer1.0
gstreamer1.0-plugins-good
gstreamer1.0-plugins-bad
```

### Audio

```text
alsa-utils
```

### Hardware

```text
python3
python3-gpiod
```

### Application

```text
pi-agent-mp3-ui
aiy-service
```

The final package list will be refined during BitBake integration to avoid unnecessary dependencies.

---

# 13. Repository Structure

A suggested top-level repository structure:

```text
pi-agent-audio-station/
│
├── README.md
├── LICENSE
│
├── docs/
│   ├── architecture.md
│   ├── ipc-protocol.md
│   └── hardware.md
│
├── meta-pi-agent/
│   ├── conf/
│   ├── recipes-bsp/
│   ├── recipes-core/
│   ├── recipes-qt/
│   └── recipes-support/
│
├── pi-agent-mp3-ui/
│   ├── CMakeLists.txt
│   ├── src/
│   ├── qml/
│   └── resources/
│
├── aiy-service/
│   ├── aiy_button_service.py
│   └── aiy-button.service
│
└── tests/
    └── ipc/
        └── test_client.py
```

This separation keeps the application, Yocto integration, hardware services, documentation, and tests independently maintainable.

---

# 14. Development Roadmap

## Phase 1 — Application Core

**Status: Complete**

Development environment:

```text
Ubuntu 26.04 LTS
```

Completed:

- [x] C++ `PlayerController`
- [x] Qt 6 `QMediaPlayer`
- [x] ID3 metadata handling
- [x] QML user interface
- [x] Album-art visualization
- [x] Playlist management
- [x] File selection
- [x] UNIX Domain Socket server
- [x] Python IPC test client

---

## Phase 2 — Yocto BSP Integration

**Status: In Progress**

Tasks:

- [ ] Create `meta-pi-agent`
- [ ] Configure Yocto Scarthgap
- [ ] Integrate `meta-raspberrypi`
- [ ] Configure Raspberry Pi 3 B+
- [ ] Enable AIY Voice HAT device tree configuration
- [ ] Package Qt application as BitBake recipe
- [ ] Package GPIO service
- [ ] Configure ALSA
- [ ] Build `pi-agent-image`

Target artifact:

```text
pi-agent-image.wic.bz2
```

---

## Phase 3 — Hardware Validation

**Status: Planned**

Target hardware:

```text
Raspberry Pi 3 B+
        +
Google AIY Voice Kit v1
        +
Display / Touchscreen
```

Validation checklist:

- [ ] Boot from SD card
- [ ] Verify kernel initialization
- [ ] Verify DRM/KMS
- [ ] Verify EGLFS rendering
- [ ] Verify Qt 6 startup
- [ ] Verify touchscreen input
- [ ] Verify AIY ALSA device
- [ ] Verify speaker output
- [ ] Verify microphone input
- [ ] Verify GPIO 23 button
- [ ] Verify GPIO 25 LED
- [ ] Verify IPC socket
- [ ] Verify end-to-end playback

---

# 15. Phase 4 — Agentic Extension

**Status: Planned**

The local IPC layer provides the foundation for integrating external AI systems.

Potential architecture:

```text
              ┌─────────────────────┐
              │     AI / LLM Agent   │
              └──────────┬──────────┘
                         │
                  Tool / Function Call
                         │
                         ▼
              ┌─────────────────────┐
              │   Local Agent Tool  │
              │     / Python        │
              └──────────┬──────────┘
                         │
                      JSON IPC
                         │
                         ▼
              ┌─────────────────────┐
              │ pi-agent-mp3-ui     │
              │                     │
              │ PlayerController    │
              └──────────┬──────────┘
                         │
                         ▼
                    GStreamer
                         │
                         ▼
                   AIY Voice HAT
```

Possible future capabilities include:

- Voice-controlled playback
- Natural-language music search
- Agent-controlled playlists
- Volume commands
- Playback-state queries
- Metadata queries
- Multi-agent local control
- Integration with home AI infrastructure

The IPC boundary intentionally keeps the audio appliance independent from the AI implementation.

---

# 16. Building the Yocto Image

## Clone Yocto Dependencies

```bash
git clone -b scarthgap git://git.yoctoproject.org/poky
git clone -b scarthgap git://git.openembedded.org/meta-openembedded
git clone -b scarthgap git://git.yoctoproject.org/meta-raspberrypi
git clone -b scarthgap https://code.qt.io/yocto/meta-qt6.git
git clone https://github.com/<your-username>/meta-pi-agent.git
```

## Initialize the Build Environment

```bash
source poky/oe-init-build-env build-rpi3
```

## Add Layers

```bash
bitbake-layers add-layer \
    ../meta-openembedded/meta-oe \
    ../meta-openembedded/meta-python \
    ../meta-raspberrypi \
    ../meta-qt6 \
    ../meta-pi-agent
```

## Build

```bash
bitbake pi-agent-image
```

The resulting image should be generated under:

```text
tmp/deploy/images/raspberrypi3/
```

---

# 17. Development Philosophy

The platform follows several architectural principles.

### Minimal

Only software required by the audio station should be included in the production image.

### Deterministic

The device should boot into a known application state without depending on a desktop session.

### Local-First

Playback and hardware control should continue to function locally without requiring cloud services.

### Modular

The Qt application, GPIO service, Yocto layer, and AI-agent interface remain separate components.

### Agent-Ready

The system should expose stable machine-readable interfaces instead of coupling AI logic directly to the GUI.

### Hardware-Aware

The software stack is designed around the actual capabilities and constraints of the Raspberry Pi 3 B+ and AIY Voice HAT.

---

# 18. Long-Term Architecture

The intended evolution is:

```text
                ┌─────────────────────┐
                │      AI Agents      │
                │                     │
                │  Voice / LLM / MCP  │
                └──────────┬──────────┘
                           │
                           ▼
                 ┌──────────────────┐
                 │   Agent Bridge   │
                 └────────┬─────────┘
                          │
                     JSON / IPC
                          │
                          ▼
              ┌────────────────────────┐
              │   Pi Agent Platform    │
              │                        │
              │  Qt 6 + C++            │
              │  Audio + Metadata      │
              │  Hardware Services     │
              └───────────┬────────────┘
                          │
                          ▼
                ┌───────────────────┐
                │ Raspberry Pi 3 B+ │
                │                   │
                │ Google AIY HAT    │
                └───────────────────┘
```

This allows the embedded device to remain a focused **audio appliance**, while increasingly sophisticated intelligence can live outside the UI process.

---

# 19. Current Milestone

The project has successfully established the **application-layer foundation** on Ubuntu 26.04 LTS.

The next major engineering step is to move the existing Qt 6 application into a reproducible **Yocto Scarthgap image** and validate the complete hardware path on Raspberry Pi 3 B+.

The resulting system will provide a clean boundary between:

```text
Embedded Hardware
       ↓
Linux / Yocto
       ↓
Qt 6 Application
       ↓
Local IPC
       ↓
AI Agent
```

That boundary is the core architectural decision of the project.

---

## License

License: **TBD**

---

*Pi Agent Embedded Audio Station — a small embedded computer with a clean path from physical hardware to local AI.*
