#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

// Структура одной записи БД - студенческая группа
struct StudentGroup {
    std::string name;
    int year;
    char degree;
    std::string faculty;
    std::string headman;
    int students_count;
};

// Класс базы данных
class Database {
private:
    std::vector<StudentGroup> groups;

public:
    void loadFromFile();
    void saveToFile();
    void display();
    void addRecord();
    void removeRecord();
    void sortByName();
    void searchByName();
    void filterByYearRange();
    void task1_facultyByCount();
    void task2_splitByDegree();
};

void printMenu() {
    std::cout << "\n========== MENU ==========\n";
    std::cout << "1. Load DB from file\n";
    std::cout << "2. Display DB\n";
    std::cout << "3. Add record\n";
    std::cout << "4. Remove record (by number)\n";
    std::cout << "5. Save DB to file\n";
    std::cout << "6. Sort by name\n";
    std::cout << "7. Search by name\n";
    std::cout << "8. Filter by year range\n";
    std::cout << "9. Task 1: faculty groups sorted by count\n";
    std::cout << "10. Task 2: split into 3 DBs by degree\n";
    std::cout << "0. Exit\n";
    std::cout << "==========================\n";
    std::cout << "Choice: ";
}

int main() {
    Database db;
    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Bye!\n";
            return 0;
        }
        else if (choice == 1)  db.loadFromFile();
        else if (choice == 2)  db.display();
        else if (choice == 3)  db.addRecord();
        else if (choice == 4)  db.removeRecord();
        else if (choice == 5)  db.saveToFile();
        else if (choice == 6)  db.sortByName();
        else if (choice == 7)  db.searchByName();
        else if (choice == 8)  db.filterByYearRange();
        else if (choice == 9)  db.task1_facultyByCount();
        else if (choice == 10) db.task2_splitByDegree();
        else std::cout << "Unknown option\n";
    }
}

// Вывод таблицы
void Database::display() {
    if (groups.size() == 0) {
        std::cout << "Database is empty.\n";
        return;
    }

    std::cout << "\n";
    std::cout << "#  | Name        | Year | D | Faculty            | Headman         | Count\n";
    std::cout << "---+-------------+------+---+--------------------+-----------------+------\n";

    for (int i = 0; i < (int)groups.size(); i++) {
        std::cout << std::left
                  << std::setw(2) << (i + 1) << " | "
                  << std::setw(11) << groups[i].name << " | "
                  << std::setw(4)  << groups[i].year << " | "
                  << groups[i].degree << " | "
                  << std::setw(18) << groups[i].faculty << " | "
                  << std::setw(15) << groups[i].headman << " | "
                  << groups[i].students_count << "\n";
    }
    std::cout << "Total: " << groups.size() << " records\n";
}

// Добавление новой записи
void Database::addRecord() {
    StudentGroup g;

    std::cin.ignore(1000, '\n');

    std::cout << "Name: ";
    std::getline(std::cin, g.name);

    std::cout << "Year: ";
    std::cin >> g.year;

    std::cout << "Degree (B=bachelor, S=specialist, M=master): ";
    std::cin >> g.degree;

    std::cin.ignore(1000, '\n');

    std::cout << "Faculty: ";
    std::getline(std::cin, g.faculty);

    std::cout << "Headman: ";
    std::getline(std::cin, g.headman);

    std::cout << "Students count: ";
    std::cin >> g.students_count;

    groups.push_back(g);
    std::cout << "Record added. Total: " << groups.size() << "\n";
}

// Удаление записи по номеру
void Database::removeRecord() {
    if (groups.size() == 0) {
        std::cout << "Database is empty.\n";
        return;
    }

    std::cout << "Enter record number to remove (1 to " << groups.size() << "): ";
    int num;
    std::cin >> num;

    if (num < 1 || num > (int)groups.size()) {
        std::cout << "Invalid number.\n";
        return;
    }

    groups.erase(groups.begin() + num - 1);
    std::cout << "Record removed. Total: " << groups.size() << "\n";
}

