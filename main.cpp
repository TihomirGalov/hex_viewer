#include <iostream>
#include "helperFunctions.h"


int main() {
    const size_t LEN = 1024;
/*
    int x = 25409;
    std::ofstream write_file("myData.dat", std::ios::binary);
    write_file.write((const char *) &x, sizeof(x));
    write_file.close();
*/


    char path[LEN];

    std::cout << "Enter a file path:" << std::endl;
    std::cout << ">";
    std::cin >> path;
    std::fstream file(path, std::ios::binary | std::ios::in);
    size_t size = getFileSize(file);

    if (!file.is_open()) {
        std::cout << "Invalid file \n";
        return 0;
    }

    std::cout << "File loaded successfully! Size:" << size << " bytes\n";
    char input[LEN];
    char *buffer = new char[LEN];
    file.read(buffer, LEN);

    file.close();
    std::cout << ">";

    while (!isPrefix("save", input)) {
        std::cin.getline(input, LEN);

        if (isPrefix("view", input))
            viewFile(buffer, size);
        else if (isPrefix("remove", input)) {
            buffer[size - 1] = '\0';
            size--;
            std::cout << "Operation successfully executed!\n";

        }
        else if (isPrefix("add", input)) {
            char value[3];
            getValue(value, input, 4); // 4 is the length of "add"
            if (value[0] == '\0') {
                std::cout << "Invalid value!\n";
                continue;
            }
            buffer = addSymbol(buffer, (char) convertHexToDex(value), size);
            size++;
            std::cout << "Operation successfully executed!\n";
        }
        else if (isPrefix("change", input)) {
            int pos = 0;
            char value[3];
            const size_t inputLen = getLength(input);

            int i;
            for (i = 7; i < inputLen; i++) {
                if (input[i] == ' ')
                    break;
                pos = pos * 10 + input[i] - '0';

            }
            getValue(value, input, i + 1); // 7 is the length of "change"

            if (value[0] == '\0' || pos < 0 || pos >= size) {
                std::cout << "Invalid value!\n";
                continue;
            }

            buffer[pos] = (char) convertHexToDex(value);
            std::cout << "Operation successfully executed!\n";
        } else
            continue;
        std::cout << ">";

    }

    if (isPrefix("save as", input)) {
        char newPath[LEN];
        const size_t inputLen = getLength(input);
        size_t j = 0;

        for (int i = 8; i < inputLen; i++) {
            newPath[j] = input[i];
            j++;
        }
        std::fstream newFile(newPath, std::ios::binary | std::ios::out | std::ios::trunc);

        if (!newFile.is_open()) {
            std::cout << "Invalid file \n";
            return 0;
        }

        file.seekg(0, std::ios::beg);
        newFile.seekp(0, std::ios::beg);
        for (int i = 0; i < size; i++) {
            newFile.put(buffer[i]);
        }
        newFile.close();
    } else {
        std::fstream newFile(path, std::ios::binary | std::ios::out | std::ios::trunc);

        if (!newFile.is_open()) {
            std::cout << "Invalid file \n";
            return 0;
        }

        file.seekg(0, std::ios::beg);
        newFile.seekp(0, std::ios::beg);
        for (int i = 0; i < size; i++) {
            newFile.put(buffer[i]);
        }
        newFile.close();
    }

    return 0;
}
