#include "dictionary.h"

#include <QHeaderView>


Dictionary::Dictionary(QWidget *parent) : QWidget(parent)
{
    showFooter(this);

    customizeTable();
    fillTable();

    connect(getMenuButton(), SIGNAL(clicked()), this, SLOT(setMenuScene()));
}


void Dictionary::customizeTable()
{
    table->setParent(this);
    table->setGeometry(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT - FOOTER_HEIGHT);
    table->setColumnCount(3);
    for(int i = 0; i < 2; i++) table->setColumnWidth(i, WINDOW_WIDTH * 0.33);
    table->horizontalHeader()->setStretchLastSection(1);
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    table->setSelectionMode(QTableWidget::NoSelection);
    table->setFocusPolicy(Qt::NoFocus);
    table->setEditTriggers(0);
    table->setShowGrid(false);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->show();
    table->setStyleSheet(QString("QTableWidget {"
                                 "background: %1;"
                                 "font-size: 17px;"
                                 "font-weight: 500;"
                                 "color: #fff;"
                                 "border: none;"
                                 "}").arg(BACKGROUND_COLOR));
}


void Dictionary::fillTable()
{
    VerbModel::Verb *verbs = getVerbs();
    int verbsCount = getVerbsCount();

    QFont font = loadFonts();
    font.setItalic(true);
    font.setPixelSize(16);

    for(int i = 0; i < verbsCount * 2; i++) {
        table->insertRow(i);

        bool isTranslate = false;
        if((i + 1) % 2 == 0) isTranslate = true;

        for(int j = 0; j < 3; j++) {
            QTableWidgetItem *item = new QTableWidgetItem();

            if(isTranslate) {
                if(j == 0) {
                    item->setText(verbs[i / 2].translate);
                    item->setForeground(QColor("#000"));
                    item->setFont(font);
                }
            }
            else if(j == 0) item->setText(verbs[i / 2].v1);
            else if(j == 1) item->setText(verbs[i / 2].v2);
            else if(j == 2) item->setText(verbs[i / 2].v3);

            if(i % 4 == 0 || (i - 1) % 4 == 0)
                item->setBackground(QColor(LIGHT_WIDGET_COLOR));
            else item->setBackground(QColor(BACKGROUND_COLOR));

            table->setItem(i, j, item);
        }
    }
}


void Dictionary::setMenuScene()
{
    emit changeScene();
}
