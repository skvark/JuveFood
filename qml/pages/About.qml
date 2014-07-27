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

            PageHeader { title: qsTr("About") }

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
                text: "<h1>JuveFood</h1>v"+APP_VERSION+"<br /><br />" +

                      "<style> .legend { font-size: 20px;  } </style>" +

                      "<span class=\"legend\">Created by</span><br />Olli-Pekka Heinisuo<br /><br />" +
                      "<span class=\"legend\">Icon and cover image by</span><br />Janne Peltonen<br /><br /><br />" +

                      "<font style=\"font-size: 23px;\">This software is released under MIT license.<br />" +
                      "You can get the code and contribute at:</font>\n" +
                      "<style>a:link { color: " + Theme.highlightColor + "; }</style><br />" +
                      "<a href='http://github.com/skvark/JuveFood'>GitHub \\ JuveFood</a>";
            }
        }
    }
}
