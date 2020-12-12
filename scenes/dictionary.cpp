#include "dictionary.h"

#include <QHeaderView>

#include <QDebug>


Dictionary::Dictionary(QWidget *parent) : QWidget(parent)
{
    showFooter(this);
    addFooterObject(input);
    searchButton = addFooterButton("", ":/resources/icons/search.svg");

    VerbModel::Verb *verbs = getVerbs();
    int verbsCount = getVerbsCount();

    customizeTable();
    customizeInput();
    fillTable(verbs, verbsCount);

    connect(getMenuButton(), SIGNAL(clicked()), this, SLOT(setMenuScene()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(showSearchInput()));
    connect(closeSearchButton, SIGNAL(clicked()), this, SLOT(hideSearchInput()));
    connect(input, SIGNAL(returnPressed()), this, SLOT(search()));
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
    table->verticalHeader()->setDefaultSectionSize(70);
    table->setWordWrap(true);
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


void Dictionary::customizeInput()
{
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setAlignment(Qt::AlignRight);
    layout->addWidget(closeSearchButton);

    input->hide();
    input->setLayout(layout);
    input->setPlaceholderText("Поиск глагола");
    input->setStyleSheet("QLineEdit {"
                         "background: #fff;"
                         "border: none;"
                         "border-radius: 10px;"
                         "font-size: 18px;"
                         "font-weight: 500;"
                         "padding: 10px;"
                         "height: 100%;"
                         "width: 300px;"
                         "qproperty-alignment: AlignCenter;"
                         "}");

    closeSearchButton->setParent(input);
    closeSearchButton->setCursor(Qt::PointingHandCursor);
    closeSearchButton->setIcon(QIcon(QPixmap(":/resources/icons/times.svg")));
    closeSearchButton->setIconSize(QSize(20, 20));
    closeSearchButton->setStyleSheet("QPushButton {"
                                     "width: 30px;"
                                     "height: 30px;"
                                     "padding: 0;"
                                     "background: #bbb;"
                                     "border-radius: 15px;"
                                     "border: none;"
                                     "}"
                                     "QPushButton:hover {"
                                     "background: #aaa;"
                                     "}");
}


void Dictionary::fillTable(VerbModel::Verb *verbs, int verbsCount)
{
    QFont font = loadFonts();
    font.setItalic(true);
    font.setPixelSize(15);

    table->setRowCount(0);

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

    table->resizeRowsToContents();
}


void Dictionary::showSearchInput()
{
    searchButton->hide();
    input->show();
    input->setFocus();
}


void Dictionary::hideSearchInput()
{
    input->hide();
    input->setText("");
    searchButton->show();

    VerbModel::Verb *verbs = getVerbs();
    int verbsCount = getVerbsCount();

    fillTable(verbs, verbsCount);
}


void Dictionary::search()
{
    if(input->text().isEmpty()) return;

    VerbModel::Verb *verbs = searchVerbs(input->text());
    int verbsCount = getVerbsCount(0, input->text());

    fillTable(verbs, verbsCount);
}


void Dictionary::setMenuScene()
{
    emit changeScene();
}
