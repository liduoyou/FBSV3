#include "ThumbnailProvider.h"
#include <QDebug>
#include <QApplication>
#include <QStyle>
#include <QImage>
#include <QBuffer>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include <QMutexLocker>
#include "CardInfo.h"
const QString ThumbComputerName = "thumbs";
const QString PhonePushImageDir = "/sdcard/DCIM";
const int defaultPhoneThumbId = -1;
const int defaultPhoneImageId = -2;
// const int defaultComputerThumbId = -3;
// const int defaultComputerImageId = -4;
// const int ScanRequestWaittingTimer = 2000; // 2s
const QString APK = "apk";
const QString MP3 = "mp3";
const QString PDF = "pdf";
const QString RAW = "raw";
const QString TXT = "txt";
const QString DOC = "doc";
const QString DOCX = "docx";
const QString PPT = "ppt";
const QString XLS = "xls";
const QString XLSX = "xlsx";
const QString APE = "ape";
const QString RAR = "rar";
const QString ZIP = "zip";

Q_GLOBAL_STATIC(ThumbnailProvider, theInstance)

ThumbnailProvider::ThumbnailProvider(QObject *parent) :
    QObject(parent), ThumbComputerDir(QApplication::applicationDirPath()+"/thumbs"),
    ImageComputerDir(QApplication::applicationDirPath()+"/images"), _defaultPic(NULL)
{
    qDebug() << "construct ThumbnailProvider";
//    connect(NetworkManager::globalInstance(), SIGNAL(networkConnected()), this, SLOT(on_PlugDevice()));
//    connect(NetworkManager::globalInstance(), SIGNAL(networkDisconnected()), this, SLOT(on_UnPlugDevice()));
//    connect(ImagesManager::globalInstance(), SIGNAL(readComplete()), this, SLOT(onReadThumbCompeleted()));
//    connect(FileManager::globalInstance(), SIGNAL(thumbMovedToComputer(QString)), this, SLOT(onPullThumbCompeleted(QString)));
//    connect(FileManager::globalInstance(), SIGNAL(imageMovedToComputer(QString)), this, SLOT(onPullImageCompeleted(QString)));
//    connect(ImagesManager::globalInstance(), SIGNAL(scanCompete(const QString&, const QString&, int)), this, SLOT(onScanCompeleted(QString,QString,int)));
//    connect(FileManager::globalInstance(), SIGNAL(imageDeleteRequest(QStringList)), this, SLOT(onImageDeleteRequest(QStringList)));
    checkComputerDir(ThumbComputerDir);
    checkComputerDir(ImageComputerDir);
}

void ThumbnailProvider::on_PlugDevice() {
//    ImagesManager::globalInstance()->startScanServiceRequest();
    emit StartWorking();
}

void ThumbnailProvider::on_UnPlugDevice() {
    cleanupDatas();
    emit StopWorking();
}

ThumbnailProvider::~ThumbnailProvider() {
    delete _defaultPic;
    qDebug() << "destruct ThumbnailProvider";
}

ThumbnailProvider* ThumbnailProvider::globalInstance() {
    return theInstance();
}

QPixmap ThumbnailProvider::thumb(const QString &imageFile) {
    // 反查对应的缩略图路径
//    QString thumbFileName;
//    FileManager::globalInstance()->extractFileName(_imageDictionary[imageFile].path, thumbFileName);

    QString thumbFileName = "title.png";//test

    QString localThumb = ThumbComputerDir+"/"+thumbFileName;
    QString itsThumb = _imageDictionary[imageFile].path;
    if(QFileInfo(localThumb).exists()) {
        _thumbMutex.lock();
        _imageState[imageFile] = ImageReady;
        _thumbMutex.unlock();
    }
    ImageState imageState = _imageState[imageFile];
    if(imageState == ImageReady) {
//        qDebug() << "load from local";
        QPixmap pic(localThumb);
        return pic.scaled(156, 156, Qt::KeepAspectRatio);
    } else if(imageState == ImageLack) {
//        qDebug() << "lack " << imageFile << " " << itsThumb;
        if(!_requestedImages.contains(imageFile)) {
            _requestedImages.insert(imageFile);
            pullImage(imageFile);
        }
        return defaultPixmap();
    }else {
        if(!_requestedImages.contains(imageFile)) {
            _requestedImages.insert(imageFile);
            requestThumb(imageFile);
        }
        return defaultPixmap();
    }
}

