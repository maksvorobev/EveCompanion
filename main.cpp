#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Aplication.h"
#include <iostream>
#include <QQmlContext>
#include <QSslSocket>
#include <QtQml/qqmlextensionplugin.h>
#include <QStringList>
#include <QStringListModel>
#include <QQuickView>
#include "Logger.h"

Q_IMPORT_QML_PLUGIN(Qml_StyleSettingsPlugin)
Q_IMPORT_QML_PLUGIN(Qml_PagesPlugin)


int main(int argc, char *argv[])
{
    Logger::init();

    QGuiApplication app(argc, argv);

    // Settings of aplication
    std::string Client_ID = "56152a60d2e04db59842338858c20449";
    std::string requirements = "esi-wallet.read_character_wallet.v1 esi-characters.read_blueprints.v1 publicData";

    qInfo() << "Aplction is strating!\n\n\n";

    Aplication* aplication = new Aplication(
        QString::fromStdString(Client_ID),
        QString::fromStdString(requirements)
        );



    QQmlApplicationEngine engine;
    engine.addImportPath(":/maksvorobev/imports");
    const QUrl url(u"qrc:/maksvorobev/imports/EveCompanion/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    //engine.rootContext()->setContextObject(A_eng);
    engine.rootContext()->setContextProperty("AuthorizationUrl", aplication->authEngine()->authorizationUrl());
    engine.rootContext()->setContextProperty("AuthEngine", aplication->authEngine());
    //engine.rootContext()->setContextProperty("MainPageModel", A_eng->getMainPageModel().get());

    engine.load(url);
    //engine.load(QUrl(u"qrc:/maksvorobev/imports/Qml.StyleSettings/Style.qml"_qs));

    bool state = app.exec();

    Logger::clean();

    return state;
}
