#include<iostream>
#include<string>
#include<ctime>

using namespace std;

const string names[30] = { "Данил", "Денис", "Александр", "Вероника", "Ева", "Мирослава", "Виктория", "Анастасия", "Полина", "Владислава", "Алиса", "Милана", "Варвара", "Дарья", "Василиса", "Екатерина", "Александра", "Ксения", "Арина", "Елизавета", "Валерия", "Есения", "Елена", "Ольга", "Наталья", "Юлия", "Надежда", "Ирина", "Татьяна", "Мария" };
const string patronymics[30] = { "Александрович", "Андреевич", "Антоновна", "Сергеевна", "Иосифовна", "Георгиевна", "Борисовна", "Владиславовна", "Дмитриевна", "Никитична","Даниловна", "Артемовна", "Александровна", "Валерьевна", "Ильинична", "Григорьевна", "Артуровна", "Денисовна", "Алексеевна", "Макаровна", "Марковна", "Кирилловна", "Михайловна", "Константиновна", "Николаевна", "Германовна", "Иннокентьевна", "Богдановна", "Станиславовна", "Васильевна" };
const string surnames[30] = { "Мишарин", "Батраков", "Власова","Маслова","Исакова","Тихонова","Аксёнова","Гаврилова","Родионова","Котова","Горбунова","Кудряшова","Быкова","Зуева","Третьякова","Савельева","Панова","Рыбакова","Суворова","Абрамова","Воронова","Мухина","Архипова","Трофимова","Мартынова","Емельянова","Горшкова","Чернова","Овчинникова","Селезнёва" };
const string IDs[30] = { "5717","5321","2323","8321","3232","9999","9210","0105","6521","8891","1118","5617","9596","3490","9085","7254","7152","2015","8047","0001","3281","2131","8328","3727","2814","9348","2388","4211","3284","5521" };
const string dates[30] = { "12.12.2011","18.05.1030","09.01.2000","21.03.2003","19.10.2010","23.09.2009","24.10.2010","25.11.2011","26.12.2012","27.01.1988","28.02.1967","29.04.1999","30.05.1867","31.12.1999","01.06.1976","02.07.1980","03.08.1982","04.09.1955","05.10.1948","06.11.2014","16.05.1977","29.06.2004","19.02.2001","09.11.1996","27.03.2002","30.10.2000","27.08.2022","28.02.2019","29.10.1932","30.09.2014" };

struct Person {
    Person() : name(""), passport(""), birthday("") {}
    Person(string n, string p, string b) : name(n), passport(p), birthday(b) {}

    string name;
    string passport;
    string birthday;
};

class HashTable {
private:
    Person* table;
    int size;
    int collisions;

public:
    HashTable(int s) : size(s), collisions(0) {
        table = new Person[size];
    }

    ~HashTable() {
        delete[] table;
    }

    int getCollisions() const { return collisions; }

    int hashFunction(const string& passport) const {
        int hash = 0;
        for (char c : passport) {
            hash = (hash * 31 + c) % size;
        }
        return hash;
    }

    void insert(const Person& person) {
        int index = hashFunction(person.passport);
        int originalIndex = index;

        while (true) {
            if (table[index].passport.empty()) {
                table[index] = person;
                return;
            }

            if (table[index].passport == person.passport) {
                // Обновляем существующую запись
                table[index] = person;
                return;
            }

            index = (index + 1) % size;
            collisions++;

            if (index == originalIndex) {
                throw runtime_error("Hash table is full");
            }
        }
    }

    Person* search(const string& passport) {
        int index = hashFunction(passport);
        int originalIndex = index;

        while (true) {
            if (table[index].passport == passport) {
                return &table[index];
            }

            if (table[index].passport.empty()) {
                return nullptr;
            }

            index = (index + 1) % size;

            if (index == originalIndex) {
                return nullptr;
            }
        }
    }

    void display() const {
        for (int i = 0; i < size; ++i) {
            if (!table[i].passport.empty()) {
                cout << "Index " << i << ":\n";
                cout << "  Name: " << table[i].name << "\n";
                cout << "  Passport: " << table[i].passport << "\n";
                cout << "  Birthday: " << table[i].birthday << "\n\n";
            }
        }
    }
};

Person generateRandomPerson() {
    int index = rand() % 30;
    string name = surnames[index] + " " + names[index] + " " + patronymics[index];
    return Person(name, IDs[index], dates[index]);
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "Russian");

    int tableSize;
    cout << "Введите размер хеш-таблицы: ";
    cin >> tableSize;

    HashTable ht(tableSize);

    // Заполняем таблицу случайными людьми
    for (int i = 0; i < tableSize; ++i) {
        ht.insert(generateRandomPerson());
    }

    // Выводим содержимое таблицы
    cout << "\nСодержимое хеш-таблицы:\n";
    ht.display();

    // Поиск по номеру паспорта
    string searchPassport;
    cout << "\nВведите номер паспорта для поиска: ";
    cin >> searchPassport;

    Person* found = ht.search(searchPassport);
    if (found) {
        cout << "\nНайден человек:\n";
        cout << "  Name: " << found->name << "\n";
        cout << "  Passport: " << found->passport << "\n";
        cout << "  Birthday: " << found->birthday << "\n";
    }
    else {
        cout << "\nЧеловек с паспортом " << searchPassport << " не найден.\n";
    }

    cout << "\nКоличество коллизий: " << ht.getCollisions() << endl;

    return 0;
}