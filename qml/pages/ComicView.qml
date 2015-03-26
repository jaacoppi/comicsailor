import QtQuick 2.0
import Sailfish.Silica 1.0
import harbour.comicsailor 1.0


Page {
    id: comicviewpage
// we get these from FirstPage - what comic to load
    property string comic 
    property string comictitle
//    allowedOrientations: Orientation.All
    allowedOrientations: Orientation.Portrait | Orientation.Landscape | Orientation.LandscapeInverted

    Selectedcomic {
        id: comicsailor
        Component.onCompleted: {
        if (comic == "XKCD") { changecomic_xkcd() }
        if (comic == "DIESEL") { changecomic_diesel() }
        if (comic == "PEEBLES") { changecomic_peebles() }
        if (comic == "SPIKED") { changecomic_spiked() }
        }
    onImgurlChanged: comic_img.source = imgurl
    }

    SilicaFlickable {
            contentHeight: comicviewpage.height
            anchors.fill: parent
        PullDownMenu {
            MenuItem {
                    text: "Comic Info"
                    onClicked: pageStack.push(Qt.resolvedUrl("InfoView.qml"), {license: comicsailor.license, homepage: comicsailor.homepage})
                    }
            MenuItem {
                        text: "First"
                        onClicked: comicsailor.comic_first()
                        }

                MenuItem {
                        text: "Next"
                        onClicked: comicsailor.comic_next()
                        }
                MenuItem {
                        text: "Previous"
                        onClicked: comicsailor.comic_prev()
                        }
                MenuItem {
                        text: "Latest"
                        onClicked: comicsailor.comic_last()
                        }
                /*
                MenuItem {
                        text: "By #"
                    onClicked: // TODO: int picker
                        } */
                }
        Label {
          id: statuslabel
          wrapMode: Text.WordWrap
          }

        Image {
		id: comic_img
		width: Screen.width
		height: Screen.height
        fillMode: Image.PreserveAspectFit

        onStatusChanged:
            switch(comic_img.status) {
                case Image.Loading:
                    statuslabel.text = "Loading strip #" + comicsailor.current;
                    break;
                case Image.Ready:
                    statuslabel.text = comicviewpage.comictitle + " strip #" + comicsailor.current;
                    break;
                case Image.Error:
                case Image.Null:
                    statuslabel.text = "Error loading strip #" + comicsailor.current + ", choose another.";
                    break;
                }
        }


      // pinch zoom in and out of the strip
      PinchArea {
          //property int xpoint
          //property int ypoint
          //property int pinchscale
          id: pinchzoom
          enabled: true
          pinch.target: comic_img
          anchors.fill: parent
          pinch.dragAxis: Pinch.NoDrag
          pinch.minimumScale: 0.5
          pinch.maximumScale: 3
          pinch.maximumRotation: 0
          //onPinchUpdated: { xpoint = pinch.center.x; ypoint = pinch.center.y; pinchscale = pinch.scale}
        }
    }
}
