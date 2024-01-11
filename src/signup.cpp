#include "signup.h"
#include "ui_signup.h"
#include "farmopolis.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <QRegExpValidator>
#include <QIntValidator>
#include "string"

//file
#include <QFile>
#include <QTextStream>
#include "QString"

//database
#include <QSqlDatabase>
#include "QSqlDriver"
#include "QSqlQuery"
#include "QSqlQueryModel"

//capcha
#include <QRandomGenerator>
#include <QPixmap>

//animation
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

int signupPageNumber = 1 ;
int lastCompletedForm = 1 ;

//check field variables
bool checkFielduser = 1 ;
bool checkFieldpass = 1 ;
bool checkFieldemail = 1 ;
bool checkFieldphonenumber = 1 ;
bool checkFieldbankasset = 1 ;
bool checkFieldcapcha = 1 ;

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

    //database
    QSqlDatabase database ;
    database = QSqlDatabase::addDatabase("QSQLITE") ;
    database.setDatabaseName("E:/My Folders/Programming/Programming Exercises/Quera Exercises/QT/Farmopolis/rec/Database/farmdata.db");
    database.open() ;

    //hide lables
    hidelabels() ;

    //visiblity control
    ui->boxwidget->setVisible(true);
    ui->formAndSettingwidget->setVisible(false) ;

    QSqlQuery q;
    QString check = "true" ;
    q.exec("SELECT firstrun FROM managers WHERE firstrun = '"+check+"' ");
    if(q.first()) {
        ui->boxwidget->setVisible(false);
        ui->formAndSettingwidget->setVisible(false) ;
        Farmopolis *farmopolispage = new Farmopolis ;
        farmopolispage->show() ;
        deleteLater();
    }

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
    ui->boxpushButton->setEnabled(false) ;

    //genarate capcha first time
    generateCaptcha(ui->capchaimagelabel) ;
}

