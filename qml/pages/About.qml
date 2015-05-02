import QtQuick 2.0
import Sailfish.Silica 1.0
// Comic Sailor about page
Page {
        id: aboutpage
        allowedOrientations: Orientation.Portrait | Orientation.Landscape | Orientation.LandscapeInverted
        Column {
                id: column
                height: parent.height
                width: parent.width
                spacing: Theme.paddingLarge
                PageHeader {
                        id: header
                        title: "About Comic Sailor"
                        }

                Label {
                    text: "<b>" + "About" + "</b>"
                    anchors.horizontalCenter: parent.horizontalCenter
                    }

                Text {
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: "Comic Sailor is used to read a variety of webcomics."
                    color: Theme.primaryColor
                    }


                Label {
                    text: "<b>" + "Source code & license" + "</b>"
                    anchors.horizontalCenter: parent.horizontalCenter
                    }

                Text {
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: "MIT Licensed. Source code can be found from http://github.com/jaacoppi/comicsailor. For more info, See README.md, TODO and LICENSE in the source code."
                    color: Theme.primaryColor
                    }

                Label {
                    text: "<b>" + "Contact the author" + "</b>"
                    anchors.horizontalCenter: parent.horizontalCenter
                    }

                Text {
                    width: parent.width
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    text: "jaacoppi on together.jolla.com or on freenode IRC servers."
                    color: Theme.primaryColor
                    }
             }
    }
