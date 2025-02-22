#include <iostream>
#include <regex>
#include <stdexcept>
#include <ctime>
#include <vector>
#include "contact.h"

namespace {
// Шаблоны регулярных выражений для проверки входных данных
const std::regex kNamePattern("^[A-Za-zА-Яа-яЁё][A-Za-zА-Яа-яЁё\\- ]*[A-Za-zА-Яа-яЁё]$");
const std::regex kDatePattern("^\\d{2}-\\d{2}-\\d{4}$");
const std::regex kEmailPattern("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
const std::regex kPhonePattern("^\\+?([0-9\\-\\(\\) ]{0,1}[0-9]){11}$");
const std::regex kSpaceTrim("^\\s+|\\s+$");
const std::regex kAllSpaces("\\s+");
}

// Конструктор по умолчанию
Contact::Contact()
    : FirstName("NoFirstName"),
    MiddleName("NoMiddleName"),
    LastName("NoLastName"),
    Date("00-00-0000"),
    Email("noname@nomail.com"),
    PhoneNumber("+0000000000")
{
}

// Конструктор с параметрами
Contact::Contact(const std::string &fName, const std::string &mName,
                 const std::string &lName, const std::string &bDate,
                 const std::string &email, const std::string &phoneNumber)
{
    if (!IsValidName(fName))
        throw std::invalid_argument("Invalid first name provided.");
    if (!IsValidName(mName))
        throw std::invalid_argument("Invalid middle name provided.");
    if (!IsValidName(lName))
        throw std::invalid_argument("Invalid last name provided.");
    if (!IsValidDate(bDate))
        throw std::invalid_argument("Invalid bDate provided.");
    if (!IsValidEmail(email))
        throw std::invalid_argument("Invalid email provided.");
    if (!IsValidPhoneNumber(phoneNumber))
        throw std::invalid_argument("Invalid phone number provided.");

    FirstName = fName;
    MiddleName = mName;
    LastName = lName;
    Date = bDate;
    Email = email;
    PhoneNumber = phoneNumber;
}

// Геттеры
std::string Contact::GetFirstName() const { return FirstName; }
std::string Contact::GetMiddleName() const { return MiddleName; }
std::string Contact::GetLastName() const { return LastName; }
std::string Contact::GetDate() const { return Date; }
std::string Contact::GetEmail() const { return Email; }
std::string Contact::GetPhoneNumber() const { return PhoneNumber; }

// Сеттеры с проверкой корректности
void Contact::SetFirstName(const std::string &fName) {
    if (!IsValidName(fName))
        throw std::invalid_argument("First name is invalid.");
    FirstName = fName;
}

void Contact::SetMiddleName(const std::string &mName) {
    if (!IsValidName(mName))
        throw std::invalid_argument("Middle name is invalid.");
    MiddleName = mName;
}

void Contact::SetLastName(const std::string &lName) {
    if (!IsValidName(lName))
        throw std::invalid_argument("Last name is invalid.");
    LastName = lName;
}

void Contact::SetDate(const std::string &bDate) {
    if (!IsValidDate(bDate))
        throw std::invalid_argument("Date is invalid.");
    Date = bDate;
}

void Contact::SetEmail(const std::string &email) {
    if (!IsValidEmail(email))
        throw std::invalid_argument("Email is invalid.");
    Email = email;
}

void Contact::SetPhoneNumber(const std::string &phoneNumber) {
    if (!IsValidPhoneNumber(phoneNumber))
        throw std::invalid_argument("Phone number is invalid.");
    PhoneNumber = phoneNumber;
}

// Возвращает все поля контакта в виде вектора строк
std::vector<std::string> Contact::GetAllFields() const {
    return { FirstName, MiddleName, LastName, Date, Email, PhoneNumber };
}

// Вывод информации о контакте
void Contact::PrintContact() const {
    std::cout << "Contact: " << LastName << " " << FirstName << " " << MiddleName
              << ", Date of birth: " << Date
              << ", Phone: " << PhoneNumber
              << ", Email: " << Email << std::endl;
}

// Проверка корректности имени
bool Contact::IsValidName(const std::string &name) const {
    std::string cleaned = std::regex_replace(name, kSpaceTrim, "");
    return std::regex_match(cleaned, kNamePattern);
}

// Проверка корректности даты
bool Contact::IsValidDate(const std::string &bDate) const {
    if (!std::regex_match(bDate, kDatePattern))
        return false;

    int day = std::stoi(bDate.substr(0, 2));
    int month = std::stoi(bDate.substr(3, 2));
    int year = std::stoi(bDate.substr(6, 4));

    if (month < 1 || month > 12)
        return false;

    bool leapYear = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
    std::vector<int> daysInMonth = { 31, 28 + static_cast<int>(leapYear), 31, 30, 31, 30,
                                    31, 31, 30, 31, 30, 31 };
    if (day < 1 || day > daysInMonth[month - 1])
        return false;

    std::time_t nowTime = std::time(nullptr);
    std::tm *current = std::localtime(&nowTime);
    int currYear = current->tm_year + 1900;
    int currMonth = current->tm_mon + 1;
    int currDay = current->tm_mday;

    if (year > currYear ||
        (year == currYear && month > currMonth) ||
        (year == currYear && month == currMonth && day > currDay))
        return false;

    return true;
}

// Проверка корректности email
bool Contact::IsValidEmail(const std::string &email) const {
    std::string noSpaces = std::regex_replace(email, kAllSpaces, "");
    return std::regex_match(noSpaces, kEmailPattern);
}

// Проверка корректности номера телефона
bool Contact::IsValidPhoneNumber(const std::string &phoneNumber) const {
    std::string compact = std::regex_replace(phoneNumber, kAllSpaces, "");
    return std::regex_match(compact, kPhonePattern);
}