void ThumbnailProvider::pullImage(const QString &imageFile) {
    QStringList files, wantedFiles;
    QString imageFileName, imageFilePath(imageFile);
//    FileManager::globalInstance()->extractFileName(imageFilePath, imageFileName);
    files << imageFilePath;
    wantedFiles << ImageComputerDir+"/"+imageFileName;
    _phoneImageCache.insert(wantedFiles.at(0), files.at(0));
    // 判断图片缓存是否存在
    if(!QFileInfo(wantedFiles.at(0)).exists()) {
//        FileManager::globalInstance()->pullItems(files, wantedFiles, FileManager::MoveImage, true);
    } else {
        onPullImageCompeleted(wantedFiles.first());
    }
}

void ThumbnailProvider::pullThumb(const QString &imageFile) {
    QStringList files, wantedFiles;
    QString thumbFileName, thumbFilePath(_imageDictionary[imageFile].path);
//    FileManager::globalInstance()->extractFileName(thumbFilePath, thumbFileName);
    files << thumbFilePath;
    wantedFiles << ThumbComputerDir+"/"+thumbFileName;
//    FileManager::globalInstance()->pullItems(files, wantedFiles, FileManager::MoveThumb, true);
}

void ThumbnailProvider::requestThumb(const QString &imageFile) {
    if(_imageDictionary.contains(imageFile)) {
        pullThumb(imageFile);
    }
}

const QPixmap& ThumbnailProvider::fileThumbObject(const CardInfo &fileItem, const QSize& size) {
    QString typeDesc;
//    typeDesc.sprintf("%d%d", size.width(), size.height());
//    if(fileItem.fileType() == FileItem::kDir) {
//        typeDesc += "folder";
//    } else if(fileItem.fileType() == FileItem::kFile) {
//        typeDesc += fileItem.fileExtension();
//    }
//    if(fileItem.fileIcon() == ":SdCard/files_icon_folder.png") {
//        typeDesc += "0";
//    } else {
//        typeDesc += "1";
//    }
////    qDebug() << fileItem.absolutePath() << " " << typeDesc;
//    if(!_icons.contains(typeDesc)) {
//        QPixmap pic;
//        if(typeDesc.contains("folder")) {
////            pic.load(fileItem.fileIcon());
//        } else {
//            // 根据文件扩展名来获取图标
//            QString extension(fileItem.fileExtension().toLower());
//            if(extension == APK) {
//                pic.load(":SdCard/adobe_apk.png");
//            } else if(extension == MP3) {
//                pic.load(":SdCard/adobe_mp3.png");
//            } else if(extension == PDF) {
//                pic.load(":SdCard/adobe_pdf.png");
//            } else if(extension == RAW) {
//                pic.load(":SdCard/adobe_raw.png");
//            } else if(extension == TXT) {
//                pic.load(":SdCard/adobe_txt.png");
//            } else if(extension == DOC) {
//                pic.load(":SdCard/office_doc.png");
//            } else if(extension == DOCX) {
//                pic.load(":SdCard/office_doc.png");
//            } else if(extension == PPT) {
//                pic.load(":SdCard/office_ppt.png");
//            } else if(extension == XLS) {
//                pic.load(":SdCard/office_xls.png");
//            } else if(extension == XLSX) {
//                pic.load(":SdCard/office_xls.png");
//            } else if(extension == APE) {
//                pic.load(":SdCard/pro_ape.png");
//            } else if(extension == RAR) {
//                pic.load(":SdCard/rar.png");
//            } else if(extension == ZIP) {
//                pic.load(":SdCard/zip.png");
//            } else {
//                pic.load(":SdCard/other.png");
//            }
//        }
//        pic = pic.scaled(size);
//        QSharedPointer<QPixmap> pPic(new QPixmap(pic));
//        _icons.insert(typeDesc, pPic);
//        //qDebug() << "try to create new item on ThumbnailProvider's pool";
//    }
    return *_icons[typeDesc];
}

QPixmap ThumbnailProvider::defaultPixmap() {
    return QPixmap(":Main/Title.png").scaled(156, 156);//pictures_grid_w140.png
}

