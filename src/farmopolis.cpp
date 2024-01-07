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
    ui->operatorwidget->hide() ;
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
            setOperatorLabels() ;
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

void Farmopolis::setOperatorLabels()
{
    ui->operatorwidget->setVisible(true) ;
    int productNumber = currentground->isfull ;
    ui->workerErrorlabel->setVisible(false) ;
    switch (productNumber) {
        case 0 :
            ui->operatorwidget->hide() ;
        case 1 :
            ui->animalkilllabel->setStyleSheet("image: url(:/rec/Icons/farm/hen.png);") ;
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/eggs.png);") ;
            ui->profitkilllabel->setText("   " + QString::number(henPrice - 1)) ;
            break ;
        case 2 :
            ui->animalkilllabel->setStyleSheet("image: url(:/rec/Icons/farm/sheep.png);") ;
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/milk.png);") ;
            ui->profitkilllabel->setText("   " + QString::number(sheepPrice - 1)) ;
            break ;
        case 3 :
            ui->animalkilllabel->setStyleSheet("image: url(:/rec/Icons/farm/cow.png);") ;
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/milk.png);") ;
            ui->profitkilllabel->setText("   " + QString::number(cowPrice - 1)) ;
            break ;
    }
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
    if (currentground && currentground->isgreen == 1 && currentground->isfull == 0 && coins >= henPrice && numberFreeWorkers >= 1) {
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/hen.png) center center no-repeat;");
        currentground->isfull = 1 ;
        coins = coins - henPrice ;
        setCoinsLabe(coins) ;
        numberFreeWorkers-- ;
        setWorkersLabel(numberFreeWorkers , numberWorkers) ;
        setOperatorLabels() ;

    }
}

void Farmopolis::on_buysheeppushButton_clicked() {
    if (currentground && currentground->isgreen == 1 && currentground->isfull == 0 && coins >= sheepPrice && numberFreeWorkers >= 1) {
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/sheep.png) center center no-repeat;");
        currentground->isfull = 2 ;
        coins = coins - sheepPrice ;
        setCoinsLabe(coins) ;
        numberFreeWorkers-- ;
        setWorkersLabel(numberFreeWorkers , numberWorkers) ;
        setOperatorLabels() ;
    }
}

void Farmopolis::on_buycowpushButton_clicked() {
    if (currentground && currentground->isgreen == 1 && currentground->isfull == 0 && coins >= cowPrice && numberFreeWorkers >= 1) {
        QString originalStyles = currentground->styleSheet();
        currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/cow.png) center center no-repeat;");
        currentground->isfull = 3 ;
        coins = coins - cowPrice ;
        setCoinsLabe(coins) ;
        numberFreeWorkers-- ;
        setWorkersLabel(numberFreeWorkers , numberWorkers) ;
        setOperatorLabels() ;
    }
}

void Farmopolis::on_roundStartpushButton_clicked() {
    timer.start(1000);
    connect(&timer, &QTimer::timeout, [&]() {
        remainingTime--;
        if (remainingTime >= 0) {
            ui->roundStartpushButton->setText(QString::number(remainingTime) + " s");
        }
        else {
            timer.stop();
            ui->roundStartpushButton->setText("Start");
        }
    });

}


void Farmopolis::on_killpushButton_clicked()
{
    int productNumber = currentground->isfull;
    switch (productNumber) {
        case 1 :
            currentground->setStyleSheet("border:3px solid #212529 ; background-color: #55A630 ;");
            coins = coins + henPrice - 1 ;
            setCoinsLabe(coins) ;
            break ;
        case 2 :
            currentground->setStyleSheet("border:3px solid #212529 ; background-color: #55A630 ;");
            coins = coins + sheepPrice - 1 ;
            setCoinsLabe(coins) ;
            break ;
        case 3 :
            currentground->setStyleSheet("border:3px solid #212529 ; background-color: #55A630 ;");
            coins = coins + cowPrice - 1 ;
            setCoinsLabe(coins) ;
            break ;
    }
    currentground->isfull = 0 ;
    numberFreeWorkers++ ;
    setWorkersLabel(numberFreeWorkers , numberWorkers) ;
    setOperatorLabels() ;
}


void Farmopolis::on_collectpushButton_clicked() {
    int productNumber = currentground->isfull ;
    if(numberFreeWorkers >= 1) {
        switch (productNumber) {
            case 1 :
                coins = coins + eggprice ;
                setCoinsLabe(coins) ;
                break ;
            case 2 :
                coins = coins + milksheep ;
                setCoinsLabe(coins) ;
                break ;
            case 3 :
                coins = coins + milkcow ;
                setCoinsLabe(coins) ;
                break ;
        }
    }
    else{
        ui->workerErrorlabel->setText("You do not have a free worker") ;
    }
}

