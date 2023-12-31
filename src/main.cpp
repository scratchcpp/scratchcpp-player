// SPDX-License-Identifier: GPL-3.0-or-later

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QIcon>

int main(int argc, char *argv[])
{
    qputenv("QSG_RENDER_LOOP", "basic");

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    QIcon::setThemeName("scratchcpp");

    QQmlApplicationEngine engine;
    engine.addImportPath(":/");

    const QUrl url(u"qrc:/ScratchCPP/main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
