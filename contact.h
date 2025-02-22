#ifndef CONTACT_H
#define CONTACT_H
#include <vector>
#include <string>

class Contact {
public:
    // Конструкторы
    Contact();
    Contact(const std::string &fName, const std::string &mName,
            const std::string &lName, const std::string &bDate,
            const std::string &email, const std::string &phoneNumber);

    // Геттеры
    std::string GetFirstName() const;
    std::string GetMiddleName() const;
    std::string GetLastName() const;
    std::string GetDate() const;
    std::string GetEmail() const;
    std::string GetPhoneNumber() const;

    // Сеттеры
    void SetFirstName(const std::string &fName);
    void SetMiddleName(const std::string &mName);
    void SetLastName(const std::string &lName);
    void SetDate(const std::string &bDate);
    void SetEmail(const std::string &email);
    void SetPhoneNumber(const std::string &phoneNumber);

    // Метод для получения всех полей
    std::vector<std::string> GetAllFields() const;

    // Метод для печати контакта (опционально)
    void PrintContact() const;

private:
    // Проверочные методы
    bool IsValidName(const std::string &name) const;
    bool IsValidDate(const std::string &bDate) const;
    bool IsValidEmail(const std::string &email) const;
    bool IsValidPhoneNumber(const std::string &phoneNumber) const;

    // Поля контакта
    std::string FirstName;
    std::string MiddleName;
    std::string LastName;
    std::string Date;
    std::string Email;
    std::string PhoneNumber;
};

#endif // CONTACT_H
