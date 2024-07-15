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
    QByteArrayData data[692];
    char stringdata0[9284];
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
QT_MOC_LITERAL(36, 422, 14), // "checkGroupName"
QT_MOC_LITERAL(37, 437, 17), // "checkLocationName"
QT_MOC_LITERAL(38, 455, 5), // "group"
QT_MOC_LITERAL(39, 461, 12), // "callCallbell"
QT_MOC_LITERAL(40, 474, 2), // "id"
QT_MOC_LITERAL(41, 477, 10), // "resetClear"
QT_MOC_LITERAL(42, 488, 10), // "getWifiNum"
QT_MOC_LITERAL(43, 499, 17), // "getWifiConnection"
QT_MOC_LITERAL(44, 517, 21), // "getEthernetConnection"
QT_MOC_LITERAL(45, 539, 21), // "getInternetConnection"
QT_MOC_LITERAL(46, 561, 14), // "getCurWifiSSID"
QT_MOC_LITERAL(47, 576, 11), // "getWifiSSID"
QT_MOC_LITERAL(48, 588, 3), // "num"
QT_MOC_LITERAL(49, 592, 11), // "connectWifi"
QT_MOC_LITERAL(50, 604, 6), // "passwd"
QT_MOC_LITERAL(51, 611, 15), // "getMasterVolume"
QT_MOC_LITERAL(52, 627, 15), // "setMasterVolume"
QT_MOC_LITERAL(53, 643, 6), // "volume"
QT_MOC_LITERAL(54, 650, 15), // "getWifiSecurity"
QT_MOC_LITERAL(55, 666, 12), // "getWifiLevel"
QT_MOC_LITERAL(56, 679, 11), // "getWifiRate"
QT_MOC_LITERAL(57, 691, 12), // "getWifiInuse"
QT_MOC_LITERAL(58, 704, 14), // "getAllWifiList"
QT_MOC_LITERAL(59, 719, 9), // "getWifiIP"
QT_MOC_LITERAL(60, 729, 11), // "setWifiDHCP"
QT_MOC_LITERAL(61, 741, 7), // "setWifi"
QT_MOC_LITERAL(62, 749, 2), // "ip"
QT_MOC_LITERAL(63, 752, 7), // "gateway"
QT_MOC_LITERAL(64, 760, 3), // "dns"
QT_MOC_LITERAL(65, 764, 6), // "subnet"
QT_MOC_LITERAL(66, 771, 4), // "dns1"
QT_MOC_LITERAL(67, 776, 4), // "dns2"
QT_MOC_LITERAL(68, 781, 11), // "setEthernet"
QT_MOC_LITERAL(69, 793, 8), // "getcurIP"
QT_MOC_LITERAL(70, 802, 13), // "getcurGateway"
QT_MOC_LITERAL(71, 816, 13), // "getcurNetmask"
QT_MOC_LITERAL(72, 830, 10), // "getcurDNS2"
QT_MOC_LITERAL(73, 841, 9), // "getcurDNS"
QT_MOC_LITERAL(74, 851, 13), // "getethernetIP"
QT_MOC_LITERAL(75, 865, 18), // "getethernetGateway"
QT_MOC_LITERAL(76, 884, 18), // "getethernetNetmask"
QT_MOC_LITERAL(77, 903, 15), // "getethernetDNS2"
QT_MOC_LITERAL(78, 919, 14), // "getethernetDNS"
QT_MOC_LITERAL(79, 934, 14), // "getcurIPMethod"
QT_MOC_LITERAL(80, 949, 13), // "readWifiState"
QT_MOC_LITERAL(81, 963, 9), // "getVolume"
QT_MOC_LITERAL(82, 973, 15), // "getSystemVolume"
QT_MOC_LITERAL(83, 989, 8), // "passInit"
QT_MOC_LITERAL(84, 998, 11), // "isDebugMode"
QT_MOC_LITERAL(85, 1010, 11), // "loopClosing"
QT_MOC_LITERAL(86, 1022, 10), // "readPatrol"
QT_MOC_LITERAL(87, 1033, 13), // "getPatrolSize"
QT_MOC_LITERAL(88, 1047, 21), // "getPatrolVoiceNameNum"
QT_MOC_LITERAL(89, 1069, 13), // "getPatrolName"
QT_MOC_LITERAL(90, 1083, 13), // "getPatrolType"
QT_MOC_LITERAL(91, 1097, 19), // "getPatrolMovingPage"
QT_MOC_LITERAL(92, 1117, 19), // "getPatrolArrivePage"
QT_MOC_LITERAL(93, 1137, 17), // "getPatrolWaitTime"
QT_MOC_LITERAL(94, 1155, 17), // "getPatrolPassTime"
QT_MOC_LITERAL(95, 1173, 14), // "getPatrolVoice"
QT_MOC_LITERAL(96, 1188, 18), // "getPatrolVoiceMode"
QT_MOC_LITERAL(97, 1207, 21), // "getPatrolVoiceMention"
QT_MOC_LITERAL(98, 1229, 22), // "getPatrolVoiceLanguage"
QT_MOC_LITERAL(99, 1252, 12), // "isPatrolPage"
QT_MOC_LITERAL(100, 1265, 19), // "getPatrolMovingMode"
QT_MOC_LITERAL(101, 1285, 19), // "getPatrolArriveMode"
QT_MOC_LITERAL(102, 1305, 16), // "setCurrentPatrol"
QT_MOC_LITERAL(103, 1322, 21), // "getPatrolLocationSize"
QT_MOC_LITERAL(104, 1344, 17), // "getPatrolLocation"
QT_MOC_LITERAL(105, 1362, 3), // "loc"
QT_MOC_LITERAL(106, 1366, 22), // "getPatrolLocationGroup"
QT_MOC_LITERAL(107, 1389, 19), // "clearPatrolLocation"
QT_MOC_LITERAL(108, 1409, 4), // "mode"
QT_MOC_LITERAL(109, 1414, 17), // "addPatrolLocation"
QT_MOC_LITERAL(110, 1432, 19), // "setPatrolMovingPage"
QT_MOC_LITERAL(111, 1452, 6), // "param1"
QT_MOC_LITERAL(112, 1459, 6), // "param2"
QT_MOC_LITERAL(113, 1466, 6), // "param3"
QT_MOC_LITERAL(114, 1473, 19), // "setPatrolArrivePage"
QT_MOC_LITERAL(115, 1493, 20), // "savePatrolVoiceBasic"
QT_MOC_LITERAL(116, 1514, 4), // "text"
QT_MOC_LITERAL(117, 1519, 14), // "setPatrolVoice"
QT_MOC_LITERAL(118, 1534, 8), // "language"
QT_MOC_LITERAL(119, 1543, 7), // "mention"
QT_MOC_LITERAL(120, 1551, 9), // "setPatrol"
QT_MOC_LITERAL(121, 1561, 4), // "type"
QT_MOC_LITERAL(122, 1566, 9), // "wait_time"
QT_MOC_LITERAL(123, 1576, 9), // "pass_time"
QT_MOC_LITERAL(124, 1586, 10), // "savePatrol"
QT_MOC_LITERAL(125, 1597, 12), // "deletePatrol"
QT_MOC_LITERAL(126, 1610, 11), // "startPatrol"
QT_MOC_LITERAL(127, 1622, 10), // "makeTTSAll"
QT_MOC_LITERAL(128, 1633, 10), // "setTTSMode"
QT_MOC_LITERAL(129, 1644, 11), // "setTTSVoice"
QT_MOC_LITERAL(130, 1656, 3), // "lan"
QT_MOC_LITERAL(131, 1660, 17), // "setTTSVoiceDetail"
QT_MOC_LITERAL(132, 1678, 5), // "speed"
QT_MOC_LITERAL(133, 1684, 5), // "pitch"
QT_MOC_LITERAL(134, 1690, 5), // "alpha"
QT_MOC_LITERAL(135, 1696, 7), // "emotion"
QT_MOC_LITERAL(136, 1704, 8), // "emostren"
QT_MOC_LITERAL(137, 1713, 13), // "clearTTSVoice"
QT_MOC_LITERAL(138, 1727, 12), // "saveTTSVoice"
QT_MOC_LITERAL(139, 1740, 13), // "makePatrolTTS"
QT_MOC_LITERAL(140, 1754, 4), // "play"
QT_MOC_LITERAL(141, 1759, 13), // "getTTSNameNum"
QT_MOC_LITERAL(142, 1773, 17), // "getTTSLanguageNum"
QT_MOC_LITERAL(143, 1791, 8), // "loadFile"
QT_MOC_LITERAL(144, 1800, 6), // "setMap"
QT_MOC_LITERAL(145, 1807, 13), // "setFullScreen"
QT_MOC_LITERAL(146, 1821, 13), // "setMapDrawing"
QT_MOC_LITERAL(147, 1835, 7), // "playBGM"
QT_MOC_LITERAL(148, 1843, 7), // "stopBGM"
QT_MOC_LITERAL(149, 1851, 9), // "isplayBGM"
QT_MOC_LITERAL(150, 1861, 12), // "setvolumeBGM"
QT_MOC_LITERAL(151, 1874, 11), // "getTTSSpeed"
QT_MOC_LITERAL(152, 1886, 11), // "getTTSPitch"
QT_MOC_LITERAL(153, 1898, 13), // "getTTSEmotion"
QT_MOC_LITERAL(154, 1912, 21), // "getTTSEmotionStrength"
QT_MOC_LITERAL(155, 1934, 11), // "getTTSAlpha"
QT_MOC_LITERAL(156, 1946, 12), // "getTTSVolume"
QT_MOC_LITERAL(157, 1959, 13), // "getTTSMention"
QT_MOC_LITERAL(158, 1973, 18), // "setTTSMentionBasic"
QT_MOC_LITERAL(159, 1992, 13), // "setTTSMention"
QT_MOC_LITERAL(160, 2006, 9), // "playVoice"
QT_MOC_LITERAL(161, 2016, 4), // "file"
QT_MOC_LITERAL(162, 2021, 11), // "getTTSVoice"
QT_MOC_LITERAL(163, 2033, 7), // "playTTS"
QT_MOC_LITERAL(164, 2041, 24), // "setServingPageBackground"
QT_MOC_LITERAL(165, 2066, 24), // "getServingPageBackground"
QT_MOC_LITERAL(166, 2091, 18), // "setServingPageMode"
QT_MOC_LITERAL(167, 2110, 18), // "getServingPageMode"
QT_MOC_LITERAL(168, 2129, 19), // "setServingPageColor"
QT_MOC_LITERAL(169, 2149, 19), // "getServingPageColor"
QT_MOC_LITERAL(170, 2169, 19), // "setServingPageImage"
QT_MOC_LITERAL(171, 2189, 19), // "getServingPageImage"
QT_MOC_LITERAL(172, 2209, 19), // "setServingPageVideo"
QT_MOC_LITERAL(173, 2229, 19), // "getServingPageVideo"
QT_MOC_LITERAL(174, 2249, 24), // "setServingPageVideoAudio"
QT_MOC_LITERAL(175, 2274, 24), // "getServingPageVideoAudio"
QT_MOC_LITERAL(176, 2299, 19), // "setServingPageAudio"
QT_MOC_LITERAL(177, 2319, 19), // "getServingPageAudio"
QT_MOC_LITERAL(178, 2339, 23), // "setMovingPageBackground"
QT_MOC_LITERAL(179, 2363, 23), // "getMovingPageBackground"
QT_MOC_LITERAL(180, 2387, 17), // "setMovingPageMode"
QT_MOC_LITERAL(181, 2405, 17), // "getMovingPageMode"
QT_MOC_LITERAL(182, 2423, 18), // "setMovingPageColor"
QT_MOC_LITERAL(183, 2442, 18), // "getMovingPageColor"
QT_MOC_LITERAL(184, 2461, 18), // "setMovingPageImage"
QT_MOC_LITERAL(185, 2480, 18), // "getMovingPageImage"
QT_MOC_LITERAL(186, 2499, 18), // "setMovingPageVideo"
QT_MOC_LITERAL(187, 2518, 18), // "getMovingPageVideo"
QT_MOC_LITERAL(188, 2537, 23), // "setMovingPageVideoAudio"
QT_MOC_LITERAL(189, 2561, 23), // "getMovingPageVideoAudio"
QT_MOC_LITERAL(190, 2585, 18), // "setMovingPageAudio"
QT_MOC_LITERAL(191, 2604, 18), // "getMovingPageAudio"
QT_MOC_LITERAL(192, 2623, 15), // "clearPatrolPage"
QT_MOC_LITERAL(193, 2639, 16), // "clearServingPage"
QT_MOC_LITERAL(194, 2656, 15), // "initServingPage"
QT_MOC_LITERAL(195, 2672, 15), // "saveServingPage"
QT_MOC_LITERAL(196, 2688, 14), // "savePatrolPage"
QT_MOC_LITERAL(197, 2703, 20), // "getServingObjectSize"
QT_MOC_LITERAL(198, 2724, 20), // "getServingObjectType"
QT_MOC_LITERAL(199, 2745, 22), // "getServingObjectSource"
QT_MOC_LITERAL(200, 2768, 21), // "getServingObjectColor"
QT_MOC_LITERAL(201, 2790, 17), // "getServingObjectX"
QT_MOC_LITERAL(202, 2808, 17), // "getServingObjectY"
QT_MOC_LITERAL(203, 2826, 21), // "getServingObjectWidth"
QT_MOC_LITERAL(204, 2848, 22), // "getServingObjectHeight"
QT_MOC_LITERAL(205, 2871, 24), // "getServingObjectFontsize"
QT_MOC_LITERAL(206, 2896, 16), // "addServingObject"
QT_MOC_LITERAL(207, 2913, 3), // "obj"
QT_MOC_LITERAL(208, 2917, 22), // "setServingObjectSource"
QT_MOC_LITERAL(209, 2940, 3), // "src"
QT_MOC_LITERAL(210, 2944, 21), // "setServingObjectColor"
QT_MOC_LITERAL(211, 2966, 5), // "color"
QT_MOC_LITERAL(212, 2972, 19), // "deleteServingObject"
QT_MOC_LITERAL(213, 2992, 17), // "moveServingObject"
QT_MOC_LITERAL(214, 3010, 1), // "x"
QT_MOC_LITERAL(215, 3012, 1), // "y"
QT_MOC_LITERAL(216, 3014, 20), // "setServingObjectSize"
QT_MOC_LITERAL(217, 3035, 5), // "point"
QT_MOC_LITERAL(218, 3041, 5), // "width"
QT_MOC_LITERAL(219, 3047, 6), // "height"
QT_MOC_LITERAL(220, 3054, 19), // "getServingObjectNum"
QT_MOC_LITERAL(221, 3074, 17), // "initCurrentPatrol"
QT_MOC_LITERAL(222, 3092, 19), // "getPatrolObjectSize"
QT_MOC_LITERAL(223, 3112, 17), // "getPageObjectType"
QT_MOC_LITERAL(224, 3130, 19), // "getPageObjectSource"
QT_MOC_LITERAL(225, 3150, 18), // "getPageObjectColor"
QT_MOC_LITERAL(226, 3169, 14), // "getPageObjectX"
QT_MOC_LITERAL(227, 3184, 14), // "getPageObjectY"
QT_MOC_LITERAL(228, 3199, 18), // "getPageObjectWidth"
QT_MOC_LITERAL(229, 3218, 19), // "getPageObjectHeight"
QT_MOC_LITERAL(230, 3238, 21), // "getPageObjectFontsize"
QT_MOC_LITERAL(231, 3260, 15), // "addPatrolObject"
QT_MOC_LITERAL(232, 3276, 19), // "setPageObjectSource"
QT_MOC_LITERAL(233, 3296, 18), // "setPageObjectColor"
QT_MOC_LITERAL(234, 3315, 18), // "deletePatrolObject"
QT_MOC_LITERAL(235, 3334, 16), // "movePatrolObject"
QT_MOC_LITERAL(236, 3351, 19), // "setPatrolObjectSize"
QT_MOC_LITERAL(237, 3371, 16), // "getPageObjectNum"
QT_MOC_LITERAL(238, 3388, 11), // "isExistNode"
QT_MOC_LITERAL(239, 3400, 19), // "confirmLocalization"
QT_MOC_LITERAL(240, 3420, 24), // "confirmLocalizationAnnot"
QT_MOC_LITERAL(241, 3445, 7), // "setName"
QT_MOC_LITERAL(242, 3453, 7), // "setTool"
QT_MOC_LITERAL(243, 3461, 7), // "getTool"
QT_MOC_LITERAL(244, 3469, 7), // "setMode"
QT_MOC_LITERAL(245, 3477, 9), // "setEnable"
QT_MOC_LITERAL(246, 3487, 2), // "en"
QT_MOC_LITERAL(247, 3490, 7), // "getMode"
QT_MOC_LITERAL(248, 3498, 12), // "setShowBrush"
QT_MOC_LITERAL(249, 3511, 5), // "onoff"
QT_MOC_LITERAL(250, 3517, 12), // "setShowLidar"
QT_MOC_LITERAL(251, 3530, 15), // "setShowLocation"
QT_MOC_LITERAL(252, 3546, 17), // "setRobotFollowing"
QT_MOC_LITERAL(253, 3564, 17), // "setShowTravelline"
QT_MOC_LITERAL(254, 3582, 18), // "setShowVelocitymap"
QT_MOC_LITERAL(255, 3601, 13), // "setShowObject"
QT_MOC_LITERAL(256, 3615, 11), // "setInitFlag"
QT_MOC_LITERAL(257, 3627, 15), // "getshowLocation"
QT_MOC_LITERAL(258, 3643, 17), // "getRobotFollowing"
QT_MOC_LITERAL(259, 3661, 12), // "getShowLidar"
QT_MOC_LITERAL(260, 3674, 15), // "setShowAvoidmap"
QT_MOC_LITERAL(261, 3690, 11), // "setShowNode"
QT_MOC_LITERAL(262, 3702, 11), // "getShowNode"
QT_MOC_LITERAL(263, 3714, 11), // "setShowName"
QT_MOC_LITERAL(264, 3726, 11), // "getShowName"
QT_MOC_LITERAL(265, 3738, 12), // "setShowTline"
QT_MOC_LITERAL(266, 3751, 12), // "getShowTline"
QT_MOC_LITERAL(267, 3764, 13), // "setShowVelmap"
QT_MOC_LITERAL(268, 3778, 13), // "getShowVelmap"
QT_MOC_LITERAL(269, 3792, 12), // "setShowAvoid"
QT_MOC_LITERAL(270, 3805, 12), // "getShowAvoid"
QT_MOC_LITERAL(271, 3818, 9), // "autoTline"
QT_MOC_LITERAL(272, 3828, 13), // "getShowObject"
QT_MOC_LITERAL(273, 3842, 11), // "setShowEdge"
QT_MOC_LITERAL(274, 3854, 11), // "getShowEdge"
QT_MOC_LITERAL(275, 3866, 11), // "setInitPose"
QT_MOC_LITERAL(276, 3878, 2), // "th"
QT_MOC_LITERAL(277, 3881, 13), // "clearInitPose"
QT_MOC_LITERAL(278, 3895, 20), // "getAnnotModifiedDate"
QT_MOC_LITERAL(279, 3916, 17), // "startDrawingTline"
QT_MOC_LITERAL(280, 3934, 16), // "stopDrawingTline"
QT_MOC_LITERAL(281, 3951, 15), // "getDrawingTline"
QT_MOC_LITERAL(282, 3967, 13), // "setRulerPoint"
QT_MOC_LITERAL(283, 3981, 11), // "setBoxPoint"
QT_MOC_LITERAL(284, 3993, 11), // "getPointBox"
QT_MOC_LITERAL(285, 4005, 13), // "saveRotateMap"
QT_MOC_LITERAL(286, 4019, 10), // "initRotate"
QT_MOC_LITERAL(287, 4030, 9), // "rotateMap"
QT_MOC_LITERAL(288, 4040, 5), // "angle"
QT_MOC_LITERAL(289, 4046, 11), // "rotateMapCW"
QT_MOC_LITERAL(290, 4058, 12), // "rotateMapCCW"
QT_MOC_LITERAL(291, 4071, 13), // "saveObjectPNG"
QT_MOC_LITERAL(292, 4085, 14), // "saveObsAreaPNG"
QT_MOC_LITERAL(293, 4100, 22), // "getLocalizationConfirm"
QT_MOC_LITERAL(294, 4123, 14), // "getDrawingFlag"
QT_MOC_LITERAL(295, 4138, 18), // "getDrawingUndoFlag"
QT_MOC_LITERAL(296, 4157, 12), // "startDrawing"
QT_MOC_LITERAL(297, 4170, 12), // "addLinePoint"
QT_MOC_LITERAL(298, 4183, 10), // "endDrawing"
QT_MOC_LITERAL(299, 4194, 11), // "startErase2"
QT_MOC_LITERAL(300, 4206, 9), // "addErase2"
QT_MOC_LITERAL(301, 4216, 9), // "endErase2"
QT_MOC_LITERAL(302, 4226, 10), // "setMapOrin"
QT_MOC_LITERAL(303, 4237, 16), // "startDrawingRect"
QT_MOC_LITERAL(304, 4254, 14), // "setDrawingRect"
QT_MOC_LITERAL(305, 4269, 14), // "endDrawingRect"
QT_MOC_LITERAL(306, 4284, 12), // "clearDrawing"
QT_MOC_LITERAL(307, 4297, 8), // "undoLine"
QT_MOC_LITERAL(308, 4306, 8), // "redoLine"
QT_MOC_LITERAL(309, 4315, 11), // "startSpline"
QT_MOC_LITERAL(310, 4327, 9), // "addSpline"
QT_MOC_LITERAL(311, 4337, 10), // "drawSpline"
QT_MOC_LITERAL(312, 4348, 9), // "endSpline"
QT_MOC_LITERAL(313, 4358, 4), // "save"
QT_MOC_LITERAL(314, 4363, 16), // "startDrawingLine"
QT_MOC_LITERAL(315, 4380, 14), // "setDrawingLine"
QT_MOC_LITERAL(316, 4395, 15), // "stopDrawingLine"
QT_MOC_LITERAL(317, 4411, 12), // "setLineColor"
QT_MOC_LITERAL(318, 4424, 12), // "setLineWidth"
QT_MOC_LITERAL(319, 4437, 7), // "pressed"
QT_MOC_LITERAL(320, 4445, 4), // "tool"
QT_MOC_LITERAL(321, 4450, 14), // "double_pressed"
QT_MOC_LITERAL(322, 4465, 2), // "x1"
QT_MOC_LITERAL(323, 4468, 2), // "y1"
QT_MOC_LITERAL(324, 4471, 2), // "x2"
QT_MOC_LITERAL(325, 4474, 2), // "y2"
QT_MOC_LITERAL(326, 4477, 5), // "moved"
QT_MOC_LITERAL(327, 4483, 12), // "double_moved"
QT_MOC_LITERAL(328, 4496, 8), // "released"
QT_MOC_LITERAL(329, 4505, 15), // "double_released"
QT_MOC_LITERAL(330, 4521, 14), // "getLocationNum"
QT_MOC_LITERAL(331, 4536, 12), // "saveLocation"
QT_MOC_LITERAL(332, 4549, 8), // "groupnum"
QT_MOC_LITERAL(333, 4558, 13), // "clearLocation"
QT_MOC_LITERAL(334, 4572, 11), // "addLocation"
QT_MOC_LITERAL(335, 4584, 14), // "addLocationCur"
QT_MOC_LITERAL(336, 4599, 11), // "setLocation"
QT_MOC_LITERAL(337, 4611, 12), // "editLocation"
QT_MOC_LITERAL(338, 4624, 14), // "removeLocation"
QT_MOC_LITERAL(339, 4639, 18), // "setTableNumberAuto"
QT_MOC_LITERAL(340, 4658, 14), // "getLocGroupNum"
QT_MOC_LITERAL(341, 4673, 7), // "saveMap"
QT_MOC_LITERAL(342, 4681, 13), // "saveEditedMap"
QT_MOC_LITERAL(343, 4695, 9), // "saveTline"
QT_MOC_LITERAL(344, 4705, 13), // "saveTlineTemp"
QT_MOC_LITERAL(345, 4719, 10), // "saveVelmap"
QT_MOC_LITERAL(346, 4730, 10), // "setMapSize"
QT_MOC_LITERAL(347, 4741, 14), // "loadAnnotation"
QT_MOC_LITERAL(348, 4756, 7), // "addNode"
QT_MOC_LITERAL(349, 4764, 4), // "attr"
QT_MOC_LITERAL(350, 4769, 8), // "editNode"
QT_MOC_LITERAL(351, 4778, 10), // "deleteNode"
QT_MOC_LITERAL(352, 4789, 8), // "linkNode"
QT_MOC_LITERAL(353, 4798, 9), // "alignNode"
QT_MOC_LITERAL(354, 4808, 1), // "n"
QT_MOC_LITERAL(355, 4810, 12), // "releaseShift"
QT_MOC_LITERAL(356, 4823, 10), // "pressShift"
QT_MOC_LITERAL(357, 4834, 6), // "zoomIn"
QT_MOC_LITERAL(358, 4841, 4), // "dist"
QT_MOC_LITERAL(359, 4846, 7), // "zoomOut"
QT_MOC_LITERAL(360, 4854, 4), // "move"
QT_MOC_LITERAL(361, 4859, 12), // "getFileWidth"
QT_MOC_LITERAL(362, 4872, 4), // "getX"
QT_MOC_LITERAL(363, 4877, 4), // "getY"
QT_MOC_LITERAL(364, 4882, 8), // "getScale"
QT_MOC_LITERAL(365, 4891, 13), // "setVelmapView"
QT_MOC_LITERAL(366, 4905, 12), // "setTlineView"
QT_MOC_LITERAL(367, 4918, 13), // "setObjectView"
QT_MOC_LITERAL(368, 4932, 15), // "setAvoidmapView"
QT_MOC_LITERAL(369, 4948, 15), // "setLocationView"
QT_MOC_LITERAL(370, 4964, 12), // "setRobotView"
QT_MOC_LITERAL(371, 4977, 15), // "setSystemVolume"
QT_MOC_LITERAL(372, 4993, 19), // "requestSystemVolume"
QT_MOC_LITERAL(373, 5013, 7), // "setSize"
QT_MOC_LITERAL(374, 5021, 13), // "getCutBoxFlag"
QT_MOC_LITERAL(375, 5035, 14), // "selectLocation"
QT_MOC_LITERAL(376, 5050, 8), // "writelog"
QT_MOC_LITERAL(377, 5059, 3), // "msg"
QT_MOC_LITERAL(378, 5063, 18), // "startDrawingObject"
QT_MOC_LITERAL(379, 5082, 17), // "stopDrawingObject"
QT_MOC_LITERAL(380, 5100, 17), // "saveDrawingObject"
QT_MOC_LITERAL(381, 5118, 13), // "setLocationUp"
QT_MOC_LITERAL(382, 5132, 15), // "setLocationDown"
QT_MOC_LITERAL(383, 5148, 8), // "checkINI"
QT_MOC_LITERAL(384, 5157, 8), // "killSLAM"
QT_MOC_LITERAL(385, 5166, 12), // "makeRobotINI"
QT_MOC_LITERAL(386, 5179, 13), // "checkRobotINI"
QT_MOC_LITERAL(387, 5193, 11), // "restartSLAM"
QT_MOC_LITERAL(388, 5205, 9), // "startSLAM"
QT_MOC_LITERAL(389, 5215, 16), // "getIPCConnection"
QT_MOC_LITERAL(390, 5232, 8), // "getIPCRX"
QT_MOC_LITERAL(391, 5241, 8), // "getIPCTX"
QT_MOC_LITERAL(392, 5250, 14), // "programRestart"
QT_MOC_LITERAL(393, 5265, 11), // "programExit"
QT_MOC_LITERAL(394, 5277, 13), // "getRawMapPath"
QT_MOC_LITERAL(395, 5291, 10), // "getMapPath"
QT_MOC_LITERAL(396, 5302, 12), // "getAnnotPath"
QT_MOC_LITERAL(397, 5315, 11), // "getMetaPath"
QT_MOC_LITERAL(398, 5327, 13), // "getTravelPath"
QT_MOC_LITERAL(399, 5341, 11), // "getCostPath"
QT_MOC_LITERAL(400, 5353, 10), // "getIniPath"
QT_MOC_LITERAL(401, 5364, 10), // "setSetting"
QT_MOC_LITERAL(402, 5375, 5), // "value"
QT_MOC_LITERAL(403, 5381, 11), // "readSetting"
QT_MOC_LITERAL(404, 5393, 8), // "map_name"
QT_MOC_LITERAL(405, 5402, 10), // "getSetting"
QT_MOC_LITERAL(406, 5413, 10), // "getTrayNum"
QT_MOC_LITERAL(407, 5424, 14), // "setTableColNum"
QT_MOC_LITERAL(408, 5439, 7), // "col_num"
QT_MOC_LITERAL(409, 5447, 12), // "getRobotType"
QT_MOC_LITERAL(410, 5460, 13), // "requestCamera"
QT_MOC_LITERAL(411, 5474, 13), // "getLeftCamera"
QT_MOC_LITERAL(412, 5488, 14), // "getRightCamera"
QT_MOC_LITERAL(413, 5503, 9), // "setCamera"
QT_MOC_LITERAL(414, 5513, 4), // "left"
QT_MOC_LITERAL(415, 5518, 5), // "right"
QT_MOC_LITERAL(416, 5524, 12), // "getCameraNum"
QT_MOC_LITERAL(417, 5537, 15), // "getCameraSerial"
QT_MOC_LITERAL(418, 5553, 13), // "setCursorView"
QT_MOC_LITERAL(419, 5567, 7), // "visible"
QT_MOC_LITERAL(420, 5575, 15), // "checkTravelline"
QT_MOC_LITERAL(421, 5591, 17), // "getNewServingName"
QT_MOC_LITERAL(422, 5609, 15), // "isDuplicateName"
QT_MOC_LITERAL(423, 5625, 13), // "updateProgram"
QT_MOC_LITERAL(424, 5639, 8), // "gitReset"
QT_MOC_LITERAL(425, 5648, 20), // "updateProgramGitPull"
QT_MOC_LITERAL(426, 5669, 17), // "checkVersionAgain"
QT_MOC_LITERAL(427, 5687, 12), // "isNewVersion"
QT_MOC_LITERAL(428, 5700, 12), // "isNeedUpdate"
QT_MOC_LITERAL(429, 5713, 15), // "getLocalVersion"
QT_MOC_LITERAL(430, 5729, 16), // "getServerVersion"
QT_MOC_LITERAL(431, 5746, 19), // "getLocalVersionDate"
QT_MOC_LITERAL(432, 5766, 22), // "getLocalVersionMessage"
QT_MOC_LITERAL(433, 5789, 23), // "getServerVersionMessage"
QT_MOC_LITERAL(434, 5813, 13), // "getUpdateDate"
QT_MOC_LITERAL(435, 5827, 13), // "getUpdateSize"
QT_MOC_LITERAL(436, 5841, 17), // "getUpdateFileName"
QT_MOC_LITERAL(437, 5859, 15), // "getUpdateCommit"
QT_MOC_LITERAL(438, 5875, 16), // "getCurrentCommit"
QT_MOC_LITERAL(439, 5892, 16), // "getUpdateMessage"
QT_MOC_LITERAL(440, 5909, 17), // "getLastUpdateDate"
QT_MOC_LITERAL(441, 5927, 21), // "checkCleaningLocation"
QT_MOC_LITERAL(442, 5949, 12), // "isRobotReady"
QT_MOC_LITERAL(443, 5962, 5), // "print"
QT_MOC_LITERAL(444, 5968, 11), // "checkUpdate"
QT_MOC_LITERAL(445, 5980, 21), // "checkNewUpdateProgram"
QT_MOC_LITERAL(446, 6002, 11), // "setlanguage"
QT_MOC_LITERAL(447, 6014, 13), // "isCallingMode"
QT_MOC_LITERAL(448, 6028, 12), // "startServing"
QT_MOC_LITERAL(449, 6041, 5), // "table"
QT_MOC_LITERAL(450, 6047, 11), // "getLocation"
QT_MOC_LITERAL(451, 6059, 8), // "LOCATION"
QT_MOC_LITERAL(452, 6068, 10), // "setUiState"
QT_MOC_LITERAL(453, 6079, 5), // "state"
QT_MOC_LITERAL(454, 6085, 11), // "clearStatus"
QT_MOC_LITERAL(455, 6097, 9), // "stateInit"
QT_MOC_LITERAL(456, 6107, 11), // "stateMoving"
QT_MOC_LITERAL(457, 6119, 17), // "resetLocalization"
QT_MOC_LITERAL(458, 6137, 24), // "resetLocalizationConfirm"
QT_MOC_LITERAL(459, 6162, 6), // "setLog"
QT_MOC_LITERAL(460, 6169, 13), // "getLogLineNum"
QT_MOC_LITERAL(461, 6183, 10), // "getLogLine"
QT_MOC_LITERAL(462, 6194, 10), // "getLogDate"
QT_MOC_LITERAL(463, 6205, 10), // "getLogAuth"
QT_MOC_LITERAL(464, 6216, 13), // "getLogMessage"
QT_MOC_LITERAL(465, 6230, 7), // "readLog"
QT_MOC_LITERAL(466, 6238, 4), // "date"
QT_MOC_LITERAL(467, 6243, 13), // "getLocaleDate"
QT_MOC_LITERAL(468, 6257, 4), // "year"
QT_MOC_LITERAL(469, 6262, 5), // "month"
QT_MOC_LITERAL(470, 6268, 9), // "updateUSB"
QT_MOC_LITERAL(471, 6278, 10), // "getusbsize"
QT_MOC_LITERAL(472, 6289, 17), // "readusbrecentfile"
QT_MOC_LITERAL(473, 6307, 14), // "getusbfilesize"
QT_MOC_LITERAL(474, 6322, 10), // "getusbfile"
QT_MOC_LITERAL(475, 6333, 16), // "getusbrecentfile"
QT_MOC_LITERAL(476, 6350, 10), // "getusbname"
QT_MOC_LITERAL(477, 6361, 7), // "readusb"
QT_MOC_LITERAL(478, 6369, 14), // "saveMapfromUsb"
QT_MOC_LITERAL(479, 6384, 4), // "path"
QT_MOC_LITERAL(480, 6389, 15), // "isConnectServer"
QT_MOC_LITERAL(481, 6405, 9), // "isLoadMap"
QT_MOC_LITERAL(482, 6415, 10), // "isExistMap"
QT_MOC_LITERAL(483, 6426, 13), // "isExistRawMap"
QT_MOC_LITERAL(484, 6440, 15), // "isExistTlineMap"
QT_MOC_LITERAL(485, 6456, 15), // "isExistAvoidMap"
QT_MOC_LITERAL(486, 6472, 13), // "isExistVelMap"
QT_MOC_LITERAL(487, 6486, 16), // "isExistObjectMap"
QT_MOC_LITERAL(488, 6503, 16), // "isExistTravelMap"
QT_MOC_LITERAL(489, 6520, 17), // "isExistAnnotation"
QT_MOC_LITERAL(490, 6538, 21), // "isAvailableAnnotation"
QT_MOC_LITERAL(491, 6560, 15), // "isExistRobotINI"
QT_MOC_LITERAL(492, 6576, 15), // "getAvailableMap"
QT_MOC_LITERAL(493, 6592, 19), // "getAvailableMapPath"
QT_MOC_LITERAL(494, 6612, 14), // "getMapFileSize"
QT_MOC_LITERAL(495, 6627, 10), // "getMapFile"
QT_MOC_LITERAL(496, 6638, 15), // "deleteEditedMap"
QT_MOC_LITERAL(497, 6654, 16), // "deleteAnnotation"
QT_MOC_LITERAL(498, 6671, 9), // "removeMap"
QT_MOC_LITERAL(499, 6681, 8), // "filename"
QT_MOC_LITERAL(500, 6690, 7), // "loadMap"
QT_MOC_LITERAL(501, 6698, 7), // "copyMap"
QT_MOC_LITERAL(502, 6706, 8), // "orinname"
QT_MOC_LITERAL(503, 6715, 7), // "newname"
QT_MOC_LITERAL(504, 6723, 10), // "rotate_map"
QT_MOC_LITERAL(505, 6734, 4), // "_src"
QT_MOC_LITERAL(506, 6739, 4), // "_dst"
QT_MOC_LITERAL(507, 6744, 12), // "startMapping"
QT_MOC_LITERAL(508, 6757, 7), // "mapsize"
QT_MOC_LITERAL(509, 6765, 4), // "grid"
QT_MOC_LITERAL(510, 6770, 11), // "stopMapping"
QT_MOC_LITERAL(511, 6782, 11), // "setSLAMMode"
QT_MOC_LITERAL(512, 6794, 11), // "saveMapping"
QT_MOC_LITERAL(513, 6806, 13), // "setInitCurPos"
QT_MOC_LITERAL(514, 6820, 10), // "setInitPos"
QT_MOC_LITERAL(515, 6831, 12), // "getInitPoseX"
QT_MOC_LITERAL(516, 6844, 12), // "getInitPoseY"
QT_MOC_LITERAL(517, 6857, 13), // "getInitPoseTH"
QT_MOC_LITERAL(518, 6871, 12), // "slam_setInit"
QT_MOC_LITERAL(519, 6884, 8), // "slam_run"
QT_MOC_LITERAL(520, 6893, 9), // "slam_stop"
QT_MOC_LITERAL(521, 6903, 13), // "slam_autoInit"
QT_MOC_LITERAL(522, 6917, 13), // "slam_restInit"
QT_MOC_LITERAL(523, 6931, 15), // "is_slam_running"
QT_MOC_LITERAL(524, 6947, 14), // "getMappingflag"
QT_MOC_LITERAL(525, 6962, 16), // "getObjectingflag"
QT_MOC_LITERAL(526, 6979, 16), // "setObjectingflag"
QT_MOC_LITERAL(527, 6996, 4), // "flag"
QT_MOC_LITERAL(528, 7001, 13), // "getnewMapname"
QT_MOC_LITERAL(529, 7015, 11), // "getLastCall"
QT_MOC_LITERAL(530, 7027, 11), // "getCallSize"
QT_MOC_LITERAL(531, 7039, 16), // "getCallQueueSize"
QT_MOC_LITERAL(532, 7056, 9), // "cleanTray"
QT_MOC_LITERAL(533, 7066, 11), // "getCallName"
QT_MOC_LITERAL(534, 7078, 14), // "clearCallQueue"
QT_MOC_LITERAL(535, 7093, 13), // "resetLingbell"
QT_MOC_LITERAL(536, 7107, 11), // "getLingbell"
QT_MOC_LITERAL(537, 7119, 7), // "getCall"
QT_MOC_LITERAL(538, 7127, 11), // "setCallbell"
QT_MOC_LITERAL(539, 7139, 16), // "setCallbellForce"
QT_MOC_LITERAL(540, 7156, 12), // "makeLingbell"
QT_MOC_LITERAL(541, 7169, 10), // "setObjPose"
QT_MOC_LITERAL(542, 7180, 14), // "getServingName"
QT_MOC_LITERAL(543, 7195, 15), // "getLocationName"
QT_MOC_LITERAL(544, 7211, 20), // "getLocationNameGroup"
QT_MOC_LITERAL(545, 7232, 15), // "getLocationType"
QT_MOC_LITERAL(546, 7248, 17), // "getLocationNumber"
QT_MOC_LITERAL(547, 7266, 17), // "setLocationNumber"
QT_MOC_LITERAL(548, 7284, 15), // "getLocationSize"
QT_MOC_LITERAL(549, 7300, 16), // "getLocationGroup"
QT_MOC_LITERAL(550, 7317, 13), // "getLocationID"
QT_MOC_LITERAL(551, 7331, 19), // "getLocationGroupNum"
QT_MOC_LITERAL(552, 7351, 20), // "getLocationGroupSize"
QT_MOC_LITERAL(553, 7372, 17), // "getLocationCallID"
QT_MOC_LITERAL(554, 7390, 17), // "getLocationLingID"
QT_MOC_LITERAL(555, 7408, 16), // "setLocationGroup"
QT_MOC_LITERAL(556, 7425, 19), // "removeLocationGroup"
QT_MOC_LITERAL(557, 7445, 16), // "addLocationGroup"
QT_MOC_LITERAL(558, 7462, 15), // "getLocGroupname"
QT_MOC_LITERAL(559, 7478, 8), // "tablenum"
QT_MOC_LITERAL(560, 7487, 12), // "getLocationX"
QT_MOC_LITERAL(561, 7500, 12), // "getLocationY"
QT_MOC_LITERAL(562, 7513, 13), // "getLocationTH"
QT_MOC_LITERAL(563, 7527, 15), // "isExistLocation"
QT_MOC_LITERAL(564, 7543, 8), // "getLidar"
QT_MOC_LITERAL(565, 7552, 16), // "getAnnotEditFlag"
QT_MOC_LITERAL(566, 7569, 16), // "setAnnotEditFlag"
QT_MOC_LITERAL(567, 7586, 17), // "clearSharedMemory"
QT_MOC_LITERAL(568, 7604, 12), // "getObjectNum"
QT_MOC_LITERAL(569, 7617, 13), // "getObjectName"
QT_MOC_LITERAL(570, 7631, 18), // "getObjectPointSize"
QT_MOC_LITERAL(571, 7650, 10), // "getObjectX"
QT_MOC_LITERAL(572, 7661, 10), // "getObjectY"
QT_MOC_LITERAL(573, 7672, 14), // "getObjPointNum"
QT_MOC_LITERAL(574, 7687, 7), // "obj_num"
QT_MOC_LITERAL(575, 7695, 9), // "getLocNum"
QT_MOC_LITERAL(576, 7705, 13), // "saveLocations"
QT_MOC_LITERAL(577, 7719, 13), // "getObjectSize"
QT_MOC_LITERAL(578, 7733, 12), // "removeObject"
QT_MOC_LITERAL(579, 7746, 14), // "saveAnnotation"
QT_MOC_LITERAL(580, 7761, 6), // "reload"
QT_MOC_LITERAL(581, 7768, 8), // "saveNode"
QT_MOC_LITERAL(582, 7777, 8), // "isOdroid"
QT_MOC_LITERAL(583, 7786, 13), // "getMultiState"
QT_MOC_LITERAL(584, 7800, 19), // "drawingRunawayStart"
QT_MOC_LITERAL(585, 7820, 18), // "drawingRunawayStop"
QT_MOC_LITERAL(586, 7839, 15), // "getRunawayState"
QT_MOC_LITERAL(587, 7855, 15), // "slam_map_reload"
QT_MOC_LITERAL(588, 7871, 15), // "slam_ini_reload"
QT_MOC_LITERAL(589, 7887, 7), // "setTray"
QT_MOC_LITERAL(590, 7895, 8), // "tray_num"
QT_MOC_LITERAL(591, 7904, 9), // "setPreset"
QT_MOC_LITERAL(592, 7914, 6), // "preset"
QT_MOC_LITERAL(593, 7921, 13), // "confirmPickup"
QT_MOC_LITERAL(594, 7935, 14), // "getPickuptrays"
QT_MOC_LITERAL(595, 7950, 10), // "QList<int>"
QT_MOC_LITERAL(596, 7961, 9), // "movePause"
QT_MOC_LITERAL(597, 7971, 10), // "moveResume"
QT_MOC_LITERAL(598, 7982, 12), // "moveStopFlag"
QT_MOC_LITERAL(599, 7995, 8), // "moveStop"
QT_MOC_LITERAL(600, 8004, 12), // "moveToCharge"
QT_MOC_LITERAL(601, 8017, 10), // "moveToWait"
QT_MOC_LITERAL(602, 8028, 14), // "moveToCleaning"
QT_MOC_LITERAL(603, 8043, 9), // "getcurLoc"
QT_MOC_LITERAL(604, 8053, 16), // "resetHomeFolders"
QT_MOC_LITERAL(605, 8070, 11), // "getObsState"
QT_MOC_LITERAL(606, 8082, 10), // "getBattery"
QT_MOC_LITERAL(607, 8093, 13), // "getMotorState"
QT_MOC_LITERAL(608, 8107, 20), // "getLocalizationState"
QT_MOC_LITERAL(609, 8128, 14), // "getStateMoving"
QT_MOC_LITERAL(610, 8143, 17), // "getStateMovingStr"
QT_MOC_LITERAL(611, 8161, 10), // "getErrcode"
QT_MOC_LITERAL(612, 8172, 12), // "getRobotName"
QT_MOC_LITERAL(613, 8185, 18), // "getMotorConnection"
QT_MOC_LITERAL(614, 8204, 14), // "getMotorStatus"
QT_MOC_LITERAL(615, 8219, 17), // "getMotorStatusStr"
QT_MOC_LITERAL(616, 8237, 19), // "getMotorTemperature"
QT_MOC_LITERAL(617, 8257, 25), // "getMotorInsideTemperature"
QT_MOC_LITERAL(618, 8283, 26), // "getMotorWarningTemperature"
QT_MOC_LITERAL(619, 8310, 15), // "getMotorCurrent"
QT_MOC_LITERAL(620, 8326, 14), // "getPowerStatus"
QT_MOC_LITERAL(621, 8341, 15), // "getRemoteStatus"
QT_MOC_LITERAL(622, 8357, 22), // "getChargeConnectStatus"
QT_MOC_LITERAL(623, 8380, 15), // "getChargeStatus"
QT_MOC_LITERAL(624, 8396, 12), // "getEmoStatus"
QT_MOC_LITERAL(625, 8409, 13), // "getLockStatus"
QT_MOC_LITERAL(626, 8423, 12), // "getBatteryIn"
QT_MOC_LITERAL(627, 8436, 13), // "getBatteryOut"
QT_MOC_LITERAL(628, 8450, 17), // "getBatteryCurrent"
QT_MOC_LITERAL(629, 8468, 8), // "getPower"
QT_MOC_LITERAL(630, 8477, 13), // "getPowerTotal"
QT_MOC_LITERAL(631, 8491, 12), // "getObsinPath"
QT_MOC_LITERAL(632, 8504, 17), // "getRobotcurPreset"
QT_MOC_LITERAL(633, 8522, 12), // "setMotorLock"
QT_MOC_LITERAL(634, 8535, 14), // "getRobotRadius"
QT_MOC_LITERAL(635, 8550, 9), // "getRobotx"
QT_MOC_LITERAL(636, 8560, 9), // "getRoboty"
QT_MOC_LITERAL(637, 8570, 10), // "getRobotth"
QT_MOC_LITERAL(638, 8581, 13), // "getlastRobotx"
QT_MOC_LITERAL(639, 8595, 13), // "getlastRoboty"
QT_MOC_LITERAL(640, 8609, 14), // "getlastRobotth"
QT_MOC_LITERAL(641, 8624, 10), // "getPathNum"
QT_MOC_LITERAL(642, 8635, 8), // "getPathx"
QT_MOC_LITERAL(643, 8644, 8), // "getPathy"
QT_MOC_LITERAL(644, 8653, 9), // "getPathth"
QT_MOC_LITERAL(645, 8663, 15), // "getLocalPathNum"
QT_MOC_LITERAL(646, 8679, 13), // "getLocalPathx"
QT_MOC_LITERAL(647, 8693, 13), // "getLocalPathy"
QT_MOC_LITERAL(648, 8707, 10), // "getuistate"
QT_MOC_LITERAL(649, 8718, 10), // "getMapname"
QT_MOC_LITERAL(650, 8729, 10), // "getMappath"
QT_MOC_LITERAL(651, 8740, 11), // "getMapWidth"
QT_MOC_LITERAL(652, 8752, 12), // "getMapHeight"
QT_MOC_LITERAL(653, 8765, 12), // "getGridWidth"
QT_MOC_LITERAL(654, 8778, 9), // "getOrigin"
QT_MOC_LITERAL(655, 8788, 15), // "getMappingWidth"
QT_MOC_LITERAL(656, 8804, 19), // "getMappingGridwidth"
QT_MOC_LITERAL(657, 8824, 17), // "getObjectPointNum"
QT_MOC_LITERAL(658, 8842, 9), // "addObject"
QT_MOC_LITERAL(659, 8852, 14), // "addObjectPoint"
QT_MOC_LITERAL(660, 8867, 9), // "setObject"
QT_MOC_LITERAL(661, 8877, 15), // "editObjectStart"
QT_MOC_LITERAL(662, 8893, 10), // "editObject"
QT_MOC_LITERAL(663, 8904, 10), // "saveObject"
QT_MOC_LITERAL(664, 8915, 11), // "clearObject"
QT_MOC_LITERAL(665, 8927, 14), // "clearObjectAll"
QT_MOC_LITERAL(666, 8942, 12), // "selectObject"
QT_MOC_LITERAL(667, 8955, 13), // "getObjectflag"
QT_MOC_LITERAL(668, 8969, 10), // "undoObject"
QT_MOC_LITERAL(669, 8980, 11), // "getICPRatio"
QT_MOC_LITERAL(670, 8992, 11), // "getICPError"
QT_MOC_LITERAL(671, 9004, 13), // "clearFlagStop"
QT_MOC_LITERAL(672, 9018, 17), // "slam_fullautoInit"
QT_MOC_LITERAL(673, 9036, 17), // "moveToServingTest"
QT_MOC_LITERAL(674, 9054, 15), // "getusberrorsize"
QT_MOC_LITERAL(675, 9070, 11), // "getusberror"
QT_MOC_LITERAL(676, 9082, 11), // "getzipstate"
QT_MOC_LITERAL(677, 9094, 10), // "clear_call"
QT_MOC_LITERAL(678, 9105, 7), // "usbsave"
QT_MOC_LITERAL(679, 9113, 3), // "usb"
QT_MOC_LITERAL(680, 9117, 3), // "_ui"
QT_MOC_LITERAL(681, 9121, 5), // "_slam"
QT_MOC_LITERAL(682, 9127, 7), // "_config"
QT_MOC_LITERAL(683, 9135, 4), // "_map"
QT_MOC_LITERAL(684, 9140, 4), // "_log"
QT_MOC_LITERAL(685, 9145, 13), // "restartUpdate"
QT_MOC_LITERAL(686, 9159, 11), // "startUpdate"
QT_MOC_LITERAL(687, 9171, 18), // "getTravellineIssue"
QT_MOC_LITERAL(688, 9190, 23), // "getTravellineIssueGroup"
QT_MOC_LITERAL(689, 9214, 22), // "getTravellineIssueName"
QT_MOC_LITERAL(690, 9237, 21), // "getTravellineIssueFar"
QT_MOC_LITERAL(691, 9259, 24) // "getTravellineIssueBroken"

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
    "sendMapServer\0checkGroupName\0"
    "checkLocationName\0group\0callCallbell\0"
    "id\0resetClear\0getWifiNum\0getWifiConnection\0"
    "getEthernetConnection\0getInternetConnection\0"
    "getCurWifiSSID\0getWifiSSID\0num\0"
    "connectWifi\0passwd\0getMasterVolume\0"
    "setMasterVolume\0volume\0getWifiSecurity\0"
    "getWifiLevel\0getWifiRate\0getWifiInuse\0"
    "getAllWifiList\0getWifiIP\0setWifiDHCP\0"
    "setWifi\0ip\0gateway\0dns\0subnet\0dns1\0"
    "dns2\0setEthernet\0getcurIP\0getcurGateway\0"
    "getcurNetmask\0getcurDNS2\0getcurDNS\0"
    "getethernetIP\0getethernetGateway\0"
    "getethernetNetmask\0getethernetDNS2\0"
    "getethernetDNS\0getcurIPMethod\0"
    "readWifiState\0getVolume\0getSystemVolume\0"
    "passInit\0isDebugMode\0loopClosing\0"
    "readPatrol\0getPatrolSize\0getPatrolVoiceNameNum\0"
    "getPatrolName\0getPatrolType\0"
    "getPatrolMovingPage\0getPatrolArrivePage\0"
    "getPatrolWaitTime\0getPatrolPassTime\0"
    "getPatrolVoice\0getPatrolVoiceMode\0"
    "getPatrolVoiceMention\0getPatrolVoiceLanguage\0"
    "isPatrolPage\0getPatrolMovingMode\0"
    "getPatrolArriveMode\0setCurrentPatrol\0"
    "getPatrolLocationSize\0getPatrolLocation\0"
    "loc\0getPatrolLocationGroup\0"
    "clearPatrolLocation\0mode\0addPatrolLocation\0"
    "setPatrolMovingPage\0param1\0param2\0"
    "param3\0setPatrolArrivePage\0"
    "savePatrolVoiceBasic\0text\0setPatrolVoice\0"
    "language\0mention\0setPatrol\0type\0"
    "wait_time\0pass_time\0savePatrol\0"
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
    "saveServingPage\0savePatrolPage\0"
    "getServingObjectSize\0getServingObjectType\0"
    "getServingObjectSource\0getServingObjectColor\0"
    "getServingObjectX\0getServingObjectY\0"
    "getServingObjectWidth\0getServingObjectHeight\0"
    "getServingObjectFontsize\0addServingObject\0"
    "obj\0setServingObjectSource\0src\0"
    "setServingObjectColor\0color\0"
    "deleteServingObject\0moveServingObject\0"
    "x\0y\0setServingObjectSize\0point\0width\0"
    "height\0getServingObjectNum\0initCurrentPatrol\0"
    "getPatrolObjectSize\0getPageObjectType\0"
    "getPageObjectSource\0getPageObjectColor\0"
    "getPageObjectX\0getPageObjectY\0"
    "getPageObjectWidth\0getPageObjectHeight\0"
    "getPageObjectFontsize\0addPatrolObject\0"
    "setPageObjectSource\0setPageObjectColor\0"
    "deletePatrolObject\0movePatrolObject\0"
    "setPatrolObjectSize\0getPageObjectNum\0"
    "isExistNode\0confirmLocalization\0"
    "confirmLocalizationAnnot\0setName\0"
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
    "loadAnnotation\0addNode\0attr\0editNode\0"
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
    "isRobotReady\0print\0checkUpdate\0"
    "checkNewUpdateProgram\0setlanguage\0"
    "isCallingMode\0startServing\0table\0"
    "getLocation\0LOCATION\0setUiState\0state\0"
    "clearStatus\0stateInit\0stateMoving\0"
    "resetLocalization\0resetLocalizationConfirm\0"
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
    "isExistAnnotation\0isAvailableAnnotation\0"
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
    "getCallName\0clearCallQueue\0resetLingbell\0"
    "getLingbell\0getCall\0setCallbell\0"
    "setCallbellForce\0makeLingbell\0setObjPose\0"
    "getServingName\0getLocationName\0"
    "getLocationNameGroup\0getLocationType\0"
    "getLocationNumber\0setLocationNumber\0"
    "getLocationSize\0getLocationGroup\0"
    "getLocationID\0getLocationGroupNum\0"
    "getLocationGroupSize\0getLocationCallID\0"
    "getLocationLingID\0setLocationGroup\0"
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
    "getcurLoc\0resetHomeFolders\0getObsState\0"
    "getBattery\0getMotorState\0getLocalizationState\0"
    "getStateMoving\0getStateMovingStr\0"
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
     650,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0, 3264,    2, 0x0a /* Public */,
       3,    0, 3265,    2, 0x0a /* Public */,
       4,    0, 3266,    2, 0x0a /* Public */,
       5,    0, 3267,    2, 0x0a /* Public */,
       6,    0, 3268,    2, 0x0a /* Public */,
       7,    1, 3269,    2, 0x0a /* Public */,
       9,    0, 3272,    2, 0x0a /* Public */,
      10,    0, 3273,    2, 0x0a /* Public */,
      11,    1, 3274,    2, 0x0a /* Public */,
      13,    1, 3277,    2, 0x0a /* Public */,
      14,    2, 3280,    2, 0x0a /* Public */,
      16,    1, 3285,    2, 0x0a /* Public */,
      17,    0, 3288,    2, 0x0a /* Public */,
      18,    0, 3289,    2, 0x0a /* Public */,
      19,    0, 3290,    2, 0x0a /* Public */,
      20,    0, 3291,    2, 0x0a /* Public */,
      21,    1, 3292,    2, 0x0a /* Public */,
      23,    1, 3295,    2, 0x0a /* Public */,
      26,    0, 3298,    2, 0x0a /* Public */,
      27,    2, 3299,    2, 0x0a /* Public */,
      29,    1, 3304,    2, 0x0a /* Public */,
      30,    1, 3307,    2, 0x0a /* Public */,
      31,    2, 3310,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      32,    1, 3315,    2, 0x02 /* Public */,
      34,    0, 3318,    2, 0x02 /* Public */,
      35,    0, 3319,    2, 0x02 /* Public */,
      36,    1, 3320,    2, 0x02 /* Public */,
      37,    2, 3323,    2, 0x02 /* Public */,
      39,    1, 3328,    2, 0x02 /* Public */,
      41,    0, 3331,    2, 0x02 /* Public */,
      42,    0, 3332,    2, 0x02 /* Public */,
      43,    0, 3333,    2, 0x02 /* Public */,
      44,    0, 3334,    2, 0x02 /* Public */,
      45,    0, 3335,    2, 0x02 /* Public */,
      46,    0, 3336,    2, 0x02 /* Public */,
      47,    1, 3337,    2, 0x02 /* Public */,
      49,    2, 3340,    2, 0x02 /* Public */,
      51,    0, 3345,    2, 0x02 /* Public */,
      52,    1, 3346,    2, 0x02 /* Public */,
      54,    1, 3349,    2, 0x02 /* Public */,
      55,    1, 3352,    2, 0x02 /* Public */,
      55,    0, 3355,    2, 0x02 /* Public */,
      56,    1, 3356,    2, 0x02 /* Public */,
      57,    1, 3359,    2, 0x02 /* Public */,
      58,    0, 3362,    2, 0x02 /* Public */,
      59,    0, 3363,    2, 0x02 /* Public */,
      60,    0, 3364,    2, 0x02 /* Public */,
      61,    3, 3365,    2, 0x02 /* Public */,
      61,    6, 3372,    2, 0x02 /* Public */,
      68,    5, 3385,    2, 0x02 /* Public */,
      69,    0, 3396,    2, 0x02 /* Public */,
      70,    0, 3397,    2, 0x02 /* Public */,
      71,    0, 3398,    2, 0x02 /* Public */,
      72,    0, 3399,    2, 0x02 /* Public */,
      73,    0, 3400,    2, 0x02 /* Public */,
      74,    0, 3401,    2, 0x02 /* Public */,
      75,    0, 3402,    2, 0x02 /* Public */,
      76,    0, 3403,    2, 0x02 /* Public */,
      77,    0, 3404,    2, 0x02 /* Public */,
      78,    0, 3405,    2, 0x02 /* Public */,
      79,    0, 3406,    2, 0x02 /* Public */,
      80,    1, 3407,    2, 0x02 /* Public */,
      81,    1, 3410,    2, 0x02 /* Public */,
      81,    1, 3413,    2, 0x02 /* Public */,
      82,    0, 3416,    2, 0x02 /* Public */,
      83,    0, 3417,    2, 0x02 /* Public */,
      84,    0, 3418,    2, 0x02 /* Public */,
      85,    0, 3419,    2, 0x02 /* Public */,
      86,    0, 3420,    2, 0x02 /* Public */,
      87,    0, 3421,    2, 0x02 /* Public */,
      88,    1, 3422,    2, 0x02 /* Public */,
      89,    1, 3425,    2, 0x02 /* Public */,
      90,    1, 3428,    2, 0x02 /* Public */,
      91,    1, 3431,    2, 0x02 /* Public */,
      92,    1, 3434,    2, 0x02 /* Public */,
      93,    1, 3437,    2, 0x02 /* Public */,
      94,    1, 3440,    2, 0x02 /* Public */,
      95,    1, 3443,    2, 0x02 /* Public */,
      96,    1, 3446,    2, 0x02 /* Public */,
      97,    1, 3449,    2, 0x02 /* Public */,
      98,    1, 3452,    2, 0x02 /* Public */,
      99,    0, 3455,    2, 0x02 /* Public */,
     100,    0, 3456,    2, 0x02 /* Public */,
     101,    0, 3457,    2, 0x02 /* Public */,
     102,    1, 3458,    2, 0x02 /* Public */,
     103,    1, 3461,    2, 0x02 /* Public */,
     104,    1, 3464,    2, 0x02 /* Public */,
     104,    2, 3467,    2, 0x02 /* Public */,
     106,    2, 3472,    2, 0x02 /* Public */,
     107,    1, 3477,    2, 0x02 /* Public */,
     109,    2, 3480,    2, 0x02 /* Public */,
     110,    4, 3485,    2, 0x02 /* Public */,
     110,    3, 3494,    2, 0x22 /* Public | MethodCloned */,
     110,    2, 3501,    2, 0x22 /* Public | MethodCloned */,
     110,    1, 3506,    2, 0x22 /* Public | MethodCloned */,
     114,    4, 3509,    2, 0x02 /* Public */,
     114,    3, 3518,    2, 0x22 /* Public | MethodCloned */,
     114,    2, 3525,    2, 0x22 /* Public | MethodCloned */,
     114,    1, 3530,    2, 0x22 /* Public | MethodCloned */,
     115,    2, 3533,    2, 0x02 /* Public */,
     117,    5, 3538,    2, 0x02 /* Public */,
     117,    4, 3549,    2, 0x22 /* Public | MethodCloned */,
     120,    5, 3558,    2, 0x02 /* Public */,
     124,    4, 3569,    2, 0x02 /* Public */,
     125,    1, 3578,    2, 0x02 /* Public */,
     126,    1, 3581,    2, 0x02 /* Public */,
     127,    0, 3584,    2, 0x02 /* Public */,
     128,    1, 3585,    2, 0x02 /* Public */,
     129,    2, 3588,    2, 0x02 /* Public */,
     131,    5, 3593,    2, 0x02 /* Public */,
     131,    4, 3604,    2, 0x22 /* Public | MethodCloned */,
     131,    3, 3613,    2, 0x22 /* Public | MethodCloned */,
     137,    2, 3620,    2, 0x02 /* Public */,
     138,    0, 3625,    2, 0x02 /* Public */,
     139,    4, 3626,    2, 0x02 /* Public */,
     139,    3, 3635,    2, 0x22 /* Public | MethodCloned */,
     141,    0, 3642,    2, 0x02 /* Public */,
     142,    0, 3643,    2, 0x02 /* Public */,
     143,    2, 3644,    2, 0x02 /* Public */,
     143,    0, 3649,    2, 0x02 /* Public */,
     144,    0, 3650,    2, 0x02 /* Public */,
     145,    0, 3651,    2, 0x02 /* Public */,
     146,    0, 3652,    2, 0x02 /* Public */,
     147,    1, 3653,    2, 0x02 /* Public */,
     147,    0, 3656,    2, 0x22 /* Public | MethodCloned */,
     148,    0, 3657,    2, 0x02 /* Public */,
     149,    0, 3658,    2, 0x02 /* Public */,
     150,    1, 3659,    2, 0x02 /* Public */,
     151,    0, 3662,    2, 0x02 /* Public */,
     152,    0, 3663,    2, 0x02 /* Public */,
     153,    0, 3664,    2, 0x02 /* Public */,
     154,    0, 3665,    2, 0x02 /* Public */,
     155,    0, 3666,    2, 0x02 /* Public */,
     156,    0, 3667,    2, 0x02 /* Public */,
     157,    1, 3668,    2, 0x02 /* Public */,
     158,    0, 3671,    2, 0x02 /* Public */,
     159,    2, 3672,    2, 0x02 /* Public */,
     160,    5, 3677,    2, 0x02 /* Public */,
     160,    4, 3688,    2, 0x22 /* Public | MethodCloned */,
     160,    3, 3697,    2, 0x22 /* Public | MethodCloned */,
     160,    2, 3704,    2, 0x22 /* Public | MethodCloned */,
     160,    1, 3709,    2, 0x22 /* Public | MethodCloned */,
     162,    2, 3712,    2, 0x02 /* Public */,
     163,    0, 3717,    2, 0x02 /* Public */,
     164,    1, 3718,    2, 0x02 /* Public */,
     165,    0, 3721,    2, 0x02 /* Public */,
     166,    1, 3722,    2, 0x02 /* Public */,
     167,    0, 3725,    2, 0x02 /* Public */,
     168,    1, 3726,    2, 0x02 /* Public */,
     169,    0, 3729,    2, 0x02 /* Public */,
     170,    1, 3730,    2, 0x02 /* Public */,
     171,    0, 3733,    2, 0x02 /* Public */,
     172,    1, 3734,    2, 0x02 /* Public */,
     173,    0, 3737,    2, 0x02 /* Public */,
     174,    1, 3738,    2, 0x02 /* Public */,
     175,    0, 3741,    2, 0x02 /* Public */,
     176,    1, 3742,    2, 0x02 /* Public */,
     177,    0, 3745,    2, 0x02 /* Public */,
     178,    1, 3746,    2, 0x02 /* Public */,
     179,    0, 3749,    2, 0x02 /* Public */,
     180,    1, 3750,    2, 0x02 /* Public */,
     181,    0, 3753,    2, 0x02 /* Public */,
     182,    1, 3754,    2, 0x02 /* Public */,
     183,    0, 3757,    2, 0x02 /* Public */,
     184,    1, 3758,    2, 0x02 /* Public */,
     185,    0, 3761,    2, 0x02 /* Public */,
     186,    1, 3762,    2, 0x02 /* Public */,
     187,    0, 3765,    2, 0x02 /* Public */,
     188,    1, 3766,    2, 0x02 /* Public */,
     189,    0, 3769,    2, 0x02 /* Public */,
     190,    1, 3770,    2, 0x02 /* Public */,
     191,    0, 3773,    2, 0x02 /* Public */,
     192,    1, 3774,    2, 0x02 /* Public */,
     193,    0, 3777,    2, 0x02 /* Public */,
     194,    0, 3778,    2, 0x02 /* Public */,
     195,    0, 3779,    2, 0x02 /* Public */,
     196,    0, 3780,    2, 0x02 /* Public */,
     197,    0, 3781,    2, 0x02 /* Public */,
     198,    1, 3782,    2, 0x02 /* Public */,
     199,    1, 3785,    2, 0x02 /* Public */,
     200,    1, 3788,    2, 0x02 /* Public */,
     201,    1, 3791,    2, 0x02 /* Public */,
     202,    1, 3794,    2, 0x02 /* Public */,
     203,    1, 3797,    2, 0x02 /* Public */,
     204,    1, 3800,    2, 0x02 /* Public */,
     205,    1, 3803,    2, 0x02 /* Public */,
     206,    2, 3806,    2, 0x02 /* Public */,
     208,    2, 3811,    2, 0x02 /* Public */,
     210,    2, 3816,    2, 0x02 /* Public */,
     212,    1, 3821,    2, 0x02 /* Public */,
     213,    3, 3824,    2, 0x02 /* Public */,
     216,    4, 3831,    2, 0x02 /* Public */,
     216,    5, 3840,    2, 0x02 /* Public */,
     220,    2, 3851,    2, 0x02 /* Public */,
     221,    0, 3856,    2, 0x02 /* Public */,
     222,    0, 3857,    2, 0x02 /* Public */,
     223,    1, 3858,    2, 0x02 /* Public */,
     224,    1, 3861,    2, 0x02 /* Public */,
     225,    1, 3864,    2, 0x02 /* Public */,
     226,    1, 3867,    2, 0x02 /* Public */,
     227,    1, 3870,    2, 0x02 /* Public */,
     228,    1, 3873,    2, 0x02 /* Public */,
     229,    1, 3876,    2, 0x02 /* Public */,
     230,    1, 3879,    2, 0x02 /* Public */,
     231,    2, 3882,    2, 0x02 /* Public */,
     232,    2, 3887,    2, 0x02 /* Public */,
     233,    2, 3892,    2, 0x02 /* Public */,
     234,    1, 3897,    2, 0x02 /* Public */,
     235,    3, 3900,    2, 0x02 /* Public */,
     236,    4, 3907,    2, 0x02 /* Public */,
     236,    5, 3916,    2, 0x02 /* Public */,
     237,    2, 3927,    2, 0x02 /* Public */,
     238,    1, 3932,    2, 0x02 /* Public */,
     239,    0, 3935,    2, 0x02 /* Public */,
     240,    0, 3936,    2, 0x02 /* Public */,
     241,    1, 3937,    2, 0x02 /* Public */,
     242,    1, 3940,    2, 0x02 /* Public */,
     243,    0, 3943,    2, 0x02 /* Public */,
     244,    1, 3944,    2, 0x02 /* Public */,
     245,    1, 3947,    2, 0x02 /* Public */,
     247,    0, 3950,    2, 0x02 /* Public */,
     248,    1, 3951,    2, 0x02 /* Public */,
     250,    1, 3954,    2, 0x02 /* Public */,
     251,    1, 3957,    2, 0x02 /* Public */,
     252,    1, 3960,    2, 0x02 /* Public */,
     253,    1, 3963,    2, 0x02 /* Public */,
     254,    1, 3966,    2, 0x02 /* Public */,
     255,    1, 3969,    2, 0x02 /* Public */,
     256,    1, 3972,    2, 0x02 /* Public */,
     257,    0, 3975,    2, 0x02 /* Public */,
     258,    0, 3976,    2, 0x02 /* Public */,
     259,    0, 3977,    2, 0x02 /* Public */,
     260,    1, 3978,    2, 0x02 /* Public */,
     261,    1, 3981,    2, 0x02 /* Public */,
     262,    0, 3984,    2, 0x02 /* Public */,
     263,    1, 3985,    2, 0x02 /* Public */,
     264,    0, 3988,    2, 0x02 /* Public */,
     265,    1, 3989,    2, 0x02 /* Public */,
     266,    0, 3992,    2, 0x02 /* Public */,
     267,    1, 3993,    2, 0x02 /* Public */,
     268,    0, 3996,    2, 0x02 /* Public */,
     269,    1, 3997,    2, 0x02 /* Public */,
     270,    0, 4000,    2, 0x02 /* Public */,
     271,    0, 4001,    2, 0x02 /* Public */,
     272,    0, 4002,    2, 0x02 /* Public */,
     273,    1, 4003,    2, 0x02 /* Public */,
     274,    0, 4006,    2, 0x02 /* Public */,
     275,    3, 4007,    2, 0x02 /* Public */,
     277,    0, 4014,    2, 0x02 /* Public */,
     278,    0, 4015,    2, 0x02 /* Public */,
     279,    0, 4016,    2, 0x02 /* Public */,
     280,    0, 4017,    2, 0x02 /* Public */,
     281,    0, 4018,    2, 0x02 /* Public */,
     282,    2, 4019,    2, 0x02 /* Public */,
     283,    3, 4024,    2, 0x02 /* Public */,
     284,    2, 4031,    2, 0x02 /* Public */,
     285,    0, 4036,    2, 0x02 /* Public */,
     286,    0, 4037,    2, 0x02 /* Public */,
     287,    1, 4038,    2, 0x02 /* Public */,
     289,    0, 4041,    2, 0x02 /* Public */,
     290,    0, 4042,    2, 0x02 /* Public */,
     291,    0, 4043,    2, 0x02 /* Public */,
     292,    0, 4044,    2, 0x02 /* Public */,
     293,    0, 4045,    2, 0x02 /* Public */,
     294,    0, 4046,    2, 0x02 /* Public */,
     295,    0, 4047,    2, 0x02 /* Public */,
     296,    2, 4048,    2, 0x02 /* Public */,
     297,    2, 4053,    2, 0x02 /* Public */,
     298,    2, 4058,    2, 0x02 /* Public */,
     299,    2, 4063,    2, 0x02 /* Public */,
     300,    2, 4068,    2, 0x02 /* Public */,
     301,    2, 4073,    2, 0x02 /* Public */,
     302,    1, 4078,    2, 0x02 /* Public */,
     303,    2, 4081,    2, 0x02 /* Public */,
     304,    2, 4086,    2, 0x02 /* Public */,
     305,    0, 4091,    2, 0x02 /* Public */,
     306,    0, 4092,    2, 0x02 /* Public */,
     307,    0, 4093,    2, 0x02 /* Public */,
     308,    0, 4094,    2, 0x02 /* Public */,
     309,    2, 4095,    2, 0x02 /* Public */,
     310,    2, 4100,    2, 0x02 /* Public */,
     311,    0, 4105,    2, 0x02 /* Public */,
     312,    1, 4106,    2, 0x02 /* Public */,
     314,    2, 4109,    2, 0x02 /* Public */,
     315,    2, 4114,    2, 0x02 /* Public */,
     316,    2, 4119,    2, 0x02 /* Public */,
     317,    1, 4124,    2, 0x02 /* Public */,
     318,    1, 4127,    2, 0x02 /* Public */,
     319,    3, 4130,    2, 0x02 /* Public */,
     321,    5, 4137,    2, 0x02 /* Public */,
     326,    3, 4148,    2, 0x02 /* Public */,
     327,    5, 4155,    2, 0x02 /* Public */,
     328,    3, 4166,    2, 0x02 /* Public */,
     329,    5, 4173,    2, 0x02 /* Public */,
     330,    2, 4184,    2, 0x02 /* Public */,
     331,    3, 4189,    2, 0x02 /* Public */,
     333,    0, 4196,    2, 0x02 /* Public */,
     334,    3, 4197,    2, 0x02 /* Public */,
     335,    3, 4204,    2, 0x02 /* Public */,
     336,    3, 4211,    2, 0x02 /* Public */,
     337,    1, 4218,    2, 0x02 /* Public */,
     330,    2, 4221,    2, 0x02 /* Public */,
     338,    1, 4226,    2, 0x02 /* Public */,
     339,    0, 4229,    2, 0x02 /* Public */,
     340,    1, 4230,    2, 0x02 /* Public */,
     341,    0, 4233,    2, 0x02 /* Public */,
     342,    0, 4234,    2, 0x02 /* Public */,
     343,    0, 4235,    2, 0x02 /* Public */,
     344,    0, 4236,    2, 0x02 /* Public */,
     345,    0, 4237,    2, 0x02 /* Public */,
     346,    3, 4238,    2, 0x02 /* Public */,
     347,    0, 4245,    2, 0x02 /* Public */,
     348,    2, 4246,    2, 0x02 /* Public */,
     348,    3, 4251,    2, 0x02 /* Public */,
     350,    0, 4258,    2, 0x02 /* Public */,
     350,    1, 4259,    2, 0x02 /* Public */,
     351,    0, 4262,    2, 0x02 /* Public */,
     352,    0, 4263,    2, 0x02 /* Public */,
     353,    1, 4264,    2, 0x02 /* Public */,
     355,    0, 4267,    2, 0x02 /* Public */,
     356,    0, 4268,    2, 0x02 /* Public */,
     357,    3, 4269,    2, 0x02 /* Public */,
     359,    3, 4276,    2, 0x02 /* Public */,
     360,    2, 4283,    2, 0x02 /* Public */,
     361,    0, 4288,    2, 0x02 /* Public */,
     362,    0, 4289,    2, 0x02 /* Public */,
     363,    0, 4290,    2, 0x02 /* Public */,
     364,    0, 4291,    2, 0x02 /* Public */,
     365,    1, 4292,    2, 0x02 /* Public */,
     366,    1, 4295,    2, 0x02 /* Public */,
     367,    1, 4298,    2, 0x02 /* Public */,
     368,    1, 4301,    2, 0x02 /* Public */,
     369,    1, 4304,    2, 0x02 /* Public */,
     370,    1, 4307,    2, 0x02 /* Public */,
     371,    1, 4310,    2, 0x02 /* Public */,
     372,    0, 4313,    2, 0x02 /* Public */,
     373,    3, 4314,    2, 0x02 /* Public */,
     374,    0, 4321,    2, 0x02 /* Public */,
     375,    1, 4322,    2, 0x02 /* Public */,
     376,    1, 4325,    2, 0x02 /* Public */,
     378,    0, 4328,    2, 0x02 /* Public */,
     379,    0, 4329,    2, 0x02 /* Public */,
     380,    0, 4330,    2, 0x02 /* Public */,
     381,    1, 4331,    2, 0x02 /* Public */,
     382,    1, 4334,    2, 0x02 /* Public */,
     383,    0, 4337,    2, 0x02 /* Public */,
     384,    0, 4338,    2, 0x02 /* Public */,
     385,    0, 4339,    2, 0x02 /* Public */,
     386,    0, 4340,    2, 0x02 /* Public */,
     387,    0, 4341,    2, 0x02 /* Public */,
     388,    0, 4342,    2, 0x02 /* Public */,
     389,    0, 4343,    2, 0x02 /* Public */,
     390,    0, 4344,    2, 0x02 /* Public */,
     391,    0, 4345,    2, 0x02 /* Public */,
     392,    0, 4346,    2, 0x02 /* Public */,
     393,    0, 4347,    2, 0x02 /* Public */,
     394,    1, 4348,    2, 0x02 /* Public */,
     395,    1, 4351,    2, 0x02 /* Public */,
     396,    1, 4354,    2, 0x02 /* Public */,
     397,    1, 4357,    2, 0x02 /* Public */,
     398,    1, 4360,    2, 0x02 /* Public */,
     399,    1, 4363,    2, 0x02 /* Public */,
     400,    1, 4366,    2, 0x02 /* Public */,
     401,    3, 4369,    2, 0x02 /* Public */,
     403,    1, 4376,    2, 0x02 /* Public */,
     403,    0, 4379,    2, 0x22 /* Public | MethodCloned */,
     405,    3, 4380,    2, 0x02 /* Public */,
     406,    0, 4387,    2, 0x02 /* Public */,
     407,    1, 4388,    2, 0x02 /* Public */,
     409,    0, 4391,    2, 0x02 /* Public */,
     410,    0, 4392,    2, 0x02 /* Public */,
     411,    0, 4393,    2, 0x02 /* Public */,
     412,    0, 4394,    2, 0x02 /* Public */,
     413,    2, 4395,    2, 0x02 /* Public */,
     416,    0, 4400,    2, 0x02 /* Public */,
     417,    1, 4401,    2, 0x02 /* Public */,
     418,    1, 4404,    2, 0x02 /* Public */,
     420,    0, 4407,    2, 0x02 /* Public */,
     421,    1, 4408,    2, 0x02 /* Public */,
     422,    2, 4411,    2, 0x02 /* Public */,
     423,    0, 4416,    2, 0x02 /* Public */,
     424,    0, 4417,    2, 0x02 /* Public */,
     425,    0, 4418,    2, 0x02 /* Public */,
     426,    0, 4419,    2, 0x02 /* Public */,
     427,    0, 4420,    2, 0x02 /* Public */,
     428,    0, 4421,    2, 0x02 /* Public */,
     429,    0, 4422,    2, 0x02 /* Public */,
     430,    0, 4423,    2, 0x02 /* Public */,
     431,    0, 4424,    2, 0x02 /* Public */,
     432,    0, 4425,    2, 0x02 /* Public */,
     433,    0, 4426,    2, 0x02 /* Public */,
     434,    0, 4427,    2, 0x02 /* Public */,
     435,    0, 4428,    2, 0x02 /* Public */,
     436,    1, 4429,    2, 0x02 /* Public */,
     437,    1, 4432,    2, 0x02 /* Public */,
     438,    1, 4435,    2, 0x02 /* Public */,
     439,    1, 4438,    2, 0x02 /* Public */,
     440,    1, 4441,    2, 0x02 /* Public */,
     441,    0, 4444,    2, 0x02 /* Public */,
     442,    1, 4445,    2, 0x02 /* Public */,
     442,    0, 4448,    2, 0x22 /* Public | MethodCloned */,
     444,    0, 4449,    2, 0x02 /* Public */,
     445,    0, 4450,    2, 0x02 /* Public */,
     446,    1, 4451,    2, 0x02 /* Public */,
     447,    0, 4454,    2, 0x02 /* Public */,
     448,    2, 4455,    2, 0x02 /* Public */,
     450,    2, 4460,    2, 0x02 /* Public */,
     450,    2, 4465,    2, 0x02 /* Public */,
     450,    1, 4470,    2, 0x02 /* Public */,
     452,    1, 4473,    2, 0x02 /* Public */,
     454,    0, 4476,    2, 0x02 /* Public */,
     455,    0, 4477,    2, 0x02 /* Public */,
     456,    0, 4478,    2, 0x02 /* Public */,
     457,    0, 4479,    2, 0x02 /* Public */,
     458,    0, 4480,    2, 0x02 /* Public */,
     459,    1, 4481,    2, 0x02 /* Public */,
     460,    0, 4484,    2, 0x02 /* Public */,
     461,    1, 4485,    2, 0x02 /* Public */,
     462,    1, 4488,    2, 0x02 /* Public */,
     463,    1, 4491,    2, 0x02 /* Public */,
     464,    1, 4494,    2, 0x02 /* Public */,
     465,    1, 4497,    2, 0x02 /* Public */,
     467,    3, 4500,    2, 0x02 /* Public */,
     470,    0, 4507,    2, 0x02 /* Public */,
     471,    0, 4508,    2, 0x02 /* Public */,
     472,    0, 4509,    2, 0x02 /* Public */,
     473,    0, 4510,    2, 0x02 /* Public */,
     474,    1, 4511,    2, 0x02 /* Public */,
     475,    0, 4514,    2, 0x02 /* Public */,
     476,    1, 4515,    2, 0x02 /* Public */,
     477,    0, 4518,    2, 0x02 /* Public */,
     478,    1, 4519,    2, 0x02 /* Public */,
     480,    0, 4522,    2, 0x02 /* Public */,
     481,    0, 4523,    2, 0x02 /* Public */,
     482,    1, 4524,    2, 0x02 /* Public */,
     482,    0, 4527,    2, 0x22 /* Public | MethodCloned */,
     483,    1, 4528,    2, 0x02 /* Public */,
     484,    1, 4531,    2, 0x02 /* Public */,
     484,    0, 4534,    2, 0x22 /* Public | MethodCloned */,
     485,    1, 4535,    2, 0x02 /* Public */,
     485,    0, 4538,    2, 0x22 /* Public | MethodCloned */,
     486,    1, 4539,    2, 0x02 /* Public */,
     486,    0, 4542,    2, 0x22 /* Public | MethodCloned */,
     487,    1, 4543,    2, 0x02 /* Public */,
     487,    0, 4546,    2, 0x22 /* Public | MethodCloned */,
     488,    1, 4547,    2, 0x02 /* Public */,
     489,    1, 4550,    2, 0x02 /* Public */,
     490,    0, 4553,    2, 0x02 /* Public */,
     491,    0, 4554,    2, 0x02 /* Public */,
     492,    0, 4555,    2, 0x02 /* Public */,
     493,    1, 4556,    2, 0x02 /* Public */,
     494,    1, 4559,    2, 0x02 /* Public */,
     495,    1, 4562,    2, 0x02 /* Public */,
     496,    0, 4565,    2, 0x02 /* Public */,
     497,    0, 4566,    2, 0x02 /* Public */,
     498,    1, 4567,    2, 0x02 /* Public */,
     500,    1, 4570,    2, 0x02 /* Public */,
     501,    2, 4573,    2, 0x02 /* Public */,
     144,    1, 4578,    2, 0x02 /* Public */,
     504,    3, 4581,    2, 0x02 /* Public */,
     507,    2, 4588,    2, 0x02 /* Public */,
     510,    0, 4593,    2, 0x02 /* Public */,
     511,    1, 4594,    2, 0x02 /* Public */,
     512,    1, 4597,    2, 0x02 /* Public */,
     513,    0, 4600,    2, 0x02 /* Public */,
     514,    3, 4601,    2, 0x02 /* Public */,
     515,    0, 4608,    2, 0x02 /* Public */,
     516,    0, 4609,    2, 0x02 /* Public */,
     517,    0, 4610,    2, 0x02 /* Public */,
     518,    0, 4611,    2, 0x02 /* Public */,
     519,    0, 4612,    2, 0x02 /* Public */,
     520,    0, 4613,    2, 0x02 /* Public */,
     521,    0, 4614,    2, 0x02 /* Public */,
     522,    0, 4615,    2, 0x02 /* Public */,
     523,    0, 4616,    2, 0x02 /* Public */,
     524,    0, 4617,    2, 0x02 /* Public */,
     525,    0, 4618,    2, 0x02 /* Public */,
     526,    1, 4619,    2, 0x02 /* Public */,
     528,    0, 4622,    2, 0x02 /* Public */,
     529,    0, 4623,    2, 0x02 /* Public */,
     530,    0, 4624,    2, 0x02 /* Public */,
     531,    0, 4625,    2, 0x02 /* Public */,
     532,    0, 4626,    2, 0x02 /* Public */,
     533,    1, 4627,    2, 0x02 /* Public */,
     534,    0, 4630,    2, 0x02 /* Public */,
     535,    1, 4631,    2, 0x02 /* Public */,
     536,    1, 4634,    2, 0x02 /* Public */,
     537,    1, 4637,    2, 0x02 /* Public */,
     538,    2, 4640,    2, 0x02 /* Public */,
     539,    2, 4645,    2, 0x02 /* Public */,
     540,    0, 4650,    2, 0x02 /* Public */,
     541,    0, 4651,    2, 0x02 /* Public */,
     542,    2, 4652,    2, 0x02 /* Public */,
     330,    1, 4657,    2, 0x02 /* Public */,
     330,    0, 4660,    2, 0x22 /* Public | MethodCloned */,
     543,    2, 4661,    2, 0x02 /* Public */,
     543,    1, 4666,    2, 0x22 /* Public | MethodCloned */,
     544,    2, 4669,    2, 0x02 /* Public */,
     544,    1, 4674,    2, 0x22 /* Public | MethodCloned */,
     545,    1, 4677,    2, 0x02 /* Public */,
     546,    2, 4680,    2, 0x02 /* Public */,
     547,    2, 4685,    2, 0x02 /* Public */,
     548,    1, 4690,    2, 0x02 /* Public */,
     549,    1, 4693,    2, 0x02 /* Public */,
     550,    2, 4696,    2, 0x02 /* Public */,
     551,    0, 4701,    2, 0x02 /* Public */,
     552,    1, 4702,    2, 0x02 /* Public */,
     551,    1, 4705,    2, 0x02 /* Public */,
     553,    1, 4708,    2, 0x02 /* Public */,
     554,    1, 4711,    2, 0x02 /* Public */,
     555,    2, 4714,    2, 0x02 /* Public */,
     556,    1, 4719,    2, 0x02 /* Public */,
     557,    1, 4722,    2, 0x02 /* Public */,
     558,    1, 4725,    2, 0x02 /* Public */,
     336,    4, 4728,    2, 0x02 /* Public */,
     560,    2, 4737,    2, 0x02 /* Public */,
     560,    1, 4742,    2, 0x22 /* Public | MethodCloned */,
     561,    2, 4745,    2, 0x02 /* Public */,
     561,    1, 4750,    2, 0x22 /* Public | MethodCloned */,
     562,    2, 4753,    2, 0x02 /* Public */,
     562,    1, 4758,    2, 0x22 /* Public | MethodCloned */,
     563,    2, 4761,    2, 0x02 /* Public */,
     564,    1, 4766,    2, 0x02 /* Public */,
     565,    0, 4769,    2, 0x02 /* Public */,
     566,    1, 4770,    2, 0x02 /* Public */,
     567,    0, 4773,    2, 0x02 /* Public */,
     568,    0, 4774,    2, 0x02 /* Public */,
     569,    1, 4775,    2, 0x02 /* Public */,
     570,    1, 4778,    2, 0x02 /* Public */,
     571,    2, 4781,    2, 0x02 /* Public */,
     572,    2, 4786,    2, 0x02 /* Public */,
     573,    3, 4791,    2, 0x02 /* Public */,
     575,    1, 4798,    2, 0x02 /* Public */,
     575,    2, 4801,    2, 0x02 /* Public */,
     576,    0, 4806,    2, 0x02 /* Public */,
     577,    1, 4807,    2, 0x02 /* Public */,
     578,    1, 4810,    2, 0x02 /* Public */,
     579,    2, 4813,    2, 0x02 /* Public */,
     579,    1, 4818,    2, 0x22 /* Public | MethodCloned */,
     581,    0, 4821,    2, 0x02 /* Public */,
     582,    0, 4822,    2, 0x02 /* Public */,
     583,    0, 4823,    2, 0x02 /* Public */,
     584,    0, 4824,    2, 0x02 /* Public */,
     585,    0, 4825,    2, 0x02 /* Public */,
     586,    0, 4826,    2, 0x02 /* Public */,
     587,    2, 4827,    2, 0x02 /* Public */,
     587,    1, 4832,    2, 0x22 /* Public | MethodCloned */,
     588,    0, 4835,    2, 0x02 /* Public */,
     589,    3, 4836,    2, 0x02 /* Public */,
     448,    0, 4843,    2, 0x02 /* Public */,
     591,    1, 4844,    2, 0x02 /* Public */,
     593,    0, 4847,    2, 0x02 /* Public */,
     594,    0, 4848,    2, 0x02 /* Public */,
     596,    0, 4849,    2, 0x02 /* Public */,
     597,    0, 4850,    2, 0x02 /* Public */,
     598,    0, 4851,    2, 0x02 /* Public */,
     599,    0, 4852,    2, 0x02 /* Public */,
     600,    0, 4853,    2, 0x02 /* Public */,
     601,    0, 4854,    2, 0x02 /* Public */,
     602,    0, 4855,    2, 0x02 /* Public */,
     603,    0, 4856,    2, 0x02 /* Public */,
     604,    0, 4857,    2, 0x02 /* Public */,
     605,    0, 4858,    2, 0x02 /* Public */,
     606,    0, 4859,    2, 0x02 /* Public */,
     607,    0, 4860,    2, 0x02 /* Public */,
     608,    0, 4861,    2, 0x02 /* Public */,
     609,    0, 4862,    2, 0x02 /* Public */,
     610,    0, 4863,    2, 0x02 /* Public */,
     611,    0, 4864,    2, 0x02 /* Public */,
     612,    0, 4865,    2, 0x02 /* Public */,
     613,    1, 4866,    2, 0x02 /* Public */,
     614,    1, 4869,    2, 0x02 /* Public */,
     615,    1, 4872,    2, 0x02 /* Public */,
     616,    1, 4875,    2, 0x02 /* Public */,
     617,    1, 4878,    2, 0x02 /* Public */,
     618,    0, 4881,    2, 0x02 /* Public */,
     619,    1, 4882,    2, 0x02 /* Public */,
     620,    0, 4885,    2, 0x02 /* Public */,
     621,    0, 4886,    2, 0x02 /* Public */,
     622,    0, 4887,    2, 0x02 /* Public */,
     623,    0, 4888,    2, 0x02 /* Public */,
     624,    0, 4889,    2, 0x02 /* Public */,
     625,    0, 4890,    2, 0x02 /* Public */,
     626,    0, 4891,    2, 0x02 /* Public */,
     627,    0, 4892,    2, 0x02 /* Public */,
     628,    0, 4893,    2, 0x02 /* Public */,
     629,    0, 4894,    2, 0x02 /* Public */,
     630,    0, 4895,    2, 0x02 /* Public */,
     631,    0, 4896,    2, 0x02 /* Public */,
     632,    0, 4897,    2, 0x02 /* Public */,
     633,    1, 4898,    2, 0x02 /* Public */,
     634,    0, 4901,    2, 0x02 /* Public */,
     635,    0, 4902,    2, 0x02 /* Public */,
     636,    0, 4903,    2, 0x02 /* Public */,
     637,    0, 4904,    2, 0x02 /* Public */,
     638,    0, 4905,    2, 0x02 /* Public */,
     639,    0, 4906,    2, 0x02 /* Public */,
     640,    0, 4907,    2, 0x02 /* Public */,
     641,    0, 4908,    2, 0x02 /* Public */,
     642,    1, 4909,    2, 0x02 /* Public */,
     643,    1, 4912,    2, 0x02 /* Public */,
     644,    1, 4915,    2, 0x02 /* Public */,
     645,    0, 4918,    2, 0x02 /* Public */,
     646,    1, 4919,    2, 0x02 /* Public */,
     647,    1, 4922,    2, 0x02 /* Public */,
     648,    0, 4925,    2, 0x02 /* Public */,
     649,    0, 4926,    2, 0x02 /* Public */,
     650,    0, 4927,    2, 0x02 /* Public */,
     651,    0, 4928,    2, 0x02 /* Public */,
     652,    0, 4929,    2, 0x02 /* Public */,
     653,    0, 4930,    2, 0x02 /* Public */,
     654,    0, 4931,    2, 0x02 /* Public */,
     655,    0, 4932,    2, 0x02 /* Public */,
     656,    0, 4933,    2, 0x02 /* Public */,
     568,    2, 4934,    2, 0x02 /* Public */,
     657,    2, 4939,    2, 0x02 /* Public */,
     658,    2, 4944,    2, 0x02 /* Public */,
     659,    2, 4949,    2, 0x02 /* Public */,
     660,    2, 4954,    2, 0x02 /* Public */,
     661,    2, 4959,    2, 0x02 /* Public */,
     662,    2, 4964,    2, 0x02 /* Public */,
     663,    0, 4969,    2, 0x02 /* Public */,
     664,    0, 4970,    2, 0x02 /* Public */,
     665,    0, 4971,    2, 0x02 /* Public */,
     666,    1, 4972,    2, 0x02 /* Public */,
     667,    0, 4975,    2, 0x02 /* Public */,
     668,    0, 4976,    2, 0x02 /* Public */,
     669,    0, 4977,    2, 0x02 /* Public */,
     670,    0, 4978,    2, 0x02 /* Public */,
     671,    0, 4979,    2, 0x02 /* Public */,
     672,    0, 4980,    2, 0x02 /* Public */,
     673,    2, 4981,    2, 0x02 /* Public */,
     674,    0, 4986,    2, 0x02 /* Public */,
     675,    1, 4987,    2, 0x02 /* Public */,
     676,    0, 4990,    2, 0x02 /* Public */,
     677,    0, 4991,    2, 0x02 /* Public */,
     678,    6, 4992,    2, 0x02 /* Public */,
     678,    5, 5005,    2, 0x22 /* Public | MethodCloned */,
     678,    4, 5016,    2, 0x22 /* Public | MethodCloned */,
     678,    3, 5025,    2, 0x22 /* Public | MethodCloned */,
     678,    2, 5032,    2, 0x22 /* Public | MethodCloned */,
     678,    1, 5037,    2, 0x22 /* Public | MethodCloned */,
     678,    0, 5040,    2, 0x22 /* Public | MethodCloned */,
     685,    0, 5041,    2, 0x02 /* Public */,
     686,    0, 5042,    2, 0x02 /* Public */,
     687,    0, 5043,    2, 0x02 /* Public */,
     688,    1, 5044,    2, 0x02 /* Public */,
     689,    1, 5047,    2, 0x02 /* Public */,
     690,    1, 5050,    2, 0x02 /* Public */,
     691,    1, 5053,    2, 0x02 /* Public */,

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
    QMetaType::Bool, QMetaType::QString,   22,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   38,   22,
    QMetaType::Void, QMetaType::QString,   40,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   28,   50,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Bool, QMetaType::QString,   28,
    QMetaType::Int, QMetaType::QString,   28,
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,   28,
    QMetaType::Bool, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   62,   63,   64,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   28,   62,   65,   63,   66,   67,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,   62,   65,   63,   66,   67,
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
    QMetaType::Int, QMetaType::Int,   53,
    QMetaType::Float, QMetaType::Float,   53,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Bool,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   48,  105,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   48,  105,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   38,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  108,  111,  112,  113,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  108,  111,  112,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  108,  111,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  108,  111,  112,  113,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  108,  111,  112,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  108,  111,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   25,  116,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  108,  118,   25,   53,  119,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  108,  118,   25,   53,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   48,   22,  121,  122,  123,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int, QMetaType::Int,   22,  121,  122,  123,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  130,   22,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  132,  133,  134,  135,  136,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  132,  133,  134,  135,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  132,  133,  134,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  130,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::Bool,  118,   25,  116,  140,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,  118,   25,  116,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   22,  121,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString, QMetaType::QString,  116,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  116,  119,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::Int,  161,   25,  108,  118,   53,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  161,   25,  108,  118,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  161,   25,  108,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  161,   25,
    QMetaType::Void, QMetaType::QString,  161,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,  130,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  161,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  161,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  161,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Float,   53,
    QMetaType::Float,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  161,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  161,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  161,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,  108,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Float,   53,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   33,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   48,  209,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   48,  211,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   48,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   48,  217,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   48,  214,  215,  218,  219,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   33,  207,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   48,  209,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   48,  211,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   48,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   48,  217,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   48,  214,  215,  218,  219,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Bool, QMetaType::QString,  121,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::Bool,  246,
    QMetaType::QString,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  276,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   48,  214,  215,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  288,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::QString,  121,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,  313,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int,  211,
    QMetaType::Void, QMetaType::Int,  218,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  320,  214,  215,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  320,  322,  323,  324,  325,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  320,  214,  215,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  320,  322,  323,  324,  325,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  320,  214,  215,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  320,  322,  323,  324,  325,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,   38,   22,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QString,  121,  332,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  276,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  276,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  276,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,  207,  218,  219,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   40,  349,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   22,   38,  349,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  349,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  354,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  358,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  358,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Void, QMetaType::Int,   53,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  218,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::QString,  377,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int,   48,
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
    QMetaType::QString, QMetaType::QString,  161,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,  161,   22,  402,
    QMetaType::Void, QMetaType::QString,  404,
    QMetaType::Void,
    QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,  161,   38,   22,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,  408,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,  414,  415,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Bool,  419,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,   38,
    QMetaType::Bool, QMetaType::Int, QMetaType::QString,   38,   22,
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
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Bool,  443,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,  130,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   38,  449,
    0x80000000 | 451, QMetaType::Int, QMetaType::QString,   38,   22,
    0x80000000 | 451, QMetaType::QString, QMetaType::QString,   38,   22,
    0x80000000 | 451, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::Int,  453,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::QDateTime,  466,
    QMetaType::QString, QMetaType::Int, QMetaType::Int, QMetaType::Int,  468,  469,  466,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  479,
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
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,  499,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Int, QMetaType::QString, QMetaType::QString,  502,  503,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::Int,  505,  506,  108,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,  508,  509,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  108,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Float,  214,  215,  276,
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
    QMetaType::Void, QMetaType::Bool,  527,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int,   40,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   40,
    QMetaType::QString, QMetaType::Int,   40,
    QMetaType::QString, QMetaType::Int,   40,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  121,   40,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  121,  249,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::QString, QMetaType::Int, QMetaType::Int,   38,   48,
    QMetaType::Int, QMetaType::QString,  121,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   48,  121,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int, QMetaType::QString,   48,  121,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   38,   48,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   22,   48,
    QMetaType::Int, QMetaType::QString,  121,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,   38,   48,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   48,   38,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::Int,   48,   22,   38,  559,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   48,  121,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   48,  121,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Float, QMetaType::Int, QMetaType::QString,   48,  121,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   38,   48,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::Bool,  527,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int, QMetaType::Int,   48,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   48,  217,
    QMetaType::Float, QMetaType::Int, QMetaType::Int,   48,  217,
    QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,  574,  214,  215,
    QMetaType::Int, QMetaType::QString,   22,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,  121,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Bool, QMetaType::QString, QMetaType::Bool,  499,  580,
    QMetaType::Bool, QMetaType::QString,  499,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,  499,  108,
    QMetaType::Void, QMetaType::QString,  499,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,  590,   38,  449,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,  592,
    QMetaType::Void,
    0x80000000 | 595,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QString,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::Bool, QMetaType::Int,   40,
    QMetaType::Int, QMetaType::Int,   40,
    QMetaType::QString, QMetaType::Int,   40,
    QMetaType::Int, QMetaType::Int,   40,
    QMetaType::Int, QMetaType::Int,   40,
    QMetaType::Int,
    QMetaType::Int, QMetaType::Int,   40,
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
    QMetaType::Void, QMetaType::Bool,  249,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Int,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Float, QMetaType::Int,   48,
    QMetaType::Int,
    QMetaType::QString,
    QMetaType::QString,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Float,
    0x80000000 | 595,
    QMetaType::Int,
    QMetaType::Float,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,  214,  215,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   48,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Float,
    QMetaType::Float,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   38,   22,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  679,  680,  681,  682,  683,  684,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  679,  680,  681,  682,  683,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,  679,  680,  681,  682,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool,  679,  680,  681,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,  679,  680,
    QMetaType::Void, QMetaType::QString,  679,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::QString, QMetaType::Int,   48,
    QMetaType::Bool, QMetaType::Int,   48,
    QMetaType::Bool, QMetaType::Int,   48,

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
        case 26: { bool _r = _t->checkGroupName((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { bool _r = _t->checkLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 28: _t->callCallbell((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 29: _t->resetClear(); break;
        case 30: { int _r = _t->getWifiNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 31: { int _r = _t->getWifiConnection();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 32: { int _r = _t->getEthernetConnection();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 33: { int _r = _t->getInternetConnection();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 34: { QString _r = _t->getCurWifiSSID();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 35: { QString _r = _t->getWifiSSID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 36: _t->connectWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 37: { int _r = _t->getMasterVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->setMasterVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: { bool _r = _t->getWifiSecurity((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 40: { int _r = _t->getWifiLevel((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 41: { int _r = _t->getWifiLevel();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 42: { int _r = _t->getWifiRate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 43: { bool _r = _t->getWifiInuse((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 44: _t->getAllWifiList(); break;
        case 45: _t->getWifiIP(); break;
        case 46: _t->setWifiDHCP(); break;
        case 47: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 48: _t->setWifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6]))); break;
        case 49: _t->setEthernet((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 50: { QString _r = _t->getcurIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 51: { QString _r = _t->getcurGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 52: { QString _r = _t->getcurNetmask();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 53: { QString _r = _t->getcurDNS2();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 54: { QString _r = _t->getcurDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 55: { QString _r = _t->getethernetIP();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 56: { QString _r = _t->getethernetGateway();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 57: { QString _r = _t->getethernetNetmask();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 58: { QString _r = _t->getethernetDNS2();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 59: { QString _r = _t->getethernetDNS();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 60: { QString _r = _t->getcurIPMethod();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 61: _t->readWifiState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 62: { int _r = _t->getVolume((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 63: { float _r = _t->getVolume((*reinterpret_cast< float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 64: { int _r = _t->getSystemVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 65: _t->passInit(); break;
        case 66: { bool _r = _t->isDebugMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 67: _t->loopClosing(); break;
        case 68: _t->readPatrol(); break;
        case 69: { int _r = _t->getPatrolSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 70: { int _r = _t->getPatrolVoiceNameNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 71: { QString _r = _t->getPatrolName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 72: { QString _r = _t->getPatrolType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 73: { QString _r = _t->getPatrolMovingPage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 74: { QString _r = _t->getPatrolArrivePage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 75: { int _r = _t->getPatrolWaitTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 76: { int _r = _t->getPatrolPassTime((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 77: { QString _r = _t->getPatrolVoice((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 78: { QString _r = _t->getPatrolVoiceMode((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 79: { QString _r = _t->getPatrolVoiceMention((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 80: { QString _r = _t->getPatrolVoiceLanguage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 81: { bool _r = _t->isPatrolPage();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 82: { QString _r = _t->getPatrolMovingMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 83: { QString _r = _t->getPatrolArriveMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 84: _t->setCurrentPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 85: { int _r = _t->getPatrolLocationSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 86: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 87: { QString _r = _t->getPatrolLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 88: { QString _r = _t->getPatrolLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 89: _t->clearPatrolLocation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 90: _t->addPatrolLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 91: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 92: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 93: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 94: _t->setPatrolMovingPage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 95: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 96: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 97: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 98: _t->setPatrolArrivePage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 99: _t->savePatrolVoiceBasic((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 100: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 101: _t->setPatrolVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 102: _t->setPatrol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 103: _t->savePatrol((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 104: _t->deletePatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 105: _t->startPatrol((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 106: _t->makeTTSAll(); break;
        case 107: _t->setTTSMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 108: _t->setTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 109: _t->setTTSVoiceDetail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 110: _t->setTTSVoiceDetail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 111: _t->setTTSVoiceDetail((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 112: _t->clearTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 113: _t->saveTTSVoice(); break;
        case 114: _t->makePatrolTTS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 115: _t->makePatrolTTS((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 116: { int _r = _t->getTTSNameNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 117: { int _r = _t->getTTSLanguageNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 118: _t->loadFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 119: _t->loadFile(); break;
        case 120: _t->setMap(); break;
        case 121: _t->setFullScreen(); break;
        case 122: _t->setMapDrawing(); break;
        case 123: _t->playBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 124: _t->playBGM(); break;
        case 125: _t->stopBGM(); break;
        case 126: { bool _r = _t->isplayBGM();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 127: _t->setvolumeBGM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 128: { int _r = _t->getTTSSpeed();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 129: { int _r = _t->getTTSPitch();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 130: { int _r = _t->getTTSEmotion();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 131: { int _r = _t->getTTSEmotionStrength();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 132: { int _r = _t->getTTSAlpha();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 133: { int _r = _t->getTTSVolume();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 134: { QString _r = _t->getTTSMention((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 135: _t->setTTSMentionBasic(); break;
        case 136: _t->setTTSMention((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 137: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 138: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 139: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 140: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 141: _t->playVoice((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 142: { QString _r = _t->getTTSVoice((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 143: _t->playTTS(); break;
        case 144: _t->setServingPageBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 145: { QString _r = _t->getServingPageBackground();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 146: _t->setServingPageMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 147: { QString _r = _t->getServingPageMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 148: _t->setServingPageColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 149: { QString _r = _t->getServingPageColor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 150: _t->setServingPageImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 151: { QString _r = _t->getServingPageImage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 152: _t->setServingPageVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 153: { QString _r = _t->getServingPageVideo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 154: _t->setServingPageVideoAudio((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 155: { QString _r = _t->getServingPageVideoAudio();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 156: _t->setServingPageAudio((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 157: { float _r = _t->getServingPageAudio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 158: _t->setMovingPageBackground((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 159: { QString _r = _t->getMovingPageBackground();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 160: _t->setMovingPageMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 161: { QString _r = _t->getMovingPageMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 162: _t->setMovingPageColor((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 163: { QString _r = _t->getMovingPageColor();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 164: _t->setMovingPageImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 165: { QString _r = _t->getMovingPageImage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 166: _t->setMovingPageVideo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 167: { QString _r = _t->getMovingPageVideo();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 168: _t->setMovingPageVideoAudio((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 169: { QString _r = _t->getMovingPageVideoAudio();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 170: _t->setMovingPageAudio((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 171: { float _r = _t->getMovingPageAudio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 172: _t->clearPatrolPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 173: _t->clearServingPage(); break;
        case 174: _t->initServingPage(); break;
        case 175: _t->saveServingPage(); break;
        case 176: _t->savePatrolPage(); break;
        case 177: { int _r = _t->getServingObjectSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 178: { QString _r = _t->getServingObjectType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 179: { QString _r = _t->getServingObjectSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 180: { QString _r = _t->getServingObjectColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 181: { int _r = _t->getServingObjectX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 182: { int _r = _t->getServingObjectY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 183: { int _r = _t->getServingObjectWidth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 184: { int _r = _t->getServingObjectHeight((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 185: { int _r = _t->getServingObjectFontsize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 186: _t->addServingObject((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 187: _t->setServingObjectSource((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 188: _t->setServingObjectColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 189: _t->deleteServingObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 190: _t->moveServingObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 191: _t->setServingObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 192: _t->setServingObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 193: { int _r = _t->getServingObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 194: _t->initCurrentPatrol(); break;
        case 195: { int _r = _t->getPatrolObjectSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 196: { QString _r = _t->getPageObjectType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 197: { QString _r = _t->getPageObjectSource((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 198: { QString _r = _t->getPageObjectColor((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 199: { int _r = _t->getPageObjectX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 200: { int _r = _t->getPageObjectY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 201: { int _r = _t->getPageObjectWidth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 202: { int _r = _t->getPageObjectHeight((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 203: { int _r = _t->getPageObjectFontsize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 204: _t->addPatrolObject((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 205: _t->setPageObjectSource((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 206: _t->setPageObjectColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 207: _t->deletePatrolObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 208: _t->movePatrolObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 209: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 210: _t->setPatrolObjectSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 211: { int _r = _t->getPageObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 212: { bool _r = _t->isExistNode((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 213: _t->confirmLocalization(); break;
        case 214: _t->confirmLocalizationAnnot(); break;
        case 215: _t->setName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 216: _t->setTool((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 217: { QString _r = _t->getTool();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 218: _t->setMode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 219: _t->setEnable((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 220: { QString _r = _t->getMode();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 221: _t->setShowBrush((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 222: _t->setShowLidar((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 223: _t->setShowLocation((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 224: _t->setRobotFollowing((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 225: _t->setShowTravelline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 226: _t->setShowVelocitymap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 227: _t->setShowObject((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 228: _t->setInitFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 229: { bool _r = _t->getshowLocation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 230: { bool _r = _t->getRobotFollowing();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 231: { bool _r = _t->getShowLidar();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 232: _t->setShowAvoidmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 233: _t->setShowNode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 234: { bool _r = _t->getShowNode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 235: _t->setShowName((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 236: { bool _r = _t->getShowName();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 237: _t->setShowTline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 238: { bool _r = _t->getShowTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 239: _t->setShowVelmap((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 240: { bool _r = _t->getShowVelmap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 241: _t->setShowAvoid((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 242: { bool _r = _t->getShowAvoid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 243: _t->autoTline(); break;
        case 244: { bool _r = _t->getShowObject();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 245: _t->setShowEdge((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 246: { bool _r = _t->getShowEdge();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 247: _t->setInitPose((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 248: _t->clearInitPose(); break;
        case 249: { QString _r = _t->getAnnotModifiedDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 250: _t->startDrawingTline(); break;
        case 251: _t->stopDrawingTline(); break;
        case 252: { bool _r = _t->getDrawingTline();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 253: _t->setRulerPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 254: _t->setBoxPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 255: { int _r = _t->getPointBox((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 256: _t->saveRotateMap(); break;
        case 257: _t->initRotate(); break;
        case 258: _t->rotateMap((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 259: _t->rotateMapCW(); break;
        case 260: _t->rotateMapCCW(); break;
        case 261: _t->saveObjectPNG(); break;
        case 262: _t->saveObsAreaPNG(); break;
        case 263: { bool _r = _t->getLocalizationConfirm();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 264: { bool _r = _t->getDrawingFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 265: { bool _r = _t->getDrawingUndoFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 266: _t->startDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 267: _t->addLinePoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 268: _t->endDrawing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 269: _t->startErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 270: _t->addErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 271: _t->endErase2((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 272: _t->setMapOrin((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 273: _t->startDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 274: _t->setDrawingRect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 275: _t->endDrawingRect(); break;
        case 276: _t->clearDrawing(); break;
        case 277: _t->undoLine(); break;
        case 278: _t->redoLine(); break;
        case 279: _t->startSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 280: _t->addSpline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 281: _t->drawSpline(); break;
        case 282: _t->endSpline((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 283: _t->startDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 284: _t->setDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 285: _t->stopDrawingLine((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 286: _t->setLineColor((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 287: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 288: _t->pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 289: _t->double_pressed((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 290: _t->moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 291: _t->double_moved((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 292: _t->released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 293: _t->double_released((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 294: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 295: _t->saveLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 296: _t->clearLocation(); break;
        case 297: _t->addLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 298: _t->addLocationCur((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 299: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 300: _t->editLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 301: { int _r = _t->getLocationNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 302: _t->removeLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 303: _t->setTableNumberAuto(); break;
        case 304: { int _r = _t->getLocGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 305: _t->saveMap(); break;
        case 306: _t->saveEditedMap(); break;
        case 307: _t->saveTline(); break;
        case 308: _t->saveTlineTemp(); break;
        case 309: _t->saveVelmap(); break;
        case 310: _t->setMapSize((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 311: _t->loadAnnotation(); break;
        case 312: _t->addNode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 313: _t->addNode((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 314: _t->editNode(); break;
        case 315: _t->editNode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 316: _t->deleteNode(); break;
        case 317: _t->linkNode(); break;
        case 318: _t->alignNode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 319: _t->releaseShift(); break;
        case 320: _t->pressShift(); break;
        case 321: _t->zoomIn((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 322: _t->zoomOut((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 323: _t->move((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 324: { int _r = _t->getFileWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 325: { int _r = _t->getX();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 326: { int _r = _t->getY();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 327: { float _r = _t->getScale();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 328: _t->setVelmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 329: _t->setTlineView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 330: _t->setObjectView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 331: _t->setAvoidmapView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 332: _t->setLocationView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 333: _t->setRobotView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 334: _t->setSystemVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 335: _t->requestSystemVolume(); break;
        case 336: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 337: { bool _r = _t->getCutBoxFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 338: _t->selectLocation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 339: _t->writelog((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 340: _t->startDrawingObject(); break;
        case 341: _t->stopDrawingObject(); break;
        case 342: _t->saveDrawingObject(); break;
        case 343: _t->setLocationUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 344: _t->setLocationDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 345: { bool _r = _t->checkINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 346: _t->killSLAM(); break;
        case 347: _t->makeRobotINI(); break;
        case 348: _t->checkRobotINI(); break;
        case 349: _t->restartSLAM(); break;
        case 350: _t->startSLAM(); break;
        case 351: { bool _r = _t->getIPCConnection();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 352: { bool _r = _t->getIPCRX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 353: { bool _r = _t->getIPCTX();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 354: _t->programRestart(); break;
        case 355: _t->programExit(); break;
        case 356: { QString _r = _t->getRawMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 357: { QString _r = _t->getMapPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 358: { QString _r = _t->getAnnotPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 359: { QString _r = _t->getMetaPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 360: { QString _r = _t->getTravelPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 361: { QString _r = _t->getCostPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 362: { QString _r = _t->getIniPath((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 363: _t->setSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 364: _t->readSetting((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 365: _t->readSetting(); break;
        case 366: { QString _r = _t->getSetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 367: { int _r = _t->getTrayNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 368: _t->setTableColNum((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 369: { QString _r = _t->getRobotType();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 370: _t->requestCamera(); break;
        case 371: { QString _r = _t->getLeftCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 372: { QString _r = _t->getRightCamera();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 373: _t->setCamera((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 374: { int _r = _t->getCameraNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 375: { QString _r = _t->getCameraSerial((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 376: _t->setCursorView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 377: _t->checkTravelline(); break;
        case 378: { QString _r = _t->getNewServingName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 379: { bool _r = _t->isDuplicateName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 380: _t->updateProgram(); break;
        case 381: _t->gitReset(); break;
        case 382: _t->updateProgramGitPull(); break;
        case 383: _t->checkVersionAgain(); break;
        case 384: { bool _r = _t->isNewVersion();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 385: { bool _r = _t->isNeedUpdate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 386: { QString _r = _t->getLocalVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 387: { QString _r = _t->getServerVersion();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 388: { QString _r = _t->getLocalVersionDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 389: { QString _r = _t->getLocalVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 390: { QString _r = _t->getServerVersionMessage();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 391: { QString _r = _t->getUpdateDate();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 392: { int _r = _t->getUpdateSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 393: { QString _r = _t->getUpdateFileName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 394: { QString _r = _t->getUpdateCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 395: { QString _r = _t->getCurrentCommit((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 396: { QString _r = _t->getUpdateMessage((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 397: { QString _r = _t->getLastUpdateDate((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 398: _t->checkCleaningLocation(); break;
        case 399: { bool _r = _t->isRobotReady((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 400: { bool _r = _t->isRobotReady();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 401: _t->checkUpdate(); break;
        case 402: { bool _r = _t->checkNewUpdateProgram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 403: _t->setlanguage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 404: { bool _r = _t->isCallingMode();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 405: _t->startServing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 406: { LOCATION _r = _t->getLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 407: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 408: { LOCATION _r = _t->getLocation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< LOCATION*>(_a[0]) = std::move(_r); }  break;
        case 409: _t->setUiState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 410: _t->clearStatus(); break;
        case 411: _t->stateInit(); break;
        case 412: _t->stateMoving(); break;
        case 413: _t->resetLocalization(); break;
        case 414: _t->resetLocalizationConfirm(); break;
        case 415: _t->setLog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 416: { int _r = _t->getLogLineNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 417: { QString _r = _t->getLogLine((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 418: { QString _r = _t->getLogDate((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 419: { QString _r = _t->getLogAuth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 420: { QString _r = _t->getLogMessage((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 421: _t->readLog((*reinterpret_cast< QDateTime(*)>(_a[1]))); break;
        case 422: { QString _r = _t->getLocaleDate((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 423: _t->updateUSB(); break;
        case 424: { int _r = _t->getusbsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 425: _t->readusbrecentfile(); break;
        case 426: { int _r = _t->getusbfilesize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 427: { QString _r = _t->getusbfile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 428: { QString _r = _t->getusbrecentfile();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 429: { QString _r = _t->getusbname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 430: _t->readusb(); break;
        case 431: _t->saveMapfromUsb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 432: { bool _r = _t->isConnectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 433: { bool _r = _t->isLoadMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 434: { bool _r = _t->isExistMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 435: { bool _r = _t->isExistMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 436: { bool _r = _t->isExistRawMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 437: { bool _r = _t->isExistTlineMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 438: { bool _r = _t->isExistTlineMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 439: { bool _r = _t->isExistAvoidMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 440: { bool _r = _t->isExistAvoidMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 441: { bool _r = _t->isExistVelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 442: { bool _r = _t->isExistVelMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 443: { bool _r = _t->isExistObjectMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 444: { bool _r = _t->isExistObjectMap();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 445: { bool _r = _t->isExistTravelMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 446: { bool _r = _t->isExistAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 447: { bool _r = _t->isAvailableAnnotation();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 448: { bool _r = _t->isExistRobotINI();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 449: { int _r = _t->getAvailableMap();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 450: { QString _r = _t->getAvailableMapPath((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 451: { int _r = _t->getMapFileSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 452: { QString _r = _t->getMapFile((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 453: _t->deleteEditedMap(); break;
        case 454: _t->deleteAnnotation(); break;
        case 455: _t->removeMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 456: _t->loadMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 457: { int _r = _t->copyMap((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 458: _t->setMap((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 459: { bool _r = _t->rotate_map((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 460: _t->startMapping((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 461: _t->stopMapping(); break;
        case 462: _t->setSLAMMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 463: _t->saveMapping((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 464: _t->setInitCurPos(); break;
        case 465: _t->setInitPos((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 466: { float _r = _t->getInitPoseX();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 467: { float _r = _t->getInitPoseY();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 468: { float _r = _t->getInitPoseTH();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 469: _t->slam_setInit(); break;
        case 470: _t->slam_run(); break;
        case 471: _t->slam_stop(); break;
        case 472: _t->slam_autoInit(); break;
        case 473: _t->slam_restInit(); break;
        case 474: { bool _r = _t->is_slam_running();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 475: { bool _r = _t->getMappingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 476: { bool _r = _t->getObjectingflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 477: _t->setObjectingflag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 478: { QString _r = _t->getnewMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 479: { QString _r = _t->getLastCall();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 480: { int _r = _t->getCallSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 481: { int _r = _t->getCallQueueSize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 482: _t->cleanTray(); break;
        case 483: { QString _r = _t->getCallName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 484: _t->clearCallQueue(); break;
        case 485: _t->resetLingbell((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 486: { QString _r = _t->getLingbell((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 487: { QString _r = _t->getCall((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 488: _t->setCallbell((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 489: _t->setCallbellForce((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 490: { QString _r = _t->makeLingbell();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 491: _t->setObjPose(); break;
        case 492: { QString _r = _t->getServingName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 493: { int _r = _t->getLocationNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 494: { int _r = _t->getLocationNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 495: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 496: { QString _r = _t->getLocationName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 497: { QString _r = _t->getLocationNameGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 498: { QString _r = _t->getLocationNameGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 499: { QString _r = _t->getLocationType((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 500: { int _r = _t->getLocationNumber((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 501: _t->setLocationNumber((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 502: { int _r = _t->getLocationSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 503: { QString _r = _t->getLocationGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 504: { int _r = _t->getLocationID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 505: { int _r = _t->getLocationGroupNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 506: { int _r = _t->getLocationGroupSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 507: { int _r = _t->getLocationGroupNum((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 508: { QString _r = _t->getLocationCallID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 509: { QString _r = _t->getLocationLingID((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 510: _t->setLocationGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 511: _t->removeLocationGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 512: _t->addLocationGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 513: { QString _r = _t->getLocGroupname((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 514: _t->setLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 515: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 516: { float _r = _t->getLocationX((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 517: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 518: { float _r = _t->getLocationY((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 519: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 520: { float _r = _t->getLocationTH((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 521: { bool _r = _t->isExistLocation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 522: { float _r = _t->getLidar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 523: { bool _r = _t->getAnnotEditFlag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 524: _t->setAnnotEditFlag((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 525: _t->clearSharedMemory(); break;
        case 526: { int _r = _t->getObjectNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 527: { QString _r = _t->getObjectName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 528: { int _r = _t->getObjectPointSize((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 529: { float _r = _t->getObjectX((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 530: { float _r = _t->getObjectY((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 531: { int _r = _t->getObjPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 532: { int _r = _t->getLocNum((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 533: { int _r = _t->getLocNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 534: _t->saveLocations(); break;
        case 535: { int _r = _t->getObjectSize((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 536: _t->removeObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 537: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 538: { bool _r = _t->saveAnnotation((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 539: _t->saveNode(); break;
        case 540: { bool _r = _t->isOdroid();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 541: { int _r = _t->getMultiState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 542: _t->drawingRunawayStart(); break;
        case 543: _t->drawingRunawayStop(); break;
        case 544: { int _r = _t->getRunawayState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 545: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 546: _t->slam_map_reload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 547: _t->slam_ini_reload(); break;
        case 548: _t->setTray((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 549: _t->startServing(); break;
        case 550: _t->setPreset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 551: _t->confirmPickup(); break;
        case 552: { QList<int> _r = _t->getPickuptrays();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 553: _t->movePause(); break;
        case 554: _t->moveResume(); break;
        case 555: _t->moveStopFlag(); break;
        case 556: _t->moveStop(); break;
        case 557: _t->moveToCharge(); break;
        case 558: _t->moveToWait(); break;
        case 559: _t->moveToCleaning(); break;
        case 560: { QString _r = _t->getcurLoc();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 561: _t->resetHomeFolders(); break;
        case 562: { int _r = _t->getObsState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 563: { int _r = _t->getBattery();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 564: { int _r = _t->getMotorState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 565: { int _r = _t->getLocalizationState();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 566: { int _r = _t->getStateMoving();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 567: { QString _r = _t->getStateMovingStr();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 568: { int _r = _t->getErrcode();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 569: { QString _r = _t->getRobotName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 570: { bool _r = _t->getMotorConnection((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 571: { int _r = _t->getMotorStatus((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 572: { QString _r = _t->getMotorStatusStr((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 573: { int _r = _t->getMotorTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 574: { int _r = _t->getMotorInsideTemperature((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 575: { int _r = _t->getMotorWarningTemperature();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 576: { int _r = _t->getMotorCurrent((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 577: { int _r = _t->getPowerStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 578: { int _r = _t->getRemoteStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 579: { int _r = _t->getChargeConnectStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 580: { int _r = _t->getChargeStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 581: { int _r = _t->getEmoStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 582: { int _r = _t->getLockStatus();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 583: { float _r = _t->getBatteryIn();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 584: { float _r = _t->getBatteryOut();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 585: { float _r = _t->getBatteryCurrent();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 586: { float _r = _t->getPower();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 587: { float _r = _t->getPowerTotal();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 588: { int _r = _t->getObsinPath();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 589: { int _r = _t->getRobotcurPreset();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 590: _t->setMotorLock((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 591: { float _r = _t->getRobotRadius();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 592: { float _r = _t->getRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 593: { float _r = _t->getRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 594: { float _r = _t->getRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 595: { float _r = _t->getlastRobotx();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 596: { float _r = _t->getlastRoboty();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 597: { float _r = _t->getlastRobotth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 598: { int _r = _t->getPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 599: { float _r = _t->getPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 600: { float _r = _t->getPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 601: { float _r = _t->getPathth((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 602: { int _r = _t->getLocalPathNum();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 603: { float _r = _t->getLocalPathx((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 604: { float _r = _t->getLocalPathy((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 605: { int _r = _t->getuistate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 606: { QString _r = _t->getMapname();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 607: { QString _r = _t->getMappath();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 608: { int _r = _t->getMapWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 609: { int _r = _t->getMapHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 610: { float _r = _t->getGridWidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 611: { QList<int> _r = _t->getOrigin();
            if (_a[0]) *reinterpret_cast< QList<int>*>(_a[0]) = std::move(_r); }  break;
        case 612: { int _r = _t->getMappingWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 613: { float _r = _t->getMappingGridwidth();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 614: { int _r = _t->getObjectNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 615: { int _r = _t->getObjectPointNum((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 616: _t->addObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 617: _t->addObjectPoint((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 618: _t->setObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 619: _t->editObjectStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 620: _t->editObject((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 621: _t->saveObject(); break;
        case 622: _t->clearObject(); break;
        case 623: _t->clearObjectAll(); break;
        case 624: _t->selectObject((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 625: { bool _r = _t->getObjectflag();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 626: _t->undoObject(); break;
        case 627: { float _r = _t->getICPRatio();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 628: { float _r = _t->getICPError();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 629: _t->clearFlagStop(); break;
        case 630: _t->slam_fullautoInit(); break;
        case 631: _t->moveToServingTest((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 632: { int _r = _t->getusberrorsize();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 633: { QString _r = _t->getusberror((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 634: { int _r = _t->getzipstate();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 635: _t->clear_call(); break;
        case 636: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 637: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 638: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 639: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 640: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 641: _t->usbsave((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 642: _t->usbsave(); break;
        case 643: _t->restartUpdate(); break;
        case 644: _t->startUpdate(); break;
        case 645: { int _r = _t->getTravellineIssue();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 646: { QString _r = _t->getTravellineIssueGroup((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 647: { QString _r = _t->getTravellineIssueName((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 648: { bool _r = _t->getTravellineIssueFar((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 649: { bool _r = _t->getTravellineIssueBroken((*reinterpret_cast< int(*)>(_a[1])));
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
        if (_id < 650)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 650;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 650)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 650;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
