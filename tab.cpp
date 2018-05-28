#include "tab.h"
#include "ui_tab.h"
Tab::Tab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab)
{
    ui->setupUi(this);
    position_of_bar=20;
timer=NULL;
X=20;
seconds=0;
column=0;
int x=0;
int y=0;
for(int i=0; i<28; i++,x+=30){
    y=0;
    for(int j=0; j<7; j++,y+=30){
buttons[i*7+j]=new MyPushButton(this);
buttons[i*7+j]->button->resize(30,30);
buttons[i*7+j]->button->move(27+x,30+y);
     QObject::connect(buttons[i*7+j]->button,SIGNAL(clicked(bool)),buttons[i*7+j],SLOT(func(bool)));
    }
}
ui->line->setFixedWidth(x);
ui->line_3->setFixedWidth(x);
ui->line_2->raise();
}

Tab::~Tab()
{
    delete ui;
}
void Tab::play_sound(){
    ui->label->setText(QString::number(seconds));
    ui->line_2->move(position_of_bar,30);
    ui->label_2->setText((QString::number(position_of_bar)));
    if(position_of_bar>=X && column<28){
        for(int k=0;k<7;k++)
            buttons[column*7+k]->play(0.5, QUrl::fromLocalFile("piano/"+QString::number(k+1)+".wav"));
        column++;
        X+=30;
    }
    if(position_of_bar==860)
    {
        position_of_bar=20;
        X=20;
        seconds=0;
        column=0;
    }
    else{
    position_of_bar+=1;
    seconds+=0.025;
    }
    //"+QString::number(7-k)+"
}
void Tab::on_pushButton_clicked()///START
{
    if(!timer){
        qDebug()<<"timer pusty";
    timer=new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(play_sound()));
    timer->start(25);
    }
    if(!ui->pushButton->isFlat())
ui->pushButton->setFlat(true);

}

void Tab::on_pushButton_2_clicked()///PAUZA
{
   /* if(timer!=NULL){
        timer->stop();
        timer=NULL;
      if(ui->pushButton->isFlat())
    ui->pushButton->setFlat(false);
    }
    */
}

void Tab::on_pushButton_3_clicked() ///STOP
{
    stop_sound();
}
void Tab::stop_sound(){
    if(timer!=NULL){
     timer->stop();
     ui->line_2->move(20,30);
     position_of_bar=20;
     timer=NULL;
     X=20;
     column=seconds=0;
     if(ui->pushButton->isFlat())
     ui->pushButton->setFlat(false);     
     ui->label->setText(QString::number(0));
    }
}

void Tab::on_pushButton_8_clicked()///PAUZA
{
    if(timer!=NULL){
        timer->stop();
        timer=NULL;
      if(ui->pushButton->isFlat())
    ui->pushButton->setFlat(false);
    }
}
void Tab::saved(){
    if_saved=true;
}

void Tab::set_notes(int *notes)
{
    for(int i=0; i<28; i++)
        for(int j=0; j<7; j++)
            if(notes[i*7+j]==1)
              buttons[i*7+j]->set_clicked(true);
            else
              buttons[i*7+j]->set_clicked(false);

    }


void Tab::set_color(QPushButton *button, bool if_clicked)
{
    if(if_clicked)
    button->setStyleSheet("background-color: blue");
    else
        button->setStyleSheet("background-color: white");
}

int *Tab::generate_notes()
{
    int* notes=new int[28*7];
    for(int i=0; i<28; i++)
        for(int j=0; j<7; j++)
            if(buttons[i*7+j]->return_bool())
             notes[i*7+j]=1;
            else
             notes[i*7+j]=0;
    return notes;

}
