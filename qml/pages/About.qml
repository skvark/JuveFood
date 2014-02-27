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
                height: 800
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                textFormat: Text.RichText;
                onLinkActivated: Qt.openUrlExternally(link)
                text: "<h1>JuveFood 0.1-2</h1><br /><br />" +
                      "Created by Olli-Pekka Heinisuo. JuveFood icon and cover by Janne Peltonen.<br /><br />" +
                      "This software is released under MIT license.\n\n" +
                      "You can get the code and contribute at:\n" +
                      "<style>a:link { color: " + Theme.highlightColor + "; }</style>" +
                      "<a href='http://github.com/skvark/JuveFood'>JuveFood - GitHub</a>";
            }
        }
    }
}
