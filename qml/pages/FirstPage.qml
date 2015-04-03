import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page
    allowedOrientations: Orientation.All

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent
        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
                }
        }

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
                id: column
                width: page.width
                spacing: Theme.paddingLarge
                PageHeader {
                        title: "Comic Sailor"
                        }
                Label {
                        id: choosecomic
                        x: Theme.paddingLarge
                        text: qsTr("Choose a comic:")
                        color: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeExtraLarge
                        anchors.horizontalCenter: parent.horizontalCenter
                        }
                SilicaListView {
                        width: 500
                        height: 400
                        anchors.horizontalCenter: parent.horizontalCenter
                        x: Theme.paddingLarge
                        model: ComicModel  {}
                        delegate: Column  {
                            anchors.horizontalCenter: parent.horizontalCenter
                            Button  {
                                text: comictitle
                                onClicked: pageStack.push(Qt.resolvedUrl("ComicView.qml"), {comic: comicname, comictitle: comictitle})
                                }
                            }
                        }
            }
        }

    }


