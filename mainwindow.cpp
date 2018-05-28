#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    vol=50;
    counter=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
      sound_play("piano/7.wav");
}

void MainWindow::on_pushButton_2_clicked()
{
      sound_play("piano/6.wav");
}

void MainWindow::on_pushButton_3_clicked()
{
      sound_play("piano/5.wav");
}

void MainWindow::on_pushButton_4_clicked()
{
      sound_play("piano/4.wav");
}

void MainWindow::on_pushButton_5_clicked()
{
      sound_play("piano/3.wav");
}

void MainWindow::on_pushButton_6_clicked()
{
      sound_play("piano/2.wav");
}

void MainWindow::on_pushButton_7_clicked()
{
      sound_play("piano/1.wav");
}
void MainWindow::sound_play(QString location){
    //sound.setSource(QUrl::fromLocalFile(location));
     QSoundEffect* sound_to_play;
    if(sound.isPlaying()){
sound_to_play=new QSoundEffect();
sound_to_play->setSource(QUrl::fromLocalFile(location));
    }
    else{
    sound.setSource(QUrl::fromLocalFile(location));
sound_to_play=&sound;
    }
    sound_to_play->setVolume(vol);
    sound_to_play->setLoopCount(0);
    sound_to_play->play();
}
void MainWindow::on_verticalSlider_valueChanged(int value)
{
    vol=(qreal)value/100;
    ui->label_2->setText(QString::number(vol*100));
}



void MainWindow::on_actionNowy_triggered()
{
    this->createNewTab(this->createTabName());
}
Tab *MainWindow::createNewTab(const QString &title)
{    this->counter++;
    Tab* newTab=new Tab;
    ui->tabWidget->addTab(newTab, title);
    ui->tabWidget->setCurrentWidget(newTab);
     return newTab;
}
QString MainWindow::createTabName()
{

    return "Nowy " + QString::number(counter);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    closeTab(index);
}
bool MainWindow::closeTab(int index)
{
    QMessageBox::StandardButton reply= QMessageBox::question(this,
                                                             "Co dalej",
                                                             "Chcesz zapisać dane?",
                                                             QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
switch (reply)
{
case QMessageBox::Yes:
    //this->save(index);
    ui->tabWidget->removeTab(index);
    counter--;
    return true;
    break;
case QMessageBox::No:
    //qDebug()<<"nie";
    ui->tabWidget->removeTab(index);
    counter--;
    return true;
    break;
case QMessageBox::Cancel:
    //qDebug()<<"cancel";
    return false;
    break;
 default :
    //qDebug()<<"nic";
    return false;
}
}

void MainWindow::on_actionOtw_rz_triggered()
{   int* notes=new int[28*7];
    qDebug()<<"open";
    QString fileName;
    QString filters("Text files (*.txt)" );
    fileName=QFileDialog::getOpenFileName(this, "tytuł oknaaa", QDir::currentPath(), filters);
    qDebug()<<"pRóba odczytu";
    if(fileName.isEmpty()||fileName.isNull())
        qDebug()<<"anulowano otwarcie pliku";
    else{
    Tab* newTab;
    newTab=this->createNewTab(fileName);
    newTab->fileName=fileName;
    //newTab=this->createNewTab(QFileDialog::getSaveFileName(this, "tytuł oknaaa", QDir::currentPath(), filters));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
    {
        qDebug()<<"Blad odczytu";
        return;
    }
    QTextStream in(&file);
    //while(!in.atEnd())
    //{
        for(int j=0;j<7;j++){
        QString line=in.readLine();
        qDebug()<<line;
        for(int i=0;i<28;i++)
        {
            if(line.at(i)=="1")
                notes[i*7+j]=1;
            else
                notes[i*7+j]=0;
        }
        }
    //}
    file.close();
    qDebug()<<"skonczony odczyt";
    newTab->set_notes(notes);
     newTab->saved();
    }
}

void MainWindow::on_actionZapisz_triggered()
{
    qDebug()<<"save";
    this->save(ui->tabWidget->currentIndex());

}
void MainWindow::save(int index){
    Tab* tab_to_save=dynamic_cast<Tab *>(ui->tabWidget->widget(index));
    QString file_name;
    if(tab_to_save->fileName.isNull())
    {
        QString filters("Text files (*.txt)" );
        file_name=QFileDialog::getSaveFileName(this, "tytuł oknaaa", QDir::currentPath(), filters);
    }
    else
        file_name=tab_to_save->fileName;
qDebug()<<"jeszcze tylko zapis";
    QFile file(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug()<<"nie mozna otworzyc pliku do zapisu";
        return;
    }
  QTextStream out(&file);
  int* notes=tab_to_save->generate_notes();
  for(int j=0;j<7;j++){
  for(int i=0;i<28;i++)
  {
      if(notes[i*7+j]==1)
          out<<"1";
      else
          out<<"0";
  }
out<<"\n";
  }
   file.flush();
   QFileInfo fileInfo(file);
   ui->tabWidget->setTabText(index, fileInfo.fileName());
   file.close();
   tab_to_save->saved();
}
