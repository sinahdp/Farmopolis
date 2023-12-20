#ifndef SIGNUP_H
#define SIGNUP_H

#include <QMainWindow>

#include <QLabel>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class SignUp; }
QT_END_NAMESPACE

class SignUp : public QMainWindow
{
    Q_OBJECT

public:
    SignUp(QWidget *parent = nullptr);
    ~SignUp();

    //fade animation
    void fadeAnimation() ;
    void emptyTheForm() ;
    void settingFormNumber() ;

    //
    bool checlen(QString str) ;

    bool checkbadstr(QString str) ;

    void generateCaptcha(QLabel *captchaLabel) ;

    void checkCaptcha(QLineEdit *captchaEntry , QLabel *captchaLabel , QLabel *erorLable , int& check) ;

private slots:

    void on_nextpushButton_clicked();

    void on_previouspushButton_clicked();

    void on_boxpushButton_clicked();


    void on_hidepasswordpushButton_clicked();

    void on_generatecapchapushButton_clicked();

    void on_submitAndNextpushButton_clicked();

    void on_darkmodepushButton_clicked();

private:
    Ui::SignUp *ui;
};
#endif // SIGNUP_H
