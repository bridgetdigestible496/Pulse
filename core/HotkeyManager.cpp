#include "HotkeyManager.h"

#include <windows.h>

HotkeyManager::HotkeyManager(QObject *parent)
    : QObject(parent)
{
}

bool HotkeyManager::registerHotkey()
{
    return RegisterHotKey(
        nullptr,
        HOTKEY_ID,
        MOD_ALT,
        VK_SPACE
        );
}

void HotkeyManager::unregisterHotkey()
{
    UnregisterHotKey(nullptr, HOTKEY_ID);
}

bool HotkeyManager::nativeEventFilter(
    const QByteArray &eventType,
    void *message,
    qintptr *result)
{
    Q_UNUSED(eventType);
    Q_UNUSED(result);

    MSG *msg = static_cast<MSG *>(message);

    if (msg->message == WM_HOTKEY &&
        msg->wParam == HOTKEY_ID)
    {
        emit hotkeyPressed();
        return true;
    }

    return false;
}
