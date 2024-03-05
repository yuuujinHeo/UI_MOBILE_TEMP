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
    QByteArrayData data[613];
    char stringdata0[7855];
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
QT_MOC_LITERAL(22, 250, 10), // "play_voice"
QT_MOC_LITERAL(23, 261, 8), // "ST_VOICE"
QT_MOC_LITERAL(24, 270, 5), // "voice"
QT_MOC_LITERAL(25, 276, 17), // "emo_state_changed"
QT_MOC_LITERAL(26, 294, 14), // "setCurrentPage"
QT_MOC_LITERAL(27, 309, 4), // "page"
QT_MOC_LITERAL(28, 314, 13), // "loadMapServer"
QT_MOC_LITERAL(29, 328, 13), // "sendMapServer"
QT_MOC_LITERAL(30, 342, 17), // "checkLocationName"
QT_MOC_LITERAL(31, 360, 5), // "group"
QT_MOC_LITERAL(32, 366, 10), // "resetClear"
QT_MOC_LITERAL(33, 377, 10), // "getWifiNum"
QT_MOC_LITERAL(34, 388, 17), // "getWifiConnection"
QT_MOC_LITERAL(35, 406, 4), // "ssid"
QT_MOC_LITERAL(36, 411, 14), // "getCurWifiSSID"
QT_MOC_LITERAL(37, 426, 11), // "getWifiSSID"
QT_MOC_LITERAL(38, 438, 3), // "num"
QT_MOC_LITERAL(39, 442, 11), // "connectWifi"
QT_MOC_LITERAL(40, 454, 6), // "passwd"
QT_MOC_LITERAL(41, 461, 15), // "getWifiSecurity"
QT_MOC_LITERAL(42, 477, 12), // "getWifiLevel"
QT_MOC_LITERAL(43, 490, 11), // "getWifiRate"
QT_MOC_LITERAL(44, 502, 12), // "getWifiInuse"
QT_MOC_LITERAL(45, 515, 14), // "getAllWifiList"
QT_MOC_LITERAL(46, 530, 9), // "getWifiIP"
QT_MOC_LITERAL(47, 540, 7), // "setWifi"
QT_MOC_LITERAL(48, 548, 2), // "ip"
QT_MOC_LITERAL(49, 551, 7), // "gateway"
QT_MOC_LITERAL(50, 559, 3), // "dns"
QT_MOC_LITERAL(51, 563, 8), // "getcurIP"
QT_MOC_LITERAL(52, 572, 13), // "getcurGateway"
QT_MOC_LITERAL(53, 586, 9), // "getcurDNS"
QT_MOC_LITERAL(54, 596, 13), // "readWifiState"
QT_MOC_LITERAL(55, 610, 10), // "setWifiSSD"
QT_MOC_LITERAL(56, 621, 15), // "getSystemVolume"
QT_MOC_LITERAL(57, 637, 8), // "passInit"
QT_MOC_LITERAL(58, 646, 11), // "isDebugMode"
QT_MOC_LITERAL(59, 658, 10), // "readPatrol"
QT_MOC_LITERAL(60, 669, 13), // "getPatrolSize"
QT_MOC_LITERAL(61, 683, 13), // "getPatrolName"
QT_MOC_LITERAL(62, 697, 13), // "getPatrolType"
QT_MOC_LITERAL(63, 711, 17), // "getPatrolLocation"
QT_MOC_LITERAL(64, 729, 19), // "getPatrolMovingPage"
QT_MOC_LITERAL(65, 749, 19), // "getPatrolArrivePage"
QT_MOC_LITERAL(66, 769, 17), // "getPatrolWaitTime"
QT_MOC_LITERAL(67, 787, 17), // "getPatrolPassTime"
QT_MOC_LITERAL(68, 805, 14), // "getPatrolVoice"
QT_MOC_LITERAL(69, 820, 18), // "getPatrolVoiceMode"
QT_MOC_LITERAL(70, 839, 22), // "getPatrolVoiceLanguage"
QT_MOC_LITERAL(71, 862, 12), // "isPatrolPage"
QT_MOC_LITERAL(72, 875, 19), // "getPatrolMovingMode"
QT_MOC_LITERAL(73, 895, 19), // "getPatrolArriveMode"
QT_MOC_LITERAL(74, 915, 16), // "setCurrentPatrol"
QT_MOC_LITERAL(75, 932, 21), // "getPatrolLocationSize"
QT_MOC_LITERAL(76, 954, 3), // "loc"
QT_MOC_LITERAL(77, 958, 19), // "clearPatrolLocation"
QT_MOC_LITERAL(78, 978, 4), // "mode"
QT_MOC_LITERAL(79, 983, 17), // "addPatrolLocation"
QT_MOC_LITERAL(80, 1001, 19), // "setPatrolMovingPage"
QT_MOC_LITERAL(81, 1021, 6), // "param1"
QT_MOC_LITERAL(82, 1028, 6), // "param2"
QT_MOC_LITERAL(83, 1035, 6), // "param3"
QT_MOC_LITERAL(84, 1042, 19), // "setPatrolArrivePage"
QT_MOC_LITERAL(85, 1062, 14), // "setPatrolVoice"
QT_MOC_LITERAL(86, 1077, 8), // "language"
QT_MOC_LITERAL(87, 1086, 6), // "volume"
QT_MOC_LITERAL(88, 1093, 9), // "setPatrol"
QT_MOC_LITERAL(89, 1103, 4), // "type"
QT_MOC_LITERAL(90, 1108, 9), // "wait_time"
QT_MOC_LITERAL(91, 1118, 9), // "pass_time"
QT_MOC_LITERAL(92, 1128, 10), // "savePatrol"
QT_MOC_LITERAL(93, 1139, 12), // "deletePatrol"
QT_MOC_LITERAL(94, 1152, 11), // "startPatrol"
QT_MOC_LITERAL(95, 1164, 14), // "setTTSLanguage"
QT_MOC_LITERAL(96, 1179, 3), // "lan"
QT_MOC_LITERAL(97, 1183, 10), // "makeTTSAll"
QT_MOC_LITERAL(98, 1194, 10), // "setTTSMode"
QT_MOC_LITERAL(99, 1205, 10), // "setTTSName"
QT_MOC_LITERAL(100, 1216, 11), // "setTTSVoice"
QT_MOC_LITERAL(101, 1228, 5), // "speed"
QT_MOC_LITERAL(102, 1234, 5), // "pitch"
QT_MOC_LITERAL(103, 1240, 5), // "alpha"
QT_MOC_LITERAL(104, 1246, 7), // "emotion"
QT_MOC_LITERAL(105, 1254, 8), // "emostren"
QT_MOC_LITERAL(106, 1263, 13), // "clearTTSVoice"
QT_MOC_LITERAL(107, 1277, 12), // "saveTTSVoice"
QT_MOC_LITERAL(108, 1290, 13), // "makePatrolTTS"
QT_MOC_LITERAL(109, 1304, 4), // "text"
QT_MOC_LITERAL(110, 1309, 13), // "getTTSNameNum"
QT_MOC_LITERAL(111, 1323, 17), // "getTTSLanguageNum"
QT_MOC_LITERAL(112, 1341, 8), // "loadFile"
QT_MOC_LITERAL(113, 1350, 6), // "setMap"
QT_MOC_LITERAL(114, 1357, 13), // "setFullScreen"
QT_MOC_LITERAL(115, 1371, 13), // "setMapDrawing"
QT_MOC_LITERAL(116, 1385, 7), // "playBGM"
QT_MOC_LITERAL(117, 1393, 7), // "stopBGM"
QT_MOC_LITERAL(118, 1401, 9), // "isplayBGM"
QT_MOC_LITERAL(119, 1411, 11), // "getTTSSpeed"
QT_MOC_LITERAL(120, 1423, 11), // "getTTSPitch"
QT_MOC_LITERAL(121, 1435, 13), // "getTTSEmotion"
QT_MOC_LITERAL(122, 1449, 21), // "getTTSEmotionStrength"
QT_MOC_LITERAL(123, 1471, 11), // "getTTSAlpha"
QT_MOC_LITERAL(124, 1483, 12), // "getTTSVolume"
QT_MOC_LITERAL(125, 1496, 13), // "getTTSMention"
QT_MOC_LITERAL(126, 1510, 13), // "setTTSMention"
QT_MOC_LITERAL(127, 1524, 7), // "mention"
QT_MOC_LITERAL(128, 1532, 9), // "playVoice"
QT_MOC_LITERAL(129, 1542, 4), // "file"
QT_MOC_LITERAL(130, 1547, 7), // "playTTS"
QT_MOC_LITERAL(131, 1555, 23), // "setMovingPageBackground"
QT_MOC_LITERAL(132, 1579, 23), // "getMovingPageBackground"
QT_MOC_LITERAL(133, 1603, 17), // "setMovingPageMode"
QT_MOC_LITERAL(134, 1621, 17), // "getMovingPageMode"
QT_MOC_LITERAL(135, 1639, 18), // "setMovingPageColor"
QT_MOC_LITERAL(136, 1658, 18), // "getMovingPageColor"
QT_MOC_LITERAL(137, 1677, 18), // "setMovingPageImage"
QT_MOC_LITERAL(138, 1696, 18), // "getMovingPageImage"
QT_MOC_LITERAL(139, 1715, 18), // "setMovingPageVideo"
QT_MOC_LITERAL(140, 1734, 18), // "getMovingPageVideo"
QT_MOC_LITERAL(141, 1753, 18), // "setMovingPageAudio"
QT_MOC_LITERAL(142, 1772, 18), // "getMovingPageAudio"
QT_MOC_LITERAL(143, 1791, 15), // "clearPatrolPage"
QT_MOC_LITERAL(144, 1807, 19), // "getPatrolObjectSize"
QT_MOC_LITERAL(145, 1827, 17), // "getPageObjectType"
QT_MOC_LITERAL(146, 1845, 19), // "getPageObjectSource"
QT_MOC_LITERAL(147, 1865, 18), // "getPageObjectColor"
QT_MOC_LITERAL(148, 1884, 14), // "getPageObjectX"
QT_MOC_LITERAL(149, 1899, 14), // "getPageObjectY"
QT_MOC_LITERAL(150, 1914, 18), // "getPageObjectWidth"
QT_MOC_LITERAL(151, 1933, 19), // "getPageObjectHeight"
QT_MOC_LITERAL(152, 1953, 21), // "getPageObjectFontsize"
QT_MOC_LITERAL(153, 1975, 15), // "addPatrolObject"
QT_MOC_LITERAL(154, 1991, 3), // "obj"
QT_MOC_LITERAL(155, 1995, 19), // "setPageObjectSource"
QT_MOC_LITERAL(156, 2015, 3), // "src"
QT_MOC_LITERAL(157, 2019, 18), // "setPageObjectColor"
QT_MOC_LITERAL(158, 2038, 5), // "color"
QT_MOC_LITERAL(159, 2044, 18), // "deletePatrolObject"
QT_MOC_LITERAL(160, 2063, 16), // "movePatrolObject"
QT_MOC_LITERAL(161, 2080, 1), // "x"
QT_MOC_LITERAL(162, 2082, 1), // "y"
QT_MOC_LITERAL(163, 2084, 19), // "setPatrolObjectSize"
QT_MOC_LITERAL(164, 2104, 5), // "point"
QT_MOC_LITERAL(165, 2110, 5), // "width"
QT_MOC_LITERAL(166, 2116, 6), // "height"
QT_MOC_LITERAL(167, 2123, 16), // "getPageObjectNum"
QT_MOC_LITERAL(168, 2140, 11), // "isExistNode"
QT_MOC_LITERAL(169, 2152, 19), // "confirmLocalization"
QT_MOC_LITERAL(170, 2172, 7), // "setName"
QT_MOC_LITERAL(171, 2180, 7), // "setTool"
QT_MOC_LITERAL(172, 2188, 7), // "getTool"
QT_MOC_LITERAL(173, 2196, 7), // "setMode"
QT_MOC_LITERAL(174, 2204, 9), // "setEnable"
QT_MOC_LITERAL(175, 2214, 2), // "en"
QT_MOC_LITERAL(176, 2217, 7), // "getMode"
QT_MOC_LITERAL(177, 2225, 12), // "setShowBrush"
QT_MOC_LITERAL(178, 2238, 5), // "onoff"
QT_MOC_LITERAL(179, 2244, 12), // "setShowLidar"
QT_MOC_LITERAL(180, 2257, 15), // "setShowLocation"
QT_MOC_LITERAL(181, 2273, 17), // "setRobotFollowing"
QT_MOC_LITERAL(182, 2291, 17), // "setShowTravelline"
QT_MOC_LITERAL(183, 2309, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(184, 2328, 13), // "setShowObject"
QT_MOC_LITERAL(185, 2342, 11), // "setInitFlag"
QT_MOC_LITERAL(186, 2354, 15), // "getshowLocation"
QT_MOC_LITERAL(187, 2370, 17), // "getRobotFollowing"
QT_MOC_LITERAL(188, 2388, 12), // "getShowLidar"
QT_MOC_LITERAL(189, 2401, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(190, 2417, 11), // "setShowNode"
QT_MOC_LITERAL(191, 2429, 11), // "getShowNode"
QT_MOC_LITERAL(192, 2441, 11), // "setShowName"
QT_MOC_LITERAL(193, 2453, 11), // "getShowName"
QT_MOC_LITERAL(194, 2465, 12), // "setShowTline"
QT_MOC_LITERAL(195, 2478, 12), // "getShowTline"
QT_MOC_LITERAL(196, 2491, 13), // "setShowVelmap"
QT_MOC_LITERAL(197, 2505, 13), // "getShowVelmap"
QT_MOC_LITERAL(198, 2519, 12), // "setShowAvoid"
QT_MOC_LITERAL(199, 2532, 12), // "getShowAvoid"
QT_MOC_LITERAL(200, 2545, 9), // "autoTline"
QT_MOC_LITERAL(201, 2555, 13), // "getShowObject"
QT_MOC_LITERAL(202, 2569, 11), // "setShowEdge"
QT_MOC_LITERAL(203, 2581, 11), // "getShowEdge"
QT_MOC_LITERAL(204, 2593, 11), // "setInitPose"
QT_MOC_LITERAL(205, 2605, 2), // "th"
QT_MOC_LITERAL(206, 2608, 13), // "clearInitPose"
QT_MOC_LITERAL(207, 2622, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(208, 2643, 17), // "startDrawingTline"
QT_MOC_LITERAL(209, 2661, 16), // "stopDrawingTline"
QT_MOC_LITERAL(210, 2678, 15), // "getDrawingTline"
QT_MOC_LITERAL(211, 2694, 13), // "setRulerPoint"
QT_MOC_LITERAL(212, 2708, 11), // "setBoxPoint"
QT_MOC_LITERAL(213, 2720, 11), // "getPointBox"
QT_MOC_LITERAL(214, 2732, 13), // "saveRotateMap"
QT_MOC_LITERAL(215, 2746, 10), // "initRotate"
QT_MOC_LITERAL(216, 2757, 9), // "rotateMap"
QT_MOC_LITERAL(217, 2767, 5), // "angle"
QT_MOC_LITERAL(218, 2773, 11), // "rotateMapCW"
QT_MOC_LITERAL(219, 2785, 12), // "rotateMapCCW"
QT_MOC_LITERAL(220, 2798, 13), // "saveObjectPNG"
QT_MOC_LITERAL(221, 2812, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(222, 2827, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(223, 2850, 14), // "getDrawingFlag"
QT_MOC_LITERAL(224, 2865, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(225, 2884, 12), // "startDrawing"
QT_MOC_LITERAL(226, 2897, 12), // "addLinePoint"
QT_MOC_LITERAL(227, 2910, 10), // "endDrawing"
QT_MOC_LITERAL(228, 2921, 11), // "startErase2"
QT_MOC_LITERAL(229, 2933, 9), // "addErase2"
QT_MOC_LITERAL(230, 2943, 9), // "endErase2"
QT_MOC_LITERAL(231, 2953, 10), // "setMapOrin"
QT_MOC_LITERAL(232, 2964, 16), // "startDrawingRect"
QT_MOC_LITERAL(233, 2981, 14), // "setDrawingRect"
QT_MOC_LITERAL(234, 2996, 14), // "endDrawingRect"
QT_MOC_LITERAL(235, 3011, 12), // "clearDrawing"
QT_MOC_LITERAL(236, 3024, 8), // "undoLine"
QT_MOC_LITERAL(237, 3033, 8), // "redoLine"
QT_MOC_LITERAL(238, 3042, 11), // "startSpline"
QT_MOC_LITERAL(239, 3054, 9), // "addSpline"
QT_MOC_LITERAL(240, 3064, 10), // "drawSpline"
QT_MOC_LITERAL(241, 3075, 9), // "endSpline"
QT_MOC_LITERAL(242, 3085, 4), // "save"
QT_MOC_LITERAL(243, 3090, 16), // "startDrawingLine"
QT_MOC_LITERAL(244, 3107, 14), // "setDrawingLine"
QT_MOC_LITERAL(245, 3122, 15), // "stopDrawingLine"
QT_MOC_LITERAL(246, 3138, 12), // "setLineColor"
QT_MOC_LITERAL(247, 3151, 12), // "setLineWidth"
QT_MOC_LITERAL(248, 3164, 7), // "pressed"
QT_MOC_LITERAL(249, 3172, 4), // "tool"
QT_MOC_LITERAL(250, 3177, 14), // "double_pressed"
QT_MOC_LITERAL(251, 3192, 2), // "x1"
QT_MOC_LITERAL(252, 3195, 2), // "y1"
QT_MOC_LITERAL(253, 3198, 2), // "x2"
QT_MOC_LITERAL(254, 3201, 2), // "y2"
QT_MOC_LITERAL(255, 3204, 5), // "moved"
QT_MOC_LITERAL(256, 3210, 12), // "double_moved"
QT_MOC_LITERAL(257, 3223, 8), // "released"
QT_MOC_LITERAL(258, 3232, 15), // "double_released"
QT_MOC_LITERAL(259, 3248, 14), // "getLocationNum"
QT_MOC_LITERAL(260, 3263, 12), // "saveLocation"
QT_MOC_LITERAL(261, 3276, 8), // "groupnum"
QT_MOC_LITERAL(262, 3285, 13), // "clearLocation"
QT_MOC_LITERAL(263, 3299, 11), // "addLocation"
QT_MOC_LITERAL(264, 3311, 14), // "addLocationCur"
QT_MOC_LITERAL(265, 3326, 11), // "setLocation"
QT_MOC_LITERAL(266, 3338, 12), // "editLocation"
QT_MOC_LITERAL(267, 3351, 14), // "removeLocation"
QT_MOC_LITERAL(268, 3366, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(269, 3385, 14), // "getLocGroupNum"
QT_MOC_LITERAL(270, 3400, 7), // "saveMap"
QT_MOC_LITERAL(271, 3408, 13), // "saveEditedMap"
QT_MOC_LITERAL(272, 3422, 9), // "saveTline"
QT_MOC_LITERAL(273, 3432, 13), // "saveTlineTemp"
QT_MOC_LITERAL(274, 3446, 10), // "saveVelmap"
QT_MOC_LITERAL(275, 3457, 10), // "setMapSize"
QT_MOC_LITERAL(276, 3468, 14), // "loadAnnotation"
QT_MOC_LITERAL(277, 3483, 7), // "addNode"
QT_MOC_LITERAL(278, 3491, 2), // "id"
QT_MOC_LITERAL(279, 3494, 4), // "attr"
QT_MOC_LITERAL(280, 3499, 8), // "editNode"
QT_MOC_LITERAL(281, 3508, 10), // "deleteNode"
QT_MOC_LITERAL(282, 3519, 8), // "linkNode"
QT_MOC_LITERAL(283, 3528, 9), // "alignNode"
QT_MOC_LITERAL(284, 3538, 1), // "n"
QT_MOC_LITERAL(285, 3540, 12), // "releaseShift"
QT_MOC_LITERAL(286, 3553, 10), // "pressShift"
QT_MOC_LITERAL(287, 3564, 6), // "zoomIn"
QT_MOC_LITERAL(288, 3571, 4), // "dist"
QT_MOC_LITERAL(289, 3576, 7), // "zoomOut"
QT_MOC_LITERAL(290, 3584, 4), // "move"
QT_MOC_LITERAL(291, 3589, 12), // "getFileWidth"
QT_MOC_LITERAL(292, 3602, 4), // "getX"
QT_MOC_LITERAL(293, 3607, 4), // "getY"
QT_MOC_LITERAL(294, 3612, 8), // "getScale"
QT_MOC_LITERAL(295, 3621, 13), // "setVelmapView"
QT_MOC_LITERAL(296, 3635, 12), // "setTlineView"
QT_MOC_LITERAL(297, 3648, 13), // "setObjectView"
QT_MOC_LITERAL(298, 3662, 15), // "setAvoidmapView"
QT_MOC_LITERAL(299, 3678, 15), // "setLocationView"
QT_MOC_LITERAL(300, 3694, 12), // "setRobotView"
QT_MOC_LITERAL(301, 3707, 15), // "setSystemVolume"
QT_MOC_LITERAL(302, 3723, 19), // "requestSystemVolume"
QT_MOC_LITERAL(303, 3743, 7), // "setSize"
QT_MOC_LITERAL(304, 3751, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(305, 3765, 14), // "selectLocation"
QT_MOC_LITERAL(306, 3780, 8), // "writelog"
QT_MOC_LITERAL(307, 3789, 3), // "msg"
QT_MOC_LITERAL(308, 3793, 18), // "startDrawingObject"
QT_MOC_LITERAL(309, 3812, 17), // "stopDrawingObject"
QT_MOC_LITERAL(310, 3830, 17), // "saveDrawingObject"
QT_MOC_LITERAL(311, 3848, 13), // "setLocationUp"
QT_MOC_LITERAL(312, 3862, 15), // "setLocationDown"
QT_MOC_LITERAL(313, 3878, 8), // "checkINI"
QT_MOC_LITERAL(314, 3887, 8), // "killSLAM"
QT_MOC_LITERAL(315, 3896, 12), // "makeRobotINI"
QT_MOC_LITERAL(316, 3909, 13), // "checkRobotINI"
QT_MOC_LITERAL(317, 3923, 11), // "restartSLAM"
QT_MOC_LITERAL(318, 3935, 9), // "startSLAM"
QT_MOC_LITERAL(319, 3945, 16), // "getIPCConnection"
QT_MOC_LITERAL(320, 3962, 8), // "getIPCRX"
QT_MOC_LITERAL(321, 3971, 8), // "getIPCTX"
QT_MOC_LITERAL(322, 3980, 14), // "programRestart"
QT_MOC_LITERAL(323, 3995, 11), // "programExit"
QT_MOC_LITERAL(324, 4007, 13), // "getRawMapPath"
QT_MOC_LITERAL(325, 4021, 10), // "getMapPath"
QT_MOC_LITERAL(326, 4032, 12), // "getAnnotPath"
QT_MOC_LITERAL(327, 4045, 11), // "getMetaPath"
QT_MOC_LITERAL(328, 4057, 13), // "getTravelPath"
QT_MOC_LITERAL(329, 4071, 11), // "getCostPath"
QT_MOC_LITERAL(330, 4083, 10), // "getIniPath"
QT_MOC_LITERAL(331, 4094, 10), // "setSetting"
QT_MOC_LITERAL(332, 4105, 5), // "value"
QT_MOC_LITERAL(333, 4111, 11), // "readSetting"
QT_MOC_LITERAL(334, 4123, 8), // "map_name"
QT_MOC_LITERAL(335, 4132, 10), // "getSetting"
QT_MOC_LITERAL(336, 4143, 10), // "getTrayNum"
QT_MOC_LITERAL(337, 4154, 14), // "setTableColNum"
QT_MOC_LITERAL(338, 4169, 7), // "col_num"
QT_MOC_LITERAL(339, 4177, 12), // "getRobotType"
QT_MOC_LITERAL(340, 4190, 13), // "requestCamera"
QT_MOC_LITERAL(341, 4204, 13), // "getLeftCamera"
QT_MOC_LITERAL(342, 4218, 14), // "getRightCamera"
QT_MOC_LITERAL(343, 4233, 9), // "setCamera"
QT_MOC_LITERAL(344, 4243, 4), // "left"
QT_MOC_LITERAL(345, 4248, 5), // "right"
QT_MOC_LITERAL(346, 4254, 12), // "getCameraNum"
QT_MOC_LITERAL(347, 4267, 15), // "getCameraSerial"
QT_MOC_LITERAL(348, 4283, 13), // "setCursorView"
QT_MOC_LITERAL(349, 4297, 7), // "visible"
QT_MOC_LITERAL(350, 4305, 15), // "checkTravelline"
QT_MOC_LITERAL(351, 4321, 13), // "updateProgram"
QT_MOC_LITERAL(352, 4335, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(353, 4356, 17), // "checkVersionAgain"
QT_MOC_LITERAL(354, 4374, 12), // "isNewVersion"
QT_MOC_LITERAL(355, 4387, 12), // "isNeedUpdate"
QT_MOC_LITERAL(356, 4400, 15), // "getLocalVersion"
QT_MOC_LITERAL(357, 4416, 16), // "getServerVersion"
QT_MOC_LITERAL(358, 4433, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(359, 4453, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(360, 4476, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(361, 4500, 13), // "getUpdateDate"
QT_MOC_LITERAL(362, 4514, 13), // "getUpdateSize"
QT_MOC_LITERAL(363, 4528, 17), // "getUpdateFileName"
QT_MOC_LITERAL(364, 4546, 15), // "getUpdateCommit"
QT_MOC_LITERAL(365, 4562, 16), // "getCurrentCommit"
QT_MOC_LITERAL(366, 4579, 16), // "getUpdateMessage"
QT_MOC_LITERAL(367, 4596, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(368, 4614, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(369, 4636, 12), // "isRobotReady"
QT_MOC_LITERAL(370, 4649, 11), // "checkUpdate"
QT_MOC_LITERAL(371, 4661, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(372, 4683, 11), // "setlanguage"
QT_MOC_LITERAL(373, 4695, 13), // "isCallingMode"
QT_MOC_LITERAL(374, 4709, 12), // "startServing"
QT_MOC_LITERAL(375, 4722, 5), // "table"
QT_MOC_LITERAL(376, 4728, 11), // "getLocation"
QT_MOC_LITERAL(377, 4740, 8), // "LOCATION"
QT_MOC_LITERAL(378, 4749, 10), // "setUiState"
QT_MOC_LITERAL(379, 4760, 5), // "state"
QT_MOC_LITERAL(380, 4766, 11), // "clearStatus"
QT_MOC_LITERAL(381, 4778, 9), // "stateInit"
QT_MOC_LITERAL(382, 4788, 11), // "stateMoving"
QT_MOC_LITERAL(383, 4800, 17), // "resetLocalization"
QT_MOC_LITERAL(384, 4818, 6), // "setLog"
QT_MOC_LITERAL(385, 4825, 13), // "getLogLineNum"
QT_MOC_LITERAL(386, 4839, 10), // "getLogLine"
QT_MOC_LITERAL(387, 4850, 10), // "getLogDate"
QT_MOC_LITERAL(388, 4861, 10), // "getLogAuth"
QT_MOC_LITERAL(389, 4872, 13), // "getLogMessage"
QT_MOC_LITERAL(390, 4886, 7), // "readLog"
QT_MOC_LITERAL(391, 4894, 4), // "date"
QT_MOC_LITERAL(392, 4899, 13), // "getLocaleDate"
QT_MOC_LITERAL(393, 4913, 4), // "year"
QT_MOC_LITERAL(394, 4918, 5), // "month"
QT_MOC_LITERAL(395, 4924, 9), // "updateUSB"
QT_MOC_LITERAL(396, 4934, 10), // "getusbsize"
QT_MOC_LITERAL(397, 4945, 17), // "readusbrecentfile"
QT_MOC_LITERAL(398, 4963, 14), // "getusbfilesize"
QT_MOC_LITERAL(399, 4978, 10), // "getusbfile"
QT_MOC_LITERAL(400, 4989, 16), // "getusbrecentfile"
QT_MOC_LITERAL(401, 5006, 10), // "getusbname"
QT_MOC_LITERAL(402, 5017, 7), // "readusb"
QT_MOC_LITERAL(403, 5025, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(404, 5040, 4), // "path"
QT_MOC_LITERAL(405, 5045, 15), // "isConnectServer"
QT_MOC_LITERAL(406, 5061, 9), // "isLoadMap"
QT_MOC_LITERAL(407, 5071, 10), // "isExistMap"
QT_MOC_LITERAL(408, 5082, 13), // "isExistRawMap"
QT_MOC_LITERAL(409, 5096, 15), // "isExistTlineMap"
QT_MOC_LITERAL(410, 5112, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(411, 5128, 13), // "isExistVelMap"
QT_MOC_LITERAL(412, 5142, 16), // "isExistObjectMap"
QT_MOC_LITERAL(413, 5159, 16), // "isExistTravelMap"
QT_MOC_LITERAL(414, 5176, 17), // "isExistAnnotation"
QT_MOC_LITERAL(415, 5194, 15), // "isExistRobotINI"
QT_MOC_LITERAL(416, 5210, 15), // "getAvailableMap"
QT_MOC_LITERAL(417, 5226, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(418, 5246, 14), // "getMapFileSize"
QT_MOC_LITERAL(419, 5261, 10), // "getMapFile"
QT_MOC_LITERAL(420, 5272, 15), // "deleteEditedMap"
QT_MOC_LITERAL(421, 5288, 16), // "deleteAnnotation"
QT_MOC_LITERAL(422, 5305, 9), // "removeMap"
QT_MOC_LITERAL(423, 5315, 8), // "filename"
QT_MOC_LITERAL(424, 5324, 7), // "loadMap"
QT_MOC_LITERAL(425, 5332, 7), // "copyMap"
QT_MOC_LITERAL(426, 5340, 8), // "orinname"
QT_MOC_LITERAL(427, 5349, 7), // "newname"
QT_MOC_LITERAL(428, 5357, 10), // "rotate_map"
QT_MOC_LITERAL(429, 5368, 4), // "_src"
QT_MOC_LITERAL(430, 5373, 4), // "_dst"
QT_MOC_LITERAL(431, 5378, 12), // "startMapping"
QT_MOC_LITERAL(432, 5391, 7), // "mapsize"
QT_MOC_LITERAL(433, 5399, 4), // "grid"
QT_MOC_LITERAL(434, 5404, 11), // "stopMapping"
QT_MOC_LITERAL(435, 5416, 11), // "setSLAMMode"
QT_MOC_LITERAL(436, 5428, 11), // "saveMapping"
QT_MOC_LITERAL(437, 5440, 13), // "setInitCurPos"
QT_MOC_LITERAL(438, 5454, 10), // "setInitPos"
QT_MOC_LITERAL(439, 5465, 12), // "getInitPoseX"
QT_MOC_LITERAL(440, 5478, 12), // "getInitPoseY"
QT_MOC_LITERAL(441, 5491, 13), // "getInitPoseTH"
QT_MOC_LITERAL(442, 5505, 12), // "slam_setInit"
QT_MOC_LITERAL(443, 5518, 8), // "slam_run"
QT_MOC_LITERAL(444, 5527, 9), // "slam_stop"
QT_MOC_LITERAL(445, 5537, 13), // "slam_autoInit"
QT_MOC_LITERAL(446, 5551, 13), // "slam_restInit"
QT_MOC_LITERAL(447, 5565, 15), // "is_slam_running"
QT_MOC_LITERAL(448, 5581, 14), // "getMappingflag"
QT_MOC_LITERAL(449, 5596, 16), // "getObjectingflag"
QT_MOC_LITERAL(450, 5613, 16), // "setObjectingflag"
QT_MOC_LITERAL(451, 5630, 4), // "flag"
QT_MOC_LITERAL(452, 5635, 13), // "getnewMapname"
QT_MOC_LITERAL(453, 5649, 11), // "getLastCall"
QT_MOC_LITERAL(454, 5661, 11), // "getCallSize"
QT_MOC_LITERAL(455, 5673, 16), // "getCallQueueSize"
QT_MOC_LITERAL(456, 5690, 9), // "cleanTray"
QT_MOC_LITERAL(457, 5700, 11), // "getCallName"
QT_MOC_LITERAL(458, 5712, 14), // "clearCallQueue"
QT_MOC_LITERAL(459, 5727, 7), // "getCall"
QT_MOC_LITERAL(460, 5735, 11), // "setCallbell"
QT_MOC_LITERAL(461, 5747, 16), // "setCallbellForce"
QT_MOC_LITERAL(462, 5764, 10), // "setObjPose"
QT_MOC_LITERAL(463, 5775, 14), // "getServingName"
QT_MOC_LITERAL(464, 5790, 15), // "getLocationName"
QT_MOC_LITERAL(465, 5806, 15), // "getLocationType"
QT_MOC_LITERAL(466, 5822, 17), // "getLocationNumber"
QT_MOC_LITERAL(467, 5840, 17), // "setLocationNumber"
QT_MOC_LITERAL(468, 5858, 15), // "getLocationSize"
QT_MOC_LITERAL(469, 5874, 16), // "getLocationGroup"
QT_MOC_LITERAL(470, 5891, 13), // "getLocationID"
QT_MOC_LITERAL(471, 5905, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(472, 5925, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(473, 5946, 17), // "getLocationCallID"
QT_MOC_LITERAL(474, 5964, 16), // "setLocationGroup"
QT_MOC_LITERAL(475, 5981, 19), // "removeLocationGroup"
QT_MOC_LITERAL(476, 6001, 16), // "addLocationGroup"
QT_MOC_LITERAL(477, 6018, 15), // "getLocGroupname"
QT_MOC_LITERAL(478, 6034, 8), // "tablenum"
QT_MOC_LITERAL(479, 6043, 12), // "getLocationX"
QT_MOC_LITERAL(480, 6056, 12), // "getLocationY"
QT_MOC_LITERAL(481, 6069, 13), // "getLocationTH"
QT_MOC_LITERAL(482, 6083, 15), // "isExistLocation"
QT_MOC_LITERAL(483, 6099, 8), // "getLidar"
QT_MOC_LITERAL(484, 6108, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(485, 6125, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(486, 6142, 17), // "clearSharedMemory"
QT_MOC_LITERAL(487, 6160, 12), // "getObjectNum"
QT_MOC_LITERAL(488, 6173, 13), // "getObjectName"
QT_MOC_LITERAL(489, 6187, 18), // "getObjectPointSize"
QT_MOC_LITERAL(490, 6206, 10), // "getObjectX"
QT_MOC_LITERAL(491, 6217, 10), // "getObjectY"
QT_MOC_LITERAL(492, 6228, 14), // "getObjPointNum"
QT_MOC_LITERAL(493, 6243, 7), // "obj_num"
QT_MOC_LITERAL(494, 6251, 9), // "getLocNum"
QT_MOC_LITERAL(495, 6261, 13), // "saveLocations"
QT_MOC_LITERAL(496, 6275, 13), // "getObjectSize"
QT_MOC_LITERAL(497, 6289, 12), // "removeObject"
QT_MOC_LITERAL(498, 6302, 14), // "saveAnnotation"
QT_MOC_LITERAL(499, 6317, 6), // "reload"
QT_MOC_LITERAL(500, 6324, 8), // "saveNode"
QT_MOC_LITERAL(501, 6333, 8), // "isOdroid"
QT_MOC_LITERAL(502, 6342, 13), // "getMultiState"
QT_MOC_LITERAL(503, 6356, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(504, 6376, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(505, 6395, 15), // "getRunawayState"
QT_MOC_LITERAL(506, 6411, 15), // "slam_map_reload"
QT_MOC_LITERAL(507, 6427, 15), // "slam_ini_reload"
QT_MOC_LITERAL(508, 6443, 7), // "setTray"
QT_MOC_LITERAL(509, 6451, 8), // "tray_num"
QT_MOC_LITERAL(510, 6460, 9), // "setPreset"
QT_MOC_LITERAL(511, 6470, 6), // "preset"
QT_MOC_LITERAL(512, 6477, 13), // "confirmPickup"
QT_MOC_LITERAL(513, 6491, 14), // "getPickuptrays"
QT_MOC_LITERAL(514, 6506, 10), // "QList<int>"
QT_MOC_LITERAL(515, 6517, 9), // "movePause"
QT_MOC_LITERAL(516, 6527, 10), // "moveResume"
QT_MOC_LITERAL(517, 6538, 12), // "moveStopFlag"
QT_MOC_LITERAL(518, 6551, 8), // "moveStop"
QT_MOC_LITERAL(519, 6560, 12), // "moveToCharge"
QT_MOC_LITERAL(520, 6573, 10), // "moveToWait"
QT_MOC_LITERAL(521, 6584, 14), // "moveToCleaning"
QT_MOC_LITERAL(522, 6599, 9), // "getcurLoc"
QT_MOC_LITERAL(523, 6609, 11), // "getcurTable"
QT_MOC_LITERAL(524, 6621, 16), // "resetHomeFolders"
QT_MOC_LITERAL(525, 6638, 13), // "issetLocation"
QT_MOC_LITERAL(526, 6652, 6), // "number"
QT_MOC_LITERAL(527, 6659, 11), // "getObsState"
QT_MOC_LITERAL(528, 6671, 10), // "getBattery"
QT_MOC_LITERAL(529, 6682, 13), // "getMotorState"
QT_MOC_LITERAL(530, 6696, 20), // "getLocalizationState"
QT_MOC_LITERAL(531, 6717, 14), // "getStateMoving"
QT_MOC_LITERAL(532, 6732, 10), // "getErrcode"
QT_MOC_LITERAL(533, 6743, 12), // "getRobotName"
QT_MOC_LITERAL(534, 6756, 18), // "getMotorConnection"
QT_MOC_LITERAL(535, 6775, 14), // "getMotorStatus"
QT_MOC_LITERAL(536, 6790, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(537, 6808, 19), // "getMotorTemperature"
QT_MOC_LITERAL(538, 6828, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(539, 6854, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(540, 6881, 15), // "getMotorCurrent"
QT_MOC_LITERAL(541, 6897, 14), // "getPowerStatus"
QT_MOC_LITERAL(542, 6912, 15), // "getRemoteStatus"
QT_MOC_LITERAL(543, 6928, 22), // "getChargeConnectStatus"
QT_MOC_LITERAL(544, 6951, 15), // "getChargeStatus"
QT_MOC_LITERAL(545, 6967, 12), // "getEmoStatus"
QT_MOC_LITERAL(546, 6980, 13), // "getLockStatus"
QT_MOC_LITERAL(547, 6994, 12), // "getBatteryIn"
QT_MOC_LITERAL(548, 7007, 13), // "getBatteryOut"
QT_MOC_LITERAL(549, 7021, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(550, 7039, 8), // "getPower"
QT_MOC_LITERAL(551, 7048, 13), // "getPowerTotal"
QT_MOC_LITERAL(552, 7062, 12), // "getObsinPath"
QT_MOC_LITERAL(553, 7075, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(554, 7093, 12), // "setMotorLock"
QT_MOC_LITERAL(555, 7106, 14), // "getRobotRadius"
QT_MOC_LITERAL(556, 7121, 9), // "getRobotx"
QT_MOC_LITERAL(557, 7131, 9), // "getRoboty"
QT_MOC_LITERAL(558, 7141, 10), // "getRobotth"
QT_MOC_LITERAL(559, 7152, 13), // "getlastRobotx"
QT_MOC_LITERAL(560, 7166, 13), // "getlastRoboty"
QT_MOC_LITERAL(561, 7180, 14), // "getlastRobotth"
QT_MOC_LITERAL(562, 7195, 10), // "getPathNum"
QT_MOC_LITERAL(563, 7206, 8), // "getPathx"
QT_MOC_LITERAL(564, 7215, 8), // "getPathy"
QT_MOC_LITERAL(565, 7224, 9), // "getPathth"
QT_MOC_LITERAL(566, 7234, 15), // "getLocalPathNum"
QT_MOC_LITERAL(567, 7250, 13), // "getLocalPathx"
QT_MOC_LITERAL(568, 7264, 13), // "getLocalPathy"
QT_MOC_LITERAL(569, 7278, 10), // "getuistate"
QT_MOC_LITERAL(570, 7289, 10), // "getMapname"
QT_MOC_LITERAL(571, 7300, 10), // "getMappath"
QT_MOC_LITERAL(572, 7311, 11), // "getMapWidth"
QT_MOC_LITERAL(573, 7323, 12), // "getMapHeight"
QT_MOC_LITERAL(574, 7336, 12), // "getGridWidth"
QT_MOC_LITERAL(575, 7349, 9), // "getOrigin"
QT_MOC_LITERAL(576, 7359, 15), // "getMappingWidth"
QT_MOC_LITERAL(577, 7375, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(578, 7395, 17), // "getObjectPointNum"
QT_MOC_LITERAL(579, 7413, 9), // "addObject"
QT_MOC_LITERAL(580, 7423, 14), // "addObjectPoint"
QT_MOC_LITERAL(581, 7438, 9), // "setObject"
QT_MOC_LITERAL(582, 7448, 15), // "editObjectStart"
QT_MOC_LITERAL(583, 7464, 10), // "editObject"
QT_MOC_LITERAL(584, 7475, 10), // "saveObject"
QT_MOC_LITERAL(585, 7486, 11), // "clearObject"
QT_MOC_LITERAL(586, 7498, 14), // "clearObjectAll"
QT_MOC_LITERAL(587, 7513, 12), // "selectObject"
QT_MOC_LITERAL(588, 7526, 13), // "getObjectflag"
QT_MOC_LITERAL(589, 7540, 10), // "undoObject"
QT_MOC_LITERAL(590, 7551, 11), // "getICPRatio"
QT_MOC_LITERAL(591, 7563, 11), // "getICPError"
QT_MOC_LITERAL(592, 7575, 13), // "clearFlagStop"
QT_MOC_LITERAL(593, 7589, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(594, 7607, 17), // "moveToServingTest"
QT_MOC_LITERAL(595, 7625, 15), // "getusberrorsize"
QT_MOC_LITERAL(596, 7641, 11), // "getusberror"
QT_MOC_LITERAL(597, 7653, 11), // "getzipstate"
QT_MOC_LITERAL(598, 7665, 10), // "clear_call"
QT_MOC_LITERAL(599, 7676, 7), // "usbsave"
QT_MOC_LITERAL(600, 7684, 3), // "usb"
QT_MOC_LITERAL(601, 7688, 3), // "_ui"
QT_MOC_LITERAL(602, 7692, 5), // "_slam"
QT_MOC_LITERAL(603, 7698, 7), // "_config"
QT_MOC_LITERAL(604, 7706, 4), // "_map"
QT_MOC_LITERAL(605, 7711, 4), // "_log"
QT_MOC_LITERAL(606, 7716, 13), // "restartUpdate"
QT_MOC_LITERAL(607, 7730, 11), // "startUpdate"
QT_MOC_LITERAL(608, 7742, 18), // "getTravellineIssue"
QT_MOC_LITERAL(609, 7761, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(610, 7785, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(611, 7808, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(612, 7830, 24) // "getTravellineIssueBroken"

    },
    "Supervisor\0onTimer\0\0path_changed\0"
    "camera_update\0mapping_update\0usb_detect\0"
    "git_pull_failed\0git_pull_success\0"
    "new_call\0process_accept\0cmd\0process_done\0"
    "process_error\0param\0process_timeout\0"
    "update_success\0update_fail\0clear_all\0"
    "map_reset\0new_call_order\0name\0play_voice\0"
    "ST_VOICE\0voice\0emo_state_changed\0"
    "setCurrentPage\0page\0loadMapServer\0"
    "sendMapServer\0checkLocationName\0group\0"
    "resetClear\0getWifiNum\0getWifiConnection\0"
    "ssid\0getCurWifiSSID\0getWifiSSID\0num\0"
    "connectWifi\0passwd\0getWifiSecurity\0"
    "getWifiLevel\0getWifiRate\0getWifiInuse\0"
    "getAllWifiList\0getWifiIP\0setWifi\0ip\0"
    "gateway\0dns\0getcurIP\0getcurGateway\0"
    "getcurDNS\0readWifiState\0setWifiSSD\0"
    "getSystemVolume\0passInit\0isDebugMode\0"
    "readPatrol\0getPatrolSize\0getPatrolName\0"
    "getPatrolType\0getPatrolLocation\0"
    "getPatrolMovingPage\0getPatrolArrivePage\0"
    "getPatrolWaitTime\0getPatrolPassTime\0"
    "getPatrolVoice\0getPatrolVoiceMode\0"
    "getPatrolVoiceLanguage\0isPatrolPage\0"
    "getPatrolMovingMode\0getPatrolArriveMode\0"
    "setCurrentPatrol\0getPatrolLocationSize\0"
    "loc\0clearPatrolLocation\0mode\0"
    "addPatrolLocation\0setPatrolMovingPage\0"
    "param1\0param2\0param3\0setPatrolArrivePage\0"
    "setPatrolVoice\0language\0volume\0setPatrol\0"
    "type\0wait_time\0pass_time\0savePatrol\0"
    "deletePatrol\0startPatrol\0setTTSLanguage\0"
    "lan\0makeTTSAll\0setTTSMode\0setTTSName\0"
    "setTTSVoice\0speed\0pitch\0alpha\0emotion\0"
    "emostren\0clearTTSVoice\0saveTTSVoice\0"
    "makePatrolTTS\0text\0getTTSNameNum\0"
    "getTTSLanguageNum\0loadFile\0setMap\0"
    "setFullScreen\0setMapDrawing\0playBGM\0"
    "stopBGM\0isplayBGM\0getTTSSpeed\0getTTSPitch\0"
    "getTTSEmotion\0getTTSEmotionStrength\0"
    "getTTSAlpha\0getTTSVolume\0getTTSMention\0"
    "setTTSMention\0mention\0playVoice\0file\0"
    "playTTS\0setMovingPageBackground\0"
    "getMovingPageBackground\0setMovingPageMode\0"
    "getMovingPageMode\0setMovingPageColor\0"
    "getMovingPageColor\0setMovingPageImage\0"
    "getMovingPageImage\0setMovingPageVideo\0"
    "getMovingPageVideo\0setMovingPageAudio\0"
    "getMovingPageAudio\0clearPatrolPage\0"
    "getPatrolObjectSize\0getPageObjectType\0"
    "getPageObjectSource\0getPageObjectColor\0"
    "getPageObjectX\0getPageObjectY\0"
    "getPageObjectWidth\0getPageObjectHeight\0"
    "getPageObjectFontsize\0addPatrolObject\0"
    "obj\0setPageObjectSource\0src\0"
    "setPageObjectColor\0color\0deletePatrolObject\0"
    "movePatrolObject\0x\0y\0setPatrolObjectSize\0"
    "point\0width\0height\0getPageObjectNum\0"
    "isExistNode\0confirmLocalization\0setName\0"
    "setTool\0getTool\0setMode\0setEnable\0en\0"
    "getMode\0setShowBrush\0onoff\0setShowLidar\0"
    "setShowLocation\0setRobotFollowing\0"
    "setShowTravelline\0setShowVelocitymap\0"
    "setShowObject\0setInitFlag\0getshowLocation\0"
    "getRobotFollowing\0getShowLidar\0"
    "setShowAvoidmap\0setShowNode\0getShowNode\0"
    "setShowName\0getShowName\0setShowTline\0"
    "getShowTline\0setShowVelmap\0getShowVelmap\0"
    "setShowAvoid\0getShowAvoid\0autoTline\0"
    "getShowObject\0setShowEdge\0getShowEdge\0"
    "setInitPose\0th\0clearInitPose\0"
    "getAnnotModifiedDate\0startDrawingTline\0"
    "stopDrawingTline\0getDrawingTline\0"
    "setRulerPoint\0setBoxPoint\0getPointBox\0"
    "saveRotateMap\0initRotate\0rotateMap\0"
    "angle\0rotateMapCW\0rotateMapCCW\0"
    "saveObjectPNG\0saveObsAreaPNG\0"
    "getLocalizationConfirm\0getDrawingFlag\0"
    "getDrawingUndoFlag\0startDrawing\0"
    "addLinePoint\0endDrawing\0startErase2\0"
    "addErase2\0endErase2\0setMapOrin\0"
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
    "loadAnnotation\0addNode\0id\0attr\0editNode\0"
    "deleteNode\0linkNode\0alignNode\0n\0"
    "releaseShift\0pressShift\0zoomIn\0dist\0"
    "zoomOut\0move\0getFileWidth\0getX\0getY\0"
    "getScale\0setVelmapView\0setTlineView\0"
    "setObjectView\0setAvoidmapView\0"
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
    "visible\0checkTravelline\0updateProgram\0"
    "updateProgramGitPull\0checkVersionAgain\0"
    "isNewVersion\0isNeedUpdate\0getLocalVersion\0"
    "getServerVersion\0getLocalVersionDate\0"
    "getLocalVersionMessage\0getServerVersionMessage\0"
    "getUpdateDate\0getUpdateSize\0"
    "getUpdateFileName\0getUpdateCommit\0"
    "getCurrentCommit\0getUpdateMessage\0"
    "getLastUpdateDate\0checkCleaningLocation\0"
    "isRobotReady\0checkUpdate\0checkNewUpdateProgram\0"
    "setlanguage\0isCallingMode\0startServing\0"
    "table\0getLocation\0LOCATION\0setUiState\0"
    "state\0clearStatus\0stateInit\0stateMoving\0"
    "resetLocalization\0setLog\0getLogLineNum\0"
    "getLogLine\0getLogDate\0getLogAuth\0"
    "getLogMessage\0readLog\0date\0getLocaleDate\0"
    "year\0month\0updateUSB\0getusbsize\0"
    "readusbrecentfile\0getusbfilesize\0"
    "getusbfile\0getusbrecentfile\0getusbname\0"
    "readusb\0saveMapfromUsb\0path\0isConnectServer\0"
    "isLoadMap\0isExistMap\0isExistRawMap\0"
    "isExistTlineMap\0isExistAvoidMap\0"
    "isExistVelMap\0isExistObjectMap\0"
    "isExistTravelMap\0isExistAnnotation\0"
    "isExistRobotINI\0getAvailableMap\0"
    "getAvailableMapPath\0getMapFileSize\0"
    "getMapFile\0deleteEditedMap\0deleteAnnotation\0"
    "removeMap\0filename\0loadMap\0copyMap\0"
    "orinname\0newname\0rotate_map\0_src\0_dst\0"
    "startMapping\0mapsize\0grid\0stopMapping\0"
    "setSLAMMode\0saveMapping\0setInitCurPos\0"
    "setInitPos\0getInitPoseX\0getInitPoseY\0"
    "getInitPoseTH\0slam_setInit\0slam_run\0"
    "slam_stop\0slam_autoInit\0slam_restInit\0"
    "is_slam_running\0getMappingflag\0"
    "getObjectingflag\0setObjectingflag\0"
    "flag\0getnewMapname\0getLastCall\0"
    "getCallSize\0getCallQueueSize\0cleanTray\0"
    "getCallName\0clearCallQueue\0getCall\0"
    "setCallbell\0setCallbellForce\0setObjPose\0"
    "getServingName\0getLocationName\0"
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
    "reload\0saveNode\0isOdroid\0getMultiState\0"
    "drawingRunawayStart\0drawingRunawayStop\0"
    "getRunawayState\0slam_map_reload\0"
    "slam_ini_reload\0setTray\0tray_num\0"
    "setPreset\0preset\0confirmPickup\0"
    "getPickuptrays\0QList<int>\0movePause\0"
    "moveResume\0moveStopFlag\0moveStop\0"
    "moveToCharge\0moveToWait\0moveToCleaning\0"
    "getcurLoc\0getcurTable\0resetHomeFolders\0"
    "issetLocation\0number\0getObsState\0"
    "getBattery\0getMotorState\0getLocalizationState\0"
    "getStateMoving\0getErrcode\0getRobotName\0"
    "getMotorConnection\0getMotorStatus\0"
    "getMotorStatusStr\0getMotorTemperature\0"
    "getMotorInsideTemperature\0"
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
     569,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 2859,    2, 0x0a /* Public */,
       3,    0, 2860,    2, 0x0a /* Public */,
       4,    0, 2861,    2, 0x0a /* Public */,
       5,    0, 2862,    2, 0x0a /* Public */,
       6,    0, 2863,    2, 0x0a /* Public */,
       7,    0, 2864,    2, 0x0a /* Public */,
       8,    0, 2865,    2, 0x0a /* Public */,
       9,    0, 2866,    2, 0x0a /* Public */,
      10,    1, 2867,    2, 0x0a /* Public */,
      12,    1, 2870,    2, 0x0a /* Public */,
      13,    2, 2873,    2, 0x0a /* Public */,
      15,    1, 2878,    2, 0x0a /* Public */,
      16,    0, 2881,    2, 0x0a /* Public */,
      17,    0, 2882,    2, 0x0a /* Public */,
      18,    0, 2883,    2, 0x0a /* Public */,
      19,    0, 2884,    2, 0x0a /* Public */,
      20,    1, 2885,    2, 0x0a /* Public */,
      22,    1, 2888,    2, 0x0a /* Public */,
      25,    0, 2891,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      26,    1, 2892,    2, 0x02 /* Public */,
      28,    0, 2895,    2, 0x02 /* Public */,
      29,    0, 2896,    2, 0x02 /* Public */,
      30,    2, 2897,    2, 0x02 /* Public */,
      32,    0, 2902,    2, 0x02 /* Public */,
      33,    0, 2903,    2, 0x02 /* Public */,
      34,    1, 2904,    2, 0x02 /* Public */,
      36,    0, 2907,    2, 0x02 /* Public */,
      37,    1, 2908,    2, 0x02 /* Public */,
      39,    2, 2911,    2, 0x02 /* Public */,
      41,    1, 2916,    2, 0x02 /* Public */,
      42,    1, 2919,    2, 0x02 /* Public */,
      43,    1, 2922,    2, 0x02 /* Public */,
      44,    1, 2925,    2, 0x02 /* Public */,
      45,    0, 2928,    2, 0x02 /* Public */,
      46,    0, 2929,    2, 0x02 /* Public */,
      47,    3, 2930,    2, 0x02 /* Public */,
      51,    0, 2937,    2, 0x02 /* Public */,
      52,    0, 2938,    2, 0x02 /* Public */,
      53,    0, 2939,    2, 0x02 /* Public */,
      54,    1, 2940,    2, 0x02 /* Public */,
      55,    1, 2943,    2, 0x02 /* Public */,
      56,    0, 2946,    2, 0x02 /* Public */,
      57,    0, 2947,    2, 0x02 /* Public */,
      58,    0, 2948,    2, 0x02 /* Public */,
      59,    0, 2949,    2, 0x02 /* Public */,
      60,    0, 2950,    2, 0x02 /* Public */,
      61,    1, 2951,    2, 0x02 /* Public */,
      62,    1, 2954,    2, 0x02 /* Public */,
      63,    1, 2957,    2, 0x02 /* Public */,
      64,    1, 2960,    2, 0x02 /* Public */,
      65,    1, 2963,    2, 0x02 /* Public */,
      66,    1, 2966,    2, 0x02 /* Public */,
      67,    1, 2969,    2, 0x02 /* Public */,
      68,    1, 2972,    2, 0x02 /* Public */,
      69,    1, 2975,    2, 0x02 /* Public */,
      70,    1, 2978,    2, 0x02 /* Public */,
      71,    0, 2981,    2, 0x02 /* Public */,
      72,    0, 2982,    2, 0x02 /* Public */,
      73,    0, 2983,    2, 0x02 /* Public */,
      74,    1, 2984,    2, 0x02 /* Public */,
      75,    1, 2987,    2, 0x02 /* Public */,
      63,    2, 2990,    2, 0x02 /* Public */,
      77,    1, 2995,    2, 0x02 /* Public */,
      79,    1, 2998,    2, 0x02 /* Public */,
      80,    4, 3001,    2, 0x02 /* Public */,
      80,    3, 3010,    2, 0x22 /* Public | MethodCloned */,
      80,    2, 3017,    2, 0x22 /* Public | MethodCloned */,
      80,    1, 3022,    2, 0x22 /* Public | MethodCloned */,
      84,    4, 3025,    2, 0x02 /* Public */,
      84,    3, 3034,    2, 0x22 /* Public | MethodCloned */,
      84,    2, 3041,    2, 0x22 /* Public | MethodCloned */,
      84,    1, 3046,    2, 0x22 /* Public | MethodCloned */,
      85,    4, 3049,    2, 0x02 /* Public */,
      88,    5, 3058,    2, 0x02 /* Public */,
      92,    4, 3069,    2, 0x02 /* Public */,
      93,    1, 3078,    2, 0x02 /* Public */,
      94,    1, 3081,    2, 0x02 /* Public */,
      95,    1, 3084,    2, 0x02 /* Public */,
      97,    0, 3087,    2, 0x02 /* Public */,
      98,    1, 3088,    2, 0x02 /* Public */,
      99,    1, 3091,    2, 0x02 /* Public */,
     100,    2, 3094,    2, 0x02 /* Public */,
     100,    7, 3099,    2, 0x02 /* Public */,
     100,    6, 3114,    2, 0x22 /* Public | MethodCloned */,
     100,    5, 3127,    2, 0x22 /* Public | MethodCloned */,
     106,    2, 3138,    2, 0x02 /* Public */,
      98,    1, 3143,    2, 0x02 /* Public */,
     107,    0, 3146,    2, 0x02 /* Public */,
     108,    1, 3147,    2, 0x02 /* Public */,
     110,    0, 3150,    2, 0x02 /* Public */,
     111,    0, 3151,    2, 0x02 /* Public */,
     112,    2, 3152,    2, 0x02 /* Public */,
     112,    0, 3157,    2, 0x02 /* Public */,
     113,    0, 3158,    2, 0x02 /* Public */,
     114,    0, 3159,    2, 0x02 /* Public */,
     115,    0, 3160,    2, 0x02 /* Public */,
     116,    1, 3161,    2, 0x02 /* Public */,
     116,    0, 3164,    2, 0x22 /* Public | MethodCloned */,
     117,    0, 3165,    2, 0x02 /* Public */,
     118,    0, 3166,    2, 0x02 /* Public */,
     119,    0, 3167,    2, 0x02 /* Public */,
     120,    0, 3168,    2, 0x02 /* Public */,
     121,    0, 3169,    2, 0x02 /* Public */,
     122,    0, 3170,    2, 0x02 /* Public */,
     123,    0, 3171,    2, 0x02 /* Public */,
     124,    0, 3172,    2, 0x02 /* Public */,
     125,    1, 3173,    2, 0x02 /* Public */,
     126,    2, 3176,    2, 0x02 /* Public */,
     128,    5, 3181,    2, 0x02 /* Public */,
     128,    4, 3192,    2, 0x22 /* Public | MethodCloned */,
     128,    3, 3201,    2, 0x22 /* Public | MethodCloned */,
     128,    2, 3208,    2, 0x22 /* Public | MethodCloned */,
     128,    1, 3213,    2, 0x22 /* Public | MethodCloned */,
     130,    0, 3216,    2, 0x02 /* Public */,
     131,    1, 3217,    2, 0x02 /* Public */,
     132,    0, 3220,    2, 0x02 /* Public */,
     133,    1, 3221,    2, 0x02 /* Public */,
     134,    0, 3224,    2, 0x02 /* Public */,
     135,    1, 3225,    2, 0x02 /* Public */,
     136,    0, 3228,    2, 0x02 /* Public */,
     137,    1, 3229,    2, 0x02 /* Public */,
     138,    0, 3232,    2, 0x02 /* Public */,
     139,    1, 3233,    2, 0x02 /* Public */,
     140,    0, 3236,    2, 0x02 /* Public */,
     141,    1, 3237,    2, 0x02 /* Public */,
     142,    0, 3240,    2, 0x02 /* Public */,
     143,    1, 3241,    2, 0x02 /* Public */,
     144,    0, 3244,    2, 0x02 /* Public */,
     145,    1, 3245,    2, 0x02 /* Public */,
     146,    1, 3248,    2, 0x02 /* Public */,
     147,    1, 3251,    2, 0x02 /* Public */,
     148,    1, 3254,    2, 0x02 /* Public */,
     149,    1, 3257,    2, 0x02 /* Public */,
     150,    1, 3260,    2, 0x02 /* Public */,
     151,    1, 3263,    2, 0x02 /* Public */,
     152,    1, 3266,    2, 0x02 /* Public */,
     153,    2, 3269,    2, 0x02 /* Public */,
     155,    2, 3274,    2, 0x02 /* Public */,
     157,    2, 3279,    2, 0x02 /* Public */,
     159,    1, 3284,    2, 0x02 /* Public */,
     160,    3, 3287,    2, 0x02 /* Public */,
     163,    4, 3294,    2, 0x02 /* Public */,
     163,    5, 3303,    2, 0x02 /* Public */,
     167,    2, 3314,    2, 0x02 /* Public */,
     168,    1, 3319,    2, 0x02 /* Public */,
     169,    0, 3322,    2, 0x02 /* Public */,
     170,    1, 3323,    2, 0x02 /* Public */,
     171,    1, 3326,    2, 0x02 /* Public */,
     172,    0, 3329,    2, 0x02 /* Public */,
     173,    1, 3330,    2, 0x02 /* Public */,
     174,    1, 3333,    2, 0x02 /* Public */,
     176,    0, 3336,    2, 0x02 /* Public */,
     177,    1, 3337,    2, 0x02 /* Public */,
     179,    1, 3340,    2, 0x02 /* Public */,
     180,    1, 3343,    2, 0x02 /* Public */,
     181,    1, 3346,    2, 0x02 /* Public */,
     182,    1, 3349,    2, 0x02 /* Public */,
     183,    1, 3352,    2, 0x02 /* Public */,
     184,    1, 3355,    2, 0x02 /* Public */,
     185,    1, 3358,    2, 0x02 /* Public */,
     186,    0, 3361,    2, 0x02 /* Public */,
     187,    0, 3362,    2, 0x02 /* Public */,
     188,    0, 3363,    2, 0x02 /* Public */,
     189,    1, 3364,    2, 0x02 /* Public */,
     190,    1, 3367,    2, 0x02 /* Public */,
     191,    0, 3370,    2, 0x02 /* Public */,
     192,    1, 3371,    2, 0x02 /* Public */,
     193,    0, 3374,    2, 0x02 /* Public */,
     194,    1, 3375,    2, 0x02 /* Public */,
     195,    0, 3378,    2, 0x02 /* Public */,
     196,    1, 3379,    2, 0x02 /* Public */,
     197,    0, 3382,    2, 0x02 /* Public */,
     198,    1, 3383,    2, 0x02 /* Public */,
     199,    0, 3386,    2, 0x02 /* Public */,
     200,    0, 3387,    2, 0x02 /* Public */,
     201,    0, 3388,    2, 0x02 /* Public */,
     202,    1, 3389,    2, 0x02 /* Public */,
     203,    0, 3392,    2, 0x02 /* Public */,
     204,    3, 3393,    2, 0x02 /* Public */,
     206,    0, 3400,    2, 0x02 /* Public */,
     207,    0, 3401,    2, 0x02 /* Public */,
     208,    0, 3402,    2, 0x02 /* Public */,
     209,    0, 3403,    2, 0x02 /* Public */,
     210,    0, 3404,    2, 0x02 /* Public */,
     211,    2, 3405,    2, 0x02 /* Public */,
     212,    3, 3410,    2, 0x02 /* Public */,
     213,    2, 3417,    2, 0x02 /* Public */,
     214,    0, 3422,    2, 0x02 /* Public */,
     215,    0, 3423,    2, 0x02 /* Public */,
     216,    1, 3424,    2, 0x02 /* Public */,
     218,    0, 3427,    2, 0x02 /* Public */,
     219,    0, 3428,    2, 0x02 /* Public */,
     220,    0, 3429,    2, 0x02 /* Public */,
     221,    0, 3430,    2, 0x02 /* Public */,
     222,    0, 3431,    2, 0x02 /* Public */,
     223,    0, 3432,    2, 0x02 /* Public */,
     224,    0, 3433,    2, 0x02 /* Public */,
     225,    2, 3434,    2, 0x02 /* Public */,
     226,    2, 3439,    2, 0x02 /* Public */,
     227,    2, 3444,    2, 0x02 /* Public */,
     228,    2, 3449,    2, 0x02 /* Public */,
     229,    2, 3454,    2, 0x02 /* Public */,
     230,    2, 3459,    2, 0x02 /* Public */,
     231,    1, 3464,    2, 0x02 /* Public */,
     232,    2, 3467,    2, 0x02 /* Public */,
     233,    2, 3472,    2, 0x02 /* Public */,
     234,    0, 3477,    2, 0x02 /* Public */,
     235,    0, 3478,    2, 0x02 /* Public */,
     236,    0, 3479,    2, 0x02 /* Public */,
     237,    0, 3480,    2, 0x02 /* Public */,
     238,    2, 3481,    2, 0x02 /* Public */,
     239,    2, 3486,    2, 0x02 /* Public */,
     240,    0, 3491,    2, 0x02 /* Public */,
     241,    1, 3492,    2, 0x02 /* Public */,
     243,    2, 3495,    2, 0x02 /* Public */,
     244,    2, 3500,    2, 0x02 /* Public */,
     245,    2, 3505,    2, 0x02 /* Public */,
     246,    1, 3510,    2, 0x02 /* Public */,
     247,    1, 3513,    2, 0x02 /* Public */,
     248,    3, 3516,    2, 0x02 /* Public */,
     250,    5, 3523,    2, 0x02 /* Public */,
     255,    3, 3534,    2, 0x02 /* Public */,
     256,    5, 3541,    2, 0x02 /* Public */,
     257,    3, 3552,    2, 0x02 /* Public */,
     258,    5, 3559,    2, 0x02 /* Public */,
     259,    2, 3570,    2, 0x02 /* Public */,
     260,    3, 3575,    2, 0x02 /* Public */,
     262,    0, 3582,    2, 0x02 /* Public */,
     263,    3, 3583,    2, 0x02 /* Public */,
     264,    3, 3590,    2, 0x02 /* Public */,
     265,    3, 3597,    2, 0x02 /* Public */,
     266,    1, 3604,    2, 0x02 /* Public */,
     259,    2, 3607,    2, 0x02 /* Public */,
     267,    1, 3612,    2, 0x02 /* Public */,
     268,    0, 3615,    2, 0x02 /* Public */,
     269,    1, 3616,    2, 0x02 /* Public */,
     270,    0, 3619,    2, 0x02 /* Public */,
     271,    0, 3620,    2, 0x02 /* Public */,
     272,    0, 3621,    2, 0x02 /* Public */,
     273,    0, 3622,    2, 0x02 /* Public */,
     274,    0, 3623,    2, 0x02 /* Public */,
     275,    3, 3624,    2, 0x02 /* Public */,
     276,    0, 3631,    2, 0x02 /* Public */,
     277,    2, 3632,    2, 0x02 /* Public */,
     277,    3, 3637,    2, 0x02 /* Public */,
     280,    0, 3644,    2, 0x02 /* Public */,
     280,    1, 3645,    2, 0x02 /* Public */,
     281,    0, 3648,    2, 0x02 /* Public */,
     282,    0, 3649,    2, 0x02 /* Public */,
     283,    1, 3650,    2, 0x02 /* Public */,
     285,    0, 3653,    2, 0x02 /* Public */,
     286,    0, 3654,    2, 0x02 /* Public */,
     287,    3, 3655,    2, 0x02 /* Public */,
     289,    3, 3662,    2, 0x02 /* Public */,
     290,    2, 3669,    2, 0x02 /* Public */,
     291,    0, 3674,    2, 0x02 /* Public */,
     292,    0, 3675,    2, 0x02 /* Public */,
     293,    0, 3676,    2, 0x02 /* Public */,
     294,    0, 3677,    2, 0x02 /* Public */,
     295,    1, 3678,    2, 0x02 /* Public */,
     296,    1, 3681,    2, 0x02 /* Public */,
     297,    1, 3684,    2, 0x02 /* Public */,
     298,    1, 3687,    2, 0x02 /* Public */,
     299,    1, 3690,    2, 0x02 /* Public */,
     300,    1, 3693,    2, 0x02 /* Public */,
     301,    1, 3696,    2, 0x02 /* Public */,
     302,    0, 3699,    2, 0x02 /* Public */,
     303,    3, 3700,    2, 0x02 /* Public */,
     304,    0, 3707,    2, 0x02 /* Public */,
     305,    1, 3708,    2, 0x02 /* Public */,
     306,    1, 3711,    2, 0x02 /* Public */,
     308,    0, 3714,    2, 0x02 /* Public */,
     309,    0, 3715,    2, 0x02 /* Public */,
     310,    0, 3716,    2, 0x02 /* Public */,
     311,    1, 3717,    2, 0x02 /* Public */,
     312,    1, 3720,    2, 0x02 /* Public */,
     313,    0, 3723,    2, 0x02 /* Public */,
     314,    0, 3724,    2, 0x02 /* Public */,
     315,    0, 3725,    2, 0x02 /* Public */,
     316,    0, 3726,    2, 0x02 /* Public */,
     317,    0, 3727,    2, 0x02 /* Public */,
     318,    0, 3728,    2, 0x02 /* Public */,
     319,    0, 3729,    2, 0x02 /* Public */,
     320,    0, 3730,    2, 0x02 /* Public */,
     321,    0, 3731,    2, 0x02 /* Public */,
     322,    0, 3732,    2, 0x02 /* Public */,
     323,    0, 3733,    2, 0x02 /* Public */,
     324,    1, 3734,    2, 0x02 /* Public */,
     325,    1, 3737,    2, 0x02 /* Public */,
     326,    1, 3740,    2, 0x02 /* Public */,
     327,    1, 3743,    2, 0x02 /* Public */,
     328,    1, 3746,    2, 0x02 /* Public */,
     329,    1, 3749,    2, 0x02 /* Public */,
     330,    1, 3752,    2, 0x02 /* Public */,
     331,    3, 3755,    2, 0x02 /* Public */,
     333,    1, 3762,    2, 0x02 /* Public */,
     333,    0, 3765,    2, 0x22 /* Public | MethodCloned */,
     335,    3, 3766,    2, 0x02 /* Public */,
     336,    0, 3773,    2, 0x02 /* Public */,
     337,    1, 3774,    2, 0x02 /* Public */,
     339,    0, 3777,    2, 0x02 /* Public */,
     340,    0, 3778,    2, 0x02 /* Public */,
     341,    0, 3779,    2, 0x02 /* Public */,
     342,    0, 3780,    2, 0x02 /* Public */,
     343,    2, 3781,    2, 0x02 /* Public */,
     346,    0, 3786,    2, 0x02 /* Public */,
     347,    1, 3787,    2, 0x02 /* Public */,
     348,    1, 3790,    2, 0x02 /* Public */,
     350,    0, 3793,    2, 0x02 /* Public */,
     351,    0, 3794,    2, 0x02 /* Public */,
     352,    0, 3795,    2, 0x02 /* Public */,
     353,    0, 3796,    2, 0x02 /* Public */,
     354,    0, 3797,    2, 0x02 /* Public */,
     355,    0, 3798,    2, 0x02 /* Public */,
     356,    0, 3799,    2, 0x02 /* Public */,
     357,    0, 3800,    2, 0x02 /* Public */,
     358,    0, 3801,    2, 0x02 /* Public */,
     359,    0, 3802,    2, 0x02 /* Public */,
     360,    0, 3803,    2, 0x02 /* Public */,
     361,    0, 3804,    2, 0x02 /* Public */,
     362,    0, 3805,    2, 0x02 /* Public */,
     363,    1, 3806,    2, 0x02 /* Public */,
     364,    1, 3809,    2, 0x02 /* Public */,
     365,    1, 3812,    2, 0x02 /* Public */,
     366,    1, 3815,    2, 0x02 /* Public */,
     367,    1, 3818,    2, 0x02 /* Public */,
     368,    0, 3821,    2, 0x02 /* Public */,
     369,    0, 3822,    2, 0x02 /* Public */,
     370,    0, 3823,    2, 0x02 /* Public */,
     371,    0, 3824,    2, 0x02 /* Public */,
     372,    1, 3825,    2, 0x02 /* Public */,
     373,    0, 3828,    2, 0x02 /* Public */,
     374,    2, 3829,    2, 0x02 /* Public */,
     376,    2, 3834,    2, 0x02 /* Public */,
     376,    1, 3839,    2, 0x02 /* Public */,
     378,    1, 3842,    2, 0x02 /* Public */,
     380,    0, 3845,    2, 0x02 /* Public */,
     381,    0, 3846,    2, 0x02 /* Public */,
     382,    0, 3847,    2, 0x02 /* Public */,
     383,    0, 3848,    2, 0x02 /* Public */,
     384,    1, 3849,    2, 0x02 /* Public */,
     385,    0, 3852,    2, 0x02 /* Public */,
     386,    1, 3853,    2, 0x02 /* Public */,
     387,    1, 3856,    2, 0x02 /* Public */,
     388,    1, 3859,    2, 0x02 /* Public */,
     389,    1, 3862,    2, 0x02 /* Public */,
     390,    1, 3865,    2, 0x02 /* Public */,
     392,    3, 3868,    2, 0x02 /* Public */,
     395,    0, 3875,    2, 0x02 /* Public */,
     396,    0, 3876,    2, 0x02 /* Public */,
     397,    0, 3877,    2, 0x02 /* Public */,
     398,    0, 3878,    2, 0x02 /* Public */,
     399,    1, 3879,    2, 0x02 /* Public */,
     400,    0, 3882,    2, 0x02 /* Public */,
     401,    1, 3883,    2, 0x02 /* Public */,
     402,    0, 3886,    2, 0x02 /* Public */,
     403,    1, 3887,    2, 0x02 /* Public */,
     405,    0, 3890,    2, 0x02 /* Public */,
     406,    0, 3891,    2, 0x02 /* Public */,
     407,    1, 3892,    2, 0x02 /* Public */,
     407,    0, 3895,    2, 0x22 /* Public | MethodCloned */,
     408,    1, 3896,    2, 0x02 /* Public */,
     409,    1, 3899,    2, 0x02 /* Public */,
     409,    0, 3902,    2, 0x22 /* Public | MethodCloned */,
     410,    1, 3903,    2, 0x02 /* Public */,
     410,    0, 3906,    2, 0x22 /* Public | MethodCloned */,
     411,    1, 3907,    2, 0x02 /* Public */,
     411,    0, 3910,    2, 0x22 /* Public | MethodCloned */,
     412,    1, 3911,    2, 0x02 /* Public */,
     412,    0, 3914,    2, 0x22 /* Public | MethodCloned */,
     413,    1, 3915,    2, 0x02 /* Public */,
     414,    1, 3918,    2, 0x02 /* Public */,
     415,    0, 3921,    2, 0x02 /* Public */,
     416,    0, 3922,    2, 0x02 /* Public */,
     417,    1, 3923,    2, 0x02 /* Public */,
     418,    1, 3926,    2, 0x02 /* Public */,
     419,    1, 3929,    2, 0x02 /* Public */,
     420,    0, 3932,    2, 0x02 /* Public */,
     421,    0, 3933,    2, 0x02 /* Public */,
     422,    1, 3934,    2, 0x02 /* Public */,
     424,    1, 3937,    2, 0x02 /* Public */,
     425,    2, 3940,    2, 0x02 /* Public */,
     113,    1, 3945,    2, 0x02 /* Public */,
     428,    3, 3948,    2, 0x02 /* Public */,
     431,    2, 3955,    2, 0x02 /* Public */,
     434,    0, 3960,    2, 0x02 /* Public */,
     435,    1, 3961,    2, 0x02 /* Public */,
     436,    1, 3964,    2, 0x02 /* Public */,
     437,    0, 3967,    2, 0x02 /* Public */,
     438,    3, 3968,    2, 0x02 /* Public */,
     439,    0, 3975,    2, 0x02 /* Public */,
     440,    0, 3976,    2, 0x02 /* Public */,
     441,    0, 3977,    2, 0x02 /* Public */,
     442,    0, 3978,    2, 0x02 /* Public */,
     443,    0, 3979,    2, 0x02 /* Public */,
     444,    0, 3980,    2, 0x02 /* Public */,
     445,    0, 3981,    2, 0x02 /* Public */,
     446,    0, 3982,    2, 0x02 /* Public */,
     447,    0, 3983,    2, 0x02 /* Public */,
     448,    0, 3984,    2, 0x02 /* Public */,
     449,    0, 3985,    2, 0x02 /* Public */,
     450,    1, 3986,    2, 0x02 /* Public */,
     452,    0, 3989,    2, 0x02 /* Public */,
     453,    0, 3990,    2, 0x02 /* Public */,
     454,    0, 3991,    2, 0x02 /* Public */,
     455,    0, 3992,    2, 0x02 /* Public */,
     456,    0, 3993,    2, 0x02 /* Public */,
     457,    1, 3994,    2, 0x02 /* Public */,
     458,    0, 3997,    2, 0x02 /* Public */,
     459,    1, 3998,    2, 0x02 /* Public */,
     460,    2, 4001,    2, 0x02 /* Public */,
     461,    2, 4006,    2, 0x02 /* Public */,
     462,    0, 4011,    2, 0x02 /* Public */,
     463,    2, 4012,    2, 0x02 /* Public */,
     259,    1, 4017,    2, 0x02 /* Public */,
     259,    0, 4020,    2, 0x22 /* Public | MethodCloned */,
     464,    2, 4021,    2, 0x02 /* Public */,
     464,    1, 4026,    2, 0x22 /* Public | MethodCloned */,
     465,    1, 4029,    2, 0x02 /* Public */,
     466,    2, 4032,    2, 0x02 /* Public */,
     467,    2, 4037,    2, 0x02 /* Public */,
     468,    1, 4042,    2, 0x02 /* Public */,
     469,    1, 4045,    2, 0x02 /* Public */,
     470,    2, 4048,    2, 0x02 /* Public */,
     471,    0, 4053,    2, 0x02 /* Public */,
     472,    1, 4054,    2, 0x02 /* Public */,
     471,    1, 4057,    2, 0x02 /* Public */,
     473,    1, 4060,    2, 0x02 /* Public */,
     474,    2, 4063,    2, 0x02 /* Public */,
     475,    1, 4068,    2, 0x02 /* Public */,
     476,    1, 4071,    2, 0x02 /* Public */,
     477,    1, 4074,    2, 0x02 /* Public */,
     265,    4, 4077,    2, 0x02 /* Public */,
     479,    2, 4086,    2, 0x02 /* Public */,
     479,    1, 4091,    2, 0x22 /* Public | MethodCloned */,
     480,    2, 4094,    2, 0x02 /* Public */,
     480,    1, 4099,    2, 0x22 /* Public | MethodCloned */,
     481,    2, 4102,    2, 0x02 /* Public */,
     481,    1, 4107,    2, 0x22 /* Public | MethodCloned */,
     482,    2, 4110,    2, 0x02 /* Public */,
     483,    1, 4115,    2, 0x02 /* Public */,
     484,    0, 4118,    2, 0x02 /* Public */,
     485,    1, 4119,    2, 0x02 /* Public */,
     486,    0, 4122,    2, 0x02 /* Public */,
     487,    0, 4123,    2, 0x02 /* Public */,
     488,    1, 4124,    2, 0x02 /* Public */,
     489,    1, 4127,    2, 0x02 /* Public */,
     490,    2, 4130,    2, 0x02 /* Public */,
     491,    2, 4135,    2, 0x02 /* Public */,
     492,    3, 4140,    2, 0x02 /* Public */,
     494,    1, 4147,    2, 0x02 /* Public */,
     494,    2, 4150,    2, 0x02 /* Public */,
     495,    0, 4155,    2, 0x02 /* Public */,
     496,    1, 4156,    2, 0x02 /* Public */,
     497,    1, 4159,    2, 0x02 /* Public */,
     498,    2, 4162,    2, 0x02 /* Public */,
     498,    1, 4167,    2, 0x22 /* Public | MethodCloned */,
     500,    0, 4170,    2, 0x02 /* Public */,
     501,    0, 4171,    2, 0x02 /* Public */,
     502,    0, 4172,    2, 0x02 /* Public */,
     503,    0, 4173,    2, 0x02 /* Public */,
     504,    0, 4174,    2, 0x02 /* Public */,
     505,    0, 4175,    2, 0x02 /* Public */,
     506,    2, 4176,    2, 0x02 /* Public */,
     506,    1, 4181,    2, 0x22 /* Public | MethodCloned */,
     507,    0, 4184,    2, 0x02 /* Public */,
     508,    3, 4185,    2, 0x02 /* Public */,
     374,    0, 4192,    2, 0x02 /* Public */,
     510,    1, 4193,    2, 0x02 /* Public */,
     512,    0, 4196,    2, 0x02 /* Public */,
     513,    0, 4197,    2, 0x02 /* Public */,
     515,    0, 4198,    2, 0x02 /* Public */,
     516,    0, 4199,    2, 0x02 /* Public */,
     517,    0, 4200,    2, 0x02 /* Public */,
     518,    0, 4201,    2, 0x02 /* Public */,
     519,    0, 4202,    2, 0x02 /* Public */,
     520,    0, 4203,    2, 0x02 /* Public */,
     521,    0, 4204,    2, 0x02 /* Public */,
     522,    0, 4205,    2, 0x02 /* Public */,
     523,    0, 4206,    2, 0x02 /* Public */,
     524,    0, 4207,    2, 0x02 /* Public */,
     525,    1, 4208,    2, 0x02 /* Public */,
     527,    0, 4211,    2, 0x02 /* Public */,
     528,    0, 4212,    2, 0x02 /* Public */,
     529,    0, 4213,    2, 0x02 /* Public */,
     530,    0, 4214,    2, 0x02 /* Public */,
     531,    0, 4215,    2, 0x02 /* Public */,
     532,    0, 4216,    2, 0x02 /* Public */,
     533,    0, 4217,    2, 0x02 /* Public */,
     534,    1, 4218,    2, 0x02 /* Public */,
     535,    1, 4221,    2, 0x02 /* Public */,
     536,    1, 4224,    2, 0x02 /* Public */,
     537,    1, 4227,    2, 0x02 /* Public */,
     538,    1, 4230,    2, 0x02 /* Public */,
     539,    0, 4233,    2, 0x02 /* Public */,
     540,    1, 4234,    2, 0x02 /* Public */,
     541,    0, 4237,    2, 0x02 /* Public */,
     542,    0, 4238,    2, 0x02 /* Public */,
     543,    0, 4239,    2, 0x02 /* Public */,
     544,    0, 4240,    2, 0x02 /* Public */,
     545,    0, 4241,    2, 0x02 /* Public */,
     546,    0, 4242,    2, 0x02 /* Public */,
     547,    0, 4243,    2, 0x02 /* Public */,
     548,    0, 4244,    2, 0x02 /* Public */,
     549,    0, 4245,    2, 0x02 /* Public */,
     550,    0, 4246,    2, 0x02 /* Public */,
     551,    0, 4247,    2, 0x02 /* Public */,
     552,    0, 4248,    2, 0x02 /* Public */,
     553,    0, 4249,    2, 0x02 /* Public */,
     554,    1, 4250,    2, 0x02 /* Public */,
     555,    0, 4253,    2, 0x02 /* Public */,
     556,    0, 4254,    2, 0x02 /* Public */,
     557,    0, 4255,    2, 0x02 /* Public */,
     558,    0, 4256,    2, 0x02 /* Public */,
     559,    0, 4257,    2, 0x02 /* Public */,
     560,    0, 4258,    2, 0x02 /* Public */,
     561,    0, 4259,    2, 0x02 /* Public */,
     562,    0, 4260,    2, 0x02 /* Public */,
     563,    1, 4261,    2, 0x02 /* Public */,
     564,    1, 4264,    2, 0x02 /* Public */,
     565,    1, 4267,    2, 0x02 /* Public */,
     566,    0, 4270,    2, 0x02 /* Public */,
     567,    1, 4271,    2, 0x02 /* Public */,
     568,    1, 4274,    2, 0x02 /* Public */,
     569,    0, 4277,    2, 0x02 /* Public */,
     570,    0, 4278,    2, 0x02 /* Public */,
     571,    0, 4279,    2, 0x02 /* Public */,
     572,    0, 4280,    2, 0x02 /* Public */,
     573,    0, 4281,    2, 0x02 /* Public */,
     574,    0, 4282,    2, 0x02 /* Public */,
     575,    0, 4283,    2, 0x02 /* Public */,
     576,    0, 4284,    2, 0x02 /* Public */,
     577,    0, 4285,    2, 0x02 /* Public */,
     487,    2, 4286,    2, 0x02 /* Public */,
     578,    2, 4291,    2, 0x02 /* Public */,
     579,    2, 4296,    2, 0x02 /* Public */,
     580,    2, 4301,    2, 0x02 /* Public */,
     581,    2, 4306,    2, 0x02 /* Public */,
     582,    2, 4311,    2, 0x02 /* Public */,
     583,    2, 4316,    2, 0x02 /* Public */,
     584,    0, 4321,    2, 0x02 /* Public */,
     585,    0, 4322,    2, 0x02 /* Public */,
     586,    0, 4323,    2, 0x02 /* Public */,
     587,    1, 4324,    2, 0x02 /* Public */,
     588,    0, 4327,    2, 0x02 /* Public */,
     589,    0, 4328,    2, 0x02 /* Public */,
     590,    0, 4329,    2, 0x02 /* Public */,
     591,    0, 4330,    2, 0x02 /* Public */,
     592,    0, 4331,    2, 0x02 /* Public */,
     593,    0, 4332,    2, 0x02 /* Public */,
     594,    2, 4333,    2, 0x02 /* Public */,
     595,    0, 4338,    2, 0x02 /* Public */,
     596,    1, 4339,    2, 0x02 /* Public */,
     597,    0, 4342,    2, 0x02 /* Public */,
     598,    0, 4343,    2, 0x02 /* Public */,
     599,    6, 4344,    2, 0x02 /* Public */,
     599,    5, 4357,    2, 0x22 /* Public | MethodCloned */,
     599,    4, 4368,    2, 0x22 /* Public | MethodCloned */,
     599,    3, 4377,    2, 0x22 /* Public | MethodCloned */,
     599,    2, 4384,    2, 0x22 /* Public | MethodCloned */,
     599,    1, 4389,    2, 0x22 /* Public | MethodCloned */,
     599,    0, 4392,    2, 0x22 /* Public | MethodCloned */,
     606,    0, 4393,    2, 0x02 /* Public */,
     607,    0, 4394,    2, 0x02 /* Public */,
     608,    0, 4395,    2, 0x02 /* Public */,
     609,    1, 4396,    2, 0x02 /* Public */,
     610,    1, 4399,    2, 0x02 /* Public */,
     611,    1, 4402,    2, 0x02 /* Public */,
     612,    1, 4405,    2, 0x02 /* Public */,

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
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   27,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   31,   21,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   35,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   35,   40,
    QMetaType::Bool, QMetaType::QString,   35,
    QMetaType::Int, QMetaType::QString,   35,
    QMetaType::Int, QMetaType::QString,   35,
    QMetaType::Bool, QMetaType::QString,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   48,   49,   50,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   38,   76,
    QMetaType::Void, QMetaType::QString,   78,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   78,   81,   82,   83,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   78,   81,   82,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   78,   81,
    QMetaType::Void, QMetaType::QString,   78,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   78,   81,   82,   83,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   78,   81,   82,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   78,   81,
    QMetaType::Void, QMetaType::QString,   78,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,   78,   86,   24,   87,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   38,   21,   89,   90,   91,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   21,   89,   90,   91,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   96,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   96,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   96,   21,  101,  102,  103,  104,  105,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   96,   21,  101,  102,  103,  104,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   96,   21,  101,  102,  103,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   96,   21,
    QMetaType::Void, QMetaType::QString,   78,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  109,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   89,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   87,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString, QMetaType::QString,  109,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  109,  127,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,  129,   24,   78,   86,   87,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  129,   24,   78,   86,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  129,   24,   78,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  129,   24,
    QMetaType::Void, QMetaType::QString,  129,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   78,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   78,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  129,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  129,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  129,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Float,   87,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   27,  154,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   38,  156,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   38,  158,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   38,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   38,  164,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   38,  161,  162,  165,  166,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Bool, QMetaType::QString,   89,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Bool,  175,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  205,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   38,  161,  162,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  217,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::QString,   89,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  242,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int,  158,
    QMetaType::Void, QMetaType::Int,  165,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  249,  161,  162,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  249,  251,  252,  253,  254,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  249,  161,  162,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  249,  251,  252,  253,  254,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  249,  161,  162,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  249,  251,  252,  253,  254,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   31,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,   89,  261,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  205,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  205,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  205,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  154,  165,  166,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  278,  279,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   21,   31,  279,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  279,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  284,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  288,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  288,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Void, QMetaType::Int,   87,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  165,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::QString,  307,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int,   38,
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
    QMetaType::QString, QMetaType::QString,  129,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  129,   21,  332,
    QMetaType::Void, QMetaType::QString,  334,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  129,   31,   21,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  338,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  344,  345,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Bool,  349,
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
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,   96,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   31,  375,
    0x80000000 | 377, QMetaType::Int, QMetaType::QString,   31,   21,
    0x80000000 | 377, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Int,  379,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::QDateTime,  391,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  393,  394,  391,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  404,
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
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  423,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  426,  427,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  429,  430,   78,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  432,  433,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   78,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  161,  162,  205,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  451,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  278,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  278,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   89,  278,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   89,  178,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   31,   38,
    QMetaType::Int, QMetaType::QString,   89,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   38,   89,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   31,   38,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   21,   38,
    QMetaType::Int, QMetaType::QString,   89,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   31,   38,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   38,   31,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   38,   21,   31,  478,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   38,   89,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   38,   89,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   38,   89,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   31,   38,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  451,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Int, QMetaType::Int,   38,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   38,  164,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   38,  164,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  493,  161,  162,
    QMetaType::Int, QMetaType::QString,   21,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   89,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,  423,  499,
    QMetaType::Bool, QMetaType::QString,  423,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  423,   78,
    QMetaType::Void, QMetaType::QString,  423,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  509,   31,  375,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  511,
    QMetaType::Void,
    0x80000000 | 514,
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
    QMetaType::Bool, QMetaType::Int,  526,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  278,
    QMetaType::Int, QMetaType::Int,  278,
    QMetaType::QString, QMetaType::Int,  278,
    QMetaType::Int, QMetaType::Int,  278,
    QMetaType::Int, QMetaType::Int,  278,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  278,
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
    QMetaType::Void, QMetaType::Bool,  178,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Float, QMetaType::Int,   38,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    0x80000000 | 514,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  161,  162,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   31,   21,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  600,  601,  602,  603,  604,  605,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  600,  601,  602,  603,  604,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  600,  601,  602,  603,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  600,  601,  602,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  600,  601,
    QMetaType::Void, QMetaType::QString,  600,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Bool, QMetaType::Int,   38,
    QMetaType::Bool, QMetaType::Int,   38,

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
        case 17: _t->play_voice((*reinterpret_cast< ST_VOICE(*)>(_a[1]))); break;
        case 18: _t->emo_state_changed(); break;
        case 19: _t->setCurrentPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 20: _t->loadMapServer(); break;
        case 21: _t->sendMapServer(); break;
        case 22: { bool _r = _t->checkLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 23: _t->resetClear(); break;
        case 24: { int _r = _t->getWifiNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 25: { int _r = _t->getWifiConnection((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 26: { QString _r = _t->getCurWifiSSID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 27: { QString _r = _t->getWifiSSID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->connectWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: { bool _r = _t->getWifiSecurity((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 30: { int _r = _t->getWifiLevel((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 31: { int _r = _t->getWifiRate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 32: { bool _r = _t->getWifiInuse((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 33: _t->getAllWifiList(); break;
        case 34: _t->getWifiIP(); break;
        case 35: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 36: { QString _r = _t->getcurIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 37: { QString _r = _t->getcurGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 38: { QString _r = _t->getcurDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->readWifiState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 40: _t->setWifiSSD((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 41: { int _r = _t->getSystemVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 42: _t->passInit(); break;
        case 43: { bool _r = _t->isDebugMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->readPatrol(); break;
        case 45: { int _r = _t->getPatrolSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 46: { QString _r = _t->getPatrolName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 47: { QString _r = _t->getPatrolType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 48: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 49: { QString _r = _t->getPatrolMovingPage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 50: { QString _r = _t->getPatrolArrivePage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 51: { int _r = _t->getPatrolWaitTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 52: { int _r = _t->getPatrolPassTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 53: { QString _r = _t->getPatrolVoice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 54: { QString _r = _t->getPatrolVoiceMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 55: { QString _r = _t->getPatrolVoiceLanguage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 56: { bool _r = _t->isPatrolPage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 57: { QString _r = _t->getPatrolMovingMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 58: { QString _r = _t->getPatrolArriveMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->setCurrentPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 60: { int _r = _t->getPatrolLocationSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 61: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 62: _t->clearPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 63: _t->addPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 64: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 65: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 66: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 67: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 68: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 69: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 70: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 71: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 72: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 73: _t->setPatrol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 74: _t->savePatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 75: _t->deletePatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 76: _t->startPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 77: _t->setTTSLanguage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 78: _t->makeTTSAll(); break;
        case 79: _t->setTTSMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 80: _t->setTTSName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 81: _t->setTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 82: _t->setTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 83: _t->setTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 84: _t->setTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 85: _t->clearTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 86: _t->setTTSMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 87: _t->saveTTSVoice(); break;
        case 88: _t->makePatrolTTS((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 89: { int _r = _t->getTTSNameNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 90: { int _r = _t->getTTSLanguageNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 91: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 92: _t->loadFile(); break;
        case 93: _t->setMap(); break;
        case 94: _t->setFullScreen(); break;
        case 95: _t->setMapDrawing(); break;
        case 96: _t->playBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 97: _t->playBGM(); break;
        case 98: _t->stopBGM(); break;
        case 99: { bool _r = _t->isplayBGM();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 100: { int _r = _t->getTTSSpeed();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 101: { int _r = _t->getTTSPitch();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 102: { int _r = _t->getTTSEmotion();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 103: { int _r = _t->getTTSEmotionStrength();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 104: { int _r = _t->getTTSAlpha();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 105: { int _r = _t->getTTSVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 106: { QString _r = _t->getTTSMention((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 107: _t->setTTSMention((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 108: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 109: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 110: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 111: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 112: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 113: _t->playTTS(); break;
        case 114: _t->setMovingPageBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 115: { QString _r = _t->getMovingPageBackground();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 116: _t->setMovingPageMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 117: { QString _r = _t->getMovingPageMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 118: _t->setMovingPageColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 119: { QString _r = _t->getMovingPageColor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 120: _t->setMovingPageImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 121: { QString _r = _t->getMovingPageImage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 122: _t->setMovingPageVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 123: { QString _r = _t->getMovingPageVideo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 124: _t->setMovingPageAudio((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 125: { float _r = _t->getMovingPageAudio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 126: _t->clearPatrolPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 127: { int _r = _t->getPatrolObjectSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 128: { QString _r = _t->getPageObjectType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 129: { QString _r = _t->getPageObjectSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 130: { QString _r = _t->getPageObjectColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 131: { int _r = _t->getPageObjectX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 132: { int _r = _t->getPageObjectY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 133: { int _r = _t->getPageObjectWidth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 134: { int _r = _t->getPageObjectHeight((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 135: { int _r = _t->getPageObjectFontsize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 136: _t->addPatrolObject((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 137: _t->setPageObjectSource((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 138: _t->setPageObjectColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 139: _t->deletePatrolObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 140: _t->movePatrolObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 141: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 142: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 143: { int _r = _t->getPageObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 144: { bool _r = _t->isExistNode((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 145: _t->confirmLocalization(); break;
        case 146: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 147: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 148: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 149: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 150: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 151: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 152: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 153: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 154: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 155: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 156: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 157: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 158: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 159: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 160: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 161: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 162: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 163: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 164: _t->setShowNode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 165: { bool _r = _t->getShowNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 166: _t->setShowName((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 167: { bool _r = _t->getShowName();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 168: _t->setShowTline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 169: { bool _r = _t->getShowTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 170: _t->setShowVelmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 171: { bool _r = _t->getShowVelmap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 172: _t->setShowAvoid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 173: { bool _r = _t->getShowAvoid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 174: _t->autoTline(); break;
        case 175: { bool _r = _t->getShowObject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 176: _t->setShowEdge((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 177: { bool _r = _t->getShowEdge();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 178: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 179: _t->clearInitPose(); break;
        case 180: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 181: _t->startDrawingTline(); break;
        case 182: _t->stopDrawingTline(); break;
        case 183: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 184: _t->setRulerPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 185: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 186: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 187: _t->saveRotateMap(); break;
        case 188: _t->initRotate(); break;
        case 189: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 190: _t->rotateMapCW(); break;
        case 191: _t->rotateMapCCW(); break;
        case 192: _t->saveObjectPNG(); break;
        case 193: _t->saveObsAreaPNG(); break;
        case 194: { bool _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 195: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 196: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 197: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 198: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 199: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 200: _t->startErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 201: _t->addErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 202: _t->endErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 203: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 204: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 205: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 206: _t->endDrawingRect(); break;
        case 207: _t->clearDrawing(); break;
        case 208: _t->undoLine(); break;
        case 209: _t->redoLine(); break;
        case 210: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 211: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 212: _t->drawSpline(); break;
        case 213: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 214: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 215: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 216: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 217: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 218: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 219: _t->pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 220: _t->double_pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 221: _t->moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 222: _t->double_moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 223: _t->released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 224: _t->double_released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 225: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 226: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 227: _t->clearLocation(); break;
        case 228: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 229: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 230: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 231: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 232: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 233: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 234: _t->setTableNumberAuto(); break;
        case 235: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 236: _t->saveMap(); break;
        case 237: _t->saveEditedMap(); break;
        case 238: _t->saveTline(); break;
        case 239: _t->saveTlineTemp(); break;
        case 240: _t->saveVelmap(); break;
        case 241: _t->setMapSize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 242: _t->loadAnnotation(); break;
        case 243: _t->addNode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 244: _t->addNode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 245: _t->editNode(); break;
        case 246: _t->editNode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 247: _t->deleteNode(); break;
        case 248: _t->linkNode(); break;
        case 249: _t->alignNode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 250: _t->releaseShift(); break;
        case 251: _t->pressShift(); break;
        case 252: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 253: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 254: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 255: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 256: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 257: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 258: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 259: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 260: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 261: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 262: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 263: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 264: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 265: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 266: _t->requestSystemVolume(); break;
        case 267: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 268: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 269: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 270: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 271: _t->startDrawingObject(); break;
        case 272: _t->stopDrawingObject(); break;
        case 273: _t->saveDrawingObject(); break;
        case 274: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 275: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 276: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 277: _t->killSLAM(); break;
        case 278: _t->makeRobotINI(); break;
        case 279: _t->checkRobotINI(); break;
        case 280: _t->restartSLAM(); break;
        case 281: _t->startSLAM(); break;
        case 282: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 283: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 284: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 285: _t->programRestart(); break;
        case 286: _t->programExit(); break;
        case 287: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 288: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 289: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 290: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 291: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 292: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 293: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 294: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 295: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 296: _t->readSetting(); break;
        case 297: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 298: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 299: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 300: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 301: _t->requestCamera(); break;
        case 302: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 303: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 304: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 305: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 306: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 307: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 308: _t->checkTravelline(); break;
        case 309: _t->updateProgram(); break;
        case 310: _t->updateProgramGitPull(); break;
        case 311: _t->checkVersionAgain(); break;
        case 312: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 313: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 314: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 315: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 316: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 317: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 318: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 319: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 320: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 321: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 322: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 323: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 324: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 325: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 326: _t->checkCleaningLocation(); break;
        case 327: { bool _r = _t->isRobotReady();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 328: _t->checkUpdate(); break;
        case 329: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 330: _t->setlanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 331: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 332: _t->startServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 333: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 334: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 335: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 336: _t->clearStatus(); break;
        case 337: _t->stateInit(); break;
        case 338: _t->stateMoving(); break;
        case 339: _t->resetLocalization(); break;
        case 340: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 341: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 342: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 343: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 344: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 345: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 346: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 347: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 348: _t->updateUSB(); break;
        case 349: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 350: _t->readusbrecentfile(); break;
        case 351: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 352: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 353: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 354: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 355: _t->readusb(); break;
        case 356: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 357: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 358: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 359: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 360: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 361: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 362: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 363: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 364: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 365: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 366: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 367: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 368: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 369: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 370: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 371: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 372: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 373: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 374: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 375: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 376: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 377: _t->deleteEditedMap(); break;
        case 378: _t->deleteAnnotation(); break;
        case 379: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 380: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 381: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 382: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 383: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 384: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 385: _t->stopMapping(); break;
        case 386: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 387: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 388: _t->setInitCurPos(); break;
        case 389: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 390: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 391: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 392: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 393: _t->slam_setInit(); break;
        case 394: _t->slam_run(); break;
        case 395: _t->slam_stop(); break;
        case 396: _t->slam_autoInit(); break;
        case 397: _t->slam_restInit(); break;
        case 398: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 399: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 400: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 401: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 402: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 403: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 404: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 405: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 406: _t->cleanTray(); break;
        case 407: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 408: _t->clearCallQueue(); break;
        case 409: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 410: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 411: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 412: _t->setObjPose(); break;
        case 413: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 414: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 415: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 416: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 417: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 418: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 419: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 420: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 421: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 422: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 423: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 424: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 425: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 426: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 427: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 428: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 429: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 430: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 431: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 432: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 433: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 434: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 435: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 436: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 437: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 438: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 439: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 440: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 441: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 442: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 443: _t->clearSharedMemory(); break;
        case 444: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 445: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 446: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 447: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 448: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 449: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 450: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 451: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 452: _t->saveLocations(); break;
        case 453: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 454: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 455: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 456: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 457: _t->saveNode(); break;
        case 458: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 459: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 460: _t->drawingRunawayStart(); break;
        case 461: _t->drawingRunawayStop(); break;
        case 462: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 463: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 464: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 465: _t->slam_ini_reload(); break;
        case 466: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 467: _t->startServing(); break;
        case 468: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 469: _t->confirmPickup(); break;
        case 470: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 471: _t->movePause(); break;
        case 472: _t->moveResume(); break;
        case 473: _t->moveStopFlag(); break;
        case 474: _t->moveStop(); break;
        case 475: _t->moveToCharge(); break;
        case 476: _t->moveToWait(); break;
        case 477: _t->moveToCleaning(); break;
        case 478: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 479: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 480: _t->resetHomeFolders(); break;
        case 481: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 482: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 483: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 484: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 485: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 486: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 487: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 488: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 489: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 490: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 491: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 492: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 493: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 494: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 495: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 496: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 497: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 498: { int _r = _t->getChargeConnectStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 499: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 500: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 501: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 502: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 503: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 504: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 505: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 506: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 507: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 508: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 509: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 510: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 511: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 512: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 513: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 514: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 515: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 516: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 517: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 518: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 519: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 520: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 521: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 522: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 523: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 524: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 525: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 526: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 527: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 528: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 529: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 530: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 531: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 532: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 533: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 534: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 535: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 536: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 537: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 538: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 539: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 540: _t->saveObject(); break;
        case 541: _t->clearObject(); break;
        case 542: _t->clearObjectAll(); break;
        case 543: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 544: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 545: _t->undoObject(); break;
        case 546: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 547: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 548: _t->clearFlagStop(); break;
        case 549: _t->slam_fullautoInit(); break;
        case 550: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 551: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 552: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 553: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 554: _t->clear_call(); break;
        case 555: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 556: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 557: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 558: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 559: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 560: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 561: _t->usbsave(); break;
        case 562: _t->restartUpdate(); break;
        case 563: _t->startUpdate(); break;
        case 564: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 565: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 566: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 567: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 568: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
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
        if (_id < 569)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 569;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 569)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 569;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
