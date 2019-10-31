#ifndef ARGSPROVIDER_H
#define ARGSPROVIDER_H

#include <QObject>
#include <QString>
#include <QVariantList>

class ArgsProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Mode mode READ getMode CONSTANT)
    Q_PROPERTY(QString folder READ getFolder CONSTANT)
    Q_PROPERTY(QVariantList files READ getFiles CONSTANT)
public:
    enum Mode {
        Empty,
        Folder,
        Files
    };
    Q_ENUM(Mode)
    explicit ArgsProvider(QObject *parent = nullptr);

    Mode getMode() const;
    QString getFolder() const;
    QVariantList getFiles() const;
private:
    Mode mode;
    QString folder;
    QVariantList files;
};

#endif // ARGSPROVIDER_H
