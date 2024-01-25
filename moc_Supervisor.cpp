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
    QByteArrayData data[516];
    char stringdata0[6573];
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
QT_MOC_LITERAL(19, 220, 9), // "map_reset"
QT_MOC_LITERAL(20, 230, 14), // "new_call_order"
QT_MOC_LITERAL(21, 245, 4), // "name"
QT_MOC_LITERAL(22, 250, 13), // "loadMapServer"
QT_MOC_LITERAL(23, 264, 13), // "sendMapServer"
QT_MOC_LITERAL(24, 278, 17), // "checkLocationName"
QT_MOC_LITERAL(25, 296, 5), // "group"
QT_MOC_LITERAL(26, 302, 10), // "resetClear"
QT_MOC_LITERAL(27, 313, 10), // "getWifiNum"
QT_MOC_LITERAL(28, 324, 17), // "getWifiConnection"
QT_MOC_LITERAL(29, 342, 4), // "ssid"
QT_MOC_LITERAL(30, 347, 14), // "getCurWifiSSID"
QT_MOC_LITERAL(31, 362, 11), // "getWifiSSID"
QT_MOC_LITERAL(32, 374, 3), // "num"
QT_MOC_LITERAL(33, 378, 11), // "connectWifi"
QT_MOC_LITERAL(34, 390, 6), // "passwd"
QT_MOC_LITERAL(35, 397, 15), // "getWifiSecurity"
QT_MOC_LITERAL(36, 413, 12), // "getWifiLevel"
QT_MOC_LITERAL(37, 426, 11), // "getWifiRate"
QT_MOC_LITERAL(38, 438, 12), // "getWifiInuse"
QT_MOC_LITERAL(39, 451, 14), // "getAllWifiList"
QT_MOC_LITERAL(40, 466, 9), // "getWifiIP"
QT_MOC_LITERAL(41, 476, 7), // "setWifi"
QT_MOC_LITERAL(42, 484, 2), // "ip"
QT_MOC_LITERAL(43, 487, 7), // "gateway"
QT_MOC_LITERAL(44, 495, 3), // "dns"
QT_MOC_LITERAL(45, 499, 8), // "getcurIP"
QT_MOC_LITERAL(46, 508, 13), // "getcurGateway"
QT_MOC_LITERAL(47, 522, 9), // "getcurDNS"
QT_MOC_LITERAL(48, 532, 13), // "readWifiState"
QT_MOC_LITERAL(49, 546, 10), // "setWifiSSD"
QT_MOC_LITERAL(50, 557, 15), // "getSystemVolume"
QT_MOC_LITERAL(51, 573, 8), // "passInit"
QT_MOC_LITERAL(52, 582, 10), // "readPatrol"
QT_MOC_LITERAL(53, 593, 13), // "getPatrolSize"
QT_MOC_LITERAL(54, 607, 13), // "getPatrolName"
QT_MOC_LITERAL(55, 621, 13), // "getPatrolType"
QT_MOC_LITERAL(56, 635, 17), // "getPatrolLocation"
QT_MOC_LITERAL(57, 653, 19), // "getPatrolMovingPage"
QT_MOC_LITERAL(58, 673, 19), // "getPatrolArrivePage"
QT_MOC_LITERAL(59, 693, 17), // "getPatrolWaitTime"
QT_MOC_LITERAL(60, 711, 14), // "getPatrolVoice"
QT_MOC_LITERAL(61, 726, 18), // "getPatrolVoiceMode"
QT_MOC_LITERAL(62, 745, 12), // "isPatrolPage"
QT_MOC_LITERAL(63, 758, 19), // "getPatrolMovingMode"
QT_MOC_LITERAL(64, 778, 19), // "getPatrolArriveMode"
QT_MOC_LITERAL(65, 798, 16), // "setCurrentPatrol"
QT_MOC_LITERAL(66, 815, 21), // "getPatrolLocationSize"
QT_MOC_LITERAL(67, 837, 3), // "loc"
QT_MOC_LITERAL(68, 841, 19), // "clearPatrolLocation"
QT_MOC_LITERAL(69, 861, 4), // "mode"
QT_MOC_LITERAL(70, 866, 17), // "addPatrolLocation"
QT_MOC_LITERAL(71, 884, 19), // "setPatrolMovingPage"
QT_MOC_LITERAL(72, 904, 6), // "param1"
QT_MOC_LITERAL(73, 911, 6), // "param2"
QT_MOC_LITERAL(74, 918, 6), // "param3"
QT_MOC_LITERAL(75, 925, 19), // "setPatrolArrivePage"
QT_MOC_LITERAL(76, 945, 14), // "setPatrolVoice"
QT_MOC_LITERAL(77, 960, 4), // "text"
QT_MOC_LITERAL(78, 965, 9), // "setPatrol"
QT_MOC_LITERAL(79, 975, 4), // "type"
QT_MOC_LITERAL(80, 980, 9), // "wait_time"
QT_MOC_LITERAL(81, 990, 10), // "savePatrol"
QT_MOC_LITERAL(82, 1001, 12), // "deletePatrol"
QT_MOC_LITERAL(83, 1014, 11), // "startPatrol"
QT_MOC_LITERAL(84, 1026, 8), // "loadFile"
QT_MOC_LITERAL(85, 1035, 6), // "setMap"
QT_MOC_LITERAL(86, 1042, 7), // "moveMap"
QT_MOC_LITERAL(87, 1050, 13), // "setFullScreen"
QT_MOC_LITERAL(88, 1064, 13), // "setMapDrawing"
QT_MOC_LITERAL(89, 1078, 10), // "clicksound"
QT_MOC_LITERAL(90, 1089, 6), // "volume"
QT_MOC_LITERAL(91, 1096, 7), // "playBGM"
QT_MOC_LITERAL(92, 1104, 7), // "stopBGM"
QT_MOC_LITERAL(93, 1112, 9), // "isplayBGM"
QT_MOC_LITERAL(94, 1122, 9), // "playVoice"
QT_MOC_LITERAL(95, 1132, 5), // "voice"
QT_MOC_LITERAL(96, 1138, 19), // "confirmLocalization"
QT_MOC_LITERAL(97, 1158, 7), // "setName"
QT_MOC_LITERAL(98, 1166, 7), // "setTool"
QT_MOC_LITERAL(99, 1174, 7), // "getTool"
QT_MOC_LITERAL(100, 1182, 7), // "setMode"
QT_MOC_LITERAL(101, 1190, 9), // "setEnable"
QT_MOC_LITERAL(102, 1200, 2), // "en"
QT_MOC_LITERAL(103, 1203, 7), // "getMode"
QT_MOC_LITERAL(104, 1211, 12), // "setShowBrush"
QT_MOC_LITERAL(105, 1224, 5), // "onoff"
QT_MOC_LITERAL(106, 1230, 12), // "setShowLidar"
QT_MOC_LITERAL(107, 1243, 15), // "setShowLocation"
QT_MOC_LITERAL(108, 1259, 17), // "setRobotFollowing"
QT_MOC_LITERAL(109, 1277, 17), // "setShowTravelline"
QT_MOC_LITERAL(110, 1295, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(111, 1314, 13), // "setShowObject"
QT_MOC_LITERAL(112, 1328, 11), // "setInitFlag"
QT_MOC_LITERAL(113, 1340, 15), // "getshowLocation"
QT_MOC_LITERAL(114, 1356, 17), // "getRobotFollowing"
QT_MOC_LITERAL(115, 1374, 12), // "getShowLidar"
QT_MOC_LITERAL(116, 1387, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(117, 1403, 11), // "setInitPose"
QT_MOC_LITERAL(118, 1415, 1), // "x"
QT_MOC_LITERAL(119, 1417, 1), // "y"
QT_MOC_LITERAL(120, 1419, 2), // "th"
QT_MOC_LITERAL(121, 1422, 13), // "clearInitPose"
QT_MOC_LITERAL(122, 1436, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(123, 1457, 17), // "startDrawingTline"
QT_MOC_LITERAL(124, 1475, 16), // "stopDrawingTline"
QT_MOC_LITERAL(125, 1492, 15), // "getDrawingTline"
QT_MOC_LITERAL(126, 1508, 11), // "setBoxPoint"
QT_MOC_LITERAL(127, 1520, 11), // "getPointBox"
QT_MOC_LITERAL(128, 1532, 13), // "saveRotateMap"
QT_MOC_LITERAL(129, 1546, 10), // "initRotate"
QT_MOC_LITERAL(130, 1557, 9), // "rotateMap"
QT_MOC_LITERAL(131, 1567, 5), // "angle"
QT_MOC_LITERAL(132, 1573, 11), // "rotateMapCW"
QT_MOC_LITERAL(133, 1585, 12), // "rotateMapCCW"
QT_MOC_LITERAL(134, 1598, 13), // "saveObjectPNG"
QT_MOC_LITERAL(135, 1612, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(136, 1627, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(137, 1650, 14), // "getDrawingFlag"
QT_MOC_LITERAL(138, 1665, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(139, 1684, 12), // "startDrawing"
QT_MOC_LITERAL(140, 1697, 12), // "addLinePoint"
QT_MOC_LITERAL(141, 1710, 10), // "endDrawing"
QT_MOC_LITERAL(142, 1721, 10), // "setMapOrin"
QT_MOC_LITERAL(143, 1732, 16), // "startDrawingRect"
QT_MOC_LITERAL(144, 1749, 14), // "setDrawingRect"
QT_MOC_LITERAL(145, 1764, 14), // "endDrawingRect"
QT_MOC_LITERAL(146, 1779, 12), // "clearDrawing"
QT_MOC_LITERAL(147, 1792, 8), // "undoLine"
QT_MOC_LITERAL(148, 1801, 8), // "redoLine"
QT_MOC_LITERAL(149, 1810, 11), // "startSpline"
QT_MOC_LITERAL(150, 1822, 9), // "addSpline"
QT_MOC_LITERAL(151, 1832, 10), // "drawSpline"
QT_MOC_LITERAL(152, 1843, 9), // "endSpline"
QT_MOC_LITERAL(153, 1853, 4), // "save"
QT_MOC_LITERAL(154, 1858, 16), // "startDrawingLine"
QT_MOC_LITERAL(155, 1875, 14), // "setDrawingLine"
QT_MOC_LITERAL(156, 1890, 15), // "stopDrawingLine"
QT_MOC_LITERAL(157, 1906, 12), // "setLineColor"
QT_MOC_LITERAL(158, 1919, 5), // "color"
QT_MOC_LITERAL(159, 1925, 12), // "setLineWidth"
QT_MOC_LITERAL(160, 1938, 5), // "width"
QT_MOC_LITERAL(161, 1944, 14), // "getLocationNum"
QT_MOC_LITERAL(162, 1959, 12), // "saveLocation"
QT_MOC_LITERAL(163, 1972, 8), // "groupnum"
QT_MOC_LITERAL(164, 1981, 13), // "clearLocation"
QT_MOC_LITERAL(165, 1995, 11), // "addLocation"
QT_MOC_LITERAL(166, 2007, 14), // "addLocationCur"
QT_MOC_LITERAL(167, 2022, 11), // "setLocation"
QT_MOC_LITERAL(168, 2034, 12), // "editLocation"
QT_MOC_LITERAL(169, 2047, 14), // "removeLocation"
QT_MOC_LITERAL(170, 2062, 20), // "getLocationAvailable"
QT_MOC_LITERAL(171, 2083, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(172, 2102, 14), // "getLocGroupNum"
QT_MOC_LITERAL(173, 2117, 7), // "saveMap"
QT_MOC_LITERAL(174, 2125, 13), // "saveEditedMap"
QT_MOC_LITERAL(175, 2139, 9), // "saveTline"
QT_MOC_LITERAL(176, 2149, 13), // "saveTlineTemp"
QT_MOC_LITERAL(177, 2163, 10), // "saveVelmap"
QT_MOC_LITERAL(178, 2174, 10), // "setMapSize"
QT_MOC_LITERAL(179, 2185, 6), // "height"
QT_MOC_LITERAL(180, 2192, 6), // "zoomIn"
QT_MOC_LITERAL(181, 2199, 4), // "dist"
QT_MOC_LITERAL(182, 2204, 7), // "zoomOut"
QT_MOC_LITERAL(183, 2212, 4), // "move"
QT_MOC_LITERAL(184, 2217, 12), // "getFileWidth"
QT_MOC_LITERAL(185, 2230, 4), // "getX"
QT_MOC_LITERAL(186, 2235, 4), // "getY"
QT_MOC_LITERAL(187, 2240, 8), // "getScale"
QT_MOC_LITERAL(188, 2249, 13), // "setVelmapView"
QT_MOC_LITERAL(189, 2263, 12), // "setTlineView"
QT_MOC_LITERAL(190, 2276, 13), // "setObjectView"
QT_MOC_LITERAL(191, 2290, 15), // "setAvoidmapView"
QT_MOC_LITERAL(192, 2306, 15), // "setLocationView"
QT_MOC_LITERAL(193, 2322, 12), // "setRobotView"
QT_MOC_LITERAL(194, 2335, 15), // "setSystemVolume"
QT_MOC_LITERAL(195, 2351, 19), // "requestSystemVolume"
QT_MOC_LITERAL(196, 2371, 7), // "setSize"
QT_MOC_LITERAL(197, 2379, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(198, 2393, 14), // "selectLocation"
QT_MOC_LITERAL(199, 2408, 8), // "writelog"
QT_MOC_LITERAL(200, 2417, 3), // "msg"
QT_MOC_LITERAL(201, 2421, 18), // "startDrawingObject"
QT_MOC_LITERAL(202, 2440, 17), // "stopDrawingObject"
QT_MOC_LITERAL(203, 2458, 17), // "saveDrawingObject"
QT_MOC_LITERAL(204, 2476, 13), // "setLocationUp"
QT_MOC_LITERAL(205, 2490, 15), // "setLocationDown"
QT_MOC_LITERAL(206, 2506, 8), // "checkINI"
QT_MOC_LITERAL(207, 2515, 8), // "killSLAM"
QT_MOC_LITERAL(208, 2524, 12), // "makeRobotINI"
QT_MOC_LITERAL(209, 2537, 13), // "checkRobotINI"
QT_MOC_LITERAL(210, 2551, 11), // "restartSLAM"
QT_MOC_LITERAL(211, 2563, 9), // "startSLAM"
QT_MOC_LITERAL(212, 2573, 16), // "getIPCConnection"
QT_MOC_LITERAL(213, 2590, 8), // "getIPCRX"
QT_MOC_LITERAL(214, 2599, 8), // "getIPCTX"
QT_MOC_LITERAL(215, 2608, 14), // "programRestart"
QT_MOC_LITERAL(216, 2623, 11), // "programExit"
QT_MOC_LITERAL(217, 2635, 13), // "getRawMapPath"
QT_MOC_LITERAL(218, 2649, 10), // "getMapPath"
QT_MOC_LITERAL(219, 2660, 12), // "getAnnotPath"
QT_MOC_LITERAL(220, 2673, 11), // "getMetaPath"
QT_MOC_LITERAL(221, 2685, 13), // "getTravelPath"
QT_MOC_LITERAL(222, 2699, 11), // "getCostPath"
QT_MOC_LITERAL(223, 2711, 10), // "getIniPath"
QT_MOC_LITERAL(224, 2722, 4), // "file"
QT_MOC_LITERAL(225, 2727, 10), // "setSetting"
QT_MOC_LITERAL(226, 2738, 5), // "value"
QT_MOC_LITERAL(227, 2744, 11), // "readSetting"
QT_MOC_LITERAL(228, 2756, 8), // "map_name"
QT_MOC_LITERAL(229, 2765, 10), // "getSetting"
QT_MOC_LITERAL(230, 2776, 10), // "getTrayNum"
QT_MOC_LITERAL(231, 2787, 14), // "setTableColNum"
QT_MOC_LITERAL(232, 2802, 7), // "col_num"
QT_MOC_LITERAL(233, 2810, 12), // "getRobotType"
QT_MOC_LITERAL(234, 2823, 13), // "requestCamera"
QT_MOC_LITERAL(235, 2837, 13), // "getLeftCamera"
QT_MOC_LITERAL(236, 2851, 14), // "getRightCamera"
QT_MOC_LITERAL(237, 2866, 9), // "setCamera"
QT_MOC_LITERAL(238, 2876, 4), // "left"
QT_MOC_LITERAL(239, 2881, 5), // "right"
QT_MOC_LITERAL(240, 2887, 12), // "getCameraNum"
QT_MOC_LITERAL(241, 2900, 15), // "getCameraSerial"
QT_MOC_LITERAL(242, 2916, 13), // "setCursorView"
QT_MOC_LITERAL(243, 2930, 7), // "visible"
QT_MOC_LITERAL(244, 2938, 8), // "getVoice"
QT_MOC_LITERAL(245, 2947, 15), // "checkTravelline"
QT_MOC_LITERAL(246, 2963, 13), // "updateProgram"
QT_MOC_LITERAL(247, 2977, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(248, 2998, 17), // "checkVersionAgain"
QT_MOC_LITERAL(249, 3016, 12), // "isNewVersion"
QT_MOC_LITERAL(250, 3029, 12), // "isNeedUpdate"
QT_MOC_LITERAL(251, 3042, 15), // "getLocalVersion"
QT_MOC_LITERAL(252, 3058, 16), // "getServerVersion"
QT_MOC_LITERAL(253, 3075, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(254, 3095, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(255, 3118, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(256, 3142, 13), // "getUpdateDate"
QT_MOC_LITERAL(257, 3156, 13), // "getUpdateSize"
QT_MOC_LITERAL(258, 3170, 17), // "getUpdateFileName"
QT_MOC_LITERAL(259, 3188, 15), // "getUpdateCommit"
QT_MOC_LITERAL(260, 3204, 16), // "getCurrentCommit"
QT_MOC_LITERAL(261, 3221, 16), // "getUpdateMessage"
QT_MOC_LITERAL(262, 3238, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(263, 3256, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(264, 3278, 11), // "checkUpdate"
QT_MOC_LITERAL(265, 3290, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(266, 3312, 11), // "setlanguage"
QT_MOC_LITERAL(267, 3324, 3), // "lan"
QT_MOC_LITERAL(268, 3328, 13), // "isCallingMode"
QT_MOC_LITERAL(269, 3342, 9), // "goServing"
QT_MOC_LITERAL(270, 3352, 5), // "table"
QT_MOC_LITERAL(271, 3358, 17), // "getLocationbyCall"
QT_MOC_LITERAL(272, 3376, 8), // "LOCATION"
QT_MOC_LITERAL(273, 3385, 4), // "call"
QT_MOC_LITERAL(274, 3390, 11), // "getLocation"
QT_MOC_LITERAL(275, 3402, 15), // "getLocationbyID"
QT_MOC_LITERAL(276, 3418, 2), // "id"
QT_MOC_LITERAL(277, 3421, 10), // "setUiState"
QT_MOC_LITERAL(278, 3432, 5), // "state"
QT_MOC_LITERAL(279, 3438, 17), // "resetLocalization"
QT_MOC_LITERAL(280, 3456, 6), // "setLog"
QT_MOC_LITERAL(281, 3463, 13), // "getLogLineNum"
QT_MOC_LITERAL(282, 3477, 10), // "getLogLine"
QT_MOC_LITERAL(283, 3488, 10), // "getLogDate"
QT_MOC_LITERAL(284, 3499, 10), // "getLogAuth"
QT_MOC_LITERAL(285, 3510, 13), // "getLogMessage"
QT_MOC_LITERAL(286, 3524, 7), // "readLog"
QT_MOC_LITERAL(287, 3532, 4), // "date"
QT_MOC_LITERAL(288, 3537, 13), // "getLocaleDate"
QT_MOC_LITERAL(289, 3551, 4), // "year"
QT_MOC_LITERAL(290, 3556, 5), // "month"
QT_MOC_LITERAL(291, 3562, 9), // "updateUSB"
QT_MOC_LITERAL(292, 3572, 10), // "getusbsize"
QT_MOC_LITERAL(293, 3583, 17), // "readusbrecentfile"
QT_MOC_LITERAL(294, 3601, 14), // "getusbfilesize"
QT_MOC_LITERAL(295, 3616, 10), // "getusbfile"
QT_MOC_LITERAL(296, 3627, 16), // "getusbrecentfile"
QT_MOC_LITERAL(297, 3644, 10), // "getusbname"
QT_MOC_LITERAL(298, 3655, 7), // "readusb"
QT_MOC_LITERAL(299, 3663, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(300, 3678, 4), // "path"
QT_MOC_LITERAL(301, 3683, 15), // "isConnectServer"
QT_MOC_LITERAL(302, 3699, 9), // "isLoadMap"
QT_MOC_LITERAL(303, 3709, 10), // "isExistMap"
QT_MOC_LITERAL(304, 3720, 13), // "isExistRawMap"
QT_MOC_LITERAL(305, 3734, 15), // "isExistTlineMap"
QT_MOC_LITERAL(306, 3750, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(307, 3766, 13), // "isExistVelMap"
QT_MOC_LITERAL(308, 3780, 16), // "isExistObjectMap"
QT_MOC_LITERAL(309, 3797, 16), // "isExistTravelMap"
QT_MOC_LITERAL(310, 3814, 17), // "isExistAnnotation"
QT_MOC_LITERAL(311, 3832, 15), // "isExistRobotINI"
QT_MOC_LITERAL(312, 3848, 15), // "getAvailableMap"
QT_MOC_LITERAL(313, 3864, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(314, 3884, 14), // "getMapFileSize"
QT_MOC_LITERAL(315, 3899, 10), // "getMapFile"
QT_MOC_LITERAL(316, 3910, 15), // "deleteEditedMap"
QT_MOC_LITERAL(317, 3926, 16), // "deleteAnnotation"
QT_MOC_LITERAL(318, 3943, 9), // "removeMap"
QT_MOC_LITERAL(319, 3953, 8), // "filename"
QT_MOC_LITERAL(320, 3962, 7), // "loadMap"
QT_MOC_LITERAL(321, 3970, 7), // "copyMap"
QT_MOC_LITERAL(322, 3978, 8), // "orinname"
QT_MOC_LITERAL(323, 3987, 7), // "newname"
QT_MOC_LITERAL(324, 3995, 10), // "rotate_map"
QT_MOC_LITERAL(325, 4006, 4), // "_src"
QT_MOC_LITERAL(326, 4011, 4), // "_dst"
QT_MOC_LITERAL(327, 4016, 12), // "startMapping"
QT_MOC_LITERAL(328, 4029, 7), // "mapsize"
QT_MOC_LITERAL(329, 4037, 4), // "grid"
QT_MOC_LITERAL(330, 4042, 11), // "stopMapping"
QT_MOC_LITERAL(331, 4054, 11), // "setSLAMMode"
QT_MOC_LITERAL(332, 4066, 11), // "saveMapping"
QT_MOC_LITERAL(333, 4078, 13), // "setInitCurPos"
QT_MOC_LITERAL(334, 4092, 10), // "setInitPos"
QT_MOC_LITERAL(335, 4103, 12), // "getInitPoseX"
QT_MOC_LITERAL(336, 4116, 12), // "getInitPoseY"
QT_MOC_LITERAL(337, 4129, 13), // "getInitPoseTH"
QT_MOC_LITERAL(338, 4143, 12), // "slam_setInit"
QT_MOC_LITERAL(339, 4156, 8), // "slam_run"
QT_MOC_LITERAL(340, 4165, 9), // "slam_stop"
QT_MOC_LITERAL(341, 4175, 13), // "slam_autoInit"
QT_MOC_LITERAL(342, 4189, 15), // "is_slam_running"
QT_MOC_LITERAL(343, 4205, 14), // "getMappingflag"
QT_MOC_LITERAL(344, 4220, 16), // "getObjectingflag"
QT_MOC_LITERAL(345, 4237, 16), // "setObjectingflag"
QT_MOC_LITERAL(346, 4254, 4), // "flag"
QT_MOC_LITERAL(347, 4259, 13), // "getnewMapname"
QT_MOC_LITERAL(348, 4273, 11), // "getLastCall"
QT_MOC_LITERAL(349, 4285, 11), // "getCallSize"
QT_MOC_LITERAL(350, 4297, 16), // "getCallQueueSize"
QT_MOC_LITERAL(351, 4314, 9), // "cleanTray"
QT_MOC_LITERAL(352, 4324, 11), // "getCallName"
QT_MOC_LITERAL(353, 4336, 14), // "clearCallQueue"
QT_MOC_LITERAL(354, 4351, 7), // "getCall"
QT_MOC_LITERAL(355, 4359, 15), // "getCallLocation"
QT_MOC_LITERAL(356, 4375, 11), // "setCallbell"
QT_MOC_LITERAL(357, 4387, 16), // "setCallbellForce"
QT_MOC_LITERAL(358, 4404, 10), // "acceptCall"
QT_MOC_LITERAL(359, 4415, 3), // "yes"
QT_MOC_LITERAL(360, 4419, 10), // "setObjPose"
QT_MOC_LITERAL(361, 4430, 14), // "getServingName"
QT_MOC_LITERAL(362, 4445, 15), // "getLocationName"
QT_MOC_LITERAL(363, 4461, 15), // "getLocationType"
QT_MOC_LITERAL(364, 4477, 17), // "getLocationNumber"
QT_MOC_LITERAL(365, 4495, 17), // "setLocationNumber"
QT_MOC_LITERAL(366, 4513, 15), // "getLocationSize"
QT_MOC_LITERAL(367, 4529, 16), // "getLocationGroup"
QT_MOC_LITERAL(368, 4546, 13), // "getLocationID"
QT_MOC_LITERAL(369, 4560, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(370, 4580, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(371, 4601, 17), // "getLocationCallID"
QT_MOC_LITERAL(372, 4619, 16), // "setLocationGroup"
QT_MOC_LITERAL(373, 4636, 19), // "removeLocationGroup"
QT_MOC_LITERAL(374, 4656, 16), // "addLocationGroup"
QT_MOC_LITERAL(375, 4673, 15), // "getLocGroupname"
QT_MOC_LITERAL(376, 4689, 8), // "tablenum"
QT_MOC_LITERAL(377, 4698, 12), // "getLocationX"
QT_MOC_LITERAL(378, 4711, 12), // "getLocationY"
QT_MOC_LITERAL(379, 4724, 13), // "getLocationTH"
QT_MOC_LITERAL(380, 4738, 15), // "isExistLocation"
QT_MOC_LITERAL(381, 4754, 8), // "getLidar"
QT_MOC_LITERAL(382, 4763, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(383, 4780, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(384, 4797, 17), // "clearSharedMemory"
QT_MOC_LITERAL(385, 4815, 12), // "getObjectNum"
QT_MOC_LITERAL(386, 4828, 13), // "getObjectName"
QT_MOC_LITERAL(387, 4842, 18), // "getObjectPointSize"
QT_MOC_LITERAL(388, 4861, 10), // "getObjectX"
QT_MOC_LITERAL(389, 4872, 5), // "point"
QT_MOC_LITERAL(390, 4878, 10), // "getObjectY"
QT_MOC_LITERAL(391, 4889, 14), // "getObjPointNum"
QT_MOC_LITERAL(392, 4904, 7), // "obj_num"
QT_MOC_LITERAL(393, 4912, 9), // "getLocNum"
QT_MOC_LITERAL(394, 4922, 13), // "saveLocations"
QT_MOC_LITERAL(395, 4936, 13), // "getObjectSize"
QT_MOC_LITERAL(396, 4950, 12), // "removeObject"
QT_MOC_LITERAL(397, 4963, 14), // "saveAnnotation"
QT_MOC_LITERAL(398, 4978, 8), // "isOdroid"
QT_MOC_LITERAL(399, 4987, 13), // "getMultiState"
QT_MOC_LITERAL(400, 5001, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(401, 5021, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(402, 5040, 15), // "getRunawayState"
QT_MOC_LITERAL(403, 5056, 15), // "slam_map_reload"
QT_MOC_LITERAL(404, 5072, 15), // "slam_ini_reload"
QT_MOC_LITERAL(405, 5088, 7), // "setTray"
QT_MOC_LITERAL(406, 5096, 8), // "tray_num"
QT_MOC_LITERAL(407, 5105, 12), // "startServing"
QT_MOC_LITERAL(408, 5118, 9), // "setPreset"
QT_MOC_LITERAL(409, 5128, 6), // "preset"
QT_MOC_LITERAL(410, 5135, 13), // "confirmPickup"
QT_MOC_LITERAL(411, 5149, 14), // "getPickuptrays"
QT_MOC_LITERAL(412, 5164, 10), // "QList<int>"
QT_MOC_LITERAL(413, 5175, 9), // "movePause"
QT_MOC_LITERAL(414, 5185, 10), // "moveResume"
QT_MOC_LITERAL(415, 5196, 12), // "moveStopFlag"
QT_MOC_LITERAL(416, 5209, 8), // "moveStop"
QT_MOC_LITERAL(417, 5218, 12), // "moveToCharge"
QT_MOC_LITERAL(418, 5231, 10), // "moveToWait"
QT_MOC_LITERAL(419, 5242, 14), // "moveToCleaning"
QT_MOC_LITERAL(420, 5257, 9), // "getcurLoc"
QT_MOC_LITERAL(421, 5267, 11), // "getcurTable"
QT_MOC_LITERAL(422, 5279, 16), // "resetHomeFolders"
QT_MOC_LITERAL(423, 5296, 13), // "issetLocation"
QT_MOC_LITERAL(424, 5310, 6), // "number"
QT_MOC_LITERAL(425, 5317, 11), // "getObsState"
QT_MOC_LITERAL(426, 5329, 10), // "getBattery"
QT_MOC_LITERAL(427, 5340, 13), // "getMotorState"
QT_MOC_LITERAL(428, 5354, 20), // "getLocalizationState"
QT_MOC_LITERAL(429, 5375, 14), // "getStateMoving"
QT_MOC_LITERAL(430, 5390, 10), // "getErrcode"
QT_MOC_LITERAL(431, 5401, 12), // "getRobotName"
QT_MOC_LITERAL(432, 5414, 18), // "getMotorConnection"
QT_MOC_LITERAL(433, 5433, 14), // "getMotorStatus"
QT_MOC_LITERAL(434, 5448, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(435, 5466, 19), // "getMotorTemperature"
QT_MOC_LITERAL(436, 5486, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(437, 5512, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(438, 5539, 15), // "getMotorCurrent"
QT_MOC_LITERAL(439, 5555, 14), // "getPowerStatus"
QT_MOC_LITERAL(440, 5570, 15), // "getRemoteStatus"
QT_MOC_LITERAL(441, 5586, 15), // "getChargeStatus"
QT_MOC_LITERAL(442, 5602, 12), // "getEmoStatus"
QT_MOC_LITERAL(443, 5615, 13), // "getLockStatus"
QT_MOC_LITERAL(444, 5629, 12), // "getBatteryIn"
QT_MOC_LITERAL(445, 5642, 13), // "getBatteryOut"
QT_MOC_LITERAL(446, 5656, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(447, 5674, 8), // "getPower"
QT_MOC_LITERAL(448, 5683, 13), // "getPowerTotal"
QT_MOC_LITERAL(449, 5697, 12), // "getObsinPath"
QT_MOC_LITERAL(450, 5710, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(451, 5728, 12), // "setMotorLock"
QT_MOC_LITERAL(452, 5741, 14), // "getRobotRadius"
QT_MOC_LITERAL(453, 5756, 9), // "getRobotx"
QT_MOC_LITERAL(454, 5766, 9), // "getRoboty"
QT_MOC_LITERAL(455, 5776, 10), // "getRobotth"
QT_MOC_LITERAL(456, 5787, 13), // "getlastRobotx"
QT_MOC_LITERAL(457, 5801, 13), // "getlastRoboty"
QT_MOC_LITERAL(458, 5815, 14), // "getlastRobotth"
QT_MOC_LITERAL(459, 5830, 10), // "getPathNum"
QT_MOC_LITERAL(460, 5841, 8), // "getPathx"
QT_MOC_LITERAL(461, 5850, 8), // "getPathy"
QT_MOC_LITERAL(462, 5859, 9), // "getPathth"
QT_MOC_LITERAL(463, 5869, 15), // "getLocalPathNum"
QT_MOC_LITERAL(464, 5885, 13), // "getLocalPathx"
QT_MOC_LITERAL(465, 5899, 13), // "getLocalPathy"
QT_MOC_LITERAL(466, 5913, 10), // "getuistate"
QT_MOC_LITERAL(467, 5924, 10), // "getMapname"
QT_MOC_LITERAL(468, 5935, 10), // "getMappath"
QT_MOC_LITERAL(469, 5946, 11), // "getMapWidth"
QT_MOC_LITERAL(470, 5958, 12), // "getMapHeight"
QT_MOC_LITERAL(471, 5971, 12), // "getGridWidth"
QT_MOC_LITERAL(472, 5984, 9), // "getOrigin"
QT_MOC_LITERAL(473, 5994, 15), // "getMappingWidth"
QT_MOC_LITERAL(474, 6010, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(475, 6030, 15), // "startDrawObject"
QT_MOC_LITERAL(476, 6046, 14), // "stopDrawObject"
QT_MOC_LITERAL(477, 6061, 14), // "saveDrawObject"
QT_MOC_LITERAL(478, 6076, 17), // "getObjectPointNum"
QT_MOC_LITERAL(479, 6094, 9), // "addObject"
QT_MOC_LITERAL(480, 6104, 14), // "addObjectPoint"
QT_MOC_LITERAL(481, 6119, 9), // "setObject"
QT_MOC_LITERAL(482, 6129, 15), // "editObjectStart"
QT_MOC_LITERAL(483, 6145, 10), // "editObject"
QT_MOC_LITERAL(484, 6156, 10), // "saveObject"
QT_MOC_LITERAL(485, 6167, 11), // "clearObject"
QT_MOC_LITERAL(486, 6179, 14), // "clearObjectAll"
QT_MOC_LITERAL(487, 6194, 12), // "selectObject"
QT_MOC_LITERAL(488, 6207, 13), // "getObjectflag"
QT_MOC_LITERAL(489, 6221, 10), // "undoObject"
QT_MOC_LITERAL(490, 6232, 15), // "clearRotateList"
QT_MOC_LITERAL(491, 6248, 13), // "setRotateList"
QT_MOC_LITERAL(492, 6262, 6), // "pickup"
QT_MOC_LITERAL(493, 6269, 11), // "getICPRatio"
QT_MOC_LITERAL(494, 6281, 11), // "getICPError"
QT_MOC_LITERAL(495, 6293, 13), // "clearFlagStop"
QT_MOC_LITERAL(496, 6307, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(497, 6325, 17), // "moveToServingTest"
QT_MOC_LITERAL(498, 6343, 15), // "getusberrorsize"
QT_MOC_LITERAL(499, 6359, 11), // "getusberror"
QT_MOC_LITERAL(500, 6371, 11), // "getzipstate"
QT_MOC_LITERAL(501, 6383, 10), // "clear_call"
QT_MOC_LITERAL(502, 6394, 7), // "usbsave"
QT_MOC_LITERAL(503, 6402, 3), // "usb"
QT_MOC_LITERAL(504, 6406, 3), // "_ui"
QT_MOC_LITERAL(505, 6410, 5), // "_slam"
QT_MOC_LITERAL(506, 6416, 7), // "_config"
QT_MOC_LITERAL(507, 6424, 4), // "_map"
QT_MOC_LITERAL(508, 6429, 4), // "_log"
QT_MOC_LITERAL(509, 6434, 13), // "restartUpdate"
QT_MOC_LITERAL(510, 6448, 11), // "startUpdate"
QT_MOC_LITERAL(511, 6460, 18), // "getTravellineIssue"
QT_MOC_LITERAL(512, 6479, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(513, 6503, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(514, 6526, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(515, 6548, 24) // "getTravellineIssueBroken"

    },
    "Supervisor\0onTimer\0\0path_changed\0"
    "camera_update\0mapping_update\0usb_detect\0"
    "git_pull_failed\0git_pull_success\0"
    "new_call\0process_accept\0cmd\0process_done\0"
    "process_error\0param\0process_timeout\0"
    "update_success\0update_fail\0clear_all\0"
    "map_reset\0new_call_order\0name\0"
    "loadMapServer\0sendMapServer\0"
    "checkLocationName\0group\0resetClear\0"
    "getWifiNum\0getWifiConnection\0ssid\0"
    "getCurWifiSSID\0getWifiSSID\0num\0"
    "connectWifi\0passwd\0getWifiSecurity\0"
    "getWifiLevel\0getWifiRate\0getWifiInuse\0"
    "getAllWifiList\0getWifiIP\0setWifi\0ip\0"
    "gateway\0dns\0getcurIP\0getcurGateway\0"
    "getcurDNS\0readWifiState\0setWifiSSD\0"
    "getSystemVolume\0passInit\0readPatrol\0"
    "getPatrolSize\0getPatrolName\0getPatrolType\0"
    "getPatrolLocation\0getPatrolMovingPage\0"
    "getPatrolArrivePage\0getPatrolWaitTime\0"
    "getPatrolVoice\0getPatrolVoiceMode\0"
    "isPatrolPage\0getPatrolMovingMode\0"
    "getPatrolArriveMode\0setCurrentPatrol\0"
    "getPatrolLocationSize\0loc\0clearPatrolLocation\0"
    "mode\0addPatrolLocation\0setPatrolMovingPage\0"
    "param1\0param2\0param3\0setPatrolArrivePage\0"
    "setPatrolVoice\0text\0setPatrol\0type\0"
    "wait_time\0savePatrol\0deletePatrol\0"
    "startPatrol\0loadFile\0setMap\0moveMap\0"
    "setFullScreen\0setMapDrawing\0clicksound\0"
    "volume\0playBGM\0stopBGM\0isplayBGM\0"
    "playVoice\0voice\0confirmLocalization\0"
    "setName\0setTool\0getTool\0setMode\0"
    "setEnable\0en\0getMode\0setShowBrush\0"
    "onoff\0setShowLidar\0setShowLocation\0"
    "setRobotFollowing\0setShowTravelline\0"
    "setShowVelocitymap\0setShowObject\0"
    "setInitFlag\0getshowLocation\0"
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
    "setlanguage\0lan\0isCallingMode\0goServing\0"
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
    "setRotateList\0pickup\0getICPRatio\0"
    "getICPError\0clearFlagStop\0slam_fullautoInit\0"
    "moveToServingTest\0getusberrorsize\0"
    "getusberror\0getzipstate\0clear_call\0"
    "usbsave\0usb\0_ui\0_slam\0_config\0_map\0"
    "_log\0restartUpdate\0startUpdate\0"
    "getTravellineIssue\0getTravellineIssueGroup\0"
    "getTravellineIssueName\0getTravellineIssueFar\0"
    "getTravellineIssueBroken"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Supervisor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
     482,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 2424,    2, 0x0a /* Public */,
       3,    0, 2425,    2, 0x0a /* Public */,
       4,    0, 2426,    2, 0x0a /* Public */,
       5,    0, 2427,    2, 0x0a /* Public */,
       6,    0, 2428,    2, 0x0a /* Public */,
       7,    0, 2429,    2, 0x0a /* Public */,
       8,    0, 2430,    2, 0x0a /* Public */,
       9,    0, 2431,    2, 0x0a /* Public */,
      10,    1, 2432,    2, 0x0a /* Public */,
      12,    1, 2435,    2, 0x0a /* Public */,
      13,    2, 2438,    2, 0x0a /* Public */,
      15,    1, 2443,    2, 0x0a /* Public */,
      16,    0, 2446,    2, 0x0a /* Public */,
      17,    0, 2447,    2, 0x0a /* Public */,
      18,    0, 2448,    2, 0x0a /* Public */,
      19,    0, 2449,    2, 0x0a /* Public */,
      20,    1, 2450,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      22,    0, 2453,    2, 0x02 /* Public */,
      23,    0, 2454,    2, 0x02 /* Public */,
      24,    2, 2455,    2, 0x02 /* Public */,
      26,    0, 2460,    2, 0x02 /* Public */,
      27,    0, 2461,    2, 0x02 /* Public */,
      28,    1, 2462,    2, 0x02 /* Public */,
      30,    0, 2465,    2, 0x02 /* Public */,
      31,    1, 2466,    2, 0x02 /* Public */,
      33,    2, 2469,    2, 0x02 /* Public */,
      35,    1, 2474,    2, 0x02 /* Public */,
      36,    1, 2477,    2, 0x02 /* Public */,
      37,    1, 2480,    2, 0x02 /* Public */,
      38,    1, 2483,    2, 0x02 /* Public */,
      39,    0, 2486,    2, 0x02 /* Public */,
      40,    0, 2487,    2, 0x02 /* Public */,
      41,    3, 2488,    2, 0x02 /* Public */,
      45,    0, 2495,    2, 0x02 /* Public */,
      46,    0, 2496,    2, 0x02 /* Public */,
      47,    0, 2497,    2, 0x02 /* Public */,
      48,    1, 2498,    2, 0x02 /* Public */,
      49,    1, 2501,    2, 0x02 /* Public */,
      50,    0, 2504,    2, 0x02 /* Public */,
      51,    0, 2505,    2, 0x02 /* Public */,
      52,    0, 2506,    2, 0x02 /* Public */,
      53,    0, 2507,    2, 0x02 /* Public */,
      54,    1, 2508,    2, 0x02 /* Public */,
      55,    1, 2511,    2, 0x02 /* Public */,
      56,    1, 2514,    2, 0x02 /* Public */,
      57,    1, 2517,    2, 0x02 /* Public */,
      58,    1, 2520,    2, 0x02 /* Public */,
      59,    1, 2523,    2, 0x02 /* Public */,
      60,    1, 2526,    2, 0x02 /* Public */,
      61,    1, 2529,    2, 0x02 /* Public */,
      62,    0, 2532,    2, 0x02 /* Public */,
      63,    0, 2533,    2, 0x02 /* Public */,
      64,    0, 2534,    2, 0x02 /* Public */,
      65,    1, 2535,    2, 0x02 /* Public */,
      66,    1, 2538,    2, 0x02 /* Public */,
      56,    2, 2541,    2, 0x02 /* Public */,
      68,    1, 2546,    2, 0x02 /* Public */,
      70,    1, 2549,    2, 0x02 /* Public */,
      71,    4, 2552,    2, 0x02 /* Public */,
      71,    3, 2561,    2, 0x22 /* Public | MethodCloned */,
      71,    2, 2568,    2, 0x22 /* Public | MethodCloned */,
      71,    1, 2573,    2, 0x22 /* Public | MethodCloned */,
      75,    4, 2576,    2, 0x02 /* Public */,
      75,    3, 2585,    2, 0x22 /* Public | MethodCloned */,
      75,    2, 2592,    2, 0x22 /* Public | MethodCloned */,
      75,    1, 2597,    2, 0x22 /* Public | MethodCloned */,
      76,    4, 2600,    2, 0x02 /* Public */,
      76,    3, 2609,    2, 0x22 /* Public | MethodCloned */,
      76,    2, 2616,    2, 0x22 /* Public | MethodCloned */,
      76,    1, 2621,    2, 0x22 /* Public | MethodCloned */,
      78,    4, 2624,    2, 0x02 /* Public */,
      81,    3, 2633,    2, 0x02 /* Public */,
      82,    1, 2640,    2, 0x02 /* Public */,
      83,    1, 2643,    2, 0x02 /* Public */,
      84,    2, 2646,    2, 0x02 /* Public */,
      85,    0, 2651,    2, 0x02 /* Public */,
      86,    0, 2652,    2, 0x02 /* Public */,
      87,    0, 2653,    2, 0x02 /* Public */,
      88,    0, 2654,    2, 0x02 /* Public */,
      89,    2, 2655,    2, 0x02 /* Public */,
      89,    1, 2660,    2, 0x22 /* Public | MethodCloned */,
      91,    1, 2663,    2, 0x02 /* Public */,
      91,    0, 2666,    2, 0x22 /* Public | MethodCloned */,
      92,    0, 2667,    2, 0x02 /* Public */,
      93,    0, 2668,    2, 0x02 /* Public */,
      94,    2, 2669,    2, 0x02 /* Public */,
      94,    1, 2674,    2, 0x22 /* Public | MethodCloned */,
      96,    0, 2677,    2, 0x02 /* Public */,
      97,    1, 2678,    2, 0x02 /* Public */,
      98,    1, 2681,    2, 0x02 /* Public */,
      99,    0, 2684,    2, 0x02 /* Public */,
     100,    1, 2685,    2, 0x02 /* Public */,
     101,    1, 2688,    2, 0x02 /* Public */,
     103,    0, 2691,    2, 0x02 /* Public */,
     104,    1, 2692,    2, 0x02 /* Public */,
     106,    1, 2695,    2, 0x02 /* Public */,
     107,    1, 2698,    2, 0x02 /* Public */,
     108,    1, 2701,    2, 0x02 /* Public */,
     109,    1, 2704,    2, 0x02 /* Public */,
     110,    1, 2707,    2, 0x02 /* Public */,
     111,    1, 2710,    2, 0x02 /* Public */,
     112,    1, 2713,    2, 0x02 /* Public */,
     113,    0, 2716,    2, 0x02 /* Public */,
     114,    0, 2717,    2, 0x02 /* Public */,
     115,    0, 2718,    2, 0x02 /* Public */,
     116,    1, 2719,    2, 0x02 /* Public */,
     117,    3, 2722,    2, 0x02 /* Public */,
     121,    0, 2729,    2, 0x02 /* Public */,
     122,    0, 2730,    2, 0x02 /* Public */,
     123,    0, 2731,    2, 0x02 /* Public */,
     124,    0, 2732,    2, 0x02 /* Public */,
     125,    0, 2733,    2, 0x02 /* Public */,
     126,    3, 2734,    2, 0x02 /* Public */,
     127,    2, 2741,    2, 0x02 /* Public */,
     128,    0, 2746,    2, 0x02 /* Public */,
     129,    0, 2747,    2, 0x02 /* Public */,
     130,    1, 2748,    2, 0x02 /* Public */,
     132,    0, 2751,    2, 0x02 /* Public */,
     133,    0, 2752,    2, 0x02 /* Public */,
     134,    0, 2753,    2, 0x02 /* Public */,
     135,    0, 2754,    2, 0x02 /* Public */,
     136,    0, 2755,    2, 0x02 /* Public */,
     137,    0, 2756,    2, 0x02 /* Public */,
     138,    0, 2757,    2, 0x02 /* Public */,
     139,    2, 2758,    2, 0x02 /* Public */,
     140,    2, 2763,    2, 0x02 /* Public */,
     141,    2, 2768,    2, 0x02 /* Public */,
     142,    1, 2773,    2, 0x02 /* Public */,
     143,    2, 2776,    2, 0x02 /* Public */,
     144,    2, 2781,    2, 0x02 /* Public */,
     145,    0, 2786,    2, 0x02 /* Public */,
     146,    0, 2787,    2, 0x02 /* Public */,
     147,    0, 2788,    2, 0x02 /* Public */,
     148,    0, 2789,    2, 0x02 /* Public */,
     149,    2, 2790,    2, 0x02 /* Public */,
     150,    2, 2795,    2, 0x02 /* Public */,
     151,    0, 2800,    2, 0x02 /* Public */,
     152,    1, 2801,    2, 0x02 /* Public */,
     154,    2, 2804,    2, 0x02 /* Public */,
     155,    2, 2809,    2, 0x02 /* Public */,
     156,    2, 2814,    2, 0x02 /* Public */,
     157,    1, 2819,    2, 0x02 /* Public */,
     159,    1, 2822,    2, 0x02 /* Public */,
     161,    2, 2825,    2, 0x02 /* Public */,
     162,    3, 2830,    2, 0x02 /* Public */,
     164,    0, 2837,    2, 0x02 /* Public */,
     165,    3, 2838,    2, 0x02 /* Public */,
     166,    3, 2845,    2, 0x02 /* Public */,
     167,    3, 2852,    2, 0x02 /* Public */,
     168,    1, 2859,    2, 0x02 /* Public */,
     161,    2, 2862,    2, 0x02 /* Public */,
     169,    1, 2867,    2, 0x02 /* Public */,
     170,    1, 2870,    2, 0x02 /* Public */,
     171,    0, 2873,    2, 0x02 /* Public */,
     172,    1, 2874,    2, 0x02 /* Public */,
     173,    0, 2877,    2, 0x02 /* Public */,
     174,    0, 2878,    2, 0x02 /* Public */,
     175,    0, 2879,    2, 0x02 /* Public */,
     176,    0, 2880,    2, 0x02 /* Public */,
     177,    0, 2881,    2, 0x02 /* Public */,
     178,    2, 2882,    2, 0x02 /* Public */,
     180,    3, 2887,    2, 0x02 /* Public */,
     182,    3, 2894,    2, 0x02 /* Public */,
     183,    2, 2901,    2, 0x02 /* Public */,
     184,    0, 2906,    2, 0x02 /* Public */,
     185,    0, 2907,    2, 0x02 /* Public */,
     186,    0, 2908,    2, 0x02 /* Public */,
     187,    0, 2909,    2, 0x02 /* Public */,
     188,    1, 2910,    2, 0x02 /* Public */,
     189,    1, 2913,    2, 0x02 /* Public */,
     190,    1, 2916,    2, 0x02 /* Public */,
     191,    1, 2919,    2, 0x02 /* Public */,
     192,    1, 2922,    2, 0x02 /* Public */,
     193,    1, 2925,    2, 0x02 /* Public */,
     194,    1, 2928,    2, 0x02 /* Public */,
     195,    0, 2931,    2, 0x02 /* Public */,
     196,    3, 2932,    2, 0x02 /* Public */,
     197,    0, 2939,    2, 0x02 /* Public */,
     198,    1, 2940,    2, 0x02 /* Public */,
     199,    1, 2943,    2, 0x02 /* Public */,
     201,    0, 2946,    2, 0x02 /* Public */,
     202,    0, 2947,    2, 0x02 /* Public */,
     203,    0, 2948,    2, 0x02 /* Public */,
     204,    1, 2949,    2, 0x02 /* Public */,
     205,    1, 2952,    2, 0x02 /* Public */,
     206,    0, 2955,    2, 0x02 /* Public */,
     207,    0, 2956,    2, 0x02 /* Public */,
     208,    0, 2957,    2, 0x02 /* Public */,
     209,    0, 2958,    2, 0x02 /* Public */,
     210,    0, 2959,    2, 0x02 /* Public */,
     211,    0, 2960,    2, 0x02 /* Public */,
     212,    0, 2961,    2, 0x02 /* Public */,
     213,    0, 2962,    2, 0x02 /* Public */,
     214,    0, 2963,    2, 0x02 /* Public */,
     215,    0, 2964,    2, 0x02 /* Public */,
     216,    0, 2965,    2, 0x02 /* Public */,
     217,    1, 2966,    2, 0x02 /* Public */,
     218,    1, 2969,    2, 0x02 /* Public */,
     219,    1, 2972,    2, 0x02 /* Public */,
     220,    1, 2975,    2, 0x02 /* Public */,
     221,    1, 2978,    2, 0x02 /* Public */,
     222,    1, 2981,    2, 0x02 /* Public */,
     223,    1, 2984,    2, 0x02 /* Public */,
     225,    3, 2987,    2, 0x02 /* Public */,
     227,    1, 2994,    2, 0x02 /* Public */,
     227,    0, 2997,    2, 0x22 /* Public | MethodCloned */,
     229,    3, 2998,    2, 0x02 /* Public */,
     230,    0, 3005,    2, 0x02 /* Public */,
     231,    1, 3006,    2, 0x02 /* Public */,
     233,    0, 3009,    2, 0x02 /* Public */,
     234,    0, 3010,    2, 0x02 /* Public */,
     235,    0, 3011,    2, 0x02 /* Public */,
     236,    0, 3012,    2, 0x02 /* Public */,
     237,    2, 3013,    2, 0x02 /* Public */,
     240,    0, 3018,    2, 0x02 /* Public */,
     241,    1, 3019,    2, 0x02 /* Public */,
     242,    1, 3022,    2, 0x02 /* Public */,
     244,    2, 3025,    2, 0x02 /* Public */,
     244,    1, 3030,    2, 0x22 /* Public | MethodCloned */,
     245,    0, 3033,    2, 0x02 /* Public */,
     246,    0, 3034,    2, 0x02 /* Public */,
     247,    0, 3035,    2, 0x02 /* Public */,
     248,    0, 3036,    2, 0x02 /* Public */,
     249,    0, 3037,    2, 0x02 /* Public */,
     250,    0, 3038,    2, 0x02 /* Public */,
     251,    0, 3039,    2, 0x02 /* Public */,
     252,    0, 3040,    2, 0x02 /* Public */,
     253,    0, 3041,    2, 0x02 /* Public */,
     254,    0, 3042,    2, 0x02 /* Public */,
     255,    0, 3043,    2, 0x02 /* Public */,
     256,    0, 3044,    2, 0x02 /* Public */,
     257,    0, 3045,    2, 0x02 /* Public */,
     258,    1, 3046,    2, 0x02 /* Public */,
     259,    1, 3049,    2, 0x02 /* Public */,
     260,    1, 3052,    2, 0x02 /* Public */,
     261,    1, 3055,    2, 0x02 /* Public */,
     262,    1, 3058,    2, 0x02 /* Public */,
     263,    0, 3061,    2, 0x02 /* Public */,
     264,    0, 3062,    2, 0x02 /* Public */,
     265,    0, 3063,    2, 0x02 /* Public */,
     266,    1, 3064,    2, 0x02 /* Public */,
     268,    0, 3067,    2, 0x02 /* Public */,
     269,    2, 3068,    2, 0x02 /* Public */,
     271,    1, 3073,    2, 0x02 /* Public */,
     274,    2, 3076,    2, 0x02 /* Public */,
     275,    1, 3081,    2, 0x02 /* Public */,
     274,    1, 3084,    2, 0x02 /* Public */,
     277,    1, 3087,    2, 0x02 /* Public */,
     279,    0, 3090,    2, 0x02 /* Public */,
     280,    1, 3091,    2, 0x02 /* Public */,
     281,    0, 3094,    2, 0x02 /* Public */,
     282,    1, 3095,    2, 0x02 /* Public */,
     283,    1, 3098,    2, 0x02 /* Public */,
     284,    1, 3101,    2, 0x02 /* Public */,
     285,    1, 3104,    2, 0x02 /* Public */,
     286,    1, 3107,    2, 0x02 /* Public */,
     288,    3, 3110,    2, 0x02 /* Public */,
     291,    0, 3117,    2, 0x02 /* Public */,
     292,    0, 3118,    2, 0x02 /* Public */,
     293,    0, 3119,    2, 0x02 /* Public */,
     294,    0, 3120,    2, 0x02 /* Public */,
     295,    1, 3121,    2, 0x02 /* Public */,
     296,    0, 3124,    2, 0x02 /* Public */,
     297,    1, 3125,    2, 0x02 /* Public */,
     298,    0, 3128,    2, 0x02 /* Public */,
     299,    1, 3129,    2, 0x02 /* Public */,
     301,    0, 3132,    2, 0x02 /* Public */,
     302,    0, 3133,    2, 0x02 /* Public */,
     303,    1, 3134,    2, 0x02 /* Public */,
     303,    0, 3137,    2, 0x22 /* Public | MethodCloned */,
     304,    1, 3138,    2, 0x02 /* Public */,
     305,    1, 3141,    2, 0x02 /* Public */,
     305,    0, 3144,    2, 0x22 /* Public | MethodCloned */,
     306,    1, 3145,    2, 0x02 /* Public */,
     306,    0, 3148,    2, 0x22 /* Public | MethodCloned */,
     307,    1, 3149,    2, 0x02 /* Public */,
     307,    0, 3152,    2, 0x22 /* Public | MethodCloned */,
     308,    1, 3153,    2, 0x02 /* Public */,
     308,    0, 3156,    2, 0x22 /* Public | MethodCloned */,
     309,    1, 3157,    2, 0x02 /* Public */,
     310,    1, 3160,    2, 0x02 /* Public */,
     311,    0, 3163,    2, 0x02 /* Public */,
     312,    0, 3164,    2, 0x02 /* Public */,
     313,    1, 3165,    2, 0x02 /* Public */,
     314,    1, 3168,    2, 0x02 /* Public */,
     315,    1, 3171,    2, 0x02 /* Public */,
     316,    0, 3174,    2, 0x02 /* Public */,
     317,    0, 3175,    2, 0x02 /* Public */,
     318,    1, 3176,    2, 0x02 /* Public */,
     320,    1, 3179,    2, 0x02 /* Public */,
     321,    2, 3182,    2, 0x02 /* Public */,
      85,    1, 3187,    2, 0x02 /* Public */,
     324,    3, 3190,    2, 0x02 /* Public */,
     327,    2, 3197,    2, 0x02 /* Public */,
     330,    0, 3202,    2, 0x02 /* Public */,
     331,    1, 3203,    2, 0x02 /* Public */,
     332,    1, 3206,    2, 0x02 /* Public */,
     333,    0, 3209,    2, 0x02 /* Public */,
     334,    3, 3210,    2, 0x02 /* Public */,
     335,    0, 3217,    2, 0x02 /* Public */,
     336,    0, 3218,    2, 0x02 /* Public */,
     337,    0, 3219,    2, 0x02 /* Public */,
     338,    0, 3220,    2, 0x02 /* Public */,
     339,    0, 3221,    2, 0x02 /* Public */,
     340,    0, 3222,    2, 0x02 /* Public */,
     341,    0, 3223,    2, 0x02 /* Public */,
     342,    0, 3224,    2, 0x02 /* Public */,
     343,    0, 3225,    2, 0x02 /* Public */,
     344,    0, 3226,    2, 0x02 /* Public */,
     345,    1, 3227,    2, 0x02 /* Public */,
     347,    0, 3230,    2, 0x02 /* Public */,
     348,    0, 3231,    2, 0x02 /* Public */,
     349,    0, 3232,    2, 0x02 /* Public */,
     350,    0, 3233,    2, 0x02 /* Public */,
     351,    0, 3234,    2, 0x02 /* Public */,
     352,    1, 3235,    2, 0x02 /* Public */,
     353,    0, 3238,    2, 0x02 /* Public */,
     354,    1, 3239,    2, 0x02 /* Public */,
     355,    1, 3242,    2, 0x02 /* Public */,
     356,    2, 3245,    2, 0x02 /* Public */,
     357,    2, 3250,    2, 0x02 /* Public */,
     358,    1, 3255,    2, 0x02 /* Public */,
     360,    0, 3258,    2, 0x02 /* Public */,
     361,    2, 3259,    2, 0x02 /* Public */,
     161,    1, 3264,    2, 0x02 /* Public */,
     161,    0, 3267,    2, 0x22 /* Public | MethodCloned */,
     362,    2, 3268,    2, 0x02 /* Public */,
     362,    1, 3273,    2, 0x22 /* Public | MethodCloned */,
     363,    1, 3276,    2, 0x02 /* Public */,
     364,    2, 3279,    2, 0x02 /* Public */,
     365,    2, 3284,    2, 0x02 /* Public */,
     366,    1, 3289,    2, 0x02 /* Public */,
     367,    1, 3292,    2, 0x02 /* Public */,
     368,    2, 3295,    2, 0x02 /* Public */,
     369,    0, 3300,    2, 0x02 /* Public */,
     370,    1, 3301,    2, 0x02 /* Public */,
     369,    1, 3304,    2, 0x02 /* Public */,
     371,    1, 3307,    2, 0x02 /* Public */,
     372,    2, 3310,    2, 0x02 /* Public */,
     373,    1, 3315,    2, 0x02 /* Public */,
     374,    1, 3318,    2, 0x02 /* Public */,
     375,    1, 3321,    2, 0x02 /* Public */,
     167,    4, 3324,    2, 0x02 /* Public */,
     377,    2, 3333,    2, 0x02 /* Public */,
     377,    1, 3338,    2, 0x22 /* Public | MethodCloned */,
     378,    2, 3341,    2, 0x02 /* Public */,
     378,    1, 3346,    2, 0x22 /* Public | MethodCloned */,
     379,    2, 3349,    2, 0x02 /* Public */,
     379,    1, 3354,    2, 0x22 /* Public | MethodCloned */,
     380,    2, 3357,    2, 0x02 /* Public */,
     381,    1, 3362,    2, 0x02 /* Public */,
     382,    0, 3365,    2, 0x02 /* Public */,
     383,    1, 3366,    2, 0x02 /* Public */,
     384,    0, 3369,    2, 0x02 /* Public */,
     385,    0, 3370,    2, 0x02 /* Public */,
     386,    1, 3371,    2, 0x02 /* Public */,
     387,    1, 3374,    2, 0x02 /* Public */,
     388,    2, 3377,    2, 0x02 /* Public */,
     390,    2, 3382,    2, 0x02 /* Public */,
     391,    3, 3387,    2, 0x02 /* Public */,
     393,    1, 3394,    2, 0x02 /* Public */,
     393,    2, 3397,    2, 0x02 /* Public */,
     394,    0, 3402,    2, 0x02 /* Public */,
     395,    1, 3403,    2, 0x02 /* Public */,
     396,    1, 3406,    2, 0x02 /* Public */,
     397,    1, 3409,    2, 0x02 /* Public */,
     398,    0, 3412,    2, 0x02 /* Public */,
     399,    0, 3413,    2, 0x02 /* Public */,
     400,    0, 3414,    2, 0x02 /* Public */,
     401,    0, 3415,    2, 0x02 /* Public */,
     402,    0, 3416,    2, 0x02 /* Public */,
     403,    2, 3417,    2, 0x02 /* Public */,
     403,    1, 3422,    2, 0x22 /* Public | MethodCloned */,
     404,    0, 3425,    2, 0x02 /* Public */,
     405,    3, 3426,    2, 0x02 /* Public */,
     407,    0, 3433,    2, 0x02 /* Public */,
     408,    1, 3434,    2, 0x02 /* Public */,
     410,    0, 3437,    2, 0x02 /* Public */,
     411,    0, 3438,    2, 0x02 /* Public */,
     413,    0, 3439,    2, 0x02 /* Public */,
     414,    0, 3440,    2, 0x02 /* Public */,
     415,    0, 3441,    2, 0x02 /* Public */,
     416,    0, 3442,    2, 0x02 /* Public */,
     417,    0, 3443,    2, 0x02 /* Public */,
     418,    0, 3444,    2, 0x02 /* Public */,
     419,    0, 3445,    2, 0x02 /* Public */,
     420,    0, 3446,    2, 0x02 /* Public */,
     421,    0, 3447,    2, 0x02 /* Public */,
     422,    0, 3448,    2, 0x02 /* Public */,
     423,    1, 3449,    2, 0x02 /* Public */,
     425,    0, 3452,    2, 0x02 /* Public */,
     426,    0, 3453,    2, 0x02 /* Public */,
     427,    0, 3454,    2, 0x02 /* Public */,
     428,    0, 3455,    2, 0x02 /* Public */,
     429,    0, 3456,    2, 0x02 /* Public */,
     430,    0, 3457,    2, 0x02 /* Public */,
     431,    0, 3458,    2, 0x02 /* Public */,
     432,    1, 3459,    2, 0x02 /* Public */,
     433,    1, 3462,    2, 0x02 /* Public */,
     434,    1, 3465,    2, 0x02 /* Public */,
     435,    1, 3468,    2, 0x02 /* Public */,
     436,    1, 3471,    2, 0x02 /* Public */,
     437,    0, 3474,    2, 0x02 /* Public */,
     438,    1, 3475,    2, 0x02 /* Public */,
     439,    0, 3478,    2, 0x02 /* Public */,
     440,    0, 3479,    2, 0x02 /* Public */,
     441,    0, 3480,    2, 0x02 /* Public */,
     442,    0, 3481,    2, 0x02 /* Public */,
     443,    0, 3482,    2, 0x02 /* Public */,
     444,    0, 3483,    2, 0x02 /* Public */,
     445,    0, 3484,    2, 0x02 /* Public */,
     446,    0, 3485,    2, 0x02 /* Public */,
     447,    0, 3486,    2, 0x02 /* Public */,
     448,    0, 3487,    2, 0x02 /* Public */,
     449,    0, 3488,    2, 0x02 /* Public */,
     450,    0, 3489,    2, 0x02 /* Public */,
     451,    1, 3490,    2, 0x02 /* Public */,
     452,    0, 3493,    2, 0x02 /* Public */,
     453,    0, 3494,    2, 0x02 /* Public */,
     454,    0, 3495,    2, 0x02 /* Public */,
     455,    0, 3496,    2, 0x02 /* Public */,
     456,    0, 3497,    2, 0x02 /* Public */,
     457,    0, 3498,    2, 0x02 /* Public */,
     458,    0, 3499,    2, 0x02 /* Public */,
     459,    0, 3500,    2, 0x02 /* Public */,
     460,    1, 3501,    2, 0x02 /* Public */,
     461,    1, 3504,    2, 0x02 /* Public */,
     462,    1, 3507,    2, 0x02 /* Public */,
     463,    0, 3510,    2, 0x02 /* Public */,
     464,    1, 3511,    2, 0x02 /* Public */,
     465,    1, 3514,    2, 0x02 /* Public */,
     466,    0, 3517,    2, 0x02 /* Public */,
     467,    0, 3518,    2, 0x02 /* Public */,
     468,    0, 3519,    2, 0x02 /* Public */,
     469,    0, 3520,    2, 0x02 /* Public */,
     470,    0, 3521,    2, 0x02 /* Public */,
     471,    0, 3522,    2, 0x02 /* Public */,
     472,    0, 3523,    2, 0x02 /* Public */,
     473,    0, 3524,    2, 0x02 /* Public */,
     474,    0, 3525,    2, 0x02 /* Public */,
     475,    0, 3526,    2, 0x02 /* Public */,
     476,    0, 3527,    2, 0x02 /* Public */,
     477,    0, 3528,    2, 0x02 /* Public */,
     385,    2, 3529,    2, 0x02 /* Public */,
     478,    2, 3534,    2, 0x02 /* Public */,
     479,    2, 3539,    2, 0x02 /* Public */,
     480,    2, 3544,    2, 0x02 /* Public */,
     481,    2, 3549,    2, 0x02 /* Public */,
     482,    2, 3554,    2, 0x02 /* Public */,
     483,    2, 3559,    2, 0x02 /* Public */,
     484,    0, 3564,    2, 0x02 /* Public */,
     485,    0, 3565,    2, 0x02 /* Public */,
     486,    0, 3566,    2, 0x02 /* Public */,
     487,    1, 3567,    2, 0x02 /* Public */,
     488,    0, 3570,    2, 0x02 /* Public */,
     489,    0, 3571,    2, 0x02 /* Public */,
     490,    0, 3572,    2, 0x02 /* Public */,
     491,    1, 3573,    2, 0x02 /* Public */,
      83,    2, 3576,    2, 0x02 /* Public */,
     493,    0, 3581,    2, 0x02 /* Public */,
     494,    0, 3582,    2, 0x02 /* Public */,
     495,    0, 3583,    2, 0x02 /* Public */,
     496,    0, 3584,    2, 0x02 /* Public */,
     497,    2, 3585,    2, 0x02 /* Public */,
     498,    0, 3590,    2, 0x02 /* Public */,
     499,    1, 3591,    2, 0x02 /* Public */,
     500,    0, 3594,    2, 0x02 /* Public */,
     501,    0, 3595,    2, 0x02 /* Public */,
     502,    6, 3596,    2, 0x02 /* Public */,
     502,    5, 3609,    2, 0x22 /* Public | MethodCloned */,
     502,    4, 3620,    2, 0x22 /* Public | MethodCloned */,
     502,    3, 3629,    2, 0x22 /* Public | MethodCloned */,
     502,    2, 3636,    2, 0x22 /* Public | MethodCloned */,
     502,    1, 3641,    2, 0x22 /* Public | MethodCloned */,
     502,    0, 3644,    2, 0x22 /* Public | MethodCloned */,
     509,    0, 3645,    2, 0x02 /* Public */,
     510,    0, 3646,    2, 0x02 /* Public */,
     511,    0, 3647,    2, 0x02 /* Public */,
     512,    1, 3648,    2, 0x02 /* Public */,
     513,    1, 3651,    2, 0x02 /* Public */,
     514,    1, 3654,    2, 0x02 /* Public */,
     515,    1, 3657,    2, 0x02 /* Public */,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   25,   21,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   29,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   29,   34,
    QMetaType::Bool, QMetaType::QString,   29,
    QMetaType::Int, QMetaType::QString,   29,
    QMetaType::Int, QMetaType::QString,   29,
    QMetaType::Bool, QMetaType::QString,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   42,   43,   44,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Void, QMetaType::QString,   29,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   32,   67,
    QMetaType::Void, QMetaType::QString,   69,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   69,   72,   73,   74,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   69,   72,   73,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   69,   72,
    QMetaType::Void, QMetaType::QString,   69,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   69,   72,   73,   74,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   69,   72,   73,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   69,   72,
    QMetaType::Void, QMetaType::QString,   69,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   77,   72,   73,   74,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   77,   72,   73,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   77,   72,
    QMetaType::Void, QMetaType::QString,   77,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int,   32,   21,   79,   80,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   21,   79,   80,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   79,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   69,   90,
    QMetaType::Void, QMetaType::QString,   69,
    QMetaType::Void, QMetaType::Int,   90,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   95,   90,
    QMetaType::Void, QMetaType::QString,   95,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Bool,  102,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  120,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,  118,  119,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  131,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::QString,   79,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  153,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int,  158,
    QMetaType::Void, QMetaType::Int,  160,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   25,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   79,  163,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  120,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  120,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  120,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  160,  179,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  181,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  181,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Void, QMetaType::Int,   90,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  160,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString,  200,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Int,   32,
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
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,  224,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  224,   21,  226,
    QMetaType::Void, QMetaType::QString,  228,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  224,   25,   21,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  232,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  238,  239,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Bool,  243,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   21,   69,
    QMetaType::QString, QMetaType::QString,   21,
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
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,  267,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,  270,
    0x80000000 | 272, QMetaType::QString,  273,
    0x80000000 | 272, QMetaType::Int, QMetaType::QString,   25,   21,
    0x80000000 | 272, QMetaType::Int,  276,
    0x80000000 | 272, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Int,  278,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QDateTime,  287,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  289,  290,  287,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  300,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::QString,   21,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  319,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  322,  323,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  325,  326,   69,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  328,  329,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   69,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  118,  119,  120,
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
    QMetaType::Void, QMetaType::Bool,  346,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  276,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  276,
    0x80000000 | 272, QMetaType::QString,  276,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   79,  276,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   79,  105,
    QMetaType::Void, QMetaType::Bool,  359,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Int, QMetaType::QString,   79,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   32,   79,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   21,   32,
    QMetaType::Int, QMetaType::QString,   79,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   32,   25,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   32,   21,   25,  376,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   79,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   79,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   79,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  346,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  389,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  389,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  392,  118,  119,
    QMetaType::Int, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   79,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::QString,  319,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  319,   69,
    QMetaType::Void, QMetaType::QString,  319,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  406,   25,  270,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  409,
    QMetaType::Void,
    0x80000000 | 412,
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
    QMetaType::Bool, QMetaType::Int,  424,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  276,
    QMetaType::Int, QMetaType::Int,  276,
    QMetaType::QString, QMetaType::Int,  276,
    QMetaType::Int, QMetaType::Int,  276,
    QMetaType::Int, QMetaType::Int,  276,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  276,
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
    QMetaType::Void, QMetaType::Bool,  105,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    0x80000000 | 412,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  118,  119,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   69,  492,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   25,   21,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  503,  504,  505,  506,  507,  508,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  503,  504,  505,  506,  507,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  503,  504,  505,  506,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  503,  504,  505,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  503,  504,
    QMetaType::Void, QMetaType::QString,  503,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int,   32,

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
        case 15: _t->map_reset(); break;
        case 16: _t->new_call_order((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->loadMapServer(); break;
        case 18: _t->sendMapServer(); break;
        case 19: { bool _r = _t->checkLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 20: _t->resetClear(); break;
        case 21: { int _r = _t->getWifiNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 22: { int _r = _t->getWifiConnection((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 23: { QString _r = _t->getCurWifiSSID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 24: { QString _r = _t->getWifiSSID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 25: _t->connectWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 26: { bool _r = _t->getWifiSecurity((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { int _r = _t->getWifiLevel((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 28: { int _r = _t->getWifiRate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 29: { bool _r = _t->getWifiInuse((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: _t->getAllWifiList(); break;
        case 31: _t->getWifiIP(); break;
        case 32: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 33: { QString _r = _t->getcurIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 34: { QString _r = _t->getcurGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 35: { QString _r = _t->getcurDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->readWifiState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 37: _t->setWifiSSD((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 38: { int _r = _t->getSystemVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->passInit(); break;
        case 40: _t->readPatrol(); break;
        case 41: { int _r = _t->getPatrolSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 42: { QString _r = _t->getPatrolName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 43: { QString _r = _t->getPatrolType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 44: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 45: { QString _r = _t->getPatrolMovingPage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 46: { QString _r = _t->getPatrolArrivePage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 47: { int _r = _t->getPatrolWaitTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 48: { QString _r = _t->getPatrolVoice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 49: { QString _r = _t->getPatrolVoiceMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 50: { bool _r = _t->isPatrolPage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 51: { QString _r = _t->getPatrolMovingMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 52: { QString _r = _t->getPatrolArriveMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 53: _t->setCurrentPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 54: { int _r = _t->getPatrolLocationSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 55: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 56: _t->clearPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 57: _t->addPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 58: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 59: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 60: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 61: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 62: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 63: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 64: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 65: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 66: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 67: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 68: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 69: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 70: _t->setPatrol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 71: _t->savePatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 72: _t->deletePatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 73: _t->startPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 74: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 75: _t->setMap(); break;
        case 76: _t->moveMap(); break;
        case 77: _t->setFullScreen(); break;
        case 78: _t->setMapDrawing(); break;
        case 79: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 80: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 81: _t->playBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 82: _t->playBGM(); break;
        case 83: _t->stopBGM(); break;
        case 84: { bool _r = _t->isplayBGM();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 85: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 86: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 87: _t->confirmLocalization(); break;
        case 88: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 89: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 90: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 91: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 92: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 93: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 94: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 95: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 96: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 97: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 98: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 99: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 100: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 101: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 102: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 103: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 104: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 105: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 106: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 107: _t->clearInitPose(); break;
        case 108: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 109: _t->startDrawingTline(); break;
        case 110: _t->stopDrawingTline(); break;
        case 111: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 112: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 113: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 114: _t->saveRotateMap(); break;
        case 115: _t->initRotate(); break;
        case 116: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 117: _t->rotateMapCW(); break;
        case 118: _t->rotateMapCCW(); break;
        case 119: _t->saveObjectPNG(); break;
        case 120: _t->saveObsAreaPNG(); break;
        case 121: { int _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 122: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 123: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 124: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 125: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 126: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 127: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 128: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 129: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 130: _t->endDrawingRect(); break;
        case 131: _t->clearDrawing(); break;
        case 132: _t->undoLine(); break;
        case 133: _t->redoLine(); break;
        case 134: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 135: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 136: _t->drawSpline(); break;
        case 137: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 138: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 139: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 140: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 141: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 142: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 143: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 144: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 145: _t->clearLocation(); break;
        case 146: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 147: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 148: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 149: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 150: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 151: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 152: { bool _r = _t->getLocationAvailable((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 153: _t->setTableNumberAuto(); break;
        case 154: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 155: _t->saveMap(); break;
        case 156: _t->saveEditedMap(); break;
        case 157: _t->saveTline(); break;
        case 158: _t->saveTlineTemp(); break;
        case 159: _t->saveVelmap(); break;
        case 160: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 161: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 162: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 163: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 164: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 165: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 166: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 167: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 168: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 169: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 170: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 171: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 172: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 173: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 174: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 175: _t->requestSystemVolume(); break;
        case 176: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 177: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 178: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 179: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 180: _t->startDrawingObject(); break;
        case 181: _t->stopDrawingObject(); break;
        case 182: _t->saveDrawingObject(); break;
        case 183: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 184: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 185: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 186: _t->killSLAM(); break;
        case 187: _t->makeRobotINI(); break;
        case 188: _t->checkRobotINI(); break;
        case 189: _t->restartSLAM(); break;
        case 190: _t->startSLAM(); break;
        case 191: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 192: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 193: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 194: _t->programRestart(); break;
        case 195: _t->programExit(); break;
        case 196: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 197: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 198: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 199: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 200: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 201: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 202: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 203: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 204: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 205: _t->readSetting(); break;
        case 206: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 207: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 208: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 209: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 210: _t->requestCamera(); break;
        case 211: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 212: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 213: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 214: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 215: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 216: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 217: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 218: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 219: _t->checkTravelline(); break;
        case 220: _t->updateProgram(); break;
        case 221: _t->updateProgramGitPull(); break;
        case 222: _t->checkVersionAgain(); break;
        case 223: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 224: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 225: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 226: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 227: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 228: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 229: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 230: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 231: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 232: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 233: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 234: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 235: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 236: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 237: _t->checkCleaningLocation(); break;
        case 238: _t->checkUpdate(); break;
        case 239: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 240: _t->setlanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 241: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 242: _t->goServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 243: { LOCATION _r = _t->getLocationbyCall((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 244: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 245: { LOCATION _r = _t->getLocationbyID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 246: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 247: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 248: _t->resetLocalization(); break;
        case 249: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 250: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 251: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 252: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 253: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 254: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 255: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 256: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 257: _t->updateUSB(); break;
        case 258: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 259: _t->readusbrecentfile(); break;
        case 260: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 261: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 262: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 263: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 264: _t->readusb(); break;
        case 265: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 266: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 267: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 268: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 269: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 270: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 271: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 272: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 273: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 274: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 275: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 276: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 277: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 278: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 279: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 280: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 281: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 282: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 283: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 284: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 285: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 286: _t->deleteEditedMap(); break;
        case 287: _t->deleteAnnotation(); break;
        case 288: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 289: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 290: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 291: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 292: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 293: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 294: _t->stopMapping(); break;
        case 295: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 296: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 297: _t->setInitCurPos(); break;
        case 298: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 299: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 300: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 301: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 302: _t->slam_setInit(); break;
        case 303: _t->slam_run(); break;
        case 304: _t->slam_stop(); break;
        case 305: _t->slam_autoInit(); break;
        case 306: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 307: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 308: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 309: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 310: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 311: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 312: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 313: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 314: _t->cleanTray(); break;
        case 315: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 316: _t->clearCallQueue(); break;
        case 317: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 318: { LOCATION _r = _t->getCallLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 319: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 320: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 321: _t->acceptCall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 322: _t->setObjPose(); break;
        case 323: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 324: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 325: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 326: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 327: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 328: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 329: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 330: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 331: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 332: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 333: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 334: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 335: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 336: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 337: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 338: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 339: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 340: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 341: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 342: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 343: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 344: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 345: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 346: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 347: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 348: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 349: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 350: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 351: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 352: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 353: _t->clearSharedMemory(); break;
        case 354: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 355: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 356: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 357: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 358: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 359: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 360: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 361: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 362: _t->saveLocations(); break;
        case 363: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 364: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 365: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 366: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 367: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 368: _t->drawingRunawayStart(); break;
        case 369: _t->drawingRunawayStop(); break;
        case 370: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 371: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 372: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 373: _t->slam_ini_reload(); break;
        case 374: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 375: _t->startServing(); break;
        case 376: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 377: _t->confirmPickup(); break;
        case 378: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 379: _t->movePause(); break;
        case 380: _t->moveResume(); break;
        case 381: _t->moveStopFlag(); break;
        case 382: _t->moveStop(); break;
        case 383: _t->moveToCharge(); break;
        case 384: _t->moveToWait(); break;
        case 385: _t->moveToCleaning(); break;
        case 386: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 387: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 388: _t->resetHomeFolders(); break;
        case 389: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 390: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 391: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 392: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 393: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 394: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 395: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 396: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 397: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 398: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 399: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 400: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 401: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 402: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 403: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 404: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 405: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 406: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 407: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 408: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 409: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 410: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 411: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 412: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 413: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 414: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 415: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 416: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 417: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 418: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 419: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 420: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 421: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 422: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 423: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 424: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 425: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 426: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 427: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 428: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 429: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 430: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 431: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 432: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 433: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 434: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 435: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 436: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 437: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 438: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 439: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 440: _t->startDrawObject(); break;
        case 441: _t->stopDrawObject(); break;
        case 442: _t->saveDrawObject(); break;
        case 443: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 444: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 445: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 446: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 447: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 448: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 449: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 450: _t->saveObject(); break;
        case 451: _t->clearObject(); break;
        case 452: _t->clearObjectAll(); break;
        case 453: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 454: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 455: _t->undoObject(); break;
        case 456: _t->clearRotateList(); break;
        case 457: _t->setRotateList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 458: _t->startPatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 459: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 460: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 461: _t->clearFlagStop(); break;
        case 462: _t->slam_fullautoInit(); break;
        case 463: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 464: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 465: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 466: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 467: _t->clear_call(); break;
        case 468: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 469: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 470: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 471: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 472: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 473: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 474: _t->usbsave(); break;
        case 475: _t->restartUpdate(); break;
        case 476: _t->startUpdate(); break;
        case 477: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 478: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 479: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 480: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 481: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
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
        if (_id < 482)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 482;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 482)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 482;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
