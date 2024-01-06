// Ground.h
#ifndef CUSTOM_LABEL_H
#define CUSTOM_LABEL_H

#include <QLabel>
#include <QObject>

class Ground : public QLabel {
    Q_OBJECT

public:
    Ground(const QString& text, QWidget* parent = nullptr);

    bool isgreen = 0 ;
    bool isfull = 0 ;

private :

protected:

};

#endif // CUSTOM_LABEL_H
