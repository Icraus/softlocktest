#include "qcryptoadaptor.h"
#include <functional>
#include <codecvt>
#include <fstream>
#include <QDebug>
using Crypto_string_ = Crypto::string_;
using namespace std::placeholders;

void QCrpytoAdaptor::applyFunctionOnFile(std::function<Crypto_string_ (Crypto_string_, Crypto_string_, Crypto_string_)> lambdaF, QString inputFile, QString outputFile, QString key, QString iv){
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

    emit state(100, tr("Finished..."));
}

void QCrpytoAdaptor::encryptFile(const QString& inputFile, const QString& outputFile, const QString& key, const QString& iv){
    auto cryptoInstance = Crypto::getInstance();
    try {
        auto f = [&](Crypto_string_ a, Crypto_string_ b, Crypto_string_ c){
             auto out = cryptoInstance.encrypt(a, b, c);
             QFile handler(outputFile);
             if(!handler.open(QIODevice::WriteOnly)){
                 emit error(tr("Error while opening file: %1 for writing").arg(inputFile));
             }
             emit state(80, tr("Writing result to file: %1.").arg(outputFile));
             handler.write(out.c_str());
             return out;

        };

        applyFunctionOnFile(f, inputFile, outputFile, key, iv);
    }  catch (const AESException& ex) {
        emit error(tr("Error encrypting file: %1 %2").arg(inputFile).arg(ex.message.c_str()));
    }
}

void QCrpytoAdaptor::decryptFile(const QString& inputFile, const QString& outputFile, const QString& key, const QString& iv){
    auto cryptoInstance = Crypto::getInstance();
    try{

        emit state(0, tr("Starting..."));
        auto status = 20;
        emit state(status, tr("Reading from file: %1").arg(inputFile));
        QFile file(inputFile);
        if(!file.open(QIODevice::ReadOnly)){
            emit error(tr("Error while reading file, maybe file: %1 doesn't exist").arg(inputFile));
        }

        status += 20;
        emit state(status, tr("Processing content."));
//        auto input = cryptoInstance.fromBase64(file.readAll().toStdString());
//        auto out = cryptoInstance.decrypt(input, key.toStdString(), iv.toStdString());
//        auto input = cryptoInstance.fromBase64(file.readAll().trimmed().toStdString());
        auto out = cryptoInstance.decrypt(file.readAll().toStdString(), key.toStdString(), iv.toStdString());
        QFile handler(outputFile);
        if(!handler.open(QIODevice::WriteOnly)){
            emit error(tr("Error while opening file: %1 for writing").arg(inputFile));
        }
        emit state(80, tr("Writing result to file: %1.").arg(outputFile));
        handler.write(out.c_str());
    } catch (const AESException& ex) {
        emit error(tr("Error decrypting file: %1 %2").arg(inputFile).arg(ex.message.c_str()));
    }
}

