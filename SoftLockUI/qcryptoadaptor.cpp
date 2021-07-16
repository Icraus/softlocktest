#include "qcryptoadaptor.h"
#include <functional>
using namespace std::placeholders;
void QCrpytoAdaptor::applyFunctionOnFile(std::function<std::string (std::string, std::string, std::string)> lambdaF, QString inputFile, QString outputFile, QString key, QString iv){
    QFile file(inputFile);
    if(!file.open(QIODevice::ReadOnly)){
        emit error("Error while reading file, maybe file doesn't exist");
    }
    auto output = lambdaF(file.readAll().toStdString(), key.toStdString(), iv.toStdString());
    QFile outputFileHandler(outputFile);
    if(!outputFileHandler.open(QIODevice::WriteOnly)){
        emit error("Error while opening File for writing");
    }
    outputFileHandler.write(output.c_str());
}

void QCrpytoAdaptor::encryptFile(QString inputFile, QString outputFile, QString key, QString iv){
    auto cryptoInstance = Crypto::getInstance();
    applyFunctionOnFile(std::bind(&Crypto::encrypt, cryptoInstance, _1,_2, _3), inputFile, outputFile, key, iv);
}

void QCrpytoAdaptor::decryptFile(QString inputFile, QString outputFile, QString key, QString iv){
    auto cryptoInstance = Crypto::getInstance();
    applyFunctionOnFile(std::bind(&Crypto::decrypt, cryptoInstance, _1,_2, _3), inputFile, outputFile, key, iv);
}
