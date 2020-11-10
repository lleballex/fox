#ifndef GENERAL_H
#define GENERAL_H

#include <QWidget>
#include <QString>
#include <QPalette>
#include <QPushButton>
#include <QHBoxLayout>


class General
{
public:
    General();

private:
    QHBoxLayout *footerLayout;
    QPushButton *menuButton;;

protected:
    const int WINDOW_WIDTH = 650;
    const int WINDOW_HEIGHT = 550;
    const int FOOTER_HEIGHT = 100;
    const int FOOTER_MARGIN = 15;
    const QString WINDOW_TITLE = "Fox";
    const QString BACKGROUND_COLOR = "#9a59b5";
    const QString WIDGET_COLOR = "#823aa0";
    const QString LIGHT_WIDGET_COLOR = "#8b50a4";

    void showFooter(QWidget *parent);

    QFont loadFonts();
    QPushButton *addFooterButton(QString text);
    QPushButton *getMenuButton();
    QPalette getMainPalette();
    QString getMainStyle();
    QIcon getFavicon();
};


#endif // GENERAL_H
