#ifndef ARGSPROVIDER_H
#define ARGSPROVIDER_H

#include <QObject>
#include <QString>
#include <QVariantList>

class ArgsProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList files READ getFiles NOTIFY filesChanged)
public:
    explicit ArgsProvider(QObject *parent = nullptr);

    QVariantList getFiles() const;
    Q_INVOKABLE void clearFiles();
    Q_INVOKABLE void touch();

    void handleFileOpenEvent(QUrl url);
signals:
    void filesChanged();
    void newList();
private:
    QVariantList files;
    bool touched;
};

#endif // ARGSPROVIDER_H
