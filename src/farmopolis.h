#ifndef FARMOPOLIS_H
#define FARMOPOLIS_H

#include <QMainWindow>

#include "signup.h"
#include "ground.h"

#include <QTimer>
#include <QTime>

#include <QList>

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

    void setTimerOperatorLabel() ;

    void buyAnimalOrSeed() ;

    void resetGame() ;

    void setFirstGround() ;

    void setUserNameLabel() ;

    void setGameTime() ;

private slots:

    void on_buygroundpushButton_clicked();

    void on_buyhenpushButton_clicked();

    void on_buysheeppushButton_clicked();

    void on_buycowpushButton_clicked();

    void on_buyWorkerpushButton_clicked();

    void on_killpushButton_clicked();

    void on_collectpushButton_clicked();

    void on_buywheatpushButton_clicked();

    void on_buybarleypushButton_clicked();



private:
    Ui::Farmopolis *ui;

    Ground *currentground = nullptr ;

    int remainingTimeGame = 20 ;
    int countremainingTimeGame ;
    QTimer timerGame ;
    QTimer timerproduct ;

    int currentUser = 1 ;
    int numbersOfUsers ;
    int coins = 20 ;

    int henPrice = 3;
    int sheepPrice = 5;
    int cowPrice = 7;
    int wheatPrice = 2;
    int barleyPrice = 2;

    int workerPrice = 5;
    int groundPrice = 3;


    int numberWorkers = 3 ;
    int numberFreeWorkers = 3 ;

    QList<Ground*> groundList ;

};

#endif // FARMOPOLIS_H
