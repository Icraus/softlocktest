#include "fileobject.h"

#include <QUrl>

FileObject::FileObject(QObject *parent) : QObject(parent)
{

}

qint64 FileObject::size()
{   if(mfilePath == "")
        return 0;
    return mfileInfo.size();
}

QString FileObject::extension()
{
    if(mfilePath == "")
        return "";
    return mfileInfo.completeSuffix();
}

QString FileObject::filePath()
{
    if(mfilePath == "")
        return "";
    return QUrl(mfilePath).toLocalFile();
}

void FileObject::setFilePath(QString filePath)
{
    if(mfilePath == filePath){
        return;
    }
    this->mfilePath = filePath;
    mfileInfo = QFileInfo(this->filePath());
    emit filePathChanged(mfilePath);
    emit extensionChanged(mfileInfo.completeSuffix());
    emit sizeChanged(mfileInfo.size());

}
