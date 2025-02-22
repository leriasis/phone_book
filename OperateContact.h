#ifndef OPERATE_CONTACT_H
#define OPERATE_CONTACT_H

#include "Contact.h"
#include <functional>
#include <string>
#include <vector>

class OperateContact {
private:
    std::vector<Contact> ContactsList; // изменено с Contacts на ContactsList

public:
    void AddNewContact(const Contact &newContact); // изменено с AddContact на AddNewContact

    void DeleteContactByIndex(size_t idx); // изменено с RemoveContact на DeleteContactByIndex

    std::vector<Contact> FindContacts(const std::function<bool(const Contact &)> &searchCriteria) const; // изменено с SearchContacts на FindContacts

    Contact& GetContactByIndex(size_t idx); // изменено с GetContact на GetContactByIndex

    const std::vector<Contact>& GetAllStoredContacts() const; // изменено с GetAllContacts на GetAllStoredContacts

    void OrderContacts(const std::function<bool(const Contact &, const Contact &)> &comparisonFunction); // изменено с SortContacts на OrderContacts

    void LoadContactsFromFile(const std::string &filePath); // изменено с LoadFromFile на LoadContactsFromFile

    void SaveContactsToFile(const std::string &filePath) const; // изменено с SaveToFile на SaveContactsToFile
};

#endif // OPERATE_CONTACT_H


