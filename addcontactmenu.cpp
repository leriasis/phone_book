#include "addcontactmenu.h"
#include "ui_addcontactmenu.h"
#include <stdexcept> // для std::invalid_argument

AddContactMenu::AddContactMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddContactMenu)
{
    ui->setupUi(this);
}

AddContactMenu::~AddContactMenu()
{
    delete ui;
}

void AddContactMenu::SetContactData(const Contact &contact)
{
    // При установке данных в поля диалога мы можем не триммить,
    // так как данные из Contact уже должны быть валидированы и очищены,
    // либо приходить в корректном формате.
    ui->lineEditFirstName->setText(QString::fromStdString(contact.GetFirstName()));
    ui->lineEditMiddleName->setText(QString::fromStdString(contact.GetMiddleName()));
    ui->lineEditLastName->setText(QString::fromStdString(contact.GetLastName()));
    ui->lineEditDate->setText(QString::fromStdString(contact.GetDate()));
    ui->lineEditEmail->setText(QString::fromStdString(contact.GetEmail()));
    ui->lineEditPhoneNumber->setText(QString::fromStdString(contact.GetPhoneNumber()));
}

Contact AddContactMenu::GetContactData() const
{
    // Извлекаем текст из полей ввода и удаляем пробелы в начале и конце:
    QString fName = ui->lineEditFirstName->text().trimmed();
    QString mName = ui->lineEditMiddleName->text().trimmed();
    QString lName = ui->lineEditLastName->text().trimmed();
    QString bDate = ui->lineEditDate->text().trimmed();
    QString email = ui->lineEditEmail->text().trimmed();
    QString phoneNumber = ui->lineEditPhoneNumber->text().trimmed();

    Contact contact;
    try {
        // Передаем очищенные строки в Contact
        contact.SetFirstName(fName.toStdString());
        contact.SetMiddleName(mName.toStdString());
        contact.SetLastName(lName.toStdString());
        contact.SetDate(bDate.toStdString());
        contact.SetEmail(email.toStdString());
        contact.SetPhoneNumber(phoneNumber.toStdString());
    } catch (const std::invalid_argument &e) {
        // Если валидация в Contact выбросила исключение, пробрасываем дальше
        throw std::invalid_argument(QString::fromStdString(e.what()).toStdString());
    }

    return contact;
}
