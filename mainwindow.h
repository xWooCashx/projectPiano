#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>
#include <QSoundEffect>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <tab.h>
#include <QFileDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
void sound_play(QString location);
Tab *createNewTab(const QString &title);
QString createTabName();
bool closeTab(int index);
qreal vol;
void save(int index);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_actionNowy_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionOtw_rz_triggered();

    void on_actionZapisz_triggered();

private:
    Ui::MainWindow *ui;
    QSoundEffect sound;
    int counter;
};

#endif // MAINWINDOW_H
