#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
class modAlphaCipher
{
private:
    std::string numAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //алфавит по порядку
    std::map <char,int> alphaNum; //ассоциативный массив "номер по символу"
    std::vector <int> key; //ключ
    std::vector<int> convert(const std::string& s); 
    std::string convert(const std::vector<int>& v); 
    std::string getValidKey(const std::string & s);
    std::string getValidOpenText(const std::string & s);
    std::string getValidCipherText(const std::string & s);
public:
    modAlphaCipher()=delete;
    modAlphaCipher(const std::string& skey);
    std::string encrypt(const std::string& open_text);
    std::string decrypt(const std::string& cipher_text);
};
class cipher_error: public std::invalid_argument {
public:
    explicit cipher_error (const std::string& what_arg):
    std::invalid_argument(what_arg) {}
    explicit cipher_error (const char* what_arg):
    std::invalid_argument(what_arg) {}
};
