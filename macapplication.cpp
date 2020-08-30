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
#include "macapplication.h"
#include <QEvent>
#include <QFileOpenEvent>
#include <QDebug>

MacApplication::MacApplication(int &argc, char **argv):
    QGuiApplication(argc, argv)
{
}

bool MacApplication::event(QEvent *event) {
    switch(event->type()) {
    case QEvent::FileOpen: {
        auto fileOpenEvent = dynamic_cast<QFileOpenEvent *>(event);
        if(fileOpenEvent) {
            getArgsProvider()->handleFileOpenEvent(fileOpenEvent->url());
            return true;
        }
        break;
    }
    default: break;
    }
    return QGuiApplication::event(event);
}

ArgsProvider *MacApplication::getArgsProvider() {
    static ArgsProvider *ap = new ArgsProvider;
    return ap;
}
