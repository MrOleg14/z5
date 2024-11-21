#include <iostream>
#include <fstream>  // работа с файлами
#include <cstdlib>  // рандомим
#include <limits>  // предельные значения типов данных
#include <sstream>  //работа со строками
// создаем файл и закидываем новые числа
void FileRandom(const std::string& filename, int lines, int numLine) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Проблема с открытием файла для записи" << std::endl;
        return;
    }

    for (int i = 0; i < lines; ++i) {  // кол-во строчек
        for (int j = 0; j < numLine; ++j) {
            int randomNumber = rand() % 1000 + 1; // создаем рандомное число 
            outFile << randomNumber;
            if (j < numLine - 1) {
                outFile << " "; // пробелы
            }
        }
        outFile << std::endl; // переходим на новую строчку
    }
    outFile.close();
}
// ищем первое и максимальное число и суммируем
void Sum(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Проблема с открытием файла для чтения" << std::endl;
        return;
    }
    int firstNum = 0;
    int maxNum = std::numeric_limits<int>::min();
    bool NumFound = false;  // булим 1ое число, если оно найдено

    std::string line;
    while (std::getline(inFile, line)) {  // читаем по строчке
        std::istringstream iss(line);  // разбиваем строку
        int number;
        while (iss >> number) {
            if (!NumFound) {
                firstNum = number;
                NumFound = true;
            }
            if (number > maxNum) {
                maxNum = number;
            }
        }
    }
    inFile.close();

    if (NumFound) {
        int sum = firstNum + maxNum;
        std::cout << "1ый элемент (" << firstNum << ") + мах элемент (" << maxNum << ") = " << sum << std::endl;
    } else {
        std::cout << "Файл пустой" << std::endl;
    }
}
int main() {
    const std::string filename = "file.txt";
    int lines, numLine;

    std::cout << "Введите количество строк: ";
    while (!(std::cin >> lines) || lines <= 0) {
        std::cout << "Ошибка, введите положительное целое число: ";
        std::cin.clear();  // обнуляем состояние
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // чистим буфер ввода
    }

    std::cout << "Введите количество чисел в строке: ";
    while (!(std::cin >> numLine) || numLine <= 0) {
        std::cout << "Ошибка, введите положительное целое число: ";
        std::cin.clear();  // обнуляем состояние
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // чистим буфер ввода
    }
    FileRandom(filename, lines, numLine);  // рандомим
    Sum(filename);  // вычисляем сумму

    return 0;
}
