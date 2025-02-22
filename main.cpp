#include <clocale>
#include <iostream>
#include <string>
#include "OperateContact.h"
#include <limits>

using namespace std;

// функции для изменений данных о контакте
void AddNewContact(OperateContact &operate);
void ModifyContact(OperateContact &operate);
void DisplayAllContacts(OperateContact &operate);
void DeleteContact(OperateContact &operate);
void EditContactDetails(Contact &contact);


// вспомогательные функции
bool GetUserInput(const string &prompt, string &input) {
    cout << prompt;
    getline(cin, input);
    if (input == "quit") {
        return false;
    }
    return true;
}

template <typename ValidationFunc>
bool GetValidatedUserInput(const string &prompt, string &input,
                            ValidationFunc validateFunc, const string &errorMessage) {
    while (true) {
        if (!GetUserInput(prompt, input)) {
            return false;
        }
        if (validateFunc(input)) {
            return true;
        } else {
            cout << errorMessage << " Пожалуйста, попробуйте снова или введите 'quit' для отмены.\n";
        }
    }
}

int main() {
    OperateContact operateContact;

    // загрузка из файла
    try {
        operateContact.LoadContactsFromFile("contacts.csv");
        cout << "Контакты успешно загружены из файла.\n";
    } catch (const exception &e) {
        cout << "Ошибка загрузки контактов: " << e.what() << "\n";
    }

    while (true) {
        cout << "\nВыберите действие:\n";
        cout << "1. Добавить новый контакт\n";
        cout << "2. Изменить контакт\n";
        cout << "3. Показать все контакты\n";
        cout << "4. Удалить контакт\n";
        cout << "5. Выйти\n";
        cout << "Ваш выбор: ";

        int option;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Пожалуйста, введите число.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (option == 5) {
            break;
        }

        switch (option) {
            case 1:
                AddNewContact(operateContact);
                break;
            case 2:
                ModifyContact(operateContact);
                break;
            case 3:
                DisplayAllContacts(operateContact);
                break;
            case 4:
                DeleteContact(operateContact);
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
                break;
        }
    }

    // сохранение контактов в файл
    try {
        operateContact.SaveContactsToFile("contacts.csv");
        cout << "Контакты успешно сохранены в файл.\n";
    } catch (const exception &e) {
        cout << "Ошибка сохранения контактов: " << e.what() << "\n";
    }

    cout << "Программа завершена.\n";
    return 0;
}

void AddNewContact(OperateContact& operate) {
    string firstName, middleName, lastName, birthDate, emailAddress, phone;

    cout << "\nДобавление нового контакта:\n";

    if (!GetValidatedUserInput("Имя: ", firstName, Contact::IsValidName, "Некорректное имя.")) return;
    if (!GetValidatedUserInput("Отчество: ", middleName, Contact::IsValidName, "Некорректное отчество.")) return;
    if (!GetValidatedUserInput("Фамилия: ", lastName, Contact::IsValidName, "Некорректная фамилия.")) return;
    if (!GetValidatedUserInput("Дата рождения (дд-мм-гггг): ", birthDate, Contact::IsValidDate, "Некорректная дата.")) return;
    if (!GetValidatedUserInput("Email: ", emailAddress, Contact::IsValidEmail, "Некорректный email.")) return;
    if (!GetValidatedUserInput("Номер телефона: ", phone, Contact::IsValidPhoneNumber, "Некорректный номер телефона.")) return;

    try {
        Contact newContact(firstName, middleName, lastName, birthDate, emailAddress, phone);
        operate.AddNewContact(newContact);
        cout << "Контакт успешно добавлен.\n";
    }
    catch (const exception& e) {
        cout << "Ошибка создания контакта: " << e.what() << "\n";
        cout << "Попробуйте снова.\n";
    }
}

void ModifyContact(OperateContact& operate) {
    cout << "\nРедактирование контакта:\n";
    const auto& contacts = operate.GetAllStoredContacts();

    if (contacts.empty()) {
        cout << "Контакты отсутствуют.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". ";
        contacts[i].PrintContact();
    }

    size_t contactIndex;
    while (true) {
        cout << "Введите номер контакта для редактирования (или 0 для отмены): ";
        if (!(cin >> contactIndex)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Пожалуйста, введите число.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (contactIndex == 0) {
            cout << "Редактирование отменено.\n";
            return;
        }
        else if (contactIndex > contacts.size()) {
            cout << "Неверный номер. Попробуйте снова.\n";
            continue;
        }
        else {
            contactIndex -= 1;
            break;
        }
    }
}

void DisplayAllContacts(OperateContact& operate) {
    const auto& contacts = operate.GetAllStoredContacts();
    if (contacts.empty()) {
        cout << "Список контактов пуст.\n";
    }
    else {
        cout << "\nСписок всех контактов:\n";
        for (const auto& contact : contacts) {
            contact.PrintContact();
        }
    }
}

void DeleteContact(OperateContact& operate) {
    cout << "\nУдаление контакта:\n";
    const auto& contacts = operate.GetAllStoredContacts();

    if (contacts.empty()) {
        cout << "Контакты отсутствуют.\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        cout << i + 1 << ". ";
        contacts[i].PrintContact();
    }

    size_t contactIndex;
    while (true) {
        cout << "Введите номер контакта для удаления (или 0 для отмены): ";
        if (!(cin >> contactIndex)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод. Пожалуйста, введите число.\n";
            continue;
        }

        if (contactIndex == 0) {
            cout << "Удаление отменено.\n";
            return;
        }
        else if (contactIndex > contacts.size()) {
            cout << "Неверный номер. Попробуйте снова.\n";
            continue;
        }
        else {
            contactIndex -= 1;
            break;
        }
    }

    try {
        operate.DeleteContactByIndex(contactIndex);
        cout << "Контакт успешно удалён.\n";
    }
    catch (const exception& e) {
        cout << "Ошибка удаления контакта: " << e.what() << "\n";
    }
}

void EditContactDetails(Contact& contact) {
    string firstName, middleName, lastName, birthDate, emailAddress, phone;

    cout << "\nРедактирование информации о контакте:\n";

    if (!GetValidatedUserInput("Имя: ", firstName, Contact::IsValidName, "Некорректное имя.")) return;
    if (!GetValidatedUserInput("Отчество: ", middleName, Contact::IsValidName, "Некорректное отчество.")) return;
    if (!GetValidatedUserInput("Фамилия: ", lastName, Contact::IsValidName, "Некорректная фамилия.")) return;
    if (!GetValidatedUserInput("Дата рождения (дд-мм-гггг): ", birthDate, Contact::IsValidDate, "Некорректная дата.")) return;
    if (!GetValidatedUserInput("Email: ", emailAddress, Contact::IsValidEmail, "Некорректный email.")) return;
    if (!GetValidatedUserInput("Номер телефона: ", phone, Contact::IsValidPhoneNumber, "Некорректный номер телефона.")) return;

    try {
        contact.SetFirstName(firstName);
        contact.SetMiddleName(middleName);
        contact.SetLastName(lastName);
        contact.SetDate(birthDate);
        contact.SetEmail(emailAddress);
        contact.SetPhoneNumber(phone);
        cout << "Данные контакта успешно обновлены.\n";
    }
    catch (const exception& e) {
        cout << "Ошибка редактирования контакта: " << e.what() << "\n";
    }
}