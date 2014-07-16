#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QString>
#include <QList>

class Restaurant
{
public:
    Restaurant(QString name, QString shortName, QList<QString> foods);

    QString getName();
    QString getShortName();
    QList<QString> getFoods();

    void setName(QString name);
    void setShortName(QString shortname);
    void setFoods(QList<QString> foods);

private:
    QString name_;
    QString shortname_;
    QList<QString> foods_;


};

#endif // RESTAURANT_H
