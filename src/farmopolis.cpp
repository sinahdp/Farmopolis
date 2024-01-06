#include "farmopolis.h"
#include "ui_farmopolis.h"

//file
#include <QFile>
#include <QTextStream>
#include "QString"

#include <QMouseEvent>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

Farmopolis::Farmopolis(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Farmopolis)
{
    ui->setupUi(this);

    //set minmum size of page
    setMinimumSize(2000,1200);
    setMaximumSize(2000,1200);

    //add css file
    QFile styleFile(":/rec/Styles/FarmStyle.css");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&styleFile);
        QString style = stream.readAll();
        styleFile.close();
        this->setStyleSheet(style);
    }

    //Create a new QGridLayout and add it to the graphics view
    QGridLayout *gridLayout = new QGridLayout(ui->groundwidget);
    const int numRows = 4;
    const int numCols = 5;

    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            // ایجاد یک Ground جدید
            Ground *ground = new Ground("",ui->groundwidget);

            // اضافه کردن رویداد کلیک به Ground
            ground->installEventFilter(this);

            // اضافه کردن Ground به QGridLayout
            gridLayout->addWidget(ground, i, j);


        }
    }
    Ground *firstground = qobject_cast<Ground*>(gridLayout->itemAtPosition(0, 4)->widget());
    firstground->setStyleSheet("background-color: #55A630 ;border:3px solid #212529;");
    firstground->isgreen = 1 ;
    currentground = firstground ;

    setCoinsLabe(coins) ;
    setWorkersLabel(numberFreeWorkers , numberWorkers) ;
}

Farmopolis::~Farmopolis() {
    delete ui;
}

bool Farmopolis::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        // تبدیل obj به Ground*
        Ground* clickedground = qobject_cast<Ground*>(obj);
        if (clickedground) {
            selectGround(clickedground);
        }
    }
    return QObject::eventFilter(obj, event);
}

void Farmopolis::setCoinsLabe(int coins) {
    ui->coinInventorylabel->setText(" " + QString::number(coins)) ;
}

void Farmopolis::setWorkersLabel(int free, int all) {
    ui->numberOfWorkerslabel->setText(" " + QString::number(free) + " / " + QString::number(all)) ;
}

void Farmopolis::selectGround(Ground *clickedground) {
    if(currentground) {
        QString stylesCurrentground = currentground->styleSheet();
        currentground->setStyleSheet(stylesCurrentground + "border: 3px solid #FFB703;") ;
    }
    QString stylesClickedground = clickedground->styleSheet();
    clickedground->setStyleSheet(stylesClickedground + "border: 3px solid #212529;") ;
    currentground = clickedground ;
}

void Farmopolis::on_buygroundpushButton_clicked() {
    if (currentground && currentground->isgreen == 0 && coins >= groundPrice) {
        currentground->isgreen = 1 ;
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet(originalStyles + "background-color: #55A630;");
        coins = coins - groundPrice ;
        setCoinsLabe(coins) ;
    }
}

void Farmopolis::on_buyWorkerpushButton_clicked() {
    if(coins >= workerPrice) {
        numberWorkers += 1 ;
        numberFreeWorkers += 1 ;
        coins = coins - workerPrice ;
        setCoinsLabe(coins) ;
        setWorkersLabel(numberFreeWorkers , numberWorkers) ;
    }
}

void Farmopolis::on_buyhenpushButton_clicked() {
    if (currentground && currentground->isgreen == 1 && currentground->isfull == 0 && coins >= henPrice) {
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/hen.png) no-repeat;");
        currentground->isfull = 1 ;
        coins = coins - henPrice ;
        setCoinsLabe(coins) ;
        numberFreeWorkers -= 1 ;
        setWorkersLabel(numberFreeWorkers , numberWorkers) ;
    }
}

void Farmopolis::on_buysheeppushButton_clicked() {
    if (currentground && currentground->isgreen == 1 && currentground->isfull == 0 && coins >= sheepPrice) {
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/sheep.png) no-repeat;");
        currentground->isfull = 1 ;
        coins = coins - sheepPrice ;
        setCoinsLabe(coins) ;
        numberFreeWorkers -= 1;
        setWorkersLabel(numberFreeWorkers , numberWorkers) ;
    }
}

void Farmopolis::on_buycowpushButton_clicked() {
    if (currentground && currentground->isgreen == 1 && currentground->isfull == 0 && coins >= cowPrice) {
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/cow.png) no-repeat;");
        currentground->isfull = 1 ;
        coins = coins - cowPrice ;
        setCoinsLabe(coins) ;
        numberFreeWorkers -= 1;
        setWorkersLabel(numberFreeWorkers , numberWorkers) ;
    }
}



