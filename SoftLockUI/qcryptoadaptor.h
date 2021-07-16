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
    void error(QString);
    void started();
    void state(QString state);
    void finished();
private:
    void applyFunctionOnFile(std::function<std::string(std::string, std::string, std::string)> lambdaF, QString inputFile, QString outputFile, QString key, QString iv);
public slots:
    void encryptFile(QString inputFile, QString outputFile, QString key, QString iv);
    void decryptFile(QString inputFile, QString outputFile, QString key, QString iv);

};


#endif // QCRYPTOADAPTOR_H
