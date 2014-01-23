#include "kitchen.h"

Kitchen::Kitchen(unsigned int kitchenId,
                 unsigned int kitchenInfoId,
                 unsigned int openInfoId,
                 unsigned int menuTypeId,
                 QString name):

                 kitchenId_(kitchenId),
                 kitchenInfoId_(kitchenInfoId),
                 openInfoId_(openInfoId),
                 menuTypeId_(menuTypeId),
                 name_(name)
{}

QString Kitchen::getKitchenName()
{
    return name_;
}

QList<QPair<QString, QString> > Kitchen::getByWeekdayQuery(QString lang)
{
    // format:
    // GetMenuByWeekday?KitchenId=6&MenuTypeId=60&Week=50&Weekday=3&lang='fi'&format=json
    QDate date = QDate::currentDate();
    QList<QPair<QString, QString> > query;

    QString language = "Finnish";
    if(QString::compare(lang, language) == 0) {
        language = "'fi'";
    } else {
        language = "'en'";
    }

    // Add query components to a list
    query.append(qMakePair(QString("KitchenId"), QString::number(kitchenId_, 10)));
    query.append(qMakePair(QString("MenuTypeId"), QString::number(menuTypeId_, 10)));
    query.append(qMakePair(QString("Week"), QString::number(date.weekNumber(), 10)));
    query.append(qMakePair(QString("Weekday"), QString::number(date.dayOfWeek(), 10)));
    query.append(qMakePair(QString("lang"), language));
    query.append(qMakePair(QString("format"), QString("json")));

    return query;
}