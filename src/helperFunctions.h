#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

void cleanJSON(QByteArray &dirty, bool isInfo);

void nameCompactor(const QString& name, QString& shortName);

QString cleanOpeningHours(QString dirty);

#endif // HELPERFUNCTIONS_H
