import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("About Comic Sailor")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
                }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
                id: column
                width: page.width
                spacing: Theme.paddingLarge
                PageHeader {
                        title: "Comic Sailor 0.0.1"
                        }
                Label {
                        id: choosecomic
                        x: Theme.paddingLarge
                        text: qsTr("Choose a comic:")
                        color: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeExtraLarge
                        }
                SilicaListView {
                        x: Theme.paddingLarge
                        width: 200
                        height: 400
                        model: ComicModel  {}

                        delegate: Column  {
                            Button  {                                
                                        text: comicname
                                        // how to center?
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        onClicked: pageStack.push(Qt.resolvedUrl("ComicView.qml"), {comic: comicname})

                                    }
                                }
                        }
            }
        }

    }


