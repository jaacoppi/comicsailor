import QtQuick 2.0
import Sailfish.Silica 1.0
import ComicSailor 1.0
// Comic Sailor Comic Info page
Page {
    id: infopage
    property string license
    property string homepage


    Column {
                id: column
                width: infopage.width
                spacing: Theme.paddingLarge
                PageHeader {
                        title: "Comic info"
                        }

        Label {
            text: "Homepage"
            horizontalAlignment: Text.AlignHCenter
            }

        Text {
		width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: homepage
			}

        Label {
            text: "License"
            horizontalAlignment: Text.AlignHCenter
            }

		Text {
		width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: license
			}

        }

    }

