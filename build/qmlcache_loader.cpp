#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,25,0,0,0,1,0,0,1,
58,0,0,0,0,0,1,0,0,0,0,0,0,2,200,0,
0,0,0,0,1,0,0,0,0,0,0,3,160,0,0,0,
0,0,1,0,0,0,0,0,0,2,78,0,0,0,0,0,
1,0,0,0,0,0,0,1,100,0,0,0,0,0,1,0,
0,0,0,0,0,0,240,0,0,0,0,0,1,0,0,0,
0,0,0,1,20,0,0,0,0,0,1,0,0,0,0,0,
0,1,172,0,0,0,0,0,1,0,0,0,0,0,0,3,
66,0,0,0,0,0,1,0,0,0,0,0,0,0,8,0,
0,0,0,0,1,0,0,0,0,0,0,2,162,0,0,0,
0,0,1,0,0,0,0,0,0,2,14,0,0,0,0,0,
1,0,0,0,0,0,0,2,48,0,0,0,0,0,1,0,
0,0,0,0,0,1,208,0,0,0,0,0,1,0,0,0,
0,0,0,1,136,0,0,0,0,0,1,0,0,0,0,0,
0,1,238,0,0,0,0,0,1,0,0,0,0,0,0,0,
158,0,0,0,0,0,1,0,0,0,0,0,0,2,126,0,
0,0,0,0,1,0,0,0,0,0,0,3,126,0,0,0,
0,0,1,0,0,0,0,0,0,3,88,0,0,0,0,0,
1,0,0,0,0,0,0,3,28,0,0,0,0,0,1,0,
0,0,0,0,0,0,106,0,0,0,0,0,1,0,0,0,
0,0,0,0,54,0,0,0,0,0,1,0,0,0,0,0,
0,0,200,0,0,0,0,0,1,0,0,0,0,0,0,2,
240,0,0,0,0,0,1,0,0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,20,8,89,246,220,0,73,0,
116,0,101,0,109,0,95,0,80,0,114,0,111,0,103,0,
114,0,101,0,115,0,115,0,66,0,97,0,114,0,46,0,
113,0,109,0,108,0,23,13,193,140,252,0,73,0,116,0,
101,0,109,0,95,0,98,0,117,0,116,0,116,0,111,0,
110,0,82,0,101,0,99,0,116,0,73,0,99,0,111,0,
110,0,46,0,113,0,109,0,108,0,23,11,246,184,220,0,
80,0,97,0,103,0,101,0,95,0,112,0,105,0,99,0,
107,0,117,0,112,0,95,0,99,0,97,0,108,0,108,0,
105,0,110,0,103,0,46,0,113,0,109,0,108,0,18,9,
255,36,156,0,73,0,116,0,101,0,109,0,95,0,115,0,
116,0,97,0,116,0,117,0,115,0,98,0,97,0,114,0,
46,0,113,0,109,0,108,0,17,14,171,53,124,0,80,0,
97,0,103,0,101,0,95,0,77,0,111,0,118,0,101,0,
70,0,97,0,105,0,108,0,46,0,113,0,109,0,108,0,
15,3,190,52,220,0,80,0,97,0,103,0,101,0,95,0,
99,0,104,0,97,0,114,0,103,0,101,0,46,0,113,0,
109,0,108,0,16,4,245,236,92,0,73,0,116,0,101,0,
109,0,95,0,98,0,117,0,116,0,116,0,111,0,110,0,
115,0,46,0,113,0,109,0,108,0,18,1,14,237,156,0,
80,0,111,0,112,0,117,0,112,0,95,0,109,0,97,0,
112,0,95,0,108,0,105,0,115,0,116,0,46,0,113,0,
109,0,108,0,15,3,75,47,252,0,73,0,116,0,101,0,
109,0,95,0,98,0,117,0,116,0,116,0,111,0,110,0,
46,0,113,0,109,0,108,0,15,9,174,211,28,0,80,0,
97,0,103,0,101,0,95,0,112,0,105,0,99,0,107,0,
117,0,112,0,46,0,113,0,109,0,108,0,15,7,39,4,
92,0,80,0,97,0,103,0,101,0,95,0,109,0,111,0,
118,0,105,0,110,0,103,0,46,0,113,0,109,0,108,0,
12,9,153,226,252,0,80,0,97,0,103,0,101,0,95,0,
108,0,111,0,103,0,46,0,113,0,109,0,108,0,13,9,
252,62,252,0,80,0,97,0,103,0,101,0,95,0,105,0,
110,0,105,0,116,0,46,0,113,0,109,0,108,0,14,8,
203,138,60,0,80,0,111,0,112,0,117,0,112,0,95,0,
104,0,101,0,108,0,112,0,46,0,113,0,109,0,108,0,
12,9,76,226,252,0,80,0,97,0,103,0,101,0,95,0,
109,0,97,0,112,0,46,0,113,0,109,0,108,0,21,3,
25,36,220,0,80,0,97,0,103,0,101,0,95,0,108,0,
111,0,99,0,97,0,108,0,105,0,122,0,97,0,116,0,
105,0,111,0,110,0,46,0,113,0,109,0,108,0,15,10,
62,4,124,0,84,0,111,0,111,0,108,0,95,0,75,0,
101,0,121,0,80,0,97,0,100,0,46,0,113,0,109,0,
108,0,16,8,152,222,124,0,80,0,97,0,103,0,101,0,
95,0,107,0,105,0,116,0,99,0,104,0,101,0,110,0,
46,0,113,0,109,0,108,0,17,1,211,62,28,0,84,0,
111,0,111,0,108,0,95,0,75,0,101,0,121,0,98,0,
111,0,97,0,114,0,100,0,46,0,113,0,109,0,108,0,
19,15,58,210,220,0,80,0,97,0,103,0,101,0,95,0,
97,0,110,0,110,0,111,0,116,0,97,0,116,0,105,0,
111,0,110,0,46,0,113,0,109,0,108,0,16,10,156,201,
156,0,80,0,97,0,103,0,101,0,95,0,109,0,97,0,
112,0,112,0,105,0,110,0,103,0,46,0,113,0,109,0,
108,0,8,8,1,90,92,0,109,0,97,0,105,0,110,0,
46,0,113,0,109,0,108,0,16,10,144,96,28,0,80,0,
97,0,103,0,101,0,95,0,115,0,101,0,116,0,116,0,
105,0,110,0,103,0,46,0,113,0,109,0,108,0,14,10,
116,135,60,0,80,0,97,0,103,0,101,0,95,0,109,0,
101,0,110,0,117,0,115,0,46,0,113,0,109,0,108,0,
13,2,57,34,188,0,77,0,65,0,80,0,95,0,70,0,
85,0,76,0,76,0,50,0,46,0,113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _0x5f__MAP_FULL2_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_menus_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_setting_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__main_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_mapping_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_annotation_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Tool_Keyboard_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_kitchen_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Tool_KeyPad_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_localization_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_map_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Popup_help_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_init_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_log_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_moving_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_pickup_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Item_button_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Popup_map_list_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Item_buttons_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_charge_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_MoveFail_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Item_statusbar_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Page_pickup_calling_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Item_buttonRectIcon_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _0x5f__Item_ProgressBar_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/MAP_FULL2.qml"), &QmlCacheGeneratedCode::_0x5f__MAP_FULL2_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_menus.qml"), &QmlCacheGeneratedCode::_0x5f__Page_menus_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_setting.qml"), &QmlCacheGeneratedCode::_0x5f__Page_setting_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/main.qml"), &QmlCacheGeneratedCode::_0x5f__main_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_mapping.qml"), &QmlCacheGeneratedCode::_0x5f__Page_mapping_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_annotation.qml"), &QmlCacheGeneratedCode::_0x5f__Page_annotation_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Tool_Keyboard.qml"), &QmlCacheGeneratedCode::_0x5f__Tool_Keyboard_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_kitchen.qml"), &QmlCacheGeneratedCode::_0x5f__Page_kitchen_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Tool_KeyPad.qml"), &QmlCacheGeneratedCode::_0x5f__Tool_KeyPad_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_localization.qml"), &QmlCacheGeneratedCode::_0x5f__Page_localization_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_map.qml"), &QmlCacheGeneratedCode::_0x5f__Page_map_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Popup_help.qml"), &QmlCacheGeneratedCode::_0x5f__Popup_help_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_init.qml"), &QmlCacheGeneratedCode::_0x5f__Page_init_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_log.qml"), &QmlCacheGeneratedCode::_0x5f__Page_log_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_moving.qml"), &QmlCacheGeneratedCode::_0x5f__Page_moving_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_pickup.qml"), &QmlCacheGeneratedCode::_0x5f__Page_pickup_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Item_button.qml"), &QmlCacheGeneratedCode::_0x5f__Item_button_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Popup_map_list.qml"), &QmlCacheGeneratedCode::_0x5f__Popup_map_list_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Item_buttons.qml"), &QmlCacheGeneratedCode::_0x5f__Item_buttons_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_charge.qml"), &QmlCacheGeneratedCode::_0x5f__Page_charge_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_MoveFail.qml"), &QmlCacheGeneratedCode::_0x5f__Page_MoveFail_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Item_statusbar.qml"), &QmlCacheGeneratedCode::_0x5f__Item_statusbar_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Page_pickup_calling.qml"), &QmlCacheGeneratedCode::_0x5f__Page_pickup_calling_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Item_buttonRectIcon.qml"), &QmlCacheGeneratedCode::_0x5f__Item_buttonRectIcon_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/Item_ProgressBar.qml"), &QmlCacheGeneratedCode::_0x5f__Item_ProgressBar_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qml)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(qml_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qml))
int QT_MANGLE_NAMESPACE(qCleanupResources_qml)() {
    Q_CLEANUP_RESOURCE(qml_qmlcache);
    return 1;
}
