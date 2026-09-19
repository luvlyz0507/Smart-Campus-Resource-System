#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include <iomanip>
#include <windows.h>

using namespace std;

struct Student {
    int id;
    string name;
    string departmentSection;
};

const int MAX_CAPACITY = 10;
const int ROWS = 4;
const int COLS = 4;
const int TABLE_WIDTH = 95;
const int LABEL_WIDTH = 25;
const int VALUE_WIDTH = 63;

  string departments[ROWS] = {
     "D1- IT Dept",
     "D2- Engineering",
     "D3- Business",
    "D4- Education"
};

int resourceMatrix[ROWS][COLS] = {
    {12, 3, 8, 5},
    {9, 2, 4, 10},
    {5, 6, 10, 2},
    {4, 8, 6, 3}
};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printBorder() {
    setColor(7);
    cout << "|" << string(TABLE_WIDTH - 2, '-') << "|" << endl;
}

void printCenteredTitle(const string& title, int color) {
    const int innerWidth = TABLE_WIDTH - 2;

    int leftSpace = (innerWidth - static_cast<int>(title.length())) / 2;
    int rightSpace = innerWidth - leftSpace - static_cast<int>(title.length());

    setColor(7);
    cout << "|";

    setColor(color);
    cout << string(leftSpace, ' ');
    cout << title;
    cout << string(rightSpace, ' ');

    setColor(7);
    cout << "|" << endl;
}

void printSeparator(const int widths[], int columns) {
    setColor(7);

    cout << "|";

    for (int i = 0; i < columns; i++) {
        cout << string(widths[i] + 2, '-');
        cout << "|";
    }

    cout << endl;
}

void printTableRow(const string& label, const string& value) {
    string displayValue = value;

    if (displayValue.length() > VALUE_WIDTH) {
        displayValue = displayValue.substr(0, VALUE_WIDTH);
    }

    setColor(7);

    cout << "| "
         << left << setw(LABEL_WIDTH) << label
         << " | "
         << left << setw(VALUE_WIDTH) << displayValue
         << " |"
         << endl;
}

string readTableInput(const string& label) {
    string input;

    setColor(7);

    cout << "| "
         << left << setw(LABEL_WIDTH) << label
         << " | ";

    getline(cin, input);

    if (input.length() > VALUE_WIDTH) {
        input = input.substr(0, VALUE_WIDTH);
    }

    cout << "|" << endl;

    return input;
}

void displayMainMenu() {
    printBorder();

    printCenteredTitle(
        "SMART CAMPUS STUDENT RESOURCE MANAGEMENT SYSTEM",
        11
    );

    printBorder();

    const int menuWidth = TABLE_WIDTH - 2;

    cout << "|"
         << string(menuWidth, ' ')
         << "|"
         << endl;

    setColor(7);
    cout << "|  "
         << left << setw(menuWidth - 2)
         << "1. Display All Students (Array Traversal)"
         << "|"
         << endl;

    cout << "|  "
         << left << setw(menuWidth - 2)
         << "2. Search Student by ID"
         << "|"
         << endl;

    cout << "|  "
         << left << setw(menuWidth - 2)
         << "3. Update Student Information"
         << "|"
         << endl;

    cout << "|  "
         << left << setw(menuWidth - 2)
         << "4. Add New Student"
         << "|"
         << endl;

    cout << "|  "
         << left << setw(menuWidth - 2)
         << "5. Delete Student by ID"
         << "|"
         << endl;

    cout << "|  "
         << left << setw(menuWidth - 2)
         << "6. Display Resource Matrix"
         << "|"
         << endl;

    cout << "|  "
         << left << setw(menuWidth - 2)
         << "7. Analyze Resource Utilization"
         << "|"
         << endl;

    cout << "|  "
         << left << setw(menuWidth - 2)
         << "8. Generate Report"
         << "|"
         << endl;

    setColor(7);
    cout << "|  ";

    setColor(12);
    cout << left << setw(menuWidth - 2)
         << "9. Exit";

    setColor(7);
    cout << "|" << endl;

    printBorder();
}

