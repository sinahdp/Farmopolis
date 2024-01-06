#ifndef FARMOPOLIS_H
#define FARMOPOLIS_H

#include <QMainWindow>

#include "signup.h"
#include "ground.h"

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

private slots:

    void on_buygroundpushButton_clicked();

    void on_buyhenpushButton_clicked();

    void on_buysheeppushButton_clicked();

    void on_buycowpushButton_clicked();

    void on_buyWorkerpushButton_clicked();

private:
    Ui::Farmopolis *ui;

    Ground *currentground = nullptr ;

    int coins = 100 ;
    int henPrice = 3 ;
    int sheepPrice = 5 ;
    int cowPrice = 7 ;
    int workerPrice = 5 ;
    int numberFreeWorkers = 3 ;
    int numberWorkers = 3 ;
    int groundPrice = 3 ;
};

#endif // FARMOPOLIS_H
