#include <iostream>
#include <fstream>  // работа с файлами
#include <cstdlib>  // для функции рандома
#include <ctime>  // инициализирует генератор рандома

// создаем бинарный файл
void BinaryFile(const std::string& filename, size_t count) {  
    std::ofstream outFile(filename, std::ios::binary);  // открываем в бинарном режиме
    if (!outFile) {
        std::cerr << "Проблема с открытием файла для записи" << std::endl;
        return;
    }
    for (size_t i = 0; i < count; ++i) {  // создаем рандомные числа
        int number = rand() % 10000; 
        outFile.write(reinterpret_cast<const char*>(&number), sizeof(number));  // записываем
    }
    outFile.close();
}
// получаем первую и последнюю цифру числа и проверяем на совпадение
bool StartEndNum(int number) {  
    int firstDigit = number;  // первая цифра
    while (firstDigit >= 10) {
        firstDigit /= 10;
    }
    
    int lastDigit = number % 10;  // последняя цифра

    return firstDigit == lastDigit;
}
// заносим нужные числа
void ChangeFile(const std::string& inputFilename, const std::string& outputFilename) {
    std::ifstream inFile(inputFilename, std::ios::binary);  // открываем файлы
    std::ofstream outFile(outputFilename, std::ios::binary);

    if (!inFile) {
        std::cerr << "Проблема с открытием исходного файла" << std::endl;
        return;
    }
    if (!outFile) {
        std::cerr << "Проблема с открытием конечного файла" << std::endl;
        return;
    }
    int number;  // проверяем и преобразуем числа 
    while (inFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        if (StartEndNum(number)) {  // записываем в файл 
            outFile.write(reinterpret_cast<const char*>(&number), sizeof(number));
        }
    }
    inFile.close();
    outFile.close();
}
void ResultFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Проблема с открытием файла для чтения" << std::endl;
        return;
    }
    int number;  // читаем числа из файла и выводим на экран
    std::cout << "Результат "":" << std::endl;
    while (inFile.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        std::cout << number << " "; // результат
    }
    std::cout << std::endl;

    inFile.close();
}
int main() {
    srand(static_cast<unsigned int>(time(0))); // инициализируем генератор рандомных чисел

    const std::string inputFilename = "input.bin";
    const std::string outputFilename = "output.bin";

    BinaryFile(inputFilename, 100); // заполняем 100 рандомами

    ChangeFile(inputFilename, outputFilename);  // ищем нужные числа и закидываем в файл

    ResultFile(inputFilename);  // результат
    ResultFile(outputFilename);

    return 0;
}
