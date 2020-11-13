#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "general.h"
#include "scenes/mainmenu.h"
#include "scenes/learning.h"
#include "scenes/training.h"
#include "scenes/exam.h"
#include "scenes/dictionary.h"
#include "scenes/levelchoice.h"


class MainWindow : public QMainWindow, private General
{
    Q_OBJECT

public:
    static const int MAIN_MENU_INDEX = 0;
    static const int LEARNING_INDEX = 1;
    static const int TRAINING_INDEX = 2;
    static const int EXAM_INDEX = 3;
    static const int DICTIONARY_INDEX = 4;
    static const int LEVEL_CHOICE_INDEX = 5;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStackedWidget *mainWidget = new QStackedWidget;

    MainMenu *mainMenu = new MainMenu;
    Learning *learning = new Learning;
    Training *training = new Training;
    Exam *exam = new Exam;
    Dictionary *dictionary = new Dictionary;
    LevelChoice *levelChoice = new LevelChoice;

private slots:
    void changeScene();
    void quitProgram();
};


#endif // MAINWINDOW_H
