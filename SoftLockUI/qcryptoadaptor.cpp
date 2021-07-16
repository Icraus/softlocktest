#include "qcryptoadaptor.h"
#include <functional>
using namespace std::placeholders;
void QCrpytoAdaptor::applyFunctionOnFile(std::function<std::string (std::string, std::string, std::string)> lambdaF, QString inputFile, QString outputFile, QString key, QString iv){
    emit state(0, tr("Starting..."));
    auto status = 20;
    emit state(status, tr("Reading from file: %1").arg(inputFile));
    QFile file(inputFile);
    if(!file.open(QIODevice::ReadOnly)){
        emit error(tr("Error while reading file, maybe file: %1 doesn't exist").arg(inputFile));
    }
    status += 20;
    emit state(status, tr("Processing content."));
    auto output = lambdaF(file.readAll().toStdString(), key.toStdString(), iv.toStdString());
    status += 20;
    emit state(status, tr("Finished Applying changes to content."));
    QFile outputFileHandler(outputFile);
    if(!outputFileHandler.open(QIODevice::WriteOnly)){
        emit error(tr("Error while opening file: %1 for writing").arg(inputFile));
    }
    status += 20;
    emit state(status, tr("Writing result to file: %1.").arg(output.c_str()));
    outputFileHandler.write(output.c_str());
    emit state(100, tr("Finished..."));
}

void QCrpytoAdaptor::encryptFile(const QString& inputFile, const QString& outputFile, const QString& key, const QString& iv){
    auto cryptoInstance = Crypto::getInstance();
    try {
        applyFunctionOnFile(std::bind(&Crypto::encrypt, cryptoInstance, _1,_2, _3), inputFile, outputFile, key, iv);
    }  catch (const AESException& ex) {
        emit error(tr("Error encrypting file: %1 %2").arg(inputFile).arg(ex.message.c_str()));
    }
}

void QCrpytoAdaptor::decryptFile(const QString& inputFile, const QString& outputFile, const QString& key, const QString& iv){
    auto cryptoInstance = Crypto::getInstance();
    try{
        applyFunctionOnFile(std::bind(&Crypto::decrypt, cryptoInstance, _1,_2, _3), inputFile, outputFile, key, iv);
    } catch (const AESException& ex) {
        emit error(tr("Error decrypting file: %1 %2").arg(inputFile).arg(ex.message.c_str()));
    }
}

