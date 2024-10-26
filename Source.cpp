#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

map<string, string> users = { {"miroslav", "123qwe"}, {"igor", "qwe123"}, {"misha", "q1w2e3"} };

class Login
{
    string login, password;
public:
    string get_login() { return login; }
    bool log_in() {
        cout << "enter login: ";
        cin >> login;
        cout << "enter password: ";
        cin >> password;
        if (users.find(login) != users.end() && users[login] == password) {
            cout << "login successful\n";
            return true;
        }
        else {
            cout << "invalid login or password\n";
            return false;
        }
    }
};

class User
{
    struct Dz
    {
        string predmet, info, dedline;
    };
    struct Otziv
    {
        string predmet, teacher, info, date;
    };
    string full_name, grupa;
    int monetki, kristaliki, medalki;
    int v_grupe, v_potoke;
    int ser_bal, vidviduvan;
    vector<Dz>dz;
    vector<Otziv>otziv;
    vector<string>nagorodi;
public:
    void display_info() {
        cout << "full name: " << full_name << "\n";
        cout << "group: " << grupa << "\n";
        cout << "monetki: " << monetki << ", kristaliki: " << kristaliki << ", medalki: " << medalki << "\n";
        cout << "rank in group: " << v_grupe << ", rank in potok: " << v_potoke << "\n";
        cout << "ser_bal score: " << ser_bal << "\nvidviduvan: " << vidviduvan << "%\n";
    }
    void display_dz() {
        cout << "\ndz:\n\n";
        for (auto it : dz) {
            cout << "predmet: " << it.predmet << "\ninfo: " << it.info << "\ndedline: " << it.dedline << "\n\n";
        }
    }
    void display_otzivi() {
        cout << "\notzivi:\n\n";
        for (auto it : otziv) {
            cout << "predmet: " << it.predmet << ", teacher: " << it.teacher << "\ninfo: " << it.info << ", date: " << it.date << "\n\n";
        }
    }
    void display_nagorodi() {
        cout << "\nnagorodi:\n\n";
        for (auto it : nagorodi) {
            cout << "nagoroda: " << it << "\n\n";
        }
    }

    void load_from_file(string filename) {
        ifstream file(filename);
        if (!file) {
            cout << "file not found: " << filename << "\n";
            return;
        }
        string line;
        while (getline(file, line)) { // chek README.md in git
            istringstream iss(line);
            string key;
            if (getline(iss, key, ':')) {
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
                    while (getline(iss, predmet, ',')) {
                        getline(iss, info, ',');
                        getline(iss, dedline, ';');
                        dz.push_back({ predmet, info, dedline });
                    }
                }
                else if (key == "otziv") {
                    string predmet, teacher, info, date;
                    while (getline(iss, predmet, ',')) {
                        getline(iss, teacher, ',');
                        getline(iss, info, ',');
                        getline(iss, date, ';');
                        otziv.push_back({ predmet, teacher, info, date });
                    }
                }
                else if (key == "nagorodi") {
                    string nagoroda;
                    while (getline(iss, nagoroda, ',')) {
                        nagorodi.push_back(nagoroda);
                    }
                }
            }
        }
    }
};

void MyStat(User& u1) {
    int ch = -1;
    for (int i = 0; i < 100; i++)
    {
        cout << endl;
    }
    u1.display_info();
    while (ch != 0) {
        cout << "\n\n\n1. main\n";
        cout << "2. dz\n";
        cout << "3. otzivi\n";
        cout << "4. nagorodi\n";
        cout << "5. oplata\n";
        cout << "6. news\n";
        cout << "7. contacts\n";
        cout << "0. exit\n";
        cout << "choose: ";
        cin >> ch;
        for (int i = 0; i < 100; i++)
        {
            cout << endl;
        }
        cout << "--- MyStat ---\n";
        switch (ch) {
        case 1:
            u1.display_info();
            break;
        case 2:
            u1.display_dz();
            break;
        case 3:
            u1.display_otzivi();
            break;
        case 4:
            u1.display_nagorodi();
            break;
        case 5: {
            cout << "oplata\ncard: 123456789\n";
            break;
        }
        case 6: {
            cout << "news:\n\n";
            cout << "Autumn camp in fabulous Japan! Updated program!\n\n";
            cout << "Free consultations";
            break;
        }
        case 7: {
            cout << "RECEIVING PART: +380123456789\n";
            cout << "EDUCATIONAL PART: +380123456789\n";
            cout << "ECONOMISTS: +380123456789";
            break;
        }
        case 0:
            cout << "exit";
            break;
        default:
            cout << "invalid choice\n";
        }
    }
}

int main() {
    Login l1;
    while (true)
    {
        if (l1.log_in()) {
            User u1;
            u1.load_from_file(l1.get_login() + ".txt");
            MyStat(u1);
            break;
        }
        else {
            cout << "access denied.\n";
        }
    }
}