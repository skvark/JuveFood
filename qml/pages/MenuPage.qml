import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    BusyIndicator {
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: load
    }

    // Update is too fast. This waits for pulley menu animation completion.
    Timer {
        id: timer
        interval: 500; running: false; repeat: false
        onTriggered: updateFoods();
   }

    SilicaListView {

        anchors.fill: parent
        id: listview
        model: foodAPI.getModelByDate

        header: Component {
            PageHeader {
                title: { date + ". Menus" + foodAPI.getModelByDate }
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
                    foodAPI.setModelByDate(new Date());
                }
            }
        }

        contentHeight: page.height
        contentWidth: page.width

        delegate: Row {

            spacing: Theme.paddingLarge
            anchors.left: parent.left
            anchors.leftMargin: margin

            Label {

                width: 520
                wrapMode: Text.WordWrap
                font.pixelSize: size
                text: name
                color: colorize ? Theme.highlightColor : Theme.primaryColor

            }
        }
        VerticalScrollDecorator { flickable: listview }

    }

    property string date: Qt.formatDateTime(new Date(), "d.M");
    property bool load: false;

    function updateFoods() {
        listview.model = foodAPI.getModelByDate
    }

}