void ThumbnailProvider::calculateThumb(const QString &thumbFilePath) {
    if(_thumbDictionary.contains(thumbFilePath)) {
        QString thumbFileName;
//        FileManager::globalInstance()->extractFileName(thumbFilePath, thumbFileName);
        // 图片大小156，156，填充背景
        QImage pic(ThumbComputerDir+"/"+thumbFileName);
        if(QFile::exists(ThumbComputerDir+"/"+thumbFileName)) {
            qDebug() << ThumbComputerDir+"/"+thumbFileName <<" exists";
        } else {
            qDebug() << ThumbComputerDir+"/"+thumbFileName <<" don't exists";
        }
        if(pic.isNull()) {
            qDebug() << "null pic 210 " << ThumbComputerDir+"/"+thumbFileName;
        }
        if(pic.width()>=156 || pic.height()>=156) {
            pic = pic.scaled(156, 156, Qt::KeepAspectRatio);
        }
        QImage background(156, 156,QImage::Format_RGB32);
//        background.fill(QColor("#444444"));
        QPainter painter(&background);
        int x = (background.width()-pic.width())/2;
        int y = (background.height()-pic.height())/2;
        painter.drawImage(x, y, pic);
        background.save(ThumbComputerDir+"/"+thumbFileName);
        QString imageFile(_thumbDictionary[thumbFilePath].path);
        _thumbMutex.lock();
        _imageState[imageFile] = ImageReady;
        _thumbMutex.unlock();
        emit thumbAvaliable(imageFile);
    } else {
        qDebug() << "invalid thumbFileName!" << thumbFilePath;
    }
}

void ThumbnailProvider::onReadThumbCompeleted() {
//    disconnect(ImagesManager::globalInstance(), SIGNAL(readComplete()), this, SLOT(onReadThumbCompeleted()));
    processImageInfo();
//    connect(ImagesManager::globalInstance(), SIGNAL(readComplete()), this, SLOT(onReadThumbCompeleted()));
}

ThumbnailProvider::ThumbInfo::ThumbInfo(int id, int imageId, QString path) {
    this->id = id;
    this->imageId = imageId;
    this->path = path;
}

ThumbnailProvider::ImageInfo::ImageInfo(int id, QString path) {
    this->id = id;
    this->path = path;
}

void ThumbnailProvider::processImageInfo() {
//    QSharedPointer<QMap<QString, Thumbnail> > _images(new QMap<QString, Thumbnail>);
//    ImagesManager::globalInstance()->queryThumbMapImage(_images);
//    if((*_images).size() == 0) {
//        emit noPictures();
//        return ;
//    }

//    cleanupDatas();
//    QMap<QString, Thumbnail>::Iterator it = (*_images).begin();
//    QStringList avaliableImages;
//    while(it != (*_images).end()) {
//        QString key(it.key());
//        if(isWritableImage(key)) { // 只有支持写操作的图片才显示，不支持gif
//            QString path,name;
//            FileManager::globalInstance()->seperatePath(key, path, name);
//            FileManager::globalInstance()->validataPhoneDirectory(path);
//            key = path+name;
//            // 只有检测到有新添加的图片文件时才插入
//            if(!_imageDictionary.contains(key)) {
//                Thumbnail value(it.value());
//                QString thumbPath, thumbName, thumbAbsPath(value.getPath());
//                FileManager::globalInstance()->seperatePath(thumbAbsPath, thumbPath, thumbName);
//                FileManager::globalInstance()->validataPhoneDirectory(thumbPath);
//                value.setPath(thumbPath+thumbName);
//                ImageInfo itsImage(value.imageID(), key);
//                ThumbInfo itsThumb(value.getID(), value.imageID(), value.getPath());
//                avaliableImages << key;
//                if(it.value().getPath() == "thumb lack") {
//                    _thumbMutex.lock();
//                    _imageState.insert(key, ImageLack);
//                    _imageDictionary.insert(key, itsThumb);
//                    _thumbMutex.unlock();
//                } else {
//                    _thumbMutex.lock();
//                    _imageState.insert(key, ImageLoading);
//                    _imageDictionary.insert(key, itsThumb);
//                    _thumbDictionary.insert(value.getPath(), itsImage);
//                    _thumbMutex.unlock();
//                }
//            }
//        } else {
////            qDebug() << key << "is not writtable";
//        }
//        ++it;
//    }
//    if(avaliableImages.size()) {
//        emit hasPictures();
//        emit imageInfoAvaliable(avaliableImages);
//    } else {
//        emit noPictures();
//    }
}

void ThumbnailProvider::onPullThumbCompeleted(const QString &thumbFilePath) {
//    qDebug() << "pull " << thumbFilePath << " successfully";
//    QtConcurrent::run(this, &ThumbnailProvider::calculateThumb, thumbFilePath);
}

