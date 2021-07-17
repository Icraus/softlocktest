#ifndef SOFTCRYPTO_H
#define SOFTCRYPTO_H

#include "softcrypto_global.h"
#include <string>

class SOFTCRYPTO_EXPORT Crypto
{

public:
    using byte = unsigned char;
    using string_ = std::string;
    static Crypto& getInstance(){
        static Crypto m_instance;
        return m_instance;
    }
    string_ encrypt(const string_& text, const string_& key, const string_& iv) const;
    string_ decrypt(const string_& cipherText, const string_& key, const string_& iv) const;
    string_ toBase64(const string_ &text);
    string_ fromBase64(const string_ &text);
    void writeToFile(FILE* file, const string_ &content);
    ~Crypto();
protected:
    void handleErrors() const;
    const string_ decrpytForBlock(const string_ &cipherText, const string_ &key, const string_ &iv, int block) const;
    const string_ encrpytForBlock(const string_ &input, const string_ &key, const string_ &iv, int block) const;
    Crypto();
};


struct AESException: public std::exception{

    std::string message;
    AESException(std::string msg): exception(), message{msg}{

    }
};

#endif // SOFTCRYPTO_H
