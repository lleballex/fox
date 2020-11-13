#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>

#include "general.h"


class MainMenu : public QWidget, private General
{
    Q_OBJECT
public:
    int nextSceneIndex;

    explicit MainMenu(QWidget *parent = nullptr);

private:
    const int buttonsCount = 6;

    QPushButton *buttons = new QPushButton[buttonsCount];

    QString getButtonStyle();

private slots:
    void setLearningScene();
    void setTrainingScene();
    void setExamScene();
    void setDictionaryScene();
    void setLevelChoiceScene();
    void quit();

signals:
    void changeScene();
    void quitProgram();
};


#endif // MAINMENU_H
