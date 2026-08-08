#include "AppModel.h"
#include "AppIconProvider.h"

#include <QVariant>
#include <QProcess>

#include <windows.h>
#include <shellapi.h>

AppModel::AppModel(QObject* parent)
    : QAbstractListModel(parent)
{
    AppScanner scanner;

    m_apps = scanner.scan();
}

int AppModel::rowCount(
    const QModelIndex& parent
    ) const
{
    if (parent.isValid())
        return 0;

    return m_apps.size();
}

QVariant AppModel::data(
    const QModelIndex& index,
    int role
    ) const
{
    if (!index.isValid())
        return {};

    const AppEntry& app = m_apps.at(index.row());

    switch (role)
    {
    case NameRole:
        return app.name;

    case ShortcutPathRole:
        return app.shortcutPath;

    case IconRole:
        return app.icon;
    }

    return {};
}

QHash<int, QByteArray> AppModel::roleNames() const
{
    return {
        { NameRole, "name" },
        { ShortcutPathRole, "shortcutPath" },
        { IconRole, "icon" }
    };
}

QString AppModel::currentName() const
{
    if (m_currentIndex < 0)
        return {};

    return m_apps.at(m_currentIndex).name;
}

bool AppModel::hasResult() const
{
    return m_currentIndex >= 0;
}

void AppModel::search(const QString& text)
{
    const QString query = text.trimmed();

    int newIndex = -1;

    if (!query.isEmpty())
    {
        for (int i = 0; i < m_apps.size(); ++i)
        {
            if (m_apps[i].name.compare(
                    query,
                    Qt::CaseInsensitive
                    ) == 0)
            {
                newIndex = i;
                break;
            }
        }

        if (newIndex == -1)
        {
            for (int i = 0; i < m_apps.size(); ++i)
            {
                if (m_apps[i].name.startsWith(
                        query,
                        Qt::CaseInsensitive
                        ))
                {
                    newIndex = i;
                    break;
                }
            }
        }

        if (newIndex == -1)
        {
            for (int i = 0; i < m_apps.size(); ++i)
            {
                if (m_apps[i].name.contains(
                        query,
                        Qt::CaseInsensitive
                        ))
                {
                    newIndex = i;
                    break;
                }
            }
        }
    }

    if (m_currentIndex == newIndex)
        return;

    m_currentIndex = newIndex;

    if (m_iconProvider)
    {
        if (m_currentIndex >= 0)
            m_iconProvider->setIcon(
                m_apps.at(m_currentIndex).icon
                );
        else
            m_iconProvider->setIcon({});
    }

    emit currentResultChanged();
}

void AppModel::setIconProvider(AppIconProvider* provider)
{
    m_iconProvider = provider;
}

void AppModel::launchCurrent()
{
    if (m_currentIndex < 0)
        return;

    const QString& shortcut =
        m_apps.at(m_currentIndex).shortcutPath;

    ShellExecuteW(
        nullptr,
        L"open",
        reinterpret_cast<LPCWSTR>(shortcut.utf16()),
        nullptr,
        nullptr,
        SW_SHOWNORMAL
        );
}

