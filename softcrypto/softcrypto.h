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
    ~Crypto();
protected:
    void handleErrors() const;

    Crypto();
};

#endif // SOFTCRYPTO_H
