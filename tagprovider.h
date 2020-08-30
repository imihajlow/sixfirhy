/*
    Sixfirhy, a minimalist macos image viewer.
    Copyright (C) 2020 Ivan Mikhailov

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
