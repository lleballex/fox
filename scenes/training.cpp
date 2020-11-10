#include "training.h"

#include <QHBoxLayout>
#include <QVBoxLayout>


Training::Training(QWidget *parent) : QWidget(parent)
{
    showFooter(this);
    checkButton = addFooterButton("Проверить");
    nextButton = addFooterButton("Дальше");

    nextButton->hide();
    customizeTestWidget();
    customizeResultWidget();

    connect(checkButton, SIGNAL(clicked()), this, SLOT(checkVerb()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(changeVerb()));
    connect(&errorButtons[0], SIGNAL(clicked()), this, SLOT(tryAgain()));
    connect(&errorButtons[1], SIGNAL(clicked()), this, SLOT(showRightAnswer()));
    connect(getMenuButton(), SIGNAL(clicked()), this, SLOT(setMenuScene()));
}


void Training::customizeTestWidget()
{
    errorButtons[0].setText("Попробовать еще");
    errorButtons[1].setText("Правильный ответ");
    for(int i = 0; i < 2; i++) {
        errorButtons[i].hide();
        errorButtons[i].setCursor(Qt::PointingHandCursor);
        errorButtons[i].setStyleSheet(QString("QPushButton {"
                                              "background: %1;"
                                              "color: #fff;"
                                              "border-radius: 10px;"
                                              "font-size: 20px;"
                                              "padding: 20px;"
                                              "}"
                                              "QPushButton:hover {"
                                              "background: %2;"
                                              "}").arg(WIDGET_COLOR).arg(LIGHT_WIDGET_COLOR));
    }

    for(int i = 0; i < 2; i++) {
        hyphens[i].setText("-");
        hyphens[i].setStyleSheet(getLabelStyle());
    }

    word->setStyleSheet(getLabelStyle());

    inputs[0].setPlaceholderText("V2");
    inputs[1].setPlaceholderText("V3");
    for(int i = 0; i < 2; i++) {
        inputs[i].setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        inputs[i].setStyleSheet(getInputStyle());
    }

    QHBoxLayout *layouts = new QHBoxLayout[2];

    layouts[0].setMargin(0);
    layouts[0].setSpacing(10);
    layouts[0].addWidget(word);
    layouts[0].addWidget(&hyphens[0]);
    layouts[0].addWidget(&inputs[0]);
    layouts[0].addWidget(&hyphens[1]);
    layouts[0].addWidget(&inputs[1]);

    layouts[1].setMargin(0);
    layouts[1].setSpacing(0);
    layouts[1].addSpacing(40);
    layouts[1].addWidget(&errorButtons[0]);
    layouts[1].addSpacing(20);
    layouts[1].addWidget(&errorButtons[1]);
    layouts[1].addSpacing(40);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(40);
    layout->setAlignment(Qt::AlignCenter);
    for(int i = 0; i < 2; i++) layout->addLayout(&layouts[i]);

    testWidget->setParent(this);
    testWidget->setLayout(layout);
    testWidget->setGeometry(0, FOOTER_MARGIN, WINDOW_WIDTH, WINDOW_HEIGHT - FOOTER_HEIGHT - FOOTER_MARGIN);
    testWidget->show();
}


void Training::customizeResultWidget()
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


void Training::setVerb(int id)
{
    verb = getVerb(id);

    word->setText(verb.v1);
    for(int i = 0; i < 2; i++) inputs[i].setText("");
}


void Training::showEvent(QShowEvent *)
{
    int level = getUser().level;
    verbsCount = getVerbsCount(level);
    errorsCount = 0;
    startVerbId = getStartVerbId(level);
    setVerb(startVerbId);

    if(!nextButton->isHidden()) nextButton->hide();

    if(testWidget->isHidden()) {
        testWidget->show();
        resultWidget->hide();
    } else if(!errorButtons[0].isHidden())
        for(int i = 0; i < 2; i++) errorButtons[i].hide();

    if(testWidget->isHidden() || !errorButtons[0].isHidden() || checkButton->isHidden()) {
        checkButton->show();
        word->setStyleSheet(getLabelStyle());
        for(int i = 0; i < 2; i++) {
            hyphens[i].setStyleSheet(getLabelStyle());
            inputs[i].setStyleSheet(getInputStyle());
            inputs[i].setReadOnly(false);
        }
    }
}


QString Training::getLabelStyle(bool success, bool wrong)
{
    QString color = "#fff";
    if(success) color = "#26de81";
    else if(wrong) color = "#fc5c65";

    return QString("QLabel {"
                   "color: %1;"
                   "font-size: 27px;"
                   "font-weight: 500;"
                   "}").arg(color);
}


QString Training::getInputStyle(bool success, bool wrong)
{
    QString color = "#fff";
    if(success) color = "#26de81";
    else if(wrong) color = "#fc5c65";

    return QString("QLineEdit {"
                   "color: %1;"
                   "font-size: 27px;"
                   "background: %2;"
                   "width: 180px;"
                   "border: none;"
                   "border-bottom: 2px solid #333;"
                   "qproperty-alignment: AlignHCenter;"
                   "font-weight: 500;"
                   "}").arg(color).arg(BACKGROUND_COLOR);
}


void Training::checkVerb()
{
    checkButton->hide();

    for(int i = 0; i < 2; i++) {
        inputs[i].clearFocus();
        inputs[i].setReadOnly(true);
    }

    if(inputs[0].text() == verb.v2 && inputs[1].text() == verb.v3) {
        nextButton->show();
        word->setStyleSheet(getLabelStyle(true));
        for(int i = 0; i < 2; i++) {
            hyphens[i].setStyleSheet(getLabelStyle(true));
            inputs[i].setStyleSheet(getInputStyle(true));
        }
    } else {
        errorsCount++;
        word->setStyleSheet(getLabelStyle(false, true));
        for(int i = 0; i < 2; i++) {
            hyphens[i].setStyleSheet(getLabelStyle(false, true));
            inputs[i].setStyleSheet(getInputStyle(false, true));
            errorButtons[i].show();
        }
    }
}


void Training::changeVerb()
{
    nextButton->hide();

    if(verb.id < verbsCount + startVerbId - 1) {
        setVerb(verb.id + 1);
        checkButton->show();
        word->setStyleSheet(getLabelStyle());
        for(int i = 0; i < 2; i++) {
            hyphens[i].setStyleSheet(getLabelStyle());
            inputs[i].setStyleSheet(getInputStyle());
            inputs[i].setReadOnly(false);
            inputs[i].clearFocus();
        }
    } else {
        result->setText(QString("Количество ошибок: %1").arg(errorsCount));
        testWidget->hide();
        resultWidget->show();
    }
}


void Training::tryAgain()
{
    verb.id--;
    for(int i = 0; i < 2; i++) errorButtons[i].hide();
    changeVerb();
}


void Training::showRightAnswer()
{
    for(int i = 0; i < 2; i++) errorButtons[i].hide();
    inputs[0].setText(verb.v2);
    inputs[1].setText(verb.v3);
    checkVerb();
}


void Training::setMenuScene()
{
    emit changeScene();
}
