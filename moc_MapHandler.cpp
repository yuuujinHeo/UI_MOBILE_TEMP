/****************************************************************************
** Meta object code from reading C++ file 'MapHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MapHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapHandler_t {
    QByteArrayData data[104];
    char stringdata0[1186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MapHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MapHandler_t qt_meta_stringdata_MapHandler = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MapHandler"
QT_MOC_LITERAL(1, 11, 7), // "onTimer"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "loadFile"
QT_MOC_LITERAL(4, 29, 4), // "name"
QT_MOC_LITERAL(5, 34, 4), // "type"
QT_MOC_LITERAL(6, 39, 6), // "setMap"
QT_MOC_LITERAL(7, 46, 10), // "setMapTest"
QT_MOC_LITERAL(8, 57, 11), // "setMapLayer"
QT_MOC_LITERAL(9, 69, 13), // "setFullScreen"
QT_MOC_LITERAL(10, 83, 13), // "setMapDrawing"
QT_MOC_LITERAL(11, 97, 7), // "setName"
QT_MOC_LITERAL(12, 105, 7), // "setTool"
QT_MOC_LITERAL(13, 113, 7), // "getTool"
QT_MOC_LITERAL(14, 121, 7), // "setMode"
QT_MOC_LITERAL(15, 129, 9), // "setEnable"
QT_MOC_LITERAL(16, 139, 2), // "en"
QT_MOC_LITERAL(17, 142, 7), // "getMode"
QT_MOC_LITERAL(18, 150, 12), // "setShowBrush"
QT_MOC_LITERAL(19, 163, 5), // "onoff"
QT_MOC_LITERAL(20, 169, 12), // "setShowLidar"
QT_MOC_LITERAL(21, 182, 15), // "setShowLocation"
QT_MOC_LITERAL(22, 198, 17), // "setRobotFollowing"
QT_MOC_LITERAL(23, 216, 13), // "setShowObject"
QT_MOC_LITERAL(24, 230, 15), // "setShowAvoidMap"
QT_MOC_LITERAL(25, 246, 12), // "setShowRobot"
QT_MOC_LITERAL(26, 259, 17), // "setShowTravelline"
QT_MOC_LITERAL(27, 277, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(28, 296, 15), // "getshowLocation"
QT_MOC_LITERAL(29, 312, 17), // "getRobotFollowing"
QT_MOC_LITERAL(30, 330, 12), // "getShowLidar"
QT_MOC_LITERAL(31, 343, 11), // "setInitPose"
QT_MOC_LITERAL(32, 355, 1), // "x"
QT_MOC_LITERAL(33, 357, 1), // "y"
QT_MOC_LITERAL(34, 359, 2), // "th"
QT_MOC_LITERAL(35, 362, 13), // "clearInitPose"
QT_MOC_LITERAL(36, 376, 11), // "setInitFlag"
QT_MOC_LITERAL(37, 388, 17), // "startDrawingTline"
QT_MOC_LITERAL(38, 406, 16), // "stopDrawingTline"
QT_MOC_LITERAL(39, 423, 15), // "getDrawingTline"
QT_MOC_LITERAL(40, 439, 13), // "setRulerPoint"
QT_MOC_LITERAL(41, 453, 11), // "setBoxPoint"
QT_MOC_LITERAL(42, 465, 3), // "num"
QT_MOC_LITERAL(43, 469, 11), // "getPointBox"
QT_MOC_LITERAL(44, 481, 13), // "saveRotateMap"
QT_MOC_LITERAL(45, 495, 10), // "initRotate"
QT_MOC_LITERAL(46, 506, 9), // "rotateMap"
QT_MOC_LITERAL(47, 516, 5), // "angle"
QT_MOC_LITERAL(48, 522, 11), // "rotateMapCW"
QT_MOC_LITERAL(49, 534, 12), // "rotateMapCCW"
QT_MOC_LITERAL(50, 547, 13), // "saveObjectPNG"
QT_MOC_LITERAL(51, 561, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(52, 576, 14), // "getDrawingFlag"
QT_MOC_LITERAL(53, 591, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(54, 610, 12), // "startDrawing"
QT_MOC_LITERAL(55, 623, 12), // "addLinePoint"
QT_MOC_LITERAL(56, 636, 10), // "endDrawing"
QT_MOC_LITERAL(57, 647, 16), // "startDrawingRect"
QT_MOC_LITERAL(58, 664, 14), // "setDrawingRect"
QT_MOC_LITERAL(59, 679, 14), // "endDrawingRect"
QT_MOC_LITERAL(60, 694, 12), // "clearDrawing"
QT_MOC_LITERAL(61, 707, 8), // "undoLine"
QT_MOC_LITERAL(62, 716, 8), // "redoLine"
QT_MOC_LITERAL(63, 725, 11), // "startSpline"
QT_MOC_LITERAL(64, 737, 9), // "addSpline"
QT_MOC_LITERAL(65, 747, 10), // "drawSpline"
QT_MOC_LITERAL(66, 758, 9), // "endSpline"
QT_MOC_LITERAL(67, 768, 4), // "save"
QT_MOC_LITERAL(68, 773, 16), // "startDrawingLine"
QT_MOC_LITERAL(69, 790, 14), // "setDrawingLine"
QT_MOC_LITERAL(70, 805, 15), // "stopDrawingLine"
QT_MOC_LITERAL(71, 821, 12), // "setLineColor"
QT_MOC_LITERAL(72, 834, 5), // "color"
QT_MOC_LITERAL(73, 840, 12), // "setLineWidth"
QT_MOC_LITERAL(74, 853, 5), // "width"
QT_MOC_LITERAL(75, 859, 18), // "setTravellineIssue"
QT_MOC_LITERAL(76, 878, 5), // "count"
QT_MOC_LITERAL(77, 884, 17), // "setSelectLocation"
QT_MOC_LITERAL(78, 902, 13), // "clearLocation"
QT_MOC_LITERAL(79, 916, 11), // "addLocation"
QT_MOC_LITERAL(80, 928, 14), // "addLocationCur"
QT_MOC_LITERAL(81, 943, 11), // "setLocation"
QT_MOC_LITERAL(82, 955, 12), // "editLocation"
QT_MOC_LITERAL(83, 968, 14), // "getLocationNum"
QT_MOC_LITERAL(84, 983, 14), // "removeLocation"
QT_MOC_LITERAL(85, 998, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(86, 1017, 14), // "getLocGroupNum"
QT_MOC_LITERAL(87, 1032, 7), // "saveMap"
QT_MOC_LITERAL(88, 1040, 13), // "saveEditedMap"
QT_MOC_LITERAL(89, 1054, 9), // "saveTline"
QT_MOC_LITERAL(90, 1064, 13), // "saveTlineTemp"
QT_MOC_LITERAL(91, 1078, 10), // "saveVelmap"
QT_MOC_LITERAL(92, 1089, 10), // "setMapSize"
QT_MOC_LITERAL(93, 1100, 6), // "height"
QT_MOC_LITERAL(94, 1107, 6), // "zoomIn"
QT_MOC_LITERAL(95, 1114, 4), // "dist"
QT_MOC_LITERAL(96, 1119, 7), // "zoomOut"
QT_MOC_LITERAL(97, 1127, 4), // "move"
QT_MOC_LITERAL(98, 1132, 12), // "getFileWidth"
QT_MOC_LITERAL(99, 1145, 4), // "getX"
QT_MOC_LITERAL(100, 1150, 4), // "getY"
QT_MOC_LITERAL(101, 1155, 8), // "getScale"
QT_MOC_LITERAL(102, 1164, 7), // "setSize"
QT_MOC_LITERAL(103, 1172, 13) // "getCutBoxFlag"

    },
    "MapHandler\0onTimer\0\0loadFile\0name\0"
    "type\0setMap\0setMapTest\0setMapLayer\0"
    "setFullScreen\0setMapDrawing\0setName\0"
    "setTool\0getTool\0setMode\0setEnable\0en\0"
    "getMode\0setShowBrush\0onoff\0setShowLidar\0"
    "setShowLocation\0setRobotFollowing\0"
    "setShowObject\0setShowAvoidMap\0"
    "setShowRobot\0setShowTravelline\0"
    "setShowVelocitymap\0getshowLocation\0"
    "getRobotFollowing\0getShowLidar\0"
    "setInitPose\0x\0y\0th\0clearInitPose\0"
    "setInitFlag\0startDrawingTline\0"
    "stopDrawingTline\0getDrawingTline\0"
    "setRulerPoint\0setBoxPoint\0num\0getPointBox\0"
    "saveRotateMap\0initRotate\0rotateMap\0"
    "angle\0rotateMapCW\0rotateMapCCW\0"
    "saveObjectPNG\0saveObsAreaPNG\0"
    "getDrawingFlag\0getDrawingUndoFlag\0"
    "startDrawing\0addLinePoint\0endDrawing\0"
    "startDrawingRect\0setDrawingRect\0"
    "endDrawingRect\0clearDrawing\0undoLine\0"
    "redoLine\0startSpline\0addSpline\0"
    "drawSpline\0endSpline\0save\0startDrawingLine\0"
    "setDrawingLine\0stopDrawingLine\0"
    "setLineColor\0color\0setLineWidth\0width\0"
    "setTravellineIssue\0count\0setSelectLocation\0"
    "clearLocation\0addLocation\0addLocationCur\0"
    "setLocation\0editLocation\0getLocationNum\0"
    "removeLocation\0setTableNumberAuto\0"
    "getLocGroupNum\0saveMap\0saveEditedMap\0"
    "saveTline\0saveTlineTemp\0saveVelmap\0"
    "setMapSize\0height\0zoomIn\0dist\0zoomOut\0"
    "move\0getFileWidth\0getX\0getY\0getScale\0"
    "setSize\0getCutBoxFlag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      88,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  454,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       3,    2,  455,    2, 0x02 /* Public */,
       6,    0,  460,    2, 0x02 /* Public */,
       7,    0,  461,    2, 0x02 /* Public */,
       8,    0,  462,    2, 0x02 /* Public */,
       9,    0,  463,    2, 0x02 /* Public */,
      10,    0,  464,    2, 0x02 /* Public */,
      11,    1,  465,    2, 0x02 /* Public */,
      12,    1,  468,    2, 0x02 /* Public */,
      13,    0,  471,    2, 0x02 /* Public */,
      14,    1,  472,    2, 0x02 /* Public */,
      15,    1,  475,    2, 0x02 /* Public */,
      17,    0,  478,    2, 0x02 /* Public */,
      18,    1,  479,    2, 0x02 /* Public */,
      20,    1,  482,    2, 0x02 /* Public */,
      21,    1,  485,    2, 0x02 /* Public */,
      22,    1,  488,    2, 0x02 /* Public */,
      23,    1,  491,    2, 0x02 /* Public */,
      24,    1,  494,    2, 0x02 /* Public */,
      25,    1,  497,    2, 0x02 /* Public */,
      26,    1,  500,    2, 0x02 /* Public */,
      27,    1,  503,    2, 0x02 /* Public */,
      28,    0,  506,    2, 0x02 /* Public */,
      29,    0,  507,    2, 0x02 /* Public */,
      30,    0,  508,    2, 0x02 /* Public */,
      31,    3,  509,    2, 0x02 /* Public */,
      35,    0,  516,    2, 0x02 /* Public */,
      36,    1,  517,    2, 0x02 /* Public */,
      37,    0,  520,    2, 0x02 /* Public */,
      38,    0,  521,    2, 0x02 /* Public */,
      39,    0,  522,    2, 0x02 /* Public */,
      40,    2,  523,    2, 0x02 /* Public */,
      41,    3,  528,    2, 0x02 /* Public */,
      43,    2,  535,    2, 0x02 /* Public */,
      44,    0,  540,    2, 0x02 /* Public */,
      45,    0,  541,    2, 0x02 /* Public */,
      46,    1,  542,    2, 0x02 /* Public */,
      48,    0,  545,    2, 0x02 /* Public */,
      49,    0,  546,    2, 0x02 /* Public */,
      50,    0,  547,    2, 0x02 /* Public */,
      51,    0,  548,    2, 0x02 /* Public */,
      52,    0,  549,    2, 0x02 /* Public */,
      53,    0,  550,    2, 0x02 /* Public */,
      54,    2,  551,    2, 0x02 /* Public */,
      55,    2,  556,    2, 0x02 /* Public */,
      56,    2,  561,    2, 0x02 /* Public */,
      57,    2,  566,    2, 0x02 /* Public */,
      58,    2,  571,    2, 0x02 /* Public */,
      59,    0,  576,    2, 0x02 /* Public */,
      60,    0,  577,    2, 0x02 /* Public */,
      61,    0,  578,    2, 0x02 /* Public */,
      62,    0,  579,    2, 0x02 /* Public */,
      63,    2,  580,    2, 0x02 /* Public */,
      64,    2,  585,    2, 0x02 /* Public */,
      65,    0,  590,    2, 0x02 /* Public */,
      66,    1,  591,    2, 0x02 /* Public */,
      68,    2,  594,    2, 0x02 /* Public */,
      69,    2,  599,    2, 0x02 /* Public */,
      70,    2,  604,    2, 0x02 /* Public */,
      71,    1,  609,    2, 0x02 /* Public */,
      73,    1,  612,    2, 0x02 /* Public */,
      75,    2,  615,    2, 0x02 /* Public */,
      77,    1,  620,    2, 0x02 /* Public */,
      78,    0,  623,    2, 0x02 /* Public */,
      79,    3,  624,    2, 0x02 /* Public */,
      80,    3,  631,    2, 0x02 /* Public */,
      81,    3,  638,    2, 0x02 /* Public */,
      82,    3,  645,    2, 0x02 /* Public */,
      83,    2,  652,    2, 0x02 /* Public */,
      84,    1,  657,    2, 0x02 /* Public */,
      85,    0,  660,    2, 0x02 /* Public */,
      83,    1,  661,    2, 0x02 /* Public */,
      86,    1,  664,    2, 0x02 /* Public */,
      87,    0,  667,    2, 0x02 /* Public */,
      88,    0,  668,    2, 0x02 /* Public */,
      89,    0,  669,    2, 0x02 /* Public */,
      90,    0,  670,    2, 0x02 /* Public */,
      91,    0,  671,    2, 0x02 /* Public */,
      92,    2,  672,    2, 0x02 /* Public */,
      94,    3,  677,    2, 0x02 /* Public */,
      96,    3,  684,    2, 0x02 /* Public */,
      97,    2,  691,    2, 0x02 /* Public */,
      98,    0,  696,    2, 0x02 /* Public */,
      99,    0,  697,    2, 0x02 /* Public */,
     100,    0,  698,    2, 0x02 /* Public */,
     101,    0,  699,    2, 0x02 /* Public */,
     102,    3,  700,    2, 0x02 /* Public */,
     103,    0,  707,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   42,   32,   33,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   67,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int,   72,
    QMetaType::Void, QMetaType::Int,   74,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   76,   42,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   34,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,    5,
    QMetaType::Int, QMetaType::Int,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   93,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   95,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   95,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   33,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   32,   33,   74,
    QMetaType::Bool,

       0        // eod
};

void MapHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MapHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onTimer(); break;
        case 1: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->setMap(); break;
        case 3: _t->setMapTest(); break;
        case 4: _t->setMapLayer(); break;
        case 5: _t->setFullScreen(); break;
        case 6: _t->setMapDrawing(); break;
        case 7: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->setShowAvoidMap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->setShowRobot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 24: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 26: _t->clearInitPose(); break;
        case 27: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 28: _t->startDrawingTline(); break;
        case 29: _t->stopDrawingTline(); break;
        case 30: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: _t->setRulerPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 32: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 33: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->saveRotateMap(); break;
        case 35: _t->initRotate(); break;
        case 36: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 37: _t->rotateMapCW(); break;
        case 38: _t->rotateMapCCW(); break;
        case 39: _t->saveObjectPNG(); break;
        case 40: _t->saveObsAreaPNG(); break;
        case 41: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 42: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 43: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 44: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 45: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 46: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 47: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 48: _t->endDrawingRect(); break;
        case 49: _t->clearDrawing(); break;
        case 50: _t->undoLine(); break;
        case 51: _t->redoLine(); break;
        case 52: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 53: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 54: _t->drawSpline(); break;
        case 55: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 57: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 58: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 59: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 60: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 61: _t->setTravellineIssue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 62: _t->setSelectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->clearLocation(); break;
        case 64: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 65: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 66: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 67: _t->editLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 68: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 69: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 70: _t->setTableNumberAuto(); break;
        case 71: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 72: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 73: _t->saveMap(); break;
        case 74: _t->saveEditedMap(); break;
        case 75: _t->saveTline(); break;
        case 76: _t->saveTlineTemp(); break;
        case 77: _t->saveVelmap(); break;
        case 78: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 79: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 80: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 81: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 82: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 83: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 84: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 85: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 86: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 87: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MapHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MapHandler.data,
    qt_meta_data_MapHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MapHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MapHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MapHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MapHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 88)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 88;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 88)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 88;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
