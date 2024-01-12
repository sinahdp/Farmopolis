#ifndef FARMOPOLIS_H
#define FARMOPOLIS_H

#include <QMainWindow>

#include "signup.h"
#include "ground.h"
#include "ranking.h"

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

    void setGroundWhenHaveProduct() ;

    void setBackGroundGround(Ground *ground , int productNumber , bool flag) ;

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

    void on_soundpushButton_clicked();

private:
    Ui::Farmopolis *ui;

    Ground *currentground = nullptr ;

    QMediaPlayer gameSound;
    QMediaPlayer clickSound;
    QMediaPlayer alertSound;
    QMediaPlayer coinsSound;
    QMediaPlayer henSound;
    QMediaPlayer sheepSound;
    QMediaPlayer cowSound;
    QMediaPlayer killSound;
    QMediaPlayer plantingSound;

    int remainingTimeGame = 60 ;
    int countremainingTimeGame ;

    QTimer timerGame ;
    QTimer timerIsProduct ;
    QTimer timerproduct ;

    int currentUser = 1 ;
    int numbersOfUsers ;
    int coins = 10 ;

    int henPrice = 3;
    int sheepPrice = 5;
    int cowPrice = 7;
    int wheatPrice = 2;
    int barleyPrice = 2;

    int workerPrice = 5;
    int groundPrice = 3;


    int numberWorkers = 1 ;
    int numberFreeWorkers = 1 ;

    QList<Ground*> groundList ;

};

#endif // FARMOPOLIS_H
