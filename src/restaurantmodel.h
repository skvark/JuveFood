#ifndef RESTAURANTMODEL_H
#define RESTAURANTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include <restaurant.h>
#include <QString>
#include <QDate>
#include <QDebug>

class RestaurantModel : public QAbstractListModel
 {
     Q_OBJECT
 public:
     enum RestaurantRoles {
         NameRole,
         ShortNameRole,
         FoodRole
     };

     RestaurantModel(QObject *parent = 0);
     void addRestaurant(Restaurant* restaurant);
     int rowCount(const QModelIndex & parent = QModelIndex()) const;
     QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
     Restaurant *alreadyAdded(QString name);

public slots:

protected:
     QHash<int, QByteArray> roleNames() const;

private:
     QList<Restaurant*> restaurants_;
 };

Q_DECLARE_METATYPE(RestaurantModel*)

#endif // RESTAURANTMODEL_H
