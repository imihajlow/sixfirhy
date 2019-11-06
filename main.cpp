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
