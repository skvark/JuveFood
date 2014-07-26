import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: page

    BusyIndicator {
        anchors.centerIn: parent
        size: BusyIndicatorSize.Large
        running: false
    }

    // Update is too fast. This waits for pulley menu animation completion.
    Timer {
        id: timer
        interval: 500; running: false; repeat: false
        onTriggered: updateFoods();
   }


   SlideshowView {

            id: menuView
            itemWidth: width
            itemHeight: height
            height: window.height
            clip: true

            anchors {
                top: parent.top;
                left: parent.left;
                right: parent.right
            }

            model: VisualItemModel {
                    OneDayFood { id: ruoka }
                    OneDayFood { id: ruoka2 }
                }

    }

    // initial date
    property var date: new Date();
    property int current_difference: 0;

    function increaseDate() {
        date.setDate(date.getDate() + 1);
        ++current_difference;
    }

    function decreaseDate() {
        date.setDate(date.getDate() + 1);
        --current_difference;
    }

    function checkDateLimit() {
        if(current_difference < 7 && current_difference > -7) {
            return true;
        } else {
            return false;
        }
    }

    function updateFoods() {
        foodAPI.setModelByDate(date);
    }

    Connections {
           target: foodAPI
           onModelChanged: {
               listview.model = foodAPI.getModelByDate
           }
    }
}


