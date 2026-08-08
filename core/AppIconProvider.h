#pragma once

#include <QQuickImageProvider>
#include <QIcon>

class AppIconProvider : public QQuickImageProvider
{
public:
    AppIconProvider();

    void setIcon(const QIcon& icon);

    QPixmap requestPixmap(
        const QString& id,
        QSize* size,
        const QSize& requestedSize
        ) override;

private:
    QIcon m_icon;
};
