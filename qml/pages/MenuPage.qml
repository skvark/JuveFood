import QtQuick 2.0
import Sailfish.Silica 1.0
import "helper.js" as Helper

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
        onTriggered: update();
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
                    id: days
                    OneDayFood { id: foods1 }
                    OneDayFood { id: foods2 }
                    OneDayFood { id: foods3 }
                    OneDayFood { id: foods4 }
                    OneDayFood { id: foods5 }
                    OneDayFood { id: foods6 }
                    OneDayFood { id: foods7 }
            }

    }

    // initial date
    property var first_date

    function addDays(theDate, days) {
        return new Date(theDate.getTime() + days*24*60*60*1000);
    }

    // called upon startup: sets initial starting point and populates all models
    function initialize(date) {

        first_date = date;
        foodAPI.setDate(first_date);

        foodAPI.createNewModel(date);
        foods1.initialize(date);

        foodAPI.createNewModel(addDays(date, 1));
        foods2.initialize(addDays(date, 1));

        foodAPI.createNewModel(addDays(date, 2));
        foods3.initialize(addDays(date, 2));

        foodAPI.createNewModel(addDays(date, 3));
        foods4.initialize(addDays(date, 3));

        foodAPI.createNewModel(addDays(date, 4));
        foods5.initialize(addDays(date, 4));

        foodAPI.createNewModel(addDays(date, 5));
        foods6.initialize(addDays(date, 5));

        foodAPI.createNewModel(addDays(date, 6));
        foods7.initialize(addDays(date, 6));

        foodAPI.init();

    }

    // reinitialize all visualitemmodels with new models
    // (if day has chnaged) and update data
    function update() {
        if (first_date.getDay() !== (new Date()).getDay()) {
            foodAPI.deleteModel(first_date);
            first_date = new Date();
            foodAPI.createNewModel(addDays(first_date, 6));
            reInitialize(first_date);
        } else {
            foodAPI.update();
        }
    }

    // updates slideshows views +1 day
    // date parameter is the new starting date
    function reInitialize(date) {
        foods1.initialize(date);
        foods2.initialize(addDays(date, 1));
        foods3.initialize(addDays(date, 2));
        foods4.initialize(addDays(date, 3));
        foods5.initialize(addDays(date, 4));
        foods6.initialize(addDays(date, 5));
        foods7.initialize(addDays(date, 6));
        foodAPI.update();
    }

    function getDayNameOfWeek(day) {
        return Helper.weekday[day];
    }

    Component.onCompleted: {
        initialize(new Date());
    }
}


