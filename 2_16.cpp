#include <iostream>
#include <fstream>  // работа с файлами
#include <vector>  // динамический массив
#include <cstdlib>  // рандом 
#include <limits> // чистим буфера

void BinaryFile(const std::string& filename, size_t count) {  // создаем бинарный файл
    std::ofstream outFile(filename, std::ios::binary);  // открываем
    if (!outFile) {
        std::cerr << "Проблема с открытием файла для записи" << std::endl;
        return;
    }
    for (size_t i = 0; i < count; ++i) {  // рандомим
        int number = rand() % 10000; 
        // преобразовываем и записываем числа
        outFile.write(reinterpret_cast<const char*>(&number), sizeof(number));
    }
    outFile.close();
}
// создаем и заполняем матрицу
void Matrix(const std::string& filename, std::vector<std::vector<int>>& matrix, int n) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Проблема с открытием файла для чтения" << std::endl;
        return;
    }
    int number;  // проходим по ячейкам и заполняем их
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (inFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
                matrix[i][j] = number;
            } else {
                matrix[i][j] = 0; // заполняем нулями, если не хватает чисел
            }
        }
    }
    inFile.close();
}
// принимаем матрицу и заменяем число
void Replace(std::vector<std::vector<int>>& matrix, int digit) {
    for (auto& row : matrix) {
        for (auto& elem : row) {  // проходим по всем ячейкам
            if (elem > 0 && std::to_string(elem).front() - '0' == digit) {
                elem = digit; // заменяем ячейку
            }
        }
    }
}
// результат
void ResultMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";  // выводим матрицу
        }
        std::cout << std::endl;
    }
}
// берем цифру от пользователя и проверяем ее
int getDigit() {
    int digit;
    while (true) {
        std::cout << "Введите цифру (от 0 до 9): ";
        std::cin >> digit;

        // проверка ввода 
        if (std::cin.fail() || digit < 0 || digit > 9) {
            std::cin.clear(); // сбрасываем состояние 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // чистим буфер ввода
            std::cout << "Ошибка. Введите целое положительное число от 0 до 9" << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // чистим буфер ввода
            return digit;
        }
    }
}
int main() {
    const std::string filename = "input.bin";
    const int n = 10; // размерность матрицы 
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    BinaryFile(filename, n * n);  // заполняем рандомом 

    Matrix(filename, matrix, n);  // заполняем матрицу из файла

    std::cout << "Исходная матрица:" << std::endl;
    ResultMatrix(matrix);

    int digit = getDigit();  // получаем цифру для замены

    Replace(matrix, digit);  // заменяем элементы

    std::cout << "Исправленная матрица:" << std::endl;  // результат
    ResultMatrix(matrix);

    return 0;
}
