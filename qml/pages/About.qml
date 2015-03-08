import QtQuick 2.0
import Sailfish.Silica 1.0
// Comic Sailor about page
Page {
        id: aboutpage
        Column {
                id: column
                //width: aboutpage.width
                height: Screen.height
                width: Screen.width
                spacing: Theme.paddingLarge
                PageHeader {
                        id: header
                        title: "About Comic Sailor"
                        }

                Text {
                        color: Theme.secondaryHighlightColor
                        font.pixelSize: Theme.fontSizeLarge
                        x: header.x + 010
                        width: parent.width
                        wrapMode: Text.WrapAnywhere
text: qsTr("Comic Sailor is used to read a variety of webcomics.\n
MIT Licensed. Source code can be found from http://github.com/jaacoppi/comicsailor\n
For more info, See README.md, TODO and LICENSE in the source code.\n
Contact the author: jaacoppi on together.jolla.com or on freenode IRC servers.")
                    }
            }
    }
