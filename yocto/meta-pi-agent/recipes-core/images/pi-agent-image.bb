SUMMARY = "Custom Yocto image for Pi Agent MP3 Station with Google AIY Voice Kit v1"
LICENSE = "MIT"

inherit core-image

IMAGE_INSTALL += " \
    packagegroup-core-boot \
    kernel-modules \
    alsa-utils \
    alsa-plugins \
    i2c-tools \
    python3 \
    python3-gpiod \
    \
    qtbase \
    qtdeclarative \
    qtmultimedia \
    qtmultimedia-plugins \
    \
    pi-agent-mp3-ui \
    aiy-service \
"

IMAGE_ROOTFS_SIZE ?= "4194304"
