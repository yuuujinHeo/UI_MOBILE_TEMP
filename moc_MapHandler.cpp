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
    char stringdata0[1180];
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
QT_MOC_LITERAL(9, 69, 7), // "moveMap"
QT_MOC_LITERAL(10, 77, 13), // "setFullScreen"
QT_MOC_LITERAL(11, 91, 13), // "setMapDrawing"
QT_MOC_LITERAL(12, 105, 7), // "setName"
QT_MOC_LITERAL(13, 113, 7), // "setTool"
QT_MOC_LITERAL(14, 121, 7), // "getTool"
QT_MOC_LITERAL(15, 129, 7), // "setMode"
QT_MOC_LITERAL(16, 137, 9), // "setEnable"
QT_MOC_LITERAL(17, 147, 2), // "en"
QT_MOC_LITERAL(18, 150, 7), // "getMode"
QT_MOC_LITERAL(19, 158, 12), // "setShowBrush"
QT_MOC_LITERAL(20, 171, 5), // "onoff"
QT_MOC_LITERAL(21, 177, 12), // "setShowLidar"
QT_MOC_LITERAL(22, 190, 15), // "setShowLocation"
QT_MOC_LITERAL(23, 206, 17), // "setRobotFollowing"
QT_MOC_LITERAL(24, 224, 13), // "setShowObject"
QT_MOC_LITERAL(25, 238, 15), // "setShowAvoidMap"
QT_MOC_LITERAL(26, 254, 12), // "setShowRobot"
QT_MOC_LITERAL(27, 267, 17), // "setShowTravelline"
QT_MOC_LITERAL(28, 285, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(29, 304, 15), // "getshowLocation"
QT_MOC_LITERAL(30, 320, 17), // "getRobotFollowing"
QT_MOC_LITERAL(31, 338, 12), // "getShowLidar"
QT_MOC_LITERAL(32, 351, 11), // "setInitPose"
QT_MOC_LITERAL(33, 363, 1), // "x"
QT_MOC_LITERAL(34, 365, 1), // "y"
QT_MOC_LITERAL(35, 367, 2), // "th"
QT_MOC_LITERAL(36, 370, 13), // "clearInitPose"
QT_MOC_LITERAL(37, 384, 11), // "setInitFlag"
QT_MOC_LITERAL(38, 396, 17), // "startDrawingTline"
QT_MOC_LITERAL(39, 414, 16), // "stopDrawingTline"
QT_MOC_LITERAL(40, 431, 15), // "getDrawingTline"
QT_MOC_LITERAL(41, 447, 11), // "setBoxPoint"
QT_MOC_LITERAL(42, 459, 3), // "num"
QT_MOC_LITERAL(43, 463, 11), // "getPointBox"
QT_MOC_LITERAL(44, 475, 13), // "saveRotateMap"
QT_MOC_LITERAL(45, 489, 10), // "initRotate"
QT_MOC_LITERAL(46, 500, 9), // "rotateMap"
QT_MOC_LITERAL(47, 510, 5), // "angle"
QT_MOC_LITERAL(48, 516, 11), // "rotateMapCW"
QT_MOC_LITERAL(49, 528, 12), // "rotateMapCCW"
QT_MOC_LITERAL(50, 541, 13), // "saveObjectPNG"
QT_MOC_LITERAL(51, 555, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(52, 570, 14), // "getDrawingFlag"
QT_MOC_LITERAL(53, 585, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(54, 604, 12), // "startDrawing"
QT_MOC_LITERAL(55, 617, 12), // "addLinePoint"
QT_MOC_LITERAL(56, 630, 10), // "endDrawing"
QT_MOC_LITERAL(57, 641, 16), // "startDrawingRect"
QT_MOC_LITERAL(58, 658, 14), // "setDrawingRect"
QT_MOC_LITERAL(59, 673, 14), // "endDrawingRect"
QT_MOC_LITERAL(60, 688, 12), // "clearDrawing"
QT_MOC_LITERAL(61, 701, 8), // "undoLine"
QT_MOC_LITERAL(62, 710, 8), // "redoLine"
QT_MOC_LITERAL(63, 719, 11), // "startSpline"
QT_MOC_LITERAL(64, 731, 9), // "addSpline"
QT_MOC_LITERAL(65, 741, 10), // "drawSpline"
QT_MOC_LITERAL(66, 752, 9), // "endSpline"
QT_MOC_LITERAL(67, 762, 4), // "save"
QT_MOC_LITERAL(68, 767, 16), // "startDrawingLine"
QT_MOC_LITERAL(69, 784, 14), // "setDrawingLine"
QT_MOC_LITERAL(70, 799, 15), // "stopDrawingLine"
QT_MOC_LITERAL(71, 815, 12), // "setLineColor"
QT_MOC_LITERAL(72, 828, 5), // "color"
QT_MOC_LITERAL(73, 834, 12), // "setLineWidth"
QT_MOC_LITERAL(74, 847, 5), // "width"
QT_MOC_LITERAL(75, 853, 18), // "setTravellineIssue"
QT_MOC_LITERAL(76, 872, 5), // "count"
QT_MOC_LITERAL(77, 878, 17), // "setSelectLocation"
QT_MOC_LITERAL(78, 896, 13), // "clearLocation"
QT_MOC_LITERAL(79, 910, 11), // "addLocation"
QT_MOC_LITERAL(80, 922, 14), // "addLocationCur"
QT_MOC_LITERAL(81, 937, 11), // "setLocation"
QT_MOC_LITERAL(82, 949, 12), // "editLocation"
QT_MOC_LITERAL(83, 962, 14), // "getLocationNum"
QT_MOC_LITERAL(84, 977, 14), // "removeLocation"
QT_MOC_LITERAL(85, 992, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(86, 1011, 14), // "getLocGroupNum"
QT_MOC_LITERAL(87, 1026, 7), // "saveMap"
QT_MOC_LITERAL(88, 1034, 13), // "saveEditedMap"
QT_MOC_LITERAL(89, 1048, 9), // "saveTline"
QT_MOC_LITERAL(90, 1058, 13), // "saveTlineTemp"
QT_MOC_LITERAL(91, 1072, 10), // "saveVelmap"
QT_MOC_LITERAL(92, 1083, 10), // "setMapSize"
QT_MOC_LITERAL(93, 1094, 6), // "height"
QT_MOC_LITERAL(94, 1101, 6), // "zoomIn"
QT_MOC_LITERAL(95, 1108, 4), // "dist"
QT_MOC_LITERAL(96, 1113, 7), // "zoomOut"
QT_MOC_LITERAL(97, 1121, 4), // "move"
QT_MOC_LITERAL(98, 1126, 12), // "getFileWidth"
QT_MOC_LITERAL(99, 1139, 4), // "getX"
QT_MOC_LITERAL(100, 1144, 4), // "getY"
QT_MOC_LITERAL(101, 1149, 8), // "getScale"
QT_MOC_LITERAL(102, 1158, 7), // "setSize"
QT_MOC_LITERAL(103, 1166, 13) // "getCutBoxFlag"

    },
    "MapHandler\0onTimer\0\0loadFile\0name\0"
    "type\0setMap\0setMapTest\0setMapLayer\0"
    "moveMap\0setFullScreen\0setMapDrawing\0"
    "setName\0setTool\0getTool\0setMode\0"
    "setEnable\0en\0getMode\0setShowBrush\0"
    "onoff\0setShowLidar\0setShowLocation\0"
    "setRobotFollowing\0setShowObject\0"
    "setShowAvoidMap\0setShowRobot\0"
    "setShowTravelline\0setShowVelocitymap\0"
    "getshowLocation\0getRobotFollowing\0"
    "getShowLidar\0setInitPose\0x\0y\0th\0"
    "clearInitPose\0setInitFlag\0startDrawingTline\0"
    "stopDrawingTline\0getDrawingTline\0"
    "setBoxPoint\0num\0getPointBox\0saveRotateMap\0"
    "initRotate\0rotateMap\0angle\0rotateMapCW\0"
    "rotateMapCCW\0saveObjectPNG\0saveObsAreaPNG\0"
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
      11,    0,  465,    2, 0x02 /* Public */,
      12,    1,  466,    2, 0x02 /* Public */,
      13,    1,  469,    2, 0x02 /* Public */,
      14,    0,  472,    2, 0x02 /* Public */,
      15,    1,  473,    2, 0x02 /* Public */,
      16,    1,  476,    2, 0x02 /* Public */,
      18,    0,  479,    2, 0x02 /* Public */,
      19,    1,  480,    2, 0x02 /* Public */,
      21,    1,  483,    2, 0x02 /* Public */,
      22,    1,  486,    2, 0x02 /* Public */,
      23,    1,  489,    2, 0x02 /* Public */,
      24,    1,  492,    2, 0x02 /* Public */,
      25,    1,  495,    2, 0x02 /* Public */,
      26,    1,  498,    2, 0x02 /* Public */,
      27,    1,  501,    2, 0x02 /* Public */,
      28,    1,  504,    2, 0x02 /* Public */,
      29,    0,  507,    2, 0x02 /* Public */,
      30,    0,  508,    2, 0x02 /* Public */,
      31,    0,  509,    2, 0x02 /* Public */,
      32,    3,  510,    2, 0x02 /* Public */,
      36,    0,  517,    2, 0x02 /* Public */,
      37,    1,  518,    2, 0x02 /* Public */,
      38,    0,  521,    2, 0x02 /* Public */,
      39,    0,  522,    2, 0x02 /* Public */,
      40,    0,  523,    2, 0x02 /* Public */,
      41,    3,  524,    2, 0x02 /* Public */,
      43,    2,  531,    2, 0x02 /* Public */,
      44,    0,  536,    2, 0x02 /* Public */,
      45,    0,  537,    2, 0x02 /* Public */,
      46,    1,  538,    2, 0x02 /* Public */,
      48,    0,  541,    2, 0x02 /* Public */,
      49,    0,  542,    2, 0x02 /* Public */,
      50,    0,  543,    2, 0x02 /* Public */,
      51,    0,  544,    2, 0x02 /* Public */,
      52,    0,  545,    2, 0x02 /* Public */,
      53,    0,  546,    2, 0x02 /* Public */,
      54,    2,  547,    2, 0x02 /* Public */,
      55,    2,  552,    2, 0x02 /* Public */,
      56,    2,  557,    2, 0x02 /* Public */,
      57,    2,  562,    2, 0x02 /* Public */,
      58,    2,  567,    2, 0x02 /* Public */,
      59,    0,  572,    2, 0x02 /* Public */,
      60,    0,  573,    2, 0x02 /* Public */,
      61,    0,  574,    2, 0x02 /* Public */,
      62,    0,  575,    2, 0x02 /* Public */,
      63,    2,  576,    2, 0x02 /* Public */,
      64,    2,  581,    2, 0x02 /* Public */,
      65,    0,  586,    2, 0x02 /* Public */,
      66,    1,  587,    2, 0x02 /* Public */,
      68,    2,  590,    2, 0x02 /* Public */,
      69,    2,  595,    2, 0x02 /* Public */,
      70,    2,  600,    2, 0x02 /* Public */,
      71,    1,  605,    2, 0x02 /* Public */,
      73,    1,  608,    2, 0x02 /* Public */,
      75,    2,  611,    2, 0x02 /* Public */,
      77,    1,  616,    2, 0x02 /* Public */,
      78,    0,  619,    2, 0x02 /* Public */,
      79,    3,  620,    2, 0x02 /* Public */,
      80,    3,  627,    2, 0x02 /* Public */,
      81,    3,  634,    2, 0x02 /* Public */,
      82,    3,  641,    2, 0x02 /* Public */,
      83,    2,  648,    2, 0x02 /* Public */,
      84,    1,  653,    2, 0x02 /* Public */,
      85,    0,  656,    2, 0x02 /* Public */,
      83,    1,  657,    2, 0x02 /* Public */,
      86,    1,  660,    2, 0x02 /* Public */,
      87,    0,  663,    2, 0x02 /* Public */,
      88,    0,  664,    2, 0x02 /* Public */,
      89,    0,  665,    2, 0x02 /* Public */,
      90,    0,  666,    2, 0x02 /* Public */,
      91,    0,  667,    2, 0x02 /* Public */,
      92,    2,  668,    2, 0x02 /* Public */,
      94,    3,  673,    2, 0x02 /* Public */,
      96,    3,  680,    2, 0x02 /* Public */,
      97,    2,  687,    2, 0x02 /* Public */,
      98,    0,  692,    2, 0x02 /* Public */,
      99,    0,  693,    2, 0x02 /* Public */,
     100,    0,  694,    2, 0x02 /* Public */,
     101,    0,  695,    2, 0x02 /* Public */,
     102,    3,  696,    2, 0x02 /* Public */,
     103,    0,  703,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   42,   33,   34,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   47,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   67,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Void, QMetaType::Int,   72,
    QMetaType::Void, QMetaType::Int,   74,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   76,   42,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   35,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   35,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   35,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   35,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   33,   34,
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
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   95,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   95,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   33,   34,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   33,   34,   74,
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
        case 5: _t->moveMap(); break;
        case 6: _t->setFullScreen(); break;
        case 7: _t->setMapDrawing(); break;
        case 8: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 19: _t->setShowAvoidMap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->setShowRobot((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 24: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 25: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 27: _t->clearInitPose(); break;
        case 28: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 29: _t->startDrawingTline(); break;
        case 30: _t->stopDrawingTline(); break;
        case 31: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
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
