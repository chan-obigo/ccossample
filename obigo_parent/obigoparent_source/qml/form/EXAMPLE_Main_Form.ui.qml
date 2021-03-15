import QtQuick 2.13
import QtQuick.Controls 2.13
import ccOS.GUI.Controls 1.0

Item {
    id: exampleMainForm
    objectName: "EXAMPLE.Main.Form"

    property int allMenuItemWidth: 316
    property int allMenuItemheight: 604
    property alias allMenuListView : allMenuListView

    ListView{
        id :allMenuListView
        width: parent.width
        height: parent.height
        orientation: ListView.Horizontal

        model: allMenuListModel
    }
}
