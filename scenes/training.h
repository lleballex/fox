#ifndef Training_H
#define Training_H

#include <QLabel>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "general.h"
#include "database/verbmodel.h"
#include "database/usermodel.h"


class Training : public QWidget, private General, private VerbModel, private UserModel
{
    Q_OBJECT
public:
    explicit Training(QWidget *parent = nullptr);

private:
    int verbIndex;
    int verbsCount;
    int errorsCount;

    QWidget *testWidget = new QWidget;
    QWidget *resultWidget = new QWidget;
    QLabel *word = new QLabel;
    QLabel *hyphens = new QLabel[2];
    QLineEdit *inputs = new QLineEdit[2];
    QLabel *result = new QLabel;
    QPushButton *checkButton;
    QPushButton *nextButton;
    QPushButton *errorButtons = new QPushButton[2];

    VerbModel::Verb *verbs;

    void customizeTestWidget();
    void customizeResultWidget();
    void showEvent(QShowEvent *);

    QString getLabelStyle(bool success = false, bool wrong = false);
    QString getInputStyle(bool success = false, bool wrong = false);

private slots:
    void checkVerb();
    void changeVerb();
    void tryAgain();
    void showRightAnswer();
    void setMenuScene();

signals:
    void changeScene();
};


#endif // Training_H
