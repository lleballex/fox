#ifndef PERCENTPANEL_H
#define PERCENTPANEL_H

#include <QLabel>


class PercentPanel
{
public:
    PercentPanel();

    void show(QWidget *parent, int width);
    void update(int p);
    int height();

private:
    int maxPercentLineWidth;

    QLabel *percent = new QLabel;
    QLabel *percentLine = new QLabel;
};


#endif // PERCENTPANEL_H
