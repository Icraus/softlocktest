#include "softcrypto.h"
#include <cstring>
#include <cstdlib>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <memory>


inline const unsigned char* to_uchar_str(const std::string& value) noexcept{
    return reinterpret_cast<unsigned char*>(const_cast<char*>(value.c_str()));
}
Crypto::Crypto()
{

}

std::string Crypto::encrypt(const std::string& plainText, const std::string& key, const std::string& iv) const
{
    EVP_CIPHER_CTX *ctx;
    int len;

    int ciphertext_len;
    unsigned char *ciphertext = new unsigned char[plainText.length()];
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, to_uchar_str(key), to_uchar_str(iv)))
        handleErrors();
    auto value = to_uchar_str(plainText);
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, value, plainText.length()))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    auto result = std::string(ciphertext, ciphertext + ciphertext_len);
    delete[] ciphertext;
    return std::move(result);

}

void Crypto::handleErrors() const
{
    ERR_print_errors_fp(stderr);
    throw AESException("Error Bad Encrypted file");
}
std::string Crypto::decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv) const
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;
    unsigned char *plain_text = new unsigned char[ciphertext.length()];

    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, to_uchar_str(key), to_uchar_str(iv)))
        handleErrors();

    if(1 != EVP_DecryptUpdate(ctx, plain_text, &len, to_uchar_str(ciphertext), ciphertext.length()))
        handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plain_text + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    auto result = std::string(plain_text, plain_text + plaintext_len);
    delete[] plain_text;
    return std::move(result);
}

Crypto::~Crypto()
{

}
