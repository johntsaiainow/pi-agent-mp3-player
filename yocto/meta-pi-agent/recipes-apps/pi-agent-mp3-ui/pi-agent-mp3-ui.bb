SUMMARY = "Pi Agent MP3 Player UI"
DESCRIPTION = "Qt6 QML MP3 Player User Interface for Raspberry Pi"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

inherit externalsrc qt6-cmake

EXTERNALSRC = "/home/john/workplace/pi-agent-mp3-player/app/qt_ui/src"

DEPENDS = " \
    qtbase \
    qtdeclarative \
    qtdeclarative-native \
    qtmultimedia \
    gstreamer1.0 \
    gstreamer1.0-plugins-base \
"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${B}/pi_agent_mp3_ui ${D}${bindir}/
}

FILES:${PN} += " \
    ${bindir}/pi_agent_mp3_ui \
"
