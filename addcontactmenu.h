#ifndef ADDCONTACTMENU_H
#define ADDCONTACTMENU_H

#include <QDialog> // Для создания окон

#include "contact.h"

namespace Ui {
class AddContactMenu;
}

class AddContactMenu : public QDialog // Наследование от QDialog, то есть создание диалового окна
{
    Q_OBJECT

public:
    explicit AddContactMenu(QWidget *parent = nullptr); // Конструктор с блокировкой неявного преобразования
    ~AddContactMenu(); // Деструктор

    // Установка данных контакта (для редактирования)
    void SetContactData(const Contact &contact);

    // Получение данных контакта после редактирования/добавления
    Contact GetContactData() const;

private:
    Ui::AddContactMenu *ui; // Указатель на объект интерфейса, через QtDesigner
};

#endif // ADDCONTACTMENU_H
