#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonObject>
#include <QJsonArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(new QTimer),
    httpManager(new HTTPManager)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()),
            this, SLOT(setCurrentTime()));

    setCurrentTime();
    timer->start(1000);

    connect(httpManager, SIGNAL(ImageReady(QPixmap *)),
            this, SLOT(processImage(QPixmap *)));

    connect(httpManager, SIGNAL(WeatherJsonReady(QJsonObject *)),
            this, SLOT(processWeatherJson(QJsonObject *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setCurrentTime()
{
    QTime time = QTime::currentTime();
    QString hour = time.toString("hh");
    QString minute = time.toString("mm");
    QString second = time.toString("ss");

    ui->hourLCD->display(hour);
    ui->minuteLCD->display(hour);
    ui->secondLCD->display(second);
}

void MainWindow::processImage(QPixmap *image)
{
    ui->imageLabel->setPixmap(*image);
}

void MainWindow::processWeatherJson(QJsonObject *json)
{
    qDebug() << "Json ready";
    QString weather = json->value("weather").toArray()[0].toObject()["main"].toString();
    QString weatherDesc = json->value("weather").toArray()[0].toObject()["description"].toString();
    double temp = json->value("main").toObject()["temp"].toDouble();
    double temp_min = json->value("main").toObject()["temp_min"].toDouble();
    double temp_max = json->value("main").toObject()["temp_max"].toDouble();

    qDebug() << weather;
    qDebug() << weatherDesc;
    qDebug() << temp;
    qDebug() << temp_min;
    qDebug() << temp_max;

    ui->weatherLabel->setText("Current Weather: " + weather + ", temp: " + QString::number(temp));

    /*
     * {
     *    "coord": {"lon":-122.38,"lat":47.64},
     *    "weather":[{"id":803,"main":"Clouds","description":"broken clouds","icon":"04d"}],
     *    "base":"stations",
     *    "main":{"temp":288.38,"pressure":1015,"humidity":72,"temp_min":287.04,"temp_max":289.82},
     *    "visibility":16093,
     *    "wind":{"speed":2.22,"deg":329.191},
     *    "clouds":{"all":75},
     *    "dt":1558543054,
     *    "sys":{"type":1,"id":3417,"message":0.0113,"country":"US","sunrise":1558527857,"sunset":1558583303},
     *    "timezone":-25200,"id":420040214,"name":"Seattle","cod":200
     * }
     * */
}

void MainWindow::on_imageDownloadButton_clicked()
{
    QString zip = ui->zipCodeEdit->text();
    qDebug() << zip;
    httpManager->sendImageRequest(zip);
}

void MainWindow::on_weatherDownloadButton_clicked()
{
    QString zip = ui->zipCodeEdit->text();
    qDebug() << zip;
    httpManager->sendWeatherRequest(zip);
}
