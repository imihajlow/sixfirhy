#pragma once
#include "argsprovider.h"

#include <QGuiApplication>

class MacApplication : public QGuiApplication
{
    Q_OBJECT
public:
    MacApplication(int &argc, char **argv);
    bool event(QEvent *event) override;

    static ArgsProvider *getArgsProvider();
};
