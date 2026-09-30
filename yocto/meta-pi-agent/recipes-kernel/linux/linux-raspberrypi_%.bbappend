FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

# Force remove KBUILD_DEFCONFIG so Yocto strictly uses SRC_URI's defconfig
KBUILD_DEFCONFIG = ""
KBUILD_DEFCONFIG:raspberrypi3 = ""

SRC_URI += "file://defconfig"