void displayStudents(Student studentList[], int count) {
    printBorder();
    printCenteredTitle("ALL STUDENTS", 11);
    printBorder();

    int widths[] = {10, 10, 25, 37};

    cout << "| "
         << left << setw(10) << "Index"
         << " | "
         << setw(10) << "ID"
         << " | "
         << setw(25) << "Name"
         << " | "
         << setw(37) << "Department & Section"
         << " |"
         << endl;

    printSeparator(widths, 4);

    for (int i = 0; i < count; i++) {
        cout << "| "
             << left << setw(10) << i + 1
             << " | "
             << setw(10) << studentList[i].id
             << " | "
             << setw(25) << studentList[i].name
             << " | "
             << setw(37) << studentList[i].departmentSection
             << " |"
             << endl;
    }

    if (count == 0) {
        cout << "| "
             << left << setw(10) << ""
             << " | "
             << setw(10) << ""
             << " | "
             << setw(25) << "No students found."
             << " | "
             << setw(37) << ""
             << " |"
             << endl;
    }

    printBorder();
}

void searchStudent(Student studentList[], int count) {
    printBorder();
    printCenteredTitle("SEARCH STUDENT", 11);
    printBorder();

    string input = readTableInput("Student ID");

    int id;

    try {
        size_t position;
        id = stoi(input, &position);

        if (position != input.length()) {
            throw invalid_argument("Invalid");
        }
    }
    catch (...) {
        printBorder();
        printCenteredTitle("SEARCH RESULT", 12);
        printBorder();

        printTableRow("Status", "Invalid student ID.");

        printBorder();
        return;
    }

    int index = -1;

    for (int i = 0; i < count; i++) {
        if (studentList[i].id == id) {
            index = i;
            break;
        }
    }

    printBorder();
    printCenteredTitle("SEARCH RESULT", 10);
    printBorder();

    if (index != -1) {
        printTableRow(
            "Student ID",
            to_string(studentList[index].id)
        );

        printTableRow(
            "Name",
            studentList[index].name
        );

        printTableRow(
            "Department & Section",
            studentList[index].departmentSection
        );
    }
    else {
        printTableRow(
            "Status",
            "Student not found."
        );
    }

    printBorder();
}

bool validName(const string& name) {
    if (name.empty()) {
        return false;
    }

    for (char ch : name) {
        if (!isalpha(static_cast<unsigned char>(ch)) && ch != ' ') {
            return false;
        }
    }

    return true;
}

int selectDepartment() {
    while (true) {
        printBorder();
        printCenteredTitle("SELECT DEPARTMENT", 11);
        printBorder();

        int widths[] = {10, 25, 50};

        cout << "| "
             << left << setw(10) << "Option"
             << " | "
             << setw(25) << "Department"
             << " | "
             << setw(50) << "Program"
             << " |"
             << endl;

        printSeparator(widths, 3);

        cout << "| "
             << setw(10) << "1"
             << " | "
             << setw(25) << "IT Dept"
             << " | "
             << setw(50) << "BSIT"
             << " |"
             << endl;

        cout << "| "
             << setw(10) << "2"
             << " | "
             << setw(25) << "Engineering"
             << " | "
             << setw(50) << "BSCE"
             << " |"
             << endl;

        cout << "| "
             << setw(10) << "3"
             << " | "
             << setw(25) << "Business"
             << " | "
             << setw(50) << "BSBA"
             << " |"
             << endl;

        cout << "| "
             << setw(10) << "4"
             << " | "
             << setw(25) << "Education"
             << " | "
             << setw(50) << "BSED"
             << " |"
             << endl;

        printBorder();

        string input = readTableInput("Department");

        try {
            size_t position;
            int choice = stoi(input, &position);

            if (position != input.length() ||
                choice < 1 ||
                choice > 4) {
                throw invalid_argument("Invalid");
            }

            return choice;
        }
        catch (...) {
            printBorder();
            printCenteredTitle("INVALID INPUT", 12);
            printBorder();

            printTableRow(
                "Status",
                "Please enter a number from 1 to 4."
            );

            printBorder();
        }
    }
}

