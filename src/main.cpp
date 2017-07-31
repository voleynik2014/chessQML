#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "gamehandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

	GameHandler gameHandler;
    QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("gameHandler", &gameHandler);
	engine.rootContext()->setContextProperty("history", &gameHandler.history);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
