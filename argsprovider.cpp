#include "argsprovider.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QUrl>
#include <QDebug>

ArgsProvider::ArgsProvider(QObject *parent) :
    QObject(parent),
    touched(false)
{
}

QVariantList ArgsProvider::getFiles() const {
    return files;
}

void ArgsProvider::clearFiles() {
    files.clear();
    emit filesChanged();
}

void ArgsProvider::handleFileOpenEvent(QUrl url) {
    if (touched) {
        files.clear();
    }
    files.append(url);
    emit filesChanged();
    if (touched) {
        touched = false;
        emit newList();
    }
}

void ArgsProvider::touch() {
    touched = true;
}
