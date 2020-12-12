#include "percentpanel.h"


PercentPanel::PercentPanel()
{
    maxPercentLineWidth = 0;
}


void PercentPanel::show(QWidget *parent, int width)
{
    const int margin = 10;
    const int percentWidth = 43;

    QLabel *label = new QLabel(parent);
    label->setGeometry(margin, margin, width - margin * 2 - percentWidth, height() - margin * 2);
    label->setStyleSheet("QLabel {"
                         "background: #7b4791;"
                         "border-radius: 5px;"
                         "}");

    maxPercentLineWidth = label->width() - 4;

    percentLine->setParent(label);
    percentLine->move(2, 2);
    percentLine->setFixedWidth(0);
    percentLine->setFixedHeight(label->height() - 4);
    percentLine->setStyleSheet("QLabel {"
                               "background: #3e2448;"
                               "border-radius: 3px;"
                               "}");

    percent->setParent(parent);
    percent->setGeometry(width - percentWidth - margin, 0, percentWidth, height());
    percent->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    percent->setStyleSheet("QLabel {"
                           "color: #fff;"
                           "font-size: 15px;"
                           "}");
}


void PercentPanel::update(int p)
{
    percent->setText(QString("%1%").arg(p));
    percentLine->setFixedWidth(maxPercentLineWidth * p / 100);
}


int PercentPanel::height()
{
    return 30;
}
