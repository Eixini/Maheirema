#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>

#include "headers/reciperequest.h"
#include "headers/recipemodel.h"
#include "headers/recipefilterproxymodel.h"

int main(int argc, char *argv[])
{
    if (qEnvironmentVariableIsEmpty("QTGLESSTREAM_DISPLAY")) {
        qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH", QByteArray("213"));
        qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT", QByteArray("120"));

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    }

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/maheirema_resource/image/icon/maheirema_logo.png"));

    // Регистрация пользовательского типа данных. Теперь функцию C++ можно использовать в QML
    qmlRegisterType<RecipeRequest>("RecipeRequestModule", 1, 0, "RecipeRequest");
    qmlRegisterType<RecipeModel>("RecipeModel", 1, 0, "RecipeModel");
    qmlRegisterType<RecipeFilterProxyModel>("RecipeModel", 1, 0, "RecipeFilterProxyModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
