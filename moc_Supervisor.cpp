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
    QByteArrayData data[677];
    char stringdata0[9017];
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
QT_MOC_LITERAL(7, 73, 13), // "git_pull_fail"
QT_MOC_LITERAL(8, 87, 6), // "reason"
QT_MOC_LITERAL(9, 94, 16), // "git_pull_success"
QT_MOC_LITERAL(10, 111, 8), // "new_call"
QT_MOC_LITERAL(11, 120, 14), // "process_accept"
QT_MOC_LITERAL(12, 135, 3), // "cmd"
QT_MOC_LITERAL(13, 139, 12), // "process_done"
QT_MOC_LITERAL(14, 152, 13), // "process_error"
QT_MOC_LITERAL(15, 166, 5), // "param"
QT_MOC_LITERAL(16, 172, 15), // "process_timeout"
QT_MOC_LITERAL(17, 188, 14), // "update_success"
QT_MOC_LITERAL(18, 203, 11), // "update_fail"
QT_MOC_LITERAL(19, 215, 9), // "clear_all"
QT_MOC_LITERAL(20, 225, 9), // "map_reset"
QT_MOC_LITERAL(21, 235, 14), // "new_call_order"
QT_MOC_LITERAL(22, 250, 4), // "name"
QT_MOC_LITERAL(23, 255, 10), // "play_voice"
QT_MOC_LITERAL(24, 266, 8), // "ST_VOICE"
QT_MOC_LITERAL(25, 275, 5), // "voice"
QT_MOC_LITERAL(26, 281, 17), // "emo_state_changed"
QT_MOC_LITERAL(27, 299, 17), // "connect_wifi_fail"
QT_MOC_LITERAL(28, 317, 4), // "ssid"
QT_MOC_LITERAL(29, 322, 20), // "connect_wifi_success"
QT_MOC_LITERAL(30, 343, 16), // "set_wifi_success"
QT_MOC_LITERAL(31, 360, 13), // "set_wifi_fail"
QT_MOC_LITERAL(32, 374, 14), // "setCurrentPage"
QT_MOC_LITERAL(33, 389, 4), // "page"
QT_MOC_LITERAL(34, 394, 13), // "loadMapServer"
QT_MOC_LITERAL(35, 408, 13), // "sendMapServer"
QT_MOC_LITERAL(36, 422, 17), // "checkLocationName"
QT_MOC_LITERAL(37, 440, 5), // "group"
QT_MOC_LITERAL(38, 446, 10), // "resetClear"
QT_MOC_LITERAL(39, 457, 10), // "getWifiNum"
QT_MOC_LITERAL(40, 468, 17), // "getWifiConnection"
QT_MOC_LITERAL(41, 486, 21), // "getEthernetConnection"
QT_MOC_LITERAL(42, 508, 21), // "getInternetConnection"
QT_MOC_LITERAL(43, 530, 14), // "getCurWifiSSID"
QT_MOC_LITERAL(44, 545, 11), // "getWifiSSID"
QT_MOC_LITERAL(45, 557, 3), // "num"
QT_MOC_LITERAL(46, 561, 11), // "connectWifi"
QT_MOC_LITERAL(47, 573, 6), // "passwd"
QT_MOC_LITERAL(48, 580, 15), // "getWifiSecurity"
QT_MOC_LITERAL(49, 596, 12), // "getWifiLevel"
QT_MOC_LITERAL(50, 609, 11), // "getWifiRate"
QT_MOC_LITERAL(51, 621, 12), // "getWifiInuse"
QT_MOC_LITERAL(52, 634, 14), // "getAllWifiList"
QT_MOC_LITERAL(53, 649, 9), // "getWifiIP"
QT_MOC_LITERAL(54, 659, 11), // "setWifiDHCP"
QT_MOC_LITERAL(55, 671, 7), // "setWifi"
QT_MOC_LITERAL(56, 679, 2), // "ip"
QT_MOC_LITERAL(57, 682, 7), // "gateway"
QT_MOC_LITERAL(58, 690, 3), // "dns"
QT_MOC_LITERAL(59, 694, 6), // "subnet"
QT_MOC_LITERAL(60, 701, 4), // "dns1"
QT_MOC_LITERAL(61, 706, 4), // "dns2"
QT_MOC_LITERAL(62, 711, 11), // "setEthernet"
QT_MOC_LITERAL(63, 723, 8), // "getcurIP"
QT_MOC_LITERAL(64, 732, 13), // "getcurGateway"
QT_MOC_LITERAL(65, 746, 13), // "getcurNetmask"
QT_MOC_LITERAL(66, 760, 10), // "getcurDNS2"
QT_MOC_LITERAL(67, 771, 9), // "getcurDNS"
QT_MOC_LITERAL(68, 781, 13), // "getethernetIP"
QT_MOC_LITERAL(69, 795, 18), // "getethernetGateway"
QT_MOC_LITERAL(70, 814, 18), // "getethernetNetmask"
QT_MOC_LITERAL(71, 833, 15), // "getethernetDNS2"
QT_MOC_LITERAL(72, 849, 14), // "getethernetDNS"
QT_MOC_LITERAL(73, 864, 14), // "getcurIPMethod"
QT_MOC_LITERAL(74, 879, 13), // "readWifiState"
QT_MOC_LITERAL(75, 893, 15), // "getSystemVolume"
QT_MOC_LITERAL(76, 909, 8), // "passInit"
QT_MOC_LITERAL(77, 918, 11), // "isDebugMode"
QT_MOC_LITERAL(78, 930, 11), // "loopClosing"
QT_MOC_LITERAL(79, 942, 10), // "readPatrol"
QT_MOC_LITERAL(80, 953, 13), // "getPatrolSize"
QT_MOC_LITERAL(81, 967, 21), // "getPatrolVoiceNameNum"
QT_MOC_LITERAL(82, 989, 13), // "getPatrolName"
QT_MOC_LITERAL(83, 1003, 13), // "getPatrolType"
QT_MOC_LITERAL(84, 1017, 17), // "getPatrolLocation"
QT_MOC_LITERAL(85, 1035, 19), // "getPatrolMovingPage"
QT_MOC_LITERAL(86, 1055, 19), // "getPatrolArrivePage"
QT_MOC_LITERAL(87, 1075, 17), // "getPatrolWaitTime"
QT_MOC_LITERAL(88, 1093, 17), // "getPatrolPassTime"
QT_MOC_LITERAL(89, 1111, 14), // "getPatrolVoice"
QT_MOC_LITERAL(90, 1126, 18), // "getPatrolVoiceMode"
QT_MOC_LITERAL(91, 1145, 21), // "getPatrolVoiceMention"
QT_MOC_LITERAL(92, 1167, 22), // "getPatrolVoiceLanguage"
QT_MOC_LITERAL(93, 1190, 12), // "isPatrolPage"
QT_MOC_LITERAL(94, 1203, 19), // "getPatrolMovingMode"
QT_MOC_LITERAL(95, 1223, 19), // "getPatrolArriveMode"
QT_MOC_LITERAL(96, 1243, 16), // "setCurrentPatrol"
QT_MOC_LITERAL(97, 1260, 21), // "getPatrolLocationSize"
QT_MOC_LITERAL(98, 1282, 3), // "loc"
QT_MOC_LITERAL(99, 1286, 19), // "clearPatrolLocation"
QT_MOC_LITERAL(100, 1306, 4), // "mode"
QT_MOC_LITERAL(101, 1311, 17), // "addPatrolLocation"
QT_MOC_LITERAL(102, 1329, 19), // "setPatrolMovingPage"
QT_MOC_LITERAL(103, 1349, 6), // "param1"
QT_MOC_LITERAL(104, 1356, 6), // "param2"
QT_MOC_LITERAL(105, 1363, 6), // "param3"
QT_MOC_LITERAL(106, 1370, 19), // "setPatrolArrivePage"
QT_MOC_LITERAL(107, 1390, 20), // "savePatrolVoiceBasic"
QT_MOC_LITERAL(108, 1411, 4), // "text"
QT_MOC_LITERAL(109, 1416, 14), // "setPatrolVoice"
QT_MOC_LITERAL(110, 1431, 8), // "language"
QT_MOC_LITERAL(111, 1440, 6), // "volume"
QT_MOC_LITERAL(112, 1447, 7), // "mention"
QT_MOC_LITERAL(113, 1455, 9), // "setPatrol"
QT_MOC_LITERAL(114, 1465, 4), // "type"
QT_MOC_LITERAL(115, 1470, 9), // "wait_time"
QT_MOC_LITERAL(116, 1480, 9), // "pass_time"
QT_MOC_LITERAL(117, 1490, 10), // "savePatrol"
QT_MOC_LITERAL(118, 1501, 12), // "deletePatrol"
QT_MOC_LITERAL(119, 1514, 11), // "startPatrol"
QT_MOC_LITERAL(120, 1526, 10), // "makeTTSAll"
QT_MOC_LITERAL(121, 1537, 10), // "setTTSMode"
QT_MOC_LITERAL(122, 1548, 11), // "setTTSVoice"
QT_MOC_LITERAL(123, 1560, 3), // "lan"
QT_MOC_LITERAL(124, 1564, 17), // "setTTSVoiceDetail"
QT_MOC_LITERAL(125, 1582, 5), // "speed"
QT_MOC_LITERAL(126, 1588, 5), // "pitch"
QT_MOC_LITERAL(127, 1594, 5), // "alpha"
QT_MOC_LITERAL(128, 1600, 7), // "emotion"
QT_MOC_LITERAL(129, 1608, 8), // "emostren"
QT_MOC_LITERAL(130, 1617, 13), // "clearTTSVoice"
QT_MOC_LITERAL(131, 1631, 12), // "saveTTSVoice"
QT_MOC_LITERAL(132, 1644, 13), // "makePatrolTTS"
QT_MOC_LITERAL(133, 1658, 4), // "play"
QT_MOC_LITERAL(134, 1663, 13), // "getTTSNameNum"
QT_MOC_LITERAL(135, 1677, 17), // "getTTSLanguageNum"
QT_MOC_LITERAL(136, 1695, 8), // "loadFile"
QT_MOC_LITERAL(137, 1704, 6), // "setMap"
QT_MOC_LITERAL(138, 1711, 13), // "setFullScreen"
QT_MOC_LITERAL(139, 1725, 13), // "setMapDrawing"
QT_MOC_LITERAL(140, 1739, 7), // "playBGM"
QT_MOC_LITERAL(141, 1747, 7), // "stopBGM"
QT_MOC_LITERAL(142, 1755, 9), // "isplayBGM"
QT_MOC_LITERAL(143, 1765, 12), // "setvolumeBGM"
QT_MOC_LITERAL(144, 1778, 11), // "getTTSSpeed"
QT_MOC_LITERAL(145, 1790, 11), // "getTTSPitch"
QT_MOC_LITERAL(146, 1802, 13), // "getTTSEmotion"
QT_MOC_LITERAL(147, 1816, 21), // "getTTSEmotionStrength"
QT_MOC_LITERAL(148, 1838, 11), // "getTTSAlpha"
QT_MOC_LITERAL(149, 1850, 12), // "getTTSVolume"
QT_MOC_LITERAL(150, 1863, 13), // "getTTSMention"
QT_MOC_LITERAL(151, 1877, 18), // "setTTSMentionBasic"
QT_MOC_LITERAL(152, 1896, 13), // "setTTSMention"
QT_MOC_LITERAL(153, 1910, 9), // "playVoice"
QT_MOC_LITERAL(154, 1920, 4), // "file"
QT_MOC_LITERAL(155, 1925, 11), // "getTTSVoice"
QT_MOC_LITERAL(156, 1937, 7), // "playTTS"
QT_MOC_LITERAL(157, 1945, 24), // "setServingPageBackground"
QT_MOC_LITERAL(158, 1970, 24), // "getServingPageBackground"
QT_MOC_LITERAL(159, 1995, 18), // "setServingPageMode"
QT_MOC_LITERAL(160, 2014, 18), // "getServingPageMode"
QT_MOC_LITERAL(161, 2033, 19), // "setServingPageColor"
QT_MOC_LITERAL(162, 2053, 19), // "getServingPageColor"
QT_MOC_LITERAL(163, 2073, 19), // "setServingPageImage"
QT_MOC_LITERAL(164, 2093, 19), // "getServingPageImage"
QT_MOC_LITERAL(165, 2113, 19), // "setServingPageVideo"
QT_MOC_LITERAL(166, 2133, 19), // "getServingPageVideo"
QT_MOC_LITERAL(167, 2153, 24), // "setServingPageVideoAudio"
QT_MOC_LITERAL(168, 2178, 24), // "getServingPageVideoAudio"
QT_MOC_LITERAL(169, 2203, 19), // "setServingPageAudio"
QT_MOC_LITERAL(170, 2223, 19), // "getServingPageAudio"
QT_MOC_LITERAL(171, 2243, 23), // "setMovingPageBackground"
QT_MOC_LITERAL(172, 2267, 23), // "getMovingPageBackground"
QT_MOC_LITERAL(173, 2291, 17), // "setMovingPageMode"
QT_MOC_LITERAL(174, 2309, 17), // "getMovingPageMode"
QT_MOC_LITERAL(175, 2327, 18), // "setMovingPageColor"
QT_MOC_LITERAL(176, 2346, 18), // "getMovingPageColor"
QT_MOC_LITERAL(177, 2365, 18), // "setMovingPageImage"
QT_MOC_LITERAL(178, 2384, 18), // "getMovingPageImage"
QT_MOC_LITERAL(179, 2403, 18), // "setMovingPageVideo"
QT_MOC_LITERAL(180, 2422, 18), // "getMovingPageVideo"
QT_MOC_LITERAL(181, 2441, 23), // "setMovingPageVideoAudio"
QT_MOC_LITERAL(182, 2465, 23), // "getMovingPageVideoAudio"
QT_MOC_LITERAL(183, 2489, 18), // "setMovingPageAudio"
QT_MOC_LITERAL(184, 2508, 18), // "getMovingPageAudio"
QT_MOC_LITERAL(185, 2527, 15), // "clearPatrolPage"
QT_MOC_LITERAL(186, 2543, 16), // "clearServingPage"
QT_MOC_LITERAL(187, 2560, 15), // "initServingPage"
QT_MOC_LITERAL(188, 2576, 15), // "saveServingPage"
QT_MOC_LITERAL(189, 2592, 20), // "getServingObjectSize"
QT_MOC_LITERAL(190, 2613, 20), // "getServingObjectType"
QT_MOC_LITERAL(191, 2634, 22), // "getServingObjectSource"
QT_MOC_LITERAL(192, 2657, 21), // "getServingObjectColor"
QT_MOC_LITERAL(193, 2679, 17), // "getServingObjectX"
QT_MOC_LITERAL(194, 2697, 17), // "getServingObjectY"
QT_MOC_LITERAL(195, 2715, 21), // "getServingObjectWidth"
QT_MOC_LITERAL(196, 2737, 22), // "getServingObjectHeight"
QT_MOC_LITERAL(197, 2760, 24), // "getServingObjectFontsize"
QT_MOC_LITERAL(198, 2785, 16), // "addServingObject"
QT_MOC_LITERAL(199, 2802, 3), // "obj"
QT_MOC_LITERAL(200, 2806, 22), // "setServingObjectSource"
QT_MOC_LITERAL(201, 2829, 3), // "src"
QT_MOC_LITERAL(202, 2833, 21), // "setServingObjectColor"
QT_MOC_LITERAL(203, 2855, 5), // "color"
QT_MOC_LITERAL(204, 2861, 19), // "deleteServingObject"
QT_MOC_LITERAL(205, 2881, 17), // "moveServingObject"
QT_MOC_LITERAL(206, 2899, 1), // "x"
QT_MOC_LITERAL(207, 2901, 1), // "y"
QT_MOC_LITERAL(208, 2903, 20), // "setServingObjectSize"
QT_MOC_LITERAL(209, 2924, 5), // "point"
QT_MOC_LITERAL(210, 2930, 5), // "width"
QT_MOC_LITERAL(211, 2936, 6), // "height"
QT_MOC_LITERAL(212, 2943, 19), // "getServingObjectNum"
QT_MOC_LITERAL(213, 2963, 19), // "getPatrolObjectSize"
QT_MOC_LITERAL(214, 2983, 17), // "getPageObjectType"
QT_MOC_LITERAL(215, 3001, 19), // "getPageObjectSource"
QT_MOC_LITERAL(216, 3021, 18), // "getPageObjectColor"
QT_MOC_LITERAL(217, 3040, 14), // "getPageObjectX"
QT_MOC_LITERAL(218, 3055, 14), // "getPageObjectY"
QT_MOC_LITERAL(219, 3070, 18), // "getPageObjectWidth"
QT_MOC_LITERAL(220, 3089, 19), // "getPageObjectHeight"
QT_MOC_LITERAL(221, 3109, 21), // "getPageObjectFontsize"
QT_MOC_LITERAL(222, 3131, 15), // "addPatrolObject"
QT_MOC_LITERAL(223, 3147, 19), // "setPageObjectSource"
QT_MOC_LITERAL(224, 3167, 18), // "setPageObjectColor"
QT_MOC_LITERAL(225, 3186, 18), // "deletePatrolObject"
QT_MOC_LITERAL(226, 3205, 16), // "movePatrolObject"
QT_MOC_LITERAL(227, 3222, 19), // "setPatrolObjectSize"
QT_MOC_LITERAL(228, 3242, 16), // "getPageObjectNum"
QT_MOC_LITERAL(229, 3259, 11), // "isExistNode"
QT_MOC_LITERAL(230, 3271, 19), // "confirmLocalization"
QT_MOC_LITERAL(231, 3291, 7), // "setName"
QT_MOC_LITERAL(232, 3299, 7), // "setTool"
QT_MOC_LITERAL(233, 3307, 7), // "getTool"
QT_MOC_LITERAL(234, 3315, 7), // "setMode"
QT_MOC_LITERAL(235, 3323, 9), // "setEnable"
QT_MOC_LITERAL(236, 3333, 2), // "en"
QT_MOC_LITERAL(237, 3336, 7), // "getMode"
QT_MOC_LITERAL(238, 3344, 12), // "setShowBrush"
QT_MOC_LITERAL(239, 3357, 5), // "onoff"
QT_MOC_LITERAL(240, 3363, 12), // "setShowLidar"
QT_MOC_LITERAL(241, 3376, 15), // "setShowLocation"
QT_MOC_LITERAL(242, 3392, 17), // "setRobotFollowing"
QT_MOC_LITERAL(243, 3410, 17), // "setShowTravelline"
QT_MOC_LITERAL(244, 3428, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(245, 3447, 13), // "setShowObject"
QT_MOC_LITERAL(246, 3461, 11), // "setInitFlag"
QT_MOC_LITERAL(247, 3473, 15), // "getshowLocation"
QT_MOC_LITERAL(248, 3489, 17), // "getRobotFollowing"
QT_MOC_LITERAL(249, 3507, 12), // "getShowLidar"
QT_MOC_LITERAL(250, 3520, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(251, 3536, 11), // "setShowNode"
QT_MOC_LITERAL(252, 3548, 11), // "getShowNode"
QT_MOC_LITERAL(253, 3560, 11), // "setShowName"
QT_MOC_LITERAL(254, 3572, 11), // "getShowName"
QT_MOC_LITERAL(255, 3584, 12), // "setShowTline"
QT_MOC_LITERAL(256, 3597, 12), // "getShowTline"
QT_MOC_LITERAL(257, 3610, 13), // "setShowVelmap"
QT_MOC_LITERAL(258, 3624, 13), // "getShowVelmap"
QT_MOC_LITERAL(259, 3638, 12), // "setShowAvoid"
QT_MOC_LITERAL(260, 3651, 12), // "getShowAvoid"
QT_MOC_LITERAL(261, 3664, 9), // "autoTline"
QT_MOC_LITERAL(262, 3674, 13), // "getShowObject"
QT_MOC_LITERAL(263, 3688, 11), // "setShowEdge"
QT_MOC_LITERAL(264, 3700, 11), // "getShowEdge"
QT_MOC_LITERAL(265, 3712, 11), // "setInitPose"
QT_MOC_LITERAL(266, 3724, 2), // "th"
QT_MOC_LITERAL(267, 3727, 13), // "clearInitPose"
QT_MOC_LITERAL(268, 3741, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(269, 3762, 17), // "startDrawingTline"
QT_MOC_LITERAL(270, 3780, 16), // "stopDrawingTline"
QT_MOC_LITERAL(271, 3797, 15), // "getDrawingTline"
QT_MOC_LITERAL(272, 3813, 13), // "setRulerPoint"
QT_MOC_LITERAL(273, 3827, 11), // "setBoxPoint"
QT_MOC_LITERAL(274, 3839, 11), // "getPointBox"
QT_MOC_LITERAL(275, 3851, 13), // "saveRotateMap"
QT_MOC_LITERAL(276, 3865, 10), // "initRotate"
QT_MOC_LITERAL(277, 3876, 9), // "rotateMap"
QT_MOC_LITERAL(278, 3886, 5), // "angle"
QT_MOC_LITERAL(279, 3892, 11), // "rotateMapCW"
QT_MOC_LITERAL(280, 3904, 12), // "rotateMapCCW"
QT_MOC_LITERAL(281, 3917, 13), // "saveObjectPNG"
QT_MOC_LITERAL(282, 3931, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(283, 3946, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(284, 3969, 14), // "getDrawingFlag"
QT_MOC_LITERAL(285, 3984, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(286, 4003, 12), // "startDrawing"
QT_MOC_LITERAL(287, 4016, 12), // "addLinePoint"
QT_MOC_LITERAL(288, 4029, 10), // "endDrawing"
QT_MOC_LITERAL(289, 4040, 11), // "startErase2"
QT_MOC_LITERAL(290, 4052, 9), // "addErase2"
QT_MOC_LITERAL(291, 4062, 9), // "endErase2"
QT_MOC_LITERAL(292, 4072, 10), // "setMapOrin"
QT_MOC_LITERAL(293, 4083, 16), // "startDrawingRect"
QT_MOC_LITERAL(294, 4100, 14), // "setDrawingRect"
QT_MOC_LITERAL(295, 4115, 14), // "endDrawingRect"
QT_MOC_LITERAL(296, 4130, 12), // "clearDrawing"
QT_MOC_LITERAL(297, 4143, 8), // "undoLine"
QT_MOC_LITERAL(298, 4152, 8), // "redoLine"
QT_MOC_LITERAL(299, 4161, 11), // "startSpline"
QT_MOC_LITERAL(300, 4173, 9), // "addSpline"
QT_MOC_LITERAL(301, 4183, 10), // "drawSpline"
QT_MOC_LITERAL(302, 4194, 9), // "endSpline"
QT_MOC_LITERAL(303, 4204, 4), // "save"
QT_MOC_LITERAL(304, 4209, 16), // "startDrawingLine"
QT_MOC_LITERAL(305, 4226, 14), // "setDrawingLine"
QT_MOC_LITERAL(306, 4241, 15), // "stopDrawingLine"
QT_MOC_LITERAL(307, 4257, 12), // "setLineColor"
QT_MOC_LITERAL(308, 4270, 12), // "setLineWidth"
QT_MOC_LITERAL(309, 4283, 7), // "pressed"
QT_MOC_LITERAL(310, 4291, 4), // "tool"
QT_MOC_LITERAL(311, 4296, 14), // "double_pressed"
QT_MOC_LITERAL(312, 4311, 2), // "x1"
QT_MOC_LITERAL(313, 4314, 2), // "y1"
QT_MOC_LITERAL(314, 4317, 2), // "x2"
QT_MOC_LITERAL(315, 4320, 2), // "y2"
QT_MOC_LITERAL(316, 4323, 5), // "moved"
QT_MOC_LITERAL(317, 4329, 12), // "double_moved"
QT_MOC_LITERAL(318, 4342, 8), // "released"
QT_MOC_LITERAL(319, 4351, 15), // "double_released"
QT_MOC_LITERAL(320, 4367, 14), // "getLocationNum"
QT_MOC_LITERAL(321, 4382, 12), // "saveLocation"
QT_MOC_LITERAL(322, 4395, 8), // "groupnum"
QT_MOC_LITERAL(323, 4404, 13), // "clearLocation"
QT_MOC_LITERAL(324, 4418, 11), // "addLocation"
QT_MOC_LITERAL(325, 4430, 14), // "addLocationCur"
QT_MOC_LITERAL(326, 4445, 11), // "setLocation"
QT_MOC_LITERAL(327, 4457, 12), // "editLocation"
QT_MOC_LITERAL(328, 4470, 14), // "removeLocation"
QT_MOC_LITERAL(329, 4485, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(330, 4504, 14), // "getLocGroupNum"
QT_MOC_LITERAL(331, 4519, 7), // "saveMap"
QT_MOC_LITERAL(332, 4527, 13), // "saveEditedMap"
QT_MOC_LITERAL(333, 4541, 9), // "saveTline"
QT_MOC_LITERAL(334, 4551, 13), // "saveTlineTemp"
QT_MOC_LITERAL(335, 4565, 10), // "saveVelmap"
QT_MOC_LITERAL(336, 4576, 10), // "setMapSize"
QT_MOC_LITERAL(337, 4587, 14), // "loadAnnotation"
QT_MOC_LITERAL(338, 4602, 7), // "addNode"
QT_MOC_LITERAL(339, 4610, 2), // "id"
QT_MOC_LITERAL(340, 4613, 4), // "attr"
QT_MOC_LITERAL(341, 4618, 8), // "editNode"
QT_MOC_LITERAL(342, 4627, 10), // "deleteNode"
QT_MOC_LITERAL(343, 4638, 8), // "linkNode"
QT_MOC_LITERAL(344, 4647, 9), // "alignNode"
QT_MOC_LITERAL(345, 4657, 1), // "n"
QT_MOC_LITERAL(346, 4659, 12), // "releaseShift"
QT_MOC_LITERAL(347, 4672, 10), // "pressShift"
QT_MOC_LITERAL(348, 4683, 6), // "zoomIn"
QT_MOC_LITERAL(349, 4690, 4), // "dist"
QT_MOC_LITERAL(350, 4695, 7), // "zoomOut"
QT_MOC_LITERAL(351, 4703, 4), // "move"
QT_MOC_LITERAL(352, 4708, 12), // "getFileWidth"
QT_MOC_LITERAL(353, 4721, 4), // "getX"
QT_MOC_LITERAL(354, 4726, 4), // "getY"
QT_MOC_LITERAL(355, 4731, 8), // "getScale"
QT_MOC_LITERAL(356, 4740, 13), // "setVelmapView"
QT_MOC_LITERAL(357, 4754, 12), // "setTlineView"
QT_MOC_LITERAL(358, 4767, 13), // "setObjectView"
QT_MOC_LITERAL(359, 4781, 15), // "setAvoidmapView"
QT_MOC_LITERAL(360, 4797, 15), // "setLocationView"
QT_MOC_LITERAL(361, 4813, 12), // "setRobotView"
QT_MOC_LITERAL(362, 4826, 15), // "setSystemVolume"
QT_MOC_LITERAL(363, 4842, 19), // "requestSystemVolume"
QT_MOC_LITERAL(364, 4862, 7), // "setSize"
QT_MOC_LITERAL(365, 4870, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(366, 4884, 14), // "selectLocation"
QT_MOC_LITERAL(367, 4899, 8), // "writelog"
QT_MOC_LITERAL(368, 4908, 3), // "msg"
QT_MOC_LITERAL(369, 4912, 18), // "startDrawingObject"
QT_MOC_LITERAL(370, 4931, 17), // "stopDrawingObject"
QT_MOC_LITERAL(371, 4949, 17), // "saveDrawingObject"
QT_MOC_LITERAL(372, 4967, 13), // "setLocationUp"
QT_MOC_LITERAL(373, 4981, 15), // "setLocationDown"
QT_MOC_LITERAL(374, 4997, 8), // "checkINI"
QT_MOC_LITERAL(375, 5006, 8), // "killSLAM"
QT_MOC_LITERAL(376, 5015, 12), // "makeRobotINI"
QT_MOC_LITERAL(377, 5028, 13), // "checkRobotINI"
QT_MOC_LITERAL(378, 5042, 11), // "restartSLAM"
QT_MOC_LITERAL(379, 5054, 9), // "startSLAM"
QT_MOC_LITERAL(380, 5064, 16), // "getIPCConnection"
QT_MOC_LITERAL(381, 5081, 8), // "getIPCRX"
QT_MOC_LITERAL(382, 5090, 8), // "getIPCTX"
QT_MOC_LITERAL(383, 5099, 14), // "programRestart"
QT_MOC_LITERAL(384, 5114, 11), // "programExit"
QT_MOC_LITERAL(385, 5126, 13), // "getRawMapPath"
QT_MOC_LITERAL(386, 5140, 10), // "getMapPath"
QT_MOC_LITERAL(387, 5151, 12), // "getAnnotPath"
QT_MOC_LITERAL(388, 5164, 11), // "getMetaPath"
QT_MOC_LITERAL(389, 5176, 13), // "getTravelPath"
QT_MOC_LITERAL(390, 5190, 11), // "getCostPath"
QT_MOC_LITERAL(391, 5202, 10), // "getIniPath"
QT_MOC_LITERAL(392, 5213, 10), // "setSetting"
QT_MOC_LITERAL(393, 5224, 5), // "value"
QT_MOC_LITERAL(394, 5230, 11), // "readSetting"
QT_MOC_LITERAL(395, 5242, 8), // "map_name"
QT_MOC_LITERAL(396, 5251, 10), // "getSetting"
QT_MOC_LITERAL(397, 5262, 10), // "getTrayNum"
QT_MOC_LITERAL(398, 5273, 14), // "setTableColNum"
QT_MOC_LITERAL(399, 5288, 7), // "col_num"
QT_MOC_LITERAL(400, 5296, 12), // "getRobotType"
QT_MOC_LITERAL(401, 5309, 13), // "requestCamera"
QT_MOC_LITERAL(402, 5323, 13), // "getLeftCamera"
QT_MOC_LITERAL(403, 5337, 14), // "getRightCamera"
QT_MOC_LITERAL(404, 5352, 9), // "setCamera"
QT_MOC_LITERAL(405, 5362, 4), // "left"
QT_MOC_LITERAL(406, 5367, 5), // "right"
QT_MOC_LITERAL(407, 5373, 12), // "getCameraNum"
QT_MOC_LITERAL(408, 5386, 15), // "getCameraSerial"
QT_MOC_LITERAL(409, 5402, 13), // "setCursorView"
QT_MOC_LITERAL(410, 5416, 7), // "visible"
QT_MOC_LITERAL(411, 5424, 15), // "checkTravelline"
QT_MOC_LITERAL(412, 5440, 17), // "getNewServingName"
QT_MOC_LITERAL(413, 5458, 15), // "isDuplicateName"
QT_MOC_LITERAL(414, 5474, 13), // "updateProgram"
QT_MOC_LITERAL(415, 5488, 8), // "gitReset"
QT_MOC_LITERAL(416, 5497, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(417, 5518, 17), // "checkVersionAgain"
QT_MOC_LITERAL(418, 5536, 12), // "isNewVersion"
QT_MOC_LITERAL(419, 5549, 12), // "isNeedUpdate"
QT_MOC_LITERAL(420, 5562, 15), // "getLocalVersion"
QT_MOC_LITERAL(421, 5578, 16), // "getServerVersion"
QT_MOC_LITERAL(422, 5595, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(423, 5615, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(424, 5638, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(425, 5662, 13), // "getUpdateDate"
QT_MOC_LITERAL(426, 5676, 13), // "getUpdateSize"
QT_MOC_LITERAL(427, 5690, 17), // "getUpdateFileName"
QT_MOC_LITERAL(428, 5708, 15), // "getUpdateCommit"
QT_MOC_LITERAL(429, 5724, 16), // "getCurrentCommit"
QT_MOC_LITERAL(430, 5741, 16), // "getUpdateMessage"
QT_MOC_LITERAL(431, 5758, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(432, 5776, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(433, 5798, 12), // "isRobotReady"
QT_MOC_LITERAL(434, 5811, 11), // "checkUpdate"
QT_MOC_LITERAL(435, 5823, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(436, 5845, 11), // "setlanguage"
QT_MOC_LITERAL(437, 5857, 13), // "isCallingMode"
QT_MOC_LITERAL(438, 5871, 12), // "startServing"
QT_MOC_LITERAL(439, 5884, 5), // "table"
QT_MOC_LITERAL(440, 5890, 11), // "getLocation"
QT_MOC_LITERAL(441, 5902, 8), // "LOCATION"
QT_MOC_LITERAL(442, 5911, 10), // "setUiState"
QT_MOC_LITERAL(443, 5922, 5), // "state"
QT_MOC_LITERAL(444, 5928, 11), // "clearStatus"
QT_MOC_LITERAL(445, 5940, 9), // "stateInit"
QT_MOC_LITERAL(446, 5950, 11), // "stateMoving"
QT_MOC_LITERAL(447, 5962, 17), // "resetLocalization"
QT_MOC_LITERAL(448, 5980, 6), // "setLog"
QT_MOC_LITERAL(449, 5987, 13), // "getLogLineNum"
QT_MOC_LITERAL(450, 6001, 10), // "getLogLine"
QT_MOC_LITERAL(451, 6012, 10), // "getLogDate"
QT_MOC_LITERAL(452, 6023, 10), // "getLogAuth"
QT_MOC_LITERAL(453, 6034, 13), // "getLogMessage"
QT_MOC_LITERAL(454, 6048, 7), // "readLog"
QT_MOC_LITERAL(455, 6056, 4), // "date"
QT_MOC_LITERAL(456, 6061, 13), // "getLocaleDate"
QT_MOC_LITERAL(457, 6075, 4), // "year"
QT_MOC_LITERAL(458, 6080, 5), // "month"
QT_MOC_LITERAL(459, 6086, 9), // "updateUSB"
QT_MOC_LITERAL(460, 6096, 10), // "getusbsize"
QT_MOC_LITERAL(461, 6107, 17), // "readusbrecentfile"
QT_MOC_LITERAL(462, 6125, 14), // "getusbfilesize"
QT_MOC_LITERAL(463, 6140, 10), // "getusbfile"
QT_MOC_LITERAL(464, 6151, 16), // "getusbrecentfile"
QT_MOC_LITERAL(465, 6168, 10), // "getusbname"
QT_MOC_LITERAL(466, 6179, 7), // "readusb"
QT_MOC_LITERAL(467, 6187, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(468, 6202, 4), // "path"
QT_MOC_LITERAL(469, 6207, 15), // "isConnectServer"
QT_MOC_LITERAL(470, 6223, 9), // "isLoadMap"
QT_MOC_LITERAL(471, 6233, 10), // "isExistMap"
QT_MOC_LITERAL(472, 6244, 13), // "isExistRawMap"
QT_MOC_LITERAL(473, 6258, 15), // "isExistTlineMap"
QT_MOC_LITERAL(474, 6274, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(475, 6290, 13), // "isExistVelMap"
QT_MOC_LITERAL(476, 6304, 16), // "isExistObjectMap"
QT_MOC_LITERAL(477, 6321, 16), // "isExistTravelMap"
QT_MOC_LITERAL(478, 6338, 17), // "isExistAnnotation"
QT_MOC_LITERAL(479, 6356, 15), // "isExistRobotINI"
QT_MOC_LITERAL(480, 6372, 15), // "getAvailableMap"
QT_MOC_LITERAL(481, 6388, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(482, 6408, 14), // "getMapFileSize"
QT_MOC_LITERAL(483, 6423, 10), // "getMapFile"
QT_MOC_LITERAL(484, 6434, 15), // "deleteEditedMap"
QT_MOC_LITERAL(485, 6450, 16), // "deleteAnnotation"
QT_MOC_LITERAL(486, 6467, 9), // "removeMap"
QT_MOC_LITERAL(487, 6477, 8), // "filename"
QT_MOC_LITERAL(488, 6486, 7), // "loadMap"
QT_MOC_LITERAL(489, 6494, 7), // "copyMap"
QT_MOC_LITERAL(490, 6502, 8), // "orinname"
QT_MOC_LITERAL(491, 6511, 7), // "newname"
QT_MOC_LITERAL(492, 6519, 10), // "rotate_map"
QT_MOC_LITERAL(493, 6530, 4), // "_src"
QT_MOC_LITERAL(494, 6535, 4), // "_dst"
QT_MOC_LITERAL(495, 6540, 12), // "startMapping"
QT_MOC_LITERAL(496, 6553, 7), // "mapsize"
QT_MOC_LITERAL(497, 6561, 4), // "grid"
QT_MOC_LITERAL(498, 6566, 11), // "stopMapping"
QT_MOC_LITERAL(499, 6578, 11), // "setSLAMMode"
QT_MOC_LITERAL(500, 6590, 11), // "saveMapping"
QT_MOC_LITERAL(501, 6602, 13), // "setInitCurPos"
QT_MOC_LITERAL(502, 6616, 10), // "setInitPos"
QT_MOC_LITERAL(503, 6627, 12), // "getInitPoseX"
QT_MOC_LITERAL(504, 6640, 12), // "getInitPoseY"
QT_MOC_LITERAL(505, 6653, 13), // "getInitPoseTH"
QT_MOC_LITERAL(506, 6667, 12), // "slam_setInit"
QT_MOC_LITERAL(507, 6680, 8), // "slam_run"
QT_MOC_LITERAL(508, 6689, 9), // "slam_stop"
QT_MOC_LITERAL(509, 6699, 13), // "slam_autoInit"
QT_MOC_LITERAL(510, 6713, 13), // "slam_restInit"
QT_MOC_LITERAL(511, 6727, 15), // "is_slam_running"
QT_MOC_LITERAL(512, 6743, 14), // "getMappingflag"
QT_MOC_LITERAL(513, 6758, 16), // "getObjectingflag"
QT_MOC_LITERAL(514, 6775, 16), // "setObjectingflag"
QT_MOC_LITERAL(515, 6792, 4), // "flag"
QT_MOC_LITERAL(516, 6797, 13), // "getnewMapname"
QT_MOC_LITERAL(517, 6811, 11), // "getLastCall"
QT_MOC_LITERAL(518, 6823, 11), // "getCallSize"
QT_MOC_LITERAL(519, 6835, 16), // "getCallQueueSize"
QT_MOC_LITERAL(520, 6852, 9), // "cleanTray"
QT_MOC_LITERAL(521, 6862, 11), // "getCallName"
QT_MOC_LITERAL(522, 6874, 14), // "clearCallQueue"
QT_MOC_LITERAL(523, 6889, 7), // "getCall"
QT_MOC_LITERAL(524, 6897, 11), // "setCallbell"
QT_MOC_LITERAL(525, 6909, 16), // "setCallbellForce"
QT_MOC_LITERAL(526, 6926, 10), // "setObjPose"
QT_MOC_LITERAL(527, 6937, 14), // "getServingName"
QT_MOC_LITERAL(528, 6952, 15), // "getLocationName"
QT_MOC_LITERAL(529, 6968, 15), // "getLocationType"
QT_MOC_LITERAL(530, 6984, 17), // "getLocationNumber"
QT_MOC_LITERAL(531, 7002, 17), // "setLocationNumber"
QT_MOC_LITERAL(532, 7020, 15), // "getLocationSize"
QT_MOC_LITERAL(533, 7036, 16), // "getLocationGroup"
QT_MOC_LITERAL(534, 7053, 13), // "getLocationID"
QT_MOC_LITERAL(535, 7067, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(536, 7087, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(537, 7108, 17), // "getLocationCallID"
QT_MOC_LITERAL(538, 7126, 16), // "setLocationGroup"
QT_MOC_LITERAL(539, 7143, 19), // "removeLocationGroup"
QT_MOC_LITERAL(540, 7163, 16), // "addLocationGroup"
QT_MOC_LITERAL(541, 7180, 15), // "getLocGroupname"
QT_MOC_LITERAL(542, 7196, 8), // "tablenum"
QT_MOC_LITERAL(543, 7205, 12), // "getLocationX"
QT_MOC_LITERAL(544, 7218, 12), // "getLocationY"
QT_MOC_LITERAL(545, 7231, 13), // "getLocationTH"
QT_MOC_LITERAL(546, 7245, 15), // "isExistLocation"
QT_MOC_LITERAL(547, 7261, 8), // "getLidar"
QT_MOC_LITERAL(548, 7270, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(549, 7287, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(550, 7304, 17), // "clearSharedMemory"
QT_MOC_LITERAL(551, 7322, 12), // "getObjectNum"
QT_MOC_LITERAL(552, 7335, 13), // "getObjectName"
QT_MOC_LITERAL(553, 7349, 18), // "getObjectPointSize"
QT_MOC_LITERAL(554, 7368, 10), // "getObjectX"
QT_MOC_LITERAL(555, 7379, 10), // "getObjectY"
QT_MOC_LITERAL(556, 7390, 14), // "getObjPointNum"
QT_MOC_LITERAL(557, 7405, 7), // "obj_num"
QT_MOC_LITERAL(558, 7413, 9), // "getLocNum"
QT_MOC_LITERAL(559, 7423, 13), // "saveLocations"
QT_MOC_LITERAL(560, 7437, 13), // "getObjectSize"
QT_MOC_LITERAL(561, 7451, 12), // "removeObject"
QT_MOC_LITERAL(562, 7464, 14), // "saveAnnotation"
QT_MOC_LITERAL(563, 7479, 6), // "reload"
QT_MOC_LITERAL(564, 7486, 8), // "saveNode"
QT_MOC_LITERAL(565, 7495, 8), // "isOdroid"
QT_MOC_LITERAL(566, 7504, 13), // "getMultiState"
QT_MOC_LITERAL(567, 7518, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(568, 7538, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(569, 7557, 15), // "getRunawayState"
QT_MOC_LITERAL(570, 7573, 15), // "slam_map_reload"
QT_MOC_LITERAL(571, 7589, 15), // "slam_ini_reload"
QT_MOC_LITERAL(572, 7605, 7), // "setTray"
QT_MOC_LITERAL(573, 7613, 8), // "tray_num"
QT_MOC_LITERAL(574, 7622, 9), // "setPreset"
QT_MOC_LITERAL(575, 7632, 6), // "preset"
QT_MOC_LITERAL(576, 7639, 13), // "confirmPickup"
QT_MOC_LITERAL(577, 7653, 14), // "getPickuptrays"
QT_MOC_LITERAL(578, 7668, 10), // "QList<int>"
QT_MOC_LITERAL(579, 7679, 9), // "movePause"
QT_MOC_LITERAL(580, 7689, 10), // "moveResume"
QT_MOC_LITERAL(581, 7700, 12), // "moveStopFlag"
QT_MOC_LITERAL(582, 7713, 8), // "moveStop"
QT_MOC_LITERAL(583, 7722, 12), // "moveToCharge"
QT_MOC_LITERAL(584, 7735, 10), // "moveToWait"
QT_MOC_LITERAL(585, 7746, 14), // "moveToCleaning"
QT_MOC_LITERAL(586, 7761, 9), // "getcurLoc"
QT_MOC_LITERAL(587, 7771, 11), // "getcurTable"
QT_MOC_LITERAL(588, 7783, 16), // "resetHomeFolders"
QT_MOC_LITERAL(589, 7800, 13), // "issetLocation"
QT_MOC_LITERAL(590, 7814, 6), // "number"
QT_MOC_LITERAL(591, 7821, 11), // "getObsState"
QT_MOC_LITERAL(592, 7833, 10), // "getBattery"
QT_MOC_LITERAL(593, 7844, 13), // "getMotorState"
QT_MOC_LITERAL(594, 7858, 20), // "getLocalizationState"
QT_MOC_LITERAL(595, 7879, 14), // "getStateMoving"
QT_MOC_LITERAL(596, 7894, 10), // "getErrcode"
QT_MOC_LITERAL(597, 7905, 12), // "getRobotName"
QT_MOC_LITERAL(598, 7918, 18), // "getMotorConnection"
QT_MOC_LITERAL(599, 7937, 14), // "getMotorStatus"
QT_MOC_LITERAL(600, 7952, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(601, 7970, 19), // "getMotorTemperature"
QT_MOC_LITERAL(602, 7990, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(603, 8016, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(604, 8043, 15), // "getMotorCurrent"
QT_MOC_LITERAL(605, 8059, 14), // "getPowerStatus"
QT_MOC_LITERAL(606, 8074, 15), // "getRemoteStatus"
QT_MOC_LITERAL(607, 8090, 22), // "getChargeConnectStatus"
QT_MOC_LITERAL(608, 8113, 15), // "getChargeStatus"
QT_MOC_LITERAL(609, 8129, 12), // "getEmoStatus"
QT_MOC_LITERAL(610, 8142, 13), // "getLockStatus"
QT_MOC_LITERAL(611, 8156, 12), // "getBatteryIn"
QT_MOC_LITERAL(612, 8169, 13), // "getBatteryOut"
QT_MOC_LITERAL(613, 8183, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(614, 8201, 8), // "getPower"
QT_MOC_LITERAL(615, 8210, 13), // "getPowerTotal"
QT_MOC_LITERAL(616, 8224, 12), // "getObsinPath"
QT_MOC_LITERAL(617, 8237, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(618, 8255, 12), // "setMotorLock"
QT_MOC_LITERAL(619, 8268, 14), // "getRobotRadius"
QT_MOC_LITERAL(620, 8283, 9), // "getRobotx"
QT_MOC_LITERAL(621, 8293, 9), // "getRoboty"
QT_MOC_LITERAL(622, 8303, 10), // "getRobotth"
QT_MOC_LITERAL(623, 8314, 13), // "getlastRobotx"
QT_MOC_LITERAL(624, 8328, 13), // "getlastRoboty"
QT_MOC_LITERAL(625, 8342, 14), // "getlastRobotth"
QT_MOC_LITERAL(626, 8357, 10), // "getPathNum"
QT_MOC_LITERAL(627, 8368, 8), // "getPathx"
QT_MOC_LITERAL(628, 8377, 8), // "getPathy"
QT_MOC_LITERAL(629, 8386, 9), // "getPathth"
QT_MOC_LITERAL(630, 8396, 15), // "getLocalPathNum"
QT_MOC_LITERAL(631, 8412, 13), // "getLocalPathx"
QT_MOC_LITERAL(632, 8426, 13), // "getLocalPathy"
QT_MOC_LITERAL(633, 8440, 10), // "getuistate"
QT_MOC_LITERAL(634, 8451, 10), // "getMapname"
QT_MOC_LITERAL(635, 8462, 10), // "getMappath"
QT_MOC_LITERAL(636, 8473, 11), // "getMapWidth"
QT_MOC_LITERAL(637, 8485, 12), // "getMapHeight"
QT_MOC_LITERAL(638, 8498, 12), // "getGridWidth"
QT_MOC_LITERAL(639, 8511, 9), // "getOrigin"
QT_MOC_LITERAL(640, 8521, 15), // "getMappingWidth"
QT_MOC_LITERAL(641, 8537, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(642, 8557, 17), // "getObjectPointNum"
QT_MOC_LITERAL(643, 8575, 9), // "addObject"
QT_MOC_LITERAL(644, 8585, 14), // "addObjectPoint"
QT_MOC_LITERAL(645, 8600, 9), // "setObject"
QT_MOC_LITERAL(646, 8610, 15), // "editObjectStart"
QT_MOC_LITERAL(647, 8626, 10), // "editObject"
QT_MOC_LITERAL(648, 8637, 10), // "saveObject"
QT_MOC_LITERAL(649, 8648, 11), // "clearObject"
QT_MOC_LITERAL(650, 8660, 14), // "clearObjectAll"
QT_MOC_LITERAL(651, 8675, 12), // "selectObject"
QT_MOC_LITERAL(652, 8688, 13), // "getObjectflag"
QT_MOC_LITERAL(653, 8702, 10), // "undoObject"
QT_MOC_LITERAL(654, 8713, 11), // "getICPRatio"
QT_MOC_LITERAL(655, 8725, 11), // "getICPError"
QT_MOC_LITERAL(656, 8737, 13), // "clearFlagStop"
QT_MOC_LITERAL(657, 8751, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(658, 8769, 17), // "moveToServingTest"
QT_MOC_LITERAL(659, 8787, 15), // "getusberrorsize"
QT_MOC_LITERAL(660, 8803, 11), // "getusberror"
QT_MOC_LITERAL(661, 8815, 11), // "getzipstate"
QT_MOC_LITERAL(662, 8827, 10), // "clear_call"
QT_MOC_LITERAL(663, 8838, 7), // "usbsave"
QT_MOC_LITERAL(664, 8846, 3), // "usb"
QT_MOC_LITERAL(665, 8850, 3), // "_ui"
QT_MOC_LITERAL(666, 8854, 5), // "_slam"
QT_MOC_LITERAL(667, 8860, 7), // "_config"
QT_MOC_LITERAL(668, 8868, 4), // "_map"
QT_MOC_LITERAL(669, 8873, 4), // "_log"
QT_MOC_LITERAL(670, 8878, 13), // "restartUpdate"
QT_MOC_LITERAL(671, 8892, 11), // "startUpdate"
QT_MOC_LITERAL(672, 8904, 18), // "getTravellineIssue"
QT_MOC_LITERAL(673, 8923, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(674, 8947, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(675, 8970, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(676, 8992, 24) // "getTravellineIssueBroken"

    },
    "Supervisor\0onTimer\0\0path_changed\0"
    "camera_update\0mapping_update\0usb_detect\0"
    "git_pull_fail\0reason\0git_pull_success\0"
    "new_call\0process_accept\0cmd\0process_done\0"
    "process_error\0param\0process_timeout\0"
    "update_success\0update_fail\0clear_all\0"
    "map_reset\0new_call_order\0name\0play_voice\0"
    "ST_VOICE\0voice\0emo_state_changed\0"
    "connect_wifi_fail\0ssid\0connect_wifi_success\0"
    "set_wifi_success\0set_wifi_fail\0"
    "setCurrentPage\0page\0loadMapServer\0"
    "sendMapServer\0checkLocationName\0group\0"
    "resetClear\0getWifiNum\0getWifiConnection\0"
    "getEthernetConnection\0getInternetConnection\0"
    "getCurWifiSSID\0getWifiSSID\0num\0"
    "connectWifi\0passwd\0getWifiSecurity\0"
    "getWifiLevel\0getWifiRate\0getWifiInuse\0"
    "getAllWifiList\0getWifiIP\0setWifiDHCP\0"
    "setWifi\0ip\0gateway\0dns\0subnet\0dns1\0"
    "dns2\0setEthernet\0getcurIP\0getcurGateway\0"
    "getcurNetmask\0getcurDNS2\0getcurDNS\0"
    "getethernetIP\0getethernetGateway\0"
    "getethernetNetmask\0getethernetDNS2\0"
    "getethernetDNS\0getcurIPMethod\0"
    "readWifiState\0getSystemVolume\0passInit\0"
    "isDebugMode\0loopClosing\0readPatrol\0"
    "getPatrolSize\0getPatrolVoiceNameNum\0"
    "getPatrolName\0getPatrolType\0"
    "getPatrolLocation\0getPatrolMovingPage\0"
    "getPatrolArrivePage\0getPatrolWaitTime\0"
    "getPatrolPassTime\0getPatrolVoice\0"
    "getPatrolVoiceMode\0getPatrolVoiceMention\0"
    "getPatrolVoiceLanguage\0isPatrolPage\0"
    "getPatrolMovingMode\0getPatrolArriveMode\0"
    "setCurrentPatrol\0getPatrolLocationSize\0"
    "loc\0clearPatrolLocation\0mode\0"
    "addPatrolLocation\0setPatrolMovingPage\0"
    "param1\0param2\0param3\0setPatrolArrivePage\0"
    "savePatrolVoiceBasic\0text\0setPatrolVoice\0"
    "language\0volume\0mention\0setPatrol\0"
    "type\0wait_time\0pass_time\0savePatrol\0"
    "deletePatrol\0startPatrol\0makeTTSAll\0"
    "setTTSMode\0setTTSVoice\0lan\0setTTSVoiceDetail\0"
    "speed\0pitch\0alpha\0emotion\0emostren\0"
    "clearTTSVoice\0saveTTSVoice\0makePatrolTTS\0"
    "play\0getTTSNameNum\0getTTSLanguageNum\0"
    "loadFile\0setMap\0setFullScreen\0"
    "setMapDrawing\0playBGM\0stopBGM\0isplayBGM\0"
    "setvolumeBGM\0getTTSSpeed\0getTTSPitch\0"
    "getTTSEmotion\0getTTSEmotionStrength\0"
    "getTTSAlpha\0getTTSVolume\0getTTSMention\0"
    "setTTSMentionBasic\0setTTSMention\0"
    "playVoice\0file\0getTTSVoice\0playTTS\0"
    "setServingPageBackground\0"
    "getServingPageBackground\0setServingPageMode\0"
    "getServingPageMode\0setServingPageColor\0"
    "getServingPageColor\0setServingPageImage\0"
    "getServingPageImage\0setServingPageVideo\0"
    "getServingPageVideo\0setServingPageVideoAudio\0"
    "getServingPageVideoAudio\0setServingPageAudio\0"
    "getServingPageAudio\0setMovingPageBackground\0"
    "getMovingPageBackground\0setMovingPageMode\0"
    "getMovingPageMode\0setMovingPageColor\0"
    "getMovingPageColor\0setMovingPageImage\0"
    "getMovingPageImage\0setMovingPageVideo\0"
    "getMovingPageVideo\0setMovingPageVideoAudio\0"
    "getMovingPageVideoAudio\0setMovingPageAudio\0"
    "getMovingPageAudio\0clearPatrolPage\0"
    "clearServingPage\0initServingPage\0"
    "saveServingPage\0getServingObjectSize\0"
    "getServingObjectType\0getServingObjectSource\0"
    "getServingObjectColor\0getServingObjectX\0"
    "getServingObjectY\0getServingObjectWidth\0"
    "getServingObjectHeight\0getServingObjectFontsize\0"
    "addServingObject\0obj\0setServingObjectSource\0"
    "src\0setServingObjectColor\0color\0"
    "deleteServingObject\0moveServingObject\0"
    "x\0y\0setServingObjectSize\0point\0width\0"
    "height\0getServingObjectNum\0"
    "getPatrolObjectSize\0getPageObjectType\0"
    "getPageObjectSource\0getPageObjectColor\0"
    "getPageObjectX\0getPageObjectY\0"
    "getPageObjectWidth\0getPageObjectHeight\0"
    "getPageObjectFontsize\0addPatrolObject\0"
    "setPageObjectSource\0setPageObjectColor\0"
    "deletePatrolObject\0movePatrolObject\0"
    "setPatrolObjectSize\0getPageObjectNum\0"
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
    "visible\0checkTravelline\0getNewServingName\0"
    "isDuplicateName\0updateProgram\0gitReset\0"
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
     631,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 3169,    2, 0x0a /* Public */,
       3,    0, 3170,    2, 0x0a /* Public */,
       4,    0, 3171,    2, 0x0a /* Public */,
       5,    0, 3172,    2, 0x0a /* Public */,
       6,    0, 3173,    2, 0x0a /* Public */,
       7,    1, 3174,    2, 0x0a /* Public */,
       9,    0, 3177,    2, 0x0a /* Public */,
      10,    0, 3178,    2, 0x0a /* Public */,
      11,    1, 3179,    2, 0x0a /* Public */,
      13,    1, 3182,    2, 0x0a /* Public */,
      14,    2, 3185,    2, 0x0a /* Public */,
      16,    1, 3190,    2, 0x0a /* Public */,
      17,    0, 3193,    2, 0x0a /* Public */,
      18,    0, 3194,    2, 0x0a /* Public */,
      19,    0, 3195,    2, 0x0a /* Public */,
      20,    0, 3196,    2, 0x0a /* Public */,
      21,    1, 3197,    2, 0x0a /* Public */,
      23,    1, 3200,    2, 0x0a /* Public */,
      26,    0, 3203,    2, 0x0a /* Public */,
      27,    2, 3204,    2, 0x0a /* Public */,
      29,    1, 3209,    2, 0x0a /* Public */,
      30,    1, 3212,    2, 0x0a /* Public */,
      31,    2, 3215,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      32,    1, 3220,    2, 0x02 /* Public */,
      34,    0, 3223,    2, 0x02 /* Public */,
      35,    0, 3224,    2, 0x02 /* Public */,
      36,    2, 3225,    2, 0x02 /* Public */,
      38,    0, 3230,    2, 0x02 /* Public */,
      39,    0, 3231,    2, 0x02 /* Public */,
      40,    0, 3232,    2, 0x02 /* Public */,
      41,    0, 3233,    2, 0x02 /* Public */,
      42,    0, 3234,    2, 0x02 /* Public */,
      43,    0, 3235,    2, 0x02 /* Public */,
      44,    1, 3236,    2, 0x02 /* Public */,
      46,    2, 3239,    2, 0x02 /* Public */,
      48,    1, 3244,    2, 0x02 /* Public */,
      49,    1, 3247,    2, 0x02 /* Public */,
      49,    0, 3250,    2, 0x02 /* Public */,
      50,    1, 3251,    2, 0x02 /* Public */,
      51,    1, 3254,    2, 0x02 /* Public */,
      52,    0, 3257,    2, 0x02 /* Public */,
      53,    0, 3258,    2, 0x02 /* Public */,
      54,    0, 3259,    2, 0x02 /* Public */,
      55,    3, 3260,    2, 0x02 /* Public */,
      55,    6, 3267,    2, 0x02 /* Public */,
      62,    5, 3280,    2, 0x02 /* Public */,
      63,    0, 3291,    2, 0x02 /* Public */,
      64,    0, 3292,    2, 0x02 /* Public */,
      65,    0, 3293,    2, 0x02 /* Public */,
      66,    0, 3294,    2, 0x02 /* Public */,
      67,    0, 3295,    2, 0x02 /* Public */,
      68,    0, 3296,    2, 0x02 /* Public */,
      69,    0, 3297,    2, 0x02 /* Public */,
      70,    0, 3298,    2, 0x02 /* Public */,
      71,    0, 3299,    2, 0x02 /* Public */,
      72,    0, 3300,    2, 0x02 /* Public */,
      73,    0, 3301,    2, 0x02 /* Public */,
      74,    1, 3302,    2, 0x02 /* Public */,
      75,    0, 3305,    2, 0x02 /* Public */,
      76,    0, 3306,    2, 0x02 /* Public */,
      77,    0, 3307,    2, 0x02 /* Public */,
      78,    0, 3308,    2, 0x02 /* Public */,
      79,    0, 3309,    2, 0x02 /* Public */,
      80,    0, 3310,    2, 0x02 /* Public */,
      81,    1, 3311,    2, 0x02 /* Public */,
      82,    1, 3314,    2, 0x02 /* Public */,
      83,    1, 3317,    2, 0x02 /* Public */,
      84,    1, 3320,    2, 0x02 /* Public */,
      85,    1, 3323,    2, 0x02 /* Public */,
      86,    1, 3326,    2, 0x02 /* Public */,
      87,    1, 3329,    2, 0x02 /* Public */,
      88,    1, 3332,    2, 0x02 /* Public */,
      89,    1, 3335,    2, 0x02 /* Public */,
      90,    1, 3338,    2, 0x02 /* Public */,
      91,    1, 3341,    2, 0x02 /* Public */,
      92,    1, 3344,    2, 0x02 /* Public */,
      93,    0, 3347,    2, 0x02 /* Public */,
      94,    0, 3348,    2, 0x02 /* Public */,
      95,    0, 3349,    2, 0x02 /* Public */,
      96,    1, 3350,    2, 0x02 /* Public */,
      97,    1, 3353,    2, 0x02 /* Public */,
      84,    2, 3356,    2, 0x02 /* Public */,
      99,    1, 3361,    2, 0x02 /* Public */,
     101,    1, 3364,    2, 0x02 /* Public */,
     102,    4, 3367,    2, 0x02 /* Public */,
     102,    3, 3376,    2, 0x22 /* Public | MethodCloned */,
     102,    2, 3383,    2, 0x22 /* Public | MethodCloned */,
     102,    1, 3388,    2, 0x22 /* Public | MethodCloned */,
     106,    4, 3391,    2, 0x02 /* Public */,
     106,    3, 3400,    2, 0x22 /* Public | MethodCloned */,
     106,    2, 3407,    2, 0x22 /* Public | MethodCloned */,
     106,    1, 3412,    2, 0x22 /* Public | MethodCloned */,
     107,    2, 3415,    2, 0x02 /* Public */,
     109,    5, 3420,    2, 0x02 /* Public */,
     109,    4, 3431,    2, 0x22 /* Public | MethodCloned */,
     113,    5, 3440,    2, 0x02 /* Public */,
     117,    4, 3451,    2, 0x02 /* Public */,
     118,    1, 3460,    2, 0x02 /* Public */,
     119,    1, 3463,    2, 0x02 /* Public */,
     120,    0, 3466,    2, 0x02 /* Public */,
     121,    1, 3467,    2, 0x02 /* Public */,
     122,    2, 3470,    2, 0x02 /* Public */,
     124,    5, 3475,    2, 0x02 /* Public */,
     124,    4, 3486,    2, 0x22 /* Public | MethodCloned */,
     124,    3, 3495,    2, 0x22 /* Public | MethodCloned */,
     130,    2, 3502,    2, 0x02 /* Public */,
     131,    0, 3507,    2, 0x02 /* Public */,
     132,    4, 3508,    2, 0x02 /* Public */,
     132,    3, 3517,    2, 0x22 /* Public | MethodCloned */,
     134,    0, 3524,    2, 0x02 /* Public */,
     135,    0, 3525,    2, 0x02 /* Public */,
     136,    2, 3526,    2, 0x02 /* Public */,
     136,    0, 3531,    2, 0x02 /* Public */,
     137,    0, 3532,    2, 0x02 /* Public */,
     138,    0, 3533,    2, 0x02 /* Public */,
     139,    0, 3534,    2, 0x02 /* Public */,
     140,    1, 3535,    2, 0x02 /* Public */,
     140,    0, 3538,    2, 0x22 /* Public | MethodCloned */,
     141,    0, 3539,    2, 0x02 /* Public */,
     142,    0, 3540,    2, 0x02 /* Public */,
     143,    1, 3541,    2, 0x02 /* Public */,
     144,    0, 3544,    2, 0x02 /* Public */,
     145,    0, 3545,    2, 0x02 /* Public */,
     146,    0, 3546,    2, 0x02 /* Public */,
     147,    0, 3547,    2, 0x02 /* Public */,
     148,    0, 3548,    2, 0x02 /* Public */,
     149,    0, 3549,    2, 0x02 /* Public */,
     150,    1, 3550,    2, 0x02 /* Public */,
     151,    0, 3553,    2, 0x02 /* Public */,
     152,    2, 3554,    2, 0x02 /* Public */,
     153,    5, 3559,    2, 0x02 /* Public */,
     153,    4, 3570,    2, 0x22 /* Public | MethodCloned */,
     153,    3, 3579,    2, 0x22 /* Public | MethodCloned */,
     153,    2, 3586,    2, 0x22 /* Public | MethodCloned */,
     153,    1, 3591,    2, 0x22 /* Public | MethodCloned */,
     155,    2, 3594,    2, 0x02 /* Public */,
     156,    0, 3599,    2, 0x02 /* Public */,
     157,    1, 3600,    2, 0x02 /* Public */,
     158,    0, 3603,    2, 0x02 /* Public */,
     159,    1, 3604,    2, 0x02 /* Public */,
     160,    0, 3607,    2, 0x02 /* Public */,
     161,    1, 3608,    2, 0x02 /* Public */,
     162,    0, 3611,    2, 0x02 /* Public */,
     163,    1, 3612,    2, 0x02 /* Public */,
     164,    0, 3615,    2, 0x02 /* Public */,
     165,    1, 3616,    2, 0x02 /* Public */,
     166,    0, 3619,    2, 0x02 /* Public */,
     167,    1, 3620,    2, 0x02 /* Public */,
     168,    0, 3623,    2, 0x02 /* Public */,
     169,    1, 3624,    2, 0x02 /* Public */,
     170,    0, 3627,    2, 0x02 /* Public */,
     171,    1, 3628,    2, 0x02 /* Public */,
     172,    0, 3631,    2, 0x02 /* Public */,
     173,    1, 3632,    2, 0x02 /* Public */,
     174,    0, 3635,    2, 0x02 /* Public */,
     175,    1, 3636,    2, 0x02 /* Public */,
     176,    0, 3639,    2, 0x02 /* Public */,
     177,    1, 3640,    2, 0x02 /* Public */,
     178,    0, 3643,    2, 0x02 /* Public */,
     179,    1, 3644,    2, 0x02 /* Public */,
     180,    0, 3647,    2, 0x02 /* Public */,
     181,    1, 3648,    2, 0x02 /* Public */,
     182,    0, 3651,    2, 0x02 /* Public */,
     183,    1, 3652,    2, 0x02 /* Public */,
     184,    0, 3655,    2, 0x02 /* Public */,
     185,    1, 3656,    2, 0x02 /* Public */,
     186,    0, 3659,    2, 0x02 /* Public */,
     187,    0, 3660,    2, 0x02 /* Public */,
     188,    0, 3661,    2, 0x02 /* Public */,
     189,    0, 3662,    2, 0x02 /* Public */,
     190,    1, 3663,    2, 0x02 /* Public */,
     191,    1, 3666,    2, 0x02 /* Public */,
     192,    1, 3669,    2, 0x02 /* Public */,
     193,    1, 3672,    2, 0x02 /* Public */,
     194,    1, 3675,    2, 0x02 /* Public */,
     195,    1, 3678,    2, 0x02 /* Public */,
     196,    1, 3681,    2, 0x02 /* Public */,
     197,    1, 3684,    2, 0x02 /* Public */,
     198,    2, 3687,    2, 0x02 /* Public */,
     200,    2, 3692,    2, 0x02 /* Public */,
     202,    2, 3697,    2, 0x02 /* Public */,
     204,    1, 3702,    2, 0x02 /* Public */,
     205,    3, 3705,    2, 0x02 /* Public */,
     208,    4, 3712,    2, 0x02 /* Public */,
     208,    5, 3721,    2, 0x02 /* Public */,
     212,    2, 3732,    2, 0x02 /* Public */,
     213,    0, 3737,    2, 0x02 /* Public */,
     214,    1, 3738,    2, 0x02 /* Public */,
     215,    1, 3741,    2, 0x02 /* Public */,
     216,    1, 3744,    2, 0x02 /* Public */,
     217,    1, 3747,    2, 0x02 /* Public */,
     218,    1, 3750,    2, 0x02 /* Public */,
     219,    1, 3753,    2, 0x02 /* Public */,
     220,    1, 3756,    2, 0x02 /* Public */,
     221,    1, 3759,    2, 0x02 /* Public */,
     222,    2, 3762,    2, 0x02 /* Public */,
     223,    2, 3767,    2, 0x02 /* Public */,
     224,    2, 3772,    2, 0x02 /* Public */,
     225,    1, 3777,    2, 0x02 /* Public */,
     226,    3, 3780,    2, 0x02 /* Public */,
     227,    4, 3787,    2, 0x02 /* Public */,
     227,    5, 3796,    2, 0x02 /* Public */,
     228,    2, 3807,    2, 0x02 /* Public */,
     229,    1, 3812,    2, 0x02 /* Public */,
     230,    0, 3815,    2, 0x02 /* Public */,
     231,    1, 3816,    2, 0x02 /* Public */,
     232,    1, 3819,    2, 0x02 /* Public */,
     233,    0, 3822,    2, 0x02 /* Public */,
     234,    1, 3823,    2, 0x02 /* Public */,
     235,    1, 3826,    2, 0x02 /* Public */,
     237,    0, 3829,    2, 0x02 /* Public */,
     238,    1, 3830,    2, 0x02 /* Public */,
     240,    1, 3833,    2, 0x02 /* Public */,
     241,    1, 3836,    2, 0x02 /* Public */,
     242,    1, 3839,    2, 0x02 /* Public */,
     243,    1, 3842,    2, 0x02 /* Public */,
     244,    1, 3845,    2, 0x02 /* Public */,
     245,    1, 3848,    2, 0x02 /* Public */,
     246,    1, 3851,    2, 0x02 /* Public */,
     247,    0, 3854,    2, 0x02 /* Public */,
     248,    0, 3855,    2, 0x02 /* Public */,
     249,    0, 3856,    2, 0x02 /* Public */,
     250,    1, 3857,    2, 0x02 /* Public */,
     251,    1, 3860,    2, 0x02 /* Public */,
     252,    0, 3863,    2, 0x02 /* Public */,
     253,    1, 3864,    2, 0x02 /* Public */,
     254,    0, 3867,    2, 0x02 /* Public */,
     255,    1, 3868,    2, 0x02 /* Public */,
     256,    0, 3871,    2, 0x02 /* Public */,
     257,    1, 3872,    2, 0x02 /* Public */,
     258,    0, 3875,    2, 0x02 /* Public */,
     259,    1, 3876,    2, 0x02 /* Public */,
     260,    0, 3879,    2, 0x02 /* Public */,
     261,    0, 3880,    2, 0x02 /* Public */,
     262,    0, 3881,    2, 0x02 /* Public */,
     263,    1, 3882,    2, 0x02 /* Public */,
     264,    0, 3885,    2, 0x02 /* Public */,
     265,    3, 3886,    2, 0x02 /* Public */,
     267,    0, 3893,    2, 0x02 /* Public */,
     268,    0, 3894,    2, 0x02 /* Public */,
     269,    0, 3895,    2, 0x02 /* Public */,
     270,    0, 3896,    2, 0x02 /* Public */,
     271,    0, 3897,    2, 0x02 /* Public */,
     272,    2, 3898,    2, 0x02 /* Public */,
     273,    3, 3903,    2, 0x02 /* Public */,
     274,    2, 3910,    2, 0x02 /* Public */,
     275,    0, 3915,    2, 0x02 /* Public */,
     276,    0, 3916,    2, 0x02 /* Public */,
     277,    1, 3917,    2, 0x02 /* Public */,
     279,    0, 3920,    2, 0x02 /* Public */,
     280,    0, 3921,    2, 0x02 /* Public */,
     281,    0, 3922,    2, 0x02 /* Public */,
     282,    0, 3923,    2, 0x02 /* Public */,
     283,    0, 3924,    2, 0x02 /* Public */,
     284,    0, 3925,    2, 0x02 /* Public */,
     285,    0, 3926,    2, 0x02 /* Public */,
     286,    2, 3927,    2, 0x02 /* Public */,
     287,    2, 3932,    2, 0x02 /* Public */,
     288,    2, 3937,    2, 0x02 /* Public */,
     289,    2, 3942,    2, 0x02 /* Public */,
     290,    2, 3947,    2, 0x02 /* Public */,
     291,    2, 3952,    2, 0x02 /* Public */,
     292,    1, 3957,    2, 0x02 /* Public */,
     293,    2, 3960,    2, 0x02 /* Public */,
     294,    2, 3965,    2, 0x02 /* Public */,
     295,    0, 3970,    2, 0x02 /* Public */,
     296,    0, 3971,    2, 0x02 /* Public */,
     297,    0, 3972,    2, 0x02 /* Public */,
     298,    0, 3973,    2, 0x02 /* Public */,
     299,    2, 3974,    2, 0x02 /* Public */,
     300,    2, 3979,    2, 0x02 /* Public */,
     301,    0, 3984,    2, 0x02 /* Public */,
     302,    1, 3985,    2, 0x02 /* Public */,
     304,    2, 3988,    2, 0x02 /* Public */,
     305,    2, 3993,    2, 0x02 /* Public */,
     306,    2, 3998,    2, 0x02 /* Public */,
     307,    1, 4003,    2, 0x02 /* Public */,
     308,    1, 4006,    2, 0x02 /* Public */,
     309,    3, 4009,    2, 0x02 /* Public */,
     311,    5, 4016,    2, 0x02 /* Public */,
     316,    3, 4027,    2, 0x02 /* Public */,
     317,    5, 4034,    2, 0x02 /* Public */,
     318,    3, 4045,    2, 0x02 /* Public */,
     319,    5, 4052,    2, 0x02 /* Public */,
     320,    2, 4063,    2, 0x02 /* Public */,
     321,    3, 4068,    2, 0x02 /* Public */,
     323,    0, 4075,    2, 0x02 /* Public */,
     324,    3, 4076,    2, 0x02 /* Public */,
     325,    3, 4083,    2, 0x02 /* Public */,
     326,    3, 4090,    2, 0x02 /* Public */,
     327,    1, 4097,    2, 0x02 /* Public */,
     320,    2, 4100,    2, 0x02 /* Public */,
     328,    1, 4105,    2, 0x02 /* Public */,
     329,    0, 4108,    2, 0x02 /* Public */,
     330,    1, 4109,    2, 0x02 /* Public */,
     331,    0, 4112,    2, 0x02 /* Public */,
     332,    0, 4113,    2, 0x02 /* Public */,
     333,    0, 4114,    2, 0x02 /* Public */,
     334,    0, 4115,    2, 0x02 /* Public */,
     335,    0, 4116,    2, 0x02 /* Public */,
     336,    3, 4117,    2, 0x02 /* Public */,
     337,    0, 4124,    2, 0x02 /* Public */,
     338,    2, 4125,    2, 0x02 /* Public */,
     338,    3, 4130,    2, 0x02 /* Public */,
     341,    0, 4137,    2, 0x02 /* Public */,
     341,    1, 4138,    2, 0x02 /* Public */,
     342,    0, 4141,    2, 0x02 /* Public */,
     343,    0, 4142,    2, 0x02 /* Public */,
     344,    1, 4143,    2, 0x02 /* Public */,
     346,    0, 4146,    2, 0x02 /* Public */,
     347,    0, 4147,    2, 0x02 /* Public */,
     348,    3, 4148,    2, 0x02 /* Public */,
     350,    3, 4155,    2, 0x02 /* Public */,
     351,    2, 4162,    2, 0x02 /* Public */,
     352,    0, 4167,    2, 0x02 /* Public */,
     353,    0, 4168,    2, 0x02 /* Public */,
     354,    0, 4169,    2, 0x02 /* Public */,
     355,    0, 4170,    2, 0x02 /* Public */,
     356,    1, 4171,    2, 0x02 /* Public */,
     357,    1, 4174,    2, 0x02 /* Public */,
     358,    1, 4177,    2, 0x02 /* Public */,
     359,    1, 4180,    2, 0x02 /* Public */,
     360,    1, 4183,    2, 0x02 /* Public */,
     361,    1, 4186,    2, 0x02 /* Public */,
     362,    1, 4189,    2, 0x02 /* Public */,
     363,    0, 4192,    2, 0x02 /* Public */,
     364,    3, 4193,    2, 0x02 /* Public */,
     365,    0, 4200,    2, 0x02 /* Public */,
     366,    1, 4201,    2, 0x02 /* Public */,
     367,    1, 4204,    2, 0x02 /* Public */,
     369,    0, 4207,    2, 0x02 /* Public */,
     370,    0, 4208,    2, 0x02 /* Public */,
     371,    0, 4209,    2, 0x02 /* Public */,
     372,    1, 4210,    2, 0x02 /* Public */,
     373,    1, 4213,    2, 0x02 /* Public */,
     374,    0, 4216,    2, 0x02 /* Public */,
     375,    0, 4217,    2, 0x02 /* Public */,
     376,    0, 4218,    2, 0x02 /* Public */,
     377,    0, 4219,    2, 0x02 /* Public */,
     378,    0, 4220,    2, 0x02 /* Public */,
     379,    0, 4221,    2, 0x02 /* Public */,
     380,    0, 4222,    2, 0x02 /* Public */,
     381,    0, 4223,    2, 0x02 /* Public */,
     382,    0, 4224,    2, 0x02 /* Public */,
     383,    0, 4225,    2, 0x02 /* Public */,
     384,    0, 4226,    2, 0x02 /* Public */,
     385,    1, 4227,    2, 0x02 /* Public */,
     386,    1, 4230,    2, 0x02 /* Public */,
     387,    1, 4233,    2, 0x02 /* Public */,
     388,    1, 4236,    2, 0x02 /* Public */,
     389,    1, 4239,    2, 0x02 /* Public */,
     390,    1, 4242,    2, 0x02 /* Public */,
     391,    1, 4245,    2, 0x02 /* Public */,
     392,    3, 4248,    2, 0x02 /* Public */,
     394,    1, 4255,    2, 0x02 /* Public */,
     394,    0, 4258,    2, 0x22 /* Public | MethodCloned */,
     396,    3, 4259,    2, 0x02 /* Public */,
     397,    0, 4266,    2, 0x02 /* Public */,
     398,    1, 4267,    2, 0x02 /* Public */,
     400,    0, 4270,    2, 0x02 /* Public */,
     401,    0, 4271,    2, 0x02 /* Public */,
     402,    0, 4272,    2, 0x02 /* Public */,
     403,    0, 4273,    2, 0x02 /* Public */,
     404,    2, 4274,    2, 0x02 /* Public */,
     407,    0, 4279,    2, 0x02 /* Public */,
     408,    1, 4280,    2, 0x02 /* Public */,
     409,    1, 4283,    2, 0x02 /* Public */,
     411,    0, 4286,    2, 0x02 /* Public */,
     412,    1, 4287,    2, 0x02 /* Public */,
     413,    2, 4290,    2, 0x02 /* Public */,
     414,    0, 4295,    2, 0x02 /* Public */,
     415,    0, 4296,    2, 0x02 /* Public */,
     416,    0, 4297,    2, 0x02 /* Public */,
     417,    0, 4298,    2, 0x02 /* Public */,
     418,    0, 4299,    2, 0x02 /* Public */,
     419,    0, 4300,    2, 0x02 /* Public */,
     420,    0, 4301,    2, 0x02 /* Public */,
     421,    0, 4302,    2, 0x02 /* Public */,
     422,    0, 4303,    2, 0x02 /* Public */,
     423,    0, 4304,    2, 0x02 /* Public */,
     424,    0, 4305,    2, 0x02 /* Public */,
     425,    0, 4306,    2, 0x02 /* Public */,
     426,    0, 4307,    2, 0x02 /* Public */,
     427,    1, 4308,    2, 0x02 /* Public */,
     428,    1, 4311,    2, 0x02 /* Public */,
     429,    1, 4314,    2, 0x02 /* Public */,
     430,    1, 4317,    2, 0x02 /* Public */,
     431,    1, 4320,    2, 0x02 /* Public */,
     432,    0, 4323,    2, 0x02 /* Public */,
     433,    0, 4324,    2, 0x02 /* Public */,
     434,    0, 4325,    2, 0x02 /* Public */,
     435,    0, 4326,    2, 0x02 /* Public */,
     436,    1, 4327,    2, 0x02 /* Public */,
     437,    0, 4330,    2, 0x02 /* Public */,
     438,    2, 4331,    2, 0x02 /* Public */,
     440,    2, 4336,    2, 0x02 /* Public */,
     440,    1, 4341,    2, 0x02 /* Public */,
     442,    1, 4344,    2, 0x02 /* Public */,
     444,    0, 4347,    2, 0x02 /* Public */,
     445,    0, 4348,    2, 0x02 /* Public */,
     446,    0, 4349,    2, 0x02 /* Public */,
     447,    0, 4350,    2, 0x02 /* Public */,
     448,    1, 4351,    2, 0x02 /* Public */,
     449,    0, 4354,    2, 0x02 /* Public */,
     450,    1, 4355,    2, 0x02 /* Public */,
     451,    1, 4358,    2, 0x02 /* Public */,
     452,    1, 4361,    2, 0x02 /* Public */,
     453,    1, 4364,    2, 0x02 /* Public */,
     454,    1, 4367,    2, 0x02 /* Public */,
     456,    3, 4370,    2, 0x02 /* Public */,
     459,    0, 4377,    2, 0x02 /* Public */,
     460,    0, 4378,    2, 0x02 /* Public */,
     461,    0, 4379,    2, 0x02 /* Public */,
     462,    0, 4380,    2, 0x02 /* Public */,
     463,    1, 4381,    2, 0x02 /* Public */,
     464,    0, 4384,    2, 0x02 /* Public */,
     465,    1, 4385,    2, 0x02 /* Public */,
     466,    0, 4388,    2, 0x02 /* Public */,
     467,    1, 4389,    2, 0x02 /* Public */,
     469,    0, 4392,    2, 0x02 /* Public */,
     470,    0, 4393,    2, 0x02 /* Public */,
     471,    1, 4394,    2, 0x02 /* Public */,
     471,    0, 4397,    2, 0x22 /* Public | MethodCloned */,
     472,    1, 4398,    2, 0x02 /* Public */,
     473,    1, 4401,    2, 0x02 /* Public */,
     473,    0, 4404,    2, 0x22 /* Public | MethodCloned */,
     474,    1, 4405,    2, 0x02 /* Public */,
     474,    0, 4408,    2, 0x22 /* Public | MethodCloned */,
     475,    1, 4409,    2, 0x02 /* Public */,
     475,    0, 4412,    2, 0x22 /* Public | MethodCloned */,
     476,    1, 4413,    2, 0x02 /* Public */,
     476,    0, 4416,    2, 0x22 /* Public | MethodCloned */,
     477,    1, 4417,    2, 0x02 /* Public */,
     478,    1, 4420,    2, 0x02 /* Public */,
     479,    0, 4423,    2, 0x02 /* Public */,
     480,    0, 4424,    2, 0x02 /* Public */,
     481,    1, 4425,    2, 0x02 /* Public */,
     482,    1, 4428,    2, 0x02 /* Public */,
     483,    1, 4431,    2, 0x02 /* Public */,
     484,    0, 4434,    2, 0x02 /* Public */,
     485,    0, 4435,    2, 0x02 /* Public */,
     486,    1, 4436,    2, 0x02 /* Public */,
     488,    1, 4439,    2, 0x02 /* Public */,
     489,    2, 4442,    2, 0x02 /* Public */,
     137,    1, 4447,    2, 0x02 /* Public */,
     492,    3, 4450,    2, 0x02 /* Public */,
     495,    2, 4457,    2, 0x02 /* Public */,
     498,    0, 4462,    2, 0x02 /* Public */,
     499,    1, 4463,    2, 0x02 /* Public */,
     500,    1, 4466,    2, 0x02 /* Public */,
     501,    0, 4469,    2, 0x02 /* Public */,
     502,    3, 4470,    2, 0x02 /* Public */,
     503,    0, 4477,    2, 0x02 /* Public */,
     504,    0, 4478,    2, 0x02 /* Public */,
     505,    0, 4479,    2, 0x02 /* Public */,
     506,    0, 4480,    2, 0x02 /* Public */,
     507,    0, 4481,    2, 0x02 /* Public */,
     508,    0, 4482,    2, 0x02 /* Public */,
     509,    0, 4483,    2, 0x02 /* Public */,
     510,    0, 4484,    2, 0x02 /* Public */,
     511,    0, 4485,    2, 0x02 /* Public */,
     512,    0, 4486,    2, 0x02 /* Public */,
     513,    0, 4487,    2, 0x02 /* Public */,
     514,    1, 4488,    2, 0x02 /* Public */,
     516,    0, 4491,    2, 0x02 /* Public */,
     517,    0, 4492,    2, 0x02 /* Public */,
     518,    0, 4493,    2, 0x02 /* Public */,
     519,    0, 4494,    2, 0x02 /* Public */,
     520,    0, 4495,    2, 0x02 /* Public */,
     521,    1, 4496,    2, 0x02 /* Public */,
     522,    0, 4499,    2, 0x02 /* Public */,
     523,    1, 4500,    2, 0x02 /* Public */,
     524,    2, 4503,    2, 0x02 /* Public */,
     525,    2, 4508,    2, 0x02 /* Public */,
     526,    0, 4513,    2, 0x02 /* Public */,
     527,    2, 4514,    2, 0x02 /* Public */,
     320,    1, 4519,    2, 0x02 /* Public */,
     320,    0, 4522,    2, 0x22 /* Public | MethodCloned */,
     528,    2, 4523,    2, 0x02 /* Public */,
     528,    1, 4528,    2, 0x22 /* Public | MethodCloned */,
     529,    1, 4531,    2, 0x02 /* Public */,
     530,    2, 4534,    2, 0x02 /* Public */,
     531,    2, 4539,    2, 0x02 /* Public */,
     532,    1, 4544,    2, 0x02 /* Public */,
     533,    1, 4547,    2, 0x02 /* Public */,
     534,    2, 4550,    2, 0x02 /* Public */,
     535,    0, 4555,    2, 0x02 /* Public */,
     536,    1, 4556,    2, 0x02 /* Public */,
     535,    1, 4559,    2, 0x02 /* Public */,
     537,    1, 4562,    2, 0x02 /* Public */,
     538,    2, 4565,    2, 0x02 /* Public */,
     539,    1, 4570,    2, 0x02 /* Public */,
     540,    1, 4573,    2, 0x02 /* Public */,
     541,    1, 4576,    2, 0x02 /* Public */,
     326,    4, 4579,    2, 0x02 /* Public */,
     543,    2, 4588,    2, 0x02 /* Public */,
     543,    1, 4593,    2, 0x22 /* Public | MethodCloned */,
     544,    2, 4596,    2, 0x02 /* Public */,
     544,    1, 4601,    2, 0x22 /* Public | MethodCloned */,
     545,    2, 4604,    2, 0x02 /* Public */,
     545,    1, 4609,    2, 0x22 /* Public | MethodCloned */,
     546,    2, 4612,    2, 0x02 /* Public */,
     547,    1, 4617,    2, 0x02 /* Public */,
     548,    0, 4620,    2, 0x02 /* Public */,
     549,    1, 4621,    2, 0x02 /* Public */,
     550,    0, 4624,    2, 0x02 /* Public */,
     551,    0, 4625,    2, 0x02 /* Public */,
     552,    1, 4626,    2, 0x02 /* Public */,
     553,    1, 4629,    2, 0x02 /* Public */,
     554,    2, 4632,    2, 0x02 /* Public */,
     555,    2, 4637,    2, 0x02 /* Public */,
     556,    3, 4642,    2, 0x02 /* Public */,
     558,    1, 4649,    2, 0x02 /* Public */,
     558,    2, 4652,    2, 0x02 /* Public */,
     559,    0, 4657,    2, 0x02 /* Public */,
     560,    1, 4658,    2, 0x02 /* Public */,
     561,    1, 4661,    2, 0x02 /* Public */,
     562,    2, 4664,    2, 0x02 /* Public */,
     562,    1, 4669,    2, 0x22 /* Public | MethodCloned */,
     564,    0, 4672,    2, 0x02 /* Public */,
     565,    0, 4673,    2, 0x02 /* Public */,
     566,    0, 4674,    2, 0x02 /* Public */,
     567,    0, 4675,    2, 0x02 /* Public */,
     568,    0, 4676,    2, 0x02 /* Public */,
     569,    0, 4677,    2, 0x02 /* Public */,
     570,    2, 4678,    2, 0x02 /* Public */,
     570,    1, 4683,    2, 0x22 /* Public | MethodCloned */,
     571,    0, 4686,    2, 0x02 /* Public */,
     572,    3, 4687,    2, 0x02 /* Public */,
     438,    0, 4694,    2, 0x02 /* Public */,
     574,    1, 4695,    2, 0x02 /* Public */,
     576,    0, 4698,    2, 0x02 /* Public */,
     577,    0, 4699,    2, 0x02 /* Public */,
     579,    0, 4700,    2, 0x02 /* Public */,
     580,    0, 4701,    2, 0x02 /* Public */,
     581,    0, 4702,    2, 0x02 /* Public */,
     582,    0, 4703,    2, 0x02 /* Public */,
     583,    0, 4704,    2, 0x02 /* Public */,
     584,    0, 4705,    2, 0x02 /* Public */,
     585,    0, 4706,    2, 0x02 /* Public */,
     586,    0, 4707,    2, 0x02 /* Public */,
     587,    0, 4708,    2, 0x02 /* Public */,
     588,    0, 4709,    2, 0x02 /* Public */,
     589,    1, 4710,    2, 0x02 /* Public */,
     591,    0, 4713,    2, 0x02 /* Public */,
     592,    0, 4714,    2, 0x02 /* Public */,
     593,    0, 4715,    2, 0x02 /* Public */,
     594,    0, 4716,    2, 0x02 /* Public */,
     595,    0, 4717,    2, 0x02 /* Public */,
     596,    0, 4718,    2, 0x02 /* Public */,
     597,    0, 4719,    2, 0x02 /* Public */,
     598,    1, 4720,    2, 0x02 /* Public */,
     599,    1, 4723,    2, 0x02 /* Public */,
     600,    1, 4726,    2, 0x02 /* Public */,
     601,    1, 4729,    2, 0x02 /* Public */,
     602,    1, 4732,    2, 0x02 /* Public */,
     603,    0, 4735,    2, 0x02 /* Public */,
     604,    1, 4736,    2, 0x02 /* Public */,
     605,    0, 4739,    2, 0x02 /* Public */,
     606,    0, 4740,    2, 0x02 /* Public */,
     607,    0, 4741,    2, 0x02 /* Public */,
     608,    0, 4742,    2, 0x02 /* Public */,
     609,    0, 4743,    2, 0x02 /* Public */,
     610,    0, 4744,    2, 0x02 /* Public */,
     611,    0, 4745,    2, 0x02 /* Public */,
     612,    0, 4746,    2, 0x02 /* Public */,
     613,    0, 4747,    2, 0x02 /* Public */,
     614,    0, 4748,    2, 0x02 /* Public */,
     615,    0, 4749,    2, 0x02 /* Public */,
     616,    0, 4750,    2, 0x02 /* Public */,
     617,    0, 4751,    2, 0x02 /* Public */,
     618,    1, 4752,    2, 0x02 /* Public */,
     619,    0, 4755,    2, 0x02 /* Public */,
     620,    0, 4756,    2, 0x02 /* Public */,
     621,    0, 4757,    2, 0x02 /* Public */,
     622,    0, 4758,    2, 0x02 /* Public */,
     623,    0, 4759,    2, 0x02 /* Public */,
     624,    0, 4760,    2, 0x02 /* Public */,
     625,    0, 4761,    2, 0x02 /* Public */,
     626,    0, 4762,    2, 0x02 /* Public */,
     627,    1, 4763,    2, 0x02 /* Public */,
     628,    1, 4766,    2, 0x02 /* Public */,
     629,    1, 4769,    2, 0x02 /* Public */,
     630,    0, 4772,    2, 0x02 /* Public */,
     631,    1, 4773,    2, 0x02 /* Public */,
     632,    1, 4776,    2, 0x02 /* Public */,
     633,    0, 4779,    2, 0x02 /* Public */,
     634,    0, 4780,    2, 0x02 /* Public */,
     635,    0, 4781,    2, 0x02 /* Public */,
     636,    0, 4782,    2, 0x02 /* Public */,
     637,    0, 4783,    2, 0x02 /* Public */,
     638,    0, 4784,    2, 0x02 /* Public */,
     639,    0, 4785,    2, 0x02 /* Public */,
     640,    0, 4786,    2, 0x02 /* Public */,
     641,    0, 4787,    2, 0x02 /* Public */,
     551,    2, 4788,    2, 0x02 /* Public */,
     642,    2, 4793,    2, 0x02 /* Public */,
     643,    2, 4798,    2, 0x02 /* Public */,
     644,    2, 4803,    2, 0x02 /* Public */,
     645,    2, 4808,    2, 0x02 /* Public */,
     646,    2, 4813,    2, 0x02 /* Public */,
     647,    2, 4818,    2, 0x02 /* Public */,
     648,    0, 4823,    2, 0x02 /* Public */,
     649,    0, 4824,    2, 0x02 /* Public */,
     650,    0, 4825,    2, 0x02 /* Public */,
     651,    1, 4826,    2, 0x02 /* Public */,
     652,    0, 4829,    2, 0x02 /* Public */,
     653,    0, 4830,    2, 0x02 /* Public */,
     654,    0, 4831,    2, 0x02 /* Public */,
     655,    0, 4832,    2, 0x02 /* Public */,
     656,    0, 4833,    2, 0x02 /* Public */,
     657,    0, 4834,    2, 0x02 /* Public */,
     658,    2, 4835,    2, 0x02 /* Public */,
     659,    0, 4840,    2, 0x02 /* Public */,
     660,    1, 4841,    2, 0x02 /* Public */,
     661,    0, 4844,    2, 0x02 /* Public */,
     662,    0, 4845,    2, 0x02 /* Public */,
     663,    6, 4846,    2, 0x02 /* Public */,
     663,    5, 4859,    2, 0x22 /* Public | MethodCloned */,
     663,    4, 4870,    2, 0x22 /* Public | MethodCloned */,
     663,    3, 4879,    2, 0x22 /* Public | MethodCloned */,
     663,    2, 4886,    2, 0x22 /* Public | MethodCloned */,
     663,    1, 4891,    2, 0x22 /* Public | MethodCloned */,
     663,    0, 4894,    2, 0x22 /* Public | MethodCloned */,
     670,    0, 4895,    2, 0x02 /* Public */,
     671,    0, 4896,    2, 0x02 /* Public */,
     672,    0, 4897,    2, 0x02 /* Public */,
     673,    1, 4898,    2, 0x02 /* Public */,
     674,    1, 4901,    2, 0x02 /* Public */,
     675,    1, 4904,    2, 0x02 /* Public */,
     676,    1, 4907,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   15,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,   28,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    8,   28,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   37,   22,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   28,   47,
    QMetaType::Bool, QMetaType::QString,   28,
    QMetaType::Int, QMetaType::QString,   28,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   28,
    QMetaType::Bool, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   56,   57,   58,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   28,   56,   59,   57,   60,   61,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   56,   59,   57,   60,   61,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   45,   98,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  100,  103,  104,  105,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  100,  103,  104,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  100,  103,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  100,  103,  104,  105,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  100,  103,  104,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  100,  103,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   25,  108,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  100,  110,   25,  111,  112,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  100,  110,   25,  111,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   45,   22,  114,  115,  116,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   22,  114,  115,  116,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  123,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,  127,  128,  129,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,  127,  128,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  125,  126,  127,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  123,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::Bool,  110,   25,  108,  133,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,  110,   25,  108,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,  114,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  111,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,  111,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString, QMetaType::QString,  108,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  108,  112,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,  154,   25,  100,  110,  111,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  154,   25,  100,  110,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  154,   25,  100,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  154,   25,
    QMetaType::Void, QMetaType::QString,  154,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,  123,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  154,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  154,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  154,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Float,  111,
    QMetaType::Float,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  154,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  154,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  154,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  100,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Float,  111,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   33,  199,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   45,  201,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   45,  203,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   45,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   45,  209,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   45,  206,  207,  210,  211,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   33,  199,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   45,  201,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   45,  203,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   45,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   45,  209,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   45,  206,  207,  210,  211,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Bool, QMetaType::QString,  114,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::Bool,  236,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  266,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   45,  206,  207,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  278,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::QString,  114,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  303,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int,  203,
    QMetaType::Void, QMetaType::Int,  210,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  310,  206,  207,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  310,  312,  313,  314,  315,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  310,  206,  207,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  310,  312,  313,  314,  315,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  310,  206,  207,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  310,  312,  313,  314,  315,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   37,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,  114,  322,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  266,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  266,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  266,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  199,  210,  211,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  339,  340,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   22,   37,  340,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  340,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  345,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  349,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  349,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Void, QMetaType::Int,  111,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  210,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::QString,  368,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Int,   45,
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
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,  154,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  154,   22,  393,
    QMetaType::Void, QMetaType::QString,  395,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  154,   37,   22,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  399,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  405,  406,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Bool,  410,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,   37,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   37,   22,
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
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,  123,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   37,  439,
    0x80000000 | 441, QMetaType::Int, QMetaType::QString,   37,   22,
    0x80000000 | 441, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::Int,  443,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::QDateTime,  455,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  457,  458,  455,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  468,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  487,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  490,  491,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  493,  494,  100,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  496,  497,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  100,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  206,  207,  266,
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
    QMetaType::Void, QMetaType::Bool,  515,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  339,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,  339,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  114,  339,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  114,  239,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   37,   45,
    QMetaType::Int, QMetaType::QString,  114,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   45,  114,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   37,   45,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   22,   45,
    QMetaType::Int, QMetaType::QString,  114,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   37,   45,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   45,   37,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   45,   22,   37,  542,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   45,  114,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   45,  114,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   45,  114,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   37,   45,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  515,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int, QMetaType::Int,   45,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   45,  209,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   45,  209,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  557,  206,  207,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,  114,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,  487,  563,
    QMetaType::Bool, QMetaType::QString,  487,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  487,  100,
    QMetaType::Void, QMetaType::QString,  487,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  573,   37,  439,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  575,
    QMetaType::Void,
    0x80000000 | 578,
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
    QMetaType::Bool, QMetaType::Int,  590,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,  339,
    QMetaType::Int, QMetaType::Int,  339,
    QMetaType::QString, QMetaType::Int,  339,
    QMetaType::Int, QMetaType::Int,  339,
    QMetaType::Int, QMetaType::Int,  339,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,  339,
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
    QMetaType::Void, QMetaType::Bool,  239,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Float, QMetaType::Int,   45,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    0x80000000 | 578,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  206,  207,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   45,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   37,   22,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  664,  665,  666,  667,  668,  669,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  664,  665,  666,  667,  668,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  664,  665,  666,  667,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  664,  665,  666,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  664,  665,
    QMetaType::Void, QMetaType::QString,  664,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::QString, QMetaType::Int,   45,
    QMetaType::Bool, QMetaType::Int,   45,
    QMetaType::Bool, QMetaType::Int,   45,

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
        case 5: _t->git_pull_fail((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        case 19: _t->connect_wifi_fail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 20: _t->connect_wifi_success((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->set_wifi_success((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->set_wifi_fail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 23: _t->setCurrentPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 24: _t->loadMapServer(); break;
        case 25: _t->sendMapServer(); break;
        case 26: { bool _r = _t->checkLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: _t->resetClear(); break;
        case 28: { int _r = _t->getWifiNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 29: { int _r = _t->getWifiConnection();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 30: { int _r = _t->getEthernetConnection();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 31: { int _r = _t->getInternetConnection();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 32: { QString _r = _t->getCurWifiSSID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 33: { QString _r = _t->getWifiSSID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 34: _t->connectWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 35: { bool _r = _t->getWifiSecurity((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 36: { int _r = _t->getWifiLevel((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 37: { int _r = _t->getWifiLevel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 38: { int _r = _t->getWifiRate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 39: { bool _r = _t->getWifiInuse((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 40: _t->getAllWifiList(); break;
        case 41: _t->getWifiIP(); break;
        case 42: _t->setWifiDHCP(); break;
        case 43: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 44: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 45: _t->setEthernet((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 46: { QString _r = _t->getcurIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 47: { QString _r = _t->getcurGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 48: { QString _r = _t->getcurNetmask();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 49: { QString _r = _t->getcurDNS2();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 50: { QString _r = _t->getcurDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 51: { QString _r = _t->getethernetIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 52: { QString _r = _t->getethernetGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 53: { QString _r = _t->getethernetNetmask();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 54: { QString _r = _t->getethernetDNS2();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 55: { QString _r = _t->getethernetDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 56: { QString _r = _t->getcurIPMethod();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 57: _t->readWifiState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 58: { int _r = _t->getSystemVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 59: _t->passInit(); break;
        case 60: { bool _r = _t->isDebugMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 61: _t->loopClosing(); break;
        case 62: _t->readPatrol(); break;
        case 63: { int _r = _t->getPatrolSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 64: { int _r = _t->getPatrolVoiceNameNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 65: { QString _r = _t->getPatrolName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 66: { QString _r = _t->getPatrolType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 67: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 68: { QString _r = _t->getPatrolMovingPage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 69: { QString _r = _t->getPatrolArrivePage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 70: { int _r = _t->getPatrolWaitTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 71: { int _r = _t->getPatrolPassTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 72: { QString _r = _t->getPatrolVoice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 73: { QString _r = _t->getPatrolVoiceMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 74: { QString _r = _t->getPatrolVoiceMention((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 75: { QString _r = _t->getPatrolVoiceLanguage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 76: { bool _r = _t->isPatrolPage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 77: { QString _r = _t->getPatrolMovingMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 78: { QString _r = _t->getPatrolArriveMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 79: _t->setCurrentPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 80: { int _r = _t->getPatrolLocationSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 81: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 82: _t->clearPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 83: _t->addPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 84: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 85: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 86: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 87: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 88: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 89: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 90: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 91: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 92: _t->savePatrolVoiceBasic((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 93: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 94: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 95: _t->setPatrol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 96: _t->savePatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 97: _t->deletePatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 98: _t->startPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 99: _t->makeTTSAll(); break;
        case 100: _t->setTTSMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 101: _t->setTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 102: _t->setTTSVoiceDetail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 103: _t->setTTSVoiceDetail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 104: _t->setTTSVoiceDetail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 105: _t->clearTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 106: _t->saveTTSVoice(); break;
        case 107: _t->makePatrolTTS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 108: _t->makePatrolTTS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 109: { int _r = _t->getTTSNameNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 110: { int _r = _t->getTTSLanguageNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 111: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 112: _t->loadFile(); break;
        case 113: _t->setMap(); break;
        case 114: _t->setFullScreen(); break;
        case 115: _t->setMapDrawing(); break;
        case 116: _t->playBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 117: _t->playBGM(); break;
        case 118: _t->stopBGM(); break;
        case 119: { bool _r = _t->isplayBGM();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 120: _t->setvolumeBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 121: { int _r = _t->getTTSSpeed();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 122: { int _r = _t->getTTSPitch();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 123: { int _r = _t->getTTSEmotion();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 124: { int _r = _t->getTTSEmotionStrength();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 125: { int _r = _t->getTTSAlpha();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 126: { int _r = _t->getTTSVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 127: { QString _r = _t->getTTSMention((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 128: _t->setTTSMentionBasic(); break;
        case 129: _t->setTTSMention((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 130: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 131: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 132: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 133: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 134: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 135: { QString _r = _t->getTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 136: _t->playTTS(); break;
        case 137: _t->setServingPageBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 138: { QString _r = _t->getServingPageBackground();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 139: _t->setServingPageMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 140: { QString _r = _t->getServingPageMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 141: _t->setServingPageColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 142: { QString _r = _t->getServingPageColor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 143: _t->setServingPageImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 144: { QString _r = _t->getServingPageImage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 145: _t->setServingPageVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 146: { QString _r = _t->getServingPageVideo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 147: _t->setServingPageVideoAudio((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 148: { QString _r = _t->getServingPageVideoAudio();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 149: _t->setServingPageAudio((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 150: { float _r = _t->getServingPageAudio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 151: _t->setMovingPageBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 152: { QString _r = _t->getMovingPageBackground();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 153: _t->setMovingPageMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 154: { QString _r = _t->getMovingPageMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 155: _t->setMovingPageColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 156: { QString _r = _t->getMovingPageColor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 157: _t->setMovingPageImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 158: { QString _r = _t->getMovingPageImage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 159: _t->setMovingPageVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 160: { QString _r = _t->getMovingPageVideo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 161: _t->setMovingPageVideoAudio((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 162: { QString _r = _t->getMovingPageVideoAudio();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 163: _t->setMovingPageAudio((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 164: { float _r = _t->getMovingPageAudio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 165: _t->clearPatrolPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 166: _t->clearServingPage(); break;
        case 167: _t->initServingPage(); break;
        case 168: _t->saveServingPage(); break;
        case 169: { int _r = _t->getServingObjectSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 170: { QString _r = _t->getServingObjectType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 171: { QString _r = _t->getServingObjectSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 172: { QString _r = _t->getServingObjectColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 173: { int _r = _t->getServingObjectX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 174: { int _r = _t->getServingObjectY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 175: { int _r = _t->getServingObjectWidth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 176: { int _r = _t->getServingObjectHeight((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 177: { int _r = _t->getServingObjectFontsize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 178: _t->addServingObject((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 179: _t->setServingObjectSource((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 180: _t->setServingObjectColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 181: _t->deleteServingObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 182: _t->moveServingObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 183: _t->setServingObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 184: _t->setServingObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 185: { int _r = _t->getServingObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 186: { int _r = _t->getPatrolObjectSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 187: { QString _r = _t->getPageObjectType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 188: { QString _r = _t->getPageObjectSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 189: { QString _r = _t->getPageObjectColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 190: { int _r = _t->getPageObjectX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 191: { int _r = _t->getPageObjectY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 192: { int _r = _t->getPageObjectWidth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 193: { int _r = _t->getPageObjectHeight((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 194: { int _r = _t->getPageObjectFontsize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 195: _t->addPatrolObject((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 196: _t->setPageObjectSource((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 197: _t->setPageObjectColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 198: _t->deletePatrolObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 199: _t->movePatrolObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 200: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 201: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 202: { int _r = _t->getPageObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 203: { bool _r = _t->isExistNode((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 204: _t->confirmLocalization(); break;
        case 205: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 206: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 207: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 208: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 209: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 210: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 211: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 212: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 213: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 214: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 215: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 216: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 217: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 218: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 219: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 220: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 221: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 222: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 223: _t->setShowNode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 224: { bool _r = _t->getShowNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 225: _t->setShowName((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 226: { bool _r = _t->getShowName();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 227: _t->setShowTline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 228: { bool _r = _t->getShowTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 229: _t->setShowVelmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 230: { bool _r = _t->getShowVelmap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 231: _t->setShowAvoid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 232: { bool _r = _t->getShowAvoid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 233: _t->autoTline(); break;
        case 234: { bool _r = _t->getShowObject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 235: _t->setShowEdge((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 236: { bool _r = _t->getShowEdge();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 237: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 238: _t->clearInitPose(); break;
        case 239: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 240: _t->startDrawingTline(); break;
        case 241: _t->stopDrawingTline(); break;
        case 242: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 243: _t->setRulerPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 244: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 245: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 246: _t->saveRotateMap(); break;
        case 247: _t->initRotate(); break;
        case 248: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 249: _t->rotateMapCW(); break;
        case 250: _t->rotateMapCCW(); break;
        case 251: _t->saveObjectPNG(); break;
        case 252: _t->saveObsAreaPNG(); break;
        case 253: { bool _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 254: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 255: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 256: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 257: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 258: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 259: _t->startErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 260: _t->addErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 261: _t->endErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 262: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 263: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 264: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 265: _t->endDrawingRect(); break;
        case 266: _t->clearDrawing(); break;
        case 267: _t->undoLine(); break;
        case 268: _t->redoLine(); break;
        case 269: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 270: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 271: _t->drawSpline(); break;
        case 272: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 273: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 274: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 275: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 276: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 277: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 278: _t->pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 279: _t->double_pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 280: _t->moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 281: _t->double_moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 282: _t->released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 283: _t->double_released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 284: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 285: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 286: _t->clearLocation(); break;
        case 287: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 288: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 289: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 290: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 291: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 292: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 293: _t->setTableNumberAuto(); break;
        case 294: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 295: _t->saveMap(); break;
        case 296: _t->saveEditedMap(); break;
        case 297: _t->saveTline(); break;
        case 298: _t->saveTlineTemp(); break;
        case 299: _t->saveVelmap(); break;
        case 300: _t->setMapSize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 301: _t->loadAnnotation(); break;
        case 302: _t->addNode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 303: _t->addNode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 304: _t->editNode(); break;
        case 305: _t->editNode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 306: _t->deleteNode(); break;
        case 307: _t->linkNode(); break;
        case 308: _t->alignNode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 309: _t->releaseShift(); break;
        case 310: _t->pressShift(); break;
        case 311: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 312: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 313: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 314: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 315: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 316: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 317: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 318: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 319: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 320: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 321: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 322: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 323: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 324: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 325: _t->requestSystemVolume(); break;
        case 326: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 327: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 328: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 329: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 330: _t->startDrawingObject(); break;
        case 331: _t->stopDrawingObject(); break;
        case 332: _t->saveDrawingObject(); break;
        case 333: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 334: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 335: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 336: _t->killSLAM(); break;
        case 337: _t->makeRobotINI(); break;
        case 338: _t->checkRobotINI(); break;
        case 339: _t->restartSLAM(); break;
        case 340: _t->startSLAM(); break;
        case 341: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 342: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 343: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 344: _t->programRestart(); break;
        case 345: _t->programExit(); break;
        case 346: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 347: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 348: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 349: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 350: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 351: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 352: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 353: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 354: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 355: _t->readSetting(); break;
        case 356: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 357: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 358: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 359: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 360: _t->requestCamera(); break;
        case 361: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 362: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 363: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 364: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 365: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 366: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 367: _t->checkTravelline(); break;
        case 368: { QString _r = _t->getNewServingName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 369: { bool _r = _t->isDuplicateName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 370: _t->updateProgram(); break;
        case 371: _t->gitReset(); break;
        case 372: _t->updateProgramGitPull(); break;
        case 373: _t->checkVersionAgain(); break;
        case 374: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 375: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 376: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 377: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 378: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 379: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 380: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 381: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 382: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 383: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 384: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 385: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 386: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 387: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 388: _t->checkCleaningLocation(); break;
        case 389: { bool _r = _t->isRobotReady();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 390: _t->checkUpdate(); break;
        case 391: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 392: _t->setlanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 393: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 394: _t->startServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 395: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 396: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 397: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 398: _t->clearStatus(); break;
        case 399: _t->stateInit(); break;
        case 400: _t->stateMoving(); break;
        case 401: _t->resetLocalization(); break;
        case 402: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 403: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 404: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 405: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 406: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 407: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 408: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 409: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 410: _t->updateUSB(); break;
        case 411: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 412: _t->readusbrecentfile(); break;
        case 413: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 414: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 415: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 416: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 417: _t->readusb(); break;
        case 418: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 419: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 420: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 421: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 422: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 423: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 424: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 425: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 426: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 427: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 428: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 429: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 430: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 431: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 432: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 433: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 434: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 435: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 436: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 437: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 438: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 439: _t->deleteEditedMap(); break;
        case 440: _t->deleteAnnotation(); break;
        case 441: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 442: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 443: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 444: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 445: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 446: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 447: _t->stopMapping(); break;
        case 448: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 449: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 450: _t->setInitCurPos(); break;
        case 451: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 452: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 453: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 454: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 455: _t->slam_setInit(); break;
        case 456: _t->slam_run(); break;
        case 457: _t->slam_stop(); break;
        case 458: _t->slam_autoInit(); break;
        case 459: _t->slam_restInit(); break;
        case 460: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 461: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 462: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 463: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 464: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 465: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 466: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 467: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 468: _t->cleanTray(); break;
        case 469: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 470: _t->clearCallQueue(); break;
        case 471: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 472: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 473: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 474: _t->setObjPose(); break;
        case 475: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 476: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 477: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 478: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 479: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 480: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 481: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 482: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 483: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 484: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 485: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 486: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 487: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 488: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 489: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 490: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 491: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 492: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 493: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 494: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 495: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 496: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 497: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 498: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 499: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 500: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 501: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 502: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 503: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 504: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 505: _t->clearSharedMemory(); break;
        case 506: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 507: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 508: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 509: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 510: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 511: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 512: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 513: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 514: _t->saveLocations(); break;
        case 515: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 516: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 517: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 518: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 519: _t->saveNode(); break;
        case 520: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 521: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 522: _t->drawingRunawayStart(); break;
        case 523: _t->drawingRunawayStop(); break;
        case 524: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 525: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 526: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 527: _t->slam_ini_reload(); break;
        case 528: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 529: _t->startServing(); break;
        case 530: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 531: _t->confirmPickup(); break;
        case 532: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 533: _t->movePause(); break;
        case 534: _t->moveResume(); break;
        case 535: _t->moveStopFlag(); break;
        case 536: _t->moveStop(); break;
        case 537: _t->moveToCharge(); break;
        case 538: _t->moveToWait(); break;
        case 539: _t->moveToCleaning(); break;
        case 540: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 541: { QString _r = _t->getcurTable();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 542: _t->resetHomeFolders(); break;
        case 543: { bool _r = _t->issetLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 544: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 545: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 546: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 547: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 548: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 549: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 550: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 551: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 552: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 553: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 554: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 555: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 556: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 557: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 558: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 559: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 560: { int _r = _t->getChargeConnectStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 561: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 562: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 563: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 564: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 565: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 566: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 567: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 568: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 569: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 570: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 571: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 572: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 573: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 574: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 575: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 576: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 577: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 578: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 579: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 580: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 581: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 582: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 583: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 584: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 585: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 586: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 587: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 588: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 589: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 590: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 591: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 592: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 593: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 594: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 595: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 596: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 597: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 598: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 599: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 600: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 601: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 602: _t->saveObject(); break;
        case 603: _t->clearObject(); break;
        case 604: _t->clearObjectAll(); break;
        case 605: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 606: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 607: _t->undoObject(); break;
        case 608: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 609: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 610: _t->clearFlagStop(); break;
        case 611: _t->slam_fullautoInit(); break;
        case 612: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 613: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 614: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 615: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 616: _t->clear_call(); break;
        case 617: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 618: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 619: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 620: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 621: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 622: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 623: _t->usbsave(); break;
        case 624: _t->restartUpdate(); break;
        case 625: _t->startUpdate(); break;
        case 626: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 627: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 628: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 629: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 630: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
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
        if (_id < 631)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 631;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 631)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 631;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
