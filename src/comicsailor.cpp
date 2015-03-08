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


    // SailfishApp::main() will display "qml/template.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //
    // To display the view, call "show()" (will show fullscreen on device).
    qmlRegisterType <Selectedcomic> ( "ComicSailor", 1, 0, "Selectedcomic" );
    return SailfishApp :: main(argc, argv);

    QGuiApplication * q_application = SailfishApp :: application ( argc, argv );
    QQuickView * q_view = SailfishApp :: createView ( );
    // after this we can use import com.comicsailor.components 1.0 && selected_comic {} in qml files
    // start GUI from FirstPage.qml
    q_view -> setSource ( SailfishApp :: pathTo ( "qml/pages/FirstPage.qml" ));
    q_view -> showFullScreen ( );
    return q_application -> exec ( );
    }
