#ifndef SOFTCRYPTO_H
#define SOFTCRYPTO_H

#include "softcrypto_global.h"
#include <string>

class SOFTCRYPTO_EXPORT Crypto
{
public:
    static Crypto& getInstance(){
        static Crypto m_instance;
        return m_instance;
    }
    std::string encrypt(const std::string& text, const std::string& key, const std::string& iv) const;
    std::string decrypt(const std::string& cipherText, const std::string& key, const std::string& iv) const;
    void writeToFile(FILE* file, const std::string &content);
    ~Crypto();
protected:
    void handleErrors() const;
    const std::string decrpytForBlock(const std::string &cipherText, const std::string &key, const std::string &iv, int block) const;
    const std::string encrpytForBlock(const std::string &input, const std::string &key, const std::string &iv, int block) const;
    Crypto();
};


struct AESException: public std::exception{
    std::string message;
    AESException(std::string msg): exception(), message{msg}{

    }
};

#endif // SOFTCRYPTO_H
