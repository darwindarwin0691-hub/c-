#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Employee {
protected:
    string id, name;
    double basic;

public:
    Employee(string i, string n, double b) : id(i), name(n), basic(b) {}
    virtual double calculateSalary() = 0;
    string getID() { return id; }
    virtual void slip() = 0;
    virtual ~Employee() {}
};

class Manager : public Employee {
public:
    Manager(string i, string n, double b) : Employee(i, n, b) {}

    double calculateSalary() override {
        double bonus = (basic > 50000) ? 5000 : 0;
        return basic + basic * 0.20 + bonus;
    }

    void slip() override {
        cout << name << " (Manager) - Basic: " << fixed << setprecision(2)
             << basic << " - Final Salary: " << calculateSalary() << endl;
    }
};

class Developer : public Employee {
    int exp;

public:
    Developer(string i, string n, double b, int e)
        : Employee(i, n, b), exp(e) {}

    double calculateSalary() override {
        double percent = 10 + 2 * exp;
        if (percent > 15) percent = 15;
        return basic + basic * percent / 100;
    }

    void slip() override {
        cout << name << " (Developer) - Basic: " << fixed << setprecision(2)
             << basic << " - Final Salary: " << calculateSalary() << endl;
    }
};

int main() {
    Employee* e[30];
    int count = 0, choice;

    do {
        cout << "\n===== Payroll Manager =====\n";
        cout << "1. Add  2. Salary Slip  3. Display All  4. Total Payroll  5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (count == 30) {
                cout << "Employee limit reached.\n";
                continue;
            }

            int type, exp;
            string id, name;
            double basic;

            cout << "Type (1-Manager, 2-Developer): ";
            cin >> type;
            cout << "Employee ID: ";
            cin >> id;
            cout << "Name: ";
            cin >> name;
            cout << "Basic Salary: ";
            cin >> basic;

            bool exists = false;
            for (int i = 0; i < count; i++)
                if (e[i]->getID() == id) exists = true;

            if (exists) {
                cout << "Employee ID already exists\n";
                continue;
            }

            if (type == 1)
                e[count++] = new Manager(id, name, basic);
            else if (type == 2) {
                cout << "Experience (years): ";
                cin >> exp;
                e[count++] = new Developer(id, name, basic, exp);
            } else {
                cout << "Invalid employee type\n";
                continue;
            }

            cout << "Employee added.\n";
        }

        else if (choice == 2) {
            string id;
            bool found = false;

            cout << "Employee ID: ";
            cin >> id;

            for (int i = 0; i < count; i++) {
                if (e[i]->getID() == id) {
                    e[i]->slip();
                    found = true;
                    break;
                }
            }

            if (!found) cout << "Employee not found\n";
        }

        else if (choice == 3) {
            if (count == 0)
                cout << "No employees found.\n";
            else
                for (int i = 0; i < count; i++)
                    cout << e[i]->getID() << " - "
                         << fixed << setprecision(2)
                         << e[i]->calculateSalary() << endl;
        }

        else if (choice == 4) {
            double total = 0;

            for (int i = 0; i < count; i++)
                total += e[i]->calculateSalary();

            cout << "Total Payroll: " << fixed << setprecision(2)
                 << total << endl;
        }

        else if (choice == 5)
            cout << "Exiting...\n";

        else
            cout << "Invalid choice\n";

    } while (choice != 5);

    for (int i = 0; i < count; i++)
        delete e[i];

    return 0;
}
