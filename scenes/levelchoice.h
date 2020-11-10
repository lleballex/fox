#ifndef LEVELCHOICE_H
#define LEVELCHOICE_H

#include <QWidget>
#include <QPushButton>

#include "general.h"
#include "database/usermodel.h"


class LevelChoice : public QWidget, private General, private UserModel
{
    Q_OBJECT
public:
    explicit LevelChoice(QWidget *parent = nullptr);

private:
    int levelsCount = 3;
    int level;

    QIcon icon;
    QPushButton *buttons = new QPushButton[levelsCount];

    void customizeWidget();
    bool eventFilter(QObject *object, QEvent *event);

private slots:
    void setMenuScene();

signals:
    void changeScene();
};


#endif // LEVELCHOICE_H
