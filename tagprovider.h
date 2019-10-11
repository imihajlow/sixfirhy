#ifndef TAGPROVIDER_H
#define TAGPROVIDER_H

#include <QObject>
#include <QUrl>
#include <QList>
#include <QVariant>
#include <memory>

class TagProvider : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ getUrl WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QVariantList tags READ getTags NOTIFY tagsChanged)
public:
    TagProvider(QObject *parent=nullptr);
    ~TagProvider();

    QUrl getUrl() const;
    void setUrl(QUrl const &url);

    QVariantList getTags() const;

    Q_INVOKABLE void toggleTag(int tag);
signals:
    void urlChanged();
    void tagsChanged();
private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif // TAGPROVIDER_H
