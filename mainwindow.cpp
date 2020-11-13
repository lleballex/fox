#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    setWindowTitle(WINDOW_TITLE);
    setWindowIcon(getFavicon());
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setPalette(getMainPalette());
    setCentralWidget(mainWidget);
    setStyleSheet(getMainStyle());
    loadFonts();

    mainWidget->addWidget(mainMenu);
    mainWidget->addWidget(learning);
    mainWidget->addWidget(training);
    mainWidget->addWidget(exam);
    mainWidget->addWidget(dictionary);
    mainWidget->addWidget(levelChoice);
    mainWidget->setCurrentIndex(MAIN_MENU_INDEX);

    connect(mainMenu, SIGNAL(changeScene()), this, SLOT(changeScene()));
    connect(learning, SIGNAL(changeScene()), this, SLOT(changeScene()));
    connect(training, SIGNAL(changeScene()), this, SLOT(changeScene()));
    connect(exam, SIGNAL(changeScene()), this, SLOT(changeScene()));
    connect(dictionary, SIGNAL(changeScene()), this, SLOT(changeScene()));
    connect(levelChoice, SIGNAL(changeScene()), this, SLOT(changeScene()));
    connect(mainMenu, SIGNAL(quitProgram()), this, SLOT(quitProgram()));
}


MainWindow::~MainWindow() {}


void MainWindow::changeScene()
{
    if(mainWidget->currentIndex() == MAIN_MENU_INDEX) {
        mainWidget->setCurrentIndex(mainMenu->nextSceneIndex);
    } else mainWidget->setCurrentIndex(MAIN_MENU_INDEX);
}


void MainWindow::quitProgram()
{
    close();
}