// Сортировка по имени (пузырьковая)
void Database::sortByName() {
    if (groups.size() == 0) {
        std::cout << "Database is empty.\n";
        return;
    }

    int n = groups.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (groups[j].name > groups[j + 1].name) {
                StudentGroup temp = groups[j];
                groups[j] = groups[j + 1];
                groups[j + 1] = temp;
            }
        }
    }

    std::cout << "Sorted by name.\n";
}

// Поиск по имени
void Database::searchByName() {
    if (groups.size() == 0) {
        std::cout << "Database is empty.\n";
        return;
    }

    std::cin.ignore(1000, '\n');
    std::cout << "Enter name to search: ";
    std::string query;
    std::getline(std::cin, query);

    bool found = false;
    for (int i = 0; i < (int)groups.size(); i++) {
        if (groups[i].name == query) {
            std::cout << "\nFound at #" << (i + 1) << ":\n";
            std::cout << "  Name:    " << groups[i].name << "\n";
            std::cout << "  Year:    " << groups[i].year << "\n";
            std::cout << "  Degree:  " << groups[i].degree << "\n";
            std::cout << "  Faculty: " << groups[i].faculty << "\n";
            std::cout << "  Headman: " << groups[i].headman << "\n";
            std::cout << "  Count:   " << groups[i].students_count << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No records with name '" << query << "'.\n";
    }
}

// Выборка по диапазону лет
void Database::filterByYearRange() {
    if (groups.size() == 0) {
        std::cout << "Database is empty.\n";
        return;
    }

    int yearFrom, yearTo;
    std::cout << "Year from: ";
    std::cin >> yearFrom;
    std::cout << "Year to: ";
    std::cin >> yearTo;

    if (yearFrom > yearTo) {
        int tmp = yearFrom;
        yearFrom = yearTo;
        yearTo = tmp;
    }

    std::cout << "\nGroups with year in [" << yearFrom << ", " << yearTo << "]:\n";
    std::cout << "#  | Name        | Year | D | Faculty            | Headman         | Count\n";
    std::cout << "---+-------------+------+---+--------------------+-----------------+------\n";

    int counter = 0;
    for (int i = 0; i < (int)groups.size(); i++) {
        if (groups[i].year >= yearFrom && groups[i].year <= yearTo) {
            counter++;
            std::cout << std::left
                      << std::setw(2) << counter << " | "
                      << std::setw(11) << groups[i].name << " | "
                      << std::setw(4)  << groups[i].year << " | "
                      << groups[i].degree << " | "
                      << std::setw(18) << groups[i].faculty << " | "
                      << std::setw(15) << groups[i].headman << " | "
                      << groups[i].students_count << "\n";
        }
    }

    if (counter == 0) {
        std::cout << "No matching records.\n";
    } else {
        std::cout << "Found: " << counter << " records.\n";
    }
}

// Задача 1: группы факультета, отсортированные по численности
void Database::task1_facultyByCount() {
    if (groups.size() == 0) {
        std::cout << "Database is empty.\n";
        return;
    }

    std::cin.ignore(1000, '\n');
    std::cout << "Enter faculty name: ";
    std::string targetFaculty;
    std::getline(std::cin, targetFaculty);

    // Копируем подходящие в отдельный вектор
    std::vector<StudentGroup> filtered;
    for (int i = 0; i < (int)groups.size(); i++) {
        if (groups[i].faculty == targetFaculty) {
            filtered.push_back(groups[i]);
        }
    }

    if (filtered.size() == 0) {
        std::cout << "No groups found for faculty '" << targetFaculty << "'.\n";
        return;
    }

    // Сортировка пузырьком по численности
    int n = filtered.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (filtered[j].students_count > filtered[j + 1].students_count) {
                StudentGroup temp = filtered[j];
                filtered[j] = filtered[j + 1];
                filtered[j + 1] = temp;
            }
        }
    }

    std::cout << "\nGroups of faculty '" << targetFaculty
              << "' sorted by students count:\n";
    std::cout << "#  | Name        | Year | D | Faculty            | Headman         | Count\n";
    std::cout << "---+-------------+------+---+--------------------+-----------------+------\n";

    for (int i = 0; i < (int)filtered.size(); i++) {
        std::cout << std::left
                  << std::setw(2) << (i + 1) << " | "
                  << std::setw(11) << filtered[i].name << " | "
                  << std::setw(4)  << filtered[i].year << " | "
                  << filtered[i].degree << " | "
                  << std::setw(18) << filtered[i].faculty << " | "
                  << std::setw(15) << filtered[i].headman << " | "
                  << filtered[i].students_count << "\n";
    }
    std::cout << "Found: " << filtered.size() << " groups.\n";
}

