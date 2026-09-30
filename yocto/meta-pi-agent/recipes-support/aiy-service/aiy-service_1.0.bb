SUMMARY = "Google AIY Voice Kit v1 GPIO & LED Bridge Service"
LICENSE = "CLOSED"

SRC_URI = " \
    file://aiy_button_service.py \
    file://aiy-button.service \
"

S = "${WORKDIR}"

inherit systemd

SYSTEMD_SERVICE:${PN} = "aiy-button.service"
SYSTEMD_AUTO_ENABLE = "enable"

RDEPENDS:${PN} = "python3-core python3-gpiod"

do_install() {
    install -d ${D}${bindir}
    install -m 0755 ${WORKDIR}/aiy_button_service.py ${D}${bindir}/

    install -d ${D}${systemd_system_unitdir}
    install -m 0644 ${WORKDIR}/aiy-button.service ${D}${systemd_system_unitdir}/
}

FILES:${PN} += " \
    ${bindir}/aiy_button_service.py \
    ${systemd_system_unitdir}/aiy-button.service \
"
