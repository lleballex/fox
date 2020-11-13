#ifndef LEARNING_H
#define LEARNING_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>

#include "general.h"
#include "database/verbmodel.h"
#include "database/usermodel.h"


class Learning : public QWidget, private General, private VerbModel, private UserModel
{
    Q_OBJECT
public:
    explicit Learning(QWidget *parent = nullptr);

private:
    int verbIndex;
    int verbsCount;

    QLabel *words = new QLabel;
    QLabel *translate = new QLabel;
    QLabel *image = new QLabel;
    QPushButton *nextButton;

    VerbModel::Verb *verbs;

    void customizeWidget();
    void showEvent(QShowEvent *);

private slots:
    void changeVerb();
    void setMenuScene();

signals:
    void changeScene();
};


#endif // LEARNING_H
