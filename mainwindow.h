#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>

#include "httpmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void setCurrentTime();
    void processImage(QPixmap *);
    void processWeatherJson(QJsonObject *json);

    void on_imageDownloadButton_clicked();

    void on_weatherDownloadButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    HTTPManager *httpManager;

};

#endif // MAINWINDOW_H
