#ifndef USERMODEL_H
#define USERMODEL_H


class UserModel
{
public:
    UserModel();

protected:
    struct User {
        int level;
    };

    User getUser();
    void setUser(int level);
};


#endif // USERMODEL_H
