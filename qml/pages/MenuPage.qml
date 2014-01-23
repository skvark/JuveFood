import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

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
                title: Qt.formatDateTime(new Date(), "d.M") + "   Menus"
            }

            SilicaListView {
                id: listview
                width: 480; height: 800
                model: foodModel

                ViewPlaceholder {
                    enabled: listview.count == 0
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

    Connections {
        target: foodAPI
        onDataReady: {
            var colorizer = false;
            if (foods.length === 1) {

            }
            for(var i = 0; i < foods.length; ++i) {
                if (i === 0) {
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


