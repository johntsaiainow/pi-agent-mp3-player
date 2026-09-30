SUMMARY = "Queen Greatest Hits audio tracks"
DESCRIPTION = "Installs FLAC audio files into /root/Music for Pi Agent MP3 Player"
LICENSE = "CLOSED"

SRC_URI = " \
    file://01.Bohemian%20Rhapsody.flac \
    file://02.Another%20One%20Bites%20The%20Dust.flac \
    file://03.Killer%20Queen.flac \
    file://04.Fat%20Bottomed%20Girls.flac \
    file://05.Bicycle%20Race.flac \
    file://06.You're%20My%20Best%20Friend.flac \
    file://07.Don't%20Stop%20Me%20Now.flac \
    file://08.Save%20Me.flac \
    file://09.Crazy%20Little%20Thing%20Called%20Love.flac \
    file://10.Somebody%20To%20Love.flac \
    file://11.Now%20I'm%20Here.flac \
    file://12.Good%20Old-Fashioned%20Lover%20Boy.flac \
    file://13.Play%20The%20Game.flac \
    file://14.Flash.flac \
    file://15.Seven%20Seas%20Of%20Rhye.flac \
    file://16.We%20Will%20Rock%20You.flac \
    file://17.We%20Are%20The%20Champions.flac \
    file://18.Teo%20Torriatte%20(Let%20Us%20Cling%20Together).flac \
"

S = "${WORKDIR}"

do_install() {
    install -d ${D}/root/Music

    UNPACK_DIR="${UNPACKDIR}"
    if [ -z "$UNPACK_DIR" ]; then
        UNPACK_DIR="${WORKDIR}"
    fi

    find "$UNPACK_DIR" -name "*.flac" -exec install -m 0644 {} ${D}/root/Music/ \;
}

FILES:${PN} = "/root /root/Music /root/Music/*"
