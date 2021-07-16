#ifndef QCRYPTOADAPTOR_H
#define QCRYPTOADAPTOR_H
#include <softcrypto.h>
#include <QObject>
#include <QFile>
class QCrpytoAdaptor: public QObject{
    Q_OBJECT
public:
    QCrpytoAdaptor(QObject *parent = nullptr): QObject(parent){

    }
    ~QCrpytoAdaptor(){

    }
signals:
    void error(QString errorMessage);
    void started(int progress);
    void state(int progress, QString state);
    void finished(int progress);
private:
    void applyFunctionOnFile(std::function<std::string(std::string, std::string, std::string)> lambdaF, QString inputFile, QString outputFile, QString key, QString iv);
public slots:
    void encryptFile(const QString& inputFile, const QString& outputFile, const QString& key, const QString& iv);
    void decryptFile(const QString& inputFile, const QString& outputFile, const QString& key, const QString& iv);

};

#endif // QCRYPTOADAPTOR_H
