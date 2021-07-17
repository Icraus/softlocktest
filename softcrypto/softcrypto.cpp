#include "softcrypto.h"
#include <cstring>
#include <cstdlib>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <memory>

inline const unsigned char* to_uchar_str(const Crypto::string_& value) noexcept{
    return reinterpret_cast<Crypto::byte*>(const_cast<char*>(value.c_str()));
}
Crypto::Crypto()
{

    ERR_load_CRYPTO_strings();
    OpenSSL_add_all_algorithms();
}

Crypto::string_ Crypto::encrypt(const string_& plainText, const string_& key, const string_& iv) const
{

    EVP_CIPHER_CTX *ctx;
    int len = plainText.length() + AES_BLOCK_SIZE;

    int ciphertext_len;
    byte *ciphertext = new byte[len];
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, to_uchar_str(key), to_uchar_str(iv)))
        handleErrors();

    auto value = to_uchar_str( plainText);
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, value, plainText.length()))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    auto result = string_(ciphertext, ciphertext + ciphertext_len);
    delete[] ciphertext;
    return std::move(result);

}

void Crypto::handleErrors() const
{
    ERR_print_errors_fp(stderr);
    throw AESException("Error Bad Encrypted file");
}

const Crypto::string_ Crypto::encrpytForBlock(const string_&input, const string_& key, const string_& iv, int block) const
{
    EVP_CIPHER_CTX *ctx;
    int len;

    int ciphertext_len;
    byte *ciphertext = new byte[block];
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, to_uchar_str(key), to_uchar_str(iv)))
        handleErrors();

    auto value = to_uchar_str( input);
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, value, input.length()))
        handleErrors();
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);
    auto result = string_(ciphertext, ciphertext + ciphertext_len);
    delete[] ciphertext;
    return std::move(result);

}
Crypto::string_ Crypto::decrypt(const string_& cipherText, const string_& key, const string_& iv) const
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;
    byte *plain_text = new byte[cipherText.length()];

    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, to_uchar_str(key), to_uchar_str(iv)))
        handleErrors();
    if(1 != EVP_DecryptUpdate(ctx, plain_text, &len, to_uchar_str(cipherText), cipherText.length()))
        handleErrors();
    plaintext_len = len;
    if(1 != EVP_DecryptFinal_ex(ctx, plain_text + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    auto result = string_(plain_text, plain_text + plaintext_len);
    delete[] plain_text;
    return std::move(result);
}

Crypto::string_ Crypto::toBase64(const string_ &text)
{
    byte *p = new byte[text.length()*2];
    int len = EVP_EncodeBlock(p, to_uchar_str(text), text.length());
    string_ result = string_(p, p+len);
    delete[] p;
    return result;
}

Crypto::string_ Crypto::fromBase64(const string_ &text)
{
    byte *p = new byte[text.length()*2];
    int len = EVP_DecodeBlock(p, to_uchar_str(text), text.length());
    string_ result = string_(p, p+len);
    delete[] p;
    return result;

}

void Crypto::writeToFile(FILE *file, const string_ &content)
{
    BIO_dump_fp(file, content.data(), content.length());
}


const Crypto::string_ Crypto::decrpytForBlock(const string_&cipherText, const string_& key, const string_& iv, int block) const
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;
    byte *plain_text = new byte[block];

    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, to_uchar_str(key), to_uchar_str(iv)))
        handleErrors();
    if(1 != EVP_DecryptUpdate(ctx, plain_text, &len, to_uchar_str(cipherText), cipherText.length()))
        handleErrors();
    plaintext_len = len;

    if(1 != EVP_DecryptFinal_ex(ctx, plain_text + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    auto result = string_(plain_text, plain_text + plaintext_len);
    delete[] plain_text;
    return std::move(result);

}
Crypto::~Crypto()
{
    EVP_cleanup();
    ERR_free_strings();

}