/*
 * 拉取图片到PC后，调用loadComputerImages方法生成缩略图，加载到GUI
 */
void ThumbnailProvider::onPullImageCompeleted(const QString &imageFileName) {
    QStringList imageFiles;
    imageFiles << imageFileName;
    loadcomputerImages(imageFiles, false);
}

void ThumbnailProvider::onScanCompeleted(const QString& imagePath, const QString& thumbnailPath,  int imageID) {
//    qDebug() << imagePath << " scan successfully " << thumbnailPath << " " << imageID;
//    ImageInfo itsImage(imageID, imagePath);
//    ThumbInfo itsThumb(defaultPhoneThumbId, defaultPhoneImageId, thumbnailPath);
//    _thumbMutex.lock();
//    _imageState[imagePath] = ImageLoading;
//    _imageDictionary.insert(imagePath, itsThumb);
//    _thumbDictionary.insert(thumbnailPath, itsImage);
//    _thumbMutex.unlock();
//    if(!_requestedImages.contains(imagePath)) {
//        _requestedImages.insert(imagePath);
//        // 拉取图片
//        requestThumb(imagePath);
//    }
}

void ThumbnailProvider::cleanupDatas() {
    _requestedImages.clear();
    _phoneImageCache.clear();
    _imageDictionary.clear();
    _thumbDictionary.clear();
}

void ThumbnailProvider::deletePics(const QStringList &filePaths) {
    emit imageDeleted(filePaths);
    foreach(const QString& filePath, filePaths) {
        ThumbInfo itsThumb(_imageDictionary[filePath]);
        QString thumbFileName;
//        FileManager::globalInstance()->extractFileName(itsThumb.path, thumbFileName);
        QString thumbPath(ThumbComputerDir+"/"+ thumbFileName);
//        FileManager::globalInstance()->deletePcPicture(thumbPath);
        if(_thumbDictionary.contains(itsThumb.path)) {
            // 更新容器
            ImageInfo itsImage(_thumbDictionary[itsThumb.path]);
            //qDebug() << itsThumb.path << " " << itsImage.path;
            _imageDictionary.remove(itsImage.path);
            _thumbDictionary.remove(itsThumb.path);
            if(itsThumb.imageId != defaultPhoneImageId) {
                // 发送删除请求
//                ImagesManager::globalInstance()->deleteThumbunailRequest(itsThumb.imageId);
            } else {
                // 使用文件管理器删除手机图片，而且删除PC上的图片缓存
//                FileManager::globalInstance()->deletePicture(filePath);
                QString imageFileName;
//                FileManager::globalInstance()->extractFileName(filePath, imageFileName);
//                FileManager::globalInstance()->deletePcPicture(ImageComputerDir+"/"+imageFileName);
            }
        } else {
            qDebug() << "the image has no thumbs record in phone " << itsThumb.path;
        }
    }
}

void ThumbnailProvider::checkComputerDir(const QString& dirPath) {
    QDir dir(dirPath);
    if(!dir.exists()) {
        dir.mkpath(dirPath);
    }
}

/*
 * 函数: loadcomputerImages
 * 功能描述: 导入电脑图片支持两种模式(是否推送到手机)
 *    如果需要将图片推送到手机，那么需要重置图片路径为手机路径
 *    否则，只需要生成缩略图(对应无法从手机获取缩略图，只能拉取手机图片到PC的情况)
 */
