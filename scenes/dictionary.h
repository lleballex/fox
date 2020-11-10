#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QWidget>
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

    void customizeTable();
    void fillTable();

private slots:
    void setMenuScene();

signals:
    void changeScene();
};


#endif // DICTIONARY_H
