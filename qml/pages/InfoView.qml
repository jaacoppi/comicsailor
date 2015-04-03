import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.comicsailor 1.0

// Comic Sailor Comic Info page
Page {
    id: infopage
    allowedOrientations: Orientation.All
    property string license
    property string homepage
    property string title


    Column {
                id: column
                width: infopage.width
                spacing: Theme.paddingLarge
                PageHeader {
                        title: infopage.title
                        }

        Label {
            text: "<b>" + "Homepage" + "</b>"
            anchors.horizontalCenter: parent.horizontalCenter
            }

        Text {
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: homepage
            color: Theme.primaryColor
			}

        Label {
            text: "<b>" + "License" + "</b>"
            anchors.horizontalCenter: parent.horizontalCenter
            }

		Text {
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: license
            color: Theme.primaryColor
			}

        }

    }

