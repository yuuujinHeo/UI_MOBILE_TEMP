/****************************************************************************
** Meta object code from reading C++ file 'Supervisor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Supervisor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Supervisor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Supervisor_t {
    QByteArrayData data[486];
    char stringdata0[6140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Supervisor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Supervisor_t qt_meta_stringdata_Supervisor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Supervisor"
QT_MOC_LITERAL(1, 11, 7), // "onTimer"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "path_changed"
QT_MOC_LITERAL(4, 33, 13), // "camera_update"
QT_MOC_LITERAL(5, 47, 14), // "mapping_update"
QT_MOC_LITERAL(6, 62, 10), // "usb_detect"
QT_MOC_LITERAL(7, 73, 15), // "git_pull_failed"
QT_MOC_LITERAL(8, 89, 16), // "git_pull_success"
QT_MOC_LITERAL(9, 106, 8), // "new_call"
QT_MOC_LITERAL(10, 115, 14), // "process_accept"
QT_MOC_LITERAL(11, 130, 3), // "cmd"
QT_MOC_LITERAL(12, 134, 12), // "process_done"
QT_MOC_LITERAL(13, 147, 13), // "process_error"
QT_MOC_LITERAL(14, 161, 5), // "param"
QT_MOC_LITERAL(15, 167, 15), // "process_timeout"
QT_MOC_LITERAL(16, 183, 14), // "update_success"
QT_MOC_LITERAL(17, 198, 11), // "update_fail"
QT_MOC_LITERAL(18, 210, 9), // "clear_all"
QT_MOC_LITERAL(19, 220, 13), // "loadMapServer"
QT_MOC_LITERAL(20, 234, 13), // "sendMapServer"
QT_MOC_LITERAL(21, 248, 17), // "checkLocationName"
QT_MOC_LITERAL(22, 266, 5), // "group"
QT_MOC_LITERAL(23, 272, 4), // "name"
QT_MOC_LITERAL(24, 277, 10), // "resetClear"
QT_MOC_LITERAL(25, 288, 10), // "getWifiNum"
QT_MOC_LITERAL(26, 299, 17), // "getWifiConnection"
QT_MOC_LITERAL(27, 317, 4), // "ssid"
QT_MOC_LITERAL(28, 322, 14), // "getCurWifiSSID"
QT_MOC_LITERAL(29, 337, 11), // "getWifiSSID"
QT_MOC_LITERAL(30, 349, 3), // "num"
QT_MOC_LITERAL(31, 353, 11), // "connectWifi"
QT_MOC_LITERAL(32, 365, 6), // "passwd"
QT_MOC_LITERAL(33, 372, 15), // "getWifiSecurity"
QT_MOC_LITERAL(34, 388, 12), // "getWifiLevel"
QT_MOC_LITERAL(35, 401, 11), // "getWifiRate"
QT_MOC_LITERAL(36, 413, 12), // "getWifiInuse"
QT_MOC_LITERAL(37, 426, 14), // "getAllWifiList"
QT_MOC_LITERAL(38, 441, 9), // "getWifiIP"
QT_MOC_LITERAL(39, 451, 7), // "setWifi"
QT_MOC_LITERAL(40, 459, 2), // "ip"
QT_MOC_LITERAL(41, 462, 7), // "gateway"
QT_MOC_LITERAL(42, 470, 3), // "dns"
QT_MOC_LITERAL(43, 474, 8), // "getcurIP"
QT_MOC_LITERAL(44, 483, 13), // "getcurGateway"
QT_MOC_LITERAL(45, 497, 9), // "getcurDNS"
QT_MOC_LITERAL(46, 507, 13), // "readWifiState"
QT_MOC_LITERAL(47, 521, 10), // "setWifiSSD"
QT_MOC_LITERAL(48, 532, 15), // "getSystemVolume"
QT_MOC_LITERAL(49, 548, 13), // "checkMoveFail"
QT_MOC_LITERAL(50, 562, 8), // "passInit"
QT_MOC_LITERAL(51, 571, 8), // "loadFile"
QT_MOC_LITERAL(52, 580, 4), // "type"
QT_MOC_LITERAL(53, 585, 6), // "setMap"
QT_MOC_LITERAL(54, 592, 7), // "moveMap"
QT_MOC_LITERAL(55, 600, 13), // "setFullScreen"
QT_MOC_LITERAL(56, 614, 13), // "setMapDrawing"
QT_MOC_LITERAL(57, 628, 10), // "clicksound"
QT_MOC_LITERAL(58, 639, 4), // "mode"
QT_MOC_LITERAL(59, 644, 6), // "volume"
QT_MOC_LITERAL(60, 651, 7), // "playBGM"
QT_MOC_LITERAL(61, 659, 7), // "stopBGM"
QT_MOC_LITERAL(62, 667, 9), // "isplayBGM"
QT_MOC_LITERAL(63, 677, 9), // "playVoice"
QT_MOC_LITERAL(64, 687, 5), // "voice"
QT_MOC_LITERAL(65, 693, 19), // "confirmLocalization"
QT_MOC_LITERAL(66, 713, 7), // "setName"
QT_MOC_LITERAL(67, 721, 7), // "setTool"
QT_MOC_LITERAL(68, 729, 7), // "getTool"
QT_MOC_LITERAL(69, 737, 7), // "setMode"
QT_MOC_LITERAL(70, 745, 9), // "setEnable"
QT_MOC_LITERAL(71, 755, 2), // "en"
QT_MOC_LITERAL(72, 758, 7), // "getMode"
QT_MOC_LITERAL(73, 766, 12), // "setShowBrush"
QT_MOC_LITERAL(74, 779, 5), // "onoff"
QT_MOC_LITERAL(75, 785, 12), // "setShowLidar"
QT_MOC_LITERAL(76, 798, 15), // "setShowLocation"
QT_MOC_LITERAL(77, 814, 17), // "setRobotFollowing"
QT_MOC_LITERAL(78, 832, 17), // "setShowTravelline"
QT_MOC_LITERAL(79, 850, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(80, 869, 13), // "setShowObject"
QT_MOC_LITERAL(81, 883, 11), // "setInitFlag"
QT_MOC_LITERAL(82, 895, 15), // "getshowLocation"
QT_MOC_LITERAL(83, 911, 17), // "getRobotFollowing"
QT_MOC_LITERAL(84, 929, 12), // "getShowLidar"
QT_MOC_LITERAL(85, 942, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(86, 958, 11), // "setInitPose"
QT_MOC_LITERAL(87, 970, 1), // "x"
QT_MOC_LITERAL(88, 972, 1), // "y"
QT_MOC_LITERAL(89, 974, 2), // "th"
QT_MOC_LITERAL(90, 977, 13), // "clearInitPose"
QT_MOC_LITERAL(91, 991, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(92, 1012, 17), // "startDrawingTline"
QT_MOC_LITERAL(93, 1030, 16), // "stopDrawingTline"
QT_MOC_LITERAL(94, 1047, 15), // "getDrawingTline"
QT_MOC_LITERAL(95, 1063, 11), // "setBoxPoint"
QT_MOC_LITERAL(96, 1075, 11), // "getPointBox"
QT_MOC_LITERAL(97, 1087, 13), // "saveRotateMap"
QT_MOC_LITERAL(98, 1101, 10), // "initRotate"
QT_MOC_LITERAL(99, 1112, 9), // "rotateMap"
QT_MOC_LITERAL(100, 1122, 5), // "angle"
QT_MOC_LITERAL(101, 1128, 11), // "rotateMapCW"
QT_MOC_LITERAL(102, 1140, 12), // "rotateMapCCW"
QT_MOC_LITERAL(103, 1153, 13), // "saveObjectPNG"
QT_MOC_LITERAL(104, 1167, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(105, 1182, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(106, 1205, 14), // "getDrawingFlag"
QT_MOC_LITERAL(107, 1220, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(108, 1239, 12), // "startDrawing"
QT_MOC_LITERAL(109, 1252, 12), // "addLinePoint"
QT_MOC_LITERAL(110, 1265, 10), // "endDrawing"
QT_MOC_LITERAL(111, 1276, 10), // "setMapOrin"
QT_MOC_LITERAL(112, 1287, 16), // "startDrawingRect"
QT_MOC_LITERAL(113, 1304, 14), // "setDrawingRect"
QT_MOC_LITERAL(114, 1319, 14), // "endDrawingRect"
QT_MOC_LITERAL(115, 1334, 12), // "clearDrawing"
QT_MOC_LITERAL(116, 1347, 8), // "undoLine"
QT_MOC_LITERAL(117, 1356, 8), // "redoLine"
QT_MOC_LITERAL(118, 1365, 11), // "startSpline"
QT_MOC_LITERAL(119, 1377, 9), // "addSpline"
QT_MOC_LITERAL(120, 1387, 10), // "drawSpline"
QT_MOC_LITERAL(121, 1398, 9), // "endSpline"
QT_MOC_LITERAL(122, 1408, 4), // "save"
QT_MOC_LITERAL(123, 1413, 16), // "startDrawingLine"
QT_MOC_LITERAL(124, 1430, 14), // "setDrawingLine"
QT_MOC_LITERAL(125, 1445, 15), // "stopDrawingLine"
QT_MOC_LITERAL(126, 1461, 12), // "setLineColor"
QT_MOC_LITERAL(127, 1474, 5), // "color"
QT_MOC_LITERAL(128, 1480, 12), // "setLineWidth"
QT_MOC_LITERAL(129, 1493, 5), // "width"
QT_MOC_LITERAL(130, 1499, 14), // "getLocationNum"
QT_MOC_LITERAL(131, 1514, 12), // "saveLocation"
QT_MOC_LITERAL(132, 1527, 8), // "groupnum"
QT_MOC_LITERAL(133, 1536, 13), // "clearLocation"
QT_MOC_LITERAL(134, 1550, 11), // "addLocation"
QT_MOC_LITERAL(135, 1562, 14), // "addLocationCur"
QT_MOC_LITERAL(136, 1577, 11), // "setLocation"
QT_MOC_LITERAL(137, 1589, 12), // "editLocation"
QT_MOC_LITERAL(138, 1602, 14), // "removeLocation"
QT_MOC_LITERAL(139, 1617, 20), // "getLocationAvailable"
QT_MOC_LITERAL(140, 1638, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(141, 1657, 14), // "getLocGroupNum"
QT_MOC_LITERAL(142, 1672, 7), // "saveMap"
QT_MOC_LITERAL(143, 1680, 13), // "saveEditedMap"
QT_MOC_LITERAL(144, 1694, 9), // "saveTline"
QT_MOC_LITERAL(145, 1704, 13), // "saveTlineTemp"
QT_MOC_LITERAL(146, 1718, 10), // "saveVelmap"
QT_MOC_LITERAL(147, 1729, 10), // "setMapSize"
QT_MOC_LITERAL(148, 1740, 6), // "height"
QT_MOC_LITERAL(149, 1747, 6), // "zoomIn"
QT_MOC_LITERAL(150, 1754, 4), // "dist"
QT_MOC_LITERAL(151, 1759, 7), // "zoomOut"
QT_MOC_LITERAL(152, 1767, 4), // "move"
QT_MOC_LITERAL(153, 1772, 12), // "getFileWidth"
QT_MOC_LITERAL(154, 1785, 4), // "getX"
QT_MOC_LITERAL(155, 1790, 4), // "getY"
QT_MOC_LITERAL(156, 1795, 8), // "getScale"
QT_MOC_LITERAL(157, 1804, 13), // "setVelmapView"
QT_MOC_LITERAL(158, 1818, 12), // "setTlineView"
QT_MOC_LITERAL(159, 1831, 13), // "setObjectView"
QT_MOC_LITERAL(160, 1845, 15), // "setAvoidmapView"
QT_MOC_LITERAL(161, 1861, 15), // "setLocationView"
QT_MOC_LITERAL(162, 1877, 12), // "setRobotView"
QT_MOC_LITERAL(163, 1890, 15), // "setSystemVolume"
QT_MOC_LITERAL(164, 1906, 19), // "requestSystemVolume"
QT_MOC_LITERAL(165, 1926, 7), // "setSize"
QT_MOC_LITERAL(166, 1934, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(167, 1948, 14), // "selectLocation"
QT_MOC_LITERAL(168, 1963, 8), // "writelog"
QT_MOC_LITERAL(169, 1972, 3), // "msg"
QT_MOC_LITERAL(170, 1976, 18), // "startDrawingObject"
QT_MOC_LITERAL(171, 1995, 17), // "stopDrawingObject"
QT_MOC_LITERAL(172, 2013, 17), // "saveDrawingObject"
QT_MOC_LITERAL(173, 2031, 13), // "setLocationUp"
QT_MOC_LITERAL(174, 2045, 15), // "setLocationDown"
QT_MOC_LITERAL(175, 2061, 8), // "checkINI"
QT_MOC_LITERAL(176, 2070, 8), // "killSLAM"
QT_MOC_LITERAL(177, 2079, 12), // "makeRobotINI"
QT_MOC_LITERAL(178, 2092, 13), // "checkRobotINI"
QT_MOC_LITERAL(179, 2106, 11), // "restartSLAM"
QT_MOC_LITERAL(180, 2118, 9), // "startSLAM"
QT_MOC_LITERAL(181, 2128, 16), // "getIPCConnection"
QT_MOC_LITERAL(182, 2145, 8), // "getIPCRX"
QT_MOC_LITERAL(183, 2154, 8), // "getIPCTX"
QT_MOC_LITERAL(184, 2163, 14), // "programRestart"
QT_MOC_LITERAL(185, 2178, 11), // "programExit"
QT_MOC_LITERAL(186, 2190, 13), // "getRawMapPath"
QT_MOC_LITERAL(187, 2204, 10), // "getMapPath"
QT_MOC_LITERAL(188, 2215, 12), // "getAnnotPath"
QT_MOC_LITERAL(189, 2228, 11), // "getMetaPath"
QT_MOC_LITERAL(190, 2240, 13), // "getTravelPath"
QT_MOC_LITERAL(191, 2254, 11), // "getCostPath"
QT_MOC_LITERAL(192, 2266, 10), // "getIniPath"
QT_MOC_LITERAL(193, 2277, 4), // "file"
QT_MOC_LITERAL(194, 2282, 10), // "setSetting"
QT_MOC_LITERAL(195, 2293, 5), // "value"
QT_MOC_LITERAL(196, 2299, 11), // "readSetting"
QT_MOC_LITERAL(197, 2311, 8), // "map_name"
QT_MOC_LITERAL(198, 2320, 10), // "getSetting"
QT_MOC_LITERAL(199, 2331, 10), // "getTrayNum"
QT_MOC_LITERAL(200, 2342, 14), // "setTableColNum"
QT_MOC_LITERAL(201, 2357, 7), // "col_num"
QT_MOC_LITERAL(202, 2365, 12), // "getRobotType"
QT_MOC_LITERAL(203, 2378, 13), // "requestCamera"
QT_MOC_LITERAL(204, 2392, 13), // "getLeftCamera"
QT_MOC_LITERAL(205, 2406, 14), // "getRightCamera"
QT_MOC_LITERAL(206, 2421, 9), // "setCamera"
QT_MOC_LITERAL(207, 2431, 4), // "left"
QT_MOC_LITERAL(208, 2436, 5), // "right"
QT_MOC_LITERAL(209, 2442, 12), // "getCameraNum"
QT_MOC_LITERAL(210, 2455, 15), // "getCameraSerial"
QT_MOC_LITERAL(211, 2471, 13), // "setCursorView"
QT_MOC_LITERAL(212, 2485, 7), // "visible"
QT_MOC_LITERAL(213, 2493, 8), // "getVoice"
QT_MOC_LITERAL(214, 2502, 15), // "checkTravelline"
QT_MOC_LITERAL(215, 2518, 13), // "updateProgram"
QT_MOC_LITERAL(216, 2532, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(217, 2553, 17), // "checkVersionAgain"
QT_MOC_LITERAL(218, 2571, 12), // "isNewVersion"
QT_MOC_LITERAL(219, 2584, 12), // "isNeedUpdate"
QT_MOC_LITERAL(220, 2597, 15), // "getLocalVersion"
QT_MOC_LITERAL(221, 2613, 16), // "getServerVersion"
QT_MOC_LITERAL(222, 2630, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(223, 2650, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(224, 2673, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(225, 2697, 13), // "getUpdateDate"
QT_MOC_LITERAL(226, 2711, 13), // "getUpdateSize"
QT_MOC_LITERAL(227, 2725, 17), // "getUpdateFileName"
QT_MOC_LITERAL(228, 2743, 15), // "getUpdateCommit"
QT_MOC_LITERAL(229, 2759, 16), // "getCurrentCommit"
QT_MOC_LITERAL(230, 2776, 16), // "getUpdateMessage"
QT_MOC_LITERAL(231, 2793, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(232, 2811, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(233, 2833, 11), // "checkUpdate"
QT_MOC_LITERAL(234, 2845, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(235, 2867, 11), // "setLangauge"
QT_MOC_LITERAL(236, 2879, 3), // "lan"
QT_MOC_LITERAL(237, 2883, 13), // "isCallingMode"
QT_MOC_LITERAL(238, 2897, 9), // "goServing"
QT_MOC_LITERAL(239, 2907, 5), // "table"
QT_MOC_LITERAL(240, 2913, 17), // "getLocationbyCall"
QT_MOC_LITERAL(241, 2931, 8), // "LOCATION"
QT_MOC_LITERAL(242, 2940, 4), // "call"
QT_MOC_LITERAL(243, 2945, 11), // "getLocation"
QT_MOC_LITERAL(244, 2957, 15), // "getLocationbyID"
QT_MOC_LITERAL(245, 2973, 2), // "id"
QT_MOC_LITERAL(246, 2976, 10), // "setUiState"
QT_MOC_LITERAL(247, 2987, 5), // "state"
QT_MOC_LITERAL(248, 2993, 17), // "resetLocalization"
QT_MOC_LITERAL(249, 3011, 6), // "setLog"
QT_MOC_LITERAL(250, 3018, 13), // "getLogLineNum"
QT_MOC_LITERAL(251, 3032, 10), // "getLogLine"
QT_MOC_LITERAL(252, 3043, 10), // "getLogDate"
QT_MOC_LITERAL(253, 3054, 10), // "getLogAuth"
QT_MOC_LITERAL(254, 3065, 13), // "getLogMessage"
QT_MOC_LITERAL(255, 3079, 7), // "readLog"
QT_MOC_LITERAL(256, 3087, 4), // "date"
QT_MOC_LITERAL(257, 3092, 13), // "getLocaleDate"
QT_MOC_LITERAL(258, 3106, 4), // "year"
QT_MOC_LITERAL(259, 3111, 5), // "month"
QT_MOC_LITERAL(260, 3117, 9), // "updateUSB"
QT_MOC_LITERAL(261, 3127, 10), // "getusbsize"
QT_MOC_LITERAL(262, 3138, 17), // "readusbrecentfile"
QT_MOC_LITERAL(263, 3156, 14), // "getusbfilesize"
QT_MOC_LITERAL(264, 3171, 10), // "getusbfile"
QT_MOC_LITERAL(265, 3182, 16), // "getusbrecentfile"
QT_MOC_LITERAL(266, 3199, 10), // "getusbname"
QT_MOC_LITERAL(267, 3210, 7), // "readusb"
QT_MOC_LITERAL(268, 3218, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(269, 3233, 4), // "path"
QT_MOC_LITERAL(270, 3238, 15), // "isConnectServer"
QT_MOC_LITERAL(271, 3254, 9), // "isLoadMap"
QT_MOC_LITERAL(272, 3264, 10), // "isExistMap"
QT_MOC_LITERAL(273, 3275, 13), // "isExistRawMap"
QT_MOC_LITERAL(274, 3289, 15), // "isExistTlineMap"
QT_MOC_LITERAL(275, 3305, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(276, 3321, 13), // "isExistVelMap"
QT_MOC_LITERAL(277, 3335, 16), // "isExistObjectMap"
QT_MOC_LITERAL(278, 3352, 16), // "isExistTravelMap"
QT_MOC_LITERAL(279, 3369, 17), // "isExistAnnotation"
QT_MOC_LITERAL(280, 3387, 15), // "isExistRobotINI"
QT_MOC_LITERAL(281, 3403, 15), // "getAvailableMap"
QT_MOC_LITERAL(282, 3419, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(283, 3439, 14), // "getMapFileSize"
QT_MOC_LITERAL(284, 3454, 10), // "getMapFile"
QT_MOC_LITERAL(285, 3465, 15), // "deleteEditedMap"
QT_MOC_LITERAL(286, 3481, 16), // "deleteAnnotation"
QT_MOC_LITERAL(287, 3498, 9), // "removeMap"
QT_MOC_LITERAL(288, 3508, 8), // "filename"
QT_MOC_LITERAL(289, 3517, 7), // "loadMap"
QT_MOC_LITERAL(290, 3525, 7), // "copyMap"
QT_MOC_LITERAL(291, 3533, 8), // "orinname"
QT_MOC_LITERAL(292, 3542, 7), // "newname"
QT_MOC_LITERAL(293, 3550, 10), // "rotate_map"
QT_MOC_LITERAL(294, 3561, 4), // "_src"
QT_MOC_LITERAL(295, 3566, 4), // "_dst"
QT_MOC_LITERAL(296, 3571, 12), // "startMapping"
QT_MOC_LITERAL(297, 3584, 7), // "mapsize"
QT_MOC_LITERAL(298, 3592, 4), // "grid"
QT_MOC_LITERAL(299, 3597, 11), // "stopMapping"
QT_MOC_LITERAL(300, 3609, 11), // "setSLAMMode"
QT_MOC_LITERAL(301, 3621, 11), // "saveMapping"
QT_MOC_LITERAL(302, 3633, 13), // "setInitCurPos"
QT_MOC_LITERAL(303, 3647, 10), // "setInitPos"
QT_MOC_LITERAL(304, 3658, 12), // "getInitPoseX"
QT_MOC_LITERAL(305, 3671, 12), // "getInitPoseY"
QT_MOC_LITERAL(306, 3684, 13), // "getInitPoseTH"
QT_MOC_LITERAL(307, 3698, 12), // "slam_setInit"
QT_MOC_LITERAL(308, 3711, 8), // "slam_run"
QT_MOC_LITERAL(309, 3720, 9), // "slam_stop"
QT_MOC_LITERAL(310, 3730, 13), // "slam_autoInit"
QT_MOC_LITERAL(311, 3744, 15), // "is_slam_running"
QT_MOC_LITERAL(312, 3760, 14), // "getMappingflag"
QT_MOC_LITERAL(313, 3775, 16), // "getObjectingflag"
QT_MOC_LITERAL(314, 3792, 16), // "setObjectingflag"
QT_MOC_LITERAL(315, 3809, 4), // "flag"
QT_MOC_LITERAL(316, 3814, 13), // "getnewMapname"
QT_MOC_LITERAL(317, 3828, 11), // "getLastCall"
QT_MOC_LITERAL(318, 3840, 11), // "getCallSize"
QT_MOC_LITERAL(319, 3852, 16), // "getCallQueueSize"
QT_MOC_LITERAL(320, 3869, 9), // "cleanTray"
QT_MOC_LITERAL(321, 3879, 11), // "getCallName"
QT_MOC_LITERAL(322, 3891, 14), // "clearCallQueue"
QT_MOC_LITERAL(323, 3906, 7), // "getCall"
QT_MOC_LITERAL(324, 3914, 15), // "getCallLocation"
QT_MOC_LITERAL(325, 3930, 11), // "setCallbell"
QT_MOC_LITERAL(326, 3942, 16), // "setCallbellForce"
QT_MOC_LITERAL(327, 3959, 10), // "acceptCall"
QT_MOC_LITERAL(328, 3970, 3), // "yes"
QT_MOC_LITERAL(329, 3974, 10), // "setObjPose"
QT_MOC_LITERAL(330, 3985, 14), // "getServingName"
QT_MOC_LITERAL(331, 4000, 15), // "getLocationName"
QT_MOC_LITERAL(332, 4016, 15), // "getLocationType"
QT_MOC_LITERAL(333, 4032, 17), // "getLocationNumber"
QT_MOC_LITERAL(334, 4050, 17), // "setLocationNumber"
QT_MOC_LITERAL(335, 4068, 15), // "getLocationSize"
QT_MOC_LITERAL(336, 4084, 16), // "getLocationGroup"
QT_MOC_LITERAL(337, 4101, 13), // "getLocationID"
QT_MOC_LITERAL(338, 4115, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(339, 4135, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(340, 4156, 17), // "getLocationCallID"
QT_MOC_LITERAL(341, 4174, 16), // "setLocationGroup"
QT_MOC_LITERAL(342, 4191, 19), // "removeLocationGroup"
QT_MOC_LITERAL(343, 4211, 16), // "addLocationGroup"
QT_MOC_LITERAL(344, 4228, 15), // "getLocGroupname"
QT_MOC_LITERAL(345, 4244, 8), // "tablenum"
QT_MOC_LITERAL(346, 4253, 12), // "getLocationX"
QT_MOC_LITERAL(347, 4266, 12), // "getLocationY"
QT_MOC_LITERAL(348, 4279, 13), // "getLocationTH"
QT_MOC_LITERAL(349, 4293, 15), // "isExistLocation"
QT_MOC_LITERAL(350, 4309, 8), // "getLidar"
QT_MOC_LITERAL(351, 4318, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(352, 4335, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(353, 4352, 17), // "clearSharedMemory"
QT_MOC_LITERAL(354, 4370, 12), // "getObjectNum"
QT_MOC_LITERAL(355, 4383, 13), // "getObjectName"
QT_MOC_LITERAL(356, 4397, 18), // "getObjectPointSize"
QT_MOC_LITERAL(357, 4416, 10), // "getObjectX"
QT_MOC_LITERAL(358, 4427, 5), // "point"
QT_MOC_LITERAL(359, 4433, 10), // "getObjectY"
QT_MOC_LITERAL(360, 4444, 14), // "getObjPointNum"
QT_MOC_LITERAL(361, 4459, 7), // "obj_num"
QT_MOC_LITERAL(362, 4467, 9), // "getLocNum"
QT_MOC_LITERAL(363, 4477, 13), // "saveLocations"
QT_MOC_LITERAL(364, 4491, 13), // "getObjectSize"
QT_MOC_LITERAL(365, 4505, 12), // "removeObject"
QT_MOC_LITERAL(366, 4518, 14), // "saveAnnotation"
QT_MOC_LITERAL(367, 4533, 8), // "isOdroid"
QT_MOC_LITERAL(368, 4542, 13), // "getMultiState"
QT_MOC_LITERAL(369, 4556, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(370, 4576, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(371, 4595, 15), // "getRunawayState"
QT_MOC_LITERAL(372, 4611, 15), // "slam_map_reload"
QT_MOC_LITERAL(373, 4627, 15), // "slam_ini_reload"
QT_MOC_LITERAL(374, 4643, 7), // "setTray"
QT_MOC_LITERAL(375, 4651, 8), // "tray_num"
QT_MOC_LITERAL(376, 4660, 12), // "startServing"
QT_MOC_LITERAL(377, 4673, 9), // "setPreset"
QT_MOC_LITERAL(378, 4683, 6), // "preset"
QT_MOC_LITERAL(379, 4690, 13), // "confirmPickup"
QT_MOC_LITERAL(380, 4704, 14), // "getPickuptrays"
QT_MOC_LITERAL(381, 4719, 10), // "QList<int>"
QT_MOC_LITERAL(382, 4730, 9), // "movePause"
QT_MOC_LITERAL(383, 4740, 10), // "moveResume"
QT_MOC_LITERAL(384, 4751, 12), // "moveStopFlag"
QT_MOC_LITERAL(385, 4764, 8), // "moveStop"
QT_MOC_LITERAL(386, 4773, 12), // "moveToCharge"
QT_MOC_LITERAL(387, 4786, 10), // "moveToWait"
QT_MOC_LITERAL(388, 4797, 14), // "moveToCleaning"
QT_MOC_LITERAL(389, 4812, 9), // "getcurLoc"
QT_MOC_LITERAL(390, 4822, 11), // "getcurTable"
QT_MOC_LITERAL(391, 4834, 16), // "resetHomeFolders"
QT_MOC_LITERAL(392, 4851, 13), // "issetLocation"
QT_MOC_LITERAL(393, 4865, 6), // "number"
QT_MOC_LITERAL(394, 4872, 11), // "getObsState"
QT_MOC_LITERAL(395, 4884, 10), // "getBattery"
QT_MOC_LITERAL(396, 4895, 13), // "getMotorState"
QT_MOC_LITERAL(397, 4909, 20), // "getLocalizationState"
QT_MOC_LITERAL(398, 4930, 14), // "getStateMoving"
QT_MOC_LITERAL(399, 4945, 10), // "getErrcode"
QT_MOC_LITERAL(400, 4956, 12), // "getRobotName"
QT_MOC_LITERAL(401, 4969, 18), // "getMotorConnection"
QT_MOC_LITERAL(402, 4988, 14), // "getMotorStatus"
QT_MOC_LITERAL(403, 5003, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(404, 5021, 19), // "getMotorTemperature"
QT_MOC_LITERAL(405, 5041, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(406, 5067, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(407, 5094, 15), // "getMotorCurrent"
QT_MOC_LITERAL(408, 5110, 14), // "getPowerStatus"
QT_MOC_LITERAL(409, 5125, 15), // "getRemoteStatus"
QT_MOC_LITERAL(410, 5141, 15), // "getChargeStatus"
QT_MOC_LITERAL(411, 5157, 12), // "getEmoStatus"
QT_MOC_LITERAL(412, 5170, 13), // "getLockStatus"
QT_MOC_LITERAL(413, 5184, 12), // "getBatteryIn"
QT_MOC_LITERAL(414, 5197, 13), // "getBatteryOut"
QT_MOC_LITERAL(415, 5211, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(416, 5229, 8), // "getPower"
QT_MOC_LITERAL(417, 5238, 13), // "getPowerTotal"
QT_MOC_LITERAL(418, 5252, 12), // "getObsinPath"
QT_MOC_LITERAL(419, 5265, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(420, 5283, 12), // "setMotorLock"
QT_MOC_LITERAL(421, 5296, 14), // "getRobotRadius"
QT_MOC_LITERAL(422, 5311, 9), // "getRobotx"
QT_MOC_LITERAL(423, 5321, 9), // "getRoboty"
QT_MOC_LITERAL(424, 5331, 10), // "getRobotth"
QT_MOC_LITERAL(425, 5342, 13), // "getlastRobotx"
QT_MOC_LITERAL(426, 5356, 13), // "getlastRoboty"
QT_MOC_LITERAL(427, 5370, 14), // "getlastRobotth"
QT_MOC_LITERAL(428, 5385, 10), // "getPathNum"
QT_MOC_LITERAL(429, 5396, 8), // "getPathx"
QT_MOC_LITERAL(430, 5405, 8), // "getPathy"
QT_MOC_LITERAL(431, 5414, 9), // "getPathth"
QT_MOC_LITERAL(432, 5424, 15), // "getLocalPathNum"
QT_MOC_LITERAL(433, 5440, 13), // "getLocalPathx"
QT_MOC_LITERAL(434, 5454, 13), // "getLocalPathy"
QT_MOC_LITERAL(435, 5468, 10), // "getuistate"
QT_MOC_LITERAL(436, 5479, 10), // "getMapname"
QT_MOC_LITERAL(437, 5490, 10), // "getMappath"
QT_MOC_LITERAL(438, 5501, 11), // "getMapWidth"
QT_MOC_LITERAL(439, 5513, 12), // "getMapHeight"
QT_MOC_LITERAL(440, 5526, 12), // "getGridWidth"
QT_MOC_LITERAL(441, 5539, 9), // "getOrigin"
QT_MOC_LITERAL(442, 5549, 15), // "getMappingWidth"
QT_MOC_LITERAL(443, 5565, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(444, 5585, 15), // "startDrawObject"
QT_MOC_LITERAL(445, 5601, 14), // "stopDrawObject"
QT_MOC_LITERAL(446, 5616, 14), // "saveDrawObject"
QT_MOC_LITERAL(447, 5631, 17), // "getObjectPointNum"
QT_MOC_LITERAL(448, 5649, 9), // "addObject"
QT_MOC_LITERAL(449, 5659, 14), // "addObjectPoint"
QT_MOC_LITERAL(450, 5674, 9), // "setObject"
QT_MOC_LITERAL(451, 5684, 15), // "editObjectStart"
QT_MOC_LITERAL(452, 5700, 10), // "editObject"
QT_MOC_LITERAL(453, 5711, 10), // "saveObject"
QT_MOC_LITERAL(454, 5722, 11), // "clearObject"
QT_MOC_LITERAL(455, 5734, 14), // "clearObjectAll"
QT_MOC_LITERAL(456, 5749, 12), // "selectObject"
QT_MOC_LITERAL(457, 5762, 13), // "getObjectflag"
QT_MOC_LITERAL(458, 5776, 10), // "undoObject"
QT_MOC_LITERAL(459, 5787, 15), // "clearRotateList"
QT_MOC_LITERAL(460, 5803, 13), // "setRotateList"
QT_MOC_LITERAL(461, 5817, 11), // "startPatrol"
QT_MOC_LITERAL(462, 5829, 6), // "pickup"
QT_MOC_LITERAL(463, 5836, 11), // "getICPRatio"
QT_MOC_LITERAL(464, 5848, 11), // "getICPError"
QT_MOC_LITERAL(465, 5860, 13), // "clearFlagStop"
QT_MOC_LITERAL(466, 5874, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(467, 5892, 17), // "moveToServingTest"
QT_MOC_LITERAL(468, 5910, 15), // "getusberrorsize"
QT_MOC_LITERAL(469, 5926, 11), // "getusberror"
QT_MOC_LITERAL(470, 5938, 11), // "getzipstate"
QT_MOC_LITERAL(471, 5950, 10), // "clear_call"
QT_MOC_LITERAL(472, 5961, 7), // "usbsave"
QT_MOC_LITERAL(473, 5969, 3), // "usb"
QT_MOC_LITERAL(474, 5973, 3), // "_ui"
QT_MOC_LITERAL(475, 5977, 5), // "_slam"
QT_MOC_LITERAL(476, 5983, 7), // "_config"
QT_MOC_LITERAL(477, 5991, 4), // "_map"
QT_MOC_LITERAL(478, 5996, 4), // "_log"
QT_MOC_LITERAL(479, 6001, 13), // "restartUpdate"
QT_MOC_LITERAL(480, 6015, 11), // "startUpdate"
QT_MOC_LITERAL(481, 6027, 18), // "getTravellineIssue"
QT_MOC_LITERAL(482, 6046, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(483, 6070, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(484, 6093, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(485, 6115, 24) // "getTravellineIssueBroken"

    },
    "Supervisor\0onTimer\0\0path_changed\0"
    "camera_update\0mapping_update\0usb_detect\0"
    "git_pull_failed\0git_pull_success\0"
    "new_call\0process_accept\0cmd\0process_done\0"
    "process_error\0param\0process_timeout\0"
    "update_success\0update_fail\0clear_all\0"
    "loadMapServer\0sendMapServer\0"
    "checkLocationName\0group\0name\0resetClear\0"
    "getWifiNum\0getWifiConnection\0ssid\0"
    "getCurWifiSSID\0getWifiSSID\0num\0"
    "connectWifi\0passwd\0getWifiSecurity\0"
    "getWifiLevel\0getWifiRate\0getWifiInuse\0"
    "getAllWifiList\0getWifiIP\0setWifi\0ip\0"
    "gateway\0dns\0getcurIP\0getcurGateway\0"
    "getcurDNS\0readWifiState\0setWifiSSD\0"
    "getSystemVolume\0checkMoveFail\0passInit\0"
    "loadFile\0type\0setMap\0moveMap\0setFullScreen\0"
    "setMapDrawing\0clicksound\0mode\0volume\0"
    "playBGM\0stopBGM\0isplayBGM\0playVoice\0"
    "voice\0confirmLocalization\0setName\0"
    "setTool\0getTool\0setMode\0setEnable\0en\0"
    "getMode\0setShowBrush\0onoff\0setShowLidar\0"
    "setShowLocation\0setRobotFollowing\0"
    "setShowTravelline\0setShowVelocitymap\0"
    "setShowObject\0setInitFlag\0getshowLocation\0"
    "getRobotFollowing\0getShowLidar\0"
    "setShowAvoidmap\0setInitPose\0x\0y\0th\0"
    "clearInitPose\0getAnnotModifiedDate\0"
    "startDrawingTline\0stopDrawingTline\0"
    "getDrawingTline\0setBoxPoint\0getPointBox\0"
    "saveRotateMap\0initRotate\0rotateMap\0"
    "angle\0rotateMapCW\0rotateMapCCW\0"
    "saveObjectPNG\0saveObsAreaPNG\0"
    "getLocalizationConfirm\0getDrawingFlag\0"
    "getDrawingUndoFlag\0startDrawing\0"
    "addLinePoint\0endDrawing\0setMapOrin\0"
    "startDrawingRect\0setDrawingRect\0"
    "endDrawingRect\0clearDrawing\0undoLine\0"
    "redoLine\0startSpline\0addSpline\0"
    "drawSpline\0endSpline\0save\0startDrawingLine\0"
    "setDrawingLine\0stopDrawingLine\0"
    "setLineColor\0color\0setLineWidth\0width\0"
    "getLocationNum\0saveLocation\0groupnum\0"
    "clearLocation\0addLocation\0addLocationCur\0"
    "setLocation\0editLocation\0removeLocation\0"
    "getLocationAvailable\0setTableNumberAuto\0"
    "getLocGroupNum\0saveMap\0saveEditedMap\0"
    "saveTline\0saveTlineTemp\0saveVelmap\0"
    "setMapSize\0height\0zoomIn\0dist\0zoomOut\0"
    "move\0getFileWidth\0getX\0getY\0getScale\0"
    "setVelmapView\0setTlineView\0setObjectView\0"
    "setAvoidmapView\0setLocationView\0"
    "setRobotView\0setSystemVolume\0"
    "requestSystemVolume\0setSize\0getCutBoxFlag\0"
    "selectLocation\0writelog\0msg\0"
    "startDrawingObject\0stopDrawingObject\0"
    "saveDrawingObject\0setLocationUp\0"
    "setLocationDown\0checkINI\0killSLAM\0"
    "makeRobotINI\0checkRobotINI\0restartSLAM\0"
    "startSLAM\0getIPCConnection\0getIPCRX\0"
    "getIPCTX\0programRestart\0programExit\0"
    "getRawMapPath\0getMapPath\0getAnnotPath\0"
    "getMetaPath\0getTravelPath\0getCostPath\0"
    "getIniPath\0file\0setSetting\0value\0"
    "readSetting\0map_name\0getSetting\0"
    "getTrayNum\0setTableColNum\0col_num\0"
    "getRobotType\0requestCamera\0getLeftCamera\0"
    "getRightCamera\0setCamera\0left\0right\0"
    "getCameraNum\0getCameraSerial\0setCursorView\0"
    "visible\0getVoice\0checkTravelline\0"
    "updateProgram\0updateProgramGitPull\0"
    "checkVersionAgain\0isNewVersion\0"
    "isNeedUpdate\0getLocalVersion\0"
    "getServerVersion\0getLocalVersionDate\0"
    "getLocalVersionMessage\0getServerVersionMessage\0"
    "getUpdateDate\0getUpdateSize\0"
    "getUpdateFileName\0getUpdateCommit\0"
    "getCurrentCommit\0getUpdateMessage\0"
    "getLastUpdateDate\0checkCleaningLocation\0"
    "checkUpdate\0checkNewUpdateProgram\0"
    "setLangauge\0lan\0isCallingMode\0goServing\0"
    "table\0getLocationbyCall\0LOCATION\0call\0"
    "getLocation\0getLocationbyID\0id\0"
    "setUiState\0state\0resetLocalization\0"
    "setLog\0getLogLineNum\0getLogLine\0"
    "getLogDate\0getLogAuth\0getLogMessage\0"
    "readLog\0date\0getLocaleDate\0year\0month\0"
    "updateUSB\0getusbsize\0readusbrecentfile\0"
    "getusbfilesize\0getusbfile\0getusbrecentfile\0"
    "getusbname\0readusb\0saveMapfromUsb\0"
    "path\0isConnectServer\0isLoadMap\0"
    "isExistMap\0isExistRawMap\0isExistTlineMap\0"
    "isExistAvoidMap\0isExistVelMap\0"
    "isExistObjectMap\0isExistTravelMap\0"
    "isExistAnnotation\0isExistRobotINI\0"
    "getAvailableMap\0getAvailableMapPath\0"
    "getMapFileSize\0getMapFile\0deleteEditedMap\0"
    "deleteAnnotation\0removeMap\0filename\0"
    "loadMap\0copyMap\0orinname\0newname\0"
    "rotate_map\0_src\0_dst\0startMapping\0"
    "mapsize\0grid\0stopMapping\0setSLAMMode\0"
    "saveMapping\0setInitCurPos\0setInitPos\0"
    "getInitPoseX\0getInitPoseY\0getInitPoseTH\0"
    "slam_setInit\0slam_run\0slam_stop\0"
    "slam_autoInit\0is_slam_running\0"
    "getMappingflag\0getObjectingflag\0"
    "setObjectingflag\0flag\0getnewMapname\0"
    "getLastCall\0getCallSize\0getCallQueueSize\0"
    "cleanTray\0getCallName\0clearCallQueue\0"
    "getCall\0getCallLocation\0setCallbell\0"
    "setCallbellForce\0acceptCall\0yes\0"
    "setObjPose\0getServingName\0getLocationName\0"
    "getLocationType\0getLocationNumber\0"
    "setLocationNumber\0getLocationSize\0"
    "getLocationGroup\0getLocationID\0"
    "getLocationGroupNum\0getLocationGroupSize\0"
    "getLocationCallID\0setLocationGroup\0"
    "removeLocationGroup\0addLocationGroup\0"
    "getLocGroupname\0tablenum\0getLocationX\0"
    "getLocationY\0getLocationTH\0isExistLocation\0"
    "getLidar\0getAnnotEditFlag\0setAnnotEditFlag\0"
    "clearSharedMemory\0getObjectNum\0"
    "getObjectName\0getObjectPointSize\0"
    "getObjectX\0point\0getObjectY\0getObjPointNum\0"
    "obj_num\0getLocNum\0saveLocations\0"
    "getObjectSize\0removeObject\0saveAnnotation\0"
    "isOdroid\0getMultiState\0drawingRunawayStart\0"
    "drawingRunawayStop\0getRunawayState\0"
    "slam_map_reload\0slam_ini_reload\0setTray\0"
    "tray_num\0startServing\0setPreset\0preset\0"
    "confirmPickup\0getPickuptrays\0QList<int>\0"
    "movePause\0moveResume\0moveStopFlag\0"
    "moveStop\0moveToCharge\0moveToWait\0"
    "moveToCleaning\0getcurLoc\0getcurTable\0"
    "resetHomeFolders\0issetLocation\0number\0"
    "getObsState\0getBattery\0getMotorState\0"
    "getLocalizationState\0getStateMoving\0"
    "getErrcode\0getRobotName\0getMotorConnection\0"
    "getMotorStatus\0getMotorStatusStr\0"
    "getMotorTemperature\0getMotorInsideTemperature\0"
    "getMotorWarningTemperature\0getMotorCurrent\0"
    "getPowerStatus\0getRemoteStatus\0"
    "getChargeStatus\0getEmoStatus\0getLockStatus\0"
    "getBatteryIn\0getBatteryOut\0getBatteryCurrent\0"
    "getPower\0getPowerTotal\0getObsinPath\0"
    "getRobotcurPreset\0setMotorLock\0"
    "getRobotRadius\0getRobotx\0getRoboty\0"
    "getRobotth\0getlastRobotx\0getlastRoboty\0"
    "getlastRobotth\0getPathNum\0getPathx\0"
    "getPathy\0getPathth\0getLocalPathNum\0"
    "getLocalPathx\0getLocalPathy\0getuistate\0"
    "getMapname\0getMappath\0getMapWidth\0"
    "getMapHeight\0getGridWidth\0getOrigin\0"
    "getMappingWidth\0getMappingGridwidth\0"
    "startDrawObject\0stopDrawObject\0"
    "saveDrawObject\0getObjectPointNum\0"
    "addObject\0addObjectPoint\0setObject\0"
    "editObjectStart\0editObject\0saveObject\0"
    "clearObject\0clearObjectAll\0selectObject\0"
    "getObjectflag\0undoObject\0clearRotateList\0"
    "setRotateList\0startPatrol\0pickup\0"
    "getICPRatio\0getICPError\0clearFlagStop\0"
    "slam_fullautoInit\0moveToServingTest\0"
    "getusberrorsize\0getusberror\0getzipstate\0"
    "clear_call\0usbsave\0usb\0_ui\0_slam\0"
    "_config\0_map\0_log\0restartUpdate\0"
    "startUpdate\0getTravellineIssue\0"
    "getTravellineIssueGroup\0getTravellineIssueName\0"
    "getTravellineIssueFar\0getTravellineIssueBroken"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Supervisor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     446,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 2244,    2, 0x0a /* Public */,
       3,    0, 2245,    2, 0x0a /* Public */,
       4,    0, 2246,    2, 0x0a /* Public */,
       5,    0, 2247,    2, 0x0a /* Public */,
       6,    0, 2248,    2, 0x0a /* Public */,
       7,    0, 2249,    2, 0x0a /* Public */,
       8,    0, 2250,    2, 0x0a /* Public */,
       9,    0, 2251,    2, 0x0a /* Public */,
      10,    1, 2252,    2, 0x0a /* Public */,
      12,    1, 2255,    2, 0x0a /* Public */,
      13,    2, 2258,    2, 0x0a /* Public */,
      15,    1, 2263,    2, 0x0a /* Public */,
      16,    0, 2266,    2, 0x0a /* Public */,
      17,    0, 2267,    2, 0x0a /* Public */,
      18,    0, 2268,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      19,    0, 2269,    2, 0x02 /* Public */,
      20,    0, 2270,    2, 0x02 /* Public */,
      21,    2, 2271,    2, 0x02 /* Public */,
      24,    0, 2276,    2, 0x02 /* Public */,
      25,    0, 2277,    2, 0x02 /* Public */,
      26,    1, 2278,    2, 0x02 /* Public */,
      28,    0, 2281,    2, 0x02 /* Public */,
      29,    1, 2282,    2, 0x02 /* Public */,
      31,    2, 2285,    2, 0x02 /* Public */,
      33,    1, 2290,    2, 0x02 /* Public */,
      34,    1, 2293,    2, 0x02 /* Public */,
      35,    1, 2296,    2, 0x02 /* Public */,
      36,    1, 2299,    2, 0x02 /* Public */,
      37,    0, 2302,    2, 0x02 /* Public */,
      38,    0, 2303,    2, 0x02 /* Public */,
      39,    3, 2304,    2, 0x02 /* Public */,
      43,    0, 2311,    2, 0x02 /* Public */,
      44,    0, 2312,    2, 0x02 /* Public */,
      45,    0, 2313,    2, 0x02 /* Public */,
      46,    1, 2314,    2, 0x02 /* Public */,
      47,    1, 2317,    2, 0x02 /* Public */,
      48,    0, 2320,    2, 0x02 /* Public */,
      49,    0, 2321,    2, 0x02 /* Public */,
      50,    0, 2322,    2, 0x02 /* Public */,
      51,    2, 2323,    2, 0x02 /* Public */,
      53,    0, 2328,    2, 0x02 /* Public */,
      54,    0, 2329,    2, 0x02 /* Public */,
      55,    0, 2330,    2, 0x02 /* Public */,
      56,    0, 2331,    2, 0x02 /* Public */,
      57,    2, 2332,    2, 0x02 /* Public */,
      57,    1, 2337,    2, 0x22 /* Public | MethodCloned */,
      60,    1, 2340,    2, 0x02 /* Public */,
      60,    0, 2343,    2, 0x22 /* Public | MethodCloned */,
      61,    0, 2344,    2, 0x02 /* Public */,
      62,    0, 2345,    2, 0x02 /* Public */,
      63,    2, 2346,    2, 0x02 /* Public */,
      63,    1, 2351,    2, 0x22 /* Public | MethodCloned */,
      65,    0, 2354,    2, 0x02 /* Public */,
      66,    1, 2355,    2, 0x02 /* Public */,
      67,    1, 2358,    2, 0x02 /* Public */,
      68,    0, 2361,    2, 0x02 /* Public */,
      69,    1, 2362,    2, 0x02 /* Public */,
      70,    1, 2365,    2, 0x02 /* Public */,
      72,    0, 2368,    2, 0x02 /* Public */,
      73,    1, 2369,    2, 0x02 /* Public */,
      75,    1, 2372,    2, 0x02 /* Public */,
      76,    1, 2375,    2, 0x02 /* Public */,
      77,    1, 2378,    2, 0x02 /* Public */,
      78,    1, 2381,    2, 0x02 /* Public */,
      79,    1, 2384,    2, 0x02 /* Public */,
      80,    1, 2387,    2, 0x02 /* Public */,
      81,    1, 2390,    2, 0x02 /* Public */,
      82,    0, 2393,    2, 0x02 /* Public */,
      83,    0, 2394,    2, 0x02 /* Public */,
      84,    0, 2395,    2, 0x02 /* Public */,
      85,    1, 2396,    2, 0x02 /* Public */,
      86,    3, 2399,    2, 0x02 /* Public */,
      90,    0, 2406,    2, 0x02 /* Public */,
      91,    0, 2407,    2, 0x02 /* Public */,
      92,    0, 2408,    2, 0x02 /* Public */,
      93,    0, 2409,    2, 0x02 /* Public */,
      94,    0, 2410,    2, 0x02 /* Public */,
      95,    3, 2411,    2, 0x02 /* Public */,
      96,    2, 2418,    2, 0x02 /* Public */,
      97,    0, 2423,    2, 0x02 /* Public */,
      98,    0, 2424,    2, 0x02 /* Public */,
      99,    1, 2425,    2, 0x02 /* Public */,
     101,    0, 2428,    2, 0x02 /* Public */,
     102,    0, 2429,    2, 0x02 /* Public */,
     103,    0, 2430,    2, 0x02 /* Public */,
     104,    0, 2431,    2, 0x02 /* Public */,
     105,    0, 2432,    2, 0x02 /* Public */,
     106,    0, 2433,    2, 0x02 /* Public */,
     107,    0, 2434,    2, 0x02 /* Public */,
     108,    2, 2435,    2, 0x02 /* Public */,
     109,    2, 2440,    2, 0x02 /* Public */,
     110,    2, 2445,    2, 0x02 /* Public */,
     111,    1, 2450,    2, 0x02 /* Public */,
     112,    2, 2453,    2, 0x02 /* Public */,
     113,    2, 2458,    2, 0x02 /* Public */,
     114,    0, 2463,    2, 0x02 /* Public */,
     115,    0, 2464,    2, 0x02 /* Public */,
     116,    0, 2465,    2, 0x02 /* Public */,
     117,    0, 2466,    2, 0x02 /* Public */,
     118,    2, 2467,    2, 0x02 /* Public */,
     119,    2, 2472,    2, 0x02 /* Public */,
     120,    0, 2477,    2, 0x02 /* Public */,
     121,    1, 2478,    2, 0x02 /* Public */,
     123,    2, 2481,    2, 0x02 /* Public */,
     124,    2, 2486,    2, 0x02 /* Public */,
     125,    2, 2491,    2, 0x02 /* Public */,
     126,    1, 2496,    2, 0x02 /* Public */,
     128,    1, 2499,    2, 0x02 /* Public */,
     130,    2, 2502,    2, 0x02 /* Public */,
     131,    3, 2507,    2, 0x02 /* Public */,
     133,    0, 2514,    2, 0x02 /* Public */,
     134,    3, 2515,    2, 0x02 /* Public */,
     135,    3, 2522,    2, 0x02 /* Public */,
     136,    3, 2529,    2, 0x02 /* Public */,
     137,    1, 2536,    2, 0x02 /* Public */,
     130,    2, 2539,    2, 0x02 /* Public */,
     138,    1, 2544,    2, 0x02 /* Public */,
     139,    1, 2547,    2, 0x02 /* Public */,
     140,    0, 2550,    2, 0x02 /* Public */,
     141,    1, 2551,    2, 0x02 /* Public */,
     142,    0, 2554,    2, 0x02 /* Public */,
     143,    0, 2555,    2, 0x02 /* Public */,
     144,    0, 2556,    2, 0x02 /* Public */,
     145,    0, 2557,    2, 0x02 /* Public */,
     146,    0, 2558,    2, 0x02 /* Public */,
     147,    2, 2559,    2, 0x02 /* Public */,
     149,    3, 2564,    2, 0x02 /* Public */,
     151,    3, 2571,    2, 0x02 /* Public */,
     152,    2, 2578,    2, 0x02 /* Public */,
     153,    0, 2583,    2, 0x02 /* Public */,
     154,    0, 2584,    2, 0x02 /* Public */,
     155,    0, 2585,    2, 0x02 /* Public */,
     156,    0, 2586,    2, 0x02 /* Public */,
     157,    1, 2587,    2, 0x02 /* Public */,
     158,    1, 2590,    2, 0x02 /* Public */,
     159,    1, 2593,    2, 0x02 /* Public */,
     160,    1, 2596,    2, 0x02 /* Public */,
     161,    1, 2599,    2, 0x02 /* Public */,
     162,    1, 2602,    2, 0x02 /* Public */,
     163,    1, 2605,    2, 0x02 /* Public */,
     164,    0, 2608,    2, 0x02 /* Public */,
     165,    3, 2609,    2, 0x02 /* Public */,
     166,    0, 2616,    2, 0x02 /* Public */,
     167,    1, 2617,    2, 0x02 /* Public */,
     168,    1, 2620,    2, 0x02 /* Public */,
     170,    0, 2623,    2, 0x02 /* Public */,
     171,    0, 2624,    2, 0x02 /* Public */,
     172,    0, 2625,    2, 0x02 /* Public */,
     173,    1, 2626,    2, 0x02 /* Public */,
     174,    1, 2629,    2, 0x02 /* Public */,
     175,    0, 2632,    2, 0x02 /* Public */,
     176,    0, 2633,    2, 0x02 /* Public */,
     177,    0, 2634,    2, 0x02 /* Public */,
     178,    0, 2635,    2, 0x02 /* Public */,
     179,    0, 2636,    2, 0x02 /* Public */,
     180,    0, 2637,    2, 0x02 /* Public */,
     181,    0, 2638,    2, 0x02 /* Public */,
     182,    0, 2639,    2, 0x02 /* Public */,
     183,    0, 2640,    2, 0x02 /* Public */,
     184,    0, 2641,    2, 0x02 /* Public */,
     185,    0, 2642,    2, 0x02 /* Public */,
     186,    1, 2643,    2, 0x02 /* Public */,
     187,    1, 2646,    2, 0x02 /* Public */,
     188,    1, 2649,    2, 0x02 /* Public */,
     189,    1, 2652,    2, 0x02 /* Public */,
     190,    1, 2655,    2, 0x02 /* Public */,
     191,    1, 2658,    2, 0x02 /* Public */,
     192,    1, 2661,    2, 0x02 /* Public */,
     194,    3, 2664,    2, 0x02 /* Public */,
     196,    1, 2671,    2, 0x02 /* Public */,
     196,    0, 2674,    2, 0x22 /* Public | MethodCloned */,
     198,    3, 2675,    2, 0x02 /* Public */,
     199,    0, 2682,    2, 0x02 /* Public */,
     200,    1, 2683,    2, 0x02 /* Public */,
     202,    0, 2686,    2, 0x02 /* Public */,
     203,    0, 2687,    2, 0x02 /* Public */,
     204,    0, 2688,    2, 0x02 /* Public */,
     205,    0, 2689,    2, 0x02 /* Public */,
     206,    2, 2690,    2, 0x02 /* Public */,
     209,    0, 2695,    2, 0x02 /* Public */,
     210,    1, 2696,    2, 0x02 /* Public */,
     211,    1, 2699,    2, 0x02 /* Public */,
     213,    2, 2702,    2, 0x02 /* Public */,
     213,    1, 2707,    2, 0x22 /* Public | MethodCloned */,
     214,    0, 2710,    2, 0x02 /* Public */,
     215,    0, 2711,    2, 0x02 /* Public */,
     216,    0, 2712,    2, 0x02 /* Public */,
     217,    0, 2713,    2, 0x02 /* Public */,
     218,    0, 2714,    2, 0x02 /* Public */,
     219,    0, 2715,    2, 0x02 /* Public */,
     220,    0, 2716,    2, 0x02 /* Public */,
     221,    0, 2717,    2, 0x02 /* Public */,
     222,    0, 2718,    2, 0x02 /* Public */,
     223,    0, 2719,    2, 0x02 /* Public */,
     224,    0, 2720,    2, 0x02 /* Public */,
     225,    0, 2721,    2, 0x02 /* Public */,
     226,    0, 2722,    2, 0x02 /* Public */,
     227,    1, 2723,    2, 0x02 /* Public */,
     228,    1, 2726,    2, 0x02 /* Public */,
     229,    1, 2729,    2, 0x02 /* Public */,
     230,    1, 2732,    2, 0x02 /* Public */,
     231,    1, 2735,    2, 0x02 /* Public */,
     232,    0, 2738,    2, 0x02 /* Public */,
     233,    0, 2739,    2, 0x02 /* Public */,
     234,    0, 2740,    2, 0x02 /* Public */,
     235,    1, 2741,    2, 0x02 /* Public */,
     237,    0, 2744,    2, 0x02 /* Public */,
     238,    2, 2745,    2, 0x02 /* Public */,
     240,    1, 2750,    2, 0x02 /* Public */,
     243,    2, 2753,    2, 0x02 /* Public */,
     244,    1, 2758,    2, 0x02 /* Public */,
     246,    1, 2761,    2, 0x02 /* Public */,
     248,    0, 2764,    2, 0x02 /* Public */,
     249,    1, 2765,    2, 0x02 /* Public */,
     250,    0, 2768,    2, 0x02 /* Public */,
     251,    1, 2769,    2, 0x02 /* Public */,
     252,    1, 2772,    2, 0x02 /* Public */,
     253,    1, 2775,    2, 0x02 /* Public */,
     254,    1, 2778,    2, 0x02 /* Public */,
     255,    1, 2781,    2, 0x02 /* Public */,
     257,    3, 2784,    2, 0x02 /* Public */,
     260,    0, 2791,    2, 0x02 /* Public */,
     261,    0, 2792,    2, 0x02 /* Public */,
     262,    0, 2793,    2, 0x02 /* Public */,
     263,    0, 2794,    2, 0x02 /* Public */,
     264,    1, 2795,    2, 0x02 /* Public */,
     265,    0, 2798,    2, 0x02 /* Public */,
     266,    1, 2799,    2, 0x02 /* Public */,
     267,    0, 2802,    2, 0x02 /* Public */,
     268,    1, 2803,    2, 0x02 /* Public */,
     270,    0, 2806,    2, 0x02 /* Public */,
     271,    0, 2807,    2, 0x02 /* Public */,
     272,    1, 2808,    2, 0x02 /* Public */,
     272,    0, 2811,    2, 0x22 /* Public | MethodCloned */,
     273,    1, 2812,    2, 0x02 /* Public */,
     274,    1, 2815,    2, 0x02 /* Public */,
     274,    0, 2818,    2, 0x22 /* Public | MethodCloned */,
     275,    1, 2819,    2, 0x02 /* Public */,
     275,    0, 2822,    2, 0x22 /* Public | MethodCloned */,
     276,    1, 2823,    2, 0x02 /* Public */,
     276,    0, 2826,    2, 0x22 /* Public | MethodCloned */,
     277,    1, 2827,    2, 0x02 /* Public */,
     277,    0, 2830,    2, 0x22 /* Public | MethodCloned */,
     278,    1, 2831,    2, 0x02 /* Public */,
     279,    1, 2834,    2, 0x02 /* Public */,
     280,    0, 2837,    2, 0x02 /* Public */,
     281,    0, 2838,    2, 0x02 /* Public */,
     282,    1, 2839,    2, 0x02 /* Public */,
     283,    1, 2842,    2, 0x02 /* Public */,
     284,    1, 2845,    2, 0x02 /* Public */,
     285,    0, 2848,    2, 0x02 /* Public */,
     286,    0, 2849,    2, 0x02 /* Public */,
     287,    1, 2850,    2, 0x02 /* Public */,
     289,    1, 2853,    2, 0x02 /* Public */,
     290,    2, 2856,    2, 0x02 /* Public */,
      53,    1, 2861,    2, 0x02 /* Public */,
     293,    3, 2864,    2, 0x02 /* Public */,
     296,    2, 2871,    2, 0x02 /* Public */,
     299,    0, 2876,    2, 0x02 /* Public */,
     300,    1, 2877,    2, 0x02 /* Public */,
     301,    1, 2880,    2, 0x02 /* Public */,
     302,    0, 2883,    2, 0x02 /* Public */,
     303,    3, 2884,    2, 0x02 /* Public */,
     304,    0, 2891,    2, 0x02 /* Public */,
     305,    0, 2892,    2, 0x02 /* Public */,
     306,    0, 2893,    2, 0x02 /* Public */,
     307,    0, 2894,    2, 0x02 /* Public */,
     308,    0, 2895,    2, 0x02 /* Public */,
     309,    0, 2896,    2, 0x02 /* Public */,
     310,    0, 2897,    2, 0x02 /* Public */,
     311,    0, 2898,    2, 0x02 /* Public */,
     312,    0, 2899,    2, 0x02 /* Public */,
     313,    0, 2900,    2, 0x02 /* Public */,
     314,    1, 2901,    2, 0x02 /* Public */,
     316,    0, 2904,    2, 0x02 /* Public */,
     317,    0, 2905,    2, 0x02 /* Public */,
     318,    0, 2906,    2, 0x02 /* Public */,
     319,    0, 2907,    2, 0x02 /* Public */,
     320,    0, 2908,    2, 0x02 /* Public */,
     321,    1, 2909,    2, 0x02 /* Public */,
     322,    0, 2912,    2, 0x02 /* Public */,
     323,    1, 2913,    2, 0x02 /* Public */,
     324,    1, 2916,    2, 0x02 /* Public */,
     325,    2, 2919,    2, 0x02 /* Public */,
     326,    2, 2924,    2, 0x02 /* Public */,
     327,    1, 2929,    2, 0x02 /* Public */,
     329,    0, 2932,    2, 0x02 /* Public */,
     330,    2, 2933,    2, 0x02 /* Public */,
     130,    1, 2938,    2, 0x02 /* Public */,
     130,    0, 2941,    2, 0x22 /* Public | MethodCloned */,
     331,    2, 2942,    2, 0x02 /* Public */,
     331,    1, 2947,    2, 0x22 /* Public | MethodCloned */,
     332,    1, 2950,    2, 0x02 /* Public */,
     333,    2, 2953,    2, 0x02 /* Public */,
     334,    2, 2958,    2, 0x02 /* Public */,
     335,    1, 2963,    2, 0x02 /* Public */,
     336,    1, 2966,    2, 0x02 /* Public */,
     337,    2, 2969,    2, 0x02 /* Public */,
     338,    0, 2974,    2, 0x02 /* Public */,
     339,    1, 2975,    2, 0x02 /* Public */,
     338,    1, 2978,    2, 0x02 /* Public */,
     340,    1, 2981,    2, 0x02 /* Public */,
     341,    2, 2984,    2, 0x02 /* Public */,
     342,    1, 2989,    2, 0x02 /* Public */,
     343,    1, 2992,    2, 0x02 /* Public */,
     344,    1, 2995,    2, 0x02 /* Public */,
     136,    4, 2998,    2, 0x02 /* Public */,
     346,    2, 3007,    2, 0x02 /* Public */,
     346,    1, 3012,    2, 0x22 /* Public | MethodCloned */,
     347,    2, 3015,    2, 0x02 /* Public */,
     347,    1, 3020,    2, 0x22 /* Public | MethodCloned */,
     348,    2, 3023,    2, 0x02 /* Public */,
     348,    1, 3028,    2, 0x22 /* Public | MethodCloned */,
     349,    2, 3031,    2, 0x02 /* Public */,
     350,    1, 3036,    2, 0x02 /* Public */,
     351,    0, 3039,    2, 0x02 /* Public */,
     352,    1, 3040,    2, 0x02 /* Public */,
     353,    0, 3043,    2, 0x02 /* Public */,
     354,    0, 3044,    2, 0x02 /* Public */,
     355,    1, 3045,    2, 0x02 /* Public */,
     356,    1, 3048,    2, 0x02 /* Public */,
     357,    2, 3051,    2, 0x02 /* Public */,
     359,    2, 3056,    2, 0x02 /* Public */,
     360,    3, 3061,    2, 0x02 /* Public */,
     362,    1, 3068,    2, 0x02 /* Public */,
     362,    2, 3071,    2, 0x02 /* Public */,
     363,    0, 3076,    2, 0x02 /* Public */,
     364,    1, 3077,    2, 0x02 /* Public */,
     365,    1, 3080,    2, 0x02 /* Public */,
     366,    1, 3083,    2, 0x02 /* Public */,
     367,    0, 3086,    2, 0x02 /* Public */,
     368,    0, 3087,    2, 0x02 /* Public */,
     369,    0, 3088,    2, 0x02 /* Public */,
     370,    0, 3089,    2, 0x02 /* Public */,
     371,    0, 3090,    2, 0x02 /* Public */,
     372,    2, 3091,    2, 0x02 /* Public */,
     372,    1, 3096,    2, 0x22 /* Public | MethodCloned */,
     373,    0, 3099,    2, 0x02 /* Public */,
     374,    3, 3100,    2, 0x02 /* Public */,
     376,    0, 3107,    2, 0x02 /* Public */,
     377,    1, 3108,    2, 0x02 /* Public */,
     379,    0, 3111,    2, 0x02 /* Public */,
     380,    0, 3112,    2, 0x02 /* Public */,
     382,    0, 3113,    2, 0x02 /* Public */,
     383,    0, 3114,    2, 0x02 /* Public */,
     384,    0, 3115,    2, 0x02 /* Public */,
     385,    0, 3116,    2, 0x02 /* Public */,
     386,    0, 3117,    2, 0x02 /* Public */,
     387,    0, 3118,    2, 0x02 /* Public */,
     388,    0, 3119,    2, 0x02 /* Public */,
     389,    0, 3120,    2, 0x02 /* Public */,
     390,    0, 3121,    2, 0x02 /* Public */,
     391,    0, 3122,    2, 0x02 /* Public */,
     392,    1, 3123,    2, 0x02 /* Public */,
     394,    0, 3126,    2, 0x02 /* Public */,
     395,    0, 3127,    2, 0x02 /* Public */,
     396,    0, 3128,    2, 0x02 /* Public */,
     397,    0, 3129,    2, 0x02 /* Public */,
     398,    0, 3130,    2, 0x02 /* Public */,
     399,    0, 3131,    2, 0x02 /* Public */,
     400,    0, 3132,    2, 0x02 /* Public */,
     401,    1, 3133,    2, 0x02 /* Public */,
     402,    1, 3136,    2, 0x02 /* Public */,
     403,    1, 3139,    2, 0x02 /* Public */,
     404,    1, 3142,    2, 0x02 /* Public */,
     405,    1, 3145,    2, 0x02 /* Public */,
     406,    0, 3148,    2, 0x02 /* Public */,
     407,    1, 3149,    2, 0x02 /* Public */,
     408,    0, 3152,    2, 0x02 /* Public */,
     409,    0, 3153,    2, 0x02 /* Public */,
     410,    0, 3154,    2, 0x02 /* Public */,
     411,    0, 3155,    2, 0x02 /* Public */,
     412,    0, 3156,    2, 0x02 /* Public */,
     413,    0, 3157,    2, 0x02 /* Public */,
     414,    0, 3158,    2, 0x02 /* Public */,
     415,    0, 3159,    2, 0x02 /* Public */,
     416,    0, 3160,    2, 0x02 /* Public */,
     417,    0, 3161,    2, 0x02 /* Public */,
     418,    0, 3162,    2, 0x02 /* Public */,
     419,    0, 3163,    2, 0x02 /* Public */,
     420,    1, 3164,    2, 0x02 /* Public */,
     421,    0, 3167,    2, 0x02 /* Public */,
     422,    0, 3168,    2, 0x02 /* Public */,
     423,    0, 3169,    2, 0x02 /* Public */,
     424,    0, 3170,    2, 0x02 /* Public */,
     425,    0, 3171,    2, 0x02 /* Public */,
     426,    0, 3172,    2, 0x02 /* Public */,
     427,    0, 3173,    2, 0x02 /* Public */,
     428,    0, 3174,    2, 0x02 /* Public */,
     429,    1, 3175,    2, 0x02 /* Public */,
     430,    1, 3178,    2, 0x02 /* Public */,
     431,    1, 3181,    2, 0x02 /* Public */,
     432,    0, 3184,    2, 0x02 /* Public */,
     433,    1, 3185,    2, 0x02 /* Public */,
     434,    1, 3188,    2, 0x02 /* Public */,
     435,    0, 3191,    2, 0x02 /* Public */,
     436,    0, 3192,    2, 0x02 /* Public */,
     437,    0, 3193,    2, 0x02 /* Public */,
     438,    0, 3194,    2, 0x02 /* Public */,
     439,    0, 3195,    2, 0x02 /* Public */,
     440,    0, 3196,    2, 0x02 /* Public */,
     441,    0, 3197,    2, 0x02 /* Public */,
     442,    0, 3198,    2, 0x02 /* Public */,
     443,    0, 3199,    2, 0x02 /* Public */,
     444,    0, 3200,    2, 0x02 /* Public */,
     445,    0, 3201,    2, 0x02 /* Public */,
     446,    0, 3202,    2, 0x02 /* Public */,
     354,    2, 3203,    2, 0x02 /* Public */,
     447,    2, 3208,    2, 0x02 /* Public */,
     448,    2, 3213,    2, 0x02 /* Public */,
     449,    2, 3218,    2, 0x02 /* Public */,
     450,    2, 3223,    2, 0x02 /* Public */,
     451,    2, 3228,    2, 0x02 /* Public */,
     452,    2, 3233,    2, 0x02 /* Public */,
     453,    0, 3238,    2, 0x02 /* Public */,
     454,    0, 3239,    2, 0x02 /* Public */,
     455,    0, 3240,    2, 0x02 /* Public */,
     456,    1, 3241,    2, 0x02 /* Public */,
     457,    0, 3244,    2, 0x02 /* Public */,
     458,    0, 3245,    2, 0x02 /* Public */,
     459,    0, 3246,    2, 0x02 /* Public */,
     460,    1, 3247,    2, 0x02 /* Public */,
     461,    2, 3250,    2, 0x02 /* Public */,
     463,    0, 3255,    2, 0x02 /* Public */,
     464,    0, 3256,    2, 0x02 /* Public */,
     465,    0, 3257,    2, 0x02 /* Public */,
     466,    0, 3258,    2, 0x02 /* Public */,
     467,    2, 3259,    2, 0x02 /* Public */,
     468,    0, 3264,    2, 0x02 /* Public */,
     469,    1, 3265,    2, 0x02 /* Public */,
     470,    0, 3268,    2, 0x02 /* Public */,
     471,    0, 3269,    2, 0x02 /* Public */,
     472,    6, 3270,    2, 0x02 /* Public */,
     472,    5, 3283,    2, 0x22 /* Public | MethodCloned */,
     472,    4, 3294,    2, 0x22 /* Public | MethodCloned */,
     472,    3, 3303,    2, 0x22 /* Public | MethodCloned */,
     472,    2, 3310,    2, 0x22 /* Public | MethodCloned */,
     472,    1, 3315,    2, 0x22 /* Public | MethodCloned */,
     472,    0, 3318,    2, 0x22 /* Public | MethodCloned */,
     479,    0, 3319,    2, 0x02 /* Public */,
     480,    0, 3320,    2, 0x02 /* Public */,
     481,    0, 3321,    2, 0x02 /* Public */,
     482,    1, 3322,    2, 0x02 /* Public */,
     483,    1, 3325,    2, 0x02 /* Public */,
     484,    1, 3328,    2, 0x02 /* Public */,
     485,    1, 3331,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   11,   14,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   22,   23,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   27,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   27,   32,
    QMetaType::Bool, QMetaType::QString,   27,
    QMetaType::Int, QMetaType::QString,   27,
    QMetaType::Int, QMetaType::QString,   27,
    QMetaType::Bool, QMetaType::QString,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   40,   41,   42,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   23,   52,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   58,   59,
    QMetaType::Void, QMetaType::QString,   58,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   64,   59,
    QMetaType::Void, QMetaType::QString,   64,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::Bool,   71,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,   89,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   30,   87,   88,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  100,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::QString,   52,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  122,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int,  127,
    QMetaType::Void, QMetaType::Int,  129,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   22,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   52,  132,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,   89,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Bool, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  129,  148,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,  150,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,  150,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,  129,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::QString,  169,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,  193,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  193,   23,  195,
    QMetaType::Void, QMetaType::QString,  197,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  193,   22,   23,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  201,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  207,  208,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Bool,  212,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   23,   58,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,  236,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   22,  239,
    0x80000000 | 241, QMetaType::QString,  242,
    0x80000000 | 241, QMetaType::Int, QMetaType::QString,   22,   23,
    0x80000000 | 241, QMetaType::Int,  245,
    QMetaType::Void, QMetaType::Int,  247,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::QDateTime,  256,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  258,  259,  256,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  269,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool, QMetaType::QString,   23,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Int, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  288,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  291,  292,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  294,  295,   58,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  297,  298,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   87,   88,   89,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  315,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  245,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  245,
    0x80000000 | 241, QMetaType::QString,  245,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   52,  245,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   52,   74,
    QMetaType::Void, QMetaType::Bool,  328,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   22,   30,
    QMetaType::Int, QMetaType::QString,   52,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   30,   52,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   30,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   23,   30,
    QMetaType::Int, QMetaType::QString,   52,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   22,   30,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   30,
    QMetaType::Int, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   30,   22,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   30,   23,   22,  345,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   30,   52,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   30,   52,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   30,   52,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   22,   30,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  315,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Int, QMetaType::Int,   30,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   30,  358,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   30,  358,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  361,   87,   88,
    QMetaType::Int, QMetaType::QString,   23,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   52,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Bool, QMetaType::QString,  288,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  288,   58,
    QMetaType::Void, QMetaType::QString,  288,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  375,   22,  239,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  378,
    QMetaType::Void,
    0x80000000 | 381,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int,  393,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  245,
    QMetaType::Int, QMetaType::Int,  245,
    QMetaType::QString, QMetaType::Int,  245,
    QMetaType::Int, QMetaType::Int,  245,
    QMetaType::Int, QMetaType::Int,  245,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  245,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Bool,   74,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Float, QMetaType::Int,   30,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    0x80000000 | 381,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   87,   88,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   58,  462,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   22,   23,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  473,  474,  475,  476,  477,  478,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  473,  474,  475,  476,  477,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  473,  474,  475,  476,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  473,  474,  475,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  473,  474,
    QMetaType::Void, QMetaType::QString,  473,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::QString, QMetaType::Int,   30,
    QMetaType::Bool, QMetaType::Int,   30,
    QMetaType::Bool, QMetaType::Int,   30,

       0        // eod
};

