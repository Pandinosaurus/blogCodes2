#ifndef SIMPLE_DOWNLOADER_HPP
#define SIMPLE_DOWNLOADER_HPP

#include <QMainWindow>
#include <QStringList>

#include <QNetworkReply>

class QNetworkAccessManager;

namespace Ui {
class simple_downloader;
}

class simple_downloader : public QMainWindow
{
    Q_OBJECT

public:
    explicit simple_downloader(QWidget *parent = nullptr);
    ~simple_downloader();

    void add_files(QStringList links, QString const &save_at);
    void download();

private slots:
    void download_finished();
    void download_with_different_suffix();
    void network_error(QNetworkReply::NetworkError code);

    void on_pushButtonClearAll_clicked();

    void on_pushButtonDownload_clicked();

private:    
    void download_progress(qint64 bytes_received, qint64 bytes_total);


    Ui::simple_downloader *ui;

    int current_download_row_;
    QNetworkAccessManager *manager_;    
};

#endif // SIMPLE_DOWNLOADER_HPP
