#include <iostream>
#include <fstream>  // работа с файлами
#include <cstdlib>  // рандомим
#include <limits>  // чистим буфера (ввод)
#include <iomanip> // задаем кол-во знаком после запятой

// создаем файл
void FileRandom(const std::string& filename, int count) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Проблема с открытием файла для записи" << std::endl;
        return;
    }
    
    for (int i = 0; i < count; ++i) {
        int randomNumber = rand() % 1000 + 1; // создаем рандомное число 
        outFile << randomNumber << std::endl; // записываем число в строку
    }
    outFile.close();
}
// считываем числа и уменьшаем их
void Reduce(const std::string& inputFilename, const std::string& outputFilename, double k) {
    std::ifstream inFile(inputFilename);
    std::ofstream outFile(outputFilename);
    if (!inFile) {
        std::cerr << "Проблема с открытием исходного файла" << std::endl;
        return;
    }
    if (!outFile) {
        std::cerr << "Проблема с открытием конечного файла" << std::endl;
        return;
    }
    int number;
    while (inFile >> number) {
        // задаем формат вывода и уменьшаем числа
        outFile << std::fixed << std::setprecision(2) << static_cast<double>(number) / k << std::endl; 
    }
    inFile.close();
    outFile.close();
}
// результат
void RelultFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Проблема с открытием файла для чтения" << std::endl;
        return;
    }
    std::cout << "Исходные данные " << filename << ":" << std::endl;
    double number;
    while (inFile >> number) {  // читаем числа и выводим
        std::cout << number << std::endl;
    }
    inFile.close();
}
int main() {
    const std::string inputFilename = "input.txt";
    const std::string outputFilename = "output.txt";
    
    int count;
    std::cout << "Введите количество чисел для записи в файл: ";
    
    while (!(std::cin >> count) || count <= 0) {
        std::cout << "Ошибка, введите положительное целое число: ";
        std::cin.clear();  // обнуляем состояние
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // чистим буфер ввода
    }
    // создаем числа
    FileRandom(inputFilename, count);
    
    double k;
    std::cout << "Введите число k для уменьшения: ";
    
    // проверяем введенное число
    while (!(std::cin >> k) || k <= 0) {
        std::cout << "Ошибка, введите положительное целое число: ";
        std::cin.clear(); // обнуляем состояние
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // чистим буфер ввода
    }
    // читаем, уменьшаем и закидываем в новый файл
    Reduce(inputFilename, outputFilename, k);

    RelultFile(inputFilename);  // результат
    RelultFile(outputFilename);

    return 0;
}
