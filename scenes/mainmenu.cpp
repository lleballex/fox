#include "mainmenu.h"
#include "mainwindow.h"

#include <QVBoxLayout>


MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    buttons[0].setText("Изучение");
    buttons[1].setText("Тренировка");
    buttons[2].setText("Экзамен");
    buttons[3].setText("Словарь");
    buttons[4].setText("Уровень");
    buttons[5].setText("Выход");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < buttonsCount; i++) {
        layout->addWidget(&buttons[i]);
        buttons[i].setCursor(Qt::PointingHandCursor);
        buttons[i].setStyleSheet(getButtonStyle());
    }

    setLayout(layout);

    QPixmap pix(":/resources/images/FOX.png");
    image->setParent(this);
    image->setPixmap(pix.scaled(280, 280, Qt::KeepAspectRatio));
    image->resize(210, 280);
    image->move(0, 240);
    image->show();

    connect(&buttons[0], SIGNAL(clicked()), this, SLOT(setLearningScene()));
    connect(&buttons[1], SIGNAL(clicked()), this, SLOT(setTrainingScene()));
    connect(&buttons[2], SIGNAL(clicked()), this, SLOT(setExamScene()));
    connect(&buttons[3], SIGNAL(clicked()), this, SLOT(setDictionaryScene()));
    connect(&buttons[4], SIGNAL(clicked()), this, SLOT(setLevelChoiceScene()));
    connect(&buttons[5], SIGNAL(clicked()), this, SLOT(quit()));
}


QString MainMenu::getButtonStyle()
{
    return QString("QPushButton {"
                   "width: 250px;"
                   "color: #fff;"
                   "font-size: 20px;"
                   "text-transform: uppercase;"
                   "padding: 20px;"
                   "border-radius: 10px;"
                   "background: %1;"
                   "}"
                   "QPushButton:hover {"
                   "background: %2;"
                   "}").arg(WIDGET_COLOR).arg(LIGHT_WIDGET_COLOR);
}


void MainMenu::setLearningScene()
{
    nextSceneIndex = MainWindow::LEARNING_INDEX;
    emit changeScene();
}


void MainMenu::setTrainingScene()
{
    nextSceneIndex = MainWindow::TRAINING_INDEX;
    emit changeScene();
}


void MainMenu::setExamScene()
{
    nextSceneIndex = MainWindow::EXAM_INDEX;
    emit changeScene();
}


void MainMenu::setDictionaryScene()
{
    nextSceneIndex = MainWindow::DICTIONARY_INDEX;
    emit changeScene();
}


void MainMenu::setLevelChoiceScene()
{
    nextSceneIndex = MainWindow::LEVEL_CHOICE_INDEX;
    emit changeScene();
}


void MainMenu::quit()
{
    emit quitProgram();
}
