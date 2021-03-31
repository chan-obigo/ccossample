import QtQuick 2.13
import ccOS.GUI.Window 1.0
import ccOS.GUI.Controls 1.0
import ccOS.StatusBarAddon 1.0

HWindow {
  id: window
  objectName: "EXAMPLE.FrontWindow"

  width: 1920
  height: 70

  Rectangle {
    id: background
    width: 1920
    height: 70
    color: "black"
  }

  FocusScope {
    anchors.fill: parent
    focus : true

    HTopBar{
      id : topbar

      Rectangle {
          y: 0
          x: 500
          width: 500

          Text {
            y: parent.y + 30
            id: subtitle
            text: qsTr("Sub Title")
            color: "white"
            font.pixelSize: 30
          }
      }

      appTitle: "Title"

      onButtonClicked:{ 
        console.log("onButtonClicked : "+buttonId);
      }

      Component.onCompleted: {
      }

      Keys.onReleased: {
        console.log("[topbar]Keys.onReleased : "+event.key+" Qt.Key_4: "+Qt.Key_4+" Qt.Key_6:"+Qt.Key_6)

        if (event.key === Qt.Key_2) {
          topbar.focusMover.currentItem.focus = false
          sceneStackView.focus = true;
        }
      }
    } 
  }

  HBottomBar { // GNB menu NowPlaying Bar 
    id: bottombar
    buttonListMenu :[
      {
        "type": text,
        "buttonId": "store",
        "text": "App Center"
      },
      {
        "type": text,
        "buttonId": "launcher",
        "text": "Launcher"
      }
    ]
    onButtonClicked:{ 
      console.log("onButtonClicked : "+buttonId);
    }
  }
}
