/****************************************************************************
** Meta object code from reading C++ file 'Supervisor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Supervisor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Supervisor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Supervisor_t {
    QByteArrayData data[451];
    char stringdata0[5635];
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
QT_MOC_LITERAL(14, 161, 15), // "process_timeout"
QT_MOC_LITERAL(15, 177, 14), // "update_success"
QT_MOC_LITERAL(16, 192, 11), // "update_fail"
QT_MOC_LITERAL(17, 204, 13), // "loadMapServer"
QT_MOC_LITERAL(18, 218, 13), // "sendMapServer"
QT_MOC_LITERAL(19, 232, 10), // "resetClear"
QT_MOC_LITERAL(20, 243, 10), // "getWifiNum"
QT_MOC_LITERAL(21, 254, 17), // "getWifiConnection"
QT_MOC_LITERAL(22, 272, 4), // "ssid"
QT_MOC_LITERAL(23, 277, 14), // "getCurWifiSSID"
QT_MOC_LITERAL(24, 292, 11), // "getWifiSSID"
QT_MOC_LITERAL(25, 304, 3), // "num"
QT_MOC_LITERAL(26, 308, 11), // "connectWifi"
QT_MOC_LITERAL(27, 320, 6), // "passwd"
QT_MOC_LITERAL(28, 327, 15), // "getWifiSecurity"
QT_MOC_LITERAL(29, 343, 12), // "getWifiLevel"
QT_MOC_LITERAL(30, 356, 11), // "getWifiRate"
QT_MOC_LITERAL(31, 368, 12), // "getWifiInuse"
QT_MOC_LITERAL(32, 381, 14), // "getAllWifiList"
QT_MOC_LITERAL(33, 396, 9), // "getWifiIP"
QT_MOC_LITERAL(34, 406, 7), // "setWifi"
QT_MOC_LITERAL(35, 414, 2), // "ip"
QT_MOC_LITERAL(36, 417, 7), // "gateway"
QT_MOC_LITERAL(37, 425, 3), // "dns"
QT_MOC_LITERAL(38, 429, 9), // "getcurSSD"
QT_MOC_LITERAL(39, 439, 8), // "getcurIP"
QT_MOC_LITERAL(40, 448, 13), // "getcurGateway"
QT_MOC_LITERAL(41, 462, 9), // "getcurDNS"
QT_MOC_LITERAL(42, 472, 13), // "readWifiState"
QT_MOC_LITERAL(43, 486, 10), // "setWifiSSD"
QT_MOC_LITERAL(44, 497, 15), // "getSystemVolume"
QT_MOC_LITERAL(45, 513, 13), // "checkMoveFail"
QT_MOC_LITERAL(46, 527, 8), // "passInit"
QT_MOC_LITERAL(47, 536, 8), // "loadFile"
QT_MOC_LITERAL(48, 545, 4), // "name"
QT_MOC_LITERAL(49, 550, 4), // "type"
QT_MOC_LITERAL(50, 555, 6), // "setMap"
QT_MOC_LITERAL(51, 562, 7), // "moveMap"
QT_MOC_LITERAL(52, 570, 13), // "setFullScreen"
QT_MOC_LITERAL(53, 584, 13), // "setMapDrawing"
QT_MOC_LITERAL(54, 598, 19), // "confirmLocalization"
QT_MOC_LITERAL(55, 618, 7), // "setName"
QT_MOC_LITERAL(56, 626, 7), // "setTool"
QT_MOC_LITERAL(57, 634, 7), // "getTool"
QT_MOC_LITERAL(58, 642, 7), // "setMode"
QT_MOC_LITERAL(59, 650, 9), // "setEnable"
QT_MOC_LITERAL(60, 660, 2), // "en"
QT_MOC_LITERAL(61, 663, 7), // "getMode"
QT_MOC_LITERAL(62, 671, 12), // "setShowBrush"
QT_MOC_LITERAL(63, 684, 5), // "onoff"
QT_MOC_LITERAL(64, 690, 12), // "setShowLidar"
QT_MOC_LITERAL(65, 703, 15), // "setShowLocation"
QT_MOC_LITERAL(66, 719, 17), // "setRobotFollowing"
QT_MOC_LITERAL(67, 737, 17), // "setShowTravelline"
QT_MOC_LITERAL(68, 755, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(69, 774, 11), // "setInitFlag"
QT_MOC_LITERAL(70, 786, 15), // "getshowLocation"
QT_MOC_LITERAL(71, 802, 17), // "getRobotFollowing"
QT_MOC_LITERAL(72, 820, 12), // "getShowLidar"
QT_MOC_LITERAL(73, 833, 11), // "setInitPose"
QT_MOC_LITERAL(74, 845, 1), // "x"
QT_MOC_LITERAL(75, 847, 1), // "y"
QT_MOC_LITERAL(76, 849, 2), // "th"
QT_MOC_LITERAL(77, 852, 13), // "clearInitPose"
QT_MOC_LITERAL(78, 866, 17), // "startDrawingTline"
QT_MOC_LITERAL(79, 884, 16), // "stopDrawingTline"
QT_MOC_LITERAL(80, 901, 15), // "getDrawingTline"
QT_MOC_LITERAL(81, 917, 11), // "setBoxPoint"
QT_MOC_LITERAL(82, 929, 11), // "getPointBox"
QT_MOC_LITERAL(83, 941, 13), // "saveRotateMap"
QT_MOC_LITERAL(84, 955, 10), // "initRotate"
QT_MOC_LITERAL(85, 966, 9), // "rotateMap"
QT_MOC_LITERAL(86, 976, 5), // "angle"
QT_MOC_LITERAL(87, 982, 11), // "rotateMapCW"
QT_MOC_LITERAL(88, 994, 12), // "rotateMapCCW"
QT_MOC_LITERAL(89, 1007, 13), // "saveObjectPNG"
QT_MOC_LITERAL(90, 1021, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(91, 1044, 14), // "getDrawingFlag"
QT_MOC_LITERAL(92, 1059, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(93, 1078, 12), // "startDrawing"
QT_MOC_LITERAL(94, 1091, 12), // "addLinePoint"
QT_MOC_LITERAL(95, 1104, 10), // "endDrawing"
QT_MOC_LITERAL(96, 1115, 10), // "setMapOrin"
QT_MOC_LITERAL(97, 1126, 16), // "startDrawingRect"
QT_MOC_LITERAL(98, 1143, 14), // "setDrawingRect"
QT_MOC_LITERAL(99, 1158, 14), // "endDrawingRect"
QT_MOC_LITERAL(100, 1173, 12), // "clearDrawing"
QT_MOC_LITERAL(101, 1186, 8), // "undoLine"
QT_MOC_LITERAL(102, 1195, 8), // "redoLine"
QT_MOC_LITERAL(103, 1204, 11), // "startSpline"
QT_MOC_LITERAL(104, 1216, 9), // "addSpline"
QT_MOC_LITERAL(105, 1226, 10), // "drawSpline"
QT_MOC_LITERAL(106, 1237, 9), // "endSpline"
QT_MOC_LITERAL(107, 1247, 4), // "save"
QT_MOC_LITERAL(108, 1252, 16), // "startDrawingLine"
QT_MOC_LITERAL(109, 1269, 14), // "setDrawingLine"
QT_MOC_LITERAL(110, 1284, 15), // "stopDrawingLine"
QT_MOC_LITERAL(111, 1300, 12), // "setLineColor"
QT_MOC_LITERAL(112, 1313, 5), // "color"
QT_MOC_LITERAL(113, 1319, 12), // "setLineWidth"
QT_MOC_LITERAL(114, 1332, 5), // "width"
QT_MOC_LITERAL(115, 1338, 12), // "saveLocation"
QT_MOC_LITERAL(116, 1351, 8), // "groupnum"
QT_MOC_LITERAL(117, 1360, 13), // "clearLocation"
QT_MOC_LITERAL(118, 1374, 11), // "addLocation"
QT_MOC_LITERAL(119, 1386, 14), // "addLocationCur"
QT_MOC_LITERAL(120, 1401, 11), // "setLocation"
QT_MOC_LITERAL(121, 1413, 12), // "editLocation"
QT_MOC_LITERAL(122, 1426, 14), // "getLocationNum"
QT_MOC_LITERAL(123, 1441, 14), // "removeLocation"
QT_MOC_LITERAL(124, 1456, 20), // "getLocationAvailable"
QT_MOC_LITERAL(125, 1477, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(126, 1496, 14), // "getLocGroupNum"
QT_MOC_LITERAL(127, 1511, 7), // "saveMap"
QT_MOC_LITERAL(128, 1519, 13), // "saveEditedMap"
QT_MOC_LITERAL(129, 1533, 9), // "saveTline"
QT_MOC_LITERAL(130, 1543, 13), // "saveTlineTemp"
QT_MOC_LITERAL(131, 1557, 10), // "saveVelmap"
QT_MOC_LITERAL(132, 1568, 10), // "setMapSize"
QT_MOC_LITERAL(133, 1579, 6), // "height"
QT_MOC_LITERAL(134, 1586, 6), // "zoomIn"
QT_MOC_LITERAL(135, 1593, 7), // "zoomOut"
QT_MOC_LITERAL(136, 1601, 4), // "move"
QT_MOC_LITERAL(137, 1606, 12), // "getFileWidth"
QT_MOC_LITERAL(138, 1619, 4), // "getX"
QT_MOC_LITERAL(139, 1624, 4), // "getY"
QT_MOC_LITERAL(140, 1629, 8), // "getScale"
QT_MOC_LITERAL(141, 1638, 15), // "setSystemVolume"
QT_MOC_LITERAL(142, 1654, 6), // "volume"
QT_MOC_LITERAL(143, 1661, 19), // "requestSystemVolume"
QT_MOC_LITERAL(144, 1681, 7), // "setSize"
QT_MOC_LITERAL(145, 1689, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(146, 1703, 14), // "selectLocation"
QT_MOC_LITERAL(147, 1718, 8), // "writelog"
QT_MOC_LITERAL(148, 1727, 3), // "msg"
QT_MOC_LITERAL(149, 1731, 18), // "startDrawingObject"
QT_MOC_LITERAL(150, 1750, 17), // "stopDrawingObject"
QT_MOC_LITERAL(151, 1768, 17), // "saveDrawingObject"
QT_MOC_LITERAL(152, 1786, 13), // "setLocationUp"
QT_MOC_LITERAL(153, 1800, 15), // "setLocationDown"
QT_MOC_LITERAL(154, 1816, 8), // "checkINI"
QT_MOC_LITERAL(155, 1825, 8), // "killSLAM"
QT_MOC_LITERAL(156, 1834, 12), // "makeRobotINI"
QT_MOC_LITERAL(157, 1847, 13), // "checkRobotINI"
QT_MOC_LITERAL(158, 1861, 11), // "restartSLAM"
QT_MOC_LITERAL(159, 1873, 9), // "startSLAM"
QT_MOC_LITERAL(160, 1883, 16), // "getIPCConnection"
QT_MOC_LITERAL(161, 1900, 8), // "getIPCRX"
QT_MOC_LITERAL(162, 1909, 8), // "getIPCTX"
QT_MOC_LITERAL(163, 1918, 14), // "programRestart"
QT_MOC_LITERAL(164, 1933, 11), // "programExit"
QT_MOC_LITERAL(165, 1945, 13), // "getRawMapPath"
QT_MOC_LITERAL(166, 1959, 10), // "getMapPath"
QT_MOC_LITERAL(167, 1970, 12), // "getAnnotPath"
QT_MOC_LITERAL(168, 1983, 11), // "getMetaPath"
QT_MOC_LITERAL(169, 1995, 13), // "getTravelPath"
QT_MOC_LITERAL(170, 2009, 11), // "getCostPath"
QT_MOC_LITERAL(171, 2021, 10), // "getIniPath"
QT_MOC_LITERAL(172, 2032, 4), // "file"
QT_MOC_LITERAL(173, 2037, 10), // "setSetting"
QT_MOC_LITERAL(174, 2048, 5), // "value"
QT_MOC_LITERAL(175, 2054, 11), // "readSetting"
QT_MOC_LITERAL(176, 2066, 8), // "map_name"
QT_MOC_LITERAL(177, 2075, 10), // "getSetting"
QT_MOC_LITERAL(178, 2086, 5), // "group"
QT_MOC_LITERAL(179, 2092, 10), // "getTrayNum"
QT_MOC_LITERAL(180, 2103, 14), // "setTableColNum"
QT_MOC_LITERAL(181, 2118, 7), // "col_num"
QT_MOC_LITERAL(182, 2126, 12), // "getRobotType"
QT_MOC_LITERAL(183, 2139, 13), // "requestCamera"
QT_MOC_LITERAL(184, 2153, 13), // "getLeftCamera"
QT_MOC_LITERAL(185, 2167, 14), // "getRightCamera"
QT_MOC_LITERAL(186, 2182, 9), // "setCamera"
QT_MOC_LITERAL(187, 2192, 4), // "left"
QT_MOC_LITERAL(188, 2197, 5), // "right"
QT_MOC_LITERAL(189, 2203, 12), // "getCameraNum"
QT_MOC_LITERAL(190, 2216, 15), // "getCameraSerial"
QT_MOC_LITERAL(191, 2232, 13), // "setCursorView"
QT_MOC_LITERAL(192, 2246, 7), // "visible"
QT_MOC_LITERAL(193, 2254, 8), // "getVoice"
QT_MOC_LITERAL(194, 2263, 4), // "mode"
QT_MOC_LITERAL(195, 2268, 15), // "checkTravelline"
QT_MOC_LITERAL(196, 2284, 13), // "updateProgram"
QT_MOC_LITERAL(197, 2298, 17), // "checkVersionAgain"
QT_MOC_LITERAL(198, 2316, 12), // "isNewVersion"
QT_MOC_LITERAL(199, 2329, 12), // "isNeedUpdate"
QT_MOC_LITERAL(200, 2342, 15), // "getLocalVersion"
QT_MOC_LITERAL(201, 2358, 16), // "getServerVersion"
QT_MOC_LITERAL(202, 2375, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(203, 2395, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(204, 2418, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(205, 2442, 13), // "getUpdateDate"
QT_MOC_LITERAL(206, 2456, 13), // "getUpdateSize"
QT_MOC_LITERAL(207, 2470, 17), // "getUpdateFileName"
QT_MOC_LITERAL(208, 2488, 15), // "getUpdateCommit"
QT_MOC_LITERAL(209, 2504, 16), // "getCurrentCommit"
QT_MOC_LITERAL(210, 2521, 16), // "getUpdateMessage"
QT_MOC_LITERAL(211, 2538, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(212, 2556, 11), // "checkUpdate"
QT_MOC_LITERAL(213, 2568, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(214, 2590, 11), // "setLangauge"
QT_MOC_LITERAL(215, 2602, 3), // "lan"
QT_MOC_LITERAL(216, 2606, 13), // "isCallingMode"
QT_MOC_LITERAL(217, 2620, 9), // "goServing"
QT_MOC_LITERAL(218, 2630, 5), // "table"
QT_MOC_LITERAL(219, 2636, 17), // "getLocationbyCall"
QT_MOC_LITERAL(220, 2654, 8), // "LOCATION"
QT_MOC_LITERAL(221, 2663, 4), // "call"
QT_MOC_LITERAL(222, 2668, 11), // "getLocation"
QT_MOC_LITERAL(223, 2680, 15), // "getLocationbyID"
QT_MOC_LITERAL(224, 2696, 2), // "id"
QT_MOC_LITERAL(225, 2699, 10), // "setUiState"
QT_MOC_LITERAL(226, 2710, 5), // "state"
QT_MOC_LITERAL(227, 2716, 17), // "resetLocalization"
QT_MOC_LITERAL(228, 2734, 6), // "setLog"
QT_MOC_LITERAL(229, 2741, 13), // "getLogLineNum"
QT_MOC_LITERAL(230, 2755, 10), // "getLogLine"
QT_MOC_LITERAL(231, 2766, 10), // "getLogDate"
QT_MOC_LITERAL(232, 2777, 10), // "getLogAuth"
QT_MOC_LITERAL(233, 2788, 13), // "getLogMessage"
QT_MOC_LITERAL(234, 2802, 7), // "readLog"
QT_MOC_LITERAL(235, 2810, 4), // "date"
QT_MOC_LITERAL(236, 2815, 13), // "getLocaleDate"
QT_MOC_LITERAL(237, 2829, 4), // "year"
QT_MOC_LITERAL(238, 2834, 5), // "month"
QT_MOC_LITERAL(239, 2840, 9), // "updateUSB"
QT_MOC_LITERAL(240, 2850, 10), // "getusbsize"
QT_MOC_LITERAL(241, 2861, 17), // "readusbrecentfile"
QT_MOC_LITERAL(242, 2879, 14), // "getusbfilesize"
QT_MOC_LITERAL(243, 2894, 10), // "getusbfile"
QT_MOC_LITERAL(244, 2905, 16), // "getusbrecentfile"
QT_MOC_LITERAL(245, 2922, 10), // "getusbname"
QT_MOC_LITERAL(246, 2933, 7), // "readusb"
QT_MOC_LITERAL(247, 2941, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(248, 2956, 4), // "path"
QT_MOC_LITERAL(249, 2961, 15), // "isConnectServer"
QT_MOC_LITERAL(250, 2977, 9), // "isLoadMap"
QT_MOC_LITERAL(251, 2987, 10), // "isExistMap"
QT_MOC_LITERAL(252, 2998, 13), // "isExistRawMap"
QT_MOC_LITERAL(253, 3012, 16), // "isExistTravelMap"
QT_MOC_LITERAL(254, 3029, 17), // "isExistAnnotation"
QT_MOC_LITERAL(255, 3047, 15), // "isExistRobotINI"
QT_MOC_LITERAL(256, 3063, 15), // "getAvailableMap"
QT_MOC_LITERAL(257, 3079, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(258, 3099, 14), // "getMapFileSize"
QT_MOC_LITERAL(259, 3114, 10), // "getMapFile"
QT_MOC_LITERAL(260, 3125, 15), // "deleteEditedMap"
QT_MOC_LITERAL(261, 3141, 16), // "deleteAnnotation"
QT_MOC_LITERAL(262, 3158, 9), // "removeMap"
QT_MOC_LITERAL(263, 3168, 8), // "filename"
QT_MOC_LITERAL(264, 3177, 7), // "loadMap"
QT_MOC_LITERAL(265, 3185, 10), // "rotate_map"
QT_MOC_LITERAL(266, 3196, 4), // "_src"
QT_MOC_LITERAL(267, 3201, 4), // "_dst"
QT_MOC_LITERAL(268, 3206, 12), // "startMapping"
QT_MOC_LITERAL(269, 3219, 7), // "mapsize"
QT_MOC_LITERAL(270, 3227, 4), // "grid"
QT_MOC_LITERAL(271, 3232, 11), // "stopMapping"
QT_MOC_LITERAL(272, 3244, 11), // "setSLAMMode"
QT_MOC_LITERAL(273, 3256, 11), // "saveMapping"
QT_MOC_LITERAL(274, 3268, 13), // "setInitCurPos"
QT_MOC_LITERAL(275, 3282, 10), // "setInitPos"
QT_MOC_LITERAL(276, 3293, 12), // "getInitPoseX"
QT_MOC_LITERAL(277, 3306, 12), // "getInitPoseY"
QT_MOC_LITERAL(278, 3319, 13), // "getInitPoseTH"
QT_MOC_LITERAL(279, 3333, 12), // "slam_setInit"
QT_MOC_LITERAL(280, 3346, 8), // "slam_run"
QT_MOC_LITERAL(281, 3355, 9), // "slam_stop"
QT_MOC_LITERAL(282, 3365, 13), // "slam_autoInit"
QT_MOC_LITERAL(283, 3379, 15), // "is_slam_running"
QT_MOC_LITERAL(284, 3395, 14), // "getMappingflag"
QT_MOC_LITERAL(285, 3410, 16), // "getObjectingflag"
QT_MOC_LITERAL(286, 3427, 16), // "setObjectingflag"
QT_MOC_LITERAL(287, 3444, 4), // "flag"
QT_MOC_LITERAL(288, 3449, 13), // "getnewMapname"
QT_MOC_LITERAL(289, 3463, 11), // "getLastCall"
QT_MOC_LITERAL(290, 3475, 11), // "getCallSize"
QT_MOC_LITERAL(291, 3487, 16), // "getCallQueueSize"
QT_MOC_LITERAL(292, 3504, 9), // "cleanTray"
QT_MOC_LITERAL(293, 3514, 11), // "getCallName"
QT_MOC_LITERAL(294, 3526, 14), // "clearCallQueue"
QT_MOC_LITERAL(295, 3541, 7), // "getCall"
QT_MOC_LITERAL(296, 3549, 15), // "getCallLocation"
QT_MOC_LITERAL(297, 3565, 11), // "setCallbell"
QT_MOC_LITERAL(298, 3577, 16), // "setCallbellForce"
QT_MOC_LITERAL(299, 3594, 10), // "acceptCall"
QT_MOC_LITERAL(300, 3605, 3), // "yes"
QT_MOC_LITERAL(301, 3609, 10), // "setObjPose"
QT_MOC_LITERAL(302, 3620, 14), // "getServingName"
QT_MOC_LITERAL(303, 3635, 15), // "getLocationName"
QT_MOC_LITERAL(304, 3651, 15), // "getLocationType"
QT_MOC_LITERAL(305, 3667, 17), // "getLocationNumber"
QT_MOC_LITERAL(306, 3685, 17), // "setLocationNumber"
QT_MOC_LITERAL(307, 3703, 15), // "getLocationSize"
QT_MOC_LITERAL(308, 3719, 16), // "getLocationGroup"
QT_MOC_LITERAL(309, 3736, 13), // "getLocationID"
QT_MOC_LITERAL(310, 3750, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(311, 3770, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(312, 3791, 17), // "getLocationCallID"
QT_MOC_LITERAL(313, 3809, 16), // "setLocationGroup"
QT_MOC_LITERAL(314, 3826, 19), // "removeLocationGroup"
QT_MOC_LITERAL(315, 3846, 16), // "addLocationGroup"
QT_MOC_LITERAL(316, 3863, 15), // "getLocGroupname"
QT_MOC_LITERAL(317, 3879, 8), // "tablenum"
QT_MOC_LITERAL(318, 3888, 12), // "getLocationX"
QT_MOC_LITERAL(319, 3901, 12), // "getLocationY"
QT_MOC_LITERAL(320, 3914, 13), // "getLocationTH"
QT_MOC_LITERAL(321, 3928, 15), // "isExistLocation"
QT_MOC_LITERAL(322, 3944, 8), // "getLidar"
QT_MOC_LITERAL(323, 3953, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(324, 3970, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(325, 3987, 17), // "clearSharedMemory"
QT_MOC_LITERAL(326, 4005, 12), // "getObjectNum"
QT_MOC_LITERAL(327, 4018, 13), // "getObjectName"
QT_MOC_LITERAL(328, 4032, 18), // "getObjectPointSize"
QT_MOC_LITERAL(329, 4051, 10), // "getObjectX"
QT_MOC_LITERAL(330, 4062, 5), // "point"
QT_MOC_LITERAL(331, 4068, 10), // "getObjectY"
QT_MOC_LITERAL(332, 4079, 14), // "getObjPointNum"
QT_MOC_LITERAL(333, 4094, 7), // "obj_num"
QT_MOC_LITERAL(334, 4102, 9), // "getLocNum"
QT_MOC_LITERAL(335, 4112, 13), // "saveLocations"
QT_MOC_LITERAL(336, 4126, 13), // "getObjectSize"
QT_MOC_LITERAL(337, 4140, 12), // "removeObject"
QT_MOC_LITERAL(338, 4153, 14), // "saveAnnotation"
QT_MOC_LITERAL(339, 4168, 8), // "isOdroid"
QT_MOC_LITERAL(340, 4177, 13), // "getMultiState"
QT_MOC_LITERAL(341, 4191, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(342, 4211, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(343, 4230, 15), // "getRunawayState"
QT_MOC_LITERAL(344, 4246, 15), // "slam_map_reload"
QT_MOC_LITERAL(345, 4262, 15), // "slam_ini_reload"
QT_MOC_LITERAL(346, 4278, 7), // "setTray"
QT_MOC_LITERAL(347, 4286, 8), // "tray_num"
QT_MOC_LITERAL(348, 4295, 9), // "table_num"
QT_MOC_LITERAL(349, 4305, 12), // "startServing"
QT_MOC_LITERAL(350, 4318, 9), // "setPreset"
QT_MOC_LITERAL(351, 4328, 6), // "preset"
QT_MOC_LITERAL(352, 4335, 13), // "confirmPickup"
QT_MOC_LITERAL(353, 4349, 14), // "getPickuptrays"
QT_MOC_LITERAL(354, 4364, 12), // "QVector<int>"
QT_MOC_LITERAL(355, 4377, 9), // "movePause"
QT_MOC_LITERAL(356, 4387, 10), // "moveResume"
QT_MOC_LITERAL(357, 4398, 12), // "moveStopFlag"
QT_MOC_LITERAL(358, 4411, 8), // "moveStop"
QT_MOC_LITERAL(359, 4420, 12), // "moveToCharge"
QT_MOC_LITERAL(360, 4433, 10), // "moveToWait"
QT_MOC_LITERAL(361, 4444, 9), // "getcurLoc"
QT_MOC_LITERAL(362, 4454, 11), // "getcurTable"
QT_MOC_LITERAL(363, 4466, 16), // "resetHomeFolders"
QT_MOC_LITERAL(364, 4483, 13), // "issetLocation"
QT_MOC_LITERAL(365, 4497, 6), // "number"
QT_MOC_LITERAL(366, 4504, 11), // "getObsState"
QT_MOC_LITERAL(367, 4516, 10), // "getBattery"
QT_MOC_LITERAL(368, 4527, 13), // "getMotorState"
QT_MOC_LITERAL(369, 4541, 20), // "getLocalizationState"
QT_MOC_LITERAL(370, 4562, 14), // "getStateMoving"
QT_MOC_LITERAL(371, 4577, 10), // "getErrcode"
QT_MOC_LITERAL(372, 4588, 12), // "getRobotName"
QT_MOC_LITERAL(373, 4601, 18), // "getMotorConnection"
QT_MOC_LITERAL(374, 4620, 14), // "getMotorStatus"
QT_MOC_LITERAL(375, 4635, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(376, 4653, 19), // "getMotorTemperature"
QT_MOC_LITERAL(377, 4673, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(378, 4699, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(379, 4726, 15), // "getMotorCurrent"
QT_MOC_LITERAL(380, 4742, 14), // "getPowerStatus"
QT_MOC_LITERAL(381, 4757, 15), // "getRemoteStatus"
QT_MOC_LITERAL(382, 4773, 15), // "getChargeStatus"
QT_MOC_LITERAL(383, 4789, 12), // "getEmoStatus"
QT_MOC_LITERAL(384, 4802, 13), // "getLockStatus"
QT_MOC_LITERAL(385, 4816, 12), // "getBatteryIn"
QT_MOC_LITERAL(386, 4829, 13), // "getBatteryOut"
QT_MOC_LITERAL(387, 4843, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(388, 4861, 8), // "getPower"
QT_MOC_LITERAL(389, 4870, 13), // "getPowerTotal"
QT_MOC_LITERAL(390, 4884, 12), // "getObsinPath"
QT_MOC_LITERAL(391, 4897, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(392, 4915, 12), // "setMotorLock"
QT_MOC_LITERAL(393, 4928, 14), // "getRobotRadius"
QT_MOC_LITERAL(394, 4943, 9), // "getRobotx"
QT_MOC_LITERAL(395, 4953, 9), // "getRoboty"
QT_MOC_LITERAL(396, 4963, 10), // "getRobotth"
QT_MOC_LITERAL(397, 4974, 13), // "getlastRobotx"
QT_MOC_LITERAL(398, 4988, 13), // "getlastRoboty"
QT_MOC_LITERAL(399, 5002, 14), // "getlastRobotth"
QT_MOC_LITERAL(400, 5017, 10), // "getPathNum"
QT_MOC_LITERAL(401, 5028, 8), // "getPathx"
QT_MOC_LITERAL(402, 5037, 8), // "getPathy"
QT_MOC_LITERAL(403, 5046, 9), // "getPathth"
QT_MOC_LITERAL(404, 5056, 15), // "getLocalPathNum"
QT_MOC_LITERAL(405, 5072, 13), // "getLocalPathx"
QT_MOC_LITERAL(406, 5086, 13), // "getLocalPathy"
QT_MOC_LITERAL(407, 5100, 10), // "getuistate"
QT_MOC_LITERAL(408, 5111, 10), // "getMapname"
QT_MOC_LITERAL(409, 5122, 10), // "getMappath"
QT_MOC_LITERAL(410, 5133, 11), // "getMapWidth"
QT_MOC_LITERAL(411, 5145, 12), // "getMapHeight"
QT_MOC_LITERAL(412, 5158, 12), // "getGridWidth"
QT_MOC_LITERAL(413, 5171, 9), // "getOrigin"
QT_MOC_LITERAL(414, 5181, 15), // "getMappingWidth"
QT_MOC_LITERAL(415, 5197, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(416, 5217, 15), // "startDrawObject"
QT_MOC_LITERAL(417, 5233, 14), // "stopDrawObject"
QT_MOC_LITERAL(418, 5248, 14), // "saveDrawObject"
QT_MOC_LITERAL(419, 5263, 17), // "getObjectPointNum"
QT_MOC_LITERAL(420, 5281, 9), // "addObject"
QT_MOC_LITERAL(421, 5291, 14), // "addObjectPoint"
QT_MOC_LITERAL(422, 5306, 9), // "setObject"
QT_MOC_LITERAL(423, 5316, 15), // "editObjectStart"
QT_MOC_LITERAL(424, 5332, 10), // "editObject"
QT_MOC_LITERAL(425, 5343, 10), // "saveObject"
QT_MOC_LITERAL(426, 5354, 11), // "clearObject"
QT_MOC_LITERAL(427, 5366, 14), // "clearObjectAll"
QT_MOC_LITERAL(428, 5381, 12), // "selectObject"
QT_MOC_LITERAL(429, 5394, 13), // "getObjectflag"
QT_MOC_LITERAL(430, 5408, 10), // "undoObject"
QT_MOC_LITERAL(431, 5419, 15), // "clearRotateList"
QT_MOC_LITERAL(432, 5435, 13), // "setRotateList"
QT_MOC_LITERAL(433, 5449, 11), // "startPatrol"
QT_MOC_LITERAL(434, 5461, 6), // "pickup"
QT_MOC_LITERAL(435, 5468, 13), // "clearFlagStop"
QT_MOC_LITERAL(436, 5482, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(437, 5500, 17), // "moveToServingTest"
QT_MOC_LITERAL(438, 5518, 15), // "getusberrorsize"
QT_MOC_LITERAL(439, 5534, 11), // "getusberror"
QT_MOC_LITERAL(440, 5546, 11), // "getzipstate"
QT_MOC_LITERAL(441, 5558, 10), // "clear_call"
QT_MOC_LITERAL(442, 5569, 7), // "usbsave"
QT_MOC_LITERAL(443, 5577, 3), // "usb"
QT_MOC_LITERAL(444, 5581, 3), // "_ui"
QT_MOC_LITERAL(445, 5585, 5), // "_slam"
QT_MOC_LITERAL(446, 5591, 7), // "_config"
QT_MOC_LITERAL(447, 5599, 4), // "_map"
QT_MOC_LITERAL(448, 5604, 4), // "_log"
QT_MOC_LITERAL(449, 5609, 13), // "restartUpdate"
QT_MOC_LITERAL(450, 5623, 11) // "startUpdate"

    },
    "Supervisor\0onTimer\0\0path_changed\0"
    "camera_update\0mapping_update\0usb_detect\0"
    "git_pull_failed\0git_pull_success\0"
    "new_call\0process_accept\0cmd\0process_done\0"
    "process_error\0process_timeout\0"
    "update_success\0update_fail\0loadMapServer\0"
    "sendMapServer\0resetClear\0getWifiNum\0"
    "getWifiConnection\0ssid\0getCurWifiSSID\0"
    "getWifiSSID\0num\0connectWifi\0passwd\0"
    "getWifiSecurity\0getWifiLevel\0getWifiRate\0"
    "getWifiInuse\0getAllWifiList\0getWifiIP\0"
    "setWifi\0ip\0gateway\0dns\0getcurSSD\0"
    "getcurIP\0getcurGateway\0getcurDNS\0"
    "readWifiState\0setWifiSSD\0getSystemVolume\0"
    "checkMoveFail\0passInit\0loadFile\0name\0"
    "type\0setMap\0moveMap\0setFullScreen\0"
    "setMapDrawing\0confirmLocalization\0"
    "setName\0setTool\0getTool\0setMode\0"
    "setEnable\0en\0getMode\0setShowBrush\0"
    "onoff\0setShowLidar\0setShowLocation\0"
    "setRobotFollowing\0setShowTravelline\0"
    "setShowVelocitymap\0setInitFlag\0"
    "getshowLocation\0getRobotFollowing\0"
    "getShowLidar\0setInitPose\0x\0y\0th\0"
    "clearInitPose\0startDrawingTline\0"
    "stopDrawingTline\0getDrawingTline\0"
    "setBoxPoint\0getPointBox\0saveRotateMap\0"
    "initRotate\0rotateMap\0angle\0rotateMapCW\0"
    "rotateMapCCW\0saveObjectPNG\0"
    "getLocalizationConfirm\0getDrawingFlag\0"
    "getDrawingUndoFlag\0startDrawing\0"
    "addLinePoint\0endDrawing\0setMapOrin\0"
    "startDrawingRect\0setDrawingRect\0"
    "endDrawingRect\0clearDrawing\0undoLine\0"
    "redoLine\0startSpline\0addSpline\0"
    "drawSpline\0endSpline\0save\0startDrawingLine\0"
    "setDrawingLine\0stopDrawingLine\0"
    "setLineColor\0color\0setLineWidth\0width\0"
    "saveLocation\0groupnum\0clearLocation\0"
    "addLocation\0addLocationCur\0setLocation\0"
    "editLocation\0getLocationNum\0removeLocation\0"
    "getLocationAvailable\0setTableNumberAuto\0"
    "getLocGroupNum\0saveMap\0saveEditedMap\0"
    "saveTline\0saveTlineTemp\0saveVelmap\0"
    "setMapSize\0height\0zoomIn\0zoomOut\0move\0"
    "getFileWidth\0getX\0getY\0getScale\0"
    "setSystemVolume\0volume\0requestSystemVolume\0"
    "setSize\0getCutBoxFlag\0selectLocation\0"
    "writelog\0msg\0startDrawingObject\0"
    "stopDrawingObject\0saveDrawingObject\0"
    "setLocationUp\0setLocationDown\0checkINI\0"
    "killSLAM\0makeRobotINI\0checkRobotINI\0"
    "restartSLAM\0startSLAM\0getIPCConnection\0"
    "getIPCRX\0getIPCTX\0programRestart\0"
    "programExit\0getRawMapPath\0getMapPath\0"
    "getAnnotPath\0getMetaPath\0getTravelPath\0"
    "getCostPath\0getIniPath\0file\0setSetting\0"
    "value\0readSetting\0map_name\0getSetting\0"
    "group\0getTrayNum\0setTableColNum\0col_num\0"
    "getRobotType\0requestCamera\0getLeftCamera\0"
    "getRightCamera\0setCamera\0left\0right\0"
    "getCameraNum\0getCameraSerial\0setCursorView\0"
    "visible\0getVoice\0mode\0checkTravelline\0"
    "updateProgram\0checkVersionAgain\0"
    "isNewVersion\0isNeedUpdate\0getLocalVersion\0"
    "getServerVersion\0getLocalVersionDate\0"
    "getLocalVersionMessage\0getServerVersionMessage\0"
    "getUpdateDate\0getUpdateSize\0"
    "getUpdateFileName\0getUpdateCommit\0"
    "getCurrentCommit\0getUpdateMessage\0"
    "getLastUpdateDate\0checkUpdate\0"
    "checkNewUpdateProgram\0setLangauge\0lan\0"
    "isCallingMode\0goServing\0table\0"
    "getLocationbyCall\0LOCATION\0call\0"
    "getLocation\0getLocationbyID\0id\0"
    "setUiState\0state\0resetLocalization\0"
    "setLog\0getLogLineNum\0getLogLine\0"
    "getLogDate\0getLogAuth\0getLogMessage\0"
    "readLog\0date\0getLocaleDate\0year\0month\0"
    "updateUSB\0getusbsize\0readusbrecentfile\0"
    "getusbfilesize\0getusbfile\0getusbrecentfile\0"
    "getusbname\0readusb\0saveMapfromUsb\0"
    "path\0isConnectServer\0isLoadMap\0"
    "isExistMap\0isExistRawMap\0isExistTravelMap\0"
    "isExistAnnotation\0isExistRobotINI\0"
    "getAvailableMap\0getAvailableMapPath\0"
    "getMapFileSize\0getMapFile\0deleteEditedMap\0"
    "deleteAnnotation\0removeMap\0filename\0"
    "loadMap\0rotate_map\0_src\0_dst\0startMapping\0"
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
    "tray_num\0table_num\0startServing\0"
    "setPreset\0preset\0confirmPickup\0"
    "getPickuptrays\0QVector<int>\0movePause\0"
    "moveResume\0moveStopFlag\0moveStop\0"
    "moveToCharge\0moveToWait\0getcurLoc\0"
    "getcurTable\0resetHomeFolders\0issetLocation\0"
    "number\0getObsState\0getBattery\0"
    "getMotorState\0getLocalizationState\0"
    "getStateMoving\0getErrcode\0getRobotName\0"
    "getMotorConnection\0getMotorStatus\0"
    "getMotorStatusStr\0getMotorTemperature\0"
    "getMotorInsideTemperature\0"
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
    "clearFlagStop\0slam_fullautoInit\0"
    "moveToServingTest\0getusberrorsize\0"
    "getusberror\0getzipstate\0clear_call\0"
    "usbsave\0usb\0_ui\0_slam\0_config\0_map\0"
    "_log\0restartUpdate\0startUpdate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Supervisor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     406,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 2044,    2, 0x0a /* Public */,
       3,    0, 2045,    2, 0x0a /* Public */,
       4,    0, 2046,    2, 0x0a /* Public */,
       5,    0, 2047,    2, 0x0a /* Public */,
       6,    0, 2048,    2, 0x0a /* Public */,
       7,    0, 2049,    2, 0x0a /* Public */,
       8,    0, 2050,    2, 0x0a /* Public */,
       9,    0, 2051,    2, 0x0a /* Public */,
      10,    1, 2052,    2, 0x0a /* Public */,
      12,    1, 2055,    2, 0x0a /* Public */,
      13,    1, 2058,    2, 0x0a /* Public */,
      14,    1, 2061,    2, 0x0a /* Public */,
      15,    0, 2064,    2, 0x0a /* Public */,
      16,    0, 2065,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      17,    0, 2066,    2, 0x02 /* Public */,
      18,    0, 2067,    2, 0x02 /* Public */,
      19,    0, 2068,    2, 0x02 /* Public */,
      20,    0, 2069,    2, 0x02 /* Public */,
      21,    1, 2070,    2, 0x02 /* Public */,
      23,    0, 2073,    2, 0x02 /* Public */,
      24,    1, 2074,    2, 0x02 /* Public */,
      26,    2, 2077,    2, 0x02 /* Public */,
      28,    1, 2082,    2, 0x02 /* Public */,
      29,    1, 2085,    2, 0x02 /* Public */,
      30,    1, 2088,    2, 0x02 /* Public */,
      31,    1, 2091,    2, 0x02 /* Public */,
      32,    0, 2094,    2, 0x02 /* Public */,
      33,    0, 2095,    2, 0x02 /* Public */,
      34,    3, 2096,    2, 0x02 /* Public */,
      38,    0, 2103,    2, 0x02 /* Public */,
      39,    0, 2104,    2, 0x02 /* Public */,
      40,    0, 2105,    2, 0x02 /* Public */,
      41,    0, 2106,    2, 0x02 /* Public */,
      42,    1, 2107,    2, 0x02 /* Public */,
      43,    1, 2110,    2, 0x02 /* Public */,
      44,    0, 2113,    2, 0x02 /* Public */,
      45,    0, 2114,    2, 0x02 /* Public */,
      46,    0, 2115,    2, 0x02 /* Public */,
      47,    2, 2116,    2, 0x02 /* Public */,
      50,    0, 2121,    2, 0x02 /* Public */,
      51,    0, 2122,    2, 0x02 /* Public */,
      52,    0, 2123,    2, 0x02 /* Public */,
      53,    0, 2124,    2, 0x02 /* Public */,
      54,    0, 2125,    2, 0x02 /* Public */,
      55,    1, 2126,    2, 0x02 /* Public */,
      56,    1, 2129,    2, 0x02 /* Public */,
      57,    0, 2132,    2, 0x02 /* Public */,
      58,    1, 2133,    2, 0x02 /* Public */,
      59,    1, 2136,    2, 0x02 /* Public */,
      61,    0, 2139,    2, 0x02 /* Public */,
      62,    1, 2140,    2, 0x02 /* Public */,
      64,    1, 2143,    2, 0x02 /* Public */,
      65,    1, 2146,    2, 0x02 /* Public */,
      66,    1, 2149,    2, 0x02 /* Public */,
      67,    1, 2152,    2, 0x02 /* Public */,
      68,    1, 2155,    2, 0x02 /* Public */,
      69,    1, 2158,    2, 0x02 /* Public */,
      70,    0, 2161,    2, 0x02 /* Public */,
      71,    0, 2162,    2, 0x02 /* Public */,
      72,    0, 2163,    2, 0x02 /* Public */,
      73,    3, 2164,    2, 0x02 /* Public */,
      77,    0, 2171,    2, 0x02 /* Public */,
      78,    0, 2172,    2, 0x02 /* Public */,
      79,    0, 2173,    2, 0x02 /* Public */,
      80,    0, 2174,    2, 0x02 /* Public */,
      81,    3, 2175,    2, 0x02 /* Public */,
      82,    2, 2182,    2, 0x02 /* Public */,
      83,    0, 2187,    2, 0x02 /* Public */,
      84,    0, 2188,    2, 0x02 /* Public */,
      85,    1, 2189,    2, 0x02 /* Public */,
      87,    0, 2192,    2, 0x02 /* Public */,
      88,    0, 2193,    2, 0x02 /* Public */,
      89,    0, 2194,    2, 0x02 /* Public */,
      90,    0, 2195,    2, 0x02 /* Public */,
      91,    0, 2196,    2, 0x02 /* Public */,
      92,    0, 2197,    2, 0x02 /* Public */,
      93,    2, 2198,    2, 0x02 /* Public */,
      94,    2, 2203,    2, 0x02 /* Public */,
      95,    2, 2208,    2, 0x02 /* Public */,
      96,    1, 2213,    2, 0x02 /* Public */,
      97,    2, 2216,    2, 0x02 /* Public */,
      98,    2, 2221,    2, 0x02 /* Public */,
      99,    0, 2226,    2, 0x02 /* Public */,
     100,    0, 2227,    2, 0x02 /* Public */,
     101,    0, 2228,    2, 0x02 /* Public */,
     102,    0, 2229,    2, 0x02 /* Public */,
     103,    2, 2230,    2, 0x02 /* Public */,
     104,    2, 2235,    2, 0x02 /* Public */,
     105,    0, 2240,    2, 0x02 /* Public */,
     106,    1, 2241,    2, 0x02 /* Public */,
     108,    2, 2244,    2, 0x02 /* Public */,
     109,    2, 2249,    2, 0x02 /* Public */,
     110,    2, 2254,    2, 0x02 /* Public */,
     111,    1, 2259,    2, 0x02 /* Public */,
     113,    1, 2262,    2, 0x02 /* Public */,
     115,    3, 2265,    2, 0x02 /* Public */,
     117,    0, 2272,    2, 0x02 /* Public */,
     118,    3, 2273,    2, 0x02 /* Public */,
     119,    3, 2280,    2, 0x02 /* Public */,
     120,    3, 2287,    2, 0x02 /* Public */,
     121,    1, 2294,    2, 0x02 /* Public */,
     122,    2, 2297,    2, 0x02 /* Public */,
     123,    1, 2302,    2, 0x02 /* Public */,
     124,    1, 2305,    2, 0x02 /* Public */,
     125,    0, 2308,    2, 0x02 /* Public */,
     126,    1, 2309,    2, 0x02 /* Public */,
     127,    0, 2312,    2, 0x02 /* Public */,
     128,    0, 2313,    2, 0x02 /* Public */,
     129,    0, 2314,    2, 0x02 /* Public */,
     130,    0, 2315,    2, 0x02 /* Public */,
     131,    0, 2316,    2, 0x02 /* Public */,
     132,    2, 2317,    2, 0x02 /* Public */,
     134,    2, 2322,    2, 0x02 /* Public */,
     135,    2, 2327,    2, 0x02 /* Public */,
     136,    2, 2332,    2, 0x02 /* Public */,
     137,    0, 2337,    2, 0x02 /* Public */,
     138,    0, 2338,    2, 0x02 /* Public */,
     139,    0, 2339,    2, 0x02 /* Public */,
     140,    0, 2340,    2, 0x02 /* Public */,
     141,    1, 2341,    2, 0x02 /* Public */,
     143,    0, 2344,    2, 0x02 /* Public */,
     144,    3, 2345,    2, 0x02 /* Public */,
     145,    0, 2352,    2, 0x02 /* Public */,
     146,    1, 2353,    2, 0x02 /* Public */,
     147,    1, 2356,    2, 0x02 /* Public */,
     149,    0, 2359,    2, 0x02 /* Public */,
     150,    0, 2360,    2, 0x02 /* Public */,
     151,    0, 2361,    2, 0x02 /* Public */,
     152,    1, 2362,    2, 0x02 /* Public */,
     153,    1, 2365,    2, 0x02 /* Public */,
     154,    0, 2368,    2, 0x02 /* Public */,
     155,    0, 2369,    2, 0x02 /* Public */,
     156,    0, 2370,    2, 0x02 /* Public */,
     157,    0, 2371,    2, 0x02 /* Public */,
     158,    0, 2372,    2, 0x02 /* Public */,
     159,    0, 2373,    2, 0x02 /* Public */,
     160,    0, 2374,    2, 0x02 /* Public */,
     161,    0, 2375,    2, 0x02 /* Public */,
     162,    0, 2376,    2, 0x02 /* Public */,
     163,    0, 2377,    2, 0x02 /* Public */,
     164,    0, 2378,    2, 0x02 /* Public */,
     165,    1, 2379,    2, 0x02 /* Public */,
     166,    1, 2382,    2, 0x02 /* Public */,
     167,    1, 2385,    2, 0x02 /* Public */,
     168,    1, 2388,    2, 0x02 /* Public */,
     169,    1, 2391,    2, 0x02 /* Public */,
     170,    1, 2394,    2, 0x02 /* Public */,
     171,    1, 2397,    2, 0x02 /* Public */,
     173,    3, 2400,    2, 0x02 /* Public */,
     175,    1, 2407,    2, 0x02 /* Public */,
     175,    0, 2410,    2, 0x22 /* Public | MethodCloned */,
     177,    3, 2411,    2, 0x02 /* Public */,
     179,    0, 2418,    2, 0x02 /* Public */,
     180,    1, 2419,    2, 0x02 /* Public */,
     182,    0, 2422,    2, 0x02 /* Public */,
     183,    0, 2423,    2, 0x02 /* Public */,
     184,    0, 2424,    2, 0x02 /* Public */,
     185,    0, 2425,    2, 0x02 /* Public */,
     186,    2, 2426,    2, 0x02 /* Public */,
     189,    0, 2431,    2, 0x02 /* Public */,
     190,    1, 2432,    2, 0x02 /* Public */,
     191,    1, 2435,    2, 0x02 /* Public */,
     193,    2, 2438,    2, 0x02 /* Public */,
     193,    1, 2443,    2, 0x22 /* Public | MethodCloned */,
     195,    0, 2446,    2, 0x02 /* Public */,
     196,    0, 2447,    2, 0x02 /* Public */,
     197,    0, 2448,    2, 0x02 /* Public */,
     198,    0, 2449,    2, 0x02 /* Public */,
     199,    0, 2450,    2, 0x02 /* Public */,
     200,    0, 2451,    2, 0x02 /* Public */,
     201,    0, 2452,    2, 0x02 /* Public */,
     202,    0, 2453,    2, 0x02 /* Public */,
     203,    0, 2454,    2, 0x02 /* Public */,
     204,    0, 2455,    2, 0x02 /* Public */,
     205,    0, 2456,    2, 0x02 /* Public */,
     206,    0, 2457,    2, 0x02 /* Public */,
     207,    1, 2458,    2, 0x02 /* Public */,
     208,    1, 2461,    2, 0x02 /* Public */,
     209,    1, 2464,    2, 0x02 /* Public */,
     210,    1, 2467,    2, 0x02 /* Public */,
     211,    1, 2470,    2, 0x02 /* Public */,
     212,    0, 2473,    2, 0x02 /* Public */,
     213,    0, 2474,    2, 0x02 /* Public */,
     214,    1, 2475,    2, 0x02 /* Public */,
     216,    0, 2478,    2, 0x02 /* Public */,
     217,    2, 2479,    2, 0x02 /* Public */,
     219,    1, 2484,    2, 0x02 /* Public */,
     222,    1, 2487,    2, 0x02 /* Public */,
     223,    1, 2490,    2, 0x02 /* Public */,
     225,    1, 2493,    2, 0x02 /* Public */,
     227,    0, 2496,    2, 0x02 /* Public */,
     228,    1, 2497,    2, 0x02 /* Public */,
     229,    0, 2500,    2, 0x02 /* Public */,
     230,    1, 2501,    2, 0x02 /* Public */,
     231,    1, 2504,    2, 0x02 /* Public */,
     232,    1, 2507,    2, 0x02 /* Public */,
     233,    1, 2510,    2, 0x02 /* Public */,
     234,    1, 2513,    2, 0x02 /* Public */,
     236,    3, 2516,    2, 0x02 /* Public */,
     239,    0, 2523,    2, 0x02 /* Public */,
     240,    0, 2524,    2, 0x02 /* Public */,
     241,    0, 2525,    2, 0x02 /* Public */,
     242,    0, 2526,    2, 0x02 /* Public */,
     243,    1, 2527,    2, 0x02 /* Public */,
     244,    0, 2530,    2, 0x02 /* Public */,
     245,    1, 2531,    2, 0x02 /* Public */,
     246,    0, 2534,    2, 0x02 /* Public */,
     247,    1, 2535,    2, 0x02 /* Public */,
     249,    0, 2538,    2, 0x02 /* Public */,
     250,    0, 2539,    2, 0x02 /* Public */,
     251,    1, 2540,    2, 0x02 /* Public */,
     251,    0, 2543,    2, 0x22 /* Public | MethodCloned */,
     252,    1, 2544,    2, 0x02 /* Public */,
     253,    1, 2547,    2, 0x02 /* Public */,
     254,    1, 2550,    2, 0x02 /* Public */,
     255,    0, 2553,    2, 0x02 /* Public */,
     256,    0, 2554,    2, 0x02 /* Public */,
     257,    1, 2555,    2, 0x02 /* Public */,
     258,    1, 2558,    2, 0x02 /* Public */,
     259,    1, 2561,    2, 0x02 /* Public */,
     260,    0, 2564,    2, 0x02 /* Public */,
     261,    0, 2565,    2, 0x02 /* Public */,
     262,    1, 2566,    2, 0x02 /* Public */,
     264,    1, 2569,    2, 0x02 /* Public */,
      50,    1, 2572,    2, 0x02 /* Public */,
     265,    3, 2575,    2, 0x02 /* Public */,
     268,    2, 2582,    2, 0x02 /* Public */,
     271,    0, 2587,    2, 0x02 /* Public */,
     272,    1, 2588,    2, 0x02 /* Public */,
     273,    1, 2591,    2, 0x02 /* Public */,
     274,    0, 2594,    2, 0x02 /* Public */,
     275,    3, 2595,    2, 0x02 /* Public */,
     276,    0, 2602,    2, 0x02 /* Public */,
     277,    0, 2603,    2, 0x02 /* Public */,
     278,    0, 2604,    2, 0x02 /* Public */,
     279,    0, 2605,    2, 0x02 /* Public */,
     280,    0, 2606,    2, 0x02 /* Public */,
     281,    0, 2607,    2, 0x02 /* Public */,
     282,    0, 2608,    2, 0x02 /* Public */,
     283,    0, 2609,    2, 0x02 /* Public */,
     284,    0, 2610,    2, 0x02 /* Public */,
     285,    0, 2611,    2, 0x02 /* Public */,
     286,    1, 2612,    2, 0x02 /* Public */,
     288,    0, 2615,    2, 0x02 /* Public */,
     289,    0, 2616,    2, 0x02 /* Public */,
     290,    0, 2617,    2, 0x02 /* Public */,
     291,    0, 2618,    2, 0x02 /* Public */,
     292,    0, 2619,    2, 0x02 /* Public */,
     293,    1, 2620,    2, 0x02 /* Public */,
     294,    0, 2623,    2, 0x02 /* Public */,
     295,    1, 2624,    2, 0x02 /* Public */,
     296,    1, 2627,    2, 0x02 /* Public */,
     297,    2, 2630,    2, 0x02 /* Public */,
     298,    2, 2635,    2, 0x02 /* Public */,
     299,    1, 2640,    2, 0x02 /* Public */,
     301,    0, 2643,    2, 0x02 /* Public */,
     302,    2, 2644,    2, 0x02 /* Public */,
     122,    1, 2649,    2, 0x02 /* Public */,
     122,    0, 2652,    2, 0x22 /* Public | MethodCloned */,
     303,    2, 2653,    2, 0x02 /* Public */,
     303,    1, 2658,    2, 0x22 /* Public | MethodCloned */,
     304,    1, 2661,    2, 0x02 /* Public */,
     305,    2, 2664,    2, 0x02 /* Public */,
     306,    2, 2669,    2, 0x02 /* Public */,
     307,    1, 2674,    2, 0x02 /* Public */,
     308,    1, 2677,    2, 0x02 /* Public */,
     309,    2, 2680,    2, 0x02 /* Public */,
     310,    0, 2685,    2, 0x02 /* Public */,
     311,    1, 2686,    2, 0x02 /* Public */,
     310,    1, 2689,    2, 0x02 /* Public */,
     312,    1, 2692,    2, 0x02 /* Public */,
     313,    2, 2695,    2, 0x02 /* Public */,
     314,    1, 2700,    2, 0x02 /* Public */,
     315,    1, 2703,    2, 0x02 /* Public */,
     316,    1, 2706,    2, 0x02 /* Public */,
     120,    4, 2709,    2, 0x02 /* Public */,
     318,    2, 2718,    2, 0x02 /* Public */,
     318,    1, 2723,    2, 0x22 /* Public | MethodCloned */,
     319,    2, 2726,    2, 0x02 /* Public */,
     319,    1, 2731,    2, 0x22 /* Public | MethodCloned */,
     320,    2, 2734,    2, 0x02 /* Public */,
     320,    1, 2739,    2, 0x22 /* Public | MethodCloned */,
     321,    2, 2742,    2, 0x02 /* Public */,
     322,    1, 2747,    2, 0x02 /* Public */,
     323,    0, 2750,    2, 0x02 /* Public */,
     324,    1, 2751,    2, 0x02 /* Public */,
     325,    0, 2754,    2, 0x02 /* Public */,
     326,    0, 2755,    2, 0x02 /* Public */,
     327,    1, 2756,    2, 0x02 /* Public */,
     328,    1, 2759,    2, 0x02 /* Public */,
     329,    2, 2762,    2, 0x02 /* Public */,
     331,    2, 2767,    2, 0x02 /* Public */,
     332,    3, 2772,    2, 0x02 /* Public */,
     334,    1, 2779,    2, 0x02 /* Public */,
     334,    2, 2782,    2, 0x02 /* Public */,
     335,    0, 2787,    2, 0x02 /* Public */,
     336,    1, 2788,    2, 0x02 /* Public */,
     337,    1, 2791,    2, 0x02 /* Public */,
     338,    1, 2794,    2, 0x02 /* Public */,
     339,    0, 2797,    2, 0x02 /* Public */,
     340,    0, 2798,    2, 0x02 /* Public */,
     341,    0, 2799,    2, 0x02 /* Public */,
     342,    0, 2800,    2, 0x02 /* Public */,
     343,    0, 2801,    2, 0x02 /* Public */,
     344,    1, 2802,    2, 0x02 /* Public */,
     345,    0, 2805,    2, 0x02 /* Public */,
     346,    2, 2806,    2, 0x02 /* Public */,
     349,    0, 2811,    2, 0x02 /* Public */,
     350,    1, 2812,    2, 0x02 /* Public */,
     352,    0, 2815,    2, 0x02 /* Public */,
     353,    0, 2816,    2, 0x02 /* Public */,
     355,    0, 2817,    2, 0x02 /* Public */,
     356,    0, 2818,    2, 0x02 /* Public */,
     357,    0, 2819,    2, 0x02 /* Public */,
     358,    0, 2820,    2, 0x02 /* Public */,
     359,    0, 2821,    2, 0x02 /* Public */,
     360,    0, 2822,    2, 0x02 /* Public */,
     361,    0, 2823,    2, 0x02 /* Public */,
     362,    0, 2824,    2, 0x02 /* Public */,
     363,    0, 2825,    2, 0x02 /* Public */,
     364,    1, 2826,    2, 0x02 /* Public */,
     366,    0, 2829,    2, 0x02 /* Public */,
     367,    0, 2830,    2, 0x02 /* Public */,
     368,    0, 2831,    2, 0x02 /* Public */,
     369,    0, 2832,    2, 0x02 /* Public */,
     370,    0, 2833,    2, 0x02 /* Public */,
     371,    0, 2834,    2, 0x02 /* Public */,
     372,    0, 2835,    2, 0x02 /* Public */,
     373,    1, 2836,    2, 0x02 /* Public */,
     374,    1, 2839,    2, 0x02 /* Public */,
     375,    1, 2842,    2, 0x02 /* Public */,
     376,    1, 2845,    2, 0x02 /* Public */,
     377,    1, 2848,    2, 0x02 /* Public */,
     378,    0, 2851,    2, 0x02 /* Public */,
     379,    1, 2852,    2, 0x02 /* Public */,
     380,    0, 2855,    2, 0x02 /* Public */,
     381,    0, 2856,    2, 0x02 /* Public */,
     382,    0, 2857,    2, 0x02 /* Public */,
     383,    0, 2858,    2, 0x02 /* Public */,
     384,    0, 2859,    2, 0x02 /* Public */,
     385,    0, 2860,    2, 0x02 /* Public */,
     386,    0, 2861,    2, 0x02 /* Public */,
     387,    0, 2862,    2, 0x02 /* Public */,
     388,    0, 2863,    2, 0x02 /* Public */,
     389,    0, 2864,    2, 0x02 /* Public */,
     390,    0, 2865,    2, 0x02 /* Public */,
     391,    0, 2866,    2, 0x02 /* Public */,
     392,    1, 2867,    2, 0x02 /* Public */,
     393,    0, 2870,    2, 0x02 /* Public */,
     394,    0, 2871,    2, 0x02 /* Public */,
     395,    0, 2872,    2, 0x02 /* Public */,
     396,    0, 2873,    2, 0x02 /* Public */,
     397,    0, 2874,    2, 0x02 /* Public */,
     398,    0, 2875,    2, 0x02 /* Public */,
     399,    0, 2876,    2, 0x02 /* Public */,
     400,    0, 2877,    2, 0x02 /* Public */,
     401,    1, 2878,    2, 0x02 /* Public */,
     402,    1, 2881,    2, 0x02 /* Public */,
     403,    1, 2884,    2, 0x02 /* Public */,
     404,    0, 2887,    2, 0x02 /* Public */,
     405,    1, 2888,    2, 0x02 /* Public */,
     406,    1, 2891,    2, 0x02 /* Public */,
     407,    0, 2894,    2, 0x02 /* Public */,
     408,    0, 2895,    2, 0x02 /* Public */,
     409,    0, 2896,    2, 0x02 /* Public */,
     410,    0, 2897,    2, 0x02 /* Public */,
     411,    0, 2898,    2, 0x02 /* Public */,
     412,    0, 2899,    2, 0x02 /* Public */,
     413,    0, 2900,    2, 0x02 /* Public */,
     414,    0, 2901,    2, 0x02 /* Public */,
     415,    0, 2902,    2, 0x02 /* Public */,
     416,    0, 2903,    2, 0x02 /* Public */,
     417,    0, 2904,    2, 0x02 /* Public */,
     418,    0, 2905,    2, 0x02 /* Public */,
     326,    2, 2906,    2, 0x02 /* Public */,
     419,    2, 2911,    2, 0x02 /* Public */,
     420,    2, 2916,    2, 0x02 /* Public */,
     421,    2, 2921,    2, 0x02 /* Public */,
     422,    2, 2926,    2, 0x02 /* Public */,
     423,    2, 2931,    2, 0x02 /* Public */,
     424,    2, 2936,    2, 0x02 /* Public */,
     425,    0, 2941,    2, 0x02 /* Public */,
     426,    0, 2942,    2, 0x02 /* Public */,
     427,    0, 2943,    2, 0x02 /* Public */,
     428,    1, 2944,    2, 0x02 /* Public */,
     429,    0, 2947,    2, 0x02 /* Public */,
     430,    0, 2948,    2, 0x02 /* Public */,
     431,    0, 2949,    2, 0x02 /* Public */,
     432,    1, 2950,    2, 0x02 /* Public */,
     433,    2, 2953,    2, 0x02 /* Public */,
     435,    0, 2958,    2, 0x02 /* Public */,
     436,    0, 2959,    2, 0x02 /* Public */,
     437,    1, 2960,    2, 0x02 /* Public */,
     438,    0, 2963,    2, 0x02 /* Public */,
     439,    1, 2964,    2, 0x02 /* Public */,
     440,    0, 2967,    2, 0x02 /* Public */,
     441,    0, 2968,    2, 0x02 /* Public */,
     442,    6, 2969,    2, 0x02 /* Public */,
     442,    5, 2982,    2, 0x22 /* Public | MethodCloned */,
     442,    4, 2993,    2, 0x22 /* Public | MethodCloned */,
     442,    3, 3002,    2, 0x22 /* Public | MethodCloned */,
     442,    2, 3009,    2, 0x22 /* Public | MethodCloned */,
     442,    1, 3014,    2, 0x22 /* Public | MethodCloned */,
     442,    0, 3017,    2, 0x22 /* Public | MethodCloned */,
     449,    0, 3018,    2, 0x02 /* Public */,
     450,    0, 3019,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,   27,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   35,   36,   37,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   48,   49,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void, QMetaType::Bool,   60,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   74,   75,   76,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   74,   75,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   86,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::QString,   49,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  107,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int,  112,
    QMetaType::Void, QMetaType::Int,  114,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   49,  116,   48,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   74,   75,   76,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   74,   75,   76,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   74,   75,   76,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Bool, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  114,  133,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int,  142,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   74,   75,  114,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString,  148,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int,   25,
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
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,  172,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  172,   48,  174,
    QMetaType::Void, QMetaType::QString,  176,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  172,  178,   48,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  181,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  187,  188,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Bool,  192,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   48,  194,
    QMetaType::QString, QMetaType::QString,   48,
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
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::QString,   48,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,  215,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  178,  218,
    0x80000000 | 220, QMetaType::QString,  221,
    0x80000000 | 220, QMetaType::QString,   48,
    0x80000000 | 220, QMetaType::Int,  224,
    QMetaType::Void, QMetaType::Int,  226,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QDateTime,  235,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  237,  238,  235,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  248,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   48,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   48,
    QMetaType::Bool, QMetaType::QString,   48,
    QMetaType::Bool, QMetaType::QString,   48,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Int, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  263,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  266,  267,  194,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  269,  270,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  194,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   74,   75,   76,
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
    QMetaType::Void, QMetaType::Bool,  287,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  224,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  224,
    0x80000000 | 220, QMetaType::QString,  224,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   49,  224,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   49,   63,
    QMetaType::Void, QMetaType::Bool,  300,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,  178,   25,
    QMetaType::Int, QMetaType::QString,   49,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   25,   49,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  178,   25,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   48,   25,
    QMetaType::Int, QMetaType::QString,   49,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  178,   25,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   25,
    QMetaType::Int, QMetaType::Int,   25,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,  178,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   25,   48,  178,  317,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   25,   49,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   25,   49,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   25,   49,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,  178,   25,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  287,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Int, QMetaType::Int,   25,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   25,  330,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   25,  330,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  333,   74,   75,
    QMetaType::Int, QMetaType::QString,   48,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   49,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Bool, QMetaType::QString,  263,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString,  263,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  347,  348,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  351,
    QMetaType::Void,
    0x80000000 | 354,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int,  365,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  224,
    QMetaType::Int, QMetaType::Int,  224,
    QMetaType::QString, QMetaType::Int,  224,
    QMetaType::Int, QMetaType::Int,  224,
    QMetaType::Int, QMetaType::Int,  224,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  224,
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
    QMetaType::Void, QMetaType::Bool,   63,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Float, QMetaType::Int,   25,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    0x80000000 | 354,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   74,   75,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  194,  434,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   48,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   25,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  443,  444,  445,  446,  447,  448,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  443,  444,  445,  446,  447,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  443,  444,  445,  446,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  443,  444,  445,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  443,  444,
    QMetaType::Void, QMetaType::QString,  443,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Supervisor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Supervisor *>(_o);
        Q_UNUSED(_t)
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
        case 10: _t->process_error((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->process_timeout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->update_success(); break;
        case 13: _t->update_fail(); break;
        case 14: _t->loadMapServer(); break;
        case 15: _t->sendMapServer(); break;
        case 16: _t->resetClear(); break;
        case 17: { int _r = _t->getWifiNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 18: { int _r = _t->getWifiConnection((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 19: { QString _r = _t->getCurWifiSSID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 20: { QString _r = _t->getWifiSSID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 21: _t->connectWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 22: { bool _r = _t->getWifiSecurity((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: { int _r = _t->getWifiLevel((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 24: { int _r = _t->getWifiRate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: { bool _r = _t->getWifiInuse((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: _t->getAllWifiList(); break;
        case 27: _t->getWifiIP(); break;
        case 28: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 29: { QString _r = _t->getcurSSD();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 30: { QString _r = _t->getcurIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 31: { QString _r = _t->getcurGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 32: { QString _r = _t->getcurDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->readWifiState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 34: _t->setWifiSSD((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 35: { int _r = _t->getSystemVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->checkMoveFail(); break;
        case 37: _t->passInit(); break;
        case 38: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 39: _t->setMap(); break;
        case 40: _t->moveMap(); break;
        case 41: _t->setFullScreen(); break;
        case 42: _t->setMapDrawing(); break;
        case 43: _t->confirmLocalization(); break;
        case 44: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 45: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 46: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 47: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 48: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 49: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 50: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 51: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 52: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 53: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 54: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 55: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 56: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 57: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 58: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 59: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 60: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 61: _t->clearInitPose(); break;
        case 62: _t->startDrawingTline(); break;
        case 63: _t->stopDrawingTline(); break;
        case 64: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 65: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 66: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 67: _t->saveRotateMap(); break;
        case 68: _t->initRotate(); break;
        case 69: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 70: _t->rotateMapCW(); break;
        case 71: _t->rotateMapCCW(); break;
        case 72: _t->saveObjectPNG(); break;
        case 73: { int _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 74: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 75: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 76: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 77: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 78: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 79: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 80: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 81: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 82: _t->endDrawingRect(); break;
        case 83: _t->clearDrawing(); break;
        case 84: _t->undoLine(); break;
        case 85: _t->redoLine(); break;
        case 86: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 87: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 88: _t->drawSpline(); break;
        case 89: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 90: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 91: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 92: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 93: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 94: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 95: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 96: _t->clearLocation(); break;
        case 97: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 98: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 99: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 100: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 101: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 102: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 103: { bool _r = _t->getLocationAvailable((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 104: _t->setTableNumberAuto(); break;
        case 105: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 106: _t->saveMap(); break;
        case 107: _t->saveEditedMap(); break;
        case 108: _t->saveTline(); break;
        case 109: _t->saveTlineTemp(); break;
        case 110: _t->saveVelmap(); break;
        case 111: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 112: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 113: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 114: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 115: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 116: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 117: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 118: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 119: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 120: _t->requestSystemVolume(); break;
        case 121: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 122: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 123: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 124: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 125: _t->startDrawingObject(); break;
        case 126: _t->stopDrawingObject(); break;
        case 127: _t->saveDrawingObject(); break;
        case 128: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 129: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 130: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 131: _t->killSLAM(); break;
        case 132: _t->makeRobotINI(); break;
        case 133: _t->checkRobotINI(); break;
        case 134: _t->restartSLAM(); break;
        case 135: _t->startSLAM(); break;
        case 136: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 137: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 138: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 139: _t->programRestart(); break;
        case 140: _t->programExit(); break;
        case 141: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 142: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 143: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 144: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 145: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 146: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 147: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 148: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 149: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 150: _t->readSetting(); break;
        case 151: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 152: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 153: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 154: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 155: _t->requestCamera(); break;
        case 156: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 157: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 158: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 159: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 160: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 161: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 162: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 163: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 164: _t->checkTravelline(); break;
        case 165: _t->updateProgram(); break;
        case 166: _t->checkVersionAgain(); break;
        case 167: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 168: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 169: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 170: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 171: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 172: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 173: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 174: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 175: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 176: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 177: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 178: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 179: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 180: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 181: _t->checkUpdate(); break;
        case 182: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 183: _t->setLangauge((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 184: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 185: _t->goServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 186: { LOCATION _r = _t->getLocationbyCall((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 187: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 188: { LOCATION _r = _t->getLocationbyID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 189: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 190: _t->resetLocalization(); break;
        case 191: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 192: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 193: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 194: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 195: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 196: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 197: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 198: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 199: _t->updateUSB(); break;
        case 200: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 201: _t->readusbrecentfile(); break;
        case 202: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 203: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 204: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 205: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 206: _t->readusb(); break;
        case 207: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 208: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 209: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 210: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 211: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 212: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 213: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 214: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 215: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 216: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 217: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 218: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 219: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 220: _t->deleteEditedMap(); break;
        case 221: _t->deleteAnnotation(); break;
        case 222: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 223: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 224: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 225: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 226: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 227: _t->stopMapping(); break;
        case 228: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 229: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 230: _t->setInitCurPos(); break;
        case 231: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 232: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 233: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 234: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 235: _t->slam_setInit(); break;
        case 236: _t->slam_run(); break;
        case 237: _t->slam_stop(); break;
        case 238: _t->slam_autoInit(); break;
        case 239: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 240: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 241: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 242: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 243: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 244: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 245: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 246: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 247: _t->cleanTray(); break;
        case 248: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 249: _t->clearCallQueue(); break;
        case 250: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 251: { LOCATION _r = _t->getCallLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 252: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 253: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 254: _t->acceptCall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 255: _t->setObjPose(); break;
        case 256: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 257: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 258: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 259: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 260: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 261: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 262: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 263: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 264: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 265: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 266: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 267: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 268: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 269: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 270: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 271: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 272: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 273: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 274: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 275: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 276: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 277: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 278: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 279: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 280: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 281: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 282: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 283: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 284: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 285: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 286: _t->clearSharedMemory(); break;
        case 287: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 288: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 289: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 290: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 291: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 292: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 293: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 294: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 295: _t->saveLocations(); break;
        case 296: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 297: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 298: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 299: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 300: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 301: _t->drawingRunawayStart(); break;
        case 302: _t->drawingRunawayStop(); break;
        case 303: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 304: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 305: _t->slam_ini_reload(); break;
        case 306: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 307: _t->startServing(); break;
        case 308: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 309: _t->confirmPickup(); break;
        case 310: { QVector<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QVector<int>*>(_a[0]) = std::move(_r); }  break;
        case 311: _t->movePause(); break;
        case 312: _t->moveResume(); break;
        case 313: _t->moveStopFlag(); break;
        case 314: _t->moveStop(); break;
        case 315: _t->moveToCharge(); break;
        case 316: _t->moveToWait(); break;
        case 317: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 318: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 319: _t->resetHomeFolders(); break;
        case 320: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 321: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 322: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 323: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 324: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 325: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 326: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 327: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 328: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 329: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 330: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 331: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 332: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 333: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 334: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 335: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 336: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 337: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 338: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 339: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 340: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 341: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 342: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 343: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 344: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 345: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 346: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 347: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 348: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 349: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 350: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 351: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 352: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 353: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 354: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 355: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 356: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 357: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 358: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 359: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 360: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 361: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 362: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 363: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 364: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 365: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 366: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 367: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 368: { QVector<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QVector<int>*>(_a[0]) = std::move(_r); }  break;
        case 369: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 370: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 371: _t->startDrawObject(); break;
        case 372: _t->stopDrawObject(); break;
        case 373: _t->saveDrawObject(); break;
        case 374: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 375: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 376: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 377: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 378: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 379: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 380: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 381: _t->saveObject(); break;
        case 382: _t->clearObject(); break;
        case 383: _t->clearObjectAll(); break;
        case 384: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 385: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 386: _t->undoObject(); break;
        case 387: _t->clearRotateList(); break;
        case 388: _t->setRotateList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 389: _t->startPatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 390: _t->clearFlagStop(); break;
        case 391: _t->slam_fullautoInit(); break;
        case 392: _t->moveToServingTest((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 393: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 394: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 395: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 396: _t->clear_call(); break;
        case 397: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 398: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 399: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 400: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 401: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 402: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 403: _t->usbsave(); break;
        case 404: _t->restartUpdate(); break;
        case 405: _t->startUpdate(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Supervisor::staticMetaObject = { {
    &QObject::staticMetaObject,
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
        if (_id < 406)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 406;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 406)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 406;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
