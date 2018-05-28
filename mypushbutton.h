#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QSoundEffect>
#include <QObject>
#include <QDebug>
#include <QUrl>
class MyPushButton: public QObject
{
    Q_OBJECT
public:
    MyPushButton(QWidget *parent);
    void play(qreal vol, QUrl path);
    QPushButton* button;
    void set_clicked(bool if_clicked);
    bool return_bool();
public slots:
    void func(bool if_clicked);
    private:
    bool clicked;
QString path;
};

#endif // MYPUSHBUTTON_H
