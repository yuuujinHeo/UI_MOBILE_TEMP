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
    QByteArrayData data[487];
    char stringdata0[6151];
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
QT_MOC_LITERAL(52, 582, 8), // "loadFile"
QT_MOC_LITERAL(53, 591, 4), // "type"
QT_MOC_LITERAL(54, 596, 6), // "setMap"
QT_MOC_LITERAL(55, 603, 7), // "moveMap"
QT_MOC_LITERAL(56, 611, 13), // "setFullScreen"
QT_MOC_LITERAL(57, 625, 13), // "setMapDrawing"
QT_MOC_LITERAL(58, 639, 10), // "clicksound"
QT_MOC_LITERAL(59, 650, 4), // "mode"
QT_MOC_LITERAL(60, 655, 6), // "volume"
QT_MOC_LITERAL(61, 662, 7), // "playBGM"
QT_MOC_LITERAL(62, 670, 7), // "stopBGM"
QT_MOC_LITERAL(63, 678, 9), // "isplayBGM"
QT_MOC_LITERAL(64, 688, 9), // "playVoice"
QT_MOC_LITERAL(65, 698, 5), // "voice"
QT_MOC_LITERAL(66, 704, 19), // "confirmLocalization"
QT_MOC_LITERAL(67, 724, 7), // "setName"
QT_MOC_LITERAL(68, 732, 7), // "setTool"
QT_MOC_LITERAL(69, 740, 7), // "getTool"
QT_MOC_LITERAL(70, 748, 7), // "setMode"
QT_MOC_LITERAL(71, 756, 9), // "setEnable"
QT_MOC_LITERAL(72, 766, 2), // "en"
QT_MOC_LITERAL(73, 769, 7), // "getMode"
QT_MOC_LITERAL(74, 777, 12), // "setShowBrush"
QT_MOC_LITERAL(75, 790, 5), // "onoff"
QT_MOC_LITERAL(76, 796, 12), // "setShowLidar"
QT_MOC_LITERAL(77, 809, 15), // "setShowLocation"
QT_MOC_LITERAL(78, 825, 17), // "setRobotFollowing"
QT_MOC_LITERAL(79, 843, 17), // "setShowTravelline"
QT_MOC_LITERAL(80, 861, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(81, 880, 13), // "setShowObject"
QT_MOC_LITERAL(82, 894, 11), // "setInitFlag"
QT_MOC_LITERAL(83, 906, 15), // "getshowLocation"
QT_MOC_LITERAL(84, 922, 17), // "getRobotFollowing"
QT_MOC_LITERAL(85, 940, 12), // "getShowLidar"
QT_MOC_LITERAL(86, 953, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(87, 969, 11), // "setInitPose"
QT_MOC_LITERAL(88, 981, 1), // "x"
QT_MOC_LITERAL(89, 983, 1), // "y"
QT_MOC_LITERAL(90, 985, 2), // "th"
QT_MOC_LITERAL(91, 988, 13), // "clearInitPose"
QT_MOC_LITERAL(92, 1002, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(93, 1023, 17), // "startDrawingTline"
QT_MOC_LITERAL(94, 1041, 16), // "stopDrawingTline"
QT_MOC_LITERAL(95, 1058, 15), // "getDrawingTline"
QT_MOC_LITERAL(96, 1074, 11), // "setBoxPoint"
QT_MOC_LITERAL(97, 1086, 11), // "getPointBox"
QT_MOC_LITERAL(98, 1098, 13), // "saveRotateMap"
QT_MOC_LITERAL(99, 1112, 10), // "initRotate"
QT_MOC_LITERAL(100, 1123, 9), // "rotateMap"
QT_MOC_LITERAL(101, 1133, 5), // "angle"
QT_MOC_LITERAL(102, 1139, 11), // "rotateMapCW"
QT_MOC_LITERAL(103, 1151, 12), // "rotateMapCCW"
QT_MOC_LITERAL(104, 1164, 13), // "saveObjectPNG"
QT_MOC_LITERAL(105, 1178, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(106, 1193, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(107, 1216, 14), // "getDrawingFlag"
QT_MOC_LITERAL(108, 1231, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(109, 1250, 12), // "startDrawing"
QT_MOC_LITERAL(110, 1263, 12), // "addLinePoint"
QT_MOC_LITERAL(111, 1276, 10), // "endDrawing"
QT_MOC_LITERAL(112, 1287, 10), // "setMapOrin"
QT_MOC_LITERAL(113, 1298, 16), // "startDrawingRect"
QT_MOC_LITERAL(114, 1315, 14), // "setDrawingRect"
QT_MOC_LITERAL(115, 1330, 14), // "endDrawingRect"
QT_MOC_LITERAL(116, 1345, 12), // "clearDrawing"
QT_MOC_LITERAL(117, 1358, 8), // "undoLine"
QT_MOC_LITERAL(118, 1367, 8), // "redoLine"
QT_MOC_LITERAL(119, 1376, 11), // "startSpline"
QT_MOC_LITERAL(120, 1388, 9), // "addSpline"
QT_MOC_LITERAL(121, 1398, 10), // "drawSpline"
QT_MOC_LITERAL(122, 1409, 9), // "endSpline"
QT_MOC_LITERAL(123, 1419, 4), // "save"
QT_MOC_LITERAL(124, 1424, 16), // "startDrawingLine"
QT_MOC_LITERAL(125, 1441, 14), // "setDrawingLine"
QT_MOC_LITERAL(126, 1456, 15), // "stopDrawingLine"
QT_MOC_LITERAL(127, 1472, 12), // "setLineColor"
QT_MOC_LITERAL(128, 1485, 5), // "color"
QT_MOC_LITERAL(129, 1491, 12), // "setLineWidth"
QT_MOC_LITERAL(130, 1504, 5), // "width"
QT_MOC_LITERAL(131, 1510, 14), // "getLocationNum"
QT_MOC_LITERAL(132, 1525, 12), // "saveLocation"
QT_MOC_LITERAL(133, 1538, 8), // "groupnum"
QT_MOC_LITERAL(134, 1547, 13), // "clearLocation"
QT_MOC_LITERAL(135, 1561, 11), // "addLocation"
QT_MOC_LITERAL(136, 1573, 14), // "addLocationCur"
QT_MOC_LITERAL(137, 1588, 11), // "setLocation"
QT_MOC_LITERAL(138, 1600, 12), // "editLocation"
QT_MOC_LITERAL(139, 1613, 14), // "removeLocation"
QT_MOC_LITERAL(140, 1628, 20), // "getLocationAvailable"
QT_MOC_LITERAL(141, 1649, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(142, 1668, 14), // "getLocGroupNum"
QT_MOC_LITERAL(143, 1683, 7), // "saveMap"
QT_MOC_LITERAL(144, 1691, 13), // "saveEditedMap"
QT_MOC_LITERAL(145, 1705, 9), // "saveTline"
QT_MOC_LITERAL(146, 1715, 13), // "saveTlineTemp"
QT_MOC_LITERAL(147, 1729, 10), // "saveVelmap"
QT_MOC_LITERAL(148, 1740, 10), // "setMapSize"
QT_MOC_LITERAL(149, 1751, 6), // "height"
QT_MOC_LITERAL(150, 1758, 6), // "zoomIn"
QT_MOC_LITERAL(151, 1765, 4), // "dist"
QT_MOC_LITERAL(152, 1770, 7), // "zoomOut"
QT_MOC_LITERAL(153, 1778, 4), // "move"
QT_MOC_LITERAL(154, 1783, 12), // "getFileWidth"
QT_MOC_LITERAL(155, 1796, 4), // "getX"
QT_MOC_LITERAL(156, 1801, 4), // "getY"
QT_MOC_LITERAL(157, 1806, 8), // "getScale"
QT_MOC_LITERAL(158, 1815, 13), // "setVelmapView"
QT_MOC_LITERAL(159, 1829, 12), // "setTlineView"
QT_MOC_LITERAL(160, 1842, 13), // "setObjectView"
QT_MOC_LITERAL(161, 1856, 15), // "setAvoidmapView"
QT_MOC_LITERAL(162, 1872, 15), // "setLocationView"
QT_MOC_LITERAL(163, 1888, 12), // "setRobotView"
QT_MOC_LITERAL(164, 1901, 15), // "setSystemVolume"
QT_MOC_LITERAL(165, 1917, 19), // "requestSystemVolume"
QT_MOC_LITERAL(166, 1937, 7), // "setSize"
QT_MOC_LITERAL(167, 1945, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(168, 1959, 14), // "selectLocation"
QT_MOC_LITERAL(169, 1974, 8), // "writelog"
QT_MOC_LITERAL(170, 1983, 3), // "msg"
QT_MOC_LITERAL(171, 1987, 18), // "startDrawingObject"
QT_MOC_LITERAL(172, 2006, 17), // "stopDrawingObject"
QT_MOC_LITERAL(173, 2024, 17), // "saveDrawingObject"
QT_MOC_LITERAL(174, 2042, 13), // "setLocationUp"
QT_MOC_LITERAL(175, 2056, 15), // "setLocationDown"
QT_MOC_LITERAL(176, 2072, 8), // "checkINI"
QT_MOC_LITERAL(177, 2081, 8), // "killSLAM"
QT_MOC_LITERAL(178, 2090, 12), // "makeRobotINI"
QT_MOC_LITERAL(179, 2103, 13), // "checkRobotINI"
QT_MOC_LITERAL(180, 2117, 11), // "restartSLAM"
QT_MOC_LITERAL(181, 2129, 9), // "startSLAM"
QT_MOC_LITERAL(182, 2139, 16), // "getIPCConnection"
QT_MOC_LITERAL(183, 2156, 8), // "getIPCRX"
QT_MOC_LITERAL(184, 2165, 8), // "getIPCTX"
QT_MOC_LITERAL(185, 2174, 14), // "programRestart"
QT_MOC_LITERAL(186, 2189, 11), // "programExit"
QT_MOC_LITERAL(187, 2201, 13), // "getRawMapPath"
QT_MOC_LITERAL(188, 2215, 10), // "getMapPath"
QT_MOC_LITERAL(189, 2226, 12), // "getAnnotPath"
QT_MOC_LITERAL(190, 2239, 11), // "getMetaPath"
QT_MOC_LITERAL(191, 2251, 13), // "getTravelPath"
QT_MOC_LITERAL(192, 2265, 11), // "getCostPath"
QT_MOC_LITERAL(193, 2277, 10), // "getIniPath"
QT_MOC_LITERAL(194, 2288, 4), // "file"
QT_MOC_LITERAL(195, 2293, 10), // "setSetting"
QT_MOC_LITERAL(196, 2304, 5), // "value"
QT_MOC_LITERAL(197, 2310, 11), // "readSetting"
QT_MOC_LITERAL(198, 2322, 8), // "map_name"
QT_MOC_LITERAL(199, 2331, 10), // "getSetting"
QT_MOC_LITERAL(200, 2342, 10), // "getTrayNum"
QT_MOC_LITERAL(201, 2353, 14), // "setTableColNum"
QT_MOC_LITERAL(202, 2368, 7), // "col_num"
QT_MOC_LITERAL(203, 2376, 12), // "getRobotType"
QT_MOC_LITERAL(204, 2389, 13), // "requestCamera"
QT_MOC_LITERAL(205, 2403, 13), // "getLeftCamera"
QT_MOC_LITERAL(206, 2417, 14), // "getRightCamera"
QT_MOC_LITERAL(207, 2432, 9), // "setCamera"
QT_MOC_LITERAL(208, 2442, 4), // "left"
QT_MOC_LITERAL(209, 2447, 5), // "right"
QT_MOC_LITERAL(210, 2453, 12), // "getCameraNum"
QT_MOC_LITERAL(211, 2466, 15), // "getCameraSerial"
QT_MOC_LITERAL(212, 2482, 13), // "setCursorView"
QT_MOC_LITERAL(213, 2496, 7), // "visible"
QT_MOC_LITERAL(214, 2504, 8), // "getVoice"
QT_MOC_LITERAL(215, 2513, 15), // "checkTravelline"
QT_MOC_LITERAL(216, 2529, 13), // "updateProgram"
QT_MOC_LITERAL(217, 2543, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(218, 2564, 17), // "checkVersionAgain"
QT_MOC_LITERAL(219, 2582, 12), // "isNewVersion"
QT_MOC_LITERAL(220, 2595, 12), // "isNeedUpdate"
QT_MOC_LITERAL(221, 2608, 15), // "getLocalVersion"
QT_MOC_LITERAL(222, 2624, 16), // "getServerVersion"
QT_MOC_LITERAL(223, 2641, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(224, 2661, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(225, 2684, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(226, 2708, 13), // "getUpdateDate"
QT_MOC_LITERAL(227, 2722, 13), // "getUpdateSize"
QT_MOC_LITERAL(228, 2736, 17), // "getUpdateFileName"
QT_MOC_LITERAL(229, 2754, 15), // "getUpdateCommit"
QT_MOC_LITERAL(230, 2770, 16), // "getCurrentCommit"
QT_MOC_LITERAL(231, 2787, 16), // "getUpdateMessage"
QT_MOC_LITERAL(232, 2804, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(233, 2822, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(234, 2844, 11), // "checkUpdate"
QT_MOC_LITERAL(235, 2856, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(236, 2878, 11), // "setlanguage"
QT_MOC_LITERAL(237, 2890, 3), // "lan"
QT_MOC_LITERAL(238, 2894, 13), // "isCallingMode"
QT_MOC_LITERAL(239, 2908, 9), // "goServing"
QT_MOC_LITERAL(240, 2918, 5), // "table"
QT_MOC_LITERAL(241, 2924, 17), // "getLocationbyCall"
QT_MOC_LITERAL(242, 2942, 8), // "LOCATION"
QT_MOC_LITERAL(243, 2951, 4), // "call"
QT_MOC_LITERAL(244, 2956, 11), // "getLocation"
QT_MOC_LITERAL(245, 2968, 15), // "getLocationbyID"
QT_MOC_LITERAL(246, 2984, 2), // "id"
QT_MOC_LITERAL(247, 2987, 10), // "setUiState"
QT_MOC_LITERAL(248, 2998, 5), // "state"
QT_MOC_LITERAL(249, 3004, 17), // "resetLocalization"
QT_MOC_LITERAL(250, 3022, 6), // "setLog"
QT_MOC_LITERAL(251, 3029, 13), // "getLogLineNum"
QT_MOC_LITERAL(252, 3043, 10), // "getLogLine"
QT_MOC_LITERAL(253, 3054, 10), // "getLogDate"
QT_MOC_LITERAL(254, 3065, 10), // "getLogAuth"
QT_MOC_LITERAL(255, 3076, 13), // "getLogMessage"
QT_MOC_LITERAL(256, 3090, 7), // "readLog"
QT_MOC_LITERAL(257, 3098, 4), // "date"
QT_MOC_LITERAL(258, 3103, 13), // "getLocaleDate"
QT_MOC_LITERAL(259, 3117, 4), // "year"
QT_MOC_LITERAL(260, 3122, 5), // "month"
QT_MOC_LITERAL(261, 3128, 9), // "updateUSB"
QT_MOC_LITERAL(262, 3138, 10), // "getusbsize"
QT_MOC_LITERAL(263, 3149, 17), // "readusbrecentfile"
QT_MOC_LITERAL(264, 3167, 14), // "getusbfilesize"
QT_MOC_LITERAL(265, 3182, 10), // "getusbfile"
QT_MOC_LITERAL(266, 3193, 16), // "getusbrecentfile"
QT_MOC_LITERAL(267, 3210, 10), // "getusbname"
QT_MOC_LITERAL(268, 3221, 7), // "readusb"
QT_MOC_LITERAL(269, 3229, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(270, 3244, 4), // "path"
QT_MOC_LITERAL(271, 3249, 15), // "isConnectServer"
QT_MOC_LITERAL(272, 3265, 9), // "isLoadMap"
QT_MOC_LITERAL(273, 3275, 10), // "isExistMap"
QT_MOC_LITERAL(274, 3286, 13), // "isExistRawMap"
QT_MOC_LITERAL(275, 3300, 15), // "isExistTlineMap"
QT_MOC_LITERAL(276, 3316, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(277, 3332, 13), // "isExistVelMap"
QT_MOC_LITERAL(278, 3346, 16), // "isExistObjectMap"
QT_MOC_LITERAL(279, 3363, 16), // "isExistTravelMap"
QT_MOC_LITERAL(280, 3380, 17), // "isExistAnnotation"
QT_MOC_LITERAL(281, 3398, 15), // "isExistRobotINI"
QT_MOC_LITERAL(282, 3414, 15), // "getAvailableMap"
QT_MOC_LITERAL(283, 3430, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(284, 3450, 14), // "getMapFileSize"
QT_MOC_LITERAL(285, 3465, 10), // "getMapFile"
QT_MOC_LITERAL(286, 3476, 15), // "deleteEditedMap"
QT_MOC_LITERAL(287, 3492, 16), // "deleteAnnotation"
QT_MOC_LITERAL(288, 3509, 9), // "removeMap"
QT_MOC_LITERAL(289, 3519, 8), // "filename"
QT_MOC_LITERAL(290, 3528, 7), // "loadMap"
QT_MOC_LITERAL(291, 3536, 7), // "copyMap"
QT_MOC_LITERAL(292, 3544, 8), // "orinname"
QT_MOC_LITERAL(293, 3553, 7), // "newname"
QT_MOC_LITERAL(294, 3561, 10), // "rotate_map"
QT_MOC_LITERAL(295, 3572, 4), // "_src"
QT_MOC_LITERAL(296, 3577, 4), // "_dst"
QT_MOC_LITERAL(297, 3582, 12), // "startMapping"
QT_MOC_LITERAL(298, 3595, 7), // "mapsize"
QT_MOC_LITERAL(299, 3603, 4), // "grid"
QT_MOC_LITERAL(300, 3608, 11), // "stopMapping"
QT_MOC_LITERAL(301, 3620, 11), // "setSLAMMode"
QT_MOC_LITERAL(302, 3632, 11), // "saveMapping"
QT_MOC_LITERAL(303, 3644, 13), // "setInitCurPos"
QT_MOC_LITERAL(304, 3658, 10), // "setInitPos"
QT_MOC_LITERAL(305, 3669, 12), // "getInitPoseX"
QT_MOC_LITERAL(306, 3682, 12), // "getInitPoseY"
QT_MOC_LITERAL(307, 3695, 13), // "getInitPoseTH"
QT_MOC_LITERAL(308, 3709, 12), // "slam_setInit"
QT_MOC_LITERAL(309, 3722, 8), // "slam_run"
QT_MOC_LITERAL(310, 3731, 9), // "slam_stop"
QT_MOC_LITERAL(311, 3741, 13), // "slam_autoInit"
QT_MOC_LITERAL(312, 3755, 15), // "is_slam_running"
QT_MOC_LITERAL(313, 3771, 14), // "getMappingflag"
QT_MOC_LITERAL(314, 3786, 16), // "getObjectingflag"
QT_MOC_LITERAL(315, 3803, 16), // "setObjectingflag"
QT_MOC_LITERAL(316, 3820, 4), // "flag"
QT_MOC_LITERAL(317, 3825, 13), // "getnewMapname"
QT_MOC_LITERAL(318, 3839, 11), // "getLastCall"
QT_MOC_LITERAL(319, 3851, 11), // "getCallSize"
QT_MOC_LITERAL(320, 3863, 16), // "getCallQueueSize"
QT_MOC_LITERAL(321, 3880, 9), // "cleanTray"
QT_MOC_LITERAL(322, 3890, 11), // "getCallName"
QT_MOC_LITERAL(323, 3902, 14), // "clearCallQueue"
QT_MOC_LITERAL(324, 3917, 7), // "getCall"
QT_MOC_LITERAL(325, 3925, 15), // "getCallLocation"
QT_MOC_LITERAL(326, 3941, 11), // "setCallbell"
QT_MOC_LITERAL(327, 3953, 16), // "setCallbellForce"
QT_MOC_LITERAL(328, 3970, 10), // "acceptCall"
QT_MOC_LITERAL(329, 3981, 3), // "yes"
QT_MOC_LITERAL(330, 3985, 10), // "setObjPose"
QT_MOC_LITERAL(331, 3996, 14), // "getServingName"
QT_MOC_LITERAL(332, 4011, 15), // "getLocationName"
QT_MOC_LITERAL(333, 4027, 15), // "getLocationType"
QT_MOC_LITERAL(334, 4043, 17), // "getLocationNumber"
QT_MOC_LITERAL(335, 4061, 17), // "setLocationNumber"
QT_MOC_LITERAL(336, 4079, 15), // "getLocationSize"
QT_MOC_LITERAL(337, 4095, 16), // "getLocationGroup"
QT_MOC_LITERAL(338, 4112, 13), // "getLocationID"
QT_MOC_LITERAL(339, 4126, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(340, 4146, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(341, 4167, 17), // "getLocationCallID"
QT_MOC_LITERAL(342, 4185, 16), // "setLocationGroup"
QT_MOC_LITERAL(343, 4202, 19), // "removeLocationGroup"
QT_MOC_LITERAL(344, 4222, 16), // "addLocationGroup"
QT_MOC_LITERAL(345, 4239, 15), // "getLocGroupname"
QT_MOC_LITERAL(346, 4255, 8), // "tablenum"
QT_MOC_LITERAL(347, 4264, 12), // "getLocationX"
QT_MOC_LITERAL(348, 4277, 12), // "getLocationY"
QT_MOC_LITERAL(349, 4290, 13), // "getLocationTH"
QT_MOC_LITERAL(350, 4304, 15), // "isExistLocation"
QT_MOC_LITERAL(351, 4320, 8), // "getLidar"
QT_MOC_LITERAL(352, 4329, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(353, 4346, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(354, 4363, 17), // "clearSharedMemory"
QT_MOC_LITERAL(355, 4381, 12), // "getObjectNum"
QT_MOC_LITERAL(356, 4394, 13), // "getObjectName"
QT_MOC_LITERAL(357, 4408, 18), // "getObjectPointSize"
QT_MOC_LITERAL(358, 4427, 10), // "getObjectX"
QT_MOC_LITERAL(359, 4438, 5), // "point"
QT_MOC_LITERAL(360, 4444, 10), // "getObjectY"
QT_MOC_LITERAL(361, 4455, 14), // "getObjPointNum"
QT_MOC_LITERAL(362, 4470, 7), // "obj_num"
QT_MOC_LITERAL(363, 4478, 9), // "getLocNum"
QT_MOC_LITERAL(364, 4488, 13), // "saveLocations"
QT_MOC_LITERAL(365, 4502, 13), // "getObjectSize"
QT_MOC_LITERAL(366, 4516, 12), // "removeObject"
QT_MOC_LITERAL(367, 4529, 14), // "saveAnnotation"
QT_MOC_LITERAL(368, 4544, 8), // "isOdroid"
QT_MOC_LITERAL(369, 4553, 13), // "getMultiState"
QT_MOC_LITERAL(370, 4567, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(371, 4587, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(372, 4606, 15), // "getRunawayState"
QT_MOC_LITERAL(373, 4622, 15), // "slam_map_reload"
QT_MOC_LITERAL(374, 4638, 15), // "slam_ini_reload"
QT_MOC_LITERAL(375, 4654, 7), // "setTray"
QT_MOC_LITERAL(376, 4662, 8), // "tray_num"
QT_MOC_LITERAL(377, 4671, 12), // "startServing"
QT_MOC_LITERAL(378, 4684, 9), // "setPreset"
QT_MOC_LITERAL(379, 4694, 6), // "preset"
QT_MOC_LITERAL(380, 4701, 13), // "confirmPickup"
QT_MOC_LITERAL(381, 4715, 14), // "getPickuptrays"
QT_MOC_LITERAL(382, 4730, 10), // "QList<int>"
QT_MOC_LITERAL(383, 4741, 9), // "movePause"
QT_MOC_LITERAL(384, 4751, 10), // "moveResume"
QT_MOC_LITERAL(385, 4762, 12), // "moveStopFlag"
QT_MOC_LITERAL(386, 4775, 8), // "moveStop"
QT_MOC_LITERAL(387, 4784, 12), // "moveToCharge"
QT_MOC_LITERAL(388, 4797, 10), // "moveToWait"
QT_MOC_LITERAL(389, 4808, 14), // "moveToCleaning"
QT_MOC_LITERAL(390, 4823, 9), // "getcurLoc"
QT_MOC_LITERAL(391, 4833, 11), // "getcurTable"
QT_MOC_LITERAL(392, 4845, 16), // "resetHomeFolders"
QT_MOC_LITERAL(393, 4862, 13), // "issetLocation"
QT_MOC_LITERAL(394, 4876, 6), // "number"
QT_MOC_LITERAL(395, 4883, 11), // "getObsState"
QT_MOC_LITERAL(396, 4895, 10), // "getBattery"
QT_MOC_LITERAL(397, 4906, 13), // "getMotorState"
QT_MOC_LITERAL(398, 4920, 20), // "getLocalizationState"
QT_MOC_LITERAL(399, 4941, 14), // "getStateMoving"
QT_MOC_LITERAL(400, 4956, 10), // "getErrcode"
QT_MOC_LITERAL(401, 4967, 12), // "getRobotName"
QT_MOC_LITERAL(402, 4980, 18), // "getMotorConnection"
QT_MOC_LITERAL(403, 4999, 14), // "getMotorStatus"
QT_MOC_LITERAL(404, 5014, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(405, 5032, 19), // "getMotorTemperature"
QT_MOC_LITERAL(406, 5052, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(407, 5078, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(408, 5105, 15), // "getMotorCurrent"
QT_MOC_LITERAL(409, 5121, 14), // "getPowerStatus"
QT_MOC_LITERAL(410, 5136, 15), // "getRemoteStatus"
QT_MOC_LITERAL(411, 5152, 15), // "getChargeStatus"
QT_MOC_LITERAL(412, 5168, 12), // "getEmoStatus"
QT_MOC_LITERAL(413, 5181, 13), // "getLockStatus"
QT_MOC_LITERAL(414, 5195, 12), // "getBatteryIn"
QT_MOC_LITERAL(415, 5208, 13), // "getBatteryOut"
QT_MOC_LITERAL(416, 5222, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(417, 5240, 8), // "getPower"
QT_MOC_LITERAL(418, 5249, 13), // "getPowerTotal"
QT_MOC_LITERAL(419, 5263, 12), // "getObsinPath"
QT_MOC_LITERAL(420, 5276, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(421, 5294, 12), // "setMotorLock"
QT_MOC_LITERAL(422, 5307, 14), // "getRobotRadius"
QT_MOC_LITERAL(423, 5322, 9), // "getRobotx"
QT_MOC_LITERAL(424, 5332, 9), // "getRoboty"
QT_MOC_LITERAL(425, 5342, 10), // "getRobotth"
QT_MOC_LITERAL(426, 5353, 13), // "getlastRobotx"
QT_MOC_LITERAL(427, 5367, 13), // "getlastRoboty"
QT_MOC_LITERAL(428, 5381, 14), // "getlastRobotth"
QT_MOC_LITERAL(429, 5396, 10), // "getPathNum"
QT_MOC_LITERAL(430, 5407, 8), // "getPathx"
QT_MOC_LITERAL(431, 5416, 8), // "getPathy"
QT_MOC_LITERAL(432, 5425, 9), // "getPathth"
QT_MOC_LITERAL(433, 5435, 15), // "getLocalPathNum"
QT_MOC_LITERAL(434, 5451, 13), // "getLocalPathx"
QT_MOC_LITERAL(435, 5465, 13), // "getLocalPathy"
QT_MOC_LITERAL(436, 5479, 10), // "getuistate"
QT_MOC_LITERAL(437, 5490, 10), // "getMapname"
QT_MOC_LITERAL(438, 5501, 10), // "getMappath"
QT_MOC_LITERAL(439, 5512, 11), // "getMapWidth"
QT_MOC_LITERAL(440, 5524, 12), // "getMapHeight"
QT_MOC_LITERAL(441, 5537, 12), // "getGridWidth"
QT_MOC_LITERAL(442, 5550, 9), // "getOrigin"
QT_MOC_LITERAL(443, 5560, 15), // "getMappingWidth"
QT_MOC_LITERAL(444, 5576, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(445, 5596, 15), // "startDrawObject"
QT_MOC_LITERAL(446, 5612, 14), // "stopDrawObject"
QT_MOC_LITERAL(447, 5627, 14), // "saveDrawObject"
QT_MOC_LITERAL(448, 5642, 17), // "getObjectPointNum"
QT_MOC_LITERAL(449, 5660, 9), // "addObject"
QT_MOC_LITERAL(450, 5670, 14), // "addObjectPoint"
QT_MOC_LITERAL(451, 5685, 9), // "setObject"
QT_MOC_LITERAL(452, 5695, 15), // "editObjectStart"
QT_MOC_LITERAL(453, 5711, 10), // "editObject"
QT_MOC_LITERAL(454, 5722, 10), // "saveObject"
QT_MOC_LITERAL(455, 5733, 11), // "clearObject"
QT_MOC_LITERAL(456, 5745, 14), // "clearObjectAll"
QT_MOC_LITERAL(457, 5760, 12), // "selectObject"
QT_MOC_LITERAL(458, 5773, 13), // "getObjectflag"
QT_MOC_LITERAL(459, 5787, 10), // "undoObject"
QT_MOC_LITERAL(460, 5798, 15), // "clearRotateList"
QT_MOC_LITERAL(461, 5814, 13), // "setRotateList"
QT_MOC_LITERAL(462, 5828, 11), // "startPatrol"
QT_MOC_LITERAL(463, 5840, 6), // "pickup"
QT_MOC_LITERAL(464, 5847, 11), // "getICPRatio"
QT_MOC_LITERAL(465, 5859, 11), // "getICPError"
QT_MOC_LITERAL(466, 5871, 13), // "clearFlagStop"
QT_MOC_LITERAL(467, 5885, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(468, 5903, 17), // "moveToServingTest"
QT_MOC_LITERAL(469, 5921, 15), // "getusberrorsize"
QT_MOC_LITERAL(470, 5937, 11), // "getusberror"
QT_MOC_LITERAL(471, 5949, 11), // "getzipstate"
QT_MOC_LITERAL(472, 5961, 10), // "clear_call"
QT_MOC_LITERAL(473, 5972, 7), // "usbsave"
QT_MOC_LITERAL(474, 5980, 3), // "usb"
QT_MOC_LITERAL(475, 5984, 3), // "_ui"
QT_MOC_LITERAL(476, 5988, 5), // "_slam"
QT_MOC_LITERAL(477, 5994, 7), // "_config"
QT_MOC_LITERAL(478, 6002, 4), // "_map"
QT_MOC_LITERAL(479, 6007, 4), // "_log"
QT_MOC_LITERAL(480, 6012, 13), // "restartUpdate"
QT_MOC_LITERAL(481, 6026, 11), // "startUpdate"
QT_MOC_LITERAL(482, 6038, 18), // "getTravellineIssue"
QT_MOC_LITERAL(483, 6057, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(484, 6081, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(485, 6104, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(486, 6126, 24) // "getTravellineIssueBroken"

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
    "getSystemVolume\0passInit\0loadFile\0"
    "type\0setMap\0moveMap\0setFullScreen\0"
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
     447,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 2249,    2, 0x0a /* Public */,
       3,    0, 2250,    2, 0x0a /* Public */,
       4,    0, 2251,    2, 0x0a /* Public */,
       5,    0, 2252,    2, 0x0a /* Public */,
       6,    0, 2253,    2, 0x0a /* Public */,
       7,    0, 2254,    2, 0x0a /* Public */,
       8,    0, 2255,    2, 0x0a /* Public */,
       9,    0, 2256,    2, 0x0a /* Public */,
      10,    1, 2257,    2, 0x0a /* Public */,
      12,    1, 2260,    2, 0x0a /* Public */,
      13,    2, 2263,    2, 0x0a /* Public */,
      15,    1, 2268,    2, 0x0a /* Public */,
      16,    0, 2271,    2, 0x0a /* Public */,
      17,    0, 2272,    2, 0x0a /* Public */,
      18,    0, 2273,    2, 0x0a /* Public */,
      19,    0, 2274,    2, 0x0a /* Public */,
      20,    1, 2275,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      22,    0, 2278,    2, 0x02 /* Public */,
      23,    0, 2279,    2, 0x02 /* Public */,
      24,    2, 2280,    2, 0x02 /* Public */,
      26,    0, 2285,    2, 0x02 /* Public */,
      27,    0, 2286,    2, 0x02 /* Public */,
      28,    1, 2287,    2, 0x02 /* Public */,
      30,    0, 2290,    2, 0x02 /* Public */,
      31,    1, 2291,    2, 0x02 /* Public */,
      33,    2, 2294,    2, 0x02 /* Public */,
      35,    1, 2299,    2, 0x02 /* Public */,
      36,    1, 2302,    2, 0x02 /* Public */,
      37,    1, 2305,    2, 0x02 /* Public */,
      38,    1, 2308,    2, 0x02 /* Public */,
      39,    0, 2311,    2, 0x02 /* Public */,
      40,    0, 2312,    2, 0x02 /* Public */,
      41,    3, 2313,    2, 0x02 /* Public */,
      45,    0, 2320,    2, 0x02 /* Public */,
      46,    0, 2321,    2, 0x02 /* Public */,
      47,    0, 2322,    2, 0x02 /* Public */,
      48,    1, 2323,    2, 0x02 /* Public */,
      49,    1, 2326,    2, 0x02 /* Public */,
      50,    0, 2329,    2, 0x02 /* Public */,
      51,    0, 2330,    2, 0x02 /* Public */,
      52,    2, 2331,    2, 0x02 /* Public */,
      54,    0, 2336,    2, 0x02 /* Public */,
      55,    0, 2337,    2, 0x02 /* Public */,
      56,    0, 2338,    2, 0x02 /* Public */,
      57,    0, 2339,    2, 0x02 /* Public */,
      58,    2, 2340,    2, 0x02 /* Public */,
      58,    1, 2345,    2, 0x22 /* Public | MethodCloned */,
      61,    1, 2348,    2, 0x02 /* Public */,
      61,    0, 2351,    2, 0x22 /* Public | MethodCloned */,
      62,    0, 2352,    2, 0x02 /* Public */,
      63,    0, 2353,    2, 0x02 /* Public */,
      64,    2, 2354,    2, 0x02 /* Public */,
      64,    1, 2359,    2, 0x22 /* Public | MethodCloned */,
      66,    0, 2362,    2, 0x02 /* Public */,
      67,    1, 2363,    2, 0x02 /* Public */,
      68,    1, 2366,    2, 0x02 /* Public */,
      69,    0, 2369,    2, 0x02 /* Public */,
      70,    1, 2370,    2, 0x02 /* Public */,
      71,    1, 2373,    2, 0x02 /* Public */,
      73,    0, 2376,    2, 0x02 /* Public */,
      74,    1, 2377,    2, 0x02 /* Public */,
      76,    1, 2380,    2, 0x02 /* Public */,
      77,    1, 2383,    2, 0x02 /* Public */,
      78,    1, 2386,    2, 0x02 /* Public */,
      79,    1, 2389,    2, 0x02 /* Public */,
      80,    1, 2392,    2, 0x02 /* Public */,
      81,    1, 2395,    2, 0x02 /* Public */,
      82,    1, 2398,    2, 0x02 /* Public */,
      83,    0, 2401,    2, 0x02 /* Public */,
      84,    0, 2402,    2, 0x02 /* Public */,
      85,    0, 2403,    2, 0x02 /* Public */,
      86,    1, 2404,    2, 0x02 /* Public */,
      87,    3, 2407,    2, 0x02 /* Public */,
      91,    0, 2414,    2, 0x02 /* Public */,
      92,    0, 2415,    2, 0x02 /* Public */,
      93,    0, 2416,    2, 0x02 /* Public */,
      94,    0, 2417,    2, 0x02 /* Public */,
      95,    0, 2418,    2, 0x02 /* Public */,
      96,    3, 2419,    2, 0x02 /* Public */,
      97,    2, 2426,    2, 0x02 /* Public */,
      98,    0, 2431,    2, 0x02 /* Public */,
      99,    0, 2432,    2, 0x02 /* Public */,
     100,    1, 2433,    2, 0x02 /* Public */,
     102,    0, 2436,    2, 0x02 /* Public */,
     103,    0, 2437,    2, 0x02 /* Public */,
     104,    0, 2438,    2, 0x02 /* Public */,
     105,    0, 2439,    2, 0x02 /* Public */,
     106,    0, 2440,    2, 0x02 /* Public */,
     107,    0, 2441,    2, 0x02 /* Public */,
     108,    0, 2442,    2, 0x02 /* Public */,
     109,    2, 2443,    2, 0x02 /* Public */,
     110,    2, 2448,    2, 0x02 /* Public */,
     111,    2, 2453,    2, 0x02 /* Public */,
     112,    1, 2458,    2, 0x02 /* Public */,
     113,    2, 2461,    2, 0x02 /* Public */,
     114,    2, 2466,    2, 0x02 /* Public */,
     115,    0, 2471,    2, 0x02 /* Public */,
     116,    0, 2472,    2, 0x02 /* Public */,
     117,    0, 2473,    2, 0x02 /* Public */,
     118,    0, 2474,    2, 0x02 /* Public */,
     119,    2, 2475,    2, 0x02 /* Public */,
     120,    2, 2480,    2, 0x02 /* Public */,
     121,    0, 2485,    2, 0x02 /* Public */,
     122,    1, 2486,    2, 0x02 /* Public */,
     124,    2, 2489,    2, 0x02 /* Public */,
     125,    2, 2494,    2, 0x02 /* Public */,
     126,    2, 2499,    2, 0x02 /* Public */,
     127,    1, 2504,    2, 0x02 /* Public */,
     129,    1, 2507,    2, 0x02 /* Public */,
     131,    2, 2510,    2, 0x02 /* Public */,
     132,    3, 2515,    2, 0x02 /* Public */,
     134,    0, 2522,    2, 0x02 /* Public */,
     135,    3, 2523,    2, 0x02 /* Public */,
     136,    3, 2530,    2, 0x02 /* Public */,
     137,    3, 2537,    2, 0x02 /* Public */,
     138,    1, 2544,    2, 0x02 /* Public */,
     131,    2, 2547,    2, 0x02 /* Public */,
     139,    1, 2552,    2, 0x02 /* Public */,
     140,    1, 2555,    2, 0x02 /* Public */,
     141,    0, 2558,    2, 0x02 /* Public */,
     142,    1, 2559,    2, 0x02 /* Public */,
     143,    0, 2562,    2, 0x02 /* Public */,
     144,    0, 2563,    2, 0x02 /* Public */,
     145,    0, 2564,    2, 0x02 /* Public */,
     146,    0, 2565,    2, 0x02 /* Public */,
     147,    0, 2566,    2, 0x02 /* Public */,
     148,    2, 2567,    2, 0x02 /* Public */,
     150,    3, 2572,    2, 0x02 /* Public */,
     152,    3, 2579,    2, 0x02 /* Public */,
     153,    2, 2586,    2, 0x02 /* Public */,
     154,    0, 2591,    2, 0x02 /* Public */,
     155,    0, 2592,    2, 0x02 /* Public */,
     156,    0, 2593,    2, 0x02 /* Public */,
     157,    0, 2594,    2, 0x02 /* Public */,
     158,    1, 2595,    2, 0x02 /* Public */,
     159,    1, 2598,    2, 0x02 /* Public */,
     160,    1, 2601,    2, 0x02 /* Public */,
     161,    1, 2604,    2, 0x02 /* Public */,
     162,    1, 2607,    2, 0x02 /* Public */,
     163,    1, 2610,    2, 0x02 /* Public */,
     164,    1, 2613,    2, 0x02 /* Public */,
     165,    0, 2616,    2, 0x02 /* Public */,
     166,    3, 2617,    2, 0x02 /* Public */,
     167,    0, 2624,    2, 0x02 /* Public */,
     168,    1, 2625,    2, 0x02 /* Public */,
     169,    1, 2628,    2, 0x02 /* Public */,
     171,    0, 2631,    2, 0x02 /* Public */,
     172,    0, 2632,    2, 0x02 /* Public */,
     173,    0, 2633,    2, 0x02 /* Public */,
     174,    1, 2634,    2, 0x02 /* Public */,
     175,    1, 2637,    2, 0x02 /* Public */,
     176,    0, 2640,    2, 0x02 /* Public */,
     177,    0, 2641,    2, 0x02 /* Public */,
     178,    0, 2642,    2, 0x02 /* Public */,
     179,    0, 2643,    2, 0x02 /* Public */,
     180,    0, 2644,    2, 0x02 /* Public */,
     181,    0, 2645,    2, 0x02 /* Public */,
     182,    0, 2646,    2, 0x02 /* Public */,
     183,    0, 2647,    2, 0x02 /* Public */,
     184,    0, 2648,    2, 0x02 /* Public */,
     185,    0, 2649,    2, 0x02 /* Public */,
     186,    0, 2650,    2, 0x02 /* Public */,
     187,    1, 2651,    2, 0x02 /* Public */,
     188,    1, 2654,    2, 0x02 /* Public */,
     189,    1, 2657,    2, 0x02 /* Public */,
     190,    1, 2660,    2, 0x02 /* Public */,
     191,    1, 2663,    2, 0x02 /* Public */,
     192,    1, 2666,    2, 0x02 /* Public */,
     193,    1, 2669,    2, 0x02 /* Public */,
     195,    3, 2672,    2, 0x02 /* Public */,
     197,    1, 2679,    2, 0x02 /* Public */,
     197,    0, 2682,    2, 0x22 /* Public | MethodCloned */,
     199,    3, 2683,    2, 0x02 /* Public */,
     200,    0, 2690,    2, 0x02 /* Public */,
     201,    1, 2691,    2, 0x02 /* Public */,
     203,    0, 2694,    2, 0x02 /* Public */,
     204,    0, 2695,    2, 0x02 /* Public */,
     205,    0, 2696,    2, 0x02 /* Public */,
     206,    0, 2697,    2, 0x02 /* Public */,
     207,    2, 2698,    2, 0x02 /* Public */,
     210,    0, 2703,    2, 0x02 /* Public */,
     211,    1, 2704,    2, 0x02 /* Public */,
     212,    1, 2707,    2, 0x02 /* Public */,
     214,    2, 2710,    2, 0x02 /* Public */,
     214,    1, 2715,    2, 0x22 /* Public | MethodCloned */,
     215,    0, 2718,    2, 0x02 /* Public */,
     216,    0, 2719,    2, 0x02 /* Public */,
     217,    0, 2720,    2, 0x02 /* Public */,
     218,    0, 2721,    2, 0x02 /* Public */,
     219,    0, 2722,    2, 0x02 /* Public */,
     220,    0, 2723,    2, 0x02 /* Public */,
     221,    0, 2724,    2, 0x02 /* Public */,
     222,    0, 2725,    2, 0x02 /* Public */,
     223,    0, 2726,    2, 0x02 /* Public */,
     224,    0, 2727,    2, 0x02 /* Public */,
     225,    0, 2728,    2, 0x02 /* Public */,
     226,    0, 2729,    2, 0x02 /* Public */,
     227,    0, 2730,    2, 0x02 /* Public */,
     228,    1, 2731,    2, 0x02 /* Public */,
     229,    1, 2734,    2, 0x02 /* Public */,
     230,    1, 2737,    2, 0x02 /* Public */,
     231,    1, 2740,    2, 0x02 /* Public */,
     232,    1, 2743,    2, 0x02 /* Public */,
     233,    0, 2746,    2, 0x02 /* Public */,
     234,    0, 2747,    2, 0x02 /* Public */,
     235,    0, 2748,    2, 0x02 /* Public */,
     236,    1, 2749,    2, 0x02 /* Public */,
     238,    0, 2752,    2, 0x02 /* Public */,
     239,    2, 2753,    2, 0x02 /* Public */,
     241,    1, 2758,    2, 0x02 /* Public */,
     244,    2, 2761,    2, 0x02 /* Public */,
     245,    1, 2766,    2, 0x02 /* Public */,
     247,    1, 2769,    2, 0x02 /* Public */,
     249,    0, 2772,    2, 0x02 /* Public */,
     250,    1, 2773,    2, 0x02 /* Public */,
     251,    0, 2776,    2, 0x02 /* Public */,
     252,    1, 2777,    2, 0x02 /* Public */,
     253,    1, 2780,    2, 0x02 /* Public */,
     254,    1, 2783,    2, 0x02 /* Public */,
     255,    1, 2786,    2, 0x02 /* Public */,
     256,    1, 2789,    2, 0x02 /* Public */,
     258,    3, 2792,    2, 0x02 /* Public */,
     261,    0, 2799,    2, 0x02 /* Public */,
     262,    0, 2800,    2, 0x02 /* Public */,
     263,    0, 2801,    2, 0x02 /* Public */,
     264,    0, 2802,    2, 0x02 /* Public */,
     265,    1, 2803,    2, 0x02 /* Public */,
     266,    0, 2806,    2, 0x02 /* Public */,
     267,    1, 2807,    2, 0x02 /* Public */,
     268,    0, 2810,    2, 0x02 /* Public */,
     269,    1, 2811,    2, 0x02 /* Public */,
     271,    0, 2814,    2, 0x02 /* Public */,
     272,    0, 2815,    2, 0x02 /* Public */,
     273,    1, 2816,    2, 0x02 /* Public */,
     273,    0, 2819,    2, 0x22 /* Public | MethodCloned */,
     274,    1, 2820,    2, 0x02 /* Public */,
     275,    1, 2823,    2, 0x02 /* Public */,
     275,    0, 2826,    2, 0x22 /* Public | MethodCloned */,
     276,    1, 2827,    2, 0x02 /* Public */,
     276,    0, 2830,    2, 0x22 /* Public | MethodCloned */,
     277,    1, 2831,    2, 0x02 /* Public */,
     277,    0, 2834,    2, 0x22 /* Public | MethodCloned */,
     278,    1, 2835,    2, 0x02 /* Public */,
     278,    0, 2838,    2, 0x22 /* Public | MethodCloned */,
     279,    1, 2839,    2, 0x02 /* Public */,
     280,    1, 2842,    2, 0x02 /* Public */,
     281,    0, 2845,    2, 0x02 /* Public */,
     282,    0, 2846,    2, 0x02 /* Public */,
     283,    1, 2847,    2, 0x02 /* Public */,
     284,    1, 2850,    2, 0x02 /* Public */,
     285,    1, 2853,    2, 0x02 /* Public */,
     286,    0, 2856,    2, 0x02 /* Public */,
     287,    0, 2857,    2, 0x02 /* Public */,
     288,    1, 2858,    2, 0x02 /* Public */,
     290,    1, 2861,    2, 0x02 /* Public */,
     291,    2, 2864,    2, 0x02 /* Public */,
      54,    1, 2869,    2, 0x02 /* Public */,
     294,    3, 2872,    2, 0x02 /* Public */,
     297,    2, 2879,    2, 0x02 /* Public */,
     300,    0, 2884,    2, 0x02 /* Public */,
     301,    1, 2885,    2, 0x02 /* Public */,
     302,    1, 2888,    2, 0x02 /* Public */,
     303,    0, 2891,    2, 0x02 /* Public */,
     304,    3, 2892,    2, 0x02 /* Public */,
     305,    0, 2899,    2, 0x02 /* Public */,
     306,    0, 2900,    2, 0x02 /* Public */,
     307,    0, 2901,    2, 0x02 /* Public */,
     308,    0, 2902,    2, 0x02 /* Public */,
     309,    0, 2903,    2, 0x02 /* Public */,
     310,    0, 2904,    2, 0x02 /* Public */,
     311,    0, 2905,    2, 0x02 /* Public */,
     312,    0, 2906,    2, 0x02 /* Public */,
     313,    0, 2907,    2, 0x02 /* Public */,
     314,    0, 2908,    2, 0x02 /* Public */,
     315,    1, 2909,    2, 0x02 /* Public */,
     317,    0, 2912,    2, 0x02 /* Public */,
     318,    0, 2913,    2, 0x02 /* Public */,
     319,    0, 2914,    2, 0x02 /* Public */,
     320,    0, 2915,    2, 0x02 /* Public */,
     321,    0, 2916,    2, 0x02 /* Public */,
     322,    1, 2917,    2, 0x02 /* Public */,
     323,    0, 2920,    2, 0x02 /* Public */,
     324,    1, 2921,    2, 0x02 /* Public */,
     325,    1, 2924,    2, 0x02 /* Public */,
     326,    2, 2927,    2, 0x02 /* Public */,
     327,    2, 2932,    2, 0x02 /* Public */,
     328,    1, 2937,    2, 0x02 /* Public */,
     330,    0, 2940,    2, 0x02 /* Public */,
     331,    2, 2941,    2, 0x02 /* Public */,
     131,    1, 2946,    2, 0x02 /* Public */,
     131,    0, 2949,    2, 0x22 /* Public | MethodCloned */,
     332,    2, 2950,    2, 0x02 /* Public */,
     332,    1, 2955,    2, 0x22 /* Public | MethodCloned */,
     333,    1, 2958,    2, 0x02 /* Public */,
     334,    2, 2961,    2, 0x02 /* Public */,
     335,    2, 2966,    2, 0x02 /* Public */,
     336,    1, 2971,    2, 0x02 /* Public */,
     337,    1, 2974,    2, 0x02 /* Public */,
     338,    2, 2977,    2, 0x02 /* Public */,
     339,    0, 2982,    2, 0x02 /* Public */,
     340,    1, 2983,    2, 0x02 /* Public */,
     339,    1, 2986,    2, 0x02 /* Public */,
     341,    1, 2989,    2, 0x02 /* Public */,
     342,    2, 2992,    2, 0x02 /* Public */,
     343,    1, 2997,    2, 0x02 /* Public */,
     344,    1, 3000,    2, 0x02 /* Public */,
     345,    1, 3003,    2, 0x02 /* Public */,
     137,    4, 3006,    2, 0x02 /* Public */,
     347,    2, 3015,    2, 0x02 /* Public */,
     347,    1, 3020,    2, 0x22 /* Public | MethodCloned */,
     348,    2, 3023,    2, 0x02 /* Public */,
     348,    1, 3028,    2, 0x22 /* Public | MethodCloned */,
     349,    2, 3031,    2, 0x02 /* Public */,
     349,    1, 3036,    2, 0x22 /* Public | MethodCloned */,
     350,    2, 3039,    2, 0x02 /* Public */,
     351,    1, 3044,    2, 0x02 /* Public */,
     352,    0, 3047,    2, 0x02 /* Public */,
     353,    1, 3048,    2, 0x02 /* Public */,
     354,    0, 3051,    2, 0x02 /* Public */,
     355,    0, 3052,    2, 0x02 /* Public */,
     356,    1, 3053,    2, 0x02 /* Public */,
     357,    1, 3056,    2, 0x02 /* Public */,
     358,    2, 3059,    2, 0x02 /* Public */,
     360,    2, 3064,    2, 0x02 /* Public */,
     361,    3, 3069,    2, 0x02 /* Public */,
     363,    1, 3076,    2, 0x02 /* Public */,
     363,    2, 3079,    2, 0x02 /* Public */,
     364,    0, 3084,    2, 0x02 /* Public */,
     365,    1, 3085,    2, 0x02 /* Public */,
     366,    1, 3088,    2, 0x02 /* Public */,
     367,    1, 3091,    2, 0x02 /* Public */,
     368,    0, 3094,    2, 0x02 /* Public */,
     369,    0, 3095,    2, 0x02 /* Public */,
     370,    0, 3096,    2, 0x02 /* Public */,
     371,    0, 3097,    2, 0x02 /* Public */,
     372,    0, 3098,    2, 0x02 /* Public */,
     373,    2, 3099,    2, 0x02 /* Public */,
     373,    1, 3104,    2, 0x22 /* Public | MethodCloned */,
     374,    0, 3107,    2, 0x02 /* Public */,
     375,    3, 3108,    2, 0x02 /* Public */,
     377,    0, 3115,    2, 0x02 /* Public */,
     378,    1, 3116,    2, 0x02 /* Public */,
     380,    0, 3119,    2, 0x02 /* Public */,
     381,    0, 3120,    2, 0x02 /* Public */,
     383,    0, 3121,    2, 0x02 /* Public */,
     384,    0, 3122,    2, 0x02 /* Public */,
     385,    0, 3123,    2, 0x02 /* Public */,
     386,    0, 3124,    2, 0x02 /* Public */,
     387,    0, 3125,    2, 0x02 /* Public */,
     388,    0, 3126,    2, 0x02 /* Public */,
     389,    0, 3127,    2, 0x02 /* Public */,
     390,    0, 3128,    2, 0x02 /* Public */,
     391,    0, 3129,    2, 0x02 /* Public */,
     392,    0, 3130,    2, 0x02 /* Public */,
     393,    1, 3131,    2, 0x02 /* Public */,
     395,    0, 3134,    2, 0x02 /* Public */,
     396,    0, 3135,    2, 0x02 /* Public */,
     397,    0, 3136,    2, 0x02 /* Public */,
     398,    0, 3137,    2, 0x02 /* Public */,
     399,    0, 3138,    2, 0x02 /* Public */,
     400,    0, 3139,    2, 0x02 /* Public */,
     401,    0, 3140,    2, 0x02 /* Public */,
     402,    1, 3141,    2, 0x02 /* Public */,
     403,    1, 3144,    2, 0x02 /* Public */,
     404,    1, 3147,    2, 0x02 /* Public */,
     405,    1, 3150,    2, 0x02 /* Public */,
     406,    1, 3153,    2, 0x02 /* Public */,
     407,    0, 3156,    2, 0x02 /* Public */,
     408,    1, 3157,    2, 0x02 /* Public */,
     409,    0, 3160,    2, 0x02 /* Public */,
     410,    0, 3161,    2, 0x02 /* Public */,
     411,    0, 3162,    2, 0x02 /* Public */,
     412,    0, 3163,    2, 0x02 /* Public */,
     413,    0, 3164,    2, 0x02 /* Public */,
     414,    0, 3165,    2, 0x02 /* Public */,
     415,    0, 3166,    2, 0x02 /* Public */,
     416,    0, 3167,    2, 0x02 /* Public */,
     417,    0, 3168,    2, 0x02 /* Public */,
     418,    0, 3169,    2, 0x02 /* Public */,
     419,    0, 3170,    2, 0x02 /* Public */,
     420,    0, 3171,    2, 0x02 /* Public */,
     421,    1, 3172,    2, 0x02 /* Public */,
     422,    0, 3175,    2, 0x02 /* Public */,
     423,    0, 3176,    2, 0x02 /* Public */,
     424,    0, 3177,    2, 0x02 /* Public */,
     425,    0, 3178,    2, 0x02 /* Public */,
     426,    0, 3179,    2, 0x02 /* Public */,
     427,    0, 3180,    2, 0x02 /* Public */,
     428,    0, 3181,    2, 0x02 /* Public */,
     429,    0, 3182,    2, 0x02 /* Public */,
     430,    1, 3183,    2, 0x02 /* Public */,
     431,    1, 3186,    2, 0x02 /* Public */,
     432,    1, 3189,    2, 0x02 /* Public */,
     433,    0, 3192,    2, 0x02 /* Public */,
     434,    1, 3193,    2, 0x02 /* Public */,
     435,    1, 3196,    2, 0x02 /* Public */,
     436,    0, 3199,    2, 0x02 /* Public */,
     437,    0, 3200,    2, 0x02 /* Public */,
     438,    0, 3201,    2, 0x02 /* Public */,
     439,    0, 3202,    2, 0x02 /* Public */,
     440,    0, 3203,    2, 0x02 /* Public */,
     441,    0, 3204,    2, 0x02 /* Public */,
     442,    0, 3205,    2, 0x02 /* Public */,
     443,    0, 3206,    2, 0x02 /* Public */,
     444,    0, 3207,    2, 0x02 /* Public */,
     445,    0, 3208,    2, 0x02 /* Public */,
     446,    0, 3209,    2, 0x02 /* Public */,
     447,    0, 3210,    2, 0x02 /* Public */,
     355,    2, 3211,    2, 0x02 /* Public */,
     448,    2, 3216,    2, 0x02 /* Public */,
     449,    2, 3221,    2, 0x02 /* Public */,
     450,    2, 3226,    2, 0x02 /* Public */,
     451,    2, 3231,    2, 0x02 /* Public */,
     452,    2, 3236,    2, 0x02 /* Public */,
     453,    2, 3241,    2, 0x02 /* Public */,
     454,    0, 3246,    2, 0x02 /* Public */,
     455,    0, 3247,    2, 0x02 /* Public */,
     456,    0, 3248,    2, 0x02 /* Public */,
     457,    1, 3249,    2, 0x02 /* Public */,
     458,    0, 3252,    2, 0x02 /* Public */,
     459,    0, 3253,    2, 0x02 /* Public */,
     460,    0, 3254,    2, 0x02 /* Public */,
     461,    1, 3255,    2, 0x02 /* Public */,
     462,    2, 3258,    2, 0x02 /* Public */,
     464,    0, 3263,    2, 0x02 /* Public */,
     465,    0, 3264,    2, 0x02 /* Public */,
     466,    0, 3265,    2, 0x02 /* Public */,
     467,    0, 3266,    2, 0x02 /* Public */,
     468,    2, 3267,    2, 0x02 /* Public */,
     469,    0, 3272,    2, 0x02 /* Public */,
     470,    1, 3273,    2, 0x02 /* Public */,
     471,    0, 3276,    2, 0x02 /* Public */,
     472,    0, 3277,    2, 0x02 /* Public */,
     473,    6, 3278,    2, 0x02 /* Public */,
     473,    5, 3291,    2, 0x22 /* Public | MethodCloned */,
     473,    4, 3302,    2, 0x22 /* Public | MethodCloned */,
     473,    3, 3311,    2, 0x22 /* Public | MethodCloned */,
     473,    2, 3318,    2, 0x22 /* Public | MethodCloned */,
     473,    1, 3323,    2, 0x22 /* Public | MethodCloned */,
     473,    0, 3326,    2, 0x22 /* Public | MethodCloned */,
     480,    0, 3327,    2, 0x02 /* Public */,
     481,    0, 3328,    2, 0x02 /* Public */,
     482,    0, 3329,    2, 0x02 /* Public */,
     483,    1, 3330,    2, 0x02 /* Public */,
     484,    1, 3333,    2, 0x02 /* Public */,
     485,    1, 3336,    2, 0x02 /* Public */,
     486,    1, 3339,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   53,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   59,   60,
    QMetaType::Void, QMetaType::QString,   59,
    QMetaType::Void, QMetaType::Int,   60,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   65,   60,
    QMetaType::Void, QMetaType::QString,   65,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Bool,   72,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,   90,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,   88,   89,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  101,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::QString,   53,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  123,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int,  128,
    QMetaType::Void, QMetaType::Int,  130,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   25,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   53,  133,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,   90,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,   90,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,   90,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  130,  149,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,  151,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,  151,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Bool,   75,
    QMetaType::Void, QMetaType::Int,   60,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,  130,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString,  170,
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
    QMetaType::QString, QMetaType::QString,  194,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  194,   21,  196,
    QMetaType::Void, QMetaType::QString,  198,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  194,   25,   21,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  202,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  208,  209,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Bool,  213,
    QMetaType::QString, QMetaType::QString, QMetaType::QString,   21,   59,
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
    QMetaType::Void, QMetaType::QString,  237,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,  240,
    0x80000000 | 242, QMetaType::QString,  243,
    0x80000000 | 242, QMetaType::Int, QMetaType::QString,   25,   21,
    0x80000000 | 242, QMetaType::Int,  246,
    QMetaType::Void, QMetaType::Int,  248,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QDateTime,  257,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  259,  260,  257,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  270,
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
    QMetaType::Void, QMetaType::QString,  289,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  292,  293,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  295,  296,   59,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  298,  299,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   59,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,   88,   89,   90,
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
    QMetaType::Void, QMetaType::Bool,  316,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  246,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  246,
    0x80000000 | 242, QMetaType::QString,  246,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   53,  246,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   53,   75,
    QMetaType::Void, QMetaType::Bool,  329,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Int, QMetaType::QString,   53,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   32,   53,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   21,   32,
    QMetaType::Int, QMetaType::QString,   53,
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
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   32,   21,   25,  346,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   53,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   53,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   53,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  316,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  359,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  359,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  362,   88,   89,
    QMetaType::Int, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   53,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::QString,  289,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  289,   59,
    QMetaType::Void, QMetaType::QString,  289,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  376,   25,  240,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  379,
    QMetaType::Void,
    0x80000000 | 382,
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
    QMetaType::Bool, QMetaType::Int,  394,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  246,
    QMetaType::Int, QMetaType::Int,  246,
    QMetaType::QString, QMetaType::Int,  246,
    QMetaType::Int, QMetaType::Int,  246,
    QMetaType::Int, QMetaType::Int,  246,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  246,
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
    QMetaType::Void, QMetaType::Bool,   75,
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
    0x80000000 | 382,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   88,   89,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   59,  463,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   25,   21,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  474,  475,  476,  477,  478,  479,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  474,  475,  476,  477,  478,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  474,  475,  476,  477,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  474,  475,  476,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  474,  475,
    QMetaType::Void, QMetaType::QString,  474,
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
        case 40: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 41: _t->setMap(); break;
        case 42: _t->moveMap(); break;
        case 43: _t->setFullScreen(); break;
        case 44: _t->setMapDrawing(); break;
        case 45: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 46: _t->clicksound((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 47: _t->playBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 48: _t->playBGM(); break;
        case 49: _t->stopBGM(); break;
        case 50: { bool _r = _t->isplayBGM();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 51: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 52: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 53: _t->confirmLocalization(); break;
        case 54: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 55: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 56: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 57: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 58: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 59: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 60: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 61: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 62: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 63: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 64: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 65: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 66: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 67: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 68: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 69: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 70: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 71: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 72: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 73: _t->clearInitPose(); break;
        case 74: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 75: _t->startDrawingTline(); break;
        case 76: _t->stopDrawingTline(); break;
        case 77: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 78: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 79: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 80: _t->saveRotateMap(); break;
        case 81: _t->initRotate(); break;
        case 82: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 83: _t->rotateMapCW(); break;
        case 84: _t->rotateMapCCW(); break;
        case 85: _t->saveObjectPNG(); break;
        case 86: _t->saveObsAreaPNG(); break;
        case 87: { int _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 88: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 89: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 90: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 91: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 92: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 93: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 94: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 95: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 96: _t->endDrawingRect(); break;
        case 97: _t->clearDrawing(); break;
        case 98: _t->undoLine(); break;
        case 99: _t->redoLine(); break;
        case 100: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 101: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 102: _t->drawSpline(); break;
        case 103: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 104: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 105: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 106: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 107: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 108: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 109: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 110: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 111: _t->clearLocation(); break;
        case 112: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 113: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 114: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 115: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 116: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 117: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 118: { bool _r = _t->getLocationAvailable((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 119: _t->setTableNumberAuto(); break;
        case 120: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 121: _t->saveMap(); break;
        case 122: _t->saveEditedMap(); break;
        case 123: _t->saveTline(); break;
        case 124: _t->saveTlineTemp(); break;
        case 125: _t->saveVelmap(); break;
        case 126: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 127: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 128: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 129: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 130: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 131: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 132: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 133: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 134: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 135: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 136: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 137: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 138: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 139: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 140: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 141: _t->requestSystemVolume(); break;
        case 142: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 143: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 144: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 145: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 146: _t->startDrawingObject(); break;
        case 147: _t->stopDrawingObject(); break;
        case 148: _t->saveDrawingObject(); break;
        case 149: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 150: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 151: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 152: _t->killSLAM(); break;
        case 153: _t->makeRobotINI(); break;
        case 154: _t->checkRobotINI(); break;
        case 155: _t->restartSLAM(); break;
        case 156: _t->startSLAM(); break;
        case 157: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 158: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 159: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 160: _t->programRestart(); break;
        case 161: _t->programExit(); break;
        case 162: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 163: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 164: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 165: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 166: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 167: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 168: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 169: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 170: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 171: _t->readSetting(); break;
        case 172: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 173: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 174: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 175: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 176: _t->requestCamera(); break;
        case 177: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 178: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 179: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 180: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 181: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 182: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 183: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 184: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 185: _t->checkTravelline(); break;
        case 186: _t->updateProgram(); break;
        case 187: _t->updateProgramGitPull(); break;
        case 188: _t->checkVersionAgain(); break;
        case 189: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 190: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 191: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 192: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 193: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 194: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 195: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 196: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 197: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 198: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 199: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 200: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 201: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 202: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 203: _t->checkCleaningLocation(); break;
        case 204: _t->checkUpdate(); break;
        case 205: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 206: _t->setlanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 207: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 208: _t->goServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 209: { LOCATION _r = _t->getLocationbyCall((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 210: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 211: { LOCATION _r = _t->getLocationbyID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 212: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 213: _t->resetLocalization(); break;
        case 214: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 215: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 216: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 217: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 218: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 219: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 220: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 221: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 222: _t->updateUSB(); break;
        case 223: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 224: _t->readusbrecentfile(); break;
        case 225: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 226: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 227: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 228: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 229: _t->readusb(); break;
        case 230: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 231: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 232: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 233: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 234: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 235: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 236: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 237: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 238: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 239: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 240: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 241: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 242: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 243: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 244: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 245: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 246: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 247: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 248: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 249: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 250: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 251: _t->deleteEditedMap(); break;
        case 252: _t->deleteAnnotation(); break;
        case 253: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 254: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 255: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 256: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 257: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 258: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 259: _t->stopMapping(); break;
        case 260: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 261: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 262: _t->setInitCurPos(); break;
        case 263: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 264: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 265: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 266: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 267: _t->slam_setInit(); break;
        case 268: _t->slam_run(); break;
        case 269: _t->slam_stop(); break;
        case 270: _t->slam_autoInit(); break;
        case 271: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 272: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 273: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 274: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 275: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 276: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 277: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 278: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 279: _t->cleanTray(); break;
        case 280: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 281: _t->clearCallQueue(); break;
        case 282: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 283: { LOCATION _r = _t->getCallLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 284: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 285: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 286: _t->acceptCall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 287: _t->setObjPose(); break;
        case 288: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 289: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 290: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 291: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 292: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 293: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 294: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 295: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 296: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 297: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 298: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 299: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 300: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 301: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 302: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 303: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 304: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 305: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 306: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 307: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 308: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 309: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 310: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 311: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 312: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 313: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 314: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 315: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 316: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 317: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 318: _t->clearSharedMemory(); break;
        case 319: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 320: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 321: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 322: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 323: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 324: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 325: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 326: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 327: _t->saveLocations(); break;
        case 328: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 329: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 330: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 331: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 332: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 333: _t->drawingRunawayStart(); break;
        case 334: _t->drawingRunawayStop(); break;
        case 335: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 336: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 337: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 338: _t->slam_ini_reload(); break;
        case 339: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 340: _t->startServing(); break;
        case 341: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 342: _t->confirmPickup(); break;
        case 343: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 344: _t->movePause(); break;
        case 345: _t->moveResume(); break;
        case 346: _t->moveStopFlag(); break;
        case 347: _t->moveStop(); break;
        case 348: _t->moveToCharge(); break;
        case 349: _t->moveToWait(); break;
        case 350: _t->moveToCleaning(); break;
        case 351: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 352: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 353: _t->resetHomeFolders(); break;
        case 354: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 355: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 356: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 357: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 358: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 359: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 360: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 361: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 362: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 363: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 364: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 365: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 366: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 367: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 368: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 369: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 370: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 371: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 372: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 373: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 374: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 375: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 376: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 377: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 378: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 379: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 380: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 381: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 382: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 383: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 384: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 385: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 386: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 387: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 388: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 389: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 390: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 391: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 392: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 393: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 394: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 395: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 396: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 397: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 398: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 399: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 400: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 401: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 402: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 403: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 404: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 405: _t->startDrawObject(); break;
        case 406: _t->stopDrawObject(); break;
        case 407: _t->saveDrawObject(); break;
        case 408: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 409: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 410: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 411: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 412: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 413: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 414: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 415: _t->saveObject(); break;
        case 416: _t->clearObject(); break;
        case 417: _t->clearObjectAll(); break;
        case 418: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 419: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 420: _t->undoObject(); break;
        case 421: _t->clearRotateList(); break;
        case 422: _t->setRotateList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 423: _t->startPatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 424: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 425: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 426: _t->clearFlagStop(); break;
        case 427: _t->slam_fullautoInit(); break;
        case 428: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 429: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 430: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 431: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 432: _t->clear_call(); break;
        case 433: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 434: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 435: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 436: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 437: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 438: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 439: _t->usbsave(); break;
        case 440: _t->restartUpdate(); break;
        case 441: _t->startUpdate(); break;
        case 442: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 443: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 444: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 445: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 446: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
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
        if (_id < 447)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 447;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 447)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 447;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
