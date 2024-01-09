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
    setMinimumSize(2000,1250);
    setMaximumSize(2000,1250);

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
            ground->installEventFilter(this);
            gridLayout->addWidget(ground, i, j);
        }
    }
    //set first ground color
    Ground *firstground = qobject_cast<Ground*>(gridLayout->itemAtPosition(0, 4)->widget());
    firstground->setStyleSheet("background-color: #55A630 ;border:3px solid #212529;");
    firstground->isgreen = 1 ;
    currentground = firstground ;

    //set coins and workers
    setCoinsLabe(coins) ;
    setWorkersLabel(numberFreeWorkers , numberWorkers) ;

    //set operatorwidget and workerErrorLabel
    ui->operatorwidget->hide() ;
    ui->coinAndWorkerErrorlabel->hide() ;

    ui->progressBar->setTextVisible(false);

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

void Farmopolis::setOperatorLabels() {
    ui->operatorwidget->show() ;
    ui->coinAndWorkerErrorlabel->hide() ;
    int productNumber = currentground->isfull ;
    switch (productNumber) {
        case 0 :
            ui->operatorwidget->hide() ;
        case 1 :
            ui->animalkilllabel->setStyleSheet("image: url(:/rec/Icons/farm/hen.png);") ;
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/eggs.png);") ;
            break ;
        case 2 :
            ui->animalkilllabel->setStyleSheet("image: url(:/rec/Icons/farm/sheep.png);") ;
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/milk.png);") ;
            break ;
        case 3 :
            ui->animalkilllabel->setStyleSheet("image: url(:/rec/Icons/farm/cow.png);") ;
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/milk.png);") ;
            break ;
        case 4 :
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/wheat.png);") ;
            break ;
        case 5 :
            ui->productcollectlabel->setStyleSheet("image: url(:/rec/Icons/farm/barley.png);") ;
            break ;

    }
    if(currentground->isfull <= 3) {
        ui->killIconlabel->setVisible(true) ;
        ui->animalkilllabel->setVisible(true) ;
        ui->profitkilllabel->setVisible(true) ;
        ui->killpushButton->setVisible(true) ;
        ui->profitkilllabel->setText("     " + QString::number(currentground->priceBuyProduct - 1)) ;
    }
    else {
        ui->killIconlabel->setVisible(false) ;
        ui->animalkilllabel->setVisible(false) ;
        ui->profitkilllabel->setVisible(false) ;
        ui->killpushButton->setVisible(false) ;
    }

    setTimerOperatorLabel() ;
    ui->progressBar->setRange(0, currentground->productionTime);
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

void Farmopolis::buyAnimalOrSeed() {
    currentground->setVariabels(currentground->isfull) ;
    currentground->counterproduction = currentground->productionTime ;
    currentground->counterExpiration = currentground->ExpirationTime ;
    if(currentground->firstTime) {
        currentground->calcproductionTimer() ;
        currentground->calcExpirationTimer() ;
        currentground->firstTime = 0 ;
    }
    setOperatorLabels() ;
    numberFreeWorkers-- ;
    setWorkersLabel(numberFreeWorkers , numberWorkers) ;
    coins = coins - currentground->priceBuyProduct ;
    setCoinsLabe(coins) ;
}

void Farmopolis::on_buyhenpushButton_clicked() {
    if(numberFreeWorkers >= 1) {
        if(coins >= henPrice) {
            if (currentground && currentground->isgreen == 1 && currentground->isfull == 0) {
                QString originalStyles = currentground->styleSheet();
                currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/hen.png) center center no-repeat;");
                currentground->isfull = 1 ;
                buyAnimalOrSeed() ;
            }
        }
        else {
            ui->coinAndWorkerErrorlabel->setText("You dont have enough coins") ;
            ui->coinAndWorkerErrorlabel->show() ;
        }
    }
    else {
        ui->coinAndWorkerErrorlabel->setText("You do not have a free worker") ;
        ui->coinAndWorkerErrorlabel->show() ;
    }
}

void Farmopolis::on_buysheeppushButton_clicked() {
    if(numberFreeWorkers >= 1) {
        if(coins >= sheepPrice) {
            if (currentground && currentground->isgreen == 1 && currentground->isfull == 0) {
                QString originalStyles = currentground->styleSheet();
                currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/sheep.png) center center no-repeat;");
                currentground->isfull = 2 ;
                buyAnimalOrSeed() ;
            }
        }
        else {
            ui->coinAndWorkerErrorlabel->setText("You dont have enough coins") ;
            ui->coinAndWorkerErrorlabel->show() ;
        }
    }
    else {
        ui->coinAndWorkerErrorlabel->setText("You do not have a free worker") ;
        ui->coinAndWorkerErrorlabel->show() ;
    }
}