string selectSection(int departmentChoice) {
    string program;

    if (departmentChoice == 1) {
        program = "BSIT";
    }
    else if (departmentChoice == 2) {
        program = "BSCE";
    }
    else if (departmentChoice == 3) {
        program = "BSBA";
    }
    else {
        program = "BSED";
    }

    while (true) {
        printBorder();
        printCenteredTitle("SELECT SECTION", 11);
        printBorder();

        int widths[] = {10, 78};

        cout << "| "
             << left << setw(10) << "Option"
             << " | "
             << setw(78) << "Section"
             << " |"
             << endl;

        printSeparator(widths, 2);

        cout << "| "
             << setw(10) << "1"
             << " | "
             << setw(78) << program + " 1A"
             << " |"
             << endl;

        cout << "| "
             << setw(10) << "2"
             << " | "
             << setw(78) << program + " 1B"
             << " |"
             << endl;

        printBorder();

        string input = readTableInput("Section");

        if (input == "1") {
            return program + " 1A";
        }

        if (input == "2") {
            return program + " 1B";
        }

        printBorder();
        printCenteredTitle("INVALID INPUT", 12);
        printBorder();

        printTableRow(
            "Status",
            "Please enter 1 or 2."
        );

        printBorder();
    }
}

void updateStudent(Student studentList[], int count) {
    printBorder();
    printCenteredTitle("UPDATE STUDENT INFORMATION", 11);
    printBorder();

    string input = readTableInput("Student ID");

    int id;

    try {
        size_t position;
        id = stoi(input, &position);

        if (position != input.length()) {
            throw invalid_argument("Invalid");
        }
    }
    catch (...) {
        printBorder();
        printCenteredTitle("UPDATE RESULT", 12);
        printBorder();

        printTableRow(
            "Status",
            "Invalid student ID."
        );

        printBorder();
        return;
    }

    int index = -1;

    for (int i = 0; i < count; i++) {
        if (studentList[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printBorder();
        printCenteredTitle("UPDATE RESULT", 12);
        printBorder();

        printTableRow(
            "Status",
            "Student not found."
        );

        printBorder();
        return;
    }

    printBorder();
    printCenteredTitle("UPDATE STUDENT INFORMATION", 11);
    printBorder();

    string newName = readTableInput("New Name");

    while (!validName(newName)) {
        printBorder();
        printCenteredTitle("INVALID NAME", 12);
        printBorder();

        printTableRow(
            "Status",
            "Use letters and spaces only."
        );

        printBorder();

        printBorder();
        printCenteredTitle("UPDATE STUDENT INFORMATION", 11);
        printBorder();

        newName = readTableInput("New Name");
    }

    int departmentChoice = selectDepartment();
    string newSection = selectSection(departmentChoice);

    studentList[index].name = newName;
    studentList[index].departmentSection = newSection;

    printBorder();
    printCenteredTitle("STUDENT UPDATED", 10);
    printBorder();

    printTableRow(
        "Student ID",
        to_string(studentList[index].id)
    );

    printTableRow(
        "Name",
        studentList[index].name
    );

    printTableRow(
        "Department & Section",
        studentList[index].departmentSection
    );

    printBorder();
}

void addStudent(Student studentList[], int& count) {
    if (count >= MAX_CAPACITY) {
        printBorder();
        printCenteredTitle("ADD STUDENT", 12);
        printBorder();

        printTableRow(
            "Status",
            "Student capacity is full."
        );

        printBorder();
        return;
    }

    printBorder();
    printCenteredTitle("ADD NEW STUDENT", 11);
    printBorder();

    string input = readTableInput("Student ID");

    int id;

    try {
        size_t position;
        id = stoi(input, &position);

        if (position != input.length()) {
            throw invalid_argument("Invalid");
        }
    }
    catch (...) {
        printBorder();
        printCenteredTitle("ADD STUDENT", 12);
        printBorder();

        printTableRow(
            "Status",
            "Invalid student ID."
        );

        printBorder();
        return;
    }

    for (int i = 0; i < count; i++) {
        if (studentList[i].id == id) {
            printBorder();
            printCenteredTitle("ADD STUDENT", 12);
            printBorder();

            printTableRow(
                "Status",
                "Student ID already exists."
            );

            printBorder();
            return;
        }
    }

    printBorder();
    printCenteredTitle("ADD NEW STUDENT", 11);
    printBorder();

    string name = readTableInput("Name");

    while (!validName(name)) {
        printBorder();
        printCenteredTitle("INVALID NAME", 12);
        printBorder();

        printTableRow(
            "Status",
            "Use letters and spaces only."
        );

        printBorder();

        printBorder();
        printCenteredTitle("ADD NEW STUDENT", 11);
        printBorder();

        name = readTableInput("Name");
    }

    int departmentChoice = selectDepartment();
    string section = selectSection(departmentChoice);

    studentList[count].id = id;
    studentList[count].name = name;
    studentList[count].departmentSection = section;

    count++;

    printBorder();
    printCenteredTitle("STUDENT ADDED", 10);
    printBorder();

    printTableRow(
        "Student ID",
        to_string(id)
    );

    printTableRow(
        "Name",
        name
    );

    printTableRow(
        "Department & Section",
        section
    );

    printBorder();
}

void deleteStudent(Student studentList[], int& count) {
    printBorder();
    printCenteredTitle("DELETE STUDENT", 12);
    printBorder();

    string input = readTableInput("Student ID");

    int id;

    try {
        size_t position;
        id = stoi(input, &position);

        if (position != input.length()) {
            throw invalid_argument("Invalid");
        }
    }
    catch (...) {
        printBorder();
        printCenteredTitle("DELETE RESULT", 12);
        printBorder();

        printTableRow(
            "Status",
            "Invalid student ID."
        );

        printBorder();
        return;
    }

    int index = -1;

    for (int i = 0; i < count; i++) {
        if (studentList[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printBorder();
        printCenteredTitle("DELETE RESULT", 12);
        printBorder();

        printTableRow(
            "Status",
            "Student not found."
        );

        printBorder();
        return;
    }

    for (int i = index; i < count - 1; i++) {
        studentList[i] = studentList[i + 1];
    }

    count--;

    printBorder();
    printCenteredTitle("STUDENT DELETED", 10);
    printBorder();

    printTableRow(
        "Deleted Student ID",
        to_string(id)
    );

    printTableRow(
        "Status",
        "Student record successfully deleted."
    );

    printBorder();
}

void displayResourceMatrix() {
    printBorder();

    printCenteredTitle(
        "CAMPUS RESOURCE UTILIZATION MATRIX",
        11
    );

    printBorder();

    int widths[] = {23, 14, 14, 14, 14};

    cout << "| "
         << left << setw(23) << "Department"
         << " | "
         << setw(14) << "R-01"
         << " | "
         << setw(14) << "R-02"
         << " | "
         << setw(14) << "R-03"
         << " | "
         << setw(14) << "R-04"
         << " |"
         << endl;

    printSeparator(widths, 5);

    for (int i = 0; i < ROWS; i++) {
        cout << "| "
             << left << setw(23) << departments[i]
             << " | "
             << setw(14) << resourceMatrix[i][0]
             << " | "
             << setw(14) << resourceMatrix[i][1]
             << " | "
             << setw(14) << resourceMatrix[i][2]
             << " | "
             << setw(14) << resourceMatrix[i][3]
             << " |"
             << endl;
    }

    printBorder();
}

void processMatrix() {
    printBorder();

    printCenteredTitle(
        "RESOURCE UTILIZATION ANALYSIS",
        11
    );

    printBorder();

    int widths[] = {23, 65};

    cout << "| "
         << left << setw(23) << "Department"
         << " | "
         << setw(65) << "Total Resource Usage"
         << " |"
         << endl;

    printSeparator(widths, 2);

    int grandTotal = 0;

    for (int i = 0; i < ROWS; i++) {
        int rowTotal = 0;

        for (int j = 0; j < COLS; j++) {
            rowTotal += resourceMatrix[i][j];
        }

        grandTotal += rowTotal;

        cout << "| "
             << left << setw(23) << departments[i]
             << " | "
             << setw(65) << rowTotal
             << " |"
             << endl;
    }

    printSeparator(widths, 2);

    cout << "| "
         << left << setw(23) << "Grand Total"
         << " | "
         << setw(65) << grandTotal
         << " |"
         << endl;

    printBorder();
}

void generateReport(Student studentList[], int count) {
    printBorder();

    printCenteredTitle(
        "SYSTEM SUMMARY REPORT",
        11
    );

    printBorder();

    int widths[] = {25, 63};

    cout << "| "
         << left << setw(25) << "Report Item"
         << " | "
         << setw(63) << "Details"
         << " |"
         << endl;

    printSeparator(widths, 2);

    cout << "| "
         << left << setw(25) << "Total Student Records"
         << " | "
         << setw(63) << count
         << " |"
         << endl;

    cout << "| "
         << left << setw(25) << "Maximum Capacity"
         << " | "
         << setw(63) << MAX_CAPACITY
         << " |"
         << endl;

    int totalResourceHours = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            totalResourceHours += resourceMatrix[i][j];
        }
    }

    cout << "| "
         << left << setw(25) << "Total Resource Usage"
         << " | "
         << setw(63) << totalResourceHours
         << " |"
         << endl;

    printSeparator(widths, 2);

    cout << "| "
         << left << setw(25) << "System Status"
         << " | "
         << setw(63) << "Operational"
         << " |"
         << endl;

    printBorder();
}

int main() {
    Student studentList[MAX_CAPACITY] = {
        {1001, "Juan Dela Cruz", "BSIT 1A"},
        {1002, "Maria Santos", "BSIT 1A"},
        {1003, "Carlo Reyes", "BSIT 1B"}
    };

    int count = 3;

    list<string> resourceList = {
        "R-01",
        "R-02",
        "R-03",
        "R-04"
    };

    int choice;

    do {
        displayMainMenu();

        string input;

        setColor(10);
        cout << " Enter your choice: ";
        getline(cin, input);

        try {
            size_t position;
            choice = stoi(input, &position);

            if (position != input.length()) {
                throw invalid_argument("Invalid");
            }
        }
        catch (...) {
            choice = 0;
        }

        switch (choice) {
            case 1:
                displayStudents(studentList, count);
                break;

            case 2:
                searchStudent(studentList, count);
                break;

            case 3:
                updateStudent(studentList, count);
                break;

            case 4:
                addStudent(studentList, count);
                break;

            case 5:
                deleteStudent(studentList, count);
                break;

            case 6:
                displayResourceMatrix();
                break;

            case 7:
                processMatrix();
                break;

            case 8:
                generateReport(studentList, count);
                break;

            case 9:
                printBorder();

                printCenteredTitle(
                    "SYSTEM EXIT",
                    10
                );

                printBorder();

                printTableRow(
                    "Status",
                    "Thank you for using the Smart Campus System."
                );

                printBorder();
                break;

            default:
                printBorder();

                printCenteredTitle(
                    "INVALID MENU CHOICE",
                    12
                );

                printBorder();

                printTableRow(
                    "Status",
                    "Please enter a number from 1 to 9."
                );

                printBorder();
        }

        if (choice != 9) {
            cout << endl;
        }

    } while (choice != 9);

    return 0;
}
