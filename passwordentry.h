#ifndef PASSWORDENTRY_H
#define PASSWORDENTRY_H

#include <QAbstractItemModel>

class PasswordEntry : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit PasswordEntry(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QString getName() const;
    void setName(const QString &newName);

    QString getUsername() const;
    void setUsername(const QString &newUsername);

    QString getPassword() const;
    void setPassword(const QString &newPassword);

    QString getUrl() const;
    void setUrl(const QString &newUrl);

private:
    QString name;
    QString username;
    QString password;
    QString url;
};

#endif // PASSWORDENTRY_H
