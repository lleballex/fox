#include "learning.h"

#include <QVBoxLayout>
#include <QHBoxLayout>


Learning::Learning(QWidget *parent) : QWidget(parent)
{
    showFooter(this);
    backButton = addFooterButton("Назад");
    nextButton = addFooterButton("Дальше");

    customizeWidget();
    percentPanel->show(this, WINDOW_WIDTH);

    connect(backButton, SIGNAL(clicked()), this, SLOT(goBack()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(changeVerb()));
    connect(getMenuButton(), SIGNAL(clicked()), this, SLOT(setMenuScene()));
}


void Learning::customizeWidget()
{
    words->setStyleSheet("QLabel {"
                         "color: #fff;"
                         "font-size: 30px;"
                         "qproperty-alignment: AlignHCenter;"
                         "}");

    translate->setStyleSheet("QLabel {"
                             "color: #fff;"
                             "font-size: 30px;"
                             "qproperty-alignment: AlignHCenter;"
                             "}");

    image->setStyleSheet("QLabel {"
                         "qproperty-alignment: AlignHCenter;"
                         "}");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(10);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(words);
    layout->addWidget(translate);
    layout->addWidget(image);

    QWidget *widget = new QWidget(this);
    widget->setGeometry(0, percentPanel->height(), WINDOW_WIDTH, WINDOW_HEIGHT - FOOTER_HEIGHT - percentPanel->height());
    widget->setLayout(layout);
    widget->show();
}


void Learning::showEvent(QShowEvent *)
{
    int level = getUser().level;
    verbIndex = -1;
    verbsCount = getVerbsCount(level);
    verbs = getVerbs(level);

    changeVerb();

    if(!backButton->isHidden()) backButton->hide();
    if(nextButton->isHidden()) nextButton->show();
}


void Learning::changeVerb()
{
    if(verbIndex + 2 >= verbsCount) nextButton->hide();
    if(verbIndex + 1 >= verbsCount) return;
    if(backButton->isHidden()) backButton->show();

    verbIndex++;

    percentPanel->update(int((verbIndex + 1.f) / verbsCount * 100));
    words->setText(QString("%1 - %2 - %3").arg(verbs[verbIndex].v1).arg(verbs[verbIndex].v2).arg(verbs[verbIndex].v3));
    translate->setText(verbs[verbIndex].translate);

    QPixmap pixmap(QString("./resources/images/%1.png").arg(verbs[verbIndex].v1));
    image->setPixmap(pixmap.scaledToHeight(300));
}


void Learning::goBack()
{
    if(verbIndex == 1) backButton->hide();
    if(nextButton->isHidden()) nextButton->show();

    verbIndex--;

    percentPanel->update(int((verbIndex + 1.f) / verbsCount * 100));
    words->setText(QString("%1 - %2 - %3").arg(verbs[verbIndex].v1).arg(verbs[verbIndex].v2).arg(verbs[verbIndex].v3));
    translate->setText(verbs[verbIndex].translate);

    QPixmap pixmap(QString("./resources/images/%1.png").arg(verbs[verbIndex].v1));
    image->setPixmap(pixmap.scaledToHeight(300));
}


void Learning::setMenuScene()
{
    emit changeScene();
}
