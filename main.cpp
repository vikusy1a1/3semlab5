#include <iostream>
#include <string>
#include <regex>
#include <algorithm> 

//класс для транспоорта
class Transport {
protected:
    std::string licensePlate;
    std::string ownerName;
    std::string model;

public:
    virtual ~Transport() = default;

    // виртуальная функция для проверки номера
    virtual bool isTransportLicensePlate(const std::string& plate) const = 0;

    // Метод для ввода данных
    void inputData() {
        while (true) {
            std::cout << "Enter the license plate: ";
            std::getline(std::cin, licensePlate);

            // Удаляем пробелы из введенного номера
            std::string cleanedPlate = removeSpaces(licensePlate);

            // Добавляем пробел в правильное место для проверки
            std::string formattedPlate = cleanedPlate.substr(0, 6) + " " + cleanedPlate.substr(6);

            // Проверка корректности номера
            if (isTransportLicensePlate(formattedPlate)) {
                licensePlate = formattedPlate; // Сохраняем отформатированный номер
                break; // Выходим из цикла, если номер корректен
            } else {
                std::cout << "Error: The license plate format is incorrect. An example of a valid license plate: A055AE 54\n";
                std::cout << "Please try again.\n";
            }
        }

        std::cout << "Enter the owner's name: ";
        std::getline(std::cin, ownerName);

        std::cout << "Enter the transport model: ";
        std::getline(std::cin, model);
    }

    // Метод для вывода данных
    void displayInfo() const {
        std::cout << "License Plate: " << licensePlate << "\n";
        std::cout << "Owner: " << ownerName << "\n";
        std::cout << "Model: " << model << "\n";
    }

private:
    // Вспомогательная функция для удаления пробелов
    std::string removeSpaces(const std::string& str) const {
        std::string result = str;
        result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end());
        return result;
    }
};

// Класс для автомобиля
class Car : public Transport {
public:
    // Реализация проверки номера
    bool isTransportLicensePlate(const std::string& plate) const override {
        // Регулярное выражение для проверки формата номера
        std::regex pattern(R"(^[A-Z]\d{3}[A-Z]{2} \d{2}$)");
        return std::regex_match(plate, pattern);
    }
};

// Фабричный метод для создания транспортных средств
class TransportFactory {
public:
    static Transport* createTransport(const std::string& type) {
        if (type == "car") {
            return new Car();
        }
        return nullptr;
    }
};

int main() {
    std::cout << "Welcome to the Traffic Police Automated Workstation!\n";

    // Создаем объект транспортного средства с помощью фабрики
    Transport* transport = TransportFactory::createTransport("car");
    if (transport) {
        transport->inputData();
        std::cout << "\nVehicle successfully added!\n";
        transport->displayInfo();
        delete transport;
    } else {
        std::cout << "Error: Invalid vehicle type.\n";
    }

    return 0;
}
