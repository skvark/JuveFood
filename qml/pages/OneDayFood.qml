import QtQuick 2.0
import Sailfish.Silica 1.0
import juvefood.restaurants 1.0

Item {

    height: menuView.height;
    width: menuView.width
    property string headerdate: ""
    property string month: ""
    property string dayofweek: ""

    function initialize(date) {
        headerdate = date.getDate().toString()
        month = (date.getMonth() + 1).toString()
        dayofweek = getDayNameOfWeek(date.getDay());
        listview.model = foodAPI.getModelByDate;
    }

    SilicaListView {

        id: listview

        header: Component {
            PageHeader {
                title: { dayofweek + " " + headerdate + "." + month + ". Menus"}
            }
        }

        PullDownMenu {
            id: menu
            MenuItem {
                text: "About"
                onClicked: {
                    pageStack.push("About.qml")
                }
            }
            MenuItem {

                text: "Settings"
                onClicked: {
                    var dialog = pageStack.push("Settings.qml");
                }
            }
            MenuItem {
                text: "Update"
                onClicked: {
                    timer.start();
                }
            }
        }

        anchors.fill: parent

        delegate: ListItem {

            width: parent.width
            height: background.height + Theme.paddingMedium
            anchors.topMargin: Theme.paddingMedium
            anchors.bottomMargin: Theme.paddingMedium

            Rectangle {
                anchors.fill: background
                radius: 5;
                color: Theme.rgba(Theme.highlightBackgroundColor, 0.3)
            }

            BackgroundItem {

                id: background
                anchors.left: parent.left;
                anchors.leftMargin: Theme.paddingMedium
                anchors.right: parent.right;
                anchors.rightMargin: Theme.paddingMedium
                height: header.height + foodcontent.height + 20;
                onClicked: pageStack.push(Qt.resolvedUrl("OpeningHours.qml"), { name: name })

            }

            Column {
                    id: column
                    anchors.left: parent.left;
                    anchors.leftMargin: Theme.paddingMedium
                    anchors.right: parent.right;
                    anchors.rightMargin: Theme.paddingMedium
                    spacing: Theme.paddingMedium

                    Label {
                        id: header
                        anchors.left: parent.left;
                        anchors.right: parent.right
                        textFormat: Text.RichText
                        text: shortname
                        anchors.leftMargin: 10
                        font.pixelSize: Theme.fontSizeLarge
                        truncationMode: TruncationMode.Fade
                    }

                    Label {
                        id: foodcontent
                        anchors.left: parent.left;
                        anchors.right: parent.right
                        anchors.leftMargin: 15
                        textFormat: Text.RichText
                        text: {
                            if(food == "") {
                                return "No menu available for this day.";
                            } else {
                                return food;
                            }
                        }
                        wrapMode: Text.Wrap
                        font.pixelSize: Theme.fontSizeSmall
                    }

                }

            }

        contentHeight: page.height
        contentWidth: page.width

        ViewPlaceholder {
            enabled: listview.count == 0
            text: "No menus available for any of your selected restaurants for this day."
        }

        VerticalScrollDecorator { flickable: listview }
    }
}

