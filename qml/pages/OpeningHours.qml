import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: openinghours
    property string name

    SilicaFlickable {
        id: info
        anchors.fill: parent
        contentHeight: column.height

        Column {
            id: column
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: Theme.paddingLarge
            anchors.rightMargin: Theme.paddingLarge

            PageHeader { title: qsTr("Opening Hours") }

            Label {
                width: parent.width
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                textFormat: Text.RichText;
                onLinkActivated: Qt.openUrlExternally(link)
                text: name + "<br /><br />"
            }

            Label {
                width: parent.width
                wrapMode: Text.Wrap
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                textFormat: Text.RichText;
                onLinkActivated: Qt.openUrlExternally(link)
                text: foodAPI.getOpeningHours(name);
            }
        }
        VerticalScrollDecorator { flickable: info }
    }
}
