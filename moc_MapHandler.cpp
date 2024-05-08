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
    QByteArrayData data[122];
    char stringdata0[1417];
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
QT_MOC_LITERAL(26, 259, 11), // "setShowNode"
QT_MOC_LITERAL(27, 271, 17), // "setShowTravelline"
QT_MOC_LITERAL(28, 289, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(29, 308, 11), // "setShowName"
QT_MOC_LITERAL(30, 320, 11), // "setShowEdge"
QT_MOC_LITERAL(31, 332, 15), // "getshowLocation"
QT_MOC_LITERAL(32, 348, 17), // "getRobotFollowing"
QT_MOC_LITERAL(33, 366, 12), // "getShowLidar"
QT_MOC_LITERAL(34, 379, 11), // "getShowNode"
QT_MOC_LITERAL(35, 391, 11), // "getShowName"
QT_MOC_LITERAL(36, 403, 11), // "getShowEdge"
QT_MOC_LITERAL(37, 415, 13), // "getShowVelmap"
QT_MOC_LITERAL(38, 429, 12), // "getShowAvoid"
QT_MOC_LITERAL(39, 442, 13), // "getShowObject"
QT_MOC_LITERAL(40, 456, 12), // "getShowTline"
QT_MOC_LITERAL(41, 469, 11), // "setInitPose"
QT_MOC_LITERAL(42, 481, 1), // "x"
QT_MOC_LITERAL(43, 483, 1), // "y"
QT_MOC_LITERAL(44, 485, 2), // "th"
QT_MOC_LITERAL(45, 488, 13), // "clearInitPose"
QT_MOC_LITERAL(46, 502, 11), // "setInitFlag"
QT_MOC_LITERAL(47, 514, 17), // "startDrawingTline"
QT_MOC_LITERAL(48, 532, 16), // "stopDrawingTline"
QT_MOC_LITERAL(49, 549, 15), // "getDrawingTline"
QT_MOC_LITERAL(50, 565, 12), // "setRulerInit"
QT_MOC_LITERAL(51, 578, 11), // "setRulerEnd"
QT_MOC_LITERAL(52, 590, 13), // "setRulerPoint"
QT_MOC_LITERAL(53, 604, 15), // "setStraightInit"
QT_MOC_LITERAL(54, 620, 14), // "setStraightEnd"
QT_MOC_LITERAL(55, 635, 16), // "setStraightPoint"
QT_MOC_LITERAL(56, 652, 11), // "setBoxPoint"
QT_MOC_LITERAL(57, 664, 3), // "num"
QT_MOC_LITERAL(58, 668, 11), // "getPointBox"
QT_MOC_LITERAL(59, 680, 13), // "saveRotateMap"
QT_MOC_LITERAL(60, 694, 10), // "initRotate"
QT_MOC_LITERAL(61, 705, 9), // "rotateMap"
QT_MOC_LITERAL(62, 715, 5), // "angle"
QT_MOC_LITERAL(63, 721, 11), // "rotateMapCW"
QT_MOC_LITERAL(64, 733, 12), // "rotateMapCCW"
QT_MOC_LITERAL(65, 746, 13), // "saveObjectPNG"
QT_MOC_LITERAL(66, 760, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(67, 775, 14), // "getDrawingFlag"
QT_MOC_LITERAL(68, 790, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(69, 809, 12), // "startDrawing"
QT_MOC_LITERAL(70, 822, 12), // "addLinePoint"
QT_MOC_LITERAL(71, 835, 10), // "endDrawing"
QT_MOC_LITERAL(72, 846, 11), // "startErase2"
QT_MOC_LITERAL(73, 858, 9), // "addErase2"
QT_MOC_LITERAL(74, 868, 9), // "endErase2"
QT_MOC_LITERAL(75, 878, 16), // "startDrawingRect"
QT_MOC_LITERAL(76, 895, 14), // "setDrawingRect"
QT_MOC_LITERAL(77, 910, 14), // "endDrawingRect"
QT_MOC_LITERAL(78, 925, 12), // "clearDrawing"
QT_MOC_LITERAL(79, 938, 8), // "undoLine"
QT_MOC_LITERAL(80, 947, 8), // "redoLine"
QT_MOC_LITERAL(81, 956, 11), // "startSpline"
QT_MOC_LITERAL(82, 968, 9), // "addSpline"
QT_MOC_LITERAL(83, 978, 10), // "drawSpline"
QT_MOC_LITERAL(84, 989, 9), // "endSpline"
QT_MOC_LITERAL(85, 999, 4), // "save"
QT_MOC_LITERAL(86, 1004, 16), // "startDrawingLine"
QT_MOC_LITERAL(87, 1021, 14), // "setDrawingLine"
QT_MOC_LITERAL(88, 1036, 15), // "stopDrawingLine"
QT_MOC_LITERAL(89, 1052, 12), // "setLineColor"
QT_MOC_LITERAL(90, 1065, 5), // "color"
QT_MOC_LITERAL(91, 1071, 12), // "setLineWidth"
QT_MOC_LITERAL(92, 1084, 5), // "width"
QT_MOC_LITERAL(93, 1090, 18), // "setTravellineIssue"
QT_MOC_LITERAL(94, 1109, 5), // "count"
QT_MOC_LITERAL(95, 1115, 17), // "setSelectLocation"
QT_MOC_LITERAL(96, 1133, 13), // "clearLocation"
QT_MOC_LITERAL(97, 1147, 11), // "addLocation"
QT_MOC_LITERAL(98, 1159, 14), // "addLocationCur"
QT_MOC_LITERAL(99, 1174, 11), // "setLocation"
QT_MOC_LITERAL(100, 1186, 12), // "editLocation"
QT_MOC_LITERAL(101, 1199, 14), // "getLocationNum"
QT_MOC_LITERAL(102, 1214, 14), // "removeLocation"
QT_MOC_LITERAL(103, 1229, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(104, 1248, 14), // "getLocGroupNum"
QT_MOC_LITERAL(105, 1263, 7), // "saveMap"
QT_MOC_LITERAL(106, 1271, 13), // "saveEditedMap"
QT_MOC_LITERAL(107, 1285, 9), // "saveTline"
QT_MOC_LITERAL(108, 1295, 13), // "saveTlineTemp"
QT_MOC_LITERAL(109, 1309, 10), // "saveVelmap"
QT_MOC_LITERAL(110, 1320, 10), // "setMapSize"
QT_MOC_LITERAL(111, 1331, 6), // "height"
QT_MOC_LITERAL(112, 1338, 6), // "zoomIn"
QT_MOC_LITERAL(113, 1345, 4), // "dist"
QT_MOC_LITERAL(114, 1350, 7), // "zoomOut"
QT_MOC_LITERAL(115, 1358, 4), // "move"
QT_MOC_LITERAL(116, 1363, 12), // "getFileWidth"
QT_MOC_LITERAL(117, 1376, 4), // "getX"
QT_MOC_LITERAL(118, 1381, 4), // "getY"
QT_MOC_LITERAL(119, 1386, 8), // "getScale"
QT_MOC_LITERAL(120, 1395, 7), // "setSize"
QT_MOC_LITERAL(121, 1403, 13) // "getCutBoxFlag"

    },
    "MapHandler\0onTimer\0\0loadFile\0name\0"
    "type\0setMap\0setMapTest\0setMapLayer\0"
    "setFullScreen\0setMapDrawing\0setName\0"
    "setTool\0getTool\0setMode\0setEnable\0en\0"
    "getMode\0setShowBrush\0onoff\0setShowLidar\0"
    "setShowLocation\0setRobotFollowing\0"
    "setShowObject\0setShowAvoidMap\0"
    "setShowRobot\0setShowNode\0setShowTravelline\0"
    "setShowVelocitymap\0setShowName\0"
    "setShowEdge\0getshowLocation\0"
    "getRobotFollowing\0getShowLidar\0"
    "getShowNode\0getShowName\0getShowEdge\0"
    "getShowVelmap\0getShowAvoid\0getShowObject\0"
    "getShowTline\0setInitPose\0x\0y\0th\0"
    "clearInitPose\0setInitFlag\0startDrawingTline\0"
    "stopDrawingTline\0getDrawingTline\0"
    "setRulerInit\0setRulerEnd\0setRulerPoint\0"
    "setStraightInit\0setStraightEnd\0"
    "setStraightPoint\0setBoxPoint\0num\0"
    "getPointBox\0saveRotateMap\0initRotate\0"
    "rotateMap\0angle\0rotateMapCW\0rotateMapCCW\0"
    "saveObjectPNG\0saveObsAreaPNG\0"
    "getDrawingFlag\0getDrawingUndoFlag\0"
    "startDrawing\0addLinePoint\0endDrawing\0"
    "startErase2\0addErase2\0endErase2\0"
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
     106,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  544,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       3,    2,  545,    2, 0x02 /* Public */,
       6,    0,  550,    2, 0x02 /* Public */,
       7,    0,  551,    2, 0x02 /* Public */,
       8,    0,  552,    2, 0x02 /* Public */,
       9,    0,  553,    2, 0x02 /* Public */,
      10,    0,  554,    2, 0x02 /* Public */,
      11,    1,  555,    2, 0x02 /* Public */,
      12,    1,  558,    2, 0x02 /* Public */,
      13,    0,  561,    2, 0x02 /* Public */,
      14,    1,  562,    2, 0x02 /* Public */,
      15,    1,  565,    2, 0x02 /* Public */,
      17,    0,  568,    2, 0x02 /* Public */,
      18,    1,  569,    2, 0x02 /* Public */,
      20,    1,  572,    2, 0x02 /* Public */,
      21,    1,  575,    2, 0x02 /* Public */,
      22,    1,  578,    2, 0x02 /* Public */,
      23,    1,  581,    2, 0x02 /* Public */,
      24,    1,  584,    2, 0x02 /* Public */,
      25,    1,  587,    2, 0x02 /* Public */,
      26,    1,  590,    2, 0x02 /* Public */,
      27,    1,  593,    2, 0x02 /* Public */,
      28,    1,  596,    2, 0x02 /* Public */,
      29,    1,  599,    2, 0x02 /* Public */,
      30,    1,  602,    2, 0x02 /* Public */,
      31,    0,  605,    2, 0x02 /* Public */,
      32,    0,  606,    2, 0x02 /* Public */,
      33,    0,  607,    2, 0x02 /* Public */,
      34,    0,  608,    2, 0x02 /* Public */,
      35,    0,  609,    2, 0x02 /* Public */,
      36,    0,  610,    2, 0x02 /* Public */,
      37,    0,  611,    2, 0x02 /* Public */,
      38,    0,  612,    2, 0x02 /* Public */,
      39,    0,  613,    2, 0x02 /* Public */,
      40,    0,  614,    2, 0x02 /* Public */,
      41,    3,  615,    2, 0x02 /* Public */,
      45,    0,  622,    2, 0x02 /* Public */,
      46,    1,  623,    2, 0x02 /* Public */,
      47,    0,  626,    2, 0x02 /* Public */,
      48,    0,  627,    2, 0x02 /* Public */,
      49,    0,  628,    2, 0x02 /* Public */,
      50,    2,  629,    2, 0x02 /* Public */,
      51,    2,  634,    2, 0x02 /* Public */,
      52,    2,  639,    2, 0x02 /* Public */,
      53,    2,  644,    2, 0x02 /* Public */,
      54,    2,  649,    2, 0x02 /* Public */,
      55,    2,  654,    2, 0x02 /* Public */,
      56,    3,  659,    2, 0x02 /* Public */,
      58,    2,  666,    2, 0x02 /* Public */,
      59,    0,  671,    2, 0x02 /* Public */,
      60,    0,  672,    2, 0x02 /* Public */,
      61,    1,  673,    2, 0x02 /* Public */,
      63,    0,  676,    2, 0x02 /* Public */,
      64,    0,  677,    2, 0x02 /* Public */,
      65,    0,  678,    2, 0x02 /* Public */,
      66,    0,  679,    2, 0x02 /* Public */,
      67,    0,  680,    2, 0x02 /* Public */,
      68,    0,  681,    2, 0x02 /* Public */,
      69,    2,  682,    2, 0x02 /* Public */,
      70,    2,  687,    2, 0x02 /* Public */,
      71,    2,  692,    2, 0x02 /* Public */,
      72,    2,  697,    2, 0x02 /* Public */,
      73,    2,  702,    2, 0x02 /* Public */,
      74,    2,  707,    2, 0x02 /* Public */,
      75,    2,  712,    2, 0x02 /* Public */,
      76,    2,  717,    2, 0x02 /* Public */,
      77,    0,  722,    2, 0x02 /* Public */,
      78,    0,  723,    2, 0x02 /* Public */,
      79,    0,  724,    2, 0x02 /* Public */,
      80,    0,  725,    2, 0x02 /* Public */,
      81,    2,  726,    2, 0x02 /* Public */,
      82,    2,  731,    2, 0x02 /* Public */,
      83,    0,  736,    2, 0x02 /* Public */,
      84,    1,  737,    2, 0x02 /* Public */,
      86,    2,  740,    2, 0x02 /* Public */,
      87,    2,  745,    2, 0x02 /* Public */,
      88,    2,  750,    2, 0x02 /* Public */,
      89,    1,  755,    2, 0x02 /* Public */,
      91,    1,  758,    2, 0x02 /* Public */,
      93,    2,  761,    2, 0x02 /* Public */,
      95,    1,  766,    2, 0x02 /* Public */,
      96,    0,  769,    2, 0x02 /* Public */,
      97,    3,  770,    2, 0x02 /* Public */,
      98,    3,  777,    2, 0x02 /* Public */,
      99,    3,  784,    2, 0x02 /* Public */,
     100,    3,  791,    2, 0x02 /* Public */,
     101,    2,  798,    2, 0x02 /* Public */,
     102,    1,  803,    2, 0x02 /* Public */,
     103,    0,  806,    2, 0x02 /* Public */,
     101,    1,  807,    2, 0x02 /* Public */,
     104,    1,  810,    2, 0x02 /* Public */,
     105,    0,  813,    2, 0x02 /* Public */,
     106,    0,  814,    2, 0x02 /* Public */,
     107,    0,  815,    2, 0x02 /* Public */,
     108,    0,  816,    2, 0x02 /* Public */,
     109,    0,  817,    2, 0x02 /* Public */,
     110,    2,  818,    2, 0x02 /* Public */,
     112,    3,  823,    2, 0x02 /* Public */,
     114,    3,  830,    2, 0x02 /* Public */,
     115,    2,  837,    2, 0x02 /* Public */,
     116,    0,  842,    2, 0x02 /* Public */,
     117,    0,  843,    2, 0x02 /* Public */,
     118,    0,  844,    2, 0x02 /* Public */,
     119,    0,  845,    2, 0x02 /* Public */,
     120,    3,  846,    2, 0x02 /* Public */,
     121,    0,  853,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,   44,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   57,   42,   43,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   62,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   85,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int,   90,
    QMetaType::Void, QMetaType::Int,   92,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   94,   57,
    QMetaType::Void, QMetaType::Int,   57,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,   44,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,   44,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Void, QMetaType::Int,   57,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,    5,
    QMetaType::Int, QMetaType::Int,   57,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   92,  111,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,  113,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,  113,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   42,   43,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   42,   43,   92,
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
        case 20: _t->setShowNode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 23: _t->setShowName((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 24: _t->setShowEdge((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 25: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 28: { bool _r = _t->getShowNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->getShowName();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { bool _r = _t->getShowEdge();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 31: { bool _r = _t->getShowVelmap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 32: { bool _r = _t->getShowAvoid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: { bool _r = _t->getShowObject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 34: { bool _r = _t->getShowTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 35: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 36: _t->clearInitPose(); break;
        case 37: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 38: _t->startDrawingTline(); break;
        case 39: _t->stopDrawingTline(); break;
        case 40: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 41: _t->setRulerInit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 42: _t->setRulerEnd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 43: _t->setRulerPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 44: _t->setStraightInit((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 45: _t->setStraightEnd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 46: _t->setStraightPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 47: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 48: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 49: _t->saveRotateMap(); break;
        case 50: _t->initRotate(); break;
        case 51: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 52: _t->rotateMapCW(); break;
        case 53: _t->rotateMapCCW(); break;
        case 54: _t->saveObjectPNG(); break;
        case 55: _t->saveObsAreaPNG(); break;
        case 56: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 57: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 58: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 59: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 60: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 61: _t->startErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 62: _t->addErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 63: _t->endErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 64: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 65: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 66: _t->endDrawingRect(); break;
        case 67: _t->clearDrawing(); break;
        case 68: _t->undoLine(); break;
        case 69: _t->redoLine(); break;
        case 70: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 71: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 72: _t->drawSpline(); break;
        case 73: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 74: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 75: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 76: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 77: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 78: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 79: _t->setTravellineIssue((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 80: _t->setSelectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 81: _t->clearLocation(); break;
        case 82: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 83: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 84: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 85: _t->editLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 86: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 87: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 88: _t->setTableNumberAuto(); break;
        case 89: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 90: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 91: _t->saveMap(); break;
        case 92: _t->saveEditedMap(); break;
        case 93: _t->saveTline(); break;
        case 94: _t->saveTlineTemp(); break;
        case 95: _t->saveVelmap(); break;
        case 96: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 97: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 98: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 99: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 100: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 101: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 102: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 103: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 104: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 105: { bool _r = _t->getCutBoxFlag();
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
        if (_id < 106)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 106;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 106)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 106;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
