#include "learning.h"

#include <QVBoxLayout>


Learning::Learning(QWidget *parent) : QWidget(parent)
{
    showFooter(this);
    nextButton = addFooterButton("Дальше");

    customizeWidget();

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
    widget->setGeometry(0, FOOTER_MARGIN, WINDOW_WIDTH, WINDOW_HEIGHT - FOOTER_HEIGHT - FOOTER_MARGIN);
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

    if(nextButton->isHidden()) nextButton->show();
}


void Learning::changeVerb()
{
    if(verbIndex + 2 >= verbsCount) nextButton->hide();
    if(verbIndex + 1 >= verbsCount) return;

    verbIndex++;

    words->setText(QString("%1 - %2 - %3").arg(verbs[verbIndex].v1).arg(verbs[verbIndex].v2).arg(verbs[verbIndex].v3));
    translate->setText(verbs[verbIndex].translate);

    if(!QString(verbs[verbIndex].image).isEmpty()) {
        QPixmap pixmap(QString(":/verbs/resources/images/%1").arg(verbs[verbIndex].image));
        image->setPixmap(pixmap.scaledToHeight(300));
        image->show();
    } else image->hide();
}


void Learning::setMenuScene()
{
    emit changeScene();
}
