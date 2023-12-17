#include "signup.h"
#include "ui_signup.h"

#include <QFile>
#include <QTextStream>
#include "QString"

#include <QStyle>
#include <QIcon>
#include <QPixmap>

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
}

SignUp::~SignUp()
{
    delete ui;
}

