#ifndef FILEOBJECT_H
#define FILEOBJECT_H

#include <QFileInfo>
#include <QObject>

class FileObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(QString extension READ extension NOTIFY extensionChanged)
    Q_PROPERTY(qint64 size READ size NOTIFY sizeChanged)
public:
    explicit FileObject(QObject *parent = nullptr);
public:
    qint64 size();
    QString extension();
    QString filePath();
public slots:
    void setFilePath(QString filePath);
private:
    QString mfilePath = "";
    QFileInfo mfileInfo;
signals:
    void filePathChanged(QString);
    void sizeChanged(qint64);
    void extensionChanged(QString);
};

#endif // FILEOBJECT_H
