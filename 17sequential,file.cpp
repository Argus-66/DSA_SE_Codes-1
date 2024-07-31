/*Department maintains s information. The file contains rollno, name, division and address. 
Allow user to insert, delete and search information of s. use sequential file to 
maintain the data*/

#include <bits/stdc++.h>
using namespace std;

struct Student{
    int rollno;
    string name;
    string division;
    string address;
};

void insert(fstream &file){
    Student s;
    cout<<"Enter roll no.: ";
    cin>> s.rollno;
    cin.ignore();
    cout<<"Enter name: ";
    getline(cin, s.name);
    cout<<"Enter division: ";
    getline(cin, s.division);
    cout<<"Enter address: ";
    getline(cin, s.address);
    file.open("students.txt", ios::app);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    file << s.rollno << " " << s.name << " " << s.division << " " << s.address << endl;
    file.close();
    cout<<"Student record inserted successfully.\n";
}

void search(fstream& file, int rollno) {
    Student s;
    bool found = false;
    file.open("students.txt", ios::in);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    while (file >> s.rollno >> s.name >> s.division >> s.address) {
        if (s.rollno == rollno) {
            cout << "Student found:" << endl;
            cout << "Roll No: " << s.rollno << endl;
            cout << "Name: " << s.name << endl;
            cout << "Division: " << s.division << endl;
            cout << "Address: " << s.address << endl;
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "Student with roll number " << rollno << " not found." << endl;
    }
}

void deleteRecord(fstream &file, int rollno){
    fstream tempfile("temp.txt", ios::out);
    Student s;
    bool found = false;
    file.open("students.txt", ios::in);
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }
    while (file >> s.rollno >> s.name >> s.division >> s.address){
        if(s.rollno != rollno){
            tempfile << s.rollno << " " << s.name << " " << s.division << " " << s.address << endl;
        } else {
            found = true;
        }
    }
    file.close();
    tempfile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found) {
        cout << "Student record with roll number " << rollno << " deleted successfully." << endl;
    } else {
        cout << "Student with roll number " << rollno << " not found." << endl;
    }
}

int main() {
    fstream file;
    while (true) {
        cout << "\n1. Insert record\n";
        cout << "2. Search record\n";
        cout << "3. Delete record\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
            case 1:
                insert(file);
                break;
            case 2:
                int searchRollNo;
                cout << "Enter roll number to search: ";
                cin >> searchRollNo;
                search(file, searchRollNo);
                break;
            case 3:
                int deleteRollNo;
                cout << "Enter roll number to delete: ";
                cin >> deleteRollNo;
                deleteRecord(file, deleteRollNo);
                break;
            case 4:
                cout << "Exiting program.";
                return 0;
            default:
                cout << "Invalid choice. Please try again.";
        }
    }
    return 0;
}