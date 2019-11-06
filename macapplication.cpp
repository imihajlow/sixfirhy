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
