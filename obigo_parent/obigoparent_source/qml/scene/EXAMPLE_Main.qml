import QtQuick 2.13
import ccOS.GUI.Window 1.0
import ccOS.GUI.Controls 1.0

HScene {
    id : scene
    sceneID: "EXAMPLE.Main"
    property var form: scene.loader.item

//    loader.sourceComponent: Component {
//        EXAMPLE_Main_Form {
//            allMenuListView.delegate: AllMenuWidgetBase {

//         }
//     }
//}
    Component.onCompleted: {

    }
}
