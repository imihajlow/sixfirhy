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
