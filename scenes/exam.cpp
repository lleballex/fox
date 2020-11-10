#include "exam.h"

#include <QVBoxLayout>

#include <QDebug>


Exam::Exam(QWidget *parent) : QWidget(parent)
{
    showFooter(this);
    nextButton = addFooterButton("Следующий");

    customizeTestWidget();
    customizeResultWidget();

    connect(nextButton, SIGNAL(clicked()), this, SLOT(changeVerb()));
    connect(getMenuButton(), SIGNAL(clicked()), this, SLOT(setMenuScene()));
}


void Exam::customizeTestWidget()
{
    word->setStyleSheet("QLabel {"
                         "color: #fff;"
                         "font-size: 25px;"
                         "text-transform: uppercase;"
                         "qproperty-alignment: AlignHCenter;"
                         "}");

    input->setPlaceholderText("V3");
    input->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    input->setStyleSheet("QLineEdit {"
                         "width: 300px;"
                         "background: #fff;"
                         "border: none;"
                         "font-size: 20px;"
                         "color: #000;"
                         "padding: 20px;"
                         "border-radius: 30px;"
                         "qproperty-alignment: AlignHCenter;"
                         "}");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(word);
    layout->addSpacing(20);
    layout->addWidget(input);

    testWidget->setParent(this);
    testWidget->setLayout(layout);
    testWidget->setGeometry(0, FOOTER_MARGIN, WINDOW_WIDTH, WINDOW_HEIGHT - FOOTER_HEIGHT - FOOTER_MARGIN);
    testWidget->show();
}


void Exam::customizeResultWidget()
{
    QLabel *label = new QLabel("Результат");
    label->setStyleSheet("QLabel {"
                         "color: #fff;"
                         "font-size: 50px;"
                         "qproperty-alignment: AlignHCenter;"
                         "text-transform: uppercase;"
                         "padding-bottom: 30px;"
                         "}");
    result->setStyleSheet("QLabel {"
                          "color: #fff;"
                          "font-size: 30px;"
                          "border-top: 2px solid #aaa;"
                          "padding-top: 30px;"
                          "}");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    layout->addWidget(result);

    resultWidget->setParent(this);
    resultWidget->setGeometry(0, FOOTER_MARGIN, WINDOW_WIDTH, WINDOW_HEIGHT - FOOTER_HEIGHT - FOOTER_MARGIN);
    resultWidget->setLayout(layout);
    resultWidget->hide();
}


void Exam::setVerb(int id)
{
    verb = getVerb(id);

    input->setText("");
    word->setText(verb.translate);
}


void Exam::showEvent(QShowEvent *)
{
    int level = getUser().level;
    verbsCount = getVerbsCount(level);
    rightCount = 0;
    startVerbId = getStartVerbId(level);
    setVerb(startVerbId);

    if(testWidget->isHidden()) {
        testWidget->show();
        nextButton->show();
        resultWidget->hide();
    }
    if(nextButton->text() != "Следующий") nextButton->setText("Следующий");
}


void Exam::changeVerb()
{
    if(input->text() == verb.v3) rightCount++;
    if(verb.id == verbsCount + startVerbId - 2) nextButton->setText("Завершить");

    if(verb.id < verbsCount + startVerbId - 1) setVerb(verb.id + 1);
    else {
        result->setText(QString("Правильных ответов: %1/%2").arg(rightCount).arg(verbsCount));
        testWidget->hide();
        nextButton->hide();
        resultWidget->show();
    }
}


void Exam::setMenuScene()
{
    emit changeScene();
}
