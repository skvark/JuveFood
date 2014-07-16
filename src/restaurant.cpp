#include "restaurant.h"

Restaurant::Restaurant(QString name,
                       QString shortName,
                       QList<QString> foods):
    name_(name),
    shortname_(shortName),
    foods_(foods)
{}

QString Restaurant::getName()
{
    return name_;
}

QString Restaurant::getShortName()
{
    return shortname_;
}

QList<QString> Restaurant::getFoods()
{
    return foods_;
}

void Restaurant::setName(QString name)
{
    name_ = name;
}

void Restaurant::setShortName(QString shortname)
{
    shortname_ = shortname;
}

void Restaurant::setFoods(QList<QString> foods)
{
    foods_ = foods;
}
