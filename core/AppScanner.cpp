#include "AppScanner.h"

#include <QProcess>
#include <QDir>
#include <QFileInfo>
#include <QStandardPaths>
#include <QPixmap>
#include <QImage>

#include <windows.h>
#include <shobjidl.h>
#include <shlguid.h>
#include <shellapi.h>


static QIcon getShortcutIcon(const QString& shortcutPath)
{
    QIcon icon;

    {
        SHFILEINFOW fileInfo{};

        DWORD_PTR result = SHGetFileInfoW(
            reinterpret_cast<LPCWSTR>(shortcutPath.utf16()),
            FILE_ATTRIBUTE_NORMAL,
            &fileInfo,
            sizeof(fileInfo),
            SHGFI_ICON | SHGFI_LARGEICON
            );

        if (result != 0 && fileInfo.hIcon)
        {
            QImage image = QImage::fromHICON(fileInfo.hIcon);

            if (!image.isNull())
                icon.addPixmap(QPixmap::fromImage(image));

            DestroyIcon(fileInfo.hIcon);
        }
    }

    if (!icon.isNull())
        return icon;

    IShellLinkW* shellLink = nullptr;

    HRESULT hr = CoCreateInstance(
        CLSID_ShellLink,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_IShellLinkW,
        reinterpret_cast<void**>(&shellLink)
        );

    if (FAILED(hr))
        return {};

    IPersistFile* persistFile = nullptr;

    hr = shellLink->QueryInterface(
        IID_IPersistFile,
        reinterpret_cast<void**>(&persistFile)
        );

    if (FAILED(hr))
    {
        shellLink->Release();
        return {};
    }

    hr = persistFile->Load(
        reinterpret_cast<LPCOLESTR>(shortcutPath.utf16()),
        STGM_READ
        );

    if (FAILED(hr))
    {
        persistFile->Release();
        shellLink->Release();
        return {};
    }

    wchar_t iconPath[MAX_PATH]{};
    int iconIndex = 0;

    hr = shellLink->GetIconLocation(
        iconPath,
        MAX_PATH,
        &iconIndex
        );

    if (SUCCEEDED(hr) && iconPath[0] != L'\0')
    {
        HICON largeIcon = nullptr;
        HICON smallIcon = nullptr;

        ExtractIconExW(
            iconPath,
            iconIndex,
            &largeIcon,
            &smallIcon,
            1
            );

        if (largeIcon)
        {
            QImage image = QImage::fromHICON(largeIcon);

            if (!image.isNull())
                icon.addPixmap(QPixmap::fromImage(image));

            DestroyIcon(largeIcon);
        }

        if (smallIcon)
        {
            QImage image = QImage::fromHICON(smallIcon);

            if (!image.isNull())
                icon.addPixmap(QPixmap::fromImage(image));

            DestroyIcon(smallIcon);
        }
    }

    if (icon.isNull())
    {
        wchar_t targetPath[MAX_PATH]{};
        WIN32_FIND_DATAW findData{};

        hr = shellLink->GetPath(
            targetPath,
            MAX_PATH,
            &findData,
            SLGP_RAWPATH
            );

        if (SUCCEEDED(hr) && targetPath[0] != L'\0')
        {
            SHFILEINFOW fileInfo{};

            DWORD_PTR result = SHGetFileInfoW(
                targetPath,
                FILE_ATTRIBUTE_NORMAL,
                &fileInfo,
                sizeof(fileInfo),
                SHGFI_ICON | SHGFI_LARGEICON
                );

            if (result != 0 && fileInfo.hIcon)
            {
                QImage image = QImage::fromHICON(fileInfo.hIcon);

                if (!image.isNull())
                    icon.addPixmap(QPixmap::fromImage(image));

                DestroyIcon(fileInfo.hIcon);
            }
        }
    }

    persistFile->Release();
    shellLink->Release();

    return icon;
}


QList<AppEntry> AppScanner::scan()
{
    QList<AppEntry> apps;

    const QString userPrograms =
        QStandardPaths::writableLocation(
            QStandardPaths::ApplicationsLocation
            );

    scanDirectory(userPrograms, apps);

    const QString systemPrograms =
        QDir::fromNativeSeparators(
            qEnvironmentVariable("ProgramData")
            )
        + "/Microsoft/Windows/Start Menu/Programs";

    scanDirectory(systemPrograms, apps);

    return apps;
}


void AppScanner::scanDirectory(
    const QString& directory,
    QList<AppEntry>& apps)
{
    QDir dir(directory);

    const QFileInfoList entries = dir.entryInfoList(
        QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot
        );

    for (const QFileInfo& entry : entries)
    {
        if (entry.isDir())
        {
            scanDirectory(entry.absoluteFilePath(), apps);
            continue;
        }

        if (entry.suffix().compare("lnk", Qt::CaseInsensitive) != 0)
            continue;

        AppEntry app;

        app.name = entry.completeBaseName();
        app.shortcutPath = entry.absoluteFilePath();
        app.icon = getShortcutIcon(app.shortcutPath);

        apps.append(app);
    }
}