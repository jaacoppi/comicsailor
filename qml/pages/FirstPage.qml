import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

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
			// TODO: is this enough to align center?
                        width: 500
                        height: 400
                        x: Theme.paddingLarge
                        model: ComicModel  {}
                        delegate: Column  {
                            Button  {                                
                                        text: comicname
                                        // how to center? - here or listview?
                                        anchors.horizontalCenter: parent.horizontalCenter
                                        onClicked: pageStack.push(Qt.resolvedUrl("ComicView.qml"), {comic: comicname})
                                    }
                                }
                        }
            }
        }

    }


