#include "restaurantmodel.h"
#include "Restaurant.h"


RestaurantModel::RestaurantModel(QObject *parent)
     : QAbstractListModel(parent)
 {

 }

QHash<int, QByteArray> RestaurantModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ShortNameRole] = "shortname";
    roles[FoodRole] = "food";
    roles[HeightRole] = "foodheight";
    return roles;
}

 void RestaurantModel::addRestaurant(Restaurant* restaurant)
 {
     beginInsertRows(QModelIndex(), rowCount(), rowCount());
     restaurants_.append(restaurant);
     qDebug() << restaurant->getName();
     endInsertRows();
 }

 int RestaurantModel::rowCount(const QModelIndex & parent) const {
     return restaurants_.size();
 }

 Restaurant* RestaurantModel::alreadyAdded(QString name) {
     Restaurant* placeholder = nullptr;
     foreach(auto restaurant, restaurants_) {
         if(restaurant->getName() == name) {
             return restaurant;
         }
     }
     return placeholder;
 }

 QVariant RestaurantModel::data(const QModelIndex & index, int role) const {

     if (index.row() < 0 || index.row() > restaurants_.count())
         return QVariant();

     Restaurant *restaurant = restaurants_[index.row()];
     if (role == NameRole)
         return restaurant->getName();
     else if (role == ShortNameRole)
         return restaurant->getShortName();
     else if (role == FoodRole) {
         QString foods = "";
         foreach(auto food, restaurant->getFoods()) {
             foods.append(food + "<br />");
         }
         return foods;
     }
     else if (role == HeightRole) {
         return 35;
     }
     return QVariant();
 }