void Farmopolis::on_buycowpushButton_clicked() {
    if(numberFreeWorkers >= 1) {
        if(coins >= cowPrice) {
            if (currentground && currentground->isgreen == 1 && currentground->isfull == 0) {
                QString originalStyles = currentground->styleSheet();
                currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/cow.png) center center no-repeat;");
                currentground->isfull = 3 ;
                buyAnimalOrSeed() ;
            }
        }
        else {
            ui->coinAndWorkerErrorlabel->setText("You dont have enough coins") ;
            ui->coinAndWorkerErrorlabel->show() ;
        }
    }
    else {
        ui->coinAndWorkerErrorlabel->setText("You do not have a free worker") ;
        ui->coinAndWorkerErrorlabel->show() ;
    }
}

void Farmopolis::on_buywheatpushButton_clicked() {
    if(numberFreeWorkers >= 1) {
        if(coins >= wheatPrice) {
            if (currentground && currentground->isgreen == 1 && currentground->isfull == 0) {
                QString originalStyles = currentground->styleSheet();
                currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/wheat-bag.png) center center no-repeat;");
                currentground->isfull = 4 ;
                buyAnimalOrSeed() ;
            }
        }
        else {
            ui->coinAndWorkerErrorlabel->setText("You dont have enough coins") ;
            ui->coinAndWorkerErrorlabel->show() ;
        }
    }
    else {
        ui->coinAndWorkerErrorlabel->setText("You do not have a free worker") ;
        ui->coinAndWorkerErrorlabel->show() ;
    }
}

void Farmopolis::on_buybarleypushButton_clicked() {
    if(numberFreeWorkers >= 1) {
        if(coins >= barleyPrice) {
            if (currentground && currentground->isgreen == 1 && currentground->isfull == 0) {
                QString originalStyles = currentground->styleSheet();
                currentground->setStyleSheet(originalStyles + "background: #55A630 url(:/rec/Icons/farm/barley-bag.png) center center no-repeat;");
                currentground->isfull = 5 ;
                buyAnimalOrSeed() ;
            }
        }
        else {
            ui->coinAndWorkerErrorlabel->setText("You dont have enough coins") ;
            ui->coinAndWorkerErrorlabel->show() ;
        }
    }
    else {
        ui->coinAndWorkerErrorlabel->setText("You do not have a free worker") ;
        ui->coinAndWorkerErrorlabel->show() ;
    }
}

void Farmopolis::on_roundStartpushButton_clicked() {
    timerGame.start(1000);
    connect(&timerGame, &QTimer::timeout, [&]() {
        remainingTimeGame--;
        if (remainingTimeGame >= 0) {
            ui->roundStartpushButton->setText(QString::number(remainingTimeGame) + " s");
        }
        else {
            timerGame.stop();
            ui->roundStartpushButton->setText("Start");
        }
    });

}

void Farmopolis::on_killpushButton_clicked() {
    currentground->countProduct = 0 ;
    currentground->amoutOfLoss = 0 ;
    currentground->setStyleSheet("border:3px solid #212529 ; background-color: #55A630 ;");
    coins = coins + currentground->priceBuyProduct - 1 ;
    setCoinsLabe(coins) ;
    currentground->isfull = 0 ;
    numberFreeWorkers++ ;
    setWorkersLabel(numberFreeWorkers , numberWorkers) ;
    setOperatorLabels() ;
}

void Farmopolis::on_collectpushButton_clicked() {
    if(numberFreeWorkers >= 1) {
        int count = currentground->countProduct ;
        int price = currentground->priceSellProduct ;
        int less = currentground->amoutOfLoss ;
        coins = coins + count*price - less ;
        currentground->countProduct = 0 ;
        currentground->amoutOfLoss = 0 ;
        setCoinsLabe(coins) ;
    }
    else {
        ui->coinAndWorkerErrorlabel->setText("You do not have a free worker") ;
        ui->coinAndWorkerErrorlabel->show() ;
    }
}

void Farmopolis::setTimerOperatorLabel() {
    timerproduct.start(200) ;
    connect(&timerproduct, &QTimer::timeout, [&]() {
        ui->productionTimerlabel->setText(" 00 : " + QString::number(currentground->counterproduction)) ;
        int count = currentground->countProduct ;
        int price = currentground->priceSellProduct ;
        int less = currentground->amoutOfLoss ;
        int profit = count*price - less ;
        ui->profitCollectionlabel->setText("     " + QString::number(profit)) ;
        ui->progressBar->setValue(currentground->counterproduction) ;
    });
}





