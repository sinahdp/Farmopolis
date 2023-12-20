#include "signup.h"
#include "ui_signup.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QFile>
#include <QTextStream>
#include "QString"

//capcha
#include <QRandomGenerator>
#include <QPainter>
#include <QFont>
#include <QTime>
#include <QImage>

#include <QStyle>
#include <QIcon>
#include <QPixmap>

//animation

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

//animation

int currentIndexForm = 1 ;
int sigupPageNumber ;

//check field
int checkFieldCapcha = 0 ;
SignUp::SignUp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);

    //set minmum size of page
    setMinimumSize(1200,1200);

    //add css file
    QFile styleFile(":/rec/Styles/Style.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&styleFile);
        QString style = stream.readAll();
        styleFile.close();
        this->setStyleSheet(style);
    }

    //hide lables
    ui->userpassErrorlabel->hide() ;
    ui->emailErrorlabel->hide() ;
    ui->phonenumberErrorlabel->hide() ;
    ui->bankassetErrorlabel->hide() ;
    ui->capchaErrorlabel->hide() ;

    //visiblity control
    ui->boxwidget->setVisible(true);
    ui->formAndSettingwidget->setVisible(false) ;

    //add combobox items
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/australia.png"), "Australia (+61)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/brazil.png"), "Brazil (+55)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/france.png"), "France (+33)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/germany.png"), "Germany (+49)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/india.png"), "India (+91)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/iran.png"), "Iran (+98)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/mexico.png"), "Mexico (+52)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/russia.png"), "Russia (+7)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/turkey.png"), "Turkey (+90)");
    ui->selectcountrycomboBox->addItem(QIcon(":/rec/Icons/flags/united-states.png"), "United States (+1)");

    // setting the initial condition for the number of managers
    ui->boxlineEdit->setInputMask("D00000");

    //genarate capcha first time
    generateCaptcha(ui->capchaimagelabel) ;
}

//change eyeimage and password mode
void SignUp::on_hidepasswordpushButton_clicked()
{
    static int check = 1 ;
    if(check){
        ui->hidepasswordpushButton->setStyleSheet("image: url(:/rec/Icons/view.png);") ;
        ui->passlineEdit->setEchoMode(QLineEdit::Normal) ;
        check = 0 ;
    }
    else{
        ui->hidepasswordpushButton->setStyleSheet("image: url(:/rec/Icons/hidden.png);") ;
        ui->passlineEdit->setEchoMode(QLineEdit::Password) ;
        check = 1 ;
    }
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::fadeAnimation()
{
    QGraphicsOpacityEffect *formOpacityEffect = new QGraphicsOpacityEffect(ui->formwidget);
    ui->formwidget->setGraphicsEffect(formOpacityEffect);

    QPropertyAnimation *formFadeOutAnimation = new QPropertyAnimation(formOpacityEffect, "opacity");
    formFadeOutAnimation->setDuration(3000);
    formFadeOutAnimation->setStartValue(1.0);
    formFadeOutAnimation->setEndValue(0.0);
    formFadeOutAnimation->start();

    ui->formwidget->setGraphicsEffect(formOpacityEffect);

    QPropertyAnimation *formFadeInAnimation = new QPropertyAnimation(formOpacityEffect, "opacity");
    formFadeInAnimation->setDuration(3000);
    formFadeInAnimation->setStartValue(0.0);
    formFadeInAnimation->setEndValue(1.0);
    formFadeInAnimation->start();
}

void SignUp::emptyTheForm()
{
    ui->userlineEdit->setText("") ;
    ui->passlineEdit->setText("") ;
    ui->emaillineEdit->setText("") ;
    ui->phonenumberlineEdit->setText("") ;
    ui->moneylineEdit->setText("") ;
    ui->capchalineEdit->setText("") ;
    ui->selectcountrycomboBox->setCurrentIndex(0);
}

void SignUp::settingFormNumber() {

    ui->titleFormlabel->setText("SignUp " + QString::number(currentIndexForm)) ;
}

//int sigupPageNumber = ui->boxlineEdit->text().toInt() ;
void SignUp::on_boxpushButton_clicked()
{
    sigupPageNumber = ui->boxlineEdit->text().toInt() ;
    ui->boxwidget->setVisible(false);
    ui->formAndSettingwidget->setVisible(true);
}

void SignUp::on_nextpushButton_clicked()
{
    if(currentIndexForm < sigupPageNumber) {
        currentIndexForm++ ;
        settingFormNumber() ;
        fadeAnimation() ;
        emptyTheForm() ;
    }
}
void SignUp::on_previouspushButton_clicked()
{
    if(1 < currentIndexForm) {
        currentIndexForm-- ;
        settingFormNumber() ;
        fadeAnimation() ;
        emptyTheForm() ;
    }
}


// genarate capcha
void SignUp::generateCaptcha(QLabel *captchaLabel)
{
    QString captchaText;
    const QString characters = "ABCDEFGHJKLMNPQRSTUVWXYZ0123456789";
    for (int i = 0; i < 6; ++i) {
        captchaText += characters.at(QRandomGenerator::global()->bounded(characters.length()));
    }

    QPixmap pixmap(100, 30);
    pixmap.fill(Qt::lightGray);
    captchaLabel->setPixmap(pixmap);
    captchaLabel->setText(captchaText);
}

void SignUp::checkCaptcha(QLineEdit *captchaEntry, QLabel *captchaLabel, QLabel *erorLable, int &check)
{
    QString userInput = captchaEntry->text();
    QString captchaText = captchaLabel->text();

    if (userInput != captchaText) {
        erorLable->setText("The securety field is note correct") ;
        erorLable->show() ;
        captchaEntry->setStyleSheet("border: 2px solid #DC3545;") ;
        check = 0 ;
    }
    else {
        captchaEntry->setStyleSheet("border: 2px solid #80B918;") ;
        erorLable->hide() ;
        check = 1 ;
    }
}
void SignUp::on_generatecapchapushButton_clicked() {
    generateCaptcha(ui->capchaimagelabel) ;
}

void SignUp::on_submitAndNextpushButton_clicked()
{
    checkCaptcha(ui->capchalineEdit ,ui->capchaimagelabel ,ui->capchaErrorlabel , checkFieldCapcha) ;
}


void SignUp::on_darkmodepushButton_clicked()
{

}

