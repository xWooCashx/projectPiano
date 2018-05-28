#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QHBoxLayout>
#include <mypushbutton.h>
namespace Ui {
class Tab;
}

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit Tab(QWidget *parent = 0);
    ~Tab();
    qreal vol;
    void stop_sound();
    void saved();
    QString fileName;
    void set_notes(int *notes);
    void set_color(QPushButton* button, bool if_clicked);
    int* generate_notes();
private slots:
    void on_pushButton_clicked();
    void play_sound();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_8_clicked();


private:
    Ui::Tab *ui;
    bool if_saved;
    QTimer *timer;
    int position_of_bar;
    MyPushButton* buttons[196];
    int X,column;
    float seconds;
};

#endif // TAB_H
