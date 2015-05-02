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
            text: "<b>" + "Home page" + "</b>"
            anchors.horizontalCenter: parent.horizontalCenter
            }

        Text {
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            text: "<a href=\"homepage\">" + homepage + "</a>"
            color: Theme.highlightColor
            onLinkActivated: Qt.openUrlExternally(infopage.homepage)
			}

        Label {
            text: "<b>" + "License" + "</b>"
            anchors.horizontalCenter: parent.horizontalCenter
            }

		Text {
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            // XKCD has a proper license page, other comics don't. This is a dirty hack.
            text: (infopage.title == "XKCD") ? "<a href=\"license\">" + infopage.license + "</a>" : "<a href=\"license\">" + license + "</a>" + ".\n\nNote that the official comic license statement is displayed on the comic home page above. This direct link is the one provided in the Creative Commons image on the home page."
            color: Theme.highlightColor
            onLinkActivated: Qt.openUrlExternally(infopage.license)
			}

        }

        }

