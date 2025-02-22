#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
private:
    std::string FirstName;
    std::string MiddleName;
    std::string LastName;
    std::string Date;
    std::string Email;
    std::string PhoneNumber;


public:
    Contact();
    Contact(const std::string &firstName, const std::string &mName,
            const std::string &lastName, const std::string &bDate,
            const std::string &email, const std::string &phoneNumber);
    
    //Getters
    std::string GetFirstName() const;
    std::string GetMiddleName() const;
    std::string GetLastName() const;
    std::string GetDate() const;
    std::string GetEmail() const;
    std::string GetPhoneNumber() const;
    
    //Setters
    void SetFirstName(const std::string &fName);
    void SetMiddleName(const std::string &mName);
    void SetLastName(const std::string &lName);
    void SetDate(const std::string &bDate);
    void SetEmail(const std::string &email);
    void SetPhoneNumber(const std::string &phoneNumber);
    
    //Static methods of validation
    static bool IsValidName(const std::string &name);
    static bool IsValidDate(const std::string &date);
    static bool IsValidEmail(const std::string &email);
    static bool IsValidPhoneNumber(const std::string &phoneNumber);

    void PrintContact() const;
};

#endif // CONTACT_H
