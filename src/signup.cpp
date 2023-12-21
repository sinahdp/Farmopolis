#include "signup.h"
#include "ui_signup.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include <QRegExpValidator>
#include <QIntValidator>
#include "string"

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
int signupPageNumber ;

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

    // setting the initial condition for the fields

    QIntValidator* intValidator = new QIntValidator(this);
    ui->boxlineEdit->setValidator(intValidator);
    ui->bankassetlineEdit->setValidator(intValidator);

    QRegExp regex("\\d{10}");
    QRegExpValidator* phoneValidator = new QRegExpValidator(regex, this);
    ui->phonenumberlineEdit->setValidator(phoneValidator);

    //set enabel pushbutton

    ui->boxpushButton->setEnabled(true) ;

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
    ui->bankassetlineEdit->setText("") ;
    ui->capchalineEdit->setText("") ;
    ui->selectcountrycomboBox->setCurrentIndex(0);
}

void SignUp::settingFormNumber() {

    ui->titleFormlabel->setText("SignUp " + QString::number(currentIndexForm)) ;
}




void SignUp::on_nextpushButton_clicked()
{
    if(currentIndexForm < signupPageNumber) {
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

// check fields functions

//check len
bool SignUp::checlen(QString str)
{
    int flag = 0 ;
    if(str.length()<7){
        flag = 1 ;
        return flag ;
    }
    return flag ;
}
//check badstr
bool SignUp::checkbadstr(QString str)
{
    char badstr[11] = "*+-/$)(#^%" ;
    int flag = 0 ;
    for(int i=0 ; i<6 ; i++){
        if(str.contains(badstr[i])){
            flag = 1 ;
            return flag ;
        }
    }
    return flag;
}

bool SignUp::endcheck(QString str) {
    int flag = 0;
    if (str.length() >= 10 &&
       (str.right(10) == "@gmail.com" ||
        str.right(10) == "@email.com" ||
       (str.length() >= 11 && str.right(11) == "@mail.um.ac"))) {
        flag = 1;
    }
    return flag;
}

void SignUp::emptyFieldError(QLineEdit *lineEdit, QLabel *errorLabel)
{
    errorLabel->setText("This field cannot be empty");
    lineEdit->setStyleSheet("border: 2px solid #DC3545;");
    errorLabel->show();
}

void SignUp::on_darkmodepushButton_clicked()
{

}


void SignUp::on_passlineEdit_textChanged(const QString &arg1)
{
    QString pass = arg1 ;
    int flag1 = 1 ;
    int flag2 = 1 ;
    if(checlen(pass)==1){
        ui->userpassErrorlabel->setText("Password cannot be less than 7 letter") ;
        ui->passlineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->userpassErrorlabel->show() ;
        flag1 = 0 ;
        //signupCheck_fieldpass = 0 ;
    }
    if(checkbadstr(pass)==1){
        ui->userpassErrorlabel->setText("Password cannot contain [*+-/$)(#^%] characters") ;
        ui->passlineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->userpassErrorlabel->show() ;
        flag2 = 0 ;
        //signupCheck_fieldpass = 0 ;
    }
    if(flag1==1 && flag2==1){
        ui->passlineEdit->setStyleSheet("border : 2px solid #80B918;") ;
        ui->userpassErrorlabel->hide() ;
        //signupCheck_fieldpass = 1 ;
    }
}


void SignUp::on_emaillineEdit_textChanged(const QString &arg1)
{
    QString email = arg1 ;
    if(endcheck(email)==0) {
        ui->emailErrorlabel->setText("Your email must end with one of @gmail.com or @email.com or @mail.um.ac") ;
        ui->emaillineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->emailErrorlabel->show() ;
    }
    else if(checkbadstr(email)==1){
        ui->emailErrorlabel->setText("Email cannot contain [*+-/$)(#^%] characters") ;
        ui->emaillineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->emailErrorlabel->show() ;
        //flag2 = 0 ;
        //signupCheck_fieldpass = 0 ;
    }
    else {
        ui->emaillineEdit->setStyleSheet("border : 2px solid #80B918;") ;
        ui->emailErrorlabel->hide() ;
    }
}


void SignUp::on_bankassetlineEdit_textChanged(const QString &arg1)
{
    QString bankAsset = arg1 ;

    if (bankAsset == "0") {
        ui->bankassetErrorlabel->setText("This field cannot be zero");
        ui->bankassetlineEdit->setStyleSheet("border: 2px solid #DC3545;");
        ui->bankassetErrorlabel->show();
    }
    else {
        ui->bankassetlineEdit->setStyleSheet("border: 2px solid #80B918;");
        ui->bankassetErrorlabel->hide();
    }
}


void SignUp::on_boxlineEdit_textChanged(const QString &arg1)
{
    QString str = arg1 ;
    if(str.toInt() == 0) {
        ui->boxlineEdit->setStyleSheet("border: 2px solid #DC3545;");
        ui->boxpushButton->setEnabled(false) ;
    }
    else {
        ui->boxlineEdit->setStyleSheet("border: 2px solid #80B918;");
        ui->boxpushButton->setEnabled(true) ;
    }
}
void SignUp::on_boxpushButton_clicked()
{
    ui->boxwidget->setVisible(false);
    ui->formAndSettingwidget->setVisible(true);
}

void SignUp::on_phonenumberlineEdit_textChanged(const QString &arg1)
{
    QString str = arg1 ;
    if(str.length() != 10) {
        ui->phonenumberErrorlabel->setText("The phone number must be 10 digits (without zero)");
        ui->phonenumberlineEdit->setStyleSheet("border: 2px solid #DC3545;");
        ui->phonenumberErrorlabel->show();
    }
    else {
        ui->phonenumberlineEdit->setStyleSheet("border: 2px solid #80B918;");
        ui->phonenumberErrorlabel->hide() ;
    }
}


void SignUp::on_userlineEdit_textChanged(const QString &arg1)
{
    QString str = arg1 ;
    if(str.isEmpty()) {
        ui->userpassErrorlabel->setText("Username cannot be empty") ;
        ui->userlineEdit->setStyleSheet("border: 2px solid #DC3545;") ;
        ui->userpassErrorlabel->show();
    }
    else {
        ui->userlineEdit->setStyleSheet("border: 2px solid #80B918;") ;
        ui->userpassErrorlabel->hide();
    }
}

