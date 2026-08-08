#pragma once

#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QByteArray>

class HotkeyManager : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit HotkeyManager(QObject *parent = nullptr);

    bool registerHotkey();
    void unregisterHotkey();

    bool nativeEventFilter(
        const QByteArray &eventType,
        void *message,
        qintptr *result
        ) override;

signals:
    void hotkeyPressed();

private:
    static constexpr int HOTKEY_ID = 1;
};
