import QtQuick 2.13
import ccOS.GUI.Window 1.0
import ccOS.GUI.Controls 1.0
import ccOS.StatusBarAddon 1.0

HWindow {
    id: window
    objectName: "EXAMPLE.FrontWindow"

    width: 1920
    height: 106

    property alias statusbar:statusbar
    property int statusbarheight: 106

    Rectangle {
        id: btn_create
        y: 200
        width: 320; height: 100
        color: "lightgray"
        objectName: "MyBtn1"
        signal createSignal()

        Text {
            id: text1
            text: "Create"
            y: 30
            anchors.horizontalCenter: page.horizontalCenter
            font.pointSize: 24; font.bold: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                btn_create.createSignal()
            }
        }
    }

    Rectangle {
        id: btn_show
        y: 350
        width: 320; height: 100
        color: "lightgray"
        objectName: "MyBtn2"
        signal showSignal()

        Text {
            id: text2
            text: "Show"
            y: 30
            anchors.horizontalCenter: page.horizontalCenter
            font.pointSize: 24; font.bold: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                btn_show.showSignal()
            }
        }
    }

    Rectangle {
        id: btn_hide
        y: 500
        width: 320; height: 100
        color: "lightgray"
        objectName: "MyBtn3"
        signal hideSignal()

        Text {
            id: text3
            text: "Hide"
            y: 30
            anchors.horizontalCenter: page.horizontalCenter
            font.pointSize: 24; font.bold: true
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                btn_hide.hideSignal()
            }
        }
    }

    FocusScope {
        anchors.fill: parent
        focus : true
        ////////////////////////////////////////////////////
        // statusbar area - start
        ////////////////////////////////////////////////////
        HStatusBar{
            id : statusbar
            anchors.right: parent
            buttonList :[back, home, menu]

            onButtonPressed:{
                console.log("onButtonPressed : " + buttonId);
                if(buttonId === back){
                    sceneStackView.pop()
                }else if(buttonId === list){
                     // todo ...
                }else if(buttonId === menu){
                    if (optionMenu.visible)
                        optionMenu.hide()
                    else
                        optionMenu.show()
                }

                statusbar.focusMover.currentItem.forceActiveFocus();
                //sceneStackView.focus = false;
            }

           Component.onCompleted: {
           }

           Keys.onReleased: {
              console.log("[statusbar]Keys.onReleased : "+event.key+" Qt.Key_4: "+Qt.Key_4+" Qt.Key_6:"+Qt.Key_6)

              if (event.key === Qt.Key_2) {
                  statusbar.focusMover.currentItem.focus = false
                  sceneStackView.focus = true;
              }
           }

        }
        ////////////////////////////////////////////////////
        // statusbar area - end
        ////////////////////////////////////////////////////
            
 
              HSceneStackView {
                id: sceneStackView
                objectName: "HSceneStackView"
                focus: true

                width: contentBackground.width
                height: contentBackground.height

                visible: true
                entryScene: "EXAMPLE.Main"


                }
     }
}
