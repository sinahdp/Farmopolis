#ifndef FARMOPOLIS_H
#define FARMOPOLIS_H

#include <QMainWindow>

#include "signup.h"
#include "ground.h"

#include <QTimer>

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class Farmopolis;
}

class Farmopolis : public QMainWindow
{
    Q_OBJECT

public:
    explicit Farmopolis(QWidget *parent = nullptr);

    ~Farmopolis();    

    bool eventFilter(QObject *obj, QEvent *event) ;

    void selectGround(Ground *clickedground);

    void setCoinsLabe(int coins) ;

    void setWorkersLabel(int free , int all) ;

    void setOperatorLabels() ;

private slots:

    void on_buygroundpushButton_clicked();

    void on_buyhenpushButton_clicked();

    void on_buysheeppushButton_clicked();

    void on_buycowpushButton_clicked();

    void on_buyWorkerpushButton_clicked();

    void on_roundStartpushButton_clicked();

    void on_killpushButton_clicked();

    void on_collectpushButton_clicked();

private:
    Ui::Farmopolis *ui;

    Ground *currentground = nullptr ;

    int remainingTime = 180;
    QTimer timer;

    int coins = 100 ;
    int henPrice = 3 ;
    int sheepPrice = 5 ;
    int cowPrice = 7 ;

    int workerPrice = 5 ;
    int groundPrice = 3 ;

    int eggprice = 2 ;
    int milksheep = 3 ;
    int milkcow = 5 ;

    int numberWorkers = 3 ;
    int numberFreeWorkers = 3 ;

};

#endif // FARMOPOLIS_H
