import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    BusyIndicator {
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: load
    }

    SilicaFlickable {
        anchors.fill: parent

        PullDownMenu {

            MenuItem {
                text: "About"
                onClicked: {
                    pageStack.push("About.qml")
                }
            }

            MenuItem {

                text: "Settings"
                onClicked: {
                    var dialog = pageStack.push("Settings.qml")
                    dialog.accepted.connect(function() {
                                foodModel.clear();
                            }
                    )
                    dialog.rejected.connect(function() {
                                foodModel.clear();
                            }
                    )
                }
            }
            MenuItem {
                text: "Update"
                onClicked: {
                    foodModel.clear();
                    foodAPI.update();
                }
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height
        contentWidth: column.width

        Column {
            id: column
            spacing: Theme.paddingSmall

            PageHeader {
                title: Qt.formatDateTime(new Date(), "d.M") + ". Menus"
            }

            SilicaListView {
                id: listview
                width: 480; height: 800
                model: foodModel

                ViewPlaceholder {
                    enabled: listview.count == 0 && !load
                    text: "No restaurants added yet. You can add them in settings."
                }

                delegate: Row {

                    spacing: Theme.paddingLarge
                    anchors.left: parent.left
                    anchors.leftMargin: margin


                    Label {
                        width: 480
                        wrapMode: Text.WordWrap
                        font.pixelSize: size
                        text: name
                        color: colorize ? Theme.highlightColor : Theme.primaryColor
                    }
                }
            }
        }
    }

    ListModel {
        id: foodModel
    }

    property bool load: true;

    Connections {
        target: foodAPI
        onLoading: {
            load = loading;
        }
        onDataReady: {
            var colorizer = false;
            for(var i = 0; i < foods.length; ++i) {

                if (i === 0) {
                    foodModel.append({"name": foodAPI.foods[i],
                                      "size": 28,
                                      "margin": 10,
                                      "colorize": false});
                } else if (!foodAPI.foods[i-1].length > 0) {
                    foodModel.append({"name": foodAPI.foods[i],
                                      "size": 28,
                                      "margin": 10,
                                      "colorize": false});
                } else {
                    foodModel.append({"name": foodAPI.foods[i],
                                      "size": 26,
                                      "margin": 20,
                                      "colorize": colorizer});
                    if (colorizer) {
                        colorizer = false;
                    } else {
                        colorizer = true;
                    }
                }
            }
        }
    }
}


