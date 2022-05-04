#include<iostream>
#include<fstream>

size_t getFileSize(std::fstream &file);

int getLength(const char *str);

bool isPrefix(const char *str1, const char *str2);

char *reverseArray(char *str);


void convertDexToHex(char *hex, int num);

size_t convertHexToDex(const char *hex);


void viewFile(const char *buffer, size_t size);


char *addSymbol(const char *buffer, char symbol, size_t size);

char *getValue(char *value, const char *input, size_t startIndex);
