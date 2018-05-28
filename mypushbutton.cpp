#include "mypushbutton.h"

 MyPushButton::MyPushButton(QWidget *parent)
{
     button=new QPushButton(parent);
     button->setStyleSheet("background-color: white");
     clicked=false;
 }


 void MyPushButton::play(qreal vol,QUrl path)
 {
     if(clicked)
     {
         QSoundEffect* sound=new QSoundEffect();
         sound->setSource(path);
         sound->setVolume(vol);
         sound->play();
         qDebug()<<path.toString();
     }
 }

 void MyPushButton::set_clicked(bool if_clicked)
 {
     clicked=if_clicked;   
     if(clicked==true)
     button->setStyleSheet("background-color: blue");
     else
         button->setStyleSheet("background-color: white");

 }

 bool MyPushButton::return_bool()
 {
     return clicked;
 }

 void MyPushButton::func(bool if_clicked)
 {

     if(clicked==false)
     {clicked=true;
     button->setStyleSheet("background-color: blue");
     }
     else{
         clicked=false;
         button->setStyleSheet("background-color: white");
     }
 }
