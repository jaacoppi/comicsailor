#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif


#include <sailfishapp.h>
#include "common.h"

// for C++ integration
#include <QGuiApplication>
#include <QQuickView>
#include <QtQml>

extern class Selectedcomic comic_data[NRCOMICS];
int main(int argc, char *argv[])
{

    // I'm not sure how to init a Sailfish App.

    // this works
    qmlRegisterType <Selectedcomic> ( "harbour.comicsailor", 1, 0, "Selectedcomic" );
    return SailfishApp :: main(argc, argv);

    // https://saildev.wordpress.com/2014/08/01/integrating-c-and-qml/comment-page-1/
    // there's also this method
    QGuiApplication * q_application = SailfishApp :: application ( argc, argv );
    QQuickView * q_view = SailfishApp :: createView ( );

    qmlRegisterType <Selectedcomic> ( "ComicSailor", 1, 0, "Selectedcomic" );
    q_view -> setSource ( SailfishApp :: pathTo ( "qml/comicsailor.qml" ));
    q_view -> showFullScreen ( );

    return q_application -> exec ( );



    }
