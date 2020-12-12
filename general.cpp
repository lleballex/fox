#include "general.h"

#include <QColor>
#include <QFontDatabase>


General::General() {}


void General::showFooter(QWidget *parent)
{
    int size = FOOTER_HEIGHT - FOOTER_MARGIN * 2;

    QWidget *footer = new QWidget(parent);
    footer->setGeometry(0, WINDOW_HEIGHT - FOOTER_HEIGHT, WINDOW_WIDTH, FOOTER_HEIGHT);

    QPixmap pixmap(":/resources/icons/home.svg");
    QIcon icon(pixmap);

    menuButton = new QPushButton;
    menuButton->setCursor(Qt::PointingHandCursor);
    menuButton->setMinimumSize(size, size);
    menuButton->setMaximumSize(size, size);
    menuButton->setIcon(icon);
    menuButton->setIconSize(QSize(size - 10, size - 10));
    menuButton->setStyleSheet(QString("QPushButton {"
                                      "background: %1;"
                                      "border-radius: 5px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background: %2"
                                      "}").arg(WIDGET_COLOR).arg(LIGHT_WIDGET_COLOR));

    footerLayout = new QHBoxLayout;
    footerLayout->setAlignment(Qt::AlignLeft);
    footerLayout->setMargin(FOOTER_MARGIN);
    footerLayout->addWidget(menuButton);
    footerLayout->addStretch(1);

    footer->setLayout(footerLayout);
    footer->show();
}


void General::addFooterObject(QWidget *object)
{
    footerLayout->addWidget(object);
}


QFont General::loadFonts()
{  
    int regularId = QFontDatabase::addApplicationFont(":/resources/fonts/Roboto-Regular.ttf");
    int mediumId = QFontDatabase::addApplicationFont(":/resources/fonts/Roboto-Medium.ttf");
    int mediumItalicId = QFontDatabase::addApplicationFont(":/resources/fonts/Roboto-MediumItalic.ttf");


    QString regularFamily = QFontDatabase::applicationFontFamilies(regularId).at(0);
    QString mediumFamily = QFontDatabase::applicationFontFamilies(mediumId).at(0);
    QString mediumItalicFamily = QFontDatabase::applicationFontFamilies(mediumItalicId).at(0);

    QFont font;
    font.setFamilies(QStringList() << regularFamily << mediumFamily << mediumItalicFamily);

    return font;
}


QPushButton *General::addFooterButton(QString text, QString icon)
{
    QPushButton *button = new QPushButton();

    if(!text.isEmpty()) button->setText(text);
    if(!icon.isEmpty()) {
        int size = FOOTER_HEIGHT - FOOTER_MARGIN * 2;
        button->setIcon(QIcon(QPixmap(icon)));
        button->setFixedSize(size, size);
        button->setIconSize(QSize(size - 10, size - 10));
    }

    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    button->setCursor(Qt::PointingHandCursor);
    button->setStyleSheet(QString("QPushButton {"
                                  "background: %1;"
                                  "border-radius: 5px;"
                                  "color: #fff;"
                                  "font-size: 18px;"
                                  "padding: 0 30px;"
                                  "text-transform: uppercase;"
                                  "}"
                                  "QPushButton:hover {"
                                  "background: %2"
                                  "}").arg(WIDGET_COLOR).arg(LIGHT_WIDGET_COLOR));

    footerLayout->addWidget(button);
    return button;
}


QPushButton *General::getMenuButton()
{
    return menuButton;
}


QPalette General::getMainPalette()
{
    QPalette *palette = new QPalette;
    palette->setColor(QPalette::Background, QColor(BACKGROUND_COLOR));
    return *palette;
}


QString General::getMainStyle()
{
    return "font-family: \"Roboto\"";
}


QIcon General::getFavicon()
{
    return QIcon(":/resources/icons/favicon.svg");
}
