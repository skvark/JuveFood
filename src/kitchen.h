#ifndef KITCHEN_H
#define KITCHEN_H
#include <QList>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QDate>

class Kitchen
{
public:
    Kitchen(unsigned int kitchenId,
            unsigned int kitchenInfoId,
            unsigned int openInfoId,
            unsigned int menuTypeId,
            QString name);

    QString getKitchenName();
    QList<QPair<QString, QString> > getByWeekdayQuery(QString lang);

private:

    // Kitchen ID
    unsigned int kitchenId_;
    // Kitchen ID for opening hours etc.
    unsigned int kitchenInfoId_;
    // not sure what this does o.o
    unsigned int openInfoId_;
    // menutype
    unsigned int menuTypeId_;
    // kitchen name
    QString name_;

};

#endif // KITCHEN_H
