#include "Contact.h"
#include <iostream>
#include <regex>
#include <ctime>
#include <vector>
#include <stdexcept>

using namespace std;

//Regular expression
const regex NameRegex("^[A-Za-zА-Яа-яЁё][A-Za-zА-Яа-яЁё\\- ]*[A-Za-zА-Яа-яЁё]$");
const regex DateRegex("^\\d{2}-\\d{2}-\\d{4}$");
const regex EmailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
const regex PhoneRegex("^\\+?[0-9\\-\\(\\) ]{7,}$");
const regex CleanString("^\\s+|\\s+$");
const regex DeleteSpacesRegex("\\s+");

//Статические методы проверки
bool Contact::IsValidName(const string &name) {
    string trimmedName = regex_replace(name, CleanString, "");
    return regex_match(trimmedName, NameRegex);
}

bool Contact::IsValidDate(const string &bDate) {
    if (!regex_match(bDate, DateRegex)) {
        return false;
    }
    int day = stoi(bDate.substr(0, 2));
    int month = stoi(bDate.substr(3, 2));
    int year = stoi(bDate.substr(6, 4));
    if (month < 1 || month > 12) {
        return false;
    }

    // проверка на високосный год
    vector<int> DaysInMonth = {
        31, 28 + ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 1 : 0), 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    
    if (day < 1 || day > DaysInMonth[month - 1]) {
        return false;
    }

    time_t t = time(nullptr);
    tm *now = localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;
    if (year > currentYear ||
        (year == currentYear && month > currentMonth) ||
        (year == currentYear && month == currentMonth && day > currentDay)) {
        return false;
    }
    return true;
}

bool Contact::IsValidEmail(const string &email) {
    string trimmedEmail = regex_replace(email, DeleteSpacesRegex, "");
    return regex_match(trimmedEmail, EmailRegex);
}

bool Contact::IsValidPhoneNumber(const string &phoneNumber) {
    string trimmedPhone = regex_replace(phoneNumber, DeleteSpacesRegex, "");
    return regex_match(trimmedPhone, PhoneRegex);
}

// Constructors
Contact::Contact()
    : FirstName("NoFirstName"), MiddleName("NoMiddleName"),
      LastName("NoLastName"), Date("00-00-0000"),
      Email("noname@nomail.com"), PhoneNumber("+0000000000") {}

Contact::Contact(const string &fName, const string &mName,
                 const string &lName, const string &bDate,
                 const string &email, const string &phoneNumber) {
    if (!IsValidName(fName)) {
        throw invalid_argument("Incorrect first name");
    }
    if (!IsValidName(mName)) {
        throw invalid_argument("Incorrect middle name");
    }
    if (!IsValidName(lName)) {
        throw invalid_argument("Incorrect last name");
    }
    if (!IsValidDate(bDate)) {
        throw invalid_argument("Incorrect bDate");
    }
    if (!IsValidEmail(email)) {
        throw invalid_argument("Incorrect email");
    }
    if (!IsValidPhoneNumber(phoneNumber)) {
        throw invalid_argument("Incorrect phone number");
    }
    FirstName = fName;
    MiddleName = mName;
    LastName = lName;
    Date = bDate;
    Email = email;
    PhoneNumber = phoneNumber;
}

// геттеры
string Contact::GetFirstName() const { return FirstName; }
string Contact::GetMiddleName() const { return MiddleName; }
string Contact::GetLastName() const { return LastName; }
string Contact::GetDate() const { return Date; }
string Contact::GetEmail() const { return Email; }
string Contact::GetPhoneNumber() const { return PhoneNumber; }
// сеттеры
void Contact::SetFirstName(const string &fName) {
    if (!IsValidName(fName)) {
        throw invalid_argument("Некорректное имя.");
    }
    FirstName = fName;
}

void Contact::SetMiddleName(const string &mName) {
    if (!IsValidName(mName)) {
        throw invalid_argument("Некорректное отчество.");
    }
    MiddleName = mName;
}

void Contact::SetLastName(const string &lName) {
    if (!IsValidName(lName)) {
        throw invalid_argument("Некорректная фамилия.");
    }
    LastName = lName;
}

void Contact::SetDate(const string &bDate) {
    if (!IsValidDate(bDate)) {
        throw invalid_argument("Некорректная дата.");
    }
    Date = bDate;
}

void Contact::SetEmail(const string &email) {
    if (!IsValidEmail(email)) {
        throw invalid_argument("Некорректный email.");
    }
    Email = email;
}

void Contact::SetPhoneNumber(const string &phoneNumber) {
    if (!IsValidPhoneNumber(phoneNumber)) {
        throw invalid_argument("Некорректный номер телефона.");
    }
    PhoneNumber = phoneNumber;
}

// Output info about contact
void Contact::PrintContact() const {
    cout << "Контакт: " << LastName << " " << FirstName << " "
              << MiddleName << ", Дата рождения: " << Date
              << ", Номер телефона: " << PhoneNumber << ", Электронная почта: "
              << Email << "\n";
}
