#include "OperateContact.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Helper function to remove leading/trailing spaces
std::string CleanString(const std::string &input) {
    size_t start = input.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = input.find_last_not_of(" \t\n\r");
    return input.substr(start, (end - start + 1));
}

void OperateContact::AddNewContact(const Contact &newContact) {
    ContactsList.push_back(newContact);
}

void OperateContact::DeleteContactByIndex(size_t idx) {
    if (idx < ContactsList.size()) {
        ContactsList.erase(ContactsList.begin() + idx);
    } else {
        throw std::out_of_range("Invalid index");
    }
}

std::vector<Contact> OperateContact::FindContacts(const std::function<bool(const Contact &)> &searchCriteria) const {
    std::vector<Contact> matchedContacts;
    for (const auto &contact : ContactsList) {
        if (searchCriteria(contact)) {
            matchedContacts.push_back(contact);
        }
    }
    return matchedContacts;
}

Contact& OperateContact::GetContactByIndex(size_t idx) {
    if (idx >= ContactsList.size()) {
        throw std::out_of_range("Index out of range");
    }
    return ContactsList[idx];
}

const std::vector<Contact>& OperateContact::GetAllStoredContacts() const {
    return ContactsList;
}

void OperateContact::OrderContacts(const std::function<bool(const Contact &, const Contact &)> &comparisonFunction) {
    std::sort(ContactsList.begin(), ContactsList.end(), comparisonFunction);
}

void OperateContact::LoadContactsFromFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for reading");
    }

    ContactsList.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::string fName, mName, lName, bDate, email, phone;

        // Parse contact fields: firstName, middleName, lastName, birthDate, email, phone
        std::getline(lineStream, fName, ',');
        std::getline(lineStream, mName, ',');
        std::getline(lineStream, lName, ',');
        std::getline(lineStream, bDate, ',');
        std::getline(lineStream, email, ',');
        std::getline(lineStream, phone, ',');

        // Clean up any excess spaces
        fName = CleanString(fName);
        mName = CleanString(mName);
        lName = CleanString(lName);
        bDate = CleanString(bDate);
        email = CleanString(email);
        phone = CleanString(phone);

        try {
            Contact contact(fName, mName, lName, bDate, email, phone);
            ContactsList.push_back(contact);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error loading contact: " << e.what() << "\n";
        }
    }
}

void OperateContact::SaveContactsToFile(const std::string &filePath) const {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file for writing");
    }

    for (const auto &contact : ContactsList) {
        file << contact.GetFirstName() << ","
             << contact.GetMiddleName() << ","
             << contact.GetLastName() << ","
             << contact.GetDate() << ","
             << contact.GetEmail() << ","
             << contact.GetPhoneNumber() << "\n";
    }
}
