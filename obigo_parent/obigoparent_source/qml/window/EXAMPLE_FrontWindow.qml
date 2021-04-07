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

      buttonList: [
         {
             "type": textml,
             "buttonId": "top1",
             "text": "TOP1"
         },
         {
             "type": text,
             "buttonId": "top2",
             "text": "TOP2"
         }
      ]

      appTitle: "Title"
      appIconURI: "general/statusbar/status_profile_default.png"

      onButtonClicked:{ 
        console.log("onButtonClicked : "+buttonId);
        if (buttonId === "top1") {
          topbar.buttonList = [
             {
                 "type": textml,
                 "buttonId": "top1",
                 "text": "TOP1"
             },
             {
                 "type": text,
                 "buttonId": "top2",
                 "text": "TOP2"
             },
             {
                 "type": text,
                 "buttonId": "t_new1",
                 "text": "T_NEW1"
             },
             {
                 "type": text,
                 "buttonId": "t_new2",
                 "text": "T_NEW2"
             }
          ]
        }
        if (buttonId === "top2") {
          topbar.buttonList = [
             {
                 "type": textml,
                 "buttonId": "top1",
                 "text": "TOP1"
             },
             {
                 "type": text,
                 "buttonId": "top2",
                 "text": "TOP2"
             }
          ]
        }
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
    property int count : 1

    buttonListMenu :[
      {
        "type": textml,
        "buttonId": "bottom1",
        "text": "BOTTOM1"
      },
      {
        "type": text,
        "buttonId": "bottom2",
        "text": "BOTTOM2"
      }
    ]
    onButtonClicked:{ 
      console.log("onButtonClicked : "+buttonId);
      if (buttonId === "Back") {
        if (bottombar.count === 1) {
          console.log("[USE buttonListMenu]");
          bottombar.isTabsUsed = false
          bottombar.buttonsTabBar = []

          bottombar.buttonListMenu = [
            {
              "type": textml,
              "buttonId": "bottom1",
              "text": "BOTTOM1"
            },
            {
              "type": text,
              "buttonId": "bottom2",
              "text": "BOTTOM2"
            }
          ]
          bottombar.count = 2
        } else if (bottombar.count === 2) {
          console.log("[USE buttonListMenu]");
          bottombar.buttonListMenu = []
          
          bottombar.isTabsUsed = true
          bottombar.buttonsTabBar = [
            {
              "buttonId": "tab_1",
              "text": "BOTTOM1"
            },
            {
              "buttonId": "tab_2",
              "text": "BOTTOM2"
            }
          ]
          bottombar.count = 1
        }
      }

      if (buttonId === "bottom1") {
        bottombar.buttonListMenu = [
           {
               "type": textml,
               "buttonId": "bottom1",
               "text": "BOTTOM1"
           },
           {
               "type": text,
               "buttonId": "bottom2",
               "text": "BOTTOM2"
           },
           {
               "type": text,
               "buttonId": "b_new1",
               "text": "B_NEW1"
           },
           {
               "type": text,
               "buttonId": "b_new2",
               "text": "B_NEW2"
           }
        ]
      }
      if (buttonId === "bottom2") {
        bottombar.buttonListMenu = [
           {
               "type": textml,
               "buttonId": "bottom1",
               "text": "BOTTOM1"
           },
           {
               "type": text,
               "buttonId": "bottom2",
               "text": "BOTTOM2"
           }
        ]
      }
      if (buttonId === "tab_1") {
        bottombar.buttonsTabBar = [
          {
            "buttonId": "tab_1",
            "text": "BOTTOM1"
          },
          {
            "buttonId": "tab_2",
            "text": "BOTTOM2"
          }
        ]
      }
      if (buttonId === "tab_2") {
        bottombar.buttonsTabBar = [
          {
            "buttonId": "tab_1",
            "text": "BOTTOM1"
          },
          {
            "buttonId": "tab_2",
            "text": "BOTTOM2"
          },
          {
            "buttonId": "tab_3",
            "text": "BOTTOM3"
          },
          {
            "buttonId": "tab_3",
            "text": "BOTTOM3"
          }
        ]
      }
    }
  }
}
