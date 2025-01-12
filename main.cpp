#include <iostream>
#include <string>
#include <regex>
#include <algorithm> 
using namespace std;

//класс для транспоорта
class Transport {
protected: //  защищенное поле
   string licensePlate;
   string ownerName;
   string model;

public:
    virtual ~Transport() = default; // Виртуальный деструктор для корректного удаления объектов производных классов

    // виртуальная функция для проверки номера
    virtual bool isTransportLicensePlate(const string& plate) const = 0;

    // Метод для ввода данных
    void inputData() {
        while (true) {
           cout << "Enter the license plate: ";
            getline(cin, licensePlate);

            // Удаляем пробелы из введенного номера
            string cleanedPlate = removeSpaces(licensePlate);

            // Добавляем пробел в правильное место для проверки
            string formattedPlate = cleanedPlate.substr(0, 6) + " " + cleanedPlate.substr(6); // пробел после 6 символа

            // Проверка корректности номера
            if (isTransportLicensePlate(formattedPlate)) {
                licensePlate = formattedPlate; // Сохраняем отформатированный номер
                break; 
            } else {
                cout << "Error: The license plate format is incorrect. An example of a valid license plate: A055AE 54\n";
                cout << "Please try again.\n";
            }
        }

        cout << "Enter the owner's name: ";
        getline(cin, ownerName);

        cout << "Enter the transport model: ";
        getline(cin, model);
    }

    // Метод для вывода данных
    void displayInfo() const {
        cout << "License Plate: " << licensePlate << "\n";
        cout << "Owner: " << ownerName << "\n";
        cout << "Model: " << model << "\n";
    }

private:
    // Вспомогательная функция для удаления пробелов
    string removeSpaces(const string& str) const {
        string result = str;
        result.erase(remove_if(result.begin(), result.end(), ::isspace), result.end());
        return result;
    }
};

// Класс для автомобиля
class Car : public Transport {
public:
    // Реализация проверки номера
    bool isTransportLicensePlate(const string& plate) const override {
        // Регулярное выражение для проверки формата номера
        regex pattern(R"(^[A-Z]\d{3}[A-Z]{2} \d{2}$)");
        return regex_match(plate, pattern);
    }
};

// Фабричный метод для создания транспортных средств
class TransportFactory {
public:
    static Transport* createTransport(const string& type) {
        if (type == "car") {
            return new Car();
        }
        return nullptr;
    }
};

int main() {
    cout << "Welcome to the automated workplace of the Traffic Police!\n";

    // Создаем объект транспортного средства с помощью фабрики
    Transport* transport = TransportFactory::createTransport("car");
    if (transport) {
        transport->inputData();
        cout << "\nTransport added successfully!\n";
        transport->displayInfo();
        delete transport;
    } else {
        cout << "Error: Invalid transport type.\n";
    }

    return 0;
}
