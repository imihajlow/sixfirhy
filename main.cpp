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
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "tagprovider.h"
#include "macapplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    MacApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<TagProvider>("com.example", 1, 0, "TagProvider");
    qmlRegisterSingletonType<ArgsProvider>("com.example", 1, 0, "ArgsProvider", [](QQmlEngine *, QJSEngine *) -> QObject * {
        return MacApplication::getArgsProvider();
    });
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
