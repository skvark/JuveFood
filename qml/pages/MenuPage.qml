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
        model: foodModel

        header: Component {
            PageHeader {
                title: { date + ". Menus" }
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
                    dialog.accepted.connect(function() {
                                foodModel.clear();
                            })
                }
            }
            MenuItem {
                text: "Update"
                onClicked: {
                    timer.start()
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

        ViewPlaceholder {
            enabled: listview.count == 0 && !load
            text: "No restaurants added yet. You can add them in settings."
        }

        ViewPlaceholder {
            enabled: listview.count == 1 && !load
            text: "No menus available for any of your selected restaurants today."
        }
    }

    ListModel {
        id: foodModel
    }

    property string date: Qt.formatDateTime(new Date(), "d.M");
    property bool load: true;

    function updateFoods() {
        foodModel.clear();
        foodAPI.update();
        date = Qt.formatDateTime(new Date(), "d.M");
    }

    Connections {
        target: foodAPI
        onLoading: {
            load = loading;
        }

        onDataReady: {
            if (foods.length > 0) {
                for(var i = 0; i < foods.length; ++i) {

                    if (i === 0) {
                        foodModel.append({"name": foodAPI.foods[i],
                                          "size": 28,
                                          "margin": 10,
                                          "colorize": true,
                                         });
                    } else if (!foodAPI.foods[i-1].length > 0) {
                        foodModel.append({"name": foodAPI.foods[i],
                                          "size": 28,
                                          "margin": 10,
                                          "colorize": true,
                                         });
                    } else {
                        foodModel.append({"name": foodAPI.foods[i],
                                          "size": 26,
                                          "margin": 20,
                                          "colorize": false,
                                         });
                    }
                }
            } else {
                foodModel.append({"name": "",
                                  "size": 40,
                                  "margin": 10,
                                  "colorize": false,
                                 });
            }
        }
    }
}


