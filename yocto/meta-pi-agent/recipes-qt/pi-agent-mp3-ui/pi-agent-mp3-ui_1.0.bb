SUMMARY = "Pi Agent Qt6 MP3 Player UI"
LICENSE = "CLOSED"

SRC_URI = "file://${TOPDIR}/../../app/qt_ui/src"

S = "${WORKDIR}/src"

inherit cmake qt6-cmake

DEPENDS = "qtbase qtdeclarative qtmultimedia gstreamer1.0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good"

RDEPENDS:${PN} = " \
    qtbase \
    qtdeclarative \
    qtmultimedia \
    qtmultimedia-plugins \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \
    gstreamer1.0-plugins-base-alsa \
    gstreamer1.0-plugins-good \
    gstreamer1.0-plugins-bad \
"

FILES:${PN} += "${bindir}/pi_agent_mp3_ui"
