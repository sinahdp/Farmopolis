// Ground.h
#ifndef CUSTOM_LABEL_H
#define CUSTOM_LABEL_H

#include <QLabel>
#include <QObject>
#include <QTimer>

class Ground : public QLabel {
    Q_OBJECT

public:
    Ground(const QString& text, QWidget* parent = nullptr);

    void calcproductionTimer() ;

    void calcExpirationTimer() ;

    void setVariabels(int typeOfGround) ;

    bool isgreen = 0 ;
    int isfull = 0 ;

    QTimer timerP ;
    QTimer timerE ;
    int counterproduction ;
    int counterExpiration ;

    int productionTime ;
    int ExpirationTime ;
    int amoutOfLoss = 0 ;
    int countProduct = 0 ;
    int priceBuyProduct ;
    int priceSellProduct ;

    int currentFuncP ;
    int currentFuncE ;

    bool firstTime = 1 ;

private:

protected:

};

#endif // CUSTOM_LABEL_H
