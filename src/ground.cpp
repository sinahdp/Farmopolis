// Ground.cpp
#include "ground.h"

#include <QEvent>

Ground::Ground(const QString& text, QWidget* parent) : QLabel(text, parent) {

}

void Ground::calcproductionTimer() {
    counterproduction = productionTime ;
    timerP.start(1000) ;
    connect(&timerP, &QTimer::timeout, [=]() {
        counterproduction-- ;
        if (counterproduction == 0) {
            counterproduction = productionTime ;
            countProduct++ ;
        }
    });
}

void Ground::calcExpirationTimer() {
    counterExpiration = ExpirationTime ;
    timerE.start(1000) ;
    connect(&timerE, &QTimer::timeout, [=]() {
        if(countProduct >= 1) {
            counterExpiration--;
            if (counterExpiration == 0) {
                counterExpiration = ExpirationTime ;
                amoutOfLoss++;
                if(amoutOfLoss >= priceSellProduct) {
                    amoutOfLoss = 0 ;
                    countProduct-- ;
                }
            }
        }
        else {
           amoutOfLoss = 0 ;
        }
    });
}

void Ground::setVariabels(int typeOfGround) {
    switch (typeOfGround) {
        case 1 :
            productionTime = 20 ;
            ExpirationTime = 5 ;
            priceBuyProduct = 3;
            priceSellProduct = 3 ;
            amoutOfLoss = 0 ;
            countProduct = 0 ;
            break ;
        case 2 :
            productionTime = 15 ;
            ExpirationTime = 4 ;
            priceBuyProduct = 5 ;
            priceSellProduct = 3 ;
            amoutOfLoss = 0 ;
            countProduct = 0 ;
            break ;
        case 3 :
            productionTime = 20 ;
            ExpirationTime = 3 ;
            priceBuyProduct = 7 ;
            priceSellProduct = 5 ;
            amoutOfLoss = 0 ;
            countProduct = 0 ;
            break ;
        case 4 :
            productionTime = 25 ;
            ExpirationTime = 12 ;
            priceBuyProduct = 2 ;
            priceSellProduct = 3 ;
            amoutOfLoss = 0 ;
            countProduct = 0 ;
            break ;
        case 5 :
            productionTime = 20 ;
            ExpirationTime = 10 ;
            priceBuyProduct = 2 ;
            priceSellProduct = 2 ;
            amoutOfLoss = 0 ;
            countProduct = 0 ;
            break ;
    }
}


