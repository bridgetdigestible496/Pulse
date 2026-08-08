#pragma once

#include <QAbstractListModel>
#include "AppScanner.h"

class AppIconProvider;

class AppModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(QString currentName READ currentName NOTIFY currentResultChanged)
    Q_PROPERTY(bool hasResult READ hasResult NOTIFY currentResultChanged)

public:
    enum Roles
    {
        NameRole = Qt::UserRole + 1,
        ShortcutPathRole,
        IconRole
    };

    explicit AppModel(QObject* parent = nullptr);

    void setIconProvider(AppIconProvider* provider);

    int rowCount(
        const QModelIndex& parent = QModelIndex()
        ) const override;

    QVariant data(
        const QModelIndex& index,
        int role = Qt::DisplayRole
        ) const override;

    QHash<int, QByteArray> roleNames() const override;

    QString currentName() const;
    bool hasResult() const;

    Q_INVOKABLE void search(const QString& text);
    Q_INVOKABLE void launchCurrent();

signals:
    void currentResultChanged();

private:
    QList<AppEntry> m_apps;

    int m_currentIndex = -1;

    AppIconProvider* m_iconProvider = nullptr;
};
