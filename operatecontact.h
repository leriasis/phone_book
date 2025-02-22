#ifndef OPERATECONTACT_H
#define OPERATECONTACT_H

#include "contact.h"

#include <vector>
#include <functional>


class OperateContact {
public:
    void AddContact(const Contact &contact);
    void RemoveContact(size_t index);
    void UpdateContact(size_t index, const Contact &contact);
    std::vector<Contact> SearchContacts(const std::function<bool(const Contact &)> &criteria) const;
    Contact GetContact(size_t index) const;
    const std::vector<Contact> &GetAllContacts() const;
    void SortContacts(const std::function<bool(const Contact &, const Contact &)> &comparator);
    void LoadFromFile(const std::string &filename);
    void SaveToFile(const std::string &filename) const;

private:
    std::vector<Contact> Contacts;
};

#endif // OPERATECONTACT_H
