#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <foodAPI.h>
#include <QQmlContext>
#include <QQuickView>
#include <QGuiApplication>
#include <QCoreApplication>
#include <QtQml>
#include <restaurant.h>
#include <QMetaType>
#include <restaurantmodel.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("harbour-juvefood");
    QCoreApplication::setOrganizationName("harbour-juvefood");
    qmlRegisterType<RestaurantModel>("harbour.juvefood.restaurantmodel", 1, 0, "RestaurantModel");
    foodAPI api;
    QGuiApplication *app = SailfishApp::application(argc, argv);
    QQuickView *view = SailfishApp::createView();
    view->rootContext()->setContextProperty("foodAPI", &api);
    view->rootContext()->setContextProperty("APP_VERSION", APP_VERSION);
    view->setSource(SailfishApp::pathTo("qml/harbour-juvefood.qml"));
    view->showFullScreen();
    app->exec();
}

