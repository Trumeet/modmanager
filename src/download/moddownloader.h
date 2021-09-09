#ifndef MODDOWNLOADER_H
#define MODDOWNLOADER_H

#include <QTimer>
#include <memory>

#include "downloader.h"
#include "downloadfileinfo.h"

class ModDownloader : public Downloader
{
    Q_OBJECT
public:
    explicit ModDownloader(QObject *parent = nullptr);

    void downloadMod(std::shared_ptr<DownloadFileInfo> info, QString path);
    void updateMod(std::shared_ptr<DownloadFileInfo> info, QString path);
    void startDownload();

    enum DownloadStatus { Idol, Queue, Downloading, Paused, Finished };

    enum DownloadType { Download, Update, Custom };

    const std::shared_ptr<DownloadFileInfo> &fileInfo() const;
    DownloadStatus status() const;
    DownloadType type() const;
    const QString &readySize() const;
    const QString &filePath() const;

    void setStatus(DownloadStatus newStatus);

signals:
    void statusChanged();

    void downloadSpeed(qint64 bytesPerSec);

private:
    QTimer speedTimer_;
    qint64 currentDownloadBytes_ = 0;
    qint64 lastDownloadBytes_ = 0;
    QList<qint64> downloadBytes_;
    std::shared_ptr<DownloadFileInfo> fileInfo_;
    DownloadStatus status_ = DownloadStatus::Idol;
    DownloadType type_;
    QString readySize_;
    QString filePath_;
};

#endif // MODDOWNLOADER_H