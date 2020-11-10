#include "levelchoice.h"

#include <QLabel>
#include <QEvent>
#include <QVBoxLayout>


LevelChoice::LevelChoice(QWidget *parent) : QWidget(parent)
{
    level = getUser().level;

    showFooter(this);

    QPixmap pixmap(":/resources/icons/favicon.svg");
    icon.addPixmap(pixmap);

    customizeWidget();

    for(int i = 0; i < levelsCount; i++) buttons[i].installEventFilter(this);

    connect(getMenuButton(), SIGNAL(clicked()), this, SLOT(setMenuScene()));
}


void LevelChoice::customizeWidget()
{
    QLabel *label = new QLabel("Выбери уровень:");
    label->setStyleSheet("QLabel {"
                         "color: #fff;"
                         "font-size: 30px;"
                         "qproperty-alignment: AlignHCenter;"
                         "}");

    buttons[0].setText("Начальный");
    buttons[1].setText("Средний");
    buttons[2].setText("Продвинутый");
    buttons[level - 1].setIcon(icon);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    layout->addSpacing(30);

    for(int i = 0; i < levelsCount; i++) {
        layout->addWidget(&buttons[i]);
        buttons[i].setIconSize(QSize(40, 40));
        buttons[i].setCursor(Qt::PointingHandCursor);
        buttons[i].setStyleSheet(QString("QPushButton {"
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
                                         "}").arg(WIDGET_COLOR).arg(LIGHT_WIDGET_COLOR));
    }

    QWidget *widget = new QWidget(this);
    widget->setGeometry(0, FOOTER_MARGIN, WINDOW_WIDTH, WINDOW_HEIGHT - FOOTER_HEIGHT - FOOTER_MARGIN);
    widget->setLayout(layout);
    widget->show();
}


bool LevelChoice::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() != QEvent::MouseButtonPress) return false;

    for(int i = 0; i < levelsCount; i++) {
        if(object == &buttons[i]) {
            buttons[i].setIcon(icon);
            setUser(i + 1);
        } else buttons[i].setIcon(QIcon());
    }

    return true;
}


void LevelChoice::setMenuScene()
{
    emit changeScene();
}
