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
    QByteArrayData data[562];
    char stringdata0[7261];
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
QT_MOC_LITERAL(103, 1220, 23), // "setMovingPageBackground"
QT_MOC_LITERAL(104, 1244, 23), // "getMovingPageBackground"
QT_MOC_LITERAL(105, 1268, 17), // "setMovingPageMode"
QT_MOC_LITERAL(106, 1286, 17), // "getMovingPageMode"
QT_MOC_LITERAL(107, 1304, 18), // "setMovingPageColor"
QT_MOC_LITERAL(108, 1323, 18), // "getMovingPageColor"
QT_MOC_LITERAL(109, 1342, 18), // "setMovingPageImage"
QT_MOC_LITERAL(110, 1361, 18), // "getMovingPageImage"
QT_MOC_LITERAL(111, 1380, 18), // "setMovingPageVideo"
QT_MOC_LITERAL(112, 1399, 18), // "getMovingPageVideo"
QT_MOC_LITERAL(113, 1418, 18), // "setMovingPageAudio"
QT_MOC_LITERAL(114, 1437, 18), // "getMovingPageAudio"
QT_MOC_LITERAL(115, 1456, 15), // "clearPatrolPage"
QT_MOC_LITERAL(116, 1472, 19), // "getPatrolObjectSize"
QT_MOC_LITERAL(117, 1492, 17), // "getPageObjectType"
QT_MOC_LITERAL(118, 1510, 19), // "getPageObjectSource"
QT_MOC_LITERAL(119, 1530, 18), // "getPageObjectColor"
QT_MOC_LITERAL(120, 1549, 14), // "getPageObjectX"
QT_MOC_LITERAL(121, 1564, 14), // "getPageObjectY"
QT_MOC_LITERAL(122, 1579, 18), // "getPageObjectWidth"
QT_MOC_LITERAL(123, 1598, 19), // "getPageObjectHeight"
QT_MOC_LITERAL(124, 1618, 21), // "getPageObjectFontsize"
QT_MOC_LITERAL(125, 1640, 15), // "addPatrolObject"
QT_MOC_LITERAL(126, 1656, 4), // "page"
QT_MOC_LITERAL(127, 1661, 3), // "obj"
QT_MOC_LITERAL(128, 1665, 19), // "setPageObjectSource"
QT_MOC_LITERAL(129, 1685, 3), // "src"
QT_MOC_LITERAL(130, 1689, 18), // "setPageObjectColor"
QT_MOC_LITERAL(131, 1708, 5), // "color"
QT_MOC_LITERAL(132, 1714, 18), // "deletePatrolObject"
QT_MOC_LITERAL(133, 1733, 16), // "movePatrolObject"
QT_MOC_LITERAL(134, 1750, 1), // "x"
QT_MOC_LITERAL(135, 1752, 1), // "y"
QT_MOC_LITERAL(136, 1754, 19), // "setPatrolObjectSize"
QT_MOC_LITERAL(137, 1774, 5), // "point"
QT_MOC_LITERAL(138, 1780, 5), // "width"
QT_MOC_LITERAL(139, 1786, 6), // "height"
QT_MOC_LITERAL(140, 1793, 16), // "getPageObjectNum"
QT_MOC_LITERAL(141, 1810, 19), // "confirmLocalization"
QT_MOC_LITERAL(142, 1830, 7), // "setName"
QT_MOC_LITERAL(143, 1838, 7), // "setTool"
QT_MOC_LITERAL(144, 1846, 7), // "getTool"
QT_MOC_LITERAL(145, 1854, 7), // "setMode"
QT_MOC_LITERAL(146, 1862, 9), // "setEnable"
QT_MOC_LITERAL(147, 1872, 2), // "en"
QT_MOC_LITERAL(148, 1875, 7), // "getMode"
QT_MOC_LITERAL(149, 1883, 12), // "setShowBrush"
QT_MOC_LITERAL(150, 1896, 5), // "onoff"
QT_MOC_LITERAL(151, 1902, 12), // "setShowLidar"
QT_MOC_LITERAL(152, 1915, 15), // "setShowLocation"
QT_MOC_LITERAL(153, 1931, 17), // "setRobotFollowing"
QT_MOC_LITERAL(154, 1949, 17), // "setShowTravelline"
QT_MOC_LITERAL(155, 1967, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(156, 1986, 13), // "setShowObject"
QT_MOC_LITERAL(157, 2000, 11), // "setInitFlag"
QT_MOC_LITERAL(158, 2012, 15), // "getshowLocation"
QT_MOC_LITERAL(159, 2028, 17), // "getRobotFollowing"
QT_MOC_LITERAL(160, 2046, 12), // "getShowLidar"
QT_MOC_LITERAL(161, 2059, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(162, 2075, 11), // "setInitPose"
QT_MOC_LITERAL(163, 2087, 2), // "th"
QT_MOC_LITERAL(164, 2090, 13), // "clearInitPose"
QT_MOC_LITERAL(165, 2104, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(166, 2125, 17), // "startDrawingTline"
QT_MOC_LITERAL(167, 2143, 16), // "stopDrawingTline"
QT_MOC_LITERAL(168, 2160, 15), // "getDrawingTline"
QT_MOC_LITERAL(169, 2176, 13), // "setRulerPoint"
QT_MOC_LITERAL(170, 2190, 11), // "setBoxPoint"
QT_MOC_LITERAL(171, 2202, 11), // "getPointBox"
QT_MOC_LITERAL(172, 2214, 13), // "saveRotateMap"
QT_MOC_LITERAL(173, 2228, 10), // "initRotate"
QT_MOC_LITERAL(174, 2239, 9), // "rotateMap"
QT_MOC_LITERAL(175, 2249, 5), // "angle"
QT_MOC_LITERAL(176, 2255, 11), // "rotateMapCW"
QT_MOC_LITERAL(177, 2267, 12), // "rotateMapCCW"
QT_MOC_LITERAL(178, 2280, 13), // "saveObjectPNG"
QT_MOC_LITERAL(179, 2294, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(180, 2309, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(181, 2332, 14), // "getDrawingFlag"
QT_MOC_LITERAL(182, 2347, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(183, 2366, 12), // "startDrawing"
QT_MOC_LITERAL(184, 2379, 12), // "addLinePoint"
QT_MOC_LITERAL(185, 2392, 10), // "endDrawing"
QT_MOC_LITERAL(186, 2403, 10), // "setMapOrin"
QT_MOC_LITERAL(187, 2414, 16), // "startDrawingRect"
QT_MOC_LITERAL(188, 2431, 14), // "setDrawingRect"
QT_MOC_LITERAL(189, 2446, 14), // "endDrawingRect"
QT_MOC_LITERAL(190, 2461, 12), // "clearDrawing"
QT_MOC_LITERAL(191, 2474, 8), // "undoLine"
QT_MOC_LITERAL(192, 2483, 8), // "redoLine"
QT_MOC_LITERAL(193, 2492, 11), // "startSpline"
QT_MOC_LITERAL(194, 2504, 9), // "addSpline"
QT_MOC_LITERAL(195, 2514, 10), // "drawSpline"
QT_MOC_LITERAL(196, 2525, 9), // "endSpline"
QT_MOC_LITERAL(197, 2535, 4), // "save"
QT_MOC_LITERAL(198, 2540, 16), // "startDrawingLine"
QT_MOC_LITERAL(199, 2557, 14), // "setDrawingLine"
QT_MOC_LITERAL(200, 2572, 15), // "stopDrawingLine"
QT_MOC_LITERAL(201, 2588, 12), // "setLineColor"
QT_MOC_LITERAL(202, 2601, 12), // "setLineWidth"
QT_MOC_LITERAL(203, 2614, 7), // "pressed"
QT_MOC_LITERAL(204, 2622, 4), // "tool"
QT_MOC_LITERAL(205, 2627, 14), // "double_pressed"
QT_MOC_LITERAL(206, 2642, 2), // "x1"
QT_MOC_LITERAL(207, 2645, 2), // "y1"
QT_MOC_LITERAL(208, 2648, 2), // "x2"
QT_MOC_LITERAL(209, 2651, 2), // "y2"
QT_MOC_LITERAL(210, 2654, 5), // "moved"
QT_MOC_LITERAL(211, 2660, 12), // "double_moved"
QT_MOC_LITERAL(212, 2673, 8), // "released"
QT_MOC_LITERAL(213, 2682, 15), // "double_released"
QT_MOC_LITERAL(214, 2698, 14), // "getLocationNum"
QT_MOC_LITERAL(215, 2713, 12), // "saveLocation"
QT_MOC_LITERAL(216, 2726, 8), // "groupnum"
QT_MOC_LITERAL(217, 2735, 13), // "clearLocation"
QT_MOC_LITERAL(218, 2749, 11), // "addLocation"
QT_MOC_LITERAL(219, 2761, 14), // "addLocationCur"
QT_MOC_LITERAL(220, 2776, 11), // "setLocation"
QT_MOC_LITERAL(221, 2788, 12), // "editLocation"
QT_MOC_LITERAL(222, 2801, 14), // "removeLocation"
QT_MOC_LITERAL(223, 2816, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(224, 2835, 14), // "getLocGroupNum"
QT_MOC_LITERAL(225, 2850, 7), // "saveMap"
QT_MOC_LITERAL(226, 2858, 13), // "saveEditedMap"
QT_MOC_LITERAL(227, 2872, 9), // "saveTline"
QT_MOC_LITERAL(228, 2882, 13), // "saveTlineTemp"
QT_MOC_LITERAL(229, 2896, 10), // "saveVelmap"
QT_MOC_LITERAL(230, 2907, 10), // "setMapSize"
QT_MOC_LITERAL(231, 2918, 6), // "zoomIn"
QT_MOC_LITERAL(232, 2925, 4), // "dist"
QT_MOC_LITERAL(233, 2930, 7), // "zoomOut"
QT_MOC_LITERAL(234, 2938, 4), // "move"
QT_MOC_LITERAL(235, 2943, 12), // "getFileWidth"
QT_MOC_LITERAL(236, 2956, 4), // "getX"
QT_MOC_LITERAL(237, 2961, 4), // "getY"
QT_MOC_LITERAL(238, 2966, 8), // "getScale"
QT_MOC_LITERAL(239, 2975, 13), // "setVelmapView"
QT_MOC_LITERAL(240, 2989, 12), // "setTlineView"
QT_MOC_LITERAL(241, 3002, 13), // "setObjectView"
QT_MOC_LITERAL(242, 3016, 15), // "setAvoidmapView"
QT_MOC_LITERAL(243, 3032, 15), // "setLocationView"
QT_MOC_LITERAL(244, 3048, 12), // "setRobotView"
QT_MOC_LITERAL(245, 3061, 15), // "setSystemVolume"
QT_MOC_LITERAL(246, 3077, 19), // "requestSystemVolume"
QT_MOC_LITERAL(247, 3097, 7), // "setSize"
QT_MOC_LITERAL(248, 3105, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(249, 3119, 14), // "selectLocation"
QT_MOC_LITERAL(250, 3134, 8), // "writelog"
QT_MOC_LITERAL(251, 3143, 3), // "msg"
QT_MOC_LITERAL(252, 3147, 18), // "startDrawingObject"
QT_MOC_LITERAL(253, 3166, 17), // "stopDrawingObject"
QT_MOC_LITERAL(254, 3184, 17), // "saveDrawingObject"
QT_MOC_LITERAL(255, 3202, 13), // "setLocationUp"
QT_MOC_LITERAL(256, 3216, 15), // "setLocationDown"
QT_MOC_LITERAL(257, 3232, 8), // "checkINI"
QT_MOC_LITERAL(258, 3241, 8), // "killSLAM"
QT_MOC_LITERAL(259, 3250, 12), // "makeRobotINI"
QT_MOC_LITERAL(260, 3263, 13), // "checkRobotINI"
QT_MOC_LITERAL(261, 3277, 11), // "restartSLAM"
QT_MOC_LITERAL(262, 3289, 9), // "startSLAM"
QT_MOC_LITERAL(263, 3299, 16), // "getIPCConnection"
QT_MOC_LITERAL(264, 3316, 8), // "getIPCRX"
QT_MOC_LITERAL(265, 3325, 8), // "getIPCTX"
QT_MOC_LITERAL(266, 3334, 14), // "programRestart"
QT_MOC_LITERAL(267, 3349, 11), // "programExit"
QT_MOC_LITERAL(268, 3361, 13), // "getRawMapPath"
QT_MOC_LITERAL(269, 3375, 10), // "getMapPath"
QT_MOC_LITERAL(270, 3386, 12), // "getAnnotPath"
QT_MOC_LITERAL(271, 3399, 11), // "getMetaPath"
QT_MOC_LITERAL(272, 3411, 13), // "getTravelPath"
QT_MOC_LITERAL(273, 3425, 11), // "getCostPath"
QT_MOC_LITERAL(274, 3437, 10), // "getIniPath"
QT_MOC_LITERAL(275, 3448, 10), // "setSetting"
QT_MOC_LITERAL(276, 3459, 5), // "value"
QT_MOC_LITERAL(277, 3465, 11), // "readSetting"
QT_MOC_LITERAL(278, 3477, 8), // "map_name"
QT_MOC_LITERAL(279, 3486, 10), // "getSetting"
QT_MOC_LITERAL(280, 3497, 10), // "getTrayNum"
QT_MOC_LITERAL(281, 3508, 14), // "setTableColNum"
QT_MOC_LITERAL(282, 3523, 7), // "col_num"
QT_MOC_LITERAL(283, 3531, 12), // "getRobotType"
QT_MOC_LITERAL(284, 3544, 13), // "requestCamera"
QT_MOC_LITERAL(285, 3558, 13), // "getLeftCamera"
QT_MOC_LITERAL(286, 3572, 14), // "getRightCamera"
QT_MOC_LITERAL(287, 3587, 9), // "setCamera"
QT_MOC_LITERAL(288, 3597, 4), // "left"
QT_MOC_LITERAL(289, 3602, 5), // "right"
QT_MOC_LITERAL(290, 3608, 12), // "getCameraNum"
QT_MOC_LITERAL(291, 3621, 15), // "getCameraSerial"
QT_MOC_LITERAL(292, 3637, 13), // "setCursorView"
QT_MOC_LITERAL(293, 3651, 7), // "visible"
QT_MOC_LITERAL(294, 3659, 8), // "getVoice"
QT_MOC_LITERAL(295, 3668, 15), // "checkTravelline"
QT_MOC_LITERAL(296, 3684, 13), // "updateProgram"
QT_MOC_LITERAL(297, 3698, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(298, 3719, 17), // "checkVersionAgain"
QT_MOC_LITERAL(299, 3737, 12), // "isNewVersion"
QT_MOC_LITERAL(300, 3750, 12), // "isNeedUpdate"
QT_MOC_LITERAL(301, 3763, 15), // "getLocalVersion"
QT_MOC_LITERAL(302, 3779, 16), // "getServerVersion"
QT_MOC_LITERAL(303, 3796, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(304, 3816, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(305, 3839, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(306, 3863, 13), // "getUpdateDate"
QT_MOC_LITERAL(307, 3877, 13), // "getUpdateSize"
QT_MOC_LITERAL(308, 3891, 17), // "getUpdateFileName"
QT_MOC_LITERAL(309, 3909, 15), // "getUpdateCommit"
QT_MOC_LITERAL(310, 3925, 16), // "getCurrentCommit"
QT_MOC_LITERAL(311, 3942, 16), // "getUpdateMessage"
QT_MOC_LITERAL(312, 3959, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(313, 3977, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(314, 3999, 11), // "checkUpdate"
QT_MOC_LITERAL(315, 4011, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(316, 4033, 11), // "setlanguage"
QT_MOC_LITERAL(317, 4045, 13), // "isCallingMode"
QT_MOC_LITERAL(318, 4059, 9), // "goServing"
QT_MOC_LITERAL(319, 4069, 5), // "table"
QT_MOC_LITERAL(320, 4075, 17), // "getLocationbyCall"
QT_MOC_LITERAL(321, 4093, 8), // "LOCATION"
QT_MOC_LITERAL(322, 4102, 4), // "call"
QT_MOC_LITERAL(323, 4107, 11), // "getLocation"
QT_MOC_LITERAL(324, 4119, 15), // "getLocationbyID"
QT_MOC_LITERAL(325, 4135, 2), // "id"
QT_MOC_LITERAL(326, 4138, 10), // "setUiState"
QT_MOC_LITERAL(327, 4149, 5), // "state"
QT_MOC_LITERAL(328, 4155, 17), // "resetLocalization"
QT_MOC_LITERAL(329, 4173, 6), // "setLog"
QT_MOC_LITERAL(330, 4180, 13), // "getLogLineNum"
QT_MOC_LITERAL(331, 4194, 10), // "getLogLine"
QT_MOC_LITERAL(332, 4205, 10), // "getLogDate"
QT_MOC_LITERAL(333, 4216, 10), // "getLogAuth"
QT_MOC_LITERAL(334, 4227, 13), // "getLogMessage"
QT_MOC_LITERAL(335, 4241, 7), // "readLog"
QT_MOC_LITERAL(336, 4249, 4), // "date"
QT_MOC_LITERAL(337, 4254, 13), // "getLocaleDate"
QT_MOC_LITERAL(338, 4268, 4), // "year"
QT_MOC_LITERAL(339, 4273, 5), // "month"
QT_MOC_LITERAL(340, 4279, 9), // "updateUSB"
QT_MOC_LITERAL(341, 4289, 10), // "getusbsize"
QT_MOC_LITERAL(342, 4300, 17), // "readusbrecentfile"
QT_MOC_LITERAL(343, 4318, 14), // "getusbfilesize"
QT_MOC_LITERAL(344, 4333, 10), // "getusbfile"
QT_MOC_LITERAL(345, 4344, 16), // "getusbrecentfile"
QT_MOC_LITERAL(346, 4361, 10), // "getusbname"
QT_MOC_LITERAL(347, 4372, 7), // "readusb"
QT_MOC_LITERAL(348, 4380, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(349, 4395, 4), // "path"
QT_MOC_LITERAL(350, 4400, 15), // "isConnectServer"
QT_MOC_LITERAL(351, 4416, 9), // "isLoadMap"
QT_MOC_LITERAL(352, 4426, 10), // "isExistMap"
QT_MOC_LITERAL(353, 4437, 13), // "isExistRawMap"
QT_MOC_LITERAL(354, 4451, 15), // "isExistTlineMap"
QT_MOC_LITERAL(355, 4467, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(356, 4483, 13), // "isExistVelMap"
QT_MOC_LITERAL(357, 4497, 16), // "isExistObjectMap"
QT_MOC_LITERAL(358, 4514, 16), // "isExistTravelMap"
QT_MOC_LITERAL(359, 4531, 17), // "isExistAnnotation"
QT_MOC_LITERAL(360, 4549, 15), // "isExistRobotINI"
QT_MOC_LITERAL(361, 4565, 15), // "getAvailableMap"
QT_MOC_LITERAL(362, 4581, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(363, 4601, 14), // "getMapFileSize"
QT_MOC_LITERAL(364, 4616, 10), // "getMapFile"
QT_MOC_LITERAL(365, 4627, 15), // "deleteEditedMap"
QT_MOC_LITERAL(366, 4643, 16), // "deleteAnnotation"
QT_MOC_LITERAL(367, 4660, 9), // "removeMap"
QT_MOC_LITERAL(368, 4670, 8), // "filename"
QT_MOC_LITERAL(369, 4679, 7), // "loadMap"
QT_MOC_LITERAL(370, 4687, 7), // "copyMap"
QT_MOC_LITERAL(371, 4695, 8), // "orinname"
QT_MOC_LITERAL(372, 4704, 7), // "newname"
QT_MOC_LITERAL(373, 4712, 10), // "rotate_map"
QT_MOC_LITERAL(374, 4723, 4), // "_src"
QT_MOC_LITERAL(375, 4728, 4), // "_dst"
QT_MOC_LITERAL(376, 4733, 12), // "startMapping"
QT_MOC_LITERAL(377, 4746, 7), // "mapsize"
QT_MOC_LITERAL(378, 4754, 4), // "grid"
QT_MOC_LITERAL(379, 4759, 11), // "stopMapping"
QT_MOC_LITERAL(380, 4771, 11), // "setSLAMMode"
QT_MOC_LITERAL(381, 4783, 11), // "saveMapping"
QT_MOC_LITERAL(382, 4795, 13), // "setInitCurPos"
QT_MOC_LITERAL(383, 4809, 10), // "setInitPos"
QT_MOC_LITERAL(384, 4820, 12), // "getInitPoseX"
QT_MOC_LITERAL(385, 4833, 12), // "getInitPoseY"
QT_MOC_LITERAL(386, 4846, 13), // "getInitPoseTH"
QT_MOC_LITERAL(387, 4860, 12), // "slam_setInit"
QT_MOC_LITERAL(388, 4873, 8), // "slam_run"
QT_MOC_LITERAL(389, 4882, 9), // "slam_stop"
QT_MOC_LITERAL(390, 4892, 13), // "slam_autoInit"
QT_MOC_LITERAL(391, 4906, 15), // "is_slam_running"
QT_MOC_LITERAL(392, 4922, 14), // "getMappingflag"
QT_MOC_LITERAL(393, 4937, 16), // "getObjectingflag"
QT_MOC_LITERAL(394, 4954, 16), // "setObjectingflag"
QT_MOC_LITERAL(395, 4971, 4), // "flag"
QT_MOC_LITERAL(396, 4976, 13), // "getnewMapname"
QT_MOC_LITERAL(397, 4990, 11), // "getLastCall"
QT_MOC_LITERAL(398, 5002, 11), // "getCallSize"
QT_MOC_LITERAL(399, 5014, 16), // "getCallQueueSize"
QT_MOC_LITERAL(400, 5031, 9), // "cleanTray"
QT_MOC_LITERAL(401, 5041, 11), // "getCallName"
QT_MOC_LITERAL(402, 5053, 14), // "clearCallQueue"
QT_MOC_LITERAL(403, 5068, 7), // "getCall"
QT_MOC_LITERAL(404, 5076, 15), // "getCallLocation"
QT_MOC_LITERAL(405, 5092, 11), // "setCallbell"
QT_MOC_LITERAL(406, 5104, 16), // "setCallbellForce"
QT_MOC_LITERAL(407, 5121, 10), // "acceptCall"
QT_MOC_LITERAL(408, 5132, 3), // "yes"
QT_MOC_LITERAL(409, 5136, 10), // "setObjPose"
QT_MOC_LITERAL(410, 5147, 14), // "getServingName"
QT_MOC_LITERAL(411, 5162, 15), // "getLocationName"
QT_MOC_LITERAL(412, 5178, 15), // "getLocationType"
QT_MOC_LITERAL(413, 5194, 17), // "getLocationNumber"
QT_MOC_LITERAL(414, 5212, 17), // "setLocationNumber"
QT_MOC_LITERAL(415, 5230, 15), // "getLocationSize"
QT_MOC_LITERAL(416, 5246, 16), // "getLocationGroup"
QT_MOC_LITERAL(417, 5263, 13), // "getLocationID"
QT_MOC_LITERAL(418, 5277, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(419, 5297, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(420, 5318, 17), // "getLocationCallID"
QT_MOC_LITERAL(421, 5336, 16), // "setLocationGroup"
QT_MOC_LITERAL(422, 5353, 19), // "removeLocationGroup"
QT_MOC_LITERAL(423, 5373, 16), // "addLocationGroup"
QT_MOC_LITERAL(424, 5390, 15), // "getLocGroupname"
QT_MOC_LITERAL(425, 5406, 8), // "tablenum"
QT_MOC_LITERAL(426, 5415, 12), // "getLocationX"
QT_MOC_LITERAL(427, 5428, 12), // "getLocationY"
QT_MOC_LITERAL(428, 5441, 13), // "getLocationTH"
QT_MOC_LITERAL(429, 5455, 15), // "isExistLocation"
QT_MOC_LITERAL(430, 5471, 8), // "getLidar"
QT_MOC_LITERAL(431, 5480, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(432, 5497, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(433, 5514, 17), // "clearSharedMemory"
QT_MOC_LITERAL(434, 5532, 12), // "getObjectNum"
QT_MOC_LITERAL(435, 5545, 13), // "getObjectName"
QT_MOC_LITERAL(436, 5559, 18), // "getObjectPointSize"
QT_MOC_LITERAL(437, 5578, 10), // "getObjectX"
QT_MOC_LITERAL(438, 5589, 10), // "getObjectY"
QT_MOC_LITERAL(439, 5600, 14), // "getObjPointNum"
QT_MOC_LITERAL(440, 5615, 7), // "obj_num"
QT_MOC_LITERAL(441, 5623, 9), // "getLocNum"
QT_MOC_LITERAL(442, 5633, 13), // "saveLocations"
QT_MOC_LITERAL(443, 5647, 13), // "getObjectSize"
QT_MOC_LITERAL(444, 5661, 12), // "removeObject"
QT_MOC_LITERAL(445, 5674, 14), // "saveAnnotation"
QT_MOC_LITERAL(446, 5689, 8), // "isOdroid"
QT_MOC_LITERAL(447, 5698, 13), // "getMultiState"
QT_MOC_LITERAL(448, 5712, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(449, 5732, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(450, 5751, 15), // "getRunawayState"
QT_MOC_LITERAL(451, 5767, 15), // "slam_map_reload"
QT_MOC_LITERAL(452, 5783, 15), // "slam_ini_reload"
QT_MOC_LITERAL(453, 5799, 7), // "setTray"
QT_MOC_LITERAL(454, 5807, 8), // "tray_num"
QT_MOC_LITERAL(455, 5816, 12), // "startServing"
QT_MOC_LITERAL(456, 5829, 9), // "setPreset"
QT_MOC_LITERAL(457, 5839, 6), // "preset"
QT_MOC_LITERAL(458, 5846, 13), // "confirmPickup"
QT_MOC_LITERAL(459, 5860, 14), // "getPickuptrays"
QT_MOC_LITERAL(460, 5875, 10), // "QList<int>"
QT_MOC_LITERAL(461, 5886, 9), // "movePause"
QT_MOC_LITERAL(462, 5896, 10), // "moveResume"
QT_MOC_LITERAL(463, 5907, 12), // "moveStopFlag"
QT_MOC_LITERAL(464, 5920, 8), // "moveStop"
QT_MOC_LITERAL(465, 5929, 12), // "moveToCharge"
QT_MOC_LITERAL(466, 5942, 10), // "moveToWait"
QT_MOC_LITERAL(467, 5953, 14), // "moveToCleaning"
QT_MOC_LITERAL(468, 5968, 9), // "getcurLoc"
QT_MOC_LITERAL(469, 5978, 11), // "getcurTable"
QT_MOC_LITERAL(470, 5990, 16), // "resetHomeFolders"
QT_MOC_LITERAL(471, 6007, 13), // "issetLocation"
QT_MOC_LITERAL(472, 6021, 6), // "number"
QT_MOC_LITERAL(473, 6028, 11), // "getObsState"
QT_MOC_LITERAL(474, 6040, 10), // "getBattery"
QT_MOC_LITERAL(475, 6051, 13), // "getMotorState"
QT_MOC_LITERAL(476, 6065, 20), // "getLocalizationState"
QT_MOC_LITERAL(477, 6086, 14), // "getStateMoving"
QT_MOC_LITERAL(478, 6101, 10), // "getErrcode"
QT_MOC_LITERAL(479, 6112, 12), // "getRobotName"
QT_MOC_LITERAL(480, 6125, 18), // "getMotorConnection"
QT_MOC_LITERAL(481, 6144, 14), // "getMotorStatus"
QT_MOC_LITERAL(482, 6159, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(483, 6177, 19), // "getMotorTemperature"
QT_MOC_LITERAL(484, 6197, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(485, 6223, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(486, 6250, 15), // "getMotorCurrent"
QT_MOC_LITERAL(487, 6266, 14), // "getPowerStatus"
QT_MOC_LITERAL(488, 6281, 15), // "getRemoteStatus"
QT_MOC_LITERAL(489, 6297, 22), // "getChargeConnectStatus"
QT_MOC_LITERAL(490, 6320, 15), // "getChargeStatus"
QT_MOC_LITERAL(491, 6336, 12), // "getEmoStatus"
QT_MOC_LITERAL(492, 6349, 13), // "getLockStatus"
QT_MOC_LITERAL(493, 6363, 12), // "getBatteryIn"
QT_MOC_LITERAL(494, 6376, 13), // "getBatteryOut"
QT_MOC_LITERAL(495, 6390, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(496, 6408, 8), // "getPower"
QT_MOC_LITERAL(497, 6417, 13), // "getPowerTotal"
QT_MOC_LITERAL(498, 6431, 12), // "getObsinPath"
QT_MOC_LITERAL(499, 6444, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(500, 6462, 12), // "setMotorLock"
QT_MOC_LITERAL(501, 6475, 14), // "getRobotRadius"
QT_MOC_LITERAL(502, 6490, 9), // "getRobotx"
QT_MOC_LITERAL(503, 6500, 9), // "getRoboty"
QT_MOC_LITERAL(504, 6510, 10), // "getRobotth"
QT_MOC_LITERAL(505, 6521, 13), // "getlastRobotx"
QT_MOC_LITERAL(506, 6535, 13), // "getlastRoboty"
QT_MOC_LITERAL(507, 6549, 14), // "getlastRobotth"
QT_MOC_LITERAL(508, 6564, 10), // "getPathNum"
QT_MOC_LITERAL(509, 6575, 8), // "getPathx"
QT_MOC_LITERAL(510, 6584, 8), // "getPathy"
QT_MOC_LITERAL(511, 6593, 9), // "getPathth"
QT_MOC_LITERAL(512, 6603, 15), // "getLocalPathNum"
QT_MOC_LITERAL(513, 6619, 13), // "getLocalPathx"
QT_MOC_LITERAL(514, 6633, 13), // "getLocalPathy"
QT_MOC_LITERAL(515, 6647, 10), // "getuistate"
QT_MOC_LITERAL(516, 6658, 10), // "getMapname"
QT_MOC_LITERAL(517, 6669, 10), // "getMappath"
QT_MOC_LITERAL(518, 6680, 11), // "getMapWidth"
QT_MOC_LITERAL(519, 6692, 12), // "getMapHeight"
QT_MOC_LITERAL(520, 6705, 12), // "getGridWidth"
QT_MOC_LITERAL(521, 6718, 9), // "getOrigin"
QT_MOC_LITERAL(522, 6728, 15), // "getMappingWidth"
QT_MOC_LITERAL(523, 6744, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(524, 6764, 17), // "getObjectPointNum"
QT_MOC_LITERAL(525, 6782, 9), // "addObject"
QT_MOC_LITERAL(526, 6792, 14), // "addObjectPoint"
QT_MOC_LITERAL(527, 6807, 9), // "setObject"
QT_MOC_LITERAL(528, 6817, 15), // "editObjectStart"
QT_MOC_LITERAL(529, 6833, 10), // "editObject"
QT_MOC_LITERAL(530, 6844, 10), // "saveObject"
QT_MOC_LITERAL(531, 6855, 11), // "clearObject"
QT_MOC_LITERAL(532, 6867, 14), // "clearObjectAll"
QT_MOC_LITERAL(533, 6882, 12), // "selectObject"
QT_MOC_LITERAL(534, 6895, 13), // "getObjectflag"
QT_MOC_LITERAL(535, 6909, 10), // "undoObject"
QT_MOC_LITERAL(536, 6920, 15), // "clearRotateList"
QT_MOC_LITERAL(537, 6936, 13), // "setRotateList"
QT_MOC_LITERAL(538, 6950, 6), // "pickup"
QT_MOC_LITERAL(539, 6957, 11), // "getICPRatio"
QT_MOC_LITERAL(540, 6969, 11), // "getICPError"
QT_MOC_LITERAL(541, 6981, 13), // "clearFlagStop"
QT_MOC_LITERAL(542, 6995, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(543, 7013, 17), // "moveToServingTest"
QT_MOC_LITERAL(544, 7031, 15), // "getusberrorsize"
QT_MOC_LITERAL(545, 7047, 11), // "getusberror"
QT_MOC_LITERAL(546, 7059, 11), // "getzipstate"
QT_MOC_LITERAL(547, 7071, 10), // "clear_call"
QT_MOC_LITERAL(548, 7082, 7), // "usbsave"
QT_MOC_LITERAL(549, 7090, 3), // "usb"
QT_MOC_LITERAL(550, 7094, 3), // "_ui"
QT_MOC_LITERAL(551, 7098, 5), // "_slam"
QT_MOC_LITERAL(552, 7104, 7), // "_config"
QT_MOC_LITERAL(553, 7112, 4), // "_map"
QT_MOC_LITERAL(554, 7117, 4), // "_log"
QT_MOC_LITERAL(555, 7122, 13), // "restartUpdate"
QT_MOC_LITERAL(556, 7136, 11), // "startUpdate"
QT_MOC_LITERAL(557, 7148, 18), // "getTravellineIssue"
QT_MOC_LITERAL(558, 7167, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(559, 7191, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(560, 7214, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(561, 7236, 24) // "getTravellineIssueBroken"

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
    "file\0makeTTS\0lan\0playTTS\0"
    "setMovingPageBackground\0getMovingPageBackground\0"
    "setMovingPageMode\0getMovingPageMode\0"
    "setMovingPageColor\0getMovingPageColor\0"
    "setMovingPageImage\0getMovingPageImage\0"
    "setMovingPageVideo\0getMovingPageVideo\0"
    "setMovingPageAudio\0getMovingPageAudio\0"
    "clearPatrolPage\0getPatrolObjectSize\0"
    "getPageObjectType\0getPageObjectSource\0"
    "getPageObjectColor\0getPageObjectX\0"
    "getPageObjectY\0getPageObjectWidth\0"
    "getPageObjectHeight\0getPageObjectFontsize\0"
    "addPatrolObject\0page\0obj\0setPageObjectSource\0"
    "src\0setPageObjectColor\0color\0"
    "deletePatrolObject\0movePatrolObject\0"
    "x\0y\0setPatrolObjectSize\0point\0width\0"
    "height\0getPageObjectNum\0confirmLocalization\0"
    "setName\0setTool\0getTool\0setMode\0"
    "setEnable\0en\0getMode\0setShowBrush\0"
    "onoff\0setShowLidar\0setShowLocation\0"
    "setRobotFollowing\0setShowTravelline\0"
    "setShowVelocitymap\0setShowObject\0"
    "setInitFlag\0getshowLocation\0"
    "getRobotFollowing\0getShowLidar\0"
    "setShowAvoidmap\0setInitPose\0th\0"
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
    "setLineColor\0setLineWidth\0pressed\0"
    "tool\0double_pressed\0x1\0y1\0x2\0y2\0moved\0"
    "double_moved\0released\0double_released\0"
    "getLocationNum\0saveLocation\0groupnum\0"
    "clearLocation\0addLocation\0addLocationCur\0"
    "setLocation\0editLocation\0removeLocation\0"
    "setTableNumberAuto\0getLocGroupNum\0"
    "saveMap\0saveEditedMap\0saveTline\0"
    "saveTlineTemp\0saveVelmap\0setMapSize\0"
    "zoomIn\0dist\0zoomOut\0move\0getFileWidth\0"
    "getX\0getY\0getScale\0setVelmapView\0"
    "setTlineView\0setObjectView\0setAvoidmapView\0"
    "setLocationView\0setRobotView\0"
    "setSystemVolume\0requestSystemVolume\0"
    "setSize\0getCutBoxFlag\0selectLocation\0"
    "writelog\0msg\0startDrawingObject\0"
    "stopDrawingObject\0saveDrawingObject\0"
    "setLocationUp\0setLocationDown\0checkINI\0"
    "killSLAM\0makeRobotINI\0checkRobotINI\0"
    "restartSLAM\0startSLAM\0getIPCConnection\0"
    "getIPCRX\0getIPCTX\0programRestart\0"
    "programExit\0getRawMapPath\0getMapPath\0"
    "getAnnotPath\0getMetaPath\0getTravelPath\0"
    "getCostPath\0getIniPath\0setSetting\0"
    "value\0readSetting\0map_name\0getSetting\0"
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
    "getObjectX\0getObjectY\0getObjPointNum\0"
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
     524,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 2634,    2, 0x0a /* Public */,
       3,    0, 2635,    2, 0x0a /* Public */,
       4,    0, 2636,    2, 0x0a /* Public */,
       5,    0, 2637,    2, 0x0a /* Public */,
       6,    0, 2638,    2, 0x0a /* Public */,
       7,    0, 2639,    2, 0x0a /* Public */,
       8,    0, 2640,    2, 0x0a /* Public */,
       9,    0, 2641,    2, 0x0a /* Public */,
      10,    1, 2642,    2, 0x0a /* Public */,
      12,    1, 2645,    2, 0x0a /* Public */,
      13,    2, 2648,    2, 0x0a /* Public */,
      15,    1, 2653,    2, 0x0a /* Public */,
      16,    0, 2656,    2, 0x0a /* Public */,
      17,    0, 2657,    2, 0x0a /* Public */,
      18,    0, 2658,    2, 0x0a /* Public */,
      19,    0, 2659,    2, 0x0a /* Public */,
      20,    1, 2660,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      22,    0, 2663,    2, 0x02 /* Public */,
      23,    0, 2664,    2, 0x02 /* Public */,
      24,    2, 2665,    2, 0x02 /* Public */,
      26,    0, 2670,    2, 0x02 /* Public */,
      27,    0, 2671,    2, 0x02 /* Public */,
      28,    1, 2672,    2, 0x02 /* Public */,
      30,    0, 2675,    2, 0x02 /* Public */,
      31,    1, 2676,    2, 0x02 /* Public */,
      33,    2, 2679,    2, 0x02 /* Public */,
      35,    1, 2684,    2, 0x02 /* Public */,
      36,    1, 2687,    2, 0x02 /* Public */,
      37,    1, 2690,    2, 0x02 /* Public */,
      38,    1, 2693,    2, 0x02 /* Public */,
      39,    0, 2696,    2, 0x02 /* Public */,
      40,    0, 2697,    2, 0x02 /* Public */,
      41,    3, 2698,    2, 0x02 /* Public */,
      45,    0, 2705,    2, 0x02 /* Public */,
      46,    0, 2706,    2, 0x02 /* Public */,
      47,    0, 2707,    2, 0x02 /* Public */,
      48,    1, 2708,    2, 0x02 /* Public */,
      49,    1, 2711,    2, 0x02 /* Public */,
      50,    0, 2714,    2, 0x02 /* Public */,
      51,    0, 2715,    2, 0x02 /* Public */,
      52,    0, 2716,    2, 0x02 /* Public */,
      53,    0, 2717,    2, 0x02 /* Public */,
      54,    1, 2718,    2, 0x02 /* Public */,
      55,    1, 2721,    2, 0x02 /* Public */,
      56,    1, 2724,    2, 0x02 /* Public */,
      57,    1, 2727,    2, 0x02 /* Public */,
      58,    1, 2730,    2, 0x02 /* Public */,
      59,    1, 2733,    2, 0x02 /* Public */,
      60,    1, 2736,    2, 0x02 /* Public */,
      61,    1, 2739,    2, 0x02 /* Public */,
      62,    1, 2742,    2, 0x02 /* Public */,
      63,    1, 2745,    2, 0x02 /* Public */,
      64,    0, 2748,    2, 0x02 /* Public */,
      65,    0, 2749,    2, 0x02 /* Public */,
      66,    0, 2750,    2, 0x02 /* Public */,
      67,    1, 2751,    2, 0x02 /* Public */,
      68,    1, 2754,    2, 0x02 /* Public */,
      56,    2, 2757,    2, 0x02 /* Public */,
      70,    1, 2762,    2, 0x02 /* Public */,
      72,    1, 2765,    2, 0x02 /* Public */,
      73,    4, 2768,    2, 0x02 /* Public */,
      73,    3, 2777,    2, 0x22 /* Public | MethodCloned */,
      73,    2, 2784,    2, 0x22 /* Public | MethodCloned */,
      73,    1, 2789,    2, 0x22 /* Public | MethodCloned */,
      77,    4, 2792,    2, 0x02 /* Public */,
      77,    3, 2801,    2, 0x22 /* Public | MethodCloned */,
      77,    2, 2808,    2, 0x22 /* Public | MethodCloned */,
      77,    1, 2813,    2, 0x22 /* Public | MethodCloned */,
      78,    4, 2816,    2, 0x02 /* Public */,
      78,    3, 2825,    2, 0x22 /* Public | MethodCloned */,
      78,    2, 2832,    2, 0x22 /* Public | MethodCloned */,
      78,    1, 2837,    2, 0x22 /* Public | MethodCloned */,
      80,    5, 2840,    2, 0x02 /* Public */,
      84,    4, 2851,    2, 0x02 /* Public */,
      85,    1, 2860,    2, 0x02 /* Public */,
      86,    1, 2863,    2, 0x02 /* Public */,
      87,    2, 2866,    2, 0x02 /* Public */,
      88,    0, 2871,    2, 0x02 /* Public */,
      89,    0, 2872,    2, 0x02 /* Public */,
      90,    0, 2873,    2, 0x02 /* Public */,
      91,    2, 2874,    2, 0x02 /* Public */,
      91,    1, 2879,    2, 0x22 /* Public | MethodCloned */,
      93,    1, 2882,    2, 0x02 /* Public */,
      93,    0, 2885,    2, 0x22 /* Public | MethodCloned */,
      94,    0, 2886,    2, 0x02 /* Public */,
      95,    0, 2887,    2, 0x02 /* Public */,
      96,    2, 2888,    2, 0x02 /* Public */,
      96,    1, 2893,    2, 0x22 /* Public | MethodCloned */,
      96,    3, 2896,    2, 0x02 /* Public */,
      96,    2, 2903,    2, 0x22 /* Public | MethodCloned */,
      98,    2, 2908,    2, 0x02 /* Public */,
      98,    1, 2913,    2, 0x22 /* Public | MethodCloned */,
     100,    2, 2916,    2, 0x02 /* Public */,
     100,    1, 2921,    2, 0x22 /* Public | MethodCloned */,
     102,    0, 2924,    2, 0x02 /* Public */,
     103,    1, 2925,    2, 0x02 /* Public */,
     104,    0, 2928,    2, 0x02 /* Public */,
     105,    1, 2929,    2, 0x02 /* Public */,
     106,    0, 2932,    2, 0x02 /* Public */,
     107,    1, 2933,    2, 0x02 /* Public */,
     108,    0, 2936,    2, 0x02 /* Public */,
     109,    1, 2937,    2, 0x02 /* Public */,
     110,    0, 2940,    2, 0x02 /* Public */,
     111,    1, 2941,    2, 0x02 /* Public */,
     112,    0, 2944,    2, 0x02 /* Public */,
     113,    1, 2945,    2, 0x02 /* Public */,
     114,    0, 2948,    2, 0x02 /* Public */,
     115,    1, 2949,    2, 0x02 /* Public */,
     116,    0, 2952,    2, 0x02 /* Public */,
     117,    1, 2953,    2, 0x02 /* Public */,
     118,    1, 2956,    2, 0x02 /* Public */,
     119,    1, 2959,    2, 0x02 /* Public */,
     120,    1, 2962,    2, 0x02 /* Public */,
     121,    1, 2965,    2, 0x02 /* Public */,
     122,    1, 2968,    2, 0x02 /* Public */,
     123,    1, 2971,    2, 0x02 /* Public */,
     124,    1, 2974,    2, 0x02 /* Public */,
     125,    2, 2977,    2, 0x02 /* Public */,
     128,    2, 2982,    2, 0x02 /* Public */,
     130,    2, 2987,    2, 0x02 /* Public */,
     132,    1, 2992,    2, 0x02 /* Public */,
     133,    3, 2995,    2, 0x02 /* Public */,
     136,    4, 3002,    2, 0x02 /* Public */,
     136,    5, 3011,    2, 0x02 /* Public */,
     140,    2, 3022,    2, 0x02 /* Public */,
     141,    0, 3027,    2, 0x02 /* Public */,
     142,    1, 3028,    2, 0x02 /* Public */,
     143,    1, 3031,    2, 0x02 /* Public */,
     144,    0, 3034,    2, 0x02 /* Public */,
     145,    1, 3035,    2, 0x02 /* Public */,
     146,    1, 3038,    2, 0x02 /* Public */,
     148,    0, 3041,    2, 0x02 /* Public */,
     149,    1, 3042,    2, 0x02 /* Public */,
     151,    1, 3045,    2, 0x02 /* Public */,
     152,    1, 3048,    2, 0x02 /* Public */,
     153,    1, 3051,    2, 0x02 /* Public */,
     154,    1, 3054,    2, 0x02 /* Public */,
     155,    1, 3057,    2, 0x02 /* Public */,
     156,    1, 3060,    2, 0x02 /* Public */,
     157,    1, 3063,    2, 0x02 /* Public */,
     158,    0, 3066,    2, 0x02 /* Public */,
     159,    0, 3067,    2, 0x02 /* Public */,
     160,    0, 3068,    2, 0x02 /* Public */,
     161,    1, 3069,    2, 0x02 /* Public */,
     162,    3, 3072,    2, 0x02 /* Public */,
     164,    0, 3079,    2, 0x02 /* Public */,
     165,    0, 3080,    2, 0x02 /* Public */,
     166,    0, 3081,    2, 0x02 /* Public */,
     167,    0, 3082,    2, 0x02 /* Public */,
     168,    0, 3083,    2, 0x02 /* Public */,
     169,    2, 3084,    2, 0x02 /* Public */,
     170,    3, 3089,    2, 0x02 /* Public */,
     171,    2, 3096,    2, 0x02 /* Public */,
     172,    0, 3101,    2, 0x02 /* Public */,
     173,    0, 3102,    2, 0x02 /* Public */,
     174,    1, 3103,    2, 0x02 /* Public */,
     176,    0, 3106,    2, 0x02 /* Public */,
     177,    0, 3107,    2, 0x02 /* Public */,
     178,    0, 3108,    2, 0x02 /* Public */,
     179,    0, 3109,    2, 0x02 /* Public */,
     180,    0, 3110,    2, 0x02 /* Public */,
     181,    0, 3111,    2, 0x02 /* Public */,
     182,    0, 3112,    2, 0x02 /* Public */,
     183,    2, 3113,    2, 0x02 /* Public */,
     184,    2, 3118,    2, 0x02 /* Public */,
     185,    2, 3123,    2, 0x02 /* Public */,
     186,    1, 3128,    2, 0x02 /* Public */,
     187,    2, 3131,    2, 0x02 /* Public */,
     188,    2, 3136,    2, 0x02 /* Public */,
     189,    0, 3141,    2, 0x02 /* Public */,
     190,    0, 3142,    2, 0x02 /* Public */,
     191,    0, 3143,    2, 0x02 /* Public */,
     192,    0, 3144,    2, 0x02 /* Public */,
     193,    2, 3145,    2, 0x02 /* Public */,
     194,    2, 3150,    2, 0x02 /* Public */,
     195,    0, 3155,    2, 0x02 /* Public */,
     196,    1, 3156,    2, 0x02 /* Public */,
     198,    2, 3159,    2, 0x02 /* Public */,
     199,    2, 3164,    2, 0x02 /* Public */,
     200,    2, 3169,    2, 0x02 /* Public */,
     201,    1, 3174,    2, 0x02 /* Public */,
     202,    1, 3177,    2, 0x02 /* Public */,
     203,    3, 3180,    2, 0x02 /* Public */,
     205,    5, 3187,    2, 0x02 /* Public */,
     210,    3, 3198,    2, 0x02 /* Public */,
     211,    5, 3205,    2, 0x02 /* Public */,
     212,    3, 3216,    2, 0x02 /* Public */,
     213,    5, 3223,    2, 0x02 /* Public */,
     214,    2, 3234,    2, 0x02 /* Public */,
     215,    3, 3239,    2, 0x02 /* Public */,
     217,    0, 3246,    2, 0x02 /* Public */,
     218,    3, 3247,    2, 0x02 /* Public */,
     219,    3, 3254,    2, 0x02 /* Public */,
     220,    3, 3261,    2, 0x02 /* Public */,
     221,    1, 3268,    2, 0x02 /* Public */,
     214,    2, 3271,    2, 0x02 /* Public */,
     222,    1, 3276,    2, 0x02 /* Public */,
     223,    0, 3279,    2, 0x02 /* Public */,
     224,    1, 3280,    2, 0x02 /* Public */,
     225,    0, 3283,    2, 0x02 /* Public */,
     226,    0, 3284,    2, 0x02 /* Public */,
     227,    0, 3285,    2, 0x02 /* Public */,
     228,    0, 3286,    2, 0x02 /* Public */,
     229,    0, 3287,    2, 0x02 /* Public */,
     230,    2, 3288,    2, 0x02 /* Public */,
     231,    3, 3293,    2, 0x02 /* Public */,
     233,    3, 3300,    2, 0x02 /* Public */,
     234,    2, 3307,    2, 0x02 /* Public */,
     235,    0, 3312,    2, 0x02 /* Public */,
     236,    0, 3313,    2, 0x02 /* Public */,
     237,    0, 3314,    2, 0x02 /* Public */,
     238,    0, 3315,    2, 0x02 /* Public */,
     239,    1, 3316,    2, 0x02 /* Public */,
     240,    1, 3319,    2, 0x02 /* Public */,
     241,    1, 3322,    2, 0x02 /* Public */,
     242,    1, 3325,    2, 0x02 /* Public */,
     243,    1, 3328,    2, 0x02 /* Public */,
     244,    1, 3331,    2, 0x02 /* Public */,
     245,    1, 3334,    2, 0x02 /* Public */,
     246,    0, 3337,    2, 0x02 /* Public */,
     247,    3, 3338,    2, 0x02 /* Public */,
     248,    0, 3345,    2, 0x02 /* Public */,
     249,    1, 3346,    2, 0x02 /* Public */,
     250,    1, 3349,    2, 0x02 /* Public */,
     252,    0, 3352,    2, 0x02 /* Public */,
     253,    0, 3353,    2, 0x02 /* Public */,
     254,    0, 3354,    2, 0x02 /* Public */,
     255,    1, 3355,    2, 0x02 /* Public */,
     256,    1, 3358,    2, 0x02 /* Public */,
     257,    0, 3361,    2, 0x02 /* Public */,
     258,    0, 3362,    2, 0x02 /* Public */,
     259,    0, 3363,    2, 0x02 /* Public */,
     260,    0, 3364,    2, 0x02 /* Public */,
     261,    0, 3365,    2, 0x02 /* Public */,
     262,    0, 3366,    2, 0x02 /* Public */,
     263,    0, 3367,    2, 0x02 /* Public */,
     264,    0, 3368,    2, 0x02 /* Public */,
     265,    0, 3369,    2, 0x02 /* Public */,
     266,    0, 3370,    2, 0x02 /* Public */,
     267,    0, 3371,    2, 0x02 /* Public */,
     268,    1, 3372,    2, 0x02 /* Public */,
     269,    1, 3375,    2, 0x02 /* Public */,
     270,    1, 3378,    2, 0x02 /* Public */,
     271,    1, 3381,    2, 0x02 /* Public */,
     272,    1, 3384,    2, 0x02 /* Public */,
     273,    1, 3387,    2, 0x02 /* Public */,
     274,    1, 3390,    2, 0x02 /* Public */,
     275,    3, 3393,    2, 0x02 /* Public */,
     277,    1, 3400,    2, 0x02 /* Public */,
     277,    0, 3403,    2, 0x22 /* Public | MethodCloned */,
     279,    3, 3404,    2, 0x02 /* Public */,
     280,    0, 3411,    2, 0x02 /* Public */,
     281,    1, 3412,    2, 0x02 /* Public */,
     283,    0, 3415,    2, 0x02 /* Public */,
     284,    0, 3416,    2, 0x02 /* Public */,
     285,    0, 3417,    2, 0x02 /* Public */,
     286,    0, 3418,    2, 0x02 /* Public */,
     287,    2, 3419,    2, 0x02 /* Public */,
     290,    0, 3424,    2, 0x02 /* Public */,
     291,    1, 3425,    2, 0x02 /* Public */,
     292,    1, 3428,    2, 0x02 /* Public */,
     294,    2, 3431,    2, 0x02 /* Public */,
     294,    1, 3436,    2, 0x22 /* Public | MethodCloned */,
     295,    0, 3439,    2, 0x02 /* Public */,
     296,    0, 3440,    2, 0x02 /* Public */,
     297,    0, 3441,    2, 0x02 /* Public */,
     298,    0, 3442,    2, 0x02 /* Public */,
     299,    0, 3443,    2, 0x02 /* Public */,
     300,    0, 3444,    2, 0x02 /* Public */,
     301,    0, 3445,    2, 0x02 /* Public */,
     302,    0, 3446,    2, 0x02 /* Public */,
     303,    0, 3447,    2, 0x02 /* Public */,
     304,    0, 3448,    2, 0x02 /* Public */,
     305,    0, 3449,    2, 0x02 /* Public */,
     306,    0, 3450,    2, 0x02 /* Public */,
     307,    0, 3451,    2, 0x02 /* Public */,
     308,    1, 3452,    2, 0x02 /* Public */,
     309,    1, 3455,    2, 0x02 /* Public */,
     310,    1, 3458,    2, 0x02 /* Public */,
     311,    1, 3461,    2, 0x02 /* Public */,
     312,    1, 3464,    2, 0x02 /* Public */,
     313,    0, 3467,    2, 0x02 /* Public */,
     314,    0, 3468,    2, 0x02 /* Public */,
     315,    0, 3469,    2, 0x02 /* Public */,
     316,    1, 3470,    2, 0x02 /* Public */,
     317,    0, 3473,    2, 0x02 /* Public */,
     318,    2, 3474,    2, 0x02 /* Public */,
     320,    1, 3479,    2, 0x02 /* Public */,
     323,    2, 3482,    2, 0x02 /* Public */,
     324,    1, 3487,    2, 0x02 /* Public */,
     323,    1, 3490,    2, 0x02 /* Public */,
     326,    1, 3493,    2, 0x02 /* Public */,
     328,    0, 3496,    2, 0x02 /* Public */,
     329,    1, 3497,    2, 0x02 /* Public */,
     330,    0, 3500,    2, 0x02 /* Public */,
     331,    1, 3501,    2, 0x02 /* Public */,
     332,    1, 3504,    2, 0x02 /* Public */,
     333,    1, 3507,    2, 0x02 /* Public */,
     334,    1, 3510,    2, 0x02 /* Public */,
     335,    1, 3513,    2, 0x02 /* Public */,
     337,    3, 3516,    2, 0x02 /* Public */,
     340,    0, 3523,    2, 0x02 /* Public */,
     341,    0, 3524,    2, 0x02 /* Public */,
     342,    0, 3525,    2, 0x02 /* Public */,
     343,    0, 3526,    2, 0x02 /* Public */,
     344,    1, 3527,    2, 0x02 /* Public */,
     345,    0, 3530,    2, 0x02 /* Public */,
     346,    1, 3531,    2, 0x02 /* Public */,
     347,    0, 3534,    2, 0x02 /* Public */,
     348,    1, 3535,    2, 0x02 /* Public */,
     350,    0, 3538,    2, 0x02 /* Public */,
     351,    0, 3539,    2, 0x02 /* Public */,
     352,    1, 3540,    2, 0x02 /* Public */,
     352,    0, 3543,    2, 0x22 /* Public | MethodCloned */,
     353,    1, 3544,    2, 0x02 /* Public */,
     354,    1, 3547,    2, 0x02 /* Public */,
     354,    0, 3550,    2, 0x22 /* Public | MethodCloned */,
     355,    1, 3551,    2, 0x02 /* Public */,
     355,    0, 3554,    2, 0x22 /* Public | MethodCloned */,
     356,    1, 3555,    2, 0x02 /* Public */,
     356,    0, 3558,    2, 0x22 /* Public | MethodCloned */,
     357,    1, 3559,    2, 0x02 /* Public */,
     357,    0, 3562,    2, 0x22 /* Public | MethodCloned */,
     358,    1, 3563,    2, 0x02 /* Public */,
     359,    1, 3566,    2, 0x02 /* Public */,
     360,    0, 3569,    2, 0x02 /* Public */,
     361,    0, 3570,    2, 0x02 /* Public */,
     362,    1, 3571,    2, 0x02 /* Public */,
     363,    1, 3574,    2, 0x02 /* Public */,
     364,    1, 3577,    2, 0x02 /* Public */,
     365,    0, 3580,    2, 0x02 /* Public */,
     366,    0, 3581,    2, 0x02 /* Public */,
     367,    1, 3582,    2, 0x02 /* Public */,
     369,    1, 3585,    2, 0x02 /* Public */,
     370,    2, 3588,    2, 0x02 /* Public */,
      88,    1, 3593,    2, 0x02 /* Public */,
     373,    3, 3596,    2, 0x02 /* Public */,
     376,    2, 3603,    2, 0x02 /* Public */,
     379,    0, 3608,    2, 0x02 /* Public */,
     380,    1, 3609,    2, 0x02 /* Public */,
     381,    1, 3612,    2, 0x02 /* Public */,
     382,    0, 3615,    2, 0x02 /* Public */,
     383,    3, 3616,    2, 0x02 /* Public */,
     384,    0, 3623,    2, 0x02 /* Public */,
     385,    0, 3624,    2, 0x02 /* Public */,
     386,    0, 3625,    2, 0x02 /* Public */,
     387,    0, 3626,    2, 0x02 /* Public */,
     388,    0, 3627,    2, 0x02 /* Public */,
     389,    0, 3628,    2, 0x02 /* Public */,
     390,    0, 3629,    2, 0x02 /* Public */,
     391,    0, 3630,    2, 0x02 /* Public */,
     392,    0, 3631,    2, 0x02 /* Public */,
     393,    0, 3632,    2, 0x02 /* Public */,
     394,    1, 3633,    2, 0x02 /* Public */,
     396,    0, 3636,    2, 0x02 /* Public */,
     397,    0, 3637,    2, 0x02 /* Public */,
     398,    0, 3638,    2, 0x02 /* Public */,
     399,    0, 3639,    2, 0x02 /* Public */,
     400,    0, 3640,    2, 0x02 /* Public */,
     401,    1, 3641,    2, 0x02 /* Public */,
     402,    0, 3644,    2, 0x02 /* Public */,
     403,    1, 3645,    2, 0x02 /* Public */,
     404,    1, 3648,    2, 0x02 /* Public */,
     405,    2, 3651,    2, 0x02 /* Public */,
     406,    2, 3656,    2, 0x02 /* Public */,
     407,    1, 3661,    2, 0x02 /* Public */,
     409,    0, 3664,    2, 0x02 /* Public */,
     410,    2, 3665,    2, 0x02 /* Public */,
     214,    1, 3670,    2, 0x02 /* Public */,
     214,    0, 3673,    2, 0x22 /* Public | MethodCloned */,
     411,    2, 3674,    2, 0x02 /* Public */,
     411,    1, 3679,    2, 0x22 /* Public | MethodCloned */,
     412,    1, 3682,    2, 0x02 /* Public */,
     413,    2, 3685,    2, 0x02 /* Public */,
     414,    2, 3690,    2, 0x02 /* Public */,
     415,    1, 3695,    2, 0x02 /* Public */,
     416,    1, 3698,    2, 0x02 /* Public */,
     417,    2, 3701,    2, 0x02 /* Public */,
     418,    0, 3706,    2, 0x02 /* Public */,
     419,    1, 3707,    2, 0x02 /* Public */,
     418,    1, 3710,    2, 0x02 /* Public */,
     420,    1, 3713,    2, 0x02 /* Public */,
     421,    2, 3716,    2, 0x02 /* Public */,
     422,    1, 3721,    2, 0x02 /* Public */,
     423,    1, 3724,    2, 0x02 /* Public */,
     424,    1, 3727,    2, 0x02 /* Public */,
     220,    4, 3730,    2, 0x02 /* Public */,
     426,    2, 3739,    2, 0x02 /* Public */,
     426,    1, 3744,    2, 0x22 /* Public | MethodCloned */,
     427,    2, 3747,    2, 0x02 /* Public */,
     427,    1, 3752,    2, 0x22 /* Public | MethodCloned */,
     428,    2, 3755,    2, 0x02 /* Public */,
     428,    1, 3760,    2, 0x22 /* Public | MethodCloned */,
     429,    2, 3763,    2, 0x02 /* Public */,
     430,    1, 3768,    2, 0x02 /* Public */,
     431,    0, 3771,    2, 0x02 /* Public */,
     432,    1, 3772,    2, 0x02 /* Public */,
     433,    0, 3775,    2, 0x02 /* Public */,
     434,    0, 3776,    2, 0x02 /* Public */,
     435,    1, 3777,    2, 0x02 /* Public */,
     436,    1, 3780,    2, 0x02 /* Public */,
     437,    2, 3783,    2, 0x02 /* Public */,
     438,    2, 3788,    2, 0x02 /* Public */,
     439,    3, 3793,    2, 0x02 /* Public */,
     441,    1, 3800,    2, 0x02 /* Public */,
     441,    2, 3803,    2, 0x02 /* Public */,
     442,    0, 3808,    2, 0x02 /* Public */,
     443,    1, 3809,    2, 0x02 /* Public */,
     444,    1, 3812,    2, 0x02 /* Public */,
     445,    1, 3815,    2, 0x02 /* Public */,
     446,    0, 3818,    2, 0x02 /* Public */,
     447,    0, 3819,    2, 0x02 /* Public */,
     448,    0, 3820,    2, 0x02 /* Public */,
     449,    0, 3821,    2, 0x02 /* Public */,
     450,    0, 3822,    2, 0x02 /* Public */,
     451,    2, 3823,    2, 0x02 /* Public */,
     451,    1, 3828,    2, 0x22 /* Public | MethodCloned */,
     452,    0, 3831,    2, 0x02 /* Public */,
     453,    3, 3832,    2, 0x02 /* Public */,
     455,    0, 3839,    2, 0x02 /* Public */,
     456,    1, 3840,    2, 0x02 /* Public */,
     458,    0, 3843,    2, 0x02 /* Public */,
     459,    0, 3844,    2, 0x02 /* Public */,
     461,    0, 3845,    2, 0x02 /* Public */,
     462,    0, 3846,    2, 0x02 /* Public */,
     463,    0, 3847,    2, 0x02 /* Public */,
     464,    0, 3848,    2, 0x02 /* Public */,
     465,    0, 3849,    2, 0x02 /* Public */,
     466,    0, 3850,    2, 0x02 /* Public */,
     467,    0, 3851,    2, 0x02 /* Public */,
     468,    0, 3852,    2, 0x02 /* Public */,
     469,    0, 3853,    2, 0x02 /* Public */,
     470,    0, 3854,    2, 0x02 /* Public */,
     471,    1, 3855,    2, 0x02 /* Public */,
     473,    0, 3858,    2, 0x02 /* Public */,
     474,    0, 3859,    2, 0x02 /* Public */,
     475,    0, 3860,    2, 0x02 /* Public */,
     476,    0, 3861,    2, 0x02 /* Public */,
     477,    0, 3862,    2, 0x02 /* Public */,
     478,    0, 3863,    2, 0x02 /* Public */,
     479,    0, 3864,    2, 0x02 /* Public */,
     480,    1, 3865,    2, 0x02 /* Public */,
     481,    1, 3868,    2, 0x02 /* Public */,
     482,    1, 3871,    2, 0x02 /* Public */,
     483,    1, 3874,    2, 0x02 /* Public */,
     484,    1, 3877,    2, 0x02 /* Public */,
     485,    0, 3880,    2, 0x02 /* Public */,
     486,    1, 3881,    2, 0x02 /* Public */,
     487,    0, 3884,    2, 0x02 /* Public */,
     488,    0, 3885,    2, 0x02 /* Public */,
     489,    0, 3886,    2, 0x02 /* Public */,
     490,    0, 3887,    2, 0x02 /* Public */,
     491,    0, 3888,    2, 0x02 /* Public */,
     492,    0, 3889,    2, 0x02 /* Public */,
     493,    0, 3890,    2, 0x02 /* Public */,
     494,    0, 3891,    2, 0x02 /* Public */,
     495,    0, 3892,    2, 0x02 /* Public */,
     496,    0, 3893,    2, 0x02 /* Public */,
     497,    0, 3894,    2, 0x02 /* Public */,
     498,    0, 3895,    2, 0x02 /* Public */,
     499,    0, 3896,    2, 0x02 /* Public */,
     500,    1, 3897,    2, 0x02 /* Public */,
     501,    0, 3900,    2, 0x02 /* Public */,
     502,    0, 3901,    2, 0x02 /* Public */,
     503,    0, 3902,    2, 0x02 /* Public */,
     504,    0, 3903,    2, 0x02 /* Public */,
     505,    0, 3904,    2, 0x02 /* Public */,
     506,    0, 3905,    2, 0x02 /* Public */,
     507,    0, 3906,    2, 0x02 /* Public */,
     508,    0, 3907,    2, 0x02 /* Public */,
     509,    1, 3908,    2, 0x02 /* Public */,
     510,    1, 3911,    2, 0x02 /* Public */,
     511,    1, 3914,    2, 0x02 /* Public */,
     512,    0, 3917,    2, 0x02 /* Public */,
     513,    1, 3918,    2, 0x02 /* Public */,
     514,    1, 3921,    2, 0x02 /* Public */,
     515,    0, 3924,    2, 0x02 /* Public */,
     516,    0, 3925,    2, 0x02 /* Public */,
     517,    0, 3926,    2, 0x02 /* Public */,
     518,    0, 3927,    2, 0x02 /* Public */,
     519,    0, 3928,    2, 0x02 /* Public */,
     520,    0, 3929,    2, 0x02 /* Public */,
     521,    0, 3930,    2, 0x02 /* Public */,
     522,    0, 3931,    2, 0x02 /* Public */,
     523,    0, 3932,    2, 0x02 /* Public */,
     434,    2, 3933,    2, 0x02 /* Public */,
     524,    2, 3938,    2, 0x02 /* Public */,
     525,    2, 3943,    2, 0x02 /* Public */,
     526,    2, 3948,    2, 0x02 /* Public */,
     527,    2, 3953,    2, 0x02 /* Public */,
     528,    2, 3958,    2, 0x02 /* Public */,
     529,    2, 3963,    2, 0x02 /* Public */,
     530,    0, 3968,    2, 0x02 /* Public */,
     531,    0, 3969,    2, 0x02 /* Public */,
     532,    0, 3970,    2, 0x02 /* Public */,
     533,    1, 3971,    2, 0x02 /* Public */,
     534,    0, 3974,    2, 0x02 /* Public */,
     535,    0, 3975,    2, 0x02 /* Public */,
     536,    0, 3976,    2, 0x02 /* Public */,
     537,    1, 3977,    2, 0x02 /* Public */,
      86,    2, 3980,    2, 0x02 /* Public */,
     539,    0, 3985,    2, 0x02 /* Public */,
     540,    0, 3986,    2, 0x02 /* Public */,
     541,    0, 3987,    2, 0x02 /* Public */,
     542,    0, 3988,    2, 0x02 /* Public */,
     543,    2, 3989,    2, 0x02 /* Public */,
     544,    0, 3994,    2, 0x02 /* Public */,
     545,    1, 3995,    2, 0x02 /* Public */,
     546,    0, 3998,    2, 0x02 /* Public */,
     547,    0, 3999,    2, 0x02 /* Public */,
     548,    6, 4000,    2, 0x02 /* Public */,
     548,    5, 4013,    2, 0x22 /* Public | MethodCloned */,
     548,    4, 4024,    2, 0x22 /* Public | MethodCloned */,
     548,    3, 4033,    2, 0x22 /* Public | MethodCloned */,
     548,    2, 4040,    2, 0x22 /* Public | MethodCloned */,
     548,    1, 4045,    2, 0x22 /* Public | MethodCloned */,
     548,    0, 4048,    2, 0x22 /* Public | MethodCloned */,
     555,    0, 4049,    2, 0x02 /* Public */,
     556,    0, 4050,    2, 0x02 /* Public */,
     557,    0, 4051,    2, 0x02 /* Public */,
     558,    1, 4052,    2, 0x02 /* Public */,
     559,    1, 4055,    2, 0x02 /* Public */,
     560,    1, 4058,    2, 0x02 /* Public */,
     561,    1, 4061,    2, 0x02 /* Public */,

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
    QMetaType::Void, QMetaType::QString,   71,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   71,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   99,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   99,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   99,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Float,   92,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  126,  127,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   32,  129,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   32,  131,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,  137,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,  134,  135,  138,  139,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Bool,  147,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  163,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   32,  134,  135,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  175,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::QString,   81,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  197,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int,  131,
    QMetaType::Void, QMetaType::Int,  138,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  204,  134,  135,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  204,  206,  207,  208,  209,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  204,  134,  135,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  204,  206,  207,  208,  209,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  204,  134,  135,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  204,  206,  207,  208,  209,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   25,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   81,  216,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  163,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  163,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  163,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  138,  139,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  232,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  232,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Bool,  150,
    QMetaType::Void, QMetaType::Int,   92,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  138,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QString,  251,
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
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   99,   21,  276,
    QMetaType::Void, QMetaType::QString,  278,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   99,   25,   21,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  282,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  288,  289,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::Bool,  293,
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
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   25,  319,
    0x80000000 | 321, QMetaType::QString,  322,
    0x80000000 | 321, QMetaType::Int, QMetaType::QString,   25,   21,
    0x80000000 | 321, QMetaType::Int,  325,
    0x80000000 | 321, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Int,  327,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void, QMetaType::QDateTime,  336,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  338,  339,  336,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  349,
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
    QMetaType::Void, QMetaType::QString,  368,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  371,  372,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  374,  375,   71,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  377,  378,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   71,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  134,  135,  163,
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
    QMetaType::Void, QMetaType::Bool,  395,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  325,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  325,
    0x80000000 | 321, QMetaType::QString,  325,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   81,  325,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   81,  150,
    QMetaType::Void, QMetaType::Bool,  408,
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
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   32,   21,   25,  425,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   81,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   81,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   32,   81,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   25,   32,
    QMetaType::Float, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  395,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int, QMetaType::Int,   32,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  137,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   32,  137,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  440,  134,  135,
    QMetaType::Int, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   81,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool, QMetaType::QString,  368,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  368,   71,
    QMetaType::Void, QMetaType::QString,  368,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  454,   25,  319,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  457,
    QMetaType::Void,
    0x80000000 | 460,
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
    QMetaType::Bool, QMetaType::Int,  472,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  325,
    QMetaType::Int, QMetaType::Int,  325,
    QMetaType::QString, QMetaType::Int,  325,
    QMetaType::Int, QMetaType::Int,  325,
    QMetaType::Int, QMetaType::Int,  325,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  325,
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
    QMetaType::Void, QMetaType::Bool,  150,
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
    0x80000000 | 460,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  134,  135,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   71,  538,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   25,   21,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   32,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  549,  550,  551,  552,  553,  554,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  549,  550,  551,  552,  553,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  549,  550,  551,  552,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  549,  550,  551,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  549,  550,
    QMetaType::Void, QMetaType::QString,  549,
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
        case 95: _t->setMovingPageBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 96: { QString _r = _t->getMovingPageBackground();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 97: _t->setMovingPageMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 98: { QString _r = _t->getMovingPageMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 99: _t->setMovingPageColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 100: { QString _r = _t->getMovingPageColor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 101: _t->setMovingPageImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 102: { QString _r = _t->getMovingPageImage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 103: _t->setMovingPageVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 104: { QString _r = _t->getMovingPageVideo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 105: _t->setMovingPageAudio((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 106: { float _r = _t->getMovingPageAudio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 107: _t->clearPatrolPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 108: { int _r = _t->getPatrolObjectSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 109: { QString _r = _t->getPageObjectType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 110: { QString _r = _t->getPageObjectSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 111: { QString _r = _t->getPageObjectColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 112: { int _r = _t->getPageObjectX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 113: { int _r = _t->getPageObjectY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 114: { int _r = _t->getPageObjectWidth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 115: { int _r = _t->getPageObjectHeight((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 116: { int _r = _t->getPageObjectFontsize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 117: _t->addPatrolObject((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 118: _t->setPageObjectSource((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 119: _t->setPageObjectColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 120: _t->deletePatrolObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 121: _t->movePatrolObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 122: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 123: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 124: { int _r = _t->getPageObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 125: _t->confirmLocalization(); break;
        case 126: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 127: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 128: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 129: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 130: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 131: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 132: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 133: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 134: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 135: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 136: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 137: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 138: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 139: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 140: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 141: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 142: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 143: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 144: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 145: _t->clearInitPose(); break;
        case 146: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 147: _t->startDrawingTline(); break;
        case 148: _t->stopDrawingTline(); break;
        case 149: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 150: _t->setRulerPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 151: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 152: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 153: _t->saveRotateMap(); break;
        case 154: _t->initRotate(); break;
        case 155: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 156: _t->rotateMapCW(); break;
        case 157: _t->rotateMapCCW(); break;
        case 158: _t->saveObjectPNG(); break;
        case 159: _t->saveObsAreaPNG(); break;
        case 160: { int _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 161: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 162: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 163: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 164: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 165: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 166: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 167: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 168: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 169: _t->endDrawingRect(); break;
        case 170: _t->clearDrawing(); break;
        case 171: _t->undoLine(); break;
        case 172: _t->redoLine(); break;
        case 173: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 174: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 175: _t->drawSpline(); break;
        case 176: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 177: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 178: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 179: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 180: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 181: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 182: _t->pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 183: _t->double_pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 184: _t->moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 185: _t->double_moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 186: _t->released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 187: _t->double_released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 188: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 189: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 190: _t->clearLocation(); break;
        case 191: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 192: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 193: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 194: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 195: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 196: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 197: _t->setTableNumberAuto(); break;
        case 198: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 199: _t->saveMap(); break;
        case 200: _t->saveEditedMap(); break;
        case 201: _t->saveTline(); break;
        case 202: _t->saveTlineTemp(); break;
        case 203: _t->saveVelmap(); break;
        case 204: _t->setMapSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 205: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 206: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 207: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 208: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 209: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 210: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 211: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 212: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 213: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 214: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 215: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 216: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 217: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 218: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 219: _t->requestSystemVolume(); break;
        case 220: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 221: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 222: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 223: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 224: _t->startDrawingObject(); break;
        case 225: _t->stopDrawingObject(); break;
        case 226: _t->saveDrawingObject(); break;
        case 227: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 228: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 229: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 230: _t->killSLAM(); break;
        case 231: _t->makeRobotINI(); break;
        case 232: _t->checkRobotINI(); break;
        case 233: _t->restartSLAM(); break;
        case 234: _t->startSLAM(); break;
        case 235: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 236: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 237: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 238: _t->programRestart(); break;
        case 239: _t->programExit(); break;
        case 240: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 241: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 242: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 243: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 244: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 245: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 246: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 247: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 248: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 249: _t->readSetting(); break;
        case 250: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 251: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 252: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 253: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 254: _t->requestCamera(); break;
        case 255: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 256: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 257: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 258: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 259: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 260: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 261: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 262: { QString _r = _t->getVoice((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 263: _t->checkTravelline(); break;
        case 264: _t->updateProgram(); break;
        case 265: _t->updateProgramGitPull(); break;
        case 266: _t->checkVersionAgain(); break;
        case 267: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 268: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 269: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 270: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 271: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 272: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 273: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 274: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 275: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 276: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 277: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 278: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 279: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 280: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 281: _t->checkCleaningLocation(); break;
        case 282: _t->checkUpdate(); break;
        case 283: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 284: _t->setlanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 285: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 286: _t->goServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 287: { LOCATION _r = _t->getLocationbyCall((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 288: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 289: { LOCATION _r = _t->getLocationbyID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 290: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 291: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 292: _t->resetLocalization(); break;
        case 293: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 294: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 295: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 296: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 297: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 298: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 299: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 300: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 301: _t->updateUSB(); break;
        case 302: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 303: _t->readusbrecentfile(); break;
        case 304: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 305: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 306: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 307: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 308: _t->readusb(); break;
        case 309: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 310: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 311: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 312: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 313: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 314: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 315: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 316: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 317: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 318: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 319: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 320: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 321: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 322: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 323: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 324: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 325: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 326: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 327: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 328: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 329: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 330: _t->deleteEditedMap(); break;
        case 331: _t->deleteAnnotation(); break;
        case 332: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 333: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 334: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 335: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 336: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 337: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 338: _t->stopMapping(); break;
        case 339: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 340: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 341: _t->setInitCurPos(); break;
        case 342: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 343: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 344: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 345: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 346: _t->slam_setInit(); break;
        case 347: _t->slam_run(); break;
        case 348: _t->slam_stop(); break;
        case 349: _t->slam_autoInit(); break;
        case 350: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 351: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 352: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 353: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 354: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 355: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 356: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 357: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 358: _t->cleanTray(); break;
        case 359: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 360: _t->clearCallQueue(); break;
        case 361: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 362: { LOCATION _r = _t->getCallLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 363: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 364: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 365: _t->acceptCall((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 366: _t->setObjPose(); break;
        case 367: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 368: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 369: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 370: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 371: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 372: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 373: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 374: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 375: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 376: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 377: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 378: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 379: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 380: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 381: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 382: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 383: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 384: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 385: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 386: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 387: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 388: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 389: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 390: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 391: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 392: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 393: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 394: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 395: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 396: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 397: _t->clearSharedMemory(); break;
        case 398: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 399: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 400: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 401: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 402: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 403: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 404: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 405: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 406: _t->saveLocations(); break;
        case 407: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 408: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 409: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 410: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 411: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 412: _t->drawingRunawayStart(); break;
        case 413: _t->drawingRunawayStop(); break;
        case 414: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 415: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 416: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 417: _t->slam_ini_reload(); break;
        case 418: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 419: _t->startServing(); break;
        case 420: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 421: _t->confirmPickup(); break;
        case 422: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 423: _t->movePause(); break;
        case 424: _t->moveResume(); break;
        case 425: _t->moveStopFlag(); break;
        case 426: _t->moveStop(); break;
        case 427: _t->moveToCharge(); break;
        case 428: _t->moveToWait(); break;
        case 429: _t->moveToCleaning(); break;
        case 430: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 431: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 432: _t->resetHomeFolders(); break;
        case 433: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 434: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 435: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 436: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 437: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 438: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 439: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 440: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 441: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 442: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 443: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 444: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 445: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 446: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 447: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 448: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 449: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 450: { int _r = _t->getChargeConnectStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 451: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 452: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 453: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 454: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 455: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 456: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 457: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 458: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 459: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 460: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 461: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 462: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 463: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 464: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 465: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 466: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 467: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 468: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 469: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 470: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 471: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 472: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 473: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 474: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 475: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 476: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 477: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 478: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 479: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 480: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 481: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 482: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 483: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 484: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 485: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 486: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 487: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 488: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 489: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 490: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 491: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 492: _t->saveObject(); break;
        case 493: _t->clearObject(); break;
        case 494: _t->clearObjectAll(); break;
        case 495: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 496: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 497: _t->undoObject(); break;
        case 498: _t->clearRotateList(); break;
        case 499: _t->setRotateList((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 500: _t->startPatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 501: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 502: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 503: _t->clearFlagStop(); break;
        case 504: _t->slam_fullautoInit(); break;
        case 505: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 506: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 507: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 508: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 509: _t->clear_call(); break;
        case 510: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 511: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 512: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 513: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 514: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 515: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 516: _t->usbsave(); break;
        case 517: _t->restartUpdate(); break;
        case 518: _t->startUpdate(); break;
        case 519: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 520: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 521: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 522: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 523: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
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
        if (_id < 524)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 524;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 524)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 524;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
