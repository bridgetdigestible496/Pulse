#pragma once

#include <QString>
#include <QIcon>
#include <QList>

struct AppEntry
{
    QString name;
    QString shortcutPath;
    QIcon icon;
};

class AppScanner
{
public:
    QList<AppEntry> scan();

private:
    void scanDirectory(
        const QString& directory,
        QList<AppEntry>& apps
        );
};
