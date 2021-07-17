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
    constexpr int block = 256;
    constexpr int string_block = 128;
    std::string result;
    int text_len = plainText.length();
    int iterations = text_len;
    std::string final_result = "";
    auto start_iter = plainText.cbegin();
    auto end_iter = plainText.cbegin();
    auto end_value = 0;
    do{
        end_value = (iterations / string_block) != 0 ? string_block : iterations % string_block;
        start_iter = end_iter;
        end_iter = start_iter + end_value;
        auto result = encrpytForBlock(std::string(start_iter, end_iter), key, iv, block);
        iterations = iterations - end_value;
        final_result.append(result);

    }while(iterations != 0);
    return std::move(final_result);

}

void Crypto::handleErrors() const
{
    ERR_print_errors_fp(stderr);
    throw AESException("Error Bad Encrypted file");
}

const std::string Crypto::encrpytForBlock(const std::string&input, const std::string& key, const std::string& iv, int block) const
{
    EVP_CIPHER_CTX *ctx;
    int len;

    int ciphertext_len;
    unsigned char *ciphertext = new unsigned char[block];
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
    auto result = std::string(ciphertext, ciphertext + ciphertext_len);
    delete[] ciphertext;
    return std::move(result);

}
std::string Crypto::decrypt(const std::string& cipherText, const std::string& key, const std::string& iv) const
{
    constexpr int block = 256;
    constexpr int string_block = 128;
    std::string result;
    int text_len = cipherText.length();
    int iterations = text_len;
    std::string final_result = "";
    auto start_iter = cipherText.cbegin();
    auto end_iter = cipherText.cbegin();
    auto end_value = 0;
    do{
        end_value = (iterations / string_block) != 0 ? string_block : iterations % string_block;
        start_iter = end_iter;
        end_iter = start_iter + end_value;
        auto result = decrpytForBlock(std::string(start_iter, end_iter), key, iv, block);
        iterations = iterations - end_value;
        final_result.append(result);

    }while(iterations != 0);
    return std::move(final_result);
}

void Crypto::writeToFile(FILE *file, const std::string &content)
{
    BIO_dump_fp(file, content.data(), content.length());
}


const std::string Crypto::decrpytForBlock(const std::string&cipherText, const std::string& key, const std::string& iv, int block) const
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;
    unsigned char *plain_text = new unsigned char[block * 2];

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
    auto result = std::string(plain_text, plain_text + plaintext_len);
    delete[] plain_text;
    return std::move(result);

}
Crypto::~Crypto()
{

}
