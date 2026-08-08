#include "AppIconProvider.h"

AppIconProvider::AppIconProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
}

void AppIconProvider::setIcon(const QIcon& icon)
{
    m_icon = icon;
}

QPixmap AppIconProvider::requestPixmap(
    const QString&,
    QSize* size,
    const QSize& requestedSize)
{
    const int width = requestedSize.width() > 0
                          ? requestedSize.width()
                          : 32;

    const int height = requestedSize.height() > 0
                           ? requestedSize.height()
                           : 32;

    if (m_icon.isNull())
    {
        if (size)
            *size = QSize();

        return {};
    }

    QPixmap pixmap = m_icon.pixmap(width, height);

    if (size)
        *size = pixmap.size();

    return pixmap;
}
