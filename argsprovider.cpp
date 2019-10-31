#include "argsprovider.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

ArgsProvider::ArgsProvider(QObject *parent) :
    QObject(parent),
    mode(Empty)
{
    auto args = QCoreApplication::arguments();
    if (args.size() <= 1) {
        mode = Empty;
    } else {
        for (int i = 1; i < args.size(); ++i) {
            QFileInfo fi(args.at(i));
            if (fi.isDir() && mode == Empty) {
                folder = args.at(i);
                mode = Folder;
                break;
            } else if (fi.exists()) {
                mode = Files;
                files.append(args.at(i));
            }
        }
    }
}

ArgsProvider::Mode ArgsProvider::getMode() const {
    return mode;
}

QString ArgsProvider::getFolder() const {
    return folder;
}

QVariantList ArgsProvider::getFiles() const {
    return files;
}
