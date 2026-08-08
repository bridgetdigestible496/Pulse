#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <objbase.h>

#include "core/HotkeyManager.h"
#include "core/AppModel.h"
#include "core/AppIconProvider.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CoInitializeEx(
        nullptr,
        COINIT_APARTMENTTHREADED
        );

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []()
        {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
        );

    AppModel appModel;
    AppIconProvider iconProvider;

    appModel.setIconProvider(&iconProvider);

    engine.addImageProvider(
        "appicon",
        &iconProvider
    );

    engine.rootContext()->setContextProperty(
        "appModel",
        &appModel
    );

    engine.loadFromModule("Pulse", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;

    const auto rootObjects = engine.rootObjects();

    if (rootObjects.isEmpty())
        return -1;

    QWindow *window = qobject_cast<QWindow *>(rootObjects.first());


    if (!window)
        return -1;
        window->hide();

    HotkeyManager hotkey;

    if (!hotkey.registerHotkey())
        return -1;

    app.installNativeEventFilter(&hotkey);

    QObject::connect(
        &hotkey,
        &HotkeyManager::hotkeyPressed,
        window,
        [window]()
        {
            if (window->isVisible())
            {
                QMetaObject::invokeMethod(
                    window,
                    "hidePulse"
                    );
            }
            else
            {
                QMetaObject::invokeMethod(
                    window,
                    "showPulse"
                    );
            }
        }
        );

    const int result = QGuiApplication::exec();

    hotkey.unregisterHotkey();

    return result;
}