//change eyeimage and password mode
void SignUp::on_hidepasswordpushButton_clicked()
{
    static int check = 1 ;
    if(check) {
        ui->hidepasswordpushButton->setStyleSheet("image: url(:/rec/Icons/view.png);") ;
        ui->passlineEdit->setEchoMode(QLineEdit::Normal) ;
        check = 0 ;
    }
    else {
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
    ui->userlineEdit->clear() ;
    ui->passlineEdit->clear() ;
    ui->emaillineEdit->clear() ;
    ui->phonenumberlineEdit->clear() ;
    ui->bankassetlineEdit->clear() ;
    ui->capchalineEdit->clear() ;
    ui->selectcountrycomboBox->setCurrentIndex(0);
}

void SignUp::setFormNumber() {
    ui->titleFormlabel->setText("Manager " + QString::number(lastCompletedForm)) ;
}

void SignUp::hidelabels()
{
    ui->userpassErrorlabel->hide() ;
    ui->emailErrorlabel->hide() ;
    ui->phonenumberErrorlabel->hide() ;
    ui->bankassetErrorlabel->hide() ;
    ui->capchaErrorlabel->hide() ;
    ui->dataAndFinalchecklabel->hide() ;
}

void SignUp::hideBorderlineEdits()
{
    ui->userlineEdit->setStyleSheet("border: 2px solid #2B3034;");
    ui->passlineEdit->setStyleSheet("border: 2px solid #2B3034;");
    ui->emaillineEdit->setStyleSheet("border: 2px solid #2B3034;");
    ui->phonenumberlineEdit->setStyleSheet("border: 2px solid #2B3034;");
    ui->bankassetlineEdit->setStyleSheet("border: 2px solid #2B3034;");
    ui->capchalineEdit->setStyleSheet("border: 2px solid #2B3034;");
}

//capcha functions
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

void SignUp::checkCaptcha(QLineEdit *captchaEntry, QLabel *captchaLabel, QLabel *erorLable)
{
    QString userInput = captchaEntry->text();
    QString captchaText = captchaLabel->text();

    if (userInput != captchaText) {
        erorLable->setText("The securety field is note correct") ;
        erorLable->show() ;
        captchaEntry->setStyleSheet("border: 2px solid #DC3545;") ;
        checkFieldcapcha = 1 ;
    }
    else {
        captchaEntry->setStyleSheet("border: 2px solid #80B918;") ;
        erorLable->hide() ;
        checkFieldcapcha = 0 ;
    }
}

void SignUp::on_generatecapchapushButton_clicked() {
    generateCaptcha(ui->capchaimagelabel) ;
}

// check fields functions
bool SignUp::checlen(QString str)
{
    int flag = 0 ;
    if(str.length()<7){
        flag = 1 ;
        return flag ;
    }
    return flag ;
}

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

void SignUp::on_userlineEdit_textChanged(const QString &arg1)
{
    QString str = arg1 ;
    if(str.isEmpty()) {
        ui->userlineEdit->setStyleSheet("border: 2px solid #DC3545;") ;
        ui->userpassErrorlabel->setText("Username cannot be empty") ;
        ui->userpassErrorlabel->show();
        checkFielduser = 1 ;
    }
    else {
        checkFielduser = 0 ;
        ui->userlineEdit->setStyleSheet("border: 2px solid #80B918;") ;
        if(checkFieldpass == 0) {
            ui->userpassErrorlabel->hide();
        }
    }
}

void SignUp::on_passlineEdit_textChanged(const QString &arg1)
{
    QString pass = arg1 ;
    if(checlen(pass) == 1){
        ui->passlineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->userpassErrorlabel->setText("Password cannot be less than 7 letter") ;
        ui->userpassErrorlabel->show() ;
        checkFieldpass = 1 ;
    }
    else if(checkbadstr(pass) == 1){
        ui->passlineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->userpassErrorlabel->setText("Password cannot contain [*+-/$)(#^%] characters") ;
        ui->userpassErrorlabel->show() ;
        checkFieldpass = 1 ;
    }
    else {
        checkFieldpass = 0 ;
        ui->passlineEdit->setStyleSheet("border : 2px solid #80B918;") ;
        if(checkFielduser == 0){
            ui->userpassErrorlabel->hide() ;
        }
        else {
            ui->userlineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
            ui->userpassErrorlabel->setText("Username cannot be empty") ;
        }
    }
}

void SignUp::on_emaillineEdit_textChanged(const QString &arg1)
{
    QString email = arg1 ;
    if(endcheck(email)==0) {
        ui->emaillineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->emailErrorlabel->setText("Your email must end with one of @gmail.com or @email.com or @mail.um.ac") ;
        ui->emailErrorlabel->show() ;
        checkFieldemail = 1 ;
    }
    else if(checkbadstr(email)==1){
        ui->emaillineEdit->setStyleSheet("border : 2px solid #DC3545;") ;
        ui->emailErrorlabel->setText("Email cannot contain [*+-/$)(#^%] characters") ;
        ui->emailErrorlabel->show() ;
        checkFieldemail = 1 ;
    }
    else {
        ui->emaillineEdit->setStyleSheet("border : 2px solid #80B918;") ;
        ui->emailErrorlabel->hide() ;
        checkFieldemail = 0 ;
    }
}

void SignUp::on_phonenumberlineEdit_textChanged(const QString &arg1)
{
    QString str = arg1 ;
    if(str.length() != 10) {
        ui->phonenumberlineEdit->setStyleSheet("border: 2px solid #DC3545;");
        ui->phonenumberErrorlabel->setText("The phone number must be 10 digits (without zero)");
        ui->phonenumberErrorlabel->show();
        checkFieldphonenumber = 1 ;
    }
    else {
        ui->phonenumberlineEdit->setStyleSheet("border: 2px solid #80B918;");
        ui->phonenumberErrorlabel->hide() ;
        checkFieldphonenumber = 0 ;
    }
}

void SignUp::on_bankassetlineEdit_textChanged(const QString &arg1)
{
    QString bankAsset = arg1 ;
    if(bankAsset.isEmpty()) {
        ui->bankassetlineEdit->setStyleSheet("border: 2px solid #DC3545;");
        ui->bankassetErrorlabel->setText("Bank assets cannot be empty");
        ui->bankassetErrorlabel->show();
        checkFieldbankasset = 1 ;
    }
    else if(bankAsset.toDouble() == 0) {
        ui->bankassetlineEdit->setStyleSheet("border: 2px solid #DC3545;");
        ui->bankassetErrorlabel->setText("Bank assets cannot be zero");
        ui->bankassetErrorlabel->show();
        checkFieldbankasset = 1 ;
    }
    else {
        ui->bankassetlineEdit->setStyleSheet("border: 2px solid #80B918;");
        ui->bankassetErrorlabel->hide();
        checkFieldbankasset = 0 ;
    }
}

//box functions
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
    signupPageNumber = ui->boxlineEdit->text().toInt() ;
    NumberOfUsers = signupPageNumber ;
    ui->boxwidget->setVisible(false);
    ui->formAndSettingwidget->setVisible(true);
}

