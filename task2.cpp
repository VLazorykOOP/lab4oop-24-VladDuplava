 #include <iostream>
#include <string>
#include <vector>
using namespace std;

class DNSRecord {
private:
    vector<string> domains;  // Вектор для доменних імен
    vector<string> ips;      // Вектор для IP-адрес
    int size;                // Кількість записів
    int codeError = 0;       // Код помилки: 0 - все ок, 1 - домен не знайдений

public:
    DNSRecord() : size(0), codeError(0) {}  // Конструктор за замовчуванням, ініціалізуємо порожні вектори та код помилки

    // Ініціалізуємо вектори за кількістю записів
    void Init(int n) {
        size = n;
        domains.resize(n);  // Розширюємо вектор доменів
        ips.resize(n);      // Розширюємо вектор IP-адрес
    }

    // Додаємо новий запис (домен і відповідний йому IP)
    void Add(const string& domain, const string& ip) {
        domains.push_back(domain);  // Додаємо домен
        ips.push_back(ip);          // Додаємо IP
        size++;                     // Збільшуємо розмір записів
    }

    // Перевантаження операції індексації: шукаємо IP по домену
    string& operator[](const string& domain) {
        for (int i = 0; i < size; ++i) {
            if (domains[i] == domain) {
                codeError = 0;  // Якщо домен знайдений, помилка відсутня
                return ips[i];   // Повертаємо відповідний IP
            }
        }
        codeError = 1;  // Якщо домен не знайдений, ставимо помилку
        static string dummy = "0.0.0.0";  // Заглушка на випадок помилки (повертаємо "0.0.0.0")
        return dummy;    // Повертаємо заглушку
    }

    // Альтернативний доступ до IP за доменом через виклик функції
    string operator()(const string& domain) {
        return (*this)[domain];  // Використовуємо оператор[] для пошуку IP
    }

    // Функція для отримання коду помилки
    int getError() const { return codeError; }  // Повертає код помилки

    // Перевантаження операції введення: зчитуємо записи DNS з потоку
    friend istream& operator>>(istream& in, DNSRecord& dns) {
        int n;
        cout << "Скільки записів DNS ввести? ";
        in >> n;  // Вводимо кількість записів
        dns.Init(n);  // Ініціалізуємо вектори за розміром
        cout << "Введіть домен і IP:\n";
        for (int i = 0; i < n; ++i) {
            string dom, ip;
            in >> dom >> ip;  // Вводимо домен і IP
            dns.domains[i] = dom;  // Зберігаємо домен
            dns.ips[i] = ip;      // Зберігаємо IP
        }
        return in;  // Повертаємо потік
    }

    // Перевантаження операції виведення: виводимо всі записи DNS
    friend ostream& operator<<(ostream& out, const DNSRecord& dns) {
        out << "DNS записи:\n";
        for (int i = 0; i < dns.size; ++i) {
            out << dns.domains[i] << " => " << dns.ips[i] << endl;  // Виводимо кожен запис
        }
        return out;  // Повертаємо потік
    }
};

int main2() {
    DNSRecord dns;  // Створюємо об'єкт класу DNSRecord
    cin >> dns;  // Вводимо записи DNS
    cout << dns;  // Виводимо записи DNS

    // Шукаємо IP для домену google.com через оператор[]
    string ip = dns["google.com"];
    if (dns.getError()) {  // Якщо код помилки не 0 (не знайдений домен)
        cout << "Помилка: домен не знайдено\n";  // Виводимо повідомлення про помилку
    } else {
        cout << "IP google.com = " << ip << endl;  // Виводимо знайдений IP
    }

    // Альтернативний доступ через виклик функції
    cout << "Альтернативний доступ: " << dns("github.com") << endl;  // Виводимо IP для github.com

    return 0;
}
