#include "passwordentry.h"

PasswordEntry::PasswordEntry(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant PasswordEntry::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex PasswordEntry::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)
    return QModelIndex();
}

QModelIndex PasswordEntry::parent(const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QModelIndex();
}

int PasswordEntry::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    return 1;
}

int PasswordEntry::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant PasswordEntry::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (index.column()) {
    case 0:
        return QVariant(name);
        break;
    case 1:
        return QVariant(username);
        break;
    case 2:
        return QVariant(password);
        break;
    case 3:
        return QVariant(url);
        break;
    }

    return QVariant();
}

QString PasswordEntry::getName() const
{
    return name;
}

void PasswordEntry::setName(const QString &newName)
{
    name = newName;
}

QString PasswordEntry::getUsername() const
{
    return username;
}

void PasswordEntry::setUsername(const QString &newUsername)
{
    username = newUsername;
}

QString PasswordEntry::getPassword() const
{
    return password;
}

void PasswordEntry::setPassword(const QString &newPassword)
{
    password = newPassword;
}

QString PasswordEntry::getUrl() const
{
    return url;
}

void PasswordEntry::setUrl(const QString &newUrl)
{
    url = newUrl;
}