void ThumbnailProvider::loadcomputerImages(QStringList &filePaths, bool needPushtoPhone) {
    QStringList pushFiles;
    if(needPushtoPhone) {
        checkImagesExist(filePaths);
    }

    // 生成缩略图
    foreach(const QString& filePath, filePaths) {
        QString fileName;
//        FileManager::globalInstance()->extractFileName(filePath, fileName);
        QString thumbPath(ThumbComputerDir+"/"+fileName);
        QFile::copy(filePath, thumbPath);
        QPixmap pic(thumbPath);
        if(pic.isNull()) {
            qDebug() << "null 390 " << thumbPath;
        }
        if(pic.width()>=156 || pic.height()>=156) {
            pic = pic.scaled(156, 156, Qt::KeepAspectRatio);
            pic.save(thumbPath);
        }
        QString phoneImagePath(filePath);
        if(!needPushtoPhone) { // 对于将图片拉取到本地再生成缩略图的情况，需要查找手机图片路径
            phoneImagePath = _phoneImageCache[filePath];
        } else {
            phoneImagePath = PhonePushImageDir+"/"+fileName;
            pushFiles << phoneImagePath;
        }
        ThumbInfo itsThumb(defaultPhoneThumbId, defaultPhoneImageId, thumbPath);
        ImageInfo itsImage(defaultPhoneImageId, phoneImagePath);
        if(!needPushtoPhone) {
            if(_imageDictionary.contains(phoneImagePath)) {
                itsThumb.imageId = _imageDictionary[phoneImagePath].imageId;
            }
        }
        _thumbMutex.lock();
        _imageState.insert(phoneImagePath, ImageLoading);
        _imageDictionary.insert(phoneImagePath, itsThumb);
        _thumbDictionary.insert(thumbPath, itsImage);
        _thumbMutex.unlock();
//        QtConcurrent::run(this, &ThumbnailProvider::calculateThumb, thumbPath);
    }
    if(needPushtoPhone) {
        if(pushFiles.size()) {
            emit hasPictures();
            emit preappendImage(pushFiles);
//            FileManager::globalInstance()->pushItems(filePaths, pushFiles, FileManager::ImportImage);
        }
    }
}

//bool ThumbnailProvider::isPhoneImage(const QString &imagePath) {
//    return !isComputerImage(imagePath);
//}

//bool ThumbnailProvider::isComputerImage(const QString &imagePath) {
//    if(_imageDictionary.contains(imagePath)) {
//        return _imageDictionary[imagePath].id == defaultComputerThumbId;
//    }
//    return false;
//}

bool ThumbnailProvider::copyComputerImages(const QStringList &files, const QStringList &wantedFiles) {
    if(files.size() == 0) {
        return true;
    }
    for(int i=0;i<files.size();++i) {
        if(!QFile::copy(files[i], wantedFiles[i])) {
            QMessageBox msgBox;
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("导出图片%1时出错，请检查是否有权限").arg(files[i]));
            msgBox.exec();
            return false;
        }
    }
    return true;
}

bool ThumbnailProvider::isImage(const QString &extension) {
    QRegExp imageSuffix("(jpg|jpeg|bmp|png)");
    imageSuffix.setCaseSensitivity(Qt::CaseInsensitive);
    return imageSuffix.exactMatch(extension);
}

/*
 * 判断文件是否可以执行写操作，当前默认/mnt/sdcard/, /sdcard/, /storage/下面的图片不能执行写操作
 */
bool ThumbnailProvider::isWritableImage(const QString &filePath) {
    QRegExp regx("^(/sdcard/|/mnt/sdcard/|/storage/).+$");
    QRegExp imageSuffix(".+\\.(jpg|jpeg|png|bmp)$"); // qt库不支持gif写操作
    imageSuffix.setCaseSensitivity(Qt::CaseInsensitive);
    return regx.exactMatch(filePath) && imageSuffix.exactMatch(filePath);
}

void ThumbnailProvider::checkImagesExist(QStringList &srcFilePaths) {
    QStringList filePaths;
    bool yesToAll = false;
    // 判断是否已导入
    foreach(const QString& filePath, srcFilePaths) {
        QString fileName;
//        FileManager::globalInstance()->extractFileName(filePath, fileName);
        QString phoneImagePath = PhonePushImageDir+"/"+fileName;
        if(!yesToAll && _imageDictionary.contains(phoneImagePath)) {
            QMessageBox msgBox;
            msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes | QMessageBox::YesToAll);
            msgBox.setWindowTitle(tr("提示"));
            msgBox.setText(tr("图片%1已经存在, 是否重新导入该图片?").arg(phoneImagePath));
            int ret = msgBox.exec();
            if(ret == QMessageBox::Yes) {
                filePaths << filePath;
            } else if(ret == QMessageBox::YesToAll) {
                yesToAll = true;
                filePaths << filePath;
            }
        } else {
            filePaths << filePath;
        }
    }
    srcFilePaths = filePaths;
}

void ThumbnailProvider::onImageDeleteRequest(const QStringList &imageFiles) {
    QStringList pics;
    for(int i=0;i<imageFiles.size();++i) {
        if(isWritableImage(imageFiles[i])) {
            pics << imageFiles[i];
        }
    }
    if(pics.size()) {
        deletePics(pics);
    }
}
