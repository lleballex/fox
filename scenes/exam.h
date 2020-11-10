#ifndef EXAM_H
#define EXAM_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "general.h"
#include "database/verbmodel.h"
#include "database/usermodel.h"


class Exam : public QWidget, private General, private VerbModel, private UserModel
{
    Q_OBJECT
public:
    explicit Exam(QWidget *parent = nullptr);

private:
    int verbsCount;
    int rightCount;
    int startVerbId;

    VerbModel::Verb verb;

    QWidget *testWidget = new QWidget;
    QWidget *resultWidget = new QWidget;
    QLabel *word = new QLabel;
    QLineEdit *input = new QLineEdit;
    QLabel *result = new QLabel;
    QPushButton *nextButton;

    void customizeTestWidget();
    void customizeResultWidget();
    void setVerb(int id);
    void showEvent(QShowEvent *);

private slots:
    void changeVerb();
    void setMenuScene();

signals:
    void changeScene();
};


#endif // EXAM_H
