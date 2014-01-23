import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            anchors.rightMargin: Theme.paddingLarge

            PageHeader { title: qsTr("About JuveFood") }

            Label {
                width: parent.width
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                text: "Created by skvark. JuveFood icon by fercen.\n\n" +
                      "This software is released under MIT license.\n\n" +
                      "You can get the code and contribute at:\n" +
                      "http://github.com/skvark/JuveFood"
            }
        }
    }
}