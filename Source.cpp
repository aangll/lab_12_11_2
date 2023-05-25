#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Subscriber {
    string name;
    string phoneNumber;
    Subscriber* left;
    Subscriber* right;

    Subscriber(const string& subscriberName, const string& subscriberPhoneNumber) : name(subscriberName), phoneNumber(subscriberPhoneNumber), left(nullptr), right(nullptr) {}
};

struct TelephoneDirectory {
    Subscriber* root;
};

void insertSubscriber(Subscriber*& root, const string& name, const string& phoneNumber) {
    if (root == nullptr) {
        root = new Subscriber(name, phoneNumber);
    }
    else if (name < root->name) {
        insertSubscriber(root->left, name, phoneNumber);
    }
    else {
        insertSubscriber(root->right, name, phoneNumber);
    }
}

void createTelephoneDirectory(TelephoneDirectory& directory) {
    cout << "Enter the number of subscribers: ";
    int count;
    cin >> count;
    cin.ignore(); // Ignore the newline character

    directory.root = nullptr;

    for (int i = 0; i < count; i++) {
        cout << "Subscriber " << i + 1 << " name: ";
        string name;
        getline(cin, name);

        cout << "Subscriber " << i + 1 << " phone number: ";
        string phoneNumber;
        getline(cin, phoneNumber);

        insertSubscriber(directory.root, name, phoneNumber);
    }
}

void printTelephoneDirectory(const Subscriber* root) {
    if (root != nullptr) {
        printTelephoneDirectory(root->left);
        cout << "Name: " << root->name << endl;
        cout << "Phone Number: " << root->phoneNumber << endl;
        printTelephoneDirectory(root->right);
    }
}

void saveTelephoneDirectoryHelper(const Subscriber* root, ofstream& file) {
    if (root != nullptr) {
        saveTelephoneDirectoryHelper(root->left, file);
        file << root->name << endl;
        file << root->phoneNumber << endl;
        saveTelephoneDirectoryHelper(root->right, file);
    }
}

void saveTelephoneDirectory(const TelephoneDirectory& directory, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        saveTelephoneDirectoryHelper(directory.root, file);
        file.close();
        cout << "Telephone directory saved to " << filename << endl;
    }
    else {
        cout << "Error opening file " << filename << " for writing." << endl;
    }
}

void loadTelephoneDirectoryHelper(Subscriber*& root, ifstream& file) {
    if (!file.eof()) {
        string name;
        getline(file, name);

        string phoneNumber;
        getline(file, phoneNumber);

        root = new Subscriber(name, phoneNumber);
        loadTelephoneDirectoryHelper(root->left, file);
        loadTelephoneDirectoryHelper(root->right, file);
    }
}

void loadTelephoneDirectory(TelephoneDirectory& directory, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        directory.root = nullptr;
        loadTelephoneDirectoryHelper(directory.root, file);
        file.close();
        cout << "Telephone directory loaded from " << filename << endl;
    }
    else {
        cout << "Error opening file " << filename << " for reading." << endl;
    }
}

bool searchSubscriber(const Subscriber* root, const string& phoneNumber) {
    if (root == nullptr) {
        return false;
    }
    else if (root->phoneNumber == phoneNumber) {
        return true;
    }
    else if (phoneNumber < root->phoneNumber) {
        return searchSubscriber(root->left, phoneNumber);
    }
    else {
        return searchSubscriber(root->right, phoneNumber);
    }
}

void makePhoneCall(const TelephoneDirectory& directory) {
    string phoneNumber;
    int duration;

    cout << "Enter phone number: ";
    getline(cin, phoneNumber);

    cout << "Enter call duration (in minutes): ";
    cin >> duration;
    cin.ignore(); // Ignore the newline character

    if (searchSubscriber(directory.root, phoneNumber)) {
        if (duration > 100) {
            cout << "Payment required for phone call with duration > 100 minutes." << endl;
        }
        else {
            cout << "Phone call recorded." << endl;
        }
    }
    else {
        cout << "Phone number not found in the directory." << endl;
    }
}

void deleteTree(Subscriber* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

int main() {
    TelephoneDirectory directory;
    string filename;

    int choice;
    do {
        cout << "Telephone Directory Menu:" << endl;
        cout << "1. Create Telephone Directory" << endl;
        cout << "2. Print Telephone Directory" << endl;
        cout << "3. Save Telephone Directory to File" << endl;
        cout << "4. Load Telephone Directory from File" << endl;
        cout << "5. Make Phone Call" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character

        switch (choice) {
        case 1:
            createTelephoneDirectory(directory);
            break;
        case 2:
            cout << "Telephone Directory:" << endl;
            printTelephoneDirectory(directory.root);
            break;
        case 3:
            cout << "Enter filename to save: ";
            getline(cin, filename);
            saveTelephoneDirectory(directory, filename);
            break;
        case 4:
            cout << "Enter filename to load: ";
            getline(cin, filename);
            loadTelephoneDirectory(directory, filename);
            break;
        case 5:
            makePhoneCall(directory);
            break;
        case 6:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            break;
        }

        cout << endl;
    } while (choice != 6);

    deleteTree(directory.root); // Free allocated memory

    return 0;
}