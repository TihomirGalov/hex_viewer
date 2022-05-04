#include <iostream>
#include "helperFunctions.h"

size_t getFileSize(std::fstream &file) {
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    return size;
}

int getLength(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

bool isPrefix(const char *str1, const char *str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
        i++;
    return str1[i] == '\0';
}

char *reverseArray(char *str) {
    int i = 0;
    int j = getLength(str) - 1;
    while (i < j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
    return str;
}


void convertDexToHex(char *hex, int num) {
    int i = 0;
    if (num == 0) {
        hex[i++] = '0';
        hex[i++] = '0';
        hex[i] = '\0';
        return;
    }
    while (num != 0) {
        int digit = num % 16;
        if (digit < 10)
            hex[i] = (char) (digit + '0');
        else
            hex[i] = (char) (digit - 10 + 'A');
        num /= 16;
        i++;
    }
    hex[i] = '\0';
    reverseArray(hex);
}

size_t convertHexToDex(const char *hex) {
    size_t num = 0;
    int i = 0;
    while (hex[i] != '\0') {
        if (hex[i] >= '0' && hex[i] <= '9')
            num = num * 16 + hex[i] - '0';
        else if (hex[i] >= 'A' && hex[i] <= 'F')
            num = num * 16 + hex[i] - 'A' + 10;
        else if (hex[i] >= 'a' && hex[i] <= 'f')
            num = num * 16 + hex[i] - 'a' + 10;
        i++;
    }
    return num;
}


void viewFile(const char *buffer, size_t size) {
    char byte[3];

    for (int i = 0; i < size; i++) {
       convertDexToHex(byte, (int) buffer[i]);
        std::cout << byte << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < size; i++) {
        if (buffer[i] >= 'a' && buffer[i] <= 'z' || buffer[i] >= 'A' && buffer[i] <= 'Z') {
            std::cout << buffer[i];
        } else {
            std::cout << ".";
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}


char *addSymbol(const char *buffer, const char symbol, size_t size) {
    char *newBuffer = new char[size + 1];
    for (int i = 0; i < size; i++) {
        newBuffer[i] = buffer[i];
    }
    newBuffer[size] = symbol;
    delete[] buffer;
    return newBuffer;
}

char *getValue(char *value, const char *input, size_t startIndex) {
    const size_t inputLen = getLength(input);
    size_t j = 0;
    bool isInvalid = false;

    for (size_t i = startIndex; i < inputLen; i++) {
        if (!(input[i] >= '0' && input[i] <= '9' || input[i] >= 'A' && input[i] <= 'F')) {
            isInvalid = true;
            break;
        }
        value[j] = input[i];
        j++;
    }
    if (isInvalid)
        value[0] = '\0';
    value[j] = '\0';
    return value;
}

