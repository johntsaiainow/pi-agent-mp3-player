/****************************************************************************
** Meta object code from reading C++ file 'playercontroller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/playercontroller.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playercontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16PlayerControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto PlayerController::qt_create_metaobjectdata<qt_meta_tag_ZN16PlayerControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "PlayerController",
        "isPlayingChanged",
        "",
        "volumeChanged",
        "positionChanged",
        "durationChanged",
        "trackChanged",
        "coverArtUrlChanged",
        "playlistChanged",
        "currentIndexChanged",
        "playPause",
        "setVolume",
        "volume",
        "setPosition",
        "position",
        "addFilesToPlaylist",
        "QList<QUrl>",
        "urls",
        "playAtIndex",
        "index",
        "nextTrack",
        "previousTrack",
        "updateMetaData",
        "handleMediaStatusChanged",
        "QMediaPlayer::MediaStatus",
        "status",
        "handleNewConnection",
        "handleSocketReadyRead",
        "isPlaying",
        "duration",
        "currentTrackTitle",
        "currentArtist",
        "coverArtUrl",
        "playlist",
        "QVariantList",
        "currentIndex"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'isPlayingChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'volumeChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'positionChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'durationChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'trackChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'coverArtUrlChanged'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'playlistChanged'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'currentIndexChanged'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'playPause'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setVolume'
        QtMocHelpers::SlotData<void(float)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 12 },
        }}),
        // Slot 'setPosition'
        QtMocHelpers::SlotData<void(qint64)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::LongLong, 14 },
        }}),
        // Slot 'addFilesToPlaylist'
        QtMocHelpers::SlotData<void(const QList<QUrl> &)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
        // Slot 'playAtIndex'
        QtMocHelpers::SlotData<void(int)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 19 },
        }}),
        // Slot 'nextTrack'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'previousTrack'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateMetaData'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleMediaStatusChanged'
        QtMocHelpers::SlotData<void(QMediaPlayer::MediaStatus)>(23, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Slot 'handleNewConnection'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleSocketReadyRead'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'isPlaying'
        QtMocHelpers::PropertyData<bool>(28, QMetaType::Bool, QMC::DefaultPropertyFlags, 0),
        // property 'volume'
        QtMocHelpers::PropertyData<float>(12, QMetaType::Float, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet, 1),
        // property 'position'
        QtMocHelpers::PropertyData<qint64>(14, QMetaType::LongLong, QMC::DefaultPropertyFlags, 2),
        // property 'duration'
        QtMocHelpers::PropertyData<qint64>(29, QMetaType::LongLong, QMC::DefaultPropertyFlags, 3),
        // property 'currentTrackTitle'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags, 4),
        // property 'currentArtist'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags, 4),
        // property 'coverArtUrl'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags, 5),
        // property 'playlist'
        QtMocHelpers::PropertyData<QVariantList>(33, 0x80000000 | 34, QMC::DefaultPropertyFlags | QMC::EnumOrFlag, 6),
        // property 'currentIndex'
        QtMocHelpers::PropertyData<int>(35, QMetaType::Int, QMC::DefaultPropertyFlags, 7),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<PlayerController, qt_meta_tag_ZN16PlayerControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject PlayerController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16PlayerControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16PlayerControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16PlayerControllerE_t>.metaTypes,
    nullptr
} };

void PlayerController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<PlayerController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->isPlayingChanged(); break;
        case 1: _t->volumeChanged(); break;
        case 2: _t->positionChanged(); break;
        case 3: _t->durationChanged(); break;
        case 4: _t->trackChanged(); break;
        case 5: _t->coverArtUrlChanged(); break;
        case 6: _t->playlistChanged(); break;
        case 7: _t->currentIndexChanged(); break;
        case 8: _t->playPause(); break;
        case 9: _t->setVolume((*reinterpret_cast<std::add_pointer_t<float>>(_a[1]))); break;
        case 10: _t->setPosition((*reinterpret_cast<std::add_pointer_t<qint64>>(_a[1]))); break;
        case 11: _t->addFilesToPlaylist((*reinterpret_cast<std::add_pointer_t<QList<QUrl>>>(_a[1]))); break;
        case 12: _t->playAtIndex((*reinterpret_cast<std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->nextTrack(); break;
        case 14: _t->previousTrack(); break;
        case 15: _t->updateMetaData(); break;
        case 16: _t->handleMediaStatusChanged((*reinterpret_cast<std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 17: _t->handleNewConnection(); break;
        case 18: _t->handleSocketReadyRead(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::isPlayingChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::volumeChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::positionChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::durationChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::trackChanged, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::coverArtUrlChanged, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::playlistChanged, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (PlayerController::*)()>(_a, &PlayerController::currentIndexChanged, 7))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isPlaying(); break;
        case 1: *reinterpret_cast<float*>(_v) = _t->volume(); break;
        case 2: *reinterpret_cast<qint64*>(_v) = _t->position(); break;
        case 3: *reinterpret_cast<qint64*>(_v) = _t->duration(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->currentTrackTitle(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->currentArtist(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->coverArtUrl(); break;
        case 7: *reinterpret_cast<QVariantList*>(_v) = _t->playlist(); break;
        case 8: *reinterpret_cast<int*>(_v) = _t->currentIndex(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 1: _t->setVolume(*reinterpret_cast<float*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *PlayerController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16PlayerControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PlayerController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 19;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void PlayerController::isPlayingChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PlayerController::volumeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PlayerController::positionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PlayerController::durationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PlayerController::trackChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PlayerController::coverArtUrlChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PlayerController::playlistChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void PlayerController::currentIndexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