// Задача 2: разделить БД на 3 файла по уровню образования
void Database::task2_splitByDegree() {
    if (groups.size() == 0) {
        std::cout << "Database is empty.\n";
        return;
    }

    std::ofstream outB("bachelor.txt");
    std::ofstream outS("specialist.txt");
    std::ofstream outM("master.txt");

    if (!outB.is_open() || !outS.is_open() || !outM.is_open()) {
        std::cout << "Error: cannot open output files.\n";
        return;
    }

    int countB = 0;
    int countS = 0;
    int countM = 0;

    for (int i = 0; i < (int)groups.size(); i++) {
        if (groups[i].degree == 'B' || groups[i].degree == 'b') {
            outB << groups[i].name << ";"
                 << groups[i].year << ";"
                 << groups[i].degree << ";"
                 << groups[i].faculty << ";"
                 << groups[i].headman << ";"
                 << groups[i].students_count << "\n";
            countB++;
        }
        else if (groups[i].degree == 'S' || groups[i].degree == 's') {
            outS << groups[i].name << ";"
                 << groups[i].year << ";"
                 << groups[i].degree << ";"
                 << groups[i].faculty << ";"
                 << groups[i].headman << ";"
                 << groups[i].students_count << "\n";
            countS++;
        }
        else if (groups[i].degree == 'M' || groups[i].degree == 'm') {
            outM << groups[i].name << ";"
                 << groups[i].year << ";"
                 << groups[i].degree << ";"
                 << groups[i].faculty << ";"
                 << groups[i].headman << ";"
                 << groups[i].students_count << "\n";
            countM++;
        }
    }

    outB.close();
    outS.close();
    outM.close();

    groups.clear();

    std::cout << "Split complete:\n";
    std::cout << "  bachelor.txt:   " << countB << " records\n";
    std::cout << "  specialist.txt: " << countS << " records\n";
    std::cout << "  master.txt:     " << countM << " records\n";
    std::cout << "Original database cleared.\n";
}

// Сохранение БД в файл
void Database::saveToFile() {
    std::cout << "Enter filename to save (e.g. database.txt): ";
    std::string filename;
    std::cin >> filename;

    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cout << "Error: cannot open file '" << filename << "' for writing.\n";
        return;
    }

    for (int i = 0; i < (int)groups.size(); i++) {
        out << groups[i].name << ";"
            << groups[i].year << ";"
            << groups[i].degree << ";"
            << groups[i].faculty << ";"
            << groups[i].headman << ";"
            << groups[i].students_count << "\n";
    }

    out.close();
    std::cout << "Saved " << groups.size() << " records to '" << filename << "'.\n";
}

// Загрузка БД из файла
void Database::loadFromFile() {
    std::cout << "Enter filename to load (e.g. database.txt): ";
    std::string filename;
    std::cin >> filename;

    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cout << "Error: cannot open file '" << filename << "'.\n";
        return;
    }

    groups.clear();
    std::string line;

    while (std::getline(in, line)) {
        if (line.size() == 0) continue;

        std::stringstream ss(line);
        StudentGroup g;
        std::string field;

        std::getline(ss, g.name, ';');

        std::getline(ss, field, ';');
        g.year = std::stoi(field);

        std::getline(ss, field, ';');
        if (field.size() == 0) g.degree = '?';
        else g.degree = field[0];

        std::getline(ss, g.faculty, ';');
        std::getline(ss, g.headman, ';');

        std::getline(ss, field, ';');
        g.students_count = std::stoi(field);

        groups.push_back(g);
    }

    in.close();
    std::cout << "Loaded " << groups.size() << " records from '" << filename << "'.\n";
}