void Supervisor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Supervisor *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onTimer(); break;
        case 1: _t->path_changed(); break;
        case 2: _t->camera_update(); break;
        case 3: _t->mapping_update(); break;
        case 4: _t->usb_detect(); break;
        case 5: _t->git_pull_failed(); break;
        case 6: _t->git_pull_success(); break;
        case 7: _t->new_call(); break;
        case 8: _t->process_accept((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->process_done((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->process_error((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->process_timeout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->update_success(); break;
        case 13: _t->update_fail(); break;
        case 14: _t->clear_all(); break;
        case 15: _t->loadMapServer(); break;
        case 16: _t->sendMapServer(); break;
        case 17: { bool _r = _t->checkLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->resetClear(); break;
        case 19: { int _r = _t->getWifiNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 20: { int _r = _t->getWifiConnection((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 21: { QString _r = _t->getCurWifiSSID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 22: { QString _r = _t->getWifiSSID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->connectWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 24: { bool _r = _t->getWifiSecurity((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 25: { int _r = _t->getWifiLevel((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: { int _r = _t->getWifiRate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 27: { bool _r = _t->getWifiInuse((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->getAllWifiList(); break;
        case 29: _t->getWifiIP(); break;
        case 30: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 31: { QString _r = _t->getcurIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 32: { QString _r = _t->getcurGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 33: { QString _r = _t->getcurDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->readWifiState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 35: _t->setWifiSSD((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 36: { int _r = _t->getSystemVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 37: _t->checkMoveFail(); break;
        case 38: _t->passInit(); break;
        case 39: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 40: _t->setMap(); break;
        case 41: _t->moveMap(); break;
        case 42: _t->setFullScreen(); break;
        case 43: _t->setMapDrawing(); break;
        case 44: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 45: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 46: _t->playBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 47: _t->playBGM(); break;
        case 48: _t->stopBGM(); break;
        case 49: { bool _r = _t->isplayBGM();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 50: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 51: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 52: _t->confirmLocalization(); break;
        case 53: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 54: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 55: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 56: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 57: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 58: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 60: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 63: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 68: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 69: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 70: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 71: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 72: _t->clearInitPose(); break;
        case 73: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 74: _t->startDrawingTline(); break;
        case 75: _t->stopDrawingTline(); break;
        case 76: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 77: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 78: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 79: _t->saveRotateMap(); break;
        case 80: _t->initRotate(); break;
        case 81: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 82: _t->rotateMapCW(); break;
        case 83: _t->rotateMapCCW(); break;
        case 84: _t->saveObjectPNG(); break;
        case 85: _t->saveObsAreaPNG(); break;
        case 86: { int _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 87: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 88: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 89: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 90: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 91: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 92: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 93: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 94: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 95: _t->endDrawingRect(); break;
        case 96: _t->clearDrawing(); break;
        case 97: _t->undoLine(); break;
        case 98: _t->redoLine(); break;
        case 99: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 100: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 101: _t->drawSpline(); break;
        case 102: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 103: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 104: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 105: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 106: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 107: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 108: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 109: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 110: _t->clearLocation(); break;
        case 111: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 112: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 113: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 114: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 115: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 116: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 117: { bool _r = _t->getLocationAvailable((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 118: _t->setTableNumberAuto(); break;
        case 119: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 120: _t->saveMap(); break;
        case 121: _t->saveEditedMap(); break;
        case 122: _t->saveTline(); break;
        case 123: _t->saveTlineTemp(); break;
        case 124: _t->saveVelmap(); break;
        case 125: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 126: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 127: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 128: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 129: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 130: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 131: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 132: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 133: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 134: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 135: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 136: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 137: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 138: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 139: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 140: _t->requestSystemVolume(); break;
        case 141: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 142: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 143: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 144: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 145: _t->startDrawingObject(); break;
        case 146: _t->stopDrawingObject(); break;
        case 147: _t->saveDrawingObject(); break;
        case 148: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 149: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 150: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 151: _t->killSLAM(); break;
        case 152: _t->makeRobotINI(); break;
        case 153: _t->checkRobotINI(); break;
        case 154: _t->restartSLAM(); break;
        case 155: _t->startSLAM(); break;
        case 156: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 157: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 158: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 159: _t->programRestart(); break;
        case 160: _t->programExit(); break;
        case 161: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 162: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 163: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 164: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 165: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 166: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 167: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 168: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 169: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 170: _t->readSetting(); break;
        case 171: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 172: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 173: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 174: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 175: _t->requestCamera(); break;
        case 176: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 177: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 178: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 179: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 180: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 181: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 182: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 183: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 184: _t->checkTravelline(); break;
        case 185: _t->updateProgram(); break;
        case 186: _t->updateProgramGitPull(); break;
        case 187: _t->checkVersionAgain(); break;
        case 188: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 189: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 190: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 191: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 192: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 193: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 194: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 195: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 196: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 197: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 198: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 199: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 200: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 201: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 202: _t->checkCleaningLocation(); break;
        case 203: _t->checkUpdate(); break;
        case 204: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 205: _t->setLangauge((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 206: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 207: _t->goServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 208: { LOCATION _r = _t->getLocationbyCall((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 209: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 210: { LOCATION _r = _t->getLocationbyID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 211: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 212: _t->resetLocalization(); break;
        case 213: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 214: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 215: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 216: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 217: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 218: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 219: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 220: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 221: _t->updateUSB(); break;
        case 222: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 223: _t->readusbrecentfile(); break;
        case 224: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 225: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 226: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 227: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 228: _t->readusb(); break;
        case 229: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 230: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 231: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 232: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 233: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 234: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 235: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 236: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 237: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 238: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 239: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 240: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 241: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 242: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 243: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 244: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 245: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 246: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 247: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 248: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 249: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 250: _t->deleteEditedMap(); break;
        case 251: _t->deleteAnnotation(); break;
        case 252: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 253: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 254: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 255: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 256: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 257: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 258: _t->stopMapping(); break;
        case 259: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 260: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 261: _t->setInitCurPos(); break;
        case 262: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 263: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 264: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 265: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 266: _t->slam_setInit(); break;
        case 267: _t->slam_run(); break;
        case 268: _t->slam_stop(); break;
        case 269: _t->slam_autoInit(); break;
        case 270: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 271: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 272: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 273: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 274: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 275: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 276: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 277: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 278: _t->cleanTray(); break;
        case 279: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 280: _t->clearCallQueue(); break;
        case 281: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 282: { LOCATION _r = _t->getCallLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 283: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 284: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 285: _t->acceptCall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 286: _t->setObjPose(); break;
        case 287: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 288: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 289: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 290: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 291: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 292: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 293: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 294: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 295: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 296: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 297: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 298: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 299: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 300: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 301: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 302: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 303: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 304: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 305: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 306: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 307: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 308: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 309: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 310: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 311: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 312: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 313: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 314: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 315: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 316: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 317: _t->clearSharedMemory(); break;
        case 318: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 319: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 320: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 321: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 322: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 323: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 324: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 325: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 326: _t->saveLocations(); break;
        case 327: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 328: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 329: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 330: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 331: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 332: _t->drawingRunawayStart(); break;
        case 333: _t->drawingRunawayStop(); break;
        case 334: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 335: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 336: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 337: _t->slam_ini_reload(); break;
        case 338: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 339: _t->startServing(); break;
        case 340: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 341: _t->confirmPickup(); break;
        case 342: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 343: _t->movePause(); break;
        case 344: _t->moveResume(); break;
        case 345: _t->moveStopFlag(); break;
        case 346: _t->moveStop(); break;
        case 347: _t->moveToCharge(); break;
        case 348: _t->moveToWait(); break;
        case 349: _t->moveToCleaning(); break;
        case 350: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 351: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 352: _t->resetHomeFolders(); break;
        case 353: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 354: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 355: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 356: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 357: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 358: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 359: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 360: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 361: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 362: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 363: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 364: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 365: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 366: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 367: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 368: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 369: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 370: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 371: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 372: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 373: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 374: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 375: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 376: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 377: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 378: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 379: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 380: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 381: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 382: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 383: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 384: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 385: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 386: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 387: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 388: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 389: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 390: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 391: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 392: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 393: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 394: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 395: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 396: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 397: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 398: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 399: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 400: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 401: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 402: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 403: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 404: _t->startDrawObject(); break;
        case 405: _t->stopDrawObject(); break;
        case 406: _t->saveDrawObject(); break;
        case 407: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 408: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 409: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 410: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 411: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 412: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 413: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 414: _t->saveObject(); break;
        case 415: _t->clearObject(); break;
        case 416: _t->clearObjectAll(); break;
        case 417: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 418: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 419: _t->undoObject(); break;
        case 420: _t->clearRotateList(); break;
        case 421: _t->setRotateList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 422: _t->startPatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 423: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 424: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 425: _t->clearFlagStop(); break;
        case 426: _t->slam_fullautoInit(); break;
        case 427: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 428: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 429: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 430: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 431: _t->clear_call(); break;
        case 432: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 433: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 434: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 435: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 436: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 437: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 438: _t->usbsave(); break;
        case 439: _t->restartUpdate(); break;
        case 440: _t->startUpdate(); break;
        case 441: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 442: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 443: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 444: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 445: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Supervisor::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Supervisor.data,
    qt_meta_data_Supervisor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Supervisor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Supervisor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Supervisor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Supervisor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 446)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 446;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 446)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 446;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
