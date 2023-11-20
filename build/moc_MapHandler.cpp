/****************************************************************************
** Meta object code from reading C++ file 'MapHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../MapHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MapHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MapHandler_t {
    QByteArrayData data[95];
    char stringdata0[1069];
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
QT_MOC_LITERAL(7, 46, 7), // "moveMap"
QT_MOC_LITERAL(8, 54, 13), // "setFullScreen"
QT_MOC_LITERAL(9, 68, 13), // "setMapDrawing"
QT_MOC_LITERAL(10, 82, 7), // "setName"
QT_MOC_LITERAL(11, 90, 7), // "setTool"
QT_MOC_LITERAL(12, 98, 7), // "getTool"
QT_MOC_LITERAL(13, 106, 7), // "setMode"
QT_MOC_LITERAL(14, 114, 9), // "setEnable"
QT_MOC_LITERAL(15, 124, 2), // "en"
QT_MOC_LITERAL(16, 127, 7), // "getMode"
QT_MOC_LITERAL(17, 135, 12), // "setShowBrush"
QT_MOC_LITERAL(18, 148, 5), // "onoff"
QT_MOC_LITERAL(19, 154, 12), // "setShowLidar"
QT_MOC_LITERAL(20, 167, 15), // "setShowLocation"
QT_MOC_LITERAL(21, 183, 17), // "setRobotFollowing"
QT_MOC_LITERAL(22, 201, 17), // "setShowTravelline"
QT_MOC_LITERAL(23, 219, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(24, 238, 15), // "getshowLocation"
QT_MOC_LITERAL(25, 254, 17), // "getRobotFollowing"
QT_MOC_LITERAL(26, 272, 12), // "getShowLidar"
QT_MOC_LITERAL(27, 285, 11), // "setInitPose"
QT_MOC_LITERAL(28, 297, 1), // "x"
QT_MOC_LITERAL(29, 299, 1), // "y"
QT_MOC_LITERAL(30, 301, 2), // "th"
QT_MOC_LITERAL(31, 304, 13), // "clearInitPose"
QT_MOC_LITERAL(32, 318, 11), // "setInitFlag"
QT_MOC_LITERAL(33, 330, 17), // "startDrawingTline"
QT_MOC_LITERAL(34, 348, 16), // "stopDrawingTline"
QT_MOC_LITERAL(35, 365, 15), // "getDrawingTline"
QT_MOC_LITERAL(36, 381, 11), // "setBoxPoint"
QT_MOC_LITERAL(37, 393, 3), // "num"
QT_MOC_LITERAL(38, 397, 11), // "getPointBox"
QT_MOC_LITERAL(39, 409, 13), // "saveRotateMap"
QT_MOC_LITERAL(40, 423, 10), // "initRotate"
QT_MOC_LITERAL(41, 434, 9), // "rotateMap"
QT_MOC_LITERAL(42, 444, 5), // "angle"
QT_MOC_LITERAL(43, 450, 11), // "rotateMapCW"
QT_MOC_LITERAL(44, 462, 12), // "rotateMapCCW"
QT_MOC_LITERAL(45, 475, 13), // "saveObjectPNG"
QT_MOC_LITERAL(46, 489, 14), // "getDrawingFlag"
QT_MOC_LITERAL(47, 504, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(48, 523, 12), // "startDrawing"
QT_MOC_LITERAL(49, 536, 12), // "addLinePoint"
QT_MOC_LITERAL(50, 549, 10), // "endDrawing"
QT_MOC_LITERAL(51, 560, 16), // "startDrawingRect"
QT_MOC_LITERAL(52, 577, 14), // "setDrawingRect"
QT_MOC_LITERAL(53, 592, 14), // "endDrawingRect"
QT_MOC_LITERAL(54, 607, 12), // "clearDrawing"
QT_MOC_LITERAL(55, 620, 8), // "undoLine"
QT_MOC_LITERAL(56, 629, 8), // "redoLine"
QT_MOC_LITERAL(57, 638, 11), // "startSpline"
QT_MOC_LITERAL(58, 650, 9), // "addSpline"
QT_MOC_LITERAL(59, 660, 10), // "drawSpline"
QT_MOC_LITERAL(60, 671, 9), // "endSpline"
QT_MOC_LITERAL(61, 681, 4), // "save"
QT_MOC_LITERAL(62, 686, 16), // "startDrawingLine"
QT_MOC_LITERAL(63, 703, 14), // "setDrawingLine"
QT_MOC_LITERAL(64, 718, 15), // "stopDrawingLine"
QT_MOC_LITERAL(65, 734, 12), // "setLineColor"
QT_MOC_LITERAL(66, 747, 5), // "color"
QT_MOC_LITERAL(67, 753, 12), // "setLineWidth"
QT_MOC_LITERAL(68, 766, 5), // "width"
QT_MOC_LITERAL(69, 772, 17), // "setSelectLocation"
QT_MOC_LITERAL(70, 790, 13), // "clearLocation"
QT_MOC_LITERAL(71, 804, 11), // "addLocation"
QT_MOC_LITERAL(72, 816, 14), // "addLocationCur"
QT_MOC_LITERAL(73, 831, 11), // "setLocation"
QT_MOC_LITERAL(74, 843, 12), // "editLocation"
QT_MOC_LITERAL(75, 856, 14), // "getLocationNum"
QT_MOC_LITERAL(76, 871, 14), // "removeLocation"
QT_MOC_LITERAL(77, 886, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(78, 905, 14), // "getLocGroupNum"
QT_MOC_LITERAL(79, 920, 7), // "saveMap"
QT_MOC_LITERAL(80, 928, 13), // "saveEditedMap"
QT_MOC_LITERAL(81, 942, 9), // "saveTline"
QT_MOC_LITERAL(82, 952, 13), // "saveTlineTemp"
QT_MOC_LITERAL(83, 966, 10), // "saveVelmap"
QT_MOC_LITERAL(84, 977, 10), // "setMapSize"
QT_MOC_LITERAL(85, 988, 6), // "height"
QT_MOC_LITERAL(86, 995, 6), // "zoomIn"
QT_MOC_LITERAL(87, 1002, 7), // "zoomOut"
QT_MOC_LITERAL(88, 1010, 4), // "move"
QT_MOC_LITERAL(89, 1015, 12), // "getFileWidth"
QT_MOC_LITERAL(90, 1028, 4), // "getX"
QT_MOC_LITERAL(91, 1033, 4), // "getY"
QT_MOC_LITERAL(92, 1038, 8), // "getScale"
QT_MOC_LITERAL(93, 1047, 7), // "setSize"
QT_MOC_LITERAL(94, 1055, 13) // "getCutBoxFlag"

    },
    "MapHandler\0onTimer\0\0loadFile\0name\0"
    "type\0setMap\0moveMap\0setFullScreen\0"
    "setMapDrawing\0setName\0setTool\0getTool\0"
    "setMode\0setEnable\0en\0getMode\0setShowBrush\0"
    "onoff\0setShowLidar\0setShowLocation\0"
    "setRobotFollowing\0setShowTravelline\0"
    "setShowVelocitymap\0getshowLocation\0"
    "getRobotFollowing\0getShowLidar\0"
    "setInitPose\0x\0y\0th\0clearInitPose\0"
    "setInitFlag\0startDrawingTline\0"
    "stopDrawingTline\0getDrawingTline\0"
    "setBoxPoint\0num\0getPointBox\0saveRotateMap\0"
    "initRotate\0rotateMap\0angle\0rotateMapCW\0"
    "rotateMapCCW\0saveObjectPNG\0getDrawingFlag\0"
    "getDrawingUndoFlag\0startDrawing\0"
    "addLinePoint\0endDrawing\0startDrawingRect\0"
    "setDrawingRect\0endDrawingRect\0"
    "clearDrawing\0undoLine\0redoLine\0"
    "startSpline\0addSpline\0drawSpline\0"
    "endSpline\0save\0startDrawingLine\0"
    "setDrawingLine\0stopDrawingLine\0"
    "setLineColor\0color\0setLineWidth\0width\0"
    "setSelectLocation\0clearLocation\0"
    "addLocation\0addLocationCur\0setLocation\0"
    "editLocation\0getLocationNum\0removeLocation\0"
    "setTableNumberAuto\0getLocGroupNum\0"
    "saveMap\0saveEditedMap\0saveTline\0"
    "saveTlineTemp\0saveVelmap\0setMapSize\0"
    "height\0zoomIn\0zoomOut\0move\0getFileWidth\0"
    "getX\0getY\0getScale\0setSize\0getCutBoxFlag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MapHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      81,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  419,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       3,    2,  420,    2, 0x02 /* Public */,
       6,    0,  425,    2, 0x02 /* Public */,
       7,    0,  426,    2, 0x02 /* Public */,
       8,    0,  427,    2, 0x02 /* Public */,
       9,    0,  428,    2, 0x02 /* Public */,
      10,    1,  429,    2, 0x02 /* Public */,
      11,    1,  432,    2, 0x02 /* Public */,
      12,    0,  435,    2, 0x02 /* Public */,
      13,    1,  436,    2, 0x02 /* Public */,
      14,    1,  439,    2, 0x02 /* Public */,
      16,    0,  442,    2, 0x02 /* Public */,
      17,    1,  443,    2, 0x02 /* Public */,
      19,    1,  446,    2, 0x02 /* Public */,
      20,    1,  449,    2, 0x02 /* Public */,
      21,    1,  452,    2, 0x02 /* Public */,
      22,    1,  455,    2, 0x02 /* Public */,
      23,    1,  458,    2, 0x02 /* Public */,
      24,    0,  461,    2, 0x02 /* Public */,
      25,    0,  462,    2, 0x02 /* Public */,
      26,    0,  463,    2, 0x02 /* Public */,
      27,    3,  464,    2, 0x02 /* Public */,
      31,    0,  471,    2, 0x02 /* Public */,
      32,    1,  472,    2, 0x02 /* Public */,
      33,    0,  475,    2, 0x02 /* Public */,
      34,    0,  476,    2, 0x02 /* Public */,
      35,    0,  477,    2, 0x02 /* Public */,
      36,    3,  478,    2, 0x02 /* Public */,
      38,    2,  485,    2, 0x02 /* Public */,
      39,    0,  490,    2, 0x02 /* Public */,
      40,    0,  491,    2, 0x02 /* Public */,
      41,    1,  492,    2, 0x02 /* Public */,
      43,    0,  495,    2, 0x02 /* Public */,
      44,    0,  496,    2, 0x02 /* Public */,
      45,    0,  497,    2, 0x02 /* Public */,
      46,    0,  498,    2, 0x02 /* Public */,
      47,    0,  499,    2, 0x02 /* Public */,
      48,    2,  500,    2, 0x02 /* Public */,
      49,    2,  505,    2, 0x02 /* Public */,
      50,    2,  510,    2, 0x02 /* Public */,
      51,    2,  515,    2, 0x02 /* Public */,
      52,    2,  520,    2, 0x02 /* Public */,
      53,    0,  525,    2, 0x02 /* Public */,
      54,    0,  526,    2, 0x02 /* Public */,
      55,    0,  527,    2, 0x02 /* Public */,
      56,    0,  528,    2, 0x02 /* Public */,
      57,    2,  529,    2, 0x02 /* Public */,
      58,    2,  534,    2, 0x02 /* Public */,
      59,    0,  539,    2, 0x02 /* Public */,
      60,    1,  540,    2, 0x02 /* Public */,
      62,    2,  543,    2, 0x02 /* Public */,
      63,    2,  548,    2, 0x02 /* Public */,
      64,    2,  553,    2, 0x02 /* Public */,
      65,    1,  558,    2, 0x02 /* Public */,
      67,    1,  561,    2, 0x02 /* Public */,
      69,    1,  564,    2, 0x02 /* Public */,
      70,    0,  567,    2, 0x02 /* Public */,
      71,    3,  568,    2, 0x02 /* Public */,
      72,    3,  575,    2, 0x02 /* Public */,
      73,    3,  582,    2, 0x02 /* Public */,
      74,    3,  589,    2, 0x02 /* Public */,
      75,    2,  596,    2, 0x02 /* Public */,
      76,    1,  601,    2, 0x02 /* Public */,
      77,    0,  604,    2, 0x02 /* Public */,
      75,    1,  605,    2, 0x02 /* Public */,
      78,    1,  608,    2, 0x02 /* Public */,
      79,    0,  611,    2, 0x02 /* Public */,
      80,    0,  612,    2, 0x02 /* Public */,
      81,    0,  613,    2, 0x02 /* Public */,
      82,    0,  614,    2, 0x02 /* Public */,
      83,    0,  615,    2, 0x02 /* Public */,
      84,    2,  616,    2, 0x02 /* Public */,
      86,    2,  621,    2, 0x02 /* Public */,
      87,    2,  626,    2, 0x02 /* Public */,
      88,    2,  631,    2, 0x02 /* Public */,
      89,    0,  636,    2, 0x02 /* Public */,
      90,    0,  637,    2, 0x02 /* Public */,
      91,    0,  638,    2, 0x02 /* Public */,
      92,    0,  639,    2, 0x02 /* Public */,
      93,    3,  640,    2, 0x02 /* Public */,
      94,    0,  647,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   28,   29,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   37,   28,   29,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   42,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   61,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int,   66,
    QMetaType::Void, QMetaType::Int,   68,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   28,   29,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   28,   29,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   28,   29,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   28,   29,   30,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,    5,
    QMetaType::Int, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   68,   85,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   28,   29,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   28,   29,   68,
    QMetaType::Bool,

       0        // eod
};

void MapHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MapHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTimer(); break;
        case 1: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->setMap(); break;
        case 3: _t->moveMap(); break;
        case 4: _t->setFullScreen(); break;
        case 5: _t->setMapDrawing(); break;
        case 6: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 17: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 19: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 22: _t->clearInitPose(); break;
        case 23: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->startDrawingTline(); break;
        case 25: _t->stopDrawingTline(); break;
        case 26: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 28: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 29: _t->saveRotateMap(); break;
        case 30: _t->initRotate(); break;
        case 31: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->rotateMapCW(); break;
        case 33: _t->rotateMapCCW(); break;
        case 34: _t->saveObjectPNG(); break;
        case 35: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 36: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 37: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 38: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 39: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 40: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 41: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 42: _t->endDrawingRect(); break;
        case 43: _t->clearDrawing(); break;
        case 44: _t->undoLine(); break;
        case 45: _t->redoLine(); break;
        case 46: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 47: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 48: _t->drawSpline(); break;
        case 49: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 50: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 51: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 52: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 53: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->setSelectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: _t->clearLocation(); break;
        case 57: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 58: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 59: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 60: _t->editLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 61: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 62: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 63: _t->setTableNumberAuto(); break;
        case 64: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 65: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 66: _t->saveMap(); break;
        case 67: _t->saveEditedMap(); break;
        case 68: _t->saveTline(); break;
        case 69: _t->saveTlineTemp(); break;
        case 70: _t->saveVelmap(); break;
        case 71: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 72: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 73: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 74: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 75: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 76: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 77: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 78: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 79: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 80: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MapHandler::staticMetaObject = { {
    &QObject::staticMetaObject,
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
        if (_id < 81)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 81;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 81)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 81;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
