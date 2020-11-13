#include "exam.h"

#include <QVBoxLayout>

#include <QDebug>


Exam::Exam(QWidget *parent) : QWidget(parent)
{
    srand(time(0));

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


void Exam::showEvent(QShowEvent *)
{
    int level = getUser().level;
    verbIndex = -1;
    verbsCount = getVerbsCount(level);
    rightAnswersCount = 0;
    verbs = getVerbs(level);

    changeVerb();

    if(testWidget->isHidden()) {
        testWidget->show();
        nextButton->show();
        resultWidget->hide();
    }
    if(nextButton->text() != "Дальше") nextButton->setText("Дальше");
}


void Exam::changeVerb()
{  
    if(verbIndex >= 0 && input->text() == rightAnswer) rightAnswersCount++;
    if(verbIndex + 2 >= verbsCount) nextButton->setText("Завершить");

    verbIndex++;

    if(verbIndex >= verbsCount) {
        result->setText(QString("Правильных ответов: %1/%2").arg(rightAnswersCount).arg(verbsCount));
        testWidget->hide();
        nextButton->hide();
        resultWidget->show();
    } else {
        input->setText("");
        word->setText(verbs[verbIndex].translate);

        switch(rand() % 3) {
        case 0:
            rightAnswer = verbs[verbIndex].v1;
            input->setPlaceholderText("V1");
            break;
        case 1:
            rightAnswer = verbs[verbIndex].v2;
            input->setPlaceholderText("V2");
            break;
        case 2:
            rightAnswer = verbs[verbIndex].v3;
            input->setPlaceholderText("V3");
            break;
        }
    }
}


void Exam::setMenuScene()
{
    emit changeScene();
}
