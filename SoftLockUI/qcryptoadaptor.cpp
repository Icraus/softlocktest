#include "qcryptoadaptor.h"
#include <functional>
using namespace std::placeholders;
void QCrpytoAdaptor::applyFunctionOnFile(std::function<std::string (std::string, std::string, std::string)> lambdaF, QString inputFile, QString outputFile, QString key, QString iv){
    emit started();
    emit state(tr("Reading from file: %1").arg(inputFile));
    QFile file(inputFile);
    if(!file.open(QIODevice::ReadOnly)){
        emit error(tr("Error while reading file, maybe file: %1 doesn't exist").arg(inputFile));
    }
    emit state(tr("Processing content."));
    auto output = lambdaF(file.readAll().toStdString(), key.toStdString(), iv.toStdString());
    emit state(tr("Finished Applying changes to content."));
    QFile outputFileHandler(outputFile);
    if(!outputFileHandler.open(QIODevice::WriteOnly)){
        emit error(tr("Error while opening file: %1 for writing").arg(inputFile));
    }
    emit state(tr("Writing result to file: %1.").arg(output.c_str()));
    outputFileHandler.write(output.c_str());
    emit finished();
}

void QCrpytoAdaptor::encryptFile(QString inputFile, QString outputFile, QString key, QString iv){
    auto cryptoInstance = Crypto::getInstance();

    applyFunctionOnFile(std::bind(&Crypto::encrypt, cryptoInstance, _1,_2, _3), inputFile, outputFile, key, iv);
}

void QCrpytoAdaptor::decryptFile(QString inputFile, QString outputFile, QString key, QString iv){
    auto cryptoInstance = Crypto::getInstance();
    applyFunctionOnFile(std::bind(&Crypto::decrypt, cryptoInstance, _1,_2, _3), inputFile, outputFile, key, iv);
}
