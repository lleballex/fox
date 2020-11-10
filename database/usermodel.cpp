#include "usermodel.h"

#include <QVariant>
#include <QSqlQuery>


UserModel::UserModel() {}


UserModel::User UserModel::getUser()
{
    QSqlQuery query("SELECT * FROM user");
    query.next();

    UserModel::User user;
    user.level = query.value(0).toInt();

    return user;
}


void UserModel::setUser(int level)
{
    QSqlQuery query(QString("UPDATE user SET level = %1").arg(level));
}
