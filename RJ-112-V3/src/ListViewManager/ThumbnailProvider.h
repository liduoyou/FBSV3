#ifndef THUMBNAILPROVIDER_H
#define THUMBNAILPROVIDER_H

#include <QObject>
#include <QMap>
#include <QPixmap>
#include <QSharedPointer>
#include <QSize>
#include <QStringList>
#include <QByteArray>
#include <QSet>
#include <QMutex>
#include "CardInfo.h"
/*
 * 类名: ThumbnailProvider
 * 用途: 采用工厂模式，提供接口来创建文件缩略图对象
 */
class ThumbnailProvider : public QObject
{
    Q_OBJECT
public:
    explicit ThumbnailProvider(QObject *parent = 0);
    ~ThumbnailProvider();
    static ThumbnailProvider* globalInstance();
    const QPixmap& fileThumbObject(const CardInfo& fileItem, const QSize& size);
    QPixmap defaultPixmap();
    QPixmap thumb(const QString& imageFile);
    void deletePics(const QStringList& filePaths);
    void loadcomputerImages(QStringList& filePaths, bool addDataToModel = true);
//    bool isPhoneImage(const QString& imagePath);
//    bool isComputerImage(const QString& imagePath);
    bool copyComputerImages(const QStringList& files, const QStringList& wantedFiles);
    bool isImage(const QString& extension);
    bool isWritableImage(const QString& filePath);
    void rescan();

signals:
    void imageInfoAvaliable(const QStringList& imageFiles);
    void preappendImage(const QStringList& imageFiles);
    void thumbAvaliable(const QString& file);
    void imageDeleted(const QStringList& imageFiles);
    void StartWorking();
    void StopWorking();
    void noPictures();
    void hasPictures();

private slots:
    void onReadThumbCompeleted();
    void onPullThumbCompeleted(const QString& thumbFileName);
    void onPullImageCompeleted(const QString& imageFileName);
    void onScanCompeleted(const QString& filePath, const QString& thumbnailPath,  int imageID);
    void on_PlugDevice();
    void on_UnPlugDevice();
    void onImageDeleteRequest(const QStringList& imageFiles);

private:
    void requestThumb(const QString& imageFile);
    void pullImage(const QString& imageFile);
    void pullThumb(const QString& imageFile);
//    bool isLocalFile(const QString& file);
    void processImageInfo();
    void calculateThumb(const QString& thumbFilePath);
    QByteArray getThumb(const QString& file);
    void cleanupDatas();
    void checkComputerDir(const QString& dirPath);
    void checkImagesExist(QStringList& filePaths);
    class ImageInfo{
    public:
        ImageInfo(int id = -1000, QString path = "");
        int id;
        QString path;
    };
    class ThumbInfo {
    public:
        ThumbInfo(int id = -1000, int imageId = -2000, QString path = "");
        int id;
        int imageId;
        QString path;
    };
    QString ThumbComputerDir;
    QString ImageComputerDir;
    QMap<QString, QSharedPointer<QPixmap> > _icons;
    QMap<QString, ThumbInfo> _imageDictionary;
    QMap<QString, ImageInfo> _thumbDictionary;
    QSet<QString> _requestedImages; // 记录有对应缩略图的图片, 防止多次对同一图片请求缩略图
    QHash<QString, QString> _phoneImageCache; // 记录手机图片在电脑上的缓存的路径，
                                              // 该缓存用于无法从手机获取缩略图的情况
//    QList<QString> _scanQuestQueue;
    enum ImageState {
        ImageLoading = 0,
        ImageReady,
        ImageLack,
    };
    QMap<QString, ImageState> _imageState;
    QPixmap *_defaultPic;
    QMutex _thumbMutex;
//    bool _startedScan; //启动软件时，启动扫描
};

#endif // THUMBNAILPROVIDER_H
