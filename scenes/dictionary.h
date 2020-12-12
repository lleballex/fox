#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QWidget>
#include <QLineEdit>
#include <QTableWidget>

#include "general.h"
#include "database/verbmodel.h"


class Dictionary : public QWidget, private General, private VerbModel
{
    Q_OBJECT
public:
    explicit Dictionary(QWidget *parent = nullptr);

private:
    QTableWidget *table = new QTableWidget;
    QLineEdit *input = new QLineEdit;
    QPushButton *closeSearchButton = new QPushButton;
    QPushButton *searchButton;

    void customizeTable();
    void customizeInput();
    void fillTable(VerbModel::Verb *verbs, int verbsCount);

private slots:
    void showSearchInput();
    void hideSearchInput();
    void search();
    void setMenuScene();

signals:
    void changeScene();
};


#endif // DICTIONARY_H
