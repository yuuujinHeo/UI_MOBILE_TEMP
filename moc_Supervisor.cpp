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
    QByteArrayData data[519];
    char stringdata0[6616];
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
QT_MOC_LITERAL(60, 711, 17), // "getPatrolPassTime"
QT_MOC_LITERAL(61, 729, 14), // "getPatrolVoice"
QT_MOC_LITERAL(62, 744, 18), // "getPatrolVoiceMode"
QT_MOC_LITERAL(63, 763, 22), // "getPatrolVoiceLanguage"
QT_MOC_LITERAL(64, 786, 12), // "isPatrolPage"
QT_MOC_LITERAL(65, 799, 19), // "getPatrolMovingMode"
QT_MOC_LITERAL(66, 819, 19), // "getPatrolArriveMode"
QT_MOC_LITERAL(67, 839, 16), // "setCurrentPatrol"
QT_MOC_LITERAL(68, 856, 21), // "getPatrolLocationSize"
QT_MOC_LITERAL(69, 878, 3), // "loc"
QT_MOC_LITERAL(70, 882, 19), // "clearPatrolLocation"
QT_MOC_LITERAL(71, 902, 4), // "mode"
QT_MOC_LITERAL(72, 907, 17), // "addPatrolLocation"
QT_MOC_LITERAL(73, 925, 19), // "setPatrolMovingPage"
QT_MOC_LITERAL(74, 945, 6), // "param1"
QT_MOC_LITERAL(75, 952, 6), // "param2"
QT_MOC_LITERAL(76, 959, 6), // "param3"
QT_MOC_LITERAL(77, 966, 19), // "setPatrolArrivePage"
QT_MOC_LITERAL(78, 986, 14), // "setPatrolVoice"
QT_MOC_LITERAL(79, 1001, 4), // "text"
QT_MOC_LITERAL(80, 1006, 9), // "setPatrol"
QT_MOC_LITERAL(81, 1016, 4), // "type"
QT_MOC_LITERAL(82, 1021, 9), // "wait_time"
QT_MOC_LITERAL(83, 1031, 9), // "pass_time"
QT_MOC_LITERAL(84, 1041, 10), // "savePatrol"
QT_MOC_LITERAL(85, 1052, 12), // "deletePatrol"
QT_MOC_LITERAL(86, 1065, 11), // "startPatrol"
QT_MOC_LITERAL(87, 1077, 8), // "loadFile"
QT_MOC_LITERAL(88, 1086, 6), // "setMap"
QT_MOC_LITERAL(89, 1093, 13), // "setFullScreen"
QT_MOC_LITERAL(90, 1107, 13), // "setMapDrawing"
QT_MOC_LITERAL(91, 1121, 10), // "clicksound"
QT_MOC_LITERAL(92, 1132, 6), // "volume"
QT_MOC_LITERAL(93, 1139, 7), // "playBGM"
QT_MOC_LITERAL(94, 1147, 7), // "stopBGM"
QT_MOC_LITERAL(95, 1155, 9), // "isplayBGM"
QT_MOC_LITERAL(96, 1165, 9), // "playVoice"
QT_MOC_LITERAL(97, 1175, 5), // "voice"
QT_MOC_LITERAL(98, 1181, 13), // "playVoiceFile"
QT_MOC_LITERAL(99, 1195, 4), // "file"
QT_MOC_LITERAL(100, 1200, 7), // "makeTTS"
QT_MOC_LITERAL(101, 1208, 3), // "lan"
QT_MOC_LITERAL(102, 1212, 7), // "playTTS"
QT_MOC_LITERAL(103, 1220, 19), // "confirmLocalization"
QT_MOC_LITERAL(104, 1240, 7), // "setName"
QT_MOC_LITERAL(105, 1248, 7), // "setTool"
QT_MOC_LITERAL(106, 1256, 7), // "getTool"
QT_MOC_LITERAL(107, 1264, 7), // "setMode"
QT_MOC_LITERAL(108, 1272, 9), // "setEnable"
QT_MOC_LITERAL(109, 1282, 2), // "en"
QT_MOC_LITERAL(110, 1285, 7), // "getMode"
QT_MOC_LITERAL(111, 1293, 12), // "setShowBrush"
QT_MOC_LITERAL(112, 1306, 5), // "onoff"
QT_MOC_LITERAL(113, 1312, 12), // "setShowLidar"
QT_MOC_LITERAL(114, 1325, 15), // "setShowLocation"
QT_MOC_LITERAL(115, 1341, 17), // "setRobotFollowing"
QT_MOC_LITERAL(116, 1359, 17), // "setShowTravelline"
QT_MOC_LITERAL(117, 1377, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(118, 1396, 13), // "setShowObject"
QT_MOC_LITERAL(119, 1410, 11), // "setInitFlag"
QT_MOC_LITERAL(120, 1422, 15), // "getshowLocation"
QT_MOC_LITERAL(121, 1438, 17), // "getRobotFollowing"
QT_MOC_LITERAL(122, 1456, 12), // "getShowLidar"
QT_MOC_LITERAL(123, 1469, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(124, 1485, 11), // "setInitPose"
QT_MOC_LITERAL(125, 1497, 1), // "x"
QT_MOC_LITERAL(126, 1499, 1), // "y"
QT_MOC_LITERAL(127, 1501, 2), // "th"
QT_MOC_LITERAL(128, 1504, 13), // "clearInitPose"
QT_MOC_LITERAL(129, 1518, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(130, 1539, 17), // "startDrawingTline"
QT_MOC_LITERAL(131, 1557, 16), // "stopDrawingTline"
QT_MOC_LITERAL(132, 1574, 15), // "getDrawingTline"
QT_MOC_LITERAL(133, 1590, 13), // "setRulerPoint"
QT_MOC_LITERAL(134, 1604, 11), // "setBoxPoint"
QT_MOC_LITERAL(135, 1616, 11), // "getPointBox"
QT_MOC_LITERAL(136, 1628, 13), // "saveRotateMap"
QT_MOC_LITERAL(137, 1642, 10), // "initRotate"
QT_MOC_LITERAL(138, 1653, 9), // "rotateMap"
QT_MOC_LITERAL(139, 1663, 5), // "angle"
QT_MOC_LITERAL(140, 1669, 11), // "rotateMapCW"
QT_MOC_LITERAL(141, 1681, 12), // "rotateMapCCW"
QT_MOC_LITERAL(142, 1694, 13), // "saveObjectPNG"
QT_MOC_LITERAL(143, 1708, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(144, 1723, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(145, 1746, 14), // "getDrawingFlag"
QT_MOC_LITERAL(146, 1761, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(147, 1780, 12), // "startDrawing"
QT_MOC_LITERAL(148, 1793, 12), // "addLinePoint"
QT_MOC_LITERAL(149, 1806, 10), // "endDrawing"
QT_MOC_LITERAL(150, 1817, 10), // "setMapOrin"
QT_MOC_LITERAL(151, 1828, 16), // "startDrawingRect"
QT_MOC_LITERAL(152, 1845, 14), // "setDrawingRect"
QT_MOC_LITERAL(153, 1860, 14), // "endDrawingRect"
QT_MOC_LITERAL(154, 1875, 12), // "clearDrawing"
QT_MOC_LITERAL(155, 1888, 8), // "undoLine"
QT_MOC_LITERAL(156, 1897, 8), // "redoLine"
QT_MOC_LITERAL(157, 1906, 11), // "startSpline"
QT_MOC_LITERAL(158, 1918, 9), // "addSpline"
QT_MOC_LITERAL(159, 1928, 10), // "drawSpline"
QT_MOC_LITERAL(160, 1939, 9), // "endSpline"
QT_MOC_LITERAL(161, 1949, 4), // "save"
QT_MOC_LITERAL(162, 1954, 16), // "startDrawingLine"
QT_MOC_LITERAL(163, 1971, 14), // "setDrawingLine"
QT_MOC_LITERAL(164, 1986, 15), // "stopDrawingLine"
QT_MOC_LITERAL(165, 2002, 12), // "setLineColor"
QT_MOC_LITERAL(166, 2015, 5), // "color"
QT_MOC_LITERAL(167, 2021, 12), // "setLineWidth"
QT_MOC_LITERAL(168, 2034, 5), // "width"
QT_MOC_LITERAL(169, 2040, 14), // "getLocationNum"
QT_MOC_LITERAL(170, 2055, 12), // "saveLocation"
QT_MOC_LITERAL(171, 2068, 8), // "groupnum"
QT_MOC_LITERAL(172, 2077, 13), // "clearLocation"
QT_MOC_LITERAL(173, 2091, 11), // "addLocation"
QT_MOC_LITERAL(174, 2103, 14), // "addLocationCur"
QT_MOC_LITERAL(175, 2118, 11), // "setLocation"
QT_MOC_LITERAL(176, 2130, 12), // "editLocation"
QT_MOC_LITERAL(177, 2143, 14), // "removeLocation"
QT_MOC_LITERAL(178, 2158, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(179, 2177, 14), // "getLocGroupNum"
QT_MOC_LITERAL(180, 2192, 7), // "saveMap"
QT_MOC_LITERAL(181, 2200, 13), // "saveEditedMap"
QT_MOC_LITERAL(182, 2214, 9), // "saveTline"
QT_MOC_LITERAL(183, 2224, 13), // "saveTlineTemp"
QT_MOC_LITERAL(184, 2238, 10), // "saveVelmap"
QT_MOC_LITERAL(185, 2249, 10), // "setMapSize"
QT_MOC_LITERAL(186, 2260, 6), // "height"
QT_MOC_LITERAL(187, 2267, 6), // "zoomIn"
QT_MOC_LITERAL(188, 2274, 4), // "dist"
QT_MOC_LITERAL(189, 2279, 7), // "zoomOut"
QT_MOC_LITERAL(190, 2287, 4), // "move"
QT_MOC_LITERAL(191, 2292, 12), // "getFileWidth"
QT_MOC_LITERAL(192, 2305, 4), // "getX"
QT_MOC_LITERAL(193, 2310, 4), // "getY"
QT_MOC_LITERAL(194, 2315, 8), // "getScale"
QT_MOC_LITERAL(195, 2324, 13), // "setVelmapView"
QT_MOC_LITERAL(196, 2338, 12), // "setTlineView"
QT_MOC_LITERAL(197, 2351, 13), // "setObjectView"
QT_MOC_LITERAL(198, 2365, 15), // "setAvoidmapView"
QT_MOC_LITERAL(199, 2381, 15), // "setLocationView"
QT_MOC_LITERAL(200, 2397, 12), // "setRobotView"
QT_MOC_LITERAL(201, 2410, 15), // "setSystemVolume"
QT_MOC_LITERAL(202, 2426, 19), // "requestSystemVolume"
QT_MOC_LITERAL(203, 2446, 7), // "setSize"
QT_MOC_LITERAL(204, 2454, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(205, 2468, 14), // "selectLocation"
QT_MOC_LITERAL(206, 2483, 8), // "writelog"
QT_MOC_LITERAL(207, 2492, 3), // "msg"
QT_MOC_LITERAL(208, 2496, 18), // "startDrawingObject"
QT_MOC_LITERAL(209, 2515, 17), // "stopDrawingObject"
QT_MOC_LITERAL(210, 2533, 17), // "saveDrawingObject"
QT_MOC_LITERAL(211, 2551, 13), // "setLocationUp"
QT_MOC_LITERAL(212, 2565, 15), // "setLocationDown"
QT_MOC_LITERAL(213, 2581, 8), // "checkINI"
QT_MOC_LITERAL(214, 2590, 8), // "killSLAM"
QT_MOC_LITERAL(215, 2599, 12), // "makeRobotINI"
QT_MOC_LITERAL(216, 2612, 13), // "checkRobotINI"
QT_MOC_LITERAL(217, 2626, 11), // "restartSLAM"
QT_MOC_LITERAL(218, 2638, 9), // "startSLAM"
QT_MOC_LITERAL(219, 2648, 16), // "getIPCConnection"
QT_MOC_LITERAL(220, 2665, 8), // "getIPCRX"
QT_MOC_LITERAL(221, 2674, 8), // "getIPCTX"
QT_MOC_LITERAL(222, 2683, 14), // "programRestart"
QT_MOC_LITERAL(223, 2698, 11), // "programExit"
QT_MOC_LITERAL(224, 2710, 13), // "getRawMapPath"
QT_MOC_LITERAL(225, 2724, 10), // "getMapPath"
QT_MOC_LITERAL(226, 2735, 12), // "getAnnotPath"
QT_MOC_LITERAL(227, 2748, 11), // "getMetaPath"
QT_MOC_LITERAL(228, 2760, 13), // "getTravelPath"
QT_MOC_LITERAL(229, 2774, 11), // "getCostPath"
QT_MOC_LITERAL(230, 2786, 10), // "getIniPath"
QT_MOC_LITERAL(231, 2797, 10), // "setSetting"
QT_MOC_LITERAL(232, 2808, 5), // "value"
QT_MOC_LITERAL(233, 2814, 11), // "readSetting"
QT_MOC_LITERAL(234, 2826, 8), // "map_name"
QT_MOC_LITERAL(235, 2835, 10), // "getSetting"
QT_MOC_LITERAL(236, 2846, 10), // "getTrayNum"
QT_MOC_LITERAL(237, 2857, 14), // "setTableColNum"
QT_MOC_LITERAL(238, 2872, 7), // "col_num"
QT_MOC_LITERAL(239, 2880, 12), // "getRobotType"
QT_MOC_LITERAL(240, 2893, 13), // "requestCamera"
QT_MOC_LITERAL(241, 2907, 13), // "getLeftCamera"
QT_MOC_LITERAL(242, 2921, 14), // "getRightCamera"
QT_MOC_LITERAL(243, 2936, 9), // "setCamera"
QT_MOC_LITERAL(244, 2946, 4), // "left"
QT_MOC_LITERAL(245, 2951, 5), // "right"
QT_MOC_LITERAL(246, 2957, 12), // "getCameraNum"
QT_MOC_LITERAL(247, 2970, 15), // "getCameraSerial"
QT_MOC_LITERAL(248, 2986, 13), // "setCursorView"
QT_MOC_LITERAL(249, 3000, 7), // "visible"
QT_MOC_LITERAL(250, 3008, 8), // "getVoice"
QT_MOC_LITERAL(251, 3017, 15), // "checkTravelline"
QT_MOC_LITERAL(252, 3033, 13), // "updateProgram"
QT_MOC_LITERAL(253, 3047, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(254, 3068, 17), // "checkVersionAgain"
QT_MOC_LITERAL(255, 3086, 12), // "isNewVersion"
QT_MOC_LITERAL(256, 3099, 12), // "isNeedUpdate"
QT_MOC_LITERAL(257, 3112, 15), // "getLocalVersion"
QT_MOC_LITERAL(258, 3128, 16), // "getServerVersion"
QT_MOC_LITERAL(259, 3145, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(260, 3165, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(261, 3188, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(262, 3212, 13), // "getUpdateDate"
QT_MOC_LITERAL(263, 3226, 13), // "getUpdateSize"
QT_MOC_LITERAL(264, 3240, 17), // "getUpdateFileName"
QT_MOC_LITERAL(265, 3258, 15), // "getUpdateCommit"
QT_MOC_LITERAL(266, 3274, 16), // "getCurrentCommit"
QT_MOC_LITERAL(267, 3291, 16), // "getUpdateMessage"
QT_MOC_LITERAL(268, 3308, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(269, 3326, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(270, 3348, 11), // "checkUpdate"
QT_MOC_LITERAL(271, 3360, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(272, 3382, 11), // "setlanguage"
QT_MOC_LITERAL(273, 3394, 13), // "isCallingMode"
QT_MOC_LITERAL(274, 3408, 9), // "goServing"
QT_MOC_LITERAL(275, 3418, 5), // "table"
QT_MOC_LITERAL(276, 3424, 17), // "getLocationbyCall"
QT_MOC_LITERAL(277, 3442, 8), // "LOCATION"
QT_MOC_LITERAL(278, 3451, 4), // "call"
QT_MOC_LITERAL(279, 3456, 11), // "getLocation"
QT_MOC_LITERAL(280, 3468, 15), // "getLocationbyID"
QT_MOC_LITERAL(281, 3484, 2), // "id"
QT_MOC_LITERAL(282, 3487, 10), // "setUiState"
QT_MOC_LITERAL(283, 3498, 5), // "state"
QT_MOC_LITERAL(284, 3504, 17), // "resetLocalization"
QT_MOC_LITERAL(285, 3522, 6), // "setLog"
QT_MOC_LITERAL(286, 3529, 13), // "getLogLineNum"
QT_MOC_LITERAL(287, 3543, 10), // "getLogLine"
QT_MOC_LITERAL(288, 3554, 10), // "getLogDate"
QT_MOC_LITERAL(289, 3565, 10), // "getLogAuth"
QT_MOC_LITERAL(290, 3576, 13), // "getLogMessage"
QT_MOC_LITERAL(291, 3590, 7), // "readLog"
QT_MOC_LITERAL(292, 3598, 4), // "date"
QT_MOC_LITERAL(293, 3603, 13), // "getLocaleDate"
QT_MOC_LITERAL(294, 3617, 4), // "year"
QT_MOC_LITERAL(295, 3622, 5), // "month"
QT_MOC_LITERAL(296, 3628, 9), // "updateUSB"
QT_MOC_LITERAL(297, 3638, 10), // "getusbsize"
QT_MOC_LITERAL(298, 3649, 17), // "readusbrecentfile"
QT_MOC_LITERAL(299, 3667, 14), // "getusbfilesize"
QT_MOC_LITERAL(300, 3682, 10), // "getusbfile"
QT_MOC_LITERAL(301, 3693, 16), // "getusbrecentfile"
QT_MOC_LITERAL(302, 3710, 10), // "getusbname"
QT_MOC_LITERAL(303, 3721, 7), // "readusb"
QT_MOC_LITERAL(304, 3729, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(305, 3744, 4), // "path"
QT_MOC_LITERAL(306, 3749, 15), // "isConnectServer"
QT_MOC_LITERAL(307, 3765, 9), // "isLoadMap"
QT_MOC_LITERAL(308, 3775, 10), // "isExistMap"
QT_MOC_LITERAL(309, 3786, 13), // "isExistRawMap"
QT_MOC_LITERAL(310, 3800, 15), // "isExistTlineMap"
QT_MOC_LITERAL(311, 3816, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(312, 3832, 13), // "isExistVelMap"
QT_MOC_LITERAL(313, 3846, 16), // "isExistObjectMap"
QT_MOC_LITERAL(314, 3863, 16), // "isExistTravelMap"
QT_MOC_LITERAL(315, 3880, 17), // "isExistAnnotation"
QT_MOC_LITERAL(316, 3898, 15), // "isExistRobotINI"
QT_MOC_LITERAL(317, 3914, 15), // "getAvailableMap"
QT_MOC_LITERAL(318, 3930, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(319, 3950, 14), // "getMapFileSize"
QT_MOC_LITERAL(320, 3965, 10), // "getMapFile"
QT_MOC_LITERAL(321, 3976, 15), // "deleteEditedMap"
QT_MOC_LITERAL(322, 3992, 16), // "deleteAnnotation"
QT_MOC_LITERAL(323, 4009, 9), // "removeMap"
QT_MOC_LITERAL(324, 4019, 8), // "filename"
QT_MOC_LITERAL(325, 4028, 7), // "loadMap"
QT_MOC_LITERAL(326, 4036, 7), // "copyMap"
QT_MOC_LITERAL(327, 4044, 8), // "orinname"
QT_MOC_LITERAL(328, 4053, 7), // "newname"
QT_MOC_LITERAL(329, 4061, 10), // "rotate_map"
QT_MOC_LITERAL(330, 4072, 4), // "_src"
QT_MOC_LITERAL(331, 4077, 4), // "_dst"
QT_MOC_LITERAL(332, 4082, 12), // "startMapping"
QT_MOC_LITERAL(333, 4095, 7), // "mapsize"
QT_MOC_LITERAL(334, 4103, 4), // "grid"
QT_MOC_LITERAL(335, 4108, 11), // "stopMapping"
QT_MOC_LITERAL(336, 4120, 11), // "setSLAMMode"
QT_MOC_LITERAL(337, 4132, 11), // "saveMapping"
QT_MOC_LITERAL(338, 4144, 13), // "setInitCurPos"
QT_MOC_LITERAL(339, 4158, 10), // "setInitPos"
QT_MOC_LITERAL(340, 4169, 12), // "getInitPoseX"
QT_MOC_LITERAL(341, 4182, 12), // "getInitPoseY"
QT_MOC_LITERAL(342, 4195, 13), // "getInitPoseTH"
QT_MOC_LITERAL(343, 4209, 12), // "slam_setInit"
QT_MOC_LITERAL(344, 4222, 8), // "slam_run"
QT_MOC_LITERAL(345, 4231, 9), // "slam_stop"
QT_MOC_LITERAL(346, 4241, 13), // "slam_autoInit"
QT_MOC_LITERAL(347, 4255, 15), // "is_slam_running"
QT_MOC_LITERAL(348, 4271, 14), // "getMappingflag"
QT_MOC_LITERAL(349, 4286, 16), // "getObjectingflag"
QT_MOC_LITERAL(350, 4303, 16), // "setObjectingflag"
QT_MOC_LITERAL(351, 4320, 4), // "flag"
QT_MOC_LITERAL(352, 4325, 13), // "getnewMapname"
QT_MOC_LITERAL(353, 4339, 11), // "getLastCall"
QT_MOC_LITERAL(354, 4351, 11), // "getCallSize"
QT_MOC_LITERAL(355, 4363, 16), // "getCallQueueSize"
QT_MOC_LITERAL(356, 4380, 9), // "cleanTray"
QT_MOC_LITERAL(357, 4390, 11), // "getCallName"
QT_MOC_LITERAL(358, 4402, 14), // "clearCallQueue"
QT_MOC_LITERAL(359, 4417, 7), // "getCall"
QT_MOC_LITERAL(360, 4425, 15), // "getCallLocation"
QT_MOC_LITERAL(361, 4441, 11), // "setCallbell"
QT_MOC_LITERAL(362, 4453, 16), // "setCallbellForce"
QT_MOC_LITERAL(363, 4470, 10), // "acceptCall"
QT_MOC_LITERAL(364, 4481, 3), // "yes"
QT_MOC_LITERAL(365, 4485, 10), // "setObjPose"
QT_MOC_LITERAL(366, 4496, 14), // "getServingName"
QT_MOC_LITERAL(367, 4511, 15), // "getLocationName"
QT_MOC_LITERAL(368, 4527, 15), // "getLocationType"
QT_MOC_LITERAL(369, 4543, 17), // "getLocationNumber"
QT_MOC_LITERAL(370, 4561, 17), // "setLocationNumber"
QT_MOC_LITERAL(371, 4579, 15), // "getLocationSize"
QT_MOC_LITERAL(372, 4595, 16), // "getLocationGroup"
QT_MOC_LITERAL(373, 4612, 13), // "getLocationID"
QT_MOC_LITERAL(374, 4626, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(375, 4646, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(376, 4667, 17), // "getLocationCallID"
QT_MOC_LITERAL(377, 4685, 16), // "setLocationGroup"
QT_MOC_LITERAL(378, 4702, 19), // "removeLocationGroup"
QT_MOC_LITERAL(379, 4722, 16), // "addLocationGroup"
QT_MOC_LITERAL(380, 4739, 15), // "getLocGroupname"
QT_MOC_LITERAL(381, 4755, 8), // "tablenum"
QT_MOC_LITERAL(382, 4764, 12), // "getLocationX"
QT_MOC_LITERAL(383, 4777, 12), // "getLocationY"
QT_MOC_LITERAL(384, 4790, 13), // "getLocationTH"
QT_MOC_LITERAL(385, 4804, 15), // "isExistLocation"
QT_MOC_LITERAL(386, 4820, 8), // "getLidar"
QT_MOC_LITERAL(387, 4829, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(388, 4846, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(389, 4863, 17), // "clearSharedMemory"
QT_MOC_LITERAL(390, 4881, 12), // "getObjectNum"
QT_MOC_LITERAL(391, 4894, 13), // "getObjectName"
QT_MOC_LITERAL(392, 4908, 18), // "getObjectPointSize"
QT_MOC_LITERAL(393, 4927, 10), // "getObjectX"
QT_MOC_LITERAL(394, 4938, 5), // "point"
QT_MOC_LITERAL(395, 4944, 10), // "getObjectY"
QT_MOC_LITERAL(396, 4955, 14), // "getObjPointNum"
QT_MOC_LITERAL(397, 4970, 7), // "obj_num"
QT_MOC_LITERAL(398, 4978, 9), // "getLocNum"
QT_MOC_LITERAL(399, 4988, 13), // "saveLocations"
QT_MOC_LITERAL(400, 5002, 13), // "getObjectSize"
QT_MOC_LITERAL(401, 5016, 12), // "removeObject"
QT_MOC_LITERAL(402, 5029, 14), // "saveAnnotation"
QT_MOC_LITERAL(403, 5044, 8), // "isOdroid"
QT_MOC_LITERAL(404, 5053, 13), // "getMultiState"
QT_MOC_LITERAL(405, 5067, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(406, 5087, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(407, 5106, 15), // "getRunawayState"
QT_MOC_LITERAL(408, 5122, 15), // "slam_map_reload"
QT_MOC_LITERAL(409, 5138, 15), // "slam_ini_reload"
QT_MOC_LITERAL(410, 5154, 7), // "setTray"
QT_MOC_LITERAL(411, 5162, 8), // "tray_num"
QT_MOC_LITERAL(412, 5171, 12), // "startServing"
QT_MOC_LITERAL(413, 5184, 9), // "setPreset"
QT_MOC_LITERAL(414, 5194, 6), // "preset"
QT_MOC_LITERAL(415, 5201, 13), // "confirmPickup"
QT_MOC_LITERAL(416, 5215, 14), // "getPickuptrays"
QT_MOC_LITERAL(417, 5230, 10), // "QList<int>"
QT_MOC_LITERAL(418, 5241, 9), // "movePause"
QT_MOC_LITERAL(419, 5251, 10), // "moveResume"
QT_MOC_LITERAL(420, 5262, 12), // "moveStopFlag"
QT_MOC_LITERAL(421, 5275, 8), // "moveStop"
QT_MOC_LITERAL(422, 5284, 12), // "moveToCharge"
QT_MOC_LITERAL(423, 5297, 10), // "moveToWait"
QT_MOC_LITERAL(424, 5308, 14), // "moveToCleaning"
QT_MOC_LITERAL(425, 5323, 9), // "getcurLoc"
QT_MOC_LITERAL(426, 5333, 11), // "getcurTable"
QT_MOC_LITERAL(427, 5345, 16), // "resetHomeFolders"
QT_MOC_LITERAL(428, 5362, 13), // "issetLocation"
QT_MOC_LITERAL(429, 5376, 6), // "number"
QT_MOC_LITERAL(430, 5383, 11), // "getObsState"
QT_MOC_LITERAL(431, 5395, 10), // "getBattery"
QT_MOC_LITERAL(432, 5406, 13), // "getMotorState"
QT_MOC_LITERAL(433, 5420, 20), // "getLocalizationState"
QT_MOC_LITERAL(434, 5441, 14), // "getStateMoving"
QT_MOC_LITERAL(435, 5456, 10), // "getErrcode"
QT_MOC_LITERAL(436, 5467, 12), // "getRobotName"
QT_MOC_LITERAL(437, 5480, 18), // "getMotorConnection"
QT_MOC_LITERAL(438, 5499, 14), // "getMotorStatus"
QT_MOC_LITERAL(439, 5514, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(440, 5532, 19), // "getMotorTemperature"
QT_MOC_LITERAL(441, 5552, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(442, 5578, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(443, 5605, 15), // "getMotorCurrent"
QT_MOC_LITERAL(444, 5621, 14), // "getPowerStatus"
QT_MOC_LITERAL(445, 5636, 15), // "getRemoteStatus"
QT_MOC_LITERAL(446, 5652, 22), // "getChargeConnectStatus"
QT_MOC_LITERAL(447, 5675, 15), // "getChargeStatus"
QT_MOC_LITERAL(448, 5691, 12), // "getEmoStatus"
QT_MOC_LITERAL(449, 5704, 13), // "getLockStatus"
QT_MOC_LITERAL(450, 5718, 12), // "getBatteryIn"
QT_MOC_LITERAL(451, 5731, 13), // "getBatteryOut"
QT_MOC_LITERAL(452, 5745, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(453, 5763, 8), // "getPower"
QT_MOC_LITERAL(454, 5772, 13), // "getPowerTotal"
QT_MOC_LITERAL(455, 5786, 12), // "getObsinPath"
QT_MOC_LITERAL(456, 5799, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(457, 5817, 12), // "setMotorLock"
QT_MOC_LITERAL(458, 5830, 14), // "getRobotRadius"
QT_MOC_LITERAL(459, 5845, 9), // "getRobotx"
QT_MOC_LITERAL(460, 5855, 9), // "getRoboty"
QT_MOC_LITERAL(461, 5865, 10), // "getRobotth"
QT_MOC_LITERAL(462, 5876, 13), // "getlastRobotx"
QT_MOC_LITERAL(463, 5890, 13), // "getlastRoboty"
QT_MOC_LITERAL(464, 5904, 14), // "getlastRobotth"
QT_MOC_LITERAL(465, 5919, 10), // "getPathNum"
QT_MOC_LITERAL(466, 5930, 8), // "getPathx"
QT_MOC_LITERAL(467, 5939, 8), // "getPathy"
QT_MOC_LITERAL(468, 5948, 9), // "getPathth"
QT_MOC_LITERAL(469, 5958, 15), // "getLocalPathNum"
QT_MOC_LITERAL(470, 5974, 13), // "getLocalPathx"
QT_MOC_LITERAL(471, 5988, 13), // "getLocalPathy"
QT_MOC_LITERAL(472, 6002, 10), // "getuistate"
QT_MOC_LITERAL(473, 6013, 10), // "getMapname"
QT_MOC_LITERAL(474, 6024, 10), // "getMappath"
QT_MOC_LITERAL(475, 6035, 11), // "getMapWidth"
QT_MOC_LITERAL(476, 6047, 12), // "getMapHeight"
QT_MOC_LITERAL(477, 6060, 12), // "getGridWidth"
QT_MOC_LITERAL(478, 6073, 9), // "getOrigin"
QT_MOC_LITERAL(479, 6083, 15), // "getMappingWidth"
QT_MOC_LITERAL(480, 6099, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(481, 6119, 17), // "getObjectPointNum"
QT_MOC_LITERAL(482, 6137, 9), // "addObject"
QT_MOC_LITERAL(483, 6147, 14), // "addObjectPoint"
QT_MOC_LITERAL(484, 6162, 9), // "setObject"
QT_MOC_LITERAL(485, 6172, 15), // "editObjectStart"
QT_MOC_LITERAL(486, 6188, 10), // "editObject"
QT_MOC_LITERAL(487, 6199, 10), // "saveObject"
QT_MOC_LITERAL(488, 6210, 11), // "clearObject"
QT_MOC_LITERAL(489, 6222, 14), // "clearObjectAll"
QT_MOC_LITERAL(490, 6237, 12), // "selectObject"
QT_MOC_LITERAL(491, 6250, 13), // "getObjectflag"
QT_MOC_LITERAL(492, 6264, 10), // "undoObject"
QT_MOC_LITERAL(493, 6275, 15), // "clearRotateList"
QT_MOC_LITERAL(494, 6291, 13), // "setRotateList"
QT_MOC_LITERAL(495, 6305, 6), // "pickup"
QT_MOC_LITERAL(496, 6312, 11), // "getICPRatio"
QT_MOC_LITERAL(497, 6324, 11), // "getICPError"
QT_MOC_LITERAL(498, 6336, 13), // "clearFlagStop"
QT_MOC_LITERAL(499, 6350, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(500, 6368, 17), // "moveToServingTest"
QT_MOC_LITERAL(501, 6386, 15), // "getusberrorsize"
QT_MOC_LITERAL(502, 6402, 11), // "getusberror"
QT_MOC_LITERAL(503, 6414, 11), // "getzipstate"
QT_MOC_LITERAL(504, 6426, 10), // "clear_call"
QT_MOC_LITERAL(505, 6437, 7), // "usbsave"
QT_MOC_LITERAL(506, 6445, 3), // "usb"
QT_MOC_LITERAL(507, 6449, 3), // "_ui"
QT_MOC_LITERAL(508, 6453, 5), // "_slam"
QT_MOC_LITERAL(509, 6459, 7), // "_config"
QT_MOC_LITERAL(510, 6467, 4), // "_map"
QT_MOC_LITERAL(511, 6472, 4), // "_log"
QT_MOC_LITERAL(512, 6477, 13), // "restartUpdate"
QT_MOC_LITERAL(513, 6491, 11), // "startUpdate"
QT_MOC_LITERAL(514, 6503, 18), // "getTravellineIssue"
QT_MOC_LITERAL(515, 6522, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(516, 6546, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(517, 6569, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(518, 6591, 24) // "getTravellineIssueBroken"

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
    "getPatrolPassTime\0getPatrolVoice\0"
    "getPatrolVoiceMode\0getPatrolVoiceLanguage\0"
    "isPatrolPage\0getPatrolMovingMode\0"
    "getPatrolArriveMode\0setCurrentPatrol\0"
    "getPatrolLocationSize\0loc\0clearPatrolLocation\0"
    "mode\0addPatrolLocation\0setPatrolMovingPage\0"
    "param1\0param2\0param3\0setPatrolArrivePage\0"
    "setPatrolVoice\0text\0setPatrol\0type\0"
    "wait_time\0pass_time\0savePatrol\0"
    "deletePatrol\0startPatrol\0loadFile\0"
    "setMap\0setFullScreen\0setMapDrawing\0"
    "clicksound\0volume\0playBGM\0stopBGM\0"
    "isplayBGM\0playVoice\0voice\0playVoiceFile\0"
    "file\0makeTTS\0lan\0playTTS\0confirmLocalization\0"
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
    "getDrawingTline\0setRulerPoint\0setBoxPoint\0"
    "getPointBox\0saveRotateMap\0initRotate\0"
    "rotateMap\0angle\0rotateMapCW\0rotateMapCCW\0"
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
    "setTableNumberAuto\0getLocGroupNum\0"
    "saveMap\0saveEditedMap\0saveTline\0"
    "saveTlineTemp\0saveVelmap\0setMapSize\0"
    "height\0zoomIn\0dist\0zoomOut\0move\0"
    "getFileWidth\0getX\0getY\0getScale\0"
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
    "getIniPath\0setSetting\0value\0readSetting\0"
    "map_name\0getSetting\0getTrayNum\0"
    "setTableColNum\0col_num\0getRobotType\0"
    "requestCamera\0getLeftCamera\0getRightCamera\0"
    "setCamera\0left\0right\0getCameraNum\0"
    "getCameraSerial\0setCursorView\0visible\0"
    "getVoice\0checkTravelline\0updateProgram\0"
    "updateProgramGitPull\0checkVersionAgain\0"
    "isNewVersion\0isNeedUpdate\0getLocalVersion\0"
    "getServerVersion\0getLocalVersionDate\0"
    "getLocalVersionMessage\0getServerVersionMessage\0"
    "getUpdateDate\0getUpdateSize\0"
    "getUpdateFileName\0getUpdateCommit\0"
    "getCurrentCommit\0getUpdateMessage\0"
    "getLastUpdateDate\0checkCleaningLocation\0"
    "checkUpdate\0checkNewUpdateProgram\0"
    "setlanguage\0isCallingMode\0goServing\0"
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
    "getChargeConnectStatus\0getChargeStatus\0"
    "getEmoStatus\0getLockStatus\0getBatteryIn\0"
    "getBatteryOut\0getBatteryCurrent\0"
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
    "getObjectPointNum\0addObject\0addObjectPoint\0"
    "setObject\0editObjectStart\0editObject\0"
    "saveObject\0clearObject\0clearObjectAll\0"
    "selectObject\0getObjectflag\0undoObject\0"
    "clearRotateList\0setRotateList\0pickup\0"
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
     488,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 2454,    2, 0x0a /* Public */,
       3,    0, 2455,    2, 0x0a /* Public */,
       4,    0, 2456,    2, 0x0a /* Public */,
       5,    0, 2457,    2, 0x0a /* Public */,
       6,    0, 2458,    2, 0x0a /* Public */,
       7,    0, 2459,    2, 0x0a /* Public */,
       8,    0, 2460,    2, 0x0a /* Public */,
       9,    0, 2461,    2, 0x0a /* Public */,
      10,    1, 2462,    2, 0x0a /* Public */,
      12,    1, 2465,    2, 0x0a /* Public */,
      13,    2, 2468,    2, 0x0a /* Public */,
      15,    1, 2473,    2, 0x0a /* Public */,
      16,    0, 2476,    2, 0x0a /* Public */,
      17,    0, 2477,    2, 0x0a /* Public */,
      18,    0, 2478,    2, 0x0a /* Public */,
      19,    0, 2479,    2, 0x0a /* Public */,
      20,    1, 2480,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      22,    0, 2483,    2, 0x02 /* Public */,
      23,    0, 2484,    2, 0x02 /* Public */,
      24,    2, 2485,    2, 0x02 /* Public */,
      26,    0, 2490,    2, 0x02 /* Public */,
      27,    0, 2491,    2, 0x02 /* Public */,
      28,    1, 2492,    2, 0x02 /* Public */,
      30,    0, 2495,    2, 0x02 /* Public */,
      31,    1, 2496,    2, 0x02 /* Public */,
      33,    2, 2499,    2, 0x02 /* Public */,
      35,    1, 2504,    2, 0x02 /* Public */,
      36,    1, 2507,    2, 0x02 /* Public */,
      37,    1, 2510,    2, 0x02 /* Public */,
      38,    1, 2513,    2, 0x02 /* Public */,
      39,    0, 2516,    2, 0x02 /* Public */,
      40,    0, 2517,    2, 0x02 /* Public */,
      41,    3, 2518,    2, 0x02 /* Public */,
      45,    0, 2525,    2, 0x02 /* Public */,
      46,    0, 2526,    2, 0x02 /* Public */,
      47,    0, 2527,    2, 0x02 /* Public */,
      48,    1, 2528,    2, 0x02 /* Public */,
      49,    1, 2531,    2, 0x02 /* Public */,
      50,    0, 2534,    2, 0x02 /* Public */,
      51,    0, 2535,    2, 0x02 /* Public */,
      52,    0, 2536,    2, 0x02 /* Public */,
      53,    0, 2537,    2, 0x02 /* Public */,
      54,    1, 2538,    2, 0x02 /* Public */,
      55,    1, 2541,    2, 0x02 /* Public */,
      56,    1, 2544,    2, 0x02 /* Public */,
      57,    1, 2547,    2, 0x02 /* Public */,
      58,    1, 2550,    2, 0x02 /* Public */,
      59,    1, 2553,    2, 0x02 /* Public */,
      60,    1, 2556,    2, 0x02 /* Public */,
      61,    1, 2559,    2, 0x02 /* Public */,
      62,    1, 2562,    2, 0x02 /* Public */,
      63,    1, 2565,    2, 0x02 /* Public */,
      64,    0, 2568,    2, 0x02 /* Public */,
      65,    0, 2569,    2, 0x02 /* Public */,
      66,    0, 2570,    2, 0x02 /* Public */,
      67,    1, 2571,    2, 0x02 /* Public */,
      68,    1, 2574,    2, 0x02 /* Public */,
      56,    2, 2577,    2, 0x02 /* Public */,
      70,    1, 2582,    2, 0x02 /* Public */,
      72,    1, 2585,    2, 0x02 /* Public */,
      73,    4, 2588,    2, 0x02 /* Public */,
      73,    3, 2597,    2, 0x22 /* Public | MethodCloned */,
      73,    2, 2604,    2, 0x22 /* Public | MethodCloned */,
      73,    1, 2609,    2, 0x22 /* Public | MethodCloned */,
      77,    4, 2612,    2, 0x02 /* Public */,
      77,    3, 2621,    2, 0x22 /* Public | MethodCloned */,
      77,    2, 2628,    2, 0x22 /* Public | MethodCloned */,
      77,    1, 2633,    2, 0x22 /* Public | MethodCloned */,
      78,    4, 2636,    2, 0x02 /* Public */,
      78,    3, 2645,    2, 0x22 /* Public | MethodCloned */,
      78,    2, 2652,    2, 0x22 /* Public | MethodCloned */,
      78,    1, 2657,    2, 0x22 /* Public | MethodCloned */,
      80,    5, 2660,    2, 0x02 /* Public */,
      84,    4, 2671,    2, 0x02 /* Public */,
      85,    1, 2680,    2, 0x02 /* Public */,
      86,    1, 2683,    2, 0x02 /* Public */,
      87,    2, 2686,    2, 0x02 /* Public */,
      88,    0, 2691,    2, 0x02 /* Public */,
      89,    0, 2692,    2, 0x02 /* Public */,
      90,    0, 2693,    2, 0x02 /* Public */,
      91,    2, 2694,    2, 0x02 /* Public */,
      91,    1, 2699,    2, 0x22 /* Public | MethodCloned */,
      93,    1, 2702,    2, 0x02 /* Public */,
      93,    0, 2705,    2, 0x22 /* Public | MethodCloned */,
      94,    0, 2706,    2, 0x02 /* Public */,
      95,    0, 2707,    2, 0x02 /* Public */,
      96,    2, 2708,    2, 0x02 /* Public */,
      96,    1, 2713,    2, 0x22 /* Public | MethodCloned */,
      96,    3, 2716,    2, 0x02 /* Public */,
      96,    2, 2723,    2, 0x22 /* Public | MethodCloned */,
      98,    2, 2728,    2, 0x02 /* Public */,
      98,    1, 2733,    2, 0x22 /* Public | MethodCloned */,
     100,    2, 2736,    2, 0x02 /* Public */,
     100,    1, 2741,    2, 0x22 /* Public | MethodCloned */,
     102,    0, 2744,    2, 0x02 /* Public */,
     103,    0, 2745,    2, 0x02 /* Public */,
     104,    1, 2746,    2, 0x02 /* Public */,
     105,    1, 2749,    2, 0x02 /* Public */,
     106,    0, 2752,    2, 0x02 /* Public */,
     107,    1, 2753,    2, 0x02 /* Public */,
     108,    1, 2756,    2, 0x02 /* Public */,
     110,    0, 2759,    2, 0x02 /* Public */,
     111,    1, 2760,    2, 0x02 /* Public */,
     113,    1, 2763,    2, 0x02 /* Public */,
     114,    1, 2766,    2, 0x02 /* Public */,
     115,    1, 2769,    2, 0x02 /* Public */,
     116,    1, 2772,    2, 0x02 /* Public */,
     117,    1, 2775,    2, 0x02 /* Public */,
     118,    1, 2778,    2, 0x02 /* Public */,
     119,    1, 2781,    2, 0x02 /* Public */,
     120,    0, 2784,    2, 0x02 /* Public */,
     121,    0, 2785,    2, 0x02 /* Public */,
     122,    0, 2786,    2, 0x02 /* Public */,
     123,    1, 2787,    2, 0x02 /* Public */,
     124,    3, 2790,    2, 0x02 /* Public */,
     128,    0, 2797,    2, 0x02 /* Public */,
     129,    0, 2798,    2, 0x02 /* Public */,
     130,    0, 2799,    2, 0x02 /* Public */,
     131,    0, 2800,    2, 0x02 /* Public */,
     132,    0, 2801,    2, 0x02 /* Public */,
     133,    2, 2802,    2, 0x02 /* Public */,
     134,    3, 2807,    2, 0x02 /* Public */,
     135,    2, 2814,    2, 0x02 /* Public */,
     136,    0, 2819,    2, 0x02 /* Public */,
     137,    0, 2820,    2, 0x02 /* Public */,
     138,    1, 2821,    2, 0x02 /* Public */,
     140,    0, 2824,    2, 0x02 /* Public */,
     141,    0, 2825,    2, 0x02 /* Public */,
     142,    0, 2826,    2, 0x02 /* Public */,
     143,    0, 2827,    2, 0x02 /* Public */,
     144,    0, 2828,    2, 0x02 /* Public */,
     145,    0, 2829,    2, 0x02 /* Public */,
     146,    0, 2830,    2, 0x02 /* Public */,
     147,    2, 2831,    2, 0x02 /* Public */,
     148,    2, 2836,    2, 0x02 /* Public */,
     149,    2, 2841,    2, 0x02 /* Public */,
     150,    1, 2846,    2, 0x02 /* Public */,
     151,    2, 2849,    2, 0x02 /* Public */,
     152,    2, 2854,    2, 0x02 /* Public */,
     153,    0, 2859,    2, 0x02 /* Public */,
     154,    0, 2860,    2, 0x02 /* Public */,
     155,    0, 2861,    2, 0x02 /* Public */,
     156,    0, 2862,    2, 0x02 /* Public */,
     157,    2, 2863,    2, 0x02 /* Public */,
     158,    2, 2868,    2, 0x02 /* Public */,
     159,    0, 2873,    2, 0x02 /* Public */,
     160,    1, 2874,    2, 0x02 /* Public */,
     162,    2, 2877,    2, 0x02 /* Public */,
     163,    2, 2882,    2, 0x02 /* Public */,
     164,    2, 2887,    2, 0x02 /* Public */,
     165,    1, 2892,    2, 0x02 /* Public */,
     167,    1, 2895,    2, 0x02 /* Public */,
     169,    2, 2898,    2, 0x02 /* Public */,
     170,    3, 2903,    2, 0x02 /* Public */,
     172,    0, 2910,    2, 0x02 /* Public */,
     173,    3, 2911,    2, 0x02 /* Public */,
     174,    3, 2918,    2, 0x02 /* Public */,
     175,    3, 2925,    2, 0x02 /* Public */,
     176,    1, 2932,    2, 0x02 /* Public */,
     169,    2, 2935,    2, 0x02 /* Public */,
     177,    1, 2940,    2, 0x02 /* Public */,
     178,    0, 2943,    2, 0x02 /* Public */,
     179,    1, 2944,    2, 0x02 /* Public */,
     180,    0, 2947,    2, 0x02 /* Public */,
     181,    0, 2948,    2, 0x02 /* Public */,
     182,    0, 2949,    2, 0x02 /* Public */,
     183,    0, 2950,    2, 0x02 /* Public */,
     184,    0, 2951,    2, 0x02 /* Public */,
     185,    2, 2952,    2, 0x02 /* Public */,
     187,    3, 2957,    2, 0x02 /* Public */,
     189,    3, 2964,    2, 0x02 /* Public */,
     190,    2, 2971,    2, 0x02 /* Public */,
     191,    0, 2976,    2, 0x02 /* Public */,
     192,    0, 2977,    2, 0x02 /* Public */,
     193,    0, 2978,    2, 0x02 /* Public */,
     194,    0, 2979,    2, 0x02 /* Public */,
     195,    1, 2980,    2, 0x02 /* Public */,
     196,    1, 2983,    2, 0x02 /* Public */,
     197,    1, 2986,    2, 0x02 /* Public */,
     198,    1, 2989,    2, 0x02 /* Public */,
     199,    1, 2992,    2, 0x02 /* Public */,
     200,    1, 2995,    2, 0x02 /* Public */,
     201,    1, 2998,    2, 0x02 /* Public */,
     202,    0, 3001,    2, 0x02 /* Public */,
     203,    3, 3002,    2, 0x02 /* Public */,
     204,    0, 3009,    2, 0x02 /* Public */,
     205,    1, 3010,    2, 0x02 /* Public */,
     206,    1, 3013,    2, 0x02 /* Public */,
     208,    0, 3016,    2, 0x02 /* Public */,
     209,    0, 3017,    2, 0x02 /* Public */,
     210,    0, 3018,    2, 0x02 /* Public */,
     211,    1, 3019,    2, 0x02 /* Public */,
     212,    1, 3022,    2, 0x02 /* Public */,
     213,    0, 3025,    2, 0x02 /* Public */,
     214,    0, 3026,    2, 0x02 /* Public */,
     215,    0, 3027,    2, 0x02 /* Public */,
     216,    0, 3028,    2, 0x02 /* Public */,
     217,    0, 3029,    2, 0x02 /* Public */,
     218,    0, 3030,    2, 0x02 /* Public */,
     219,    0, 3031,    2, 0x02 /* Public */,
     220,    0, 3032,    2, 0x02 /* Public */,
     221,    0, 3033,    2, 0x02 /* Public */,
     222,    0, 3034,    2, 0x02 /* Public */,
     223,    0, 3035,    2, 0x02 /* Public */,
     224,    1, 3036,    2, 0x02 /* Public */,
     225,    1, 3039,    2, 0x02 /* Public */,
     226,    1, 3042,    2, 0x02 /* Public */,
     227,    1, 3045,    2, 0x02 /* Public */,
     228,    1, 3048,    2, 0x02 /* Public */,
     229,    1, 3051,    2, 0x02 /* Public */,
     230,    1, 3054,    2, 0x02 /* Public */,
     231,    3, 3057,    2, 0x02 /* Public */,
     233,    1, 3064,    2, 0x02 /* Public */,
     233,    0, 3067,    2, 0x22 /* Public | MethodCloned */,
     235,    3, 3068,    2, 0x02 /* Public */,
     236,    0, 3075,    2, 0x02 /* Public */,
     237,    1, 3076,    2, 0x02 /* Public */,
     239,    0, 3079,    2, 0x02 /* Public */,
     240,    0, 3080,    2, 0x02 /* Public */,
     241,    0, 3081,    2, 0x02 /* Public */,
     242,    0, 3082,    2, 0x02 /* Public */,
     243,    2, 3083,    2, 0x02 /* Public */,
     246,    0, 3088,    2, 0x02 /* Public */,
     247,    1, 3089,    2, 0x02 /* Public */,
     248,    1, 3092,    2, 0x02 /* Public */,
     250,    2, 3095,    2, 0x02 /* Public */,
     250,    1, 3100,    2, 0x22 /* Public | MethodCloned */,
     251,    0, 3103,    2, 0x02 /* Public */,
     252,    0, 3104,    2, 0x02 /* Public */,
     253,    0, 3105,    2, 0x02 /* Public */,
     254,    0, 3106,    2, 0x02 /* Public */,
     255,    0, 3107,    2, 0x02 /* Public */,
     256,    0, 3108,    2, 0x02 /* Public */,
     257,    0, 3109,    2, 0x02 /* Public */,
     258,    0, 3110,    2, 0x02 /* Public */,
     259,    0, 3111,    2, 0x02 /* Public */,
     260,    0, 3112,    2, 0x02 /* Public */,
     261,    0, 3113,    2, 0x02 /* Public */,
     262,    0, 3114,    2, 0x02 /* Public */,
     263,    0, 3115,    2, 0x02 /* Public */,
     264,    1, 3116,    2, 0x02 /* Public */,
     265,    1, 3119,    2, 0x02 /* Public */,
     266,    1, 3122,    2, 0x02 /* Public */,
     267,    1, 3125,    2, 0x02 /* Public */,
     268,    1, 3128,    2, 0x02 /* Public */,
     269,    0, 3131,    2, 0x02 /* Public */,
     270,    0, 3132,    2, 0x02 /* Public */,
     271,    0, 3133,    2, 0x02 /* Public */,
     272,    1, 3134,    2, 0x02 /* Public */,
     273,    0, 3137,    2, 0x02 /* Public */,
     274,    2, 3138,    2, 0x02 /* Public */,
     276,    1, 3143,    2, 0x02 /* Public */,
     279,    2, 3146,    2, 0x02 /* Public */,
     280,    1, 3151,    2, 0x02 /* Public */,
     279,    1, 3154,    2, 0x02 /* Public */,
     282,    1, 3157,    2, 0x02 /* Public */,
     284,    0, 3160,    2, 0x02 /* Public */,
     285,    1, 3161,    2, 0x02 /* Public */,
     286,    0, 3164,    2, 0x02 /* Public */,
     287,    1, 3165,    2, 0x02 /* Public */,
     288,    1, 3168,    2, 0x02 /* Public */,
     289,    1, 3171,    2, 0x02 /* Public */,
     290,    1, 3174,    2, 0x02 /* Public */,
     291,    1, 3177,    2, 0x02 /* Public */,
     293,    3, 3180,    2, 0x02 /* Public */,
     296,    0, 3187,    2, 0x02 /* Public */,
     297,    0, 3188,    2, 0x02 /* Public */,
     298,    0, 3189,    2, 0x02 /* Public */,
     299,    0, 3190,    2, 0x02 /* Public */,
     300,    1, 3191,    2, 0x02 /* Public */,
     301,    0, 3194,    2, 0x02 /* Public */,
     302,    1, 3195,    2, 0x02 /* Public */,
     303,    0, 3198,    2, 0x02 /* Public */,
     304,    1, 3199,    2, 0x02 /* Public */,
     306,    0, 3202,    2, 0x02 /* Public */,
     307,    0, 3203,    2, 0x02 /* Public */,
     308,    1, 3204,    2, 0x02 /* Public */,
     308,    0, 3207,    2, 0x22 /* Public | MethodCloned */,
     309,    1, 3208,    2, 0x02 /* Public */,
     310,    1, 3211,    2, 0x02 /* Public */,
     310,    0, 3214,    2, 0x22 /* Public | MethodCloned */,
     311,    1, 3215,    2, 0x02 /* Public */,
     311,    0, 3218,    2, 0x22 /* Public | MethodCloned */,
     312,    1, 3219,    2, 0x02 /* Public */,
     312,    0, 3222,    2, 0x22 /* Public | MethodCloned */,
     313,    1, 3223,    2, 0x02 /* Public */,
     313,    0, 3226,    2, 0x22 /* Public | MethodCloned */,
     314,    1, 3227,    2, 0x02 /* Public */,
     315,    1, 3230,    2, 0x02 /* Public */,
     316,    0, 3233,    2, 0x02 /* Public */,
     317,    0, 3234,    2, 0x02 /* Public */,
     318,    1, 3235,    2, 0x02 /* Public */,
     319,    1, 3238,    2, 0x02 /* Public */,
     320,    1, 3241,    2, 0x02 /* Public */,
     321,    0, 3244,    2, 0x02 /* Public */,
     322,    0, 3245,    2, 0x02 /* Public */,
     323,    1, 3246,    2, 0x02 /* Public */,
     325,    1, 3249,    2, 0x02 /* Public */,
     326,    2, 3252,    2, 0x02 /* Public */,
      88,    1, 3257,    2, 0x02 /* Public */,
     329,    3, 3260,    2, 0x02 /* Public */,
     332,    2, 3267,    2, 0x02 /* Public */,
     335,    0, 3272,    2, 0x02 /* Public */,
     336,    1, 3273,    2, 0x02 /* Public */,
     337,    1, 3276,    2, 0x02 /* Public */,
     338,    0, 3279,    2, 0x02 /* Public */,
     339,    3, 3280,    2, 0x02 /* Public */,
     340,    0, 3287,    2, 0x02 /* Public */,
     341,    0, 3288,    2, 0x02 /* Public */,
     342,    0, 3289,    2, 0x02 /* Public */,
     343,    0, 3290,    2, 0x02 /* Public */,
     344,    0, 3291,    2, 0x02 /* Public */,
     345,    0, 3292,    2, 0x02 /* Public */,
     346,    0, 3293,    2, 0x02 /* Public */,
     347,    0, 3294,    2, 0x02 /* Public */,
     348,    0, 3295,    2, 0x02 /* Public */,
     349,    0, 3296,    2, 0x02 /* Public */,
     350,    1, 3297,    2, 0x02 /* Public */,
     352,    0, 3300,    2, 0x02 /* Public */,
     353,    0, 3301,    2, 0x02 /* Public */,
     354,    0, 3302,    2, 0x02 /* Public */,
     355,    0, 3303,    2, 0x02 /* Public */,
     356,    0, 3304,    2, 0x02 /* Public */,
     357,    1, 3305,    2, 0x02 /* Public */,
     358,    0, 3308,    2, 0x02 /* Public */,
     359,    1, 3309,    2, 0x02 /* Public */,
     360,    1, 3312,    2, 0x02 /* Public */,
     361,    2, 3315,    2, 0x02 /* Public */,
     362,    2, 3320,    2, 0x02 /* Public */,
     363,    1, 3325,    2, 0x02 /* Public */,
     365,    0, 3328,    2, 0x02 /* Public */,
     366,    2, 3329,    2, 0x02 /* Public */,
     169,    1, 3334,    2, 0x02 /* Public */,
     169,    0, 3337,    2, 0x22 /* Public | MethodCloned */,
     367,    2, 3338,    2, 0x02 /* Public */,
     367,    1, 3343,    2, 0x22 /* Public | MethodCloned */,
     368,    1, 3346,    2, 0x02 /* Public */,
     369,    2, 3349,    2, 0x02 /* Public */,
     370,    2, 3354,    2, 0x02 /* Public */,
     371,    1, 3359,    2, 0x02 /* Public */,
     372,    1, 3362,    2, 0x02 /* Public */,
     373,    2, 3365,    2, 0x02 /* Public */,
     374,    0, 3370,    2, 0x02 /* Public */,
     375,    1, 3371,    2, 0x02 /* Public */,
     374,    1, 3374,    2, 0x02 /* Public */,
     376,    1, 3377,    2, 0x02 /* Public */,
     377,    2, 3380,    2, 0x02 /* Public */,
     378,    1, 3385,    2, 0x02 /* Public */,
     379,    1, 3388,    2, 0x02 /* Public */,
     380,    1, 3391,    2, 0x02 /* Public */,
     175,    4, 3394,    2, 0x02 /* Public */,
     382,    2, 3403,    2, 0x02 /* Public */,
     382,    1, 3408,    2, 0x22 /* Public | MethodCloned */,
     383,    2, 3411,    2, 0x02 /* Public */,
     383,    1, 3416,    2, 0x22 /* Public | MethodCloned */,
     384,    2, 3419,    2, 0x02 /* Public */,
     384,    1, 3424,    2, 0x22 /* Public | MethodCloned */,
     385,    2, 3427,    2, 0x02 /* Public */,
     386,    1, 3432,    2, 0x02 /* Public */,
     387,    0, 3435,    2, 0x02 /* Public */,
     388,    1, 3436,    2, 0x02 /* Public */,
     389,    0, 3439,    2, 0x02 /* Public */,
     390,    0, 3440,    2, 0x02 /* Public */,
     391,    1, 3441,    2, 0x02 /* Public */,
     392,    1, 3444,    2, 0x02 /* Public */,
     393,    2, 3447,    2, 0x02 /* Public */,
     395,    2, 3452,    2, 0x02 /* Public */,
     396,    3, 3457,    2, 0x02 /* Public */,
     398,    1, 3464,    2, 0x02 /* Public */,
     398,    2, 3467,    2, 0x02 /* Public */,
     399,    0, 3472,    2, 0x02 /* Public */,
     400,    1, 3473,    2, 0x02 /* Public */,
     401,    1, 3476,    2, 0x02 /* Public */,
     402,    1, 3479,    2, 0x02 /* Public */,
     403,    0, 3482,    2, 0x02 /* Public */,
     404,    0, 3483,    2, 0x02 /* Public */,
     405,    0, 3484,    2, 0x02 /* Public */,
     406,    0, 3485,    2, 0x02 /* Public */,
     407,    0, 3486,    2, 0x02 /* Public */,
     408,    2, 3487,    2, 0x02 /* Public */,
     408,    1, 3492,    2, 0x22 /* Public | MethodCloned */,
     409,    0, 3495,    2, 0x02 /* Public */,
     410,    3, 3496,    2, 0x02 /* Public */,
     412,    0, 3503,    2, 0x02 /* Public */,
     413,    1, 3504,    2, 0x02 /* Public */,
     415,    0, 3507,    2, 0x02 /* Public */,
     416,    0, 3508,    2, 0x02 /* Public */,
     418,    0, 3509,    2, 0x02 /* Public */,
     419,    0, 3510,    2, 0x02 /* Public */,
     420,    0, 3511,    2, 0x02 /* Public */,
     421,    0, 3512,    2, 0x02 /* Public */,
     422,    0, 3513,    2, 0x02 /* Public */,
     423,    0, 3514,    2, 0x02 /* Public */,
     424,    0, 3515,    2, 0x02 /* Public */,
     425,    0, 3516,    2, 0x02 /* Public */,
     426,    0, 3517,    2, 0x02 /* Public */,
     427,    0, 3518,    2, 0x02 /* Public */,
     428,    1, 3519,    2, 0x02 /* Public */,
     430,    0, 3522,    2, 0x02 /* Public */,
     431,    0, 3523,    2, 0x02 /* Public */,
     432,    0, 3524,    2, 0x02 /* Public */,
     433,    0, 3525,    2, 0x02 /* Public */,
     434,    0, 3526,    2, 0x02 /* Public */,
     435,    0, 3527,    2, 0x02 /* Public */,
     436,    0, 3528,    2, 0x02 /* Public */,
     437,    1, 3529,    2, 0x02 /* Public */,
     438,    1, 3532,    2, 0x02 /* Public */,
     439,    1, 3535,    2, 0x02 /* Public */,
     440,    1, 3538,    2, 0x02 /* Public */,
     441,    1, 3541,    2, 0x02 /* Public */,
     442,    0, 3544,    2, 0x02 /* Public */,
     443,    1, 3545,    2, 0x02 /* Public */,
     444,    0, 3548,    2, 0x02 /* Public */,
     445,    0, 3549,    2, 0x02 /* Public */,
     446,    0, 3550,    2, 0x02 /* Public */,
     447,    0, 3551,    2, 0x02 /* Public */,
     448,    0, 3552,    2, 0x02 /* Public */,
     449,    0, 3553,    2, 0x02 /* Public */,
     450,    0, 3554,    2, 0x02 /* Public */,
     451,    0, 3555,    2, 0x02 /* Public */,
     452,    0, 3556,    2, 0x02 /* Public */,
     453,    0, 3557,    2, 0x02 /* Public */,
     454,    0, 3558,    2, 0x02 /* Public */,
     455,    0, 3559,    2, 0x02 /* Public */,
     456,    0, 3560,    2, 0x02 /* Public */,
     457,    1, 3561,    2, 0x02 /* Public */,
     458,    0, 3564,    2, 0x02 /* Public */,
     459,    0, 3565,    2, 0x02 /* Public */,
     460,    0, 3566,    2, 0x02 /* Public */,
     461,    0, 3567,    2, 0x02 /* Public */,
     462,    0, 3568,    2, 0x02 /* Public */,
     463,    0, 3569,    2, 0x02 /* Public */,
     464,    0, 3570,    2, 0x02 /* Public */,
     465,    0, 3571,    2, 0x02 /* Public */,
     466,    1, 3572,    2, 0x02 /* Public */,
     467,    1, 3575,    2, 0x02 /* Public */,
     468,    1, 3578,    2, 0x02 /* Public */,
     469,    0, 3581,    2, 0x02 /* Public */,
     470,    1, 3582,    2, 0x02 /* Public */,
     471,    1, 3585,    2, 0x02 /* Public */,
     472,    0, 3588,    2, 0x02 /* Public */,
     473,    0, 3589,    2, 0x02 /* Public */,
     474,    0, 3590,    2, 0x02 /* Public */,
     475,    0, 3591,    2, 0x02 /* Public */,
     476,    0, 3592,    2, 0x02 /* Public */,
     477,    0, 3593,    2, 0x02 /* Public */,
     478,    0, 3594,    2, 0x02 /* Public */,
     479,    0, 3595,    2, 0x02 /* Public */,
     480,    0, 3596,    2, 0x02 /* Public */,
     390,    2, 3597,    2, 0x02 /* Public */,
     481,    2, 3602,    2, 0x02 /* Public */,
     482,    2, 3607,    2, 0x02 /* Public */,
     483,    2, 3612,    2, 0x02 /* Public */,
     484,    2, 3617,    2, 0x02 /* Public */,
     485,    2, 3622,    2, 0x02 /* Public */,
     486,    2, 3627,    2, 0x02 /* Public */,
     487,    0, 3632,    2, 0x02 /* Public */,
     488,    0, 3633,    2, 0x02 /* Public */,
     489,    0, 3634,    2, 0x02 /* Public */,
     490,    1, 3635,    2, 0x02 /* Public */,
     491,    0, 3638,    2, 0x02 /* Public */,
     492,    0, 3639,    2, 0x02 /* Public */,
     493,    0, 3640,    2, 0x02 /* Public */,
     494,    1, 3641,    2, 0x02 /* Public */,
      86,    2, 3644,    2, 0x02 /* Public */,
     496,    0, 3649,    2, 0x02 /* Public */,
     497,    0, 3650,    2, 0x02 /* Public */,
     498,    0, 3651,    2, 0x02 /* Public */,
     499,    0, 3652,    2, 0x02 /* Public */,
     500,    2, 3653,    2, 0x02 /* Public */,
     501,    0, 3658,    2, 0x02 /* Public */,
     502,    1, 3659,    2, 0x02 /* Public */,
     503,    0, 3662,    2, 0x02 /* Public */,
     504,    0, 3663,    2, 0x02 /* Public */,
     505,    6, 3664,    2, 0x02 /* Public */,
     505,    5, 3677,    2, 0x22 /* Public | MethodCloned */,
     505,    4, 3688,    2, 0x22 /* Public | MethodCloned */,
     505,    3, 3697,    2, 0x22 /* Public | MethodCloned */,
     505,    2, 3704,    2, 0x22 /* Public | MethodCloned */,
     505,    1, 3709,    2, 0x22 /* Public | MethodCloned */,
     505,    0, 3712,    2, 0x22 /* Public | MethodCloned */,
     512,    0, 3713,    2, 0x02 /* Public */,
     513,    0, 3714,    2, 0x02 /* Public */,
     514,    0, 3715,    2, 0x02 /* Public */,
     515,    1, 3716,    2, 0x02 /* Public */,
     516,    1, 3719,    2, 0x02 /* Public */,
     517,    1, 3722,    2, 0x02 /* Public */,
     518,    1, 3725,    2, 0x02 /* Public */,

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
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   32,   69,
    QMetaType::Void, QMetaType::QString,   71,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   71,   74,   75,   76,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   71,   74,   75,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   71,   74,
    QMetaType::Void, QMetaType::QString,   71,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   71,   74,   75,   76,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   71,   74,   75,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   71,   74,
    QMetaType::Void, QMetaType::QString,   71,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   79,   74,   75,   76,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   79,   74,   75,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   79,   74,
    QMetaType::Void, QMetaType::QString,   79,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   32,   21,   81,   82,   83,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   21,   81,   82,   83,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   81,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   71,   92,
    QMetaType::Void, QMetaType::QString,   71,
    QMetaType::Void, QMetaType::Int,   92,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   97,   92,
    QMetaType::Void, QMetaType::QString,   97,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,   97,   79,   92,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   97,   79,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   99,   92,
    QMetaType::Void, QMetaType::QString,   99,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   79,  101,
    QMetaType::Void, QMetaType::QString,   79,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Bool,  109,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  127,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,  125,  126,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  139,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::QString,   81,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  161,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int,  166,
    QMetaType::Void, QMetaType::Int,  168,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   25,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   81,  171,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  127,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  127,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  127,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  168,  186,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  188,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  188,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Bool,  112,
    QMetaType::Void, QMetaType::Int,   92,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  168,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString,  207,
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
    QMetaType::QString, QMetaType::QString,   99,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   99,   21,  232,
    QMetaType::Void, QMetaType::QString,  234,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   99,   25,   21,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  238,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  244,  245,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   21,   71,
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
    QMetaType::Void, QMetaType::QString,  101,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,  275,
    0x80000000 | 277, QMetaType::QString,  278,
    0x80000000 | 277, QMetaType::Int, QMetaType::QString,   25,   21,
    0x80000000 | 277, QMetaType::Int,  281,
    0x80000000 | 277, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Int,  283,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QDateTime,  292,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  294,  295,  292,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  305,
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
    QMetaType::Void, QMetaType::QString,  324,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  327,  328,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  330,  331,   71,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  333,  334,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   71,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  125,  126,  127,
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
    QMetaType::Void, QMetaType::Bool,  351,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  281,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  281,
    0x80000000 | 277, QMetaType::QString,  281,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   81,  281,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   81,  112,
    QMetaType::Void, QMetaType::Bool,  364,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Int, QMetaType::QString,   81,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   32,   81,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   21,   32,
    QMetaType::Int, QMetaType::QString,   81,
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
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   32,   21,   25,  381,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   81,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   81,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   81,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  351,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  394,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  394,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  397,  125,  126,
    QMetaType::Int, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   81,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::QString,  324,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  324,   71,
    QMetaType::Void, QMetaType::QString,  324,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  411,   25,  275,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  414,
    QMetaType::Void,
    0x80000000 | 417,
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
    QMetaType::Bool, QMetaType::Int,  429,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  281,
    QMetaType::Int, QMetaType::Int,  281,
    QMetaType::QString, QMetaType::Int,  281,
    QMetaType::Int, QMetaType::Int,  281,
    QMetaType::Int, QMetaType::Int,  281,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  281,
    QMetaType::Int,
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
    QMetaType::Void, QMetaType::Bool,  112,
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
    0x80000000 | 417,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  125,  126,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   71,  495,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   25,   21,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  506,  507,  508,  509,  510,  511,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  506,  507,  508,  509,  510,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  506,  507,  508,  509,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  506,  507,  508,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  506,  507,
    QMetaType::Void, QMetaType::QString,  506,
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
        case 48: { int _r = _t->getPatrolPassTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 49: { QString _r = _t->getPatrolVoice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 50: { QString _r = _t->getPatrolVoiceMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 51: { QString _r = _t->getPatrolVoiceLanguage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 52: { bool _r = _t->isPatrolPage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 53: { QString _r = _t->getPatrolMovingMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 54: { QString _r = _t->getPatrolArriveMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 55: _t->setCurrentPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 56: { int _r = _t->getPatrolLocationSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 57: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 58: _t->clearPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 59: _t->addPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 60: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 61: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 62: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 63: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 64: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 65: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 66: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 67: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 68: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 69: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 70: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 71: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 72: _t->setPatrol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 73: _t->savePatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 74: _t->deletePatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 75: _t->startPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 77: _t->setMap(); break;
        case 78: _t->setFullScreen(); break;
        case 79: _t->setMapDrawing(); break;
        case 80: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 81: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 82: _t->playBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 83: _t->playBGM(); break;
        case 84: _t->stopBGM(); break;
        case 85: { bool _r = _t->isplayBGM();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 86: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 87: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 88: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 89: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 90: _t->playVoiceFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 91: _t->playVoiceFile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 92: _t->makeTTS((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 93: _t->makeTTS((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 94: _t->playTTS(); break;
        case 95: _t->confirmLocalization(); break;
        case 96: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 97: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 98: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 99: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 100: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 101: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 102: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 103: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 104: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 105: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 106: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 107: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 108: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 109: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 110: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 111: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 112: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 113: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 114: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 115: _t->clearInitPose(); break;
        case 116: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 117: _t->startDrawingTline(); break;
        case 118: _t->stopDrawingTline(); break;
        case 119: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 120: _t->setRulerPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 121: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 122: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 123: _t->saveRotateMap(); break;
        case 124: _t->initRotate(); break;
        case 125: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 126: _t->rotateMapCW(); break;
        case 127: _t->rotateMapCCW(); break;
        case 128: _t->saveObjectPNG(); break;
        case 129: _t->saveObsAreaPNG(); break;
        case 130: { int _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 131: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 132: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 133: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 134: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 135: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 136: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 137: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 138: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 139: _t->endDrawingRect(); break;
        case 140: _t->clearDrawing(); break;
        case 141: _t->undoLine(); break;
        case 142: _t->redoLine(); break;
        case 143: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 144: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 145: _t->drawSpline(); break;
        case 146: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 147: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 148: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 149: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 150: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 151: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 152: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 153: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 154: _t->clearLocation(); break;
        case 155: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 156: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 157: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 158: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 159: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 160: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 161: _t->setTableNumberAuto(); break;
        case 162: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 163: _t->saveMap(); break;
        case 164: _t->saveEditedMap(); break;
        case 165: _t->saveTline(); break;
        case 166: _t->saveTlineTemp(); break;
        case 167: _t->saveVelmap(); break;
        case 168: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 169: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 170: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 171: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 172: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 173: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 174: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 175: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 176: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 177: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 178: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 179: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 180: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 181: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 182: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 183: _t->requestSystemVolume(); break;
        case 184: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 185: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 186: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 187: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 188: _t->startDrawingObject(); break;
        case 189: _t->stopDrawingObject(); break;
        case 190: _t->saveDrawingObject(); break;
        case 191: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 192: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 193: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 194: _t->killSLAM(); break;
        case 195: _t->makeRobotINI(); break;
        case 196: _t->checkRobotINI(); break;
        case 197: _t->restartSLAM(); break;
        case 198: _t->startSLAM(); break;
        case 199: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 200: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 201: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 202: _t->programRestart(); break;
        case 203: _t->programExit(); break;
        case 204: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 205: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 206: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 207: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 208: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 209: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 210: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 211: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 212: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 213: _t->readSetting(); break;
        case 214: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 215: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 216: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 217: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 218: _t->requestCamera(); break;
        case 219: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 220: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 221: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 222: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 223: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 224: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 225: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 226: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 227: _t->checkTravelline(); break;
        case 228: _t->updateProgram(); break;
        case 229: _t->updateProgramGitPull(); break;
        case 230: _t->checkVersionAgain(); break;
        case 231: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 232: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 233: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 234: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 235: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 236: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 237: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 238: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 239: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 240: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 241: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 242: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 243: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 244: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 245: _t->checkCleaningLocation(); break;
        case 246: _t->checkUpdate(); break;
        case 247: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 248: _t->setlanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 249: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 250: _t->goServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 251: { LOCATION _r = _t->getLocationbyCall((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 252: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 253: { LOCATION _r = _t->getLocationbyID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 254: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 255: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 256: _t->resetLocalization(); break;
        case 257: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 258: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 259: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 260: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 261: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 262: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 263: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 264: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 265: _t->updateUSB(); break;
        case 266: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 267: _t->readusbrecentfile(); break;
        case 268: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 269: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 270: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 271: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 272: _t->readusb(); break;
        case 273: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 274: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 275: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 276: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 277: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 278: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 279: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 280: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 281: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 282: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 283: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 284: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 285: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 286: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 287: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 288: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 289: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 290: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 291: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 292: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 293: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 294: _t->deleteEditedMap(); break;
        case 295: _t->deleteAnnotation(); break;
        case 296: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 297: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 298: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 299: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 300: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 301: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 302: _t->stopMapping(); break;
        case 303: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 304: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 305: _t->setInitCurPos(); break;
        case 306: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 307: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 308: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 309: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 310: _t->slam_setInit(); break;
        case 311: _t->slam_run(); break;
        case 312: _t->slam_stop(); break;
        case 313: _t->slam_autoInit(); break;
        case 314: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 315: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 316: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 317: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 318: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 319: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 320: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 321: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 322: _t->cleanTray(); break;
        case 323: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 324: _t->clearCallQueue(); break;
        case 325: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 326: { LOCATION _r = _t->getCallLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 327: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 328: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 329: _t->acceptCall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 330: _t->setObjPose(); break;
        case 331: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 332: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 333: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 334: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 335: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 336: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 337: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 338: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 339: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 340: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 341: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 342: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 343: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 344: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 345: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 346: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 347: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 348: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 349: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 350: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 351: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 352: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 353: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 354: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 355: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 356: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 357: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 358: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 359: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 360: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 361: _t->clearSharedMemory(); break;
        case 362: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 363: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 364: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 365: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 366: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 367: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 368: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 369: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 370: _t->saveLocations(); break;
        case 371: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 372: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 373: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 374: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 375: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 376: _t->drawingRunawayStart(); break;
        case 377: _t->drawingRunawayStop(); break;
        case 378: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 379: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 380: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 381: _t->slam_ini_reload(); break;
        case 382: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 383: _t->startServing(); break;
        case 384: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 385: _t->confirmPickup(); break;
        case 386: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 387: _t->movePause(); break;
        case 388: _t->moveResume(); break;
        case 389: _t->moveStopFlag(); break;
        case 390: _t->moveStop(); break;
        case 391: _t->moveToCharge(); break;
        case 392: _t->moveToWait(); break;
        case 393: _t->moveToCleaning(); break;
        case 394: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 395: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 396: _t->resetHomeFolders(); break;
        case 397: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 398: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 399: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 400: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 401: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 402: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 403: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 404: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 405: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 406: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 407: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 408: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 409: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 410: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 411: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 412: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 413: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 414: { int _r = _t->getChargeConnectStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 415: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 416: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 417: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 418: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 419: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 420: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 421: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 422: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 423: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 424: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 425: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 426: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 427: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 428: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 429: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 430: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 431: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 432: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 433: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 434: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 435: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 436: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 437: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 438: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 439: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 440: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 441: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 442: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 443: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 444: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 445: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 446: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 447: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 448: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 449: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 450: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 451: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 452: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 453: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 454: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 455: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 456: _t->saveObject(); break;
        case 457: _t->clearObject(); break;
        case 458: _t->clearObjectAll(); break;
        case 459: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 460: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 461: _t->undoObject(); break;
        case 462: _t->clearRotateList(); break;
        case 463: _t->setRotateList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 464: _t->startPatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 465: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 466: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 467: _t->clearFlagStop(); break;
        case 468: _t->slam_fullautoInit(); break;
        case 469: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 470: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 471: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 472: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 473: _t->clear_call(); break;
        case 474: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 475: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 476: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 477: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 478: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 479: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 480: _t->usbsave(); break;
        case 481: _t->restartUpdate(); break;
        case 482: _t->startUpdate(); break;
        case 483: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 484: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 485: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 486: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 487: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
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
        if (_id < 488)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 488;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 488)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 488;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
