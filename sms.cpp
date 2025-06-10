#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cctype>  
using namespace std;

struct Student {
    int rollNo;
    string firstName;
    string lastName;
    string courseID;
    int age;
    string contactNo;
};

void displayMenu(){
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Welcome to the Student Management System" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Please select an option:" << std::endl;
    std::cout << "1. Add new Student to the database" << std::endl;
    std::cout << "2. Search for a Student by RollNo." << std::endl;
    std::cout << "3. Search for a Student by First Name." << std::endl;
    std::cout << "4. Search for a Student by Course ID." << std::endl;
    std::cout << "5. Count the total number of Students." << std::endl;
    std::cout << "6. Display all Students." << std::endl;
    std::cout << "7. Update a Student's information." << std::endl;
    std::cout << "8. Delete a Student from the database." << std::endl;
    std::cout << "9. Exit the program." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void loadStudentsFromFile(vector<Student> &students) {
    ifstream inFile("students.txt");
    if(inFile.is_open()) {
        Student s;
        while(inFile >> s.rollNo >> s.firstName >> s.lastName >> s.courseID >> s.age >> s.contactNo) {
            students.push_back(s);
        }
        inFile.close();
    } else {
        cout << "Error opening file to load student data." << endl;
    }
}

void updateStudentsToFile(const vector<Student> &students){
    ofstream outFile("students.txt");
    if(!outFile.is_open()){
        cout << "Failed to update the file." << endl;
        return;
    }

    for(const auto &s : students){
        outFile << s.rollNo << " "
                << s.firstName << " "
                << s.lastName << " "
                << s.courseID << " "
                << s.age << " "
                << s.contactNo << endl;
    }
    outFile.close();
}

void addStudent(vector<Student> &students) {
    char confirm;
    do{
        Student s;
        while (true) {
            cout << "Enter Roll Number: ";
            cin >> s.rollNo;
            cin.ignore();

            bool exists = false;
            for (const auto& student : students) {
                if (student.rollNo == s.rollNo) {
                    cout << "Roll Number already exists. Please try again." << endl;
                    std::cout << "----------------------------------------" << std::endl;
                    exists = true;
                    break;
                }
            }

            if (!exists) break;  // roll number is unique, exit loop
        }
       cout << "Enter First Name: ";
        cin >> s.firstName;
        transform(s.firstName.begin(), s.firstName.end(), s.firstName.begin(), ::tolower);

        cout << "Enter Last Name: ";
        cin >> s.lastName;
        transform(s.lastName.begin(), s.lastName.end(), s.lastName.begin(), ::tolower);

        cout << "Enter Course ID: ";
        cin >> s.courseID;
        cout << "Enter Age: "; 
        cin >> s.age;
        cout << "Enter Contact Number: ";
        cin >> s.contactNo;

        students.push_back(s);
        cout << "Student added successfully!" << endl;
        std::cout << "----------------------------------------" << std::endl;

        ofstream outFile("students.txt", ios::app);
        if(outFile.is_open()){
            outFile << s.rollNo << " "
                    << s.firstName << " "
                    << s.lastName << " "
                    << s.courseID << " "
                    << s.age << " "
                    << s.contactNo << endl;
            outFile.close();
        }else{
            cout << "Error opening file to save student data." << endl;
        }

        cout << "Add another student? (Y/N): ";
        cin >> confirm;
        cin.ignore();
    }while(confirm == 'y' || confirm =='Y');

}

void searchByRollNo(const vector<Student> &students){
    char choice;
    do{
        int roll;
        cout << "Enter Roll Number to search: ";
        cin >> roll;
        bool found = false;
        for(const auto &s : students) {
            if(s.rollNo == roll) {
                cout << "\nStudent Found:\n";
                cout << "Roll No: " << s.rollNo << endl;
                string fName = s.firstName;
                string lName = s.lastName;

                if (!fName.empty()) fName[0] = toupper(fName[0]);
                if (!lName.empty()) lName[0] = toupper(lName[0]);

                cout << "Name: " << fName << " " << lName << endl;
                cout << "Course ID: " << s.courseID << endl;
                cout << "Age: " << s.age << endl;
                cout << "Contact: " << s.contactNo << endl;
                found = true;
                break;
            }
        }
        if(!found) {
            cout << "No student found with Roll Number: " << roll << endl;
        }
        cout << "Search another student? (Y/N): ";
        cin >> choice;
        std::cout << "----------------------------------------" << std::endl;
        cin.ignore();
    }while(choice == 'y' || choice == 'Y');
}

void searchByFirstName(const vector<Student> &students){
    char choice;
    do{
        string fName;
        cout << "Enter First Name to search: ";
        cin >> fName;
        transform(fName.begin(), fName.end(), fName.begin(), ::tolower);
        bool found = false;
        for (auto &s: students){
            if(s.firstName == fName) {
                cout << "\nStudent Found:\n";
                cout << "Roll No: " << s.rollNo << endl;
                string fName = s.firstName;
                string lName = s.lastName;

                if (!fName.empty()) fName[0] = toupper(fName[0]);
                if (!lName.empty()) lName[0] = toupper(lName[0]);

                cout << "Name: " << fName << " " << lName << endl;
                cout << "Course ID: " << s.courseID << endl;
                cout << "Age: " << s.age << endl;
                cout << "Contact: " << s.contactNo << endl;
                found = true;
                break;
            }
        }
        if(!found){
            cout << "No student found with First Name: " << fName << endl;
        }
        cout << "Search another student? (Y/N): ";
        cin >> choice;
        std::cout << "----------------------------------------" << std::endl;
        cin.ignore();
    }while(choice == 'y' || choice == 'Y');
}

void searchByCourseId(const vector<Student> &students){
    char choice;
    do{
        string courseid;
        cout << "Enter Course ID to search: ";
        cin >> courseid;
        bool found = false;
        for (auto &s: students){
            if(s.courseID == courseid) {
                cout << "\nStudent Found:\n";
                cout << "Roll No: " << s.rollNo << endl;
                string fName = s.firstName;
                string lName = s.lastName;

                if (!fName.empty()) fName[0] = toupper(fName[0]);
                if (!lName.empty()) lName[0] = toupper(lName[0]);

                cout << "Name: " << fName << " " << lName << endl;
                cout << "Course ID: " << s.courseID << endl;
                cout << "Age: " << s.age << endl;
                cout << "Contact: " << s.contactNo << endl;
                found = true;
            }
        }
        if(!found){
            cout << "No student found with First Name: " << courseid << endl;
        }
        cout << "Search another course? (Y/N): ";
        cin >> choice;
        std::cout << "----------------------------------------" << std::endl;
        cin.ignore();
    }while(choice == 'y' || choice == 'Y');
    
}

void countStudents(const vector<Student> &students){
    if(students.empty()) {
        cout << "No students found in the database." << endl;
        return;
    }
    cout << "Total number of students: " << students.size() << endl;
}

void displayStudents(const vector<Student> &students){
    cout << "\nDisplaying all the Students:\n";
    for(auto &s: students){
        cout << "Roll No: " << s.rollNo << endl;
        string fName = s.firstName;
        string lName = s.lastName;

        if (!fName.empty()) fName[0] = toupper(fName[0]);
        if (!lName.empty()) lName[0] = toupper(lName[0]);

        cout << "Name: " << fName << " " << lName << endl;
        cout << "Course ID: " << s.courseID << endl;
        cout << "Age: " << s.age << endl;
        cout << "Contact: " << s.contactNo << endl;
    }
}

void updateStudent(vector<Student> &students){
    char choice;
    do{
        int roll;
        cout << "Enter Roll Number of the student to update: ";
        cin >> roll;
        cin.ignore();

        bool found = false;
        for(auto &s : students){
            if(s.rollNo == roll){
                cout << "Student found. Enter new details:\n";

                string input;

                cout << "First Name [" << s.firstName << "]: ";
                getline(cin, input);
                if (!input.empty()) s.firstName = input;

                cout << "Last Name [" << s.lastName << "]: ";
                getline(cin, input);
                if (!input.empty()) s.lastName = input;

                cout << "Course ID [" << s.courseID << "]: ";
                getline(cin, input);
                if (!input.empty()) s.courseID = input;

                cout << "Age [" << s.age << "]: ";
                getline(cin, input);
                if (!input.empty()) {
                    stringstream ss(input);
                    int age;
                    if (ss >> age) s.age = age;
                }

                cout << "Contact Number [" << s.contactNo << "]: ";
                getline(cin, input);
                if (!input.empty()) {
                    stringstream ss(input);
                    int contact;
                    if (ss >> contact) s.contactNo = contact;
                }


                found = true;
                break;
            }
        }

        if(!found){
            cout << "No student found with Roll Number: " << roll << endl;
        }else{
            updateStudentsToFile(students);
        }
        cout << "Update another student? (Y/N): ";
        cin >> choice;
        std::cout << "----------------------------------------" << std::endl;
        cin.ignore();
    }while(choice == 'y' || choice == 'Y');
    
}

void deleteStudent(vector<Student> &students) {
    char choice;
    do{
        int roll;
        cout << "Enter Roll Number of the student to delete: ";
        cin >> roll;

        bool found = false;
        for(auto it = students.begin(); it != students.end(); ++it){
            if(it->rollNo == roll){
                students.erase(it);
                found = true;
                cout << "Student with Roll Number " << roll << " has been deleted." << endl;
                break;
            }
        }

        if(!found){
            cout << "No student found with Roll Number: " << roll << endl;
        }else{
            updateStudentsToFile(students);
        }
        cout << "Delete another student? (Y/N): ";
        cin >> choice;
        std::cout << "----------------------------------------" << std::endl;
        cin.ignore();
    }while(choice == 'y' || choice == 'Y');
}

int main(){
    int choice;
    vector<Student> student;
    loadStudentsFromFile(student);
    do
    {
        displayMenu();
        std::cout << "Enter your choice (1-9): ";
        std::cin >> choice;
        std::cout << "----------------------------------------" << std::endl;
        switch(choice){
            case 1:
                addStudent(student);
                break;
            case 2:
                searchByRollNo(student);
                break;
            case 3:
                searchByFirstName(student);
                break;
            case 4:
                searchByCourseId(student);
                break; 
            case 5:
                countStudents(student);
                break;
            case 6:
                displayStudents(student);
                break;
            case 7: 
                updateStudent(student);
                break;
            case 8:
                deleteStudent(student);
                break;
            case 9:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 9);
    
    return 0;
}