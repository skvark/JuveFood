import QtQuick 2.0
import Sailfish.Silica 1.0
import "helper.js" as Helper

Dialog {

    id: page
    onAccepted: { save(); }
    Component.onCompleted: {
        getSettings();
        settingsLoad = foodAPI.settingsLoadingStatus();
    }

    BusyIndicator {
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: settingsLoad
    }

    SilicaFlickable {
        anchors.fill: parent
        width: parent.width
        contentHeight: childrenRect.height

        DialogHeader {
            id: header
            acceptText: "Save"
        }

        Column {
            id: content
            spacing: Theme.paddingSmall
            width: parent.width
            anchors.top: header.bottom
            height: 200

            ComboBox {
                id: combo
                parent: content
                width: 540
                label: "Language"
                currentIndex: language

                menu: ContextMenu {
                    id: combocontent
                    MenuItem {
                        text: "Finnish"
                        height: 60
                    }
                    MenuItem {
                        text: "English"
                        height: 60
                    }
                }
            }

        }

        anchors.leftMargin: Theme.paddingMedium

        SilicaListView {
            parent: page
            id: listView
            y: 390
            width: parent.width;
            height: 500
            model: restaurantModel

            delegate: BackgroundItem {
                id: delegate
                down: check
                width: parent.width
                anchors.left: parent.left;

                Label {
                    id: kitchenlabel
                    font.pixelSize: 26
                    wrapMode: Text.WordWrap
                    text: name
                    width: parent.width
                    height: parent.height
                    anchors.left: parent.left;
                    anchors.leftMargin: Theme.paddingMedium
                    verticalAlignment: Text.AlignVCenter
                    color: delegate.highlighted ? Theme.highlightColor : Theme.primaryColor
                }
                onClicked: select(kitchenlabel.text, index)

                function select(name, index) {
                    if (Helper.selected.indexOf(name) !== -1) {
                        Helper.selected.splice(Helper.selected.indexOf(name), 1);
                        restaurantModel.setProperty(index, "check", false)
                    } else {
                        Helper.selected.push(name);
                        restaurantModel.setProperty(index, "check", true)
                    }
                }

            }
            VerticalScrollDecorator {
                flickable: listView

            }
        }
    }

    ListModel {
        id: restaurantModel
    }

    function save() {
        Helper.selected.push(combo.value);
        foodAPI.saveSettings(Helper.selected);
    }

    property int language: 0;
    property bool settingsLoad: true;

    Connections {
        target: foodAPI
        onSettingsLoading: {
            settingsLoad = settingsLoading;
        }
    }

    function getSettings() {

        var restaurants = foodAPI.getKitchenNameList().sort();
        var settings = foodAPI.loadSettings();

        if (settings[settings.length-1] === "Finnish") {
            language = 0;
        } else if (settings[settings.length-1] === "English") {
            language = 1;
        }
        combo._updateCurrent(language, settings[settings.length-1])

        for(var i = 0; i < restaurants.length; ++i) {

            if (i !== restaurants.length - 1) {
                if (settings.indexOf(restaurants[i]) > -1) {
                    restaurantModel.append({"name": restaurants[i], "check": true});
                    Helper.selected.push(restaurants[i]);
                } else {
                    restaurantModel.append({"name": restaurants[i], "check": false});
                }
            }
        }
    }
}





