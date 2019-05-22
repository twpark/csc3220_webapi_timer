#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class HTTPManager : public QObject
{
    Q_OBJECT
public:
    explicit HTTPManager(QObject *parent = nullptr);
    ~HTTPManager();

    void sendImageRequest(QString zip);
    void sendWeatherRequest(QString zip);

signals:
    void ImageReady(QPixmap *image);
    void WeatherJsonReady(QJsonObject *json);

private slots:
    void ImageDownloadedHandler(QNetworkReply *reply);
    void WeatherDownloadedHandler(QNetworkReply *reply);

private:
    QNetworkAccessManager *imageDownloadManager;
    QNetworkAccessManager *weatherAPIManager;
    QByteArray downloadedData;
};

#endif // HTTPMANAGER_H
