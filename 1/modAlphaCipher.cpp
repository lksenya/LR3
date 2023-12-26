#include "modAlphaCipher.h"
#include <locale>
modAlphaCipher::modAlphaCipher(const std::string& skey)
{

    for (unsigned i=0; i<numAlpha.size(); i++) {
        alphaNum[numAlpha[i]]=i;
    }
    key = convert(getValidKey(skey));
    int n = 0;
    for (auto e:key) {
        if (e==0)
            n++;
    }
    if (2*n > key.size())
        throw cipher_error("WeakKey");
}

std::string modAlphaCipher::encrypt(const std::string& open_text)
{

    std::vector<int> work = convert(getValidOpenText(open_text));
    for(unsigned i=0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

std::string modAlphaCipher::decrypt(const std::string& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for(unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

inline std::vector<int> modAlphaCipher::convert(const std::string& s)
{

    std::vector<int> result;
    for(auto c:s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

inline std::string modAlphaCipher::convert(const std::vector<int>& v)
{

    std::string result;
    for(auto i:v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

inline std::string modAlphaCipher::getValidKey(const std::string & s)
{

    if (s.empty())
        throw cipher_error("Empty key");
    std::string tmp(s);
    for (auto c:tmp) {
        if (!isalpha(c))
            throw cipher_error(std::string("Invalid key"));
        if (islower(c))
            c = toupper(c);
    }
    return tmp;
}

inline std::string modAlphaCipher::getValidOpenText(const std::string & s)
{

    std::string tmp;
    for (auto c:s) {
        if (isalpha(c)) {
            if (islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

inline std::string modAlphaCipher::getValidCipherText(const std::string & s)
{

    if (s.empty())
        throw cipher_error("Empty cipher text");
    for (auto c:s) {
        if (!isupper(c))
            throw cipher_error(std::string("Invalid cipher text"));
    }
    return s;
}
