#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// Хранение пользователей и их паролей
map<string, string> users = { {"miroslav", "123qwe"}, {"igor", "qwe123"}, {"misha", "q1w2e3"} };

// Класс для обработки логина
class Login
{
    string login, password; // Переменные для хранения логина и пароля
public:
    string get_login() { return login; } // Метод для получения логина

    // Метод для выполнения логина
    bool log_in() {
        cout << "enter login: ";
        cin >> login; // Запрашиваем логин у пользователя
        cout << "enter password: ";
        cin >> password; // Запрашиваем пароль у пользователя
        // Проверяем, существует ли пользователь и совпадает ли пароль
        if (users.find(login) != users.end() && users[login] == password) {
            cout << "login successful\n"; // Успешный вход
            return true;
        }
        else {
            cout << "invalid login or password\n"; // Ошибка входа
            return false;
        }
    }
};

// Класс для хранения и обработки информации о пользователе
class User
{
    // Структура для домашних заданий
    struct Dz
    {
        string predmet, info, dedline; // Предмет, информация и дедлайн
    };
    // Структура для отзывов
    struct Otziv
    {
        string predmet, teacher, info, date; // Предмет, учитель, информация и дата
    };
    // Переменные для хранения информации о пользователе
    string full_name, grupa;
    int monetki, kristaliki, medalki;
    int v_grupe, v_potoke;
    int ser_bal, vidviduvan;
    vector<Dz> dz; // Вектор домашних заданий
    vector<Otziv> otziv; // Вектор отзывов
    vector<string> nagorodi; // Вектор наград
public:
    // Метод для отображения информации о пользователе
    void display_info() {
        cout << "full name: " << full_name << "\n";
        cout << "group: " << grupa << "\n";
        cout << "monetki: " << monetki << ", kristaliki: " << kristaliki << ", medalki: " << medalki << "\n";
        cout << "rank in group: " << v_grupe << ", rank in potok: " << v_potoke << "\n";
        cout << "ser_bal score: " << ser_bal << "\nvidviduvan: " << vidviduvan << "%\n";
    }

    // Метод для отображения домашних заданий
    void display_dz() {
        cout << "\ndz:\n\n";
        for (auto it : dz) {
            cout << "predmet: " << it.predmet << "\ninfo: " << it.info << "\ndedline: " << it.dedline << "\n\n";
        }
    }

    // Метод для отображения отзывов
    void display_otzivi() {
        cout << "\notzivi:\n\n";
        for (auto it : otziv) {
            cout << "predmet: " << it.predmet << ", teacher: " << it.teacher << "\ninfo: " << it.info << ", date: " << it.date << "\n\n";
        }
    }

    // Метод для отображения наград
    void display_nagorodi() {
        cout << "\nnagorodi:\n\n";
        for (auto it : nagorodi) {
            cout << "nagoroda: " << it << "\n\n";
        }
    }

    // Метод для загрузки информации о пользователе из файла
    void load_from_file(string filename) { // chek README.md in git
        ifstream file(filename); // Открываем файл
        if (!file) {
            cout << "file not found: " << filename << "\n"; // Если файл не найден
            return;
        }
        string line;
        while (getline(file, line)) { // Читаем файл построчно
            istringstream iss(line); // Создаем поток для разбора строки
            string key;
            if (getline(iss, key, ':')) { // Считываем ключ (например, полное имя)
                // В зависимости от ключа считываем соответствующее значение
                if (key == "full_name") getline(iss, full_name);
                else if (key == "grupa") getline(iss, grupa);
                else if (key == "monetki") iss >> monetki;
                else if (key == "kristaliki") iss >> kristaliki;
                else if (key == "medalki") iss >> medalki;
                else if (key == "v_grupe") iss >> v_grupe;
                else if (key == "v_potoke") iss >> v_potoke;
                else if (key == "ser_bal") iss >> ser_bal;
                else if (key == "vidviduvan") iss >> vidviduvan;
                else if (key == "dz") {
                    string predmet, info, dedline;
                    // Считываем домашние задания
                    while (getline(iss, predmet, ',')) {
                        getline(iss, info, ',');
                        getline(iss, dedline, ';');
                        dz.push_back({ predmet, info, dedline });
                    }
                }
                else if (key == "otziv") {
                    string predmet, teacher, info, date;
                    // Считываем отзывы
                    while (getline(iss, predmet, ',')) {
                        getline(iss, teacher, ',');
                        getline(iss, info, ',');
                        getline(iss, date, ';');
                        otziv.push_back({ predmet, teacher, info, date });
                    }
                }
                else if (key == "nagorodi") {
                    string nagoroda;
                    // Считываем награды
                    while (getline(iss, nagoroda, ',')) {
                        nagorodi.push_back(nagoroda);
                    }
                }
            }
        }
    }
};

// Функция для отображения статистики пользователя
void MyStat(User& u1) {
    int ch = -1; // Переменная для выбора меню
    // Очищаем экран
    for (int i = 0; i < 100; i++)
    {
        cout << endl;
    }
    u1.display_info(); // Отображаем информацию о пользователе
    while (ch != 0) { // Пока не выбрана команда выхода
        cout << "\n\n\n1. main\n";
        cout << "2. dz\n";
        cout << "3. otzivi\n";
        cout << "4. nagorodi\n";
        cout << "5. oplata\n";
        cout << "6. news\n";
        cout << "7. contacts\n";
        cout << "0. exit\n";
        cout << "choose: ";
        cin >> ch; // Получаем выбор пользователя
        // Очищаем экран
        for (int i = 0; i < 100; i++)
        {
            cout << endl;
        }
        cout << "--- MyStat ---\n";
        switch (ch) {
        case 1:
            u1.display_info(); // Отображаем информацию о пользователе
            break;
        case 2:
            u1.display_dz(); // Отображаем домашние задания
            break;
        case 3:
            u1.display_otzivi(); // Отображаем отзывы
            break;
        case 4:
            u1.display_nagorodi(); // Отображаем награды
            break;
        case 5: {
            cout << "oplata\ncard: 123456789\n"; // Информация о платеже
            break;
        }
        case 6: {
            cout << "news:\n\n";
            cout << "Autumn camp in fabulous Japan! Updated program!\n\n"; // Новости
            cout << "Free consultations";
            break;
        }
        case 7: {
            cout << "RECEIVING PART: +380123456789\n"; // Контактная информация
            cout << "EDUCATIONAL PART: +380123456789\n";
            cout << "ECONOMISTS: +380123456789";
            break;
        }
        case 0:
            cout << "exit"; // Выход из меню
            break;
        default:
            cout << "invalid choice\n"; // Неверный выбор
        }
    }
}

int main() {
    Login l1; // Создаем объект для логина
    while (true) // Бесконечный цикл для входа
    {
        if (l1.log_in()) { // Пытаемся войти
            User u1; // Создаем объект пользователя
            u1.load_from_file(l1.get_login() + ".txt"); // Загружаем данные из файла
            MyStat(u1); // Отображаем статистику
            break; // Выходим из цикла после успешного входа
        }
        else {
            cout << "access denied.\n"; // Доступ запрещён
        }
    }
}