void SignUp::on_darkmodepushButton_clicked()
{
    static int check = 1 ;
    if(check){
        check = 0 ;
        ui->darkmodepushButton->setStyleSheet("image: url(:/rec/Icons/light-mode.png);") ;
        ui->fatherwidget->setStyleSheet("#fatherwidget { background-color: #F8f9fa; }");
        ui->formwidget->setStyleSheet("#formwidget { background-color: #ADB5BD; }");
        ui->formAndSettingwidget->setStyleSheet("#formAndSettingwidget QLineEdit { background-color: #F8f9fa ; color: black ; border: 2px solid #ADB5BD}");
    }
    else {
        check = 1 ;
        ui->darkmodepushButton->setStyleSheet("image: url(:/rec/Icons/night-mode.png);") ;
        ui->fatherwidget->setStyleSheet("#fatherwidget { background-color: #2B3034; }");
        ui->formwidget->setStyleSheet("#formwidget { background-color: #212529; }");
        ui->formAndSettingwidget->setStyleSheet("#formAndSettingwidget QLineEdit { background-color: #2B3034 ; color: white ; border: 2px solid #2B3034}");
    }
}

//submit and database
void SignUp::on_submitAndNextpushButton_clicked() {

    checkCaptcha(ui->capchalineEdit ,ui->capchaimagelabel ,ui->capchaErrorlabel) ;

    int finalCheck = checkFielduser + checkFieldpass + checkFieldemail + checkFieldphonenumber + checkFieldbankasset + checkFieldcapcha ;
    if (finalCheck == 0) {
        QSqlQuery q;
        QString username = ui->userlineEdit->text();
        QString password = ui->passlineEdit->text();
        QString email = ui->emaillineEdit->text();
        QString country = ui->selectcountrycomboBox->currentText();
        QString phonenumber = ui->phonenumberlineEdit->text();
        double bankassets = ui->bankassetlineEdit->text().toDouble();
        q.exec("SELECT username FROM managers WHERE username = '"+username+"' ");
        if (q.first()) {
            ui->dataAndFinalchecklabel->show();
            ui->dataAndFinalchecklabel->setStyleSheet("background-color:#DC3545 ; color: white ;");
            ui->dataAndFinalchecklabel->setText("This username exists in the game");
        }
        else {
            int id = lastCompletedForm ;
            q.prepare("INSERT INTO managers (id, username, password, email, country, phonenumber, bankassets) VALUES (:id, :username, :password, :email, :country, :phonenumber, :bankassets)");
            q.bindValue(":id", id);
            q.bindValue(":username", username);
            q.bindValue(":password", password);
            q.bindValue(":email", email);
            q.bindValue(":country", country);
            q.bindValue(":phonenumber", phonenumber);
            q.bindValue(":bankassets", bankassets);
            q.exec();

            ui->dataAndFinalchecklabel->show();
            ui->dataAndFinalchecklabel->setText("Your information has been successfuly registered");
            ui->dataAndFinalchecklabel->setStyleSheet("background-color:#80B918; color: white;");
            if(lastCompletedForm < signupPageNumber){
                lastCompletedForm++ ;
                setFormNumber() ;
                fadeAnimation() ;
                emptyTheForm() ;
                hidelabels() ;
                hideBorderlineEdits() ;
                generateCaptcha(ui->capchaimagelabel) ;
            }
            else {
                QSqlQuery q;
                QString check = "true";
                q.prepare("INSERT INTO managers (firstrun) VALUES (:firstrun)");
                q.bindValue(":firstrun", check);
                q.exec();
                Farmopolis *farmopolispage = new Farmopolis ;
                farmopolispage->show() ;
                deleteLater();
            }
        }
    }
    else {
        ui->dataAndFinalchecklabel->show();
        ui->dataAndFinalchecklabel->setText("Please complete the fields correctly");
        ui->dataAndFinalchecklabel->setStyleSheet("background-color:#DC3545 ; color: white ;");
    }
}
