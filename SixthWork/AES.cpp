#include <openssl/evp.h>
#include <openssl/rand.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip> 
#include <Windows.h>
#include <string>

using namespace std;

vector<unsigned char> EncryptAes(string& plain_text, vector<unsigned char>& key) {
    unsigned char iv[16];
    RAND_bytes(iv, 16);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv);

    vector<unsigned char> ciphertext(plain_text.size() + 16);
    int len1 = 0, len2 = 0;

    EVP_EncryptUpdate(ctx, ciphertext.data(), &len1,
        (unsigned char*)plain_text.c_str(), plain_text.size());

    EVP_EncryptFinal_ex(ctx, ciphertext.data() + len1, &len2);

    ciphertext.resize(len1 + len2);

    EVP_CIPHER_CTX_free(ctx);

    vector<unsigned char> result;
    result.insert(result.end(), iv, iv + 16);
    result.insert(result.end(), ciphertext.begin(), ciphertext.end());
    return result;
}

string DecryptAes(vector<unsigned char>& encrypted_data, vector<unsigned char>& key) {
        unsigned char iv[16];
        copy(encrypted_data.begin(), encrypted_data.begin() + 16, iv);

        vector<unsigned char> ciphertext(encrypted_data.begin() + 16, encrypted_data.end());

        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key.data(), iv);

        vector<unsigned char> plaintext(ciphertext.size() + 16);
        int len1 = 0, len2 = 0;

        EVP_DecryptUpdate(ctx, plaintext.data(), &len1, ciphertext.data(), ciphertext.size());

        EVP_DecryptFinal_ex(ctx, plaintext.data() + len1, &len2);
        plaintext.resize(len1 + len2);

        EVP_CIPHER_CTX_free(ctx);

        return string(plaintext.begin(), plaintext.end());
}

void InputFile(string data) {
    ofstream input("data.txt");

    if (input.is_open())
    {
        input << data;
        input.close();
    }
    else {
        cout << "Файл не был открыт" << endl;
    }
}

void OutputFile(string data) {
    ofstream input("data.txt");

    if (input.is_open())
    {
        input << data;
        input.close();
    }
    else {
        cout << "Файл не был открыт" << endl;
    }
}


string OutputFile() {
    ifstream output("data.txt");
    string data;
    if (output.is_open())
    {

        getline(output,data);
        output.close();
    }
    else {
        cout << "Файл не был открыт" << endl;
    }

    return data;
}






int main() {
    setlocale(LC_ALL,"");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string original_text;
    cout << "Введите текст для шифрования: "; getline(cin, original_text);
    InputFile(original_text);
    original_text = OutputFile();

    vector<unsigned char> key(32);

    vector<unsigned char> encrypted = EncryptAes(original_text, key);

    string decrypted_text = DecryptAes(encrypted, key);

    cout << "Исходный: " << original_text << endl;
    cout << "Шифрованный: ";
    for (auto& item : encrypted) {

        cout << item;

    }
    cout << endl;
    cout << "Расшифрованный: " << decrypted_text << endl;
    cout << "Совпадает: " << (original_text == decrypted_text ? "ДА" : "НЕТ") << endl;

    return 0;
}