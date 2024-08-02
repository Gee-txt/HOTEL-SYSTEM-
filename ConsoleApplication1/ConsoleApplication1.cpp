#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>


using namespace std;

struct RUM {
    int roomno;
    int p_ebed;  
    char bed[15];
    char roomtype[30];
    float roomcst;
    int avl;
    bool availability[3][7];
};

// Function for calling 
void search();
void displayUserMenu();
void login();
void regist();
void forget();
void displayRooms();
void mainMenu();
void displayAdminMenu();
void addRoom();
bool isUsernameUnique(const string& username);
void bookRoom();
void displayRoomsuser();
void initializeAvailability(bool availability[3][7]);

void initializeAvailability(bool availability[3][7])
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            availability[i][j] = true; // Set all periods to available
        }
    }
}

void displayAvailability(const RUM& room)
{
    const char* periods[] = { "Morning", "Afternoon", "Night" };
    const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    cout << "Room Number: " << room.roomno << "\n";
    cout << "Availability:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "  " << periods[i] << ":\n";
        for (int j = 0; j < 7; ++j) {
            cout << "    " << days[j] << ": " << (room.availability[i][j] ? "Available" : "Not Available") << "\n";
        }
    }
}

void addRoom() {
    system("cls");
    RUM newRoom;

    cout << "Enter Room Number: ";
    cin >> newRoom.roomno;

    cout << "Enter Price for Extra Bed: ";
    cin >> newRoom.p_ebed;

    cout << "Enter Bed Type: ";
    cin.ignore();  // To ignore the newline character left by previous input
    cin.getline(newRoom.bed, 15);

    cout << "Enter Room Type: ";
    cin.getline(newRoom.roomtype, 30);

    cout << "Enter Room Cost: ";
    cin >> newRoom.roomcst;

    cout << "Enter Availability (1 for available, 0 for not available): ";
    cin >> newRoom.avl;

    // Initialize availability
    initializeAvailability(newRoom.availability);

    // Open file in append mode and write room details
    ofstream file("rooms.txt", ios::app);
    if (file.is_open()) {
        file << newRoom.roomno << " "
            << newRoom.p_ebed << " "
            << newRoom.bed << " "
            << newRoom.roomtype << " "
            << newRoom.roomcst << " "
            << newRoom.avl << "\n";
        file.close();
        system("cls");
        displayAdminMenu();
        cout << "Room added successfully!\n";
    }
    else {
        system("cls");
        addRoom();
        cout << "Unable to open file.\n";
    }
}

void displayRooms()
{
    system("cls");
    ifstream file("rooms.txt");
    if (file.is_open()) {
        cout << "************************************************** [ROOM LIST] **************************************************\n";
        RUM room;
        while (file >> room.roomno >> room.p_ebed >> room.bed >> room.roomtype >> room.roomcst >> room.avl)
        {
            cout << "Room Number: " << room.roomno << "\n";
            cout << "Price for Extra Bed: " << room.p_ebed << "\n";
            cout << "Bed Type: " << room.bed << "\n";
            cout << "Room Type: " << room.roomtype << "\n";
            cout << "Room Cost: " << room.roomcst << "\n";
            cout << "Availability: " << (room.avl ? "Available" : "Not Available") << "\n";
            cout << "----------------------------------\n";
        }
        file.close();

    }
    else {
        cout << "Unable to open file.\n";
    }
    cout << "Press any key to go back" << endl;
    string st;
    cin >> st;
    displayAdminMenu();
}

void displayRoomsuser()
{
    system("cls");
    ifstream file("rooms.txt");
    if (file.is_open()) {
        cout << "************************************************** [ROOM LIST] **************************************************\n";
        RUM room;
        while (file >> room.roomno >> room.p_ebed >> room.bed >> room.roomtype >> room.roomcst >> room.avl)
        {
            cout << "Room Number: " << room.roomno << "\n";
            cout << "Price for Extra Bed: " << room.p_ebed << "\n";
            cout << "Bed Type: " << room.bed << "\n";
            cout << "Room Type: " << room.roomtype << "\n";
            cout << "Room Cost: " << room.roomcst << "\n";
            cout << "Availability: " << (room.avl ? "Available" : "Not Available") << "\n";
            cout << "----------------------------------\n";
        }
        file.close();
    }
    else {
        cout << "Unable to open file.\n";
    }
    cout << "Press any key to go back" << endl;
    string st;
    cin >> st;
    displayUserMenu();
}

void displayAdminMenu()
{
    cout << "************************************************** [MAIN MENU] **************************************************\n";
    cout << "*Please enter your choice from menu*:\n";
    cout << "----------------------------------\n";
    cout << "Enter 1 -> Add Rooms\n";
    cout << "Enter 2 -> View Customers Records\n";
    cout << "Enter 3 -> Delete Customer Record\n";
    cout << "Enter 4 -> Edit Record\n";
    cout << "Enter 5 -> View Rooms\n";
    cout << "Enter 6 -> Exit\n";
    cout << "----------------------------------\n";
    int ch;
    cin >> ch;
    switch (ch)
    {
    case 1:
        addRoom();
        break;
    case 2:
        //view func;
        break;
    case 3:
        //delete func;
        break;
    case 4:
        //edit rec;
        break;
    case 5:
        displayRooms();
        break;
    case 6:
        mainMenu();
        break;
    default:
        cout << "Invalid choice! Please enter again.\n";
        displayAdminMenu();
    }
};

void bookRoom() {
    int roomNumber;
    cout << "Enter Room Number to book: ";
    cin >> roomNumber;

    // Read all rooms from file
    ifstream infile("rooms.txt");
    vector<RUM> rooms;
    RUM room;
    bool found = false;

    if (infile.is_open()) {
        while (infile >> room.roomno >> room.p_ebed 
            >> room.bed >> room.roomtype >> room.roomcst >> room.avl) {
            rooms.push_back(room);
        }
        infile.close();

        // Search for the room and update availability
        for (auto& r : rooms) {
            if (r.roomno == roomNumber) {
                if (r.avl == 1) {
                    r.avl = 0;
                    found = true;

                    cout << "Room " << roomNumber << " booked successfully.\n";
                    cout << "Press any key to go back" << endl;
                    string st;
                    cin >> st;
                    displayUserMenu();
                }
                else {
                    cout << "Room " << roomNumber << " is already booked.\n";
                }
                break;
            }
        }

        if (!found) {
            cout << "Room " << roomNumber << " not found.\n";
        }

        // Write updated rooms back to file
        ofstream outfile("rooms.txt");
        if (outfile.is_open()) {
            for (const auto& r : rooms) {
                outfile << r.roomno << " "
                    << r.p_ebed << " "
                    << r.bed << " "
                    << r.roomtype << " "
                    << r.roomcst << " "
                    << r.avl << "\n";
            }
            outfile.close();
        }
        else {
            cout << "Unable to open file for writing.\n";
        }
    }
    else {
        cout << "Unable to open file for reading.\n";
    }

}

void displayUserMenu() {
    cout << "************************************************** [MAIN MENU] **************************************************\n";
    cout << "*Please enter your choice from menu*:\n";
    cout << "----------------------------------\n";
    cout << "Enter 1 -> Search Rooms\n";
    cout << "Enter 2 -> Book a Room\n";
    cout << "Enter 3 -> Delete Customer Record\n";
    cout << "Enter 4 -> Search Customer Record\n";
    cout << "Enter 5 -> Edit Record\n";
    cout << "Enter 6 -> Exit\n";
    cout << "----------------------------------\n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        search();
        break;
    case 2:
        system("cls");
        bookRoom();
        break;
    case 3:
        // Call function to delete customer record
        cout << "Delete customer record functionality" << endl;
        break;
    case 4:
        // Call function to search customer record
        cout << "Search customer record functionality" << endl;
        break;
    case 5:
        // Call function to edit record
        cout << "Edit record functionality" << endl;
        break;
    case 6:
        // Exit the menu
        cout << "Thank you for using the system. Exiting..." << endl;
        return;
    default:
        cout << "Invalid choice, please try again." << endl;
    }
}

void login() {
    system("cls");
    int count = 0;
    string user, pc, id, pass;

    cout << "\t\t\t\t\t\t\t\t***** Welcome To Login Page *****\t\t\t\t\t\t\t\t\n\n" << endl;
    cout << "Please Insert Username and Password" << endl;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pc;

    ifstream input("data.txt");
    while (input >> id >> pass) {
        if (id == user && pass == pc) {
            count = 1;
            system("cls");
            cout << "Welcome " << user << " to your user account" << endl;
            displayUserMenu();
            return;
        }
    }
    input.close();

    ifstream adminInput("admin.txt");
    while (adminInput >> id >> pass) {
        if (id == user && pass == pc) {
            count = 2;
            system("cls");
            cout << "Welcome " << user << " to your admin account" << endl;
            displayAdminMenu();
            return;
        }
    }
    adminInput.close();

    
    system("cls");
    cout << "Error\nPlease try to enter password or username\nor try to register" << endl;
    cout << "Press 1 to go back" << endl;
    cout << "Press 2 to go to main menu" << endl;
    int num;
    cin >> num;
    cin.ignore();
    system("cls");

    if (num == 1) {
        login();
    }
    else {
        mainMenu();
    }
}

bool isUsernameUnique(const string& username) {
    ifstream dataFile("data.txt");
    ifstream adminFile("admin.txt");
    string id, pass;

    while (dataFile >> id >> pass) {
        if (id == username) {
            return false;
        }
    }
    dataFile.close();

    while (adminFile >> id >> pass) {
        if (id == username) {
            return false;
        }
    }
    adminFile.close();

    return true;
}

void regist() {
    int scode = 272012;
    string ruser, rpc, id, pass;
    system("cls");
    cout << "\t\t\t\t\t\t\t\t***** Welcome To Registration Page *****\t\t\t\t\t\t\t\t\n\n" << endl;
    cout << "Press 1 for Admin Registration" << endl;
    cout << "Press 2 for User Registration" << endl;
    int ch;
    cin >> ch;

    if (ch == 1) {
        cout << "Enter your Serial Code" << endl;
        int sc;
        cin >> sc;
        if (sc == scode) {
            cout << "Enter Your Username: ";
            cin >> ruser;
            cout << "Enter Your Password: ";
            cin >> rpc;

            if (!isUsernameUnique(ruser)) {
                system("cls");
                cout << "Username already exists" << endl;
                regist();
                return;
            }

            ofstream f1("admin.txt", ios::app);
            f1 << ruser << ' ' << rpc << endl;
            f1.close();
            system("cls");
            cout << "Registered Successfully" << endl;
            mainMenu();
        }
        else {
            cout << "Invalid Serial Code" << endl << "Press any key to go back" << endl;
            string st;
            cin >> st;
            regist();
        }
    }
    else if (ch == 2) {
        cout << "Enter Your Username: ";
        cin >> ruser;
        cout << "Enter Your Password: ";
        cin >> rpc;

        if (!isUsernameUnique(ruser)) {
            system("cls");
            cout << "Username already exists" << endl;
            regist();
            return;
        }

        ofstream f1("data.txt", ios::app);
        f1 << ruser << ' ' << rpc << endl;
        f1.close();
        system("cls");
        cout << "Registered Successfully" << endl;
        mainMenu();
    }
    else {
        cout << "Invalid Input" << endl << "Press any key to go back" << endl;
        string st;
        cin >> st;
        regist();
    }
}

void forget() {
    int option;
    system("cls");
    cout << "\t\t\t You forgot the password? No worries \n";
    cout << "Press 1 to search your id by username " << endl;
    cout << "Press 2 to go back to the main menu " << endl;
    cout << "\t\t\t Enter your choice:";
    cin >> option;

    switch (option) {
    case 1: {
        int count = 0;
        string suserId, sid, spass;
        cout << "\n\t\t\tEnter the username which you remembered :";
        cin >> suserId;
        ifstream f2("data.txt");
        while (f2 >> sid >> spass) {
            if (sid == suserId) {
                count = 1;
                break;
            }
        }
        f2.close();
        if (count == 1) {
            cout << "\n\n Your account is found! \n";
            cout << "\n\n Your password is: " << spass << endl;
        }
        else {
            cout << "\n\t Sorry! your account is not found! \n";
        }
        mainMenu();
        break;
    }
    case 2:
        mainMenu();
        break;
    default:
        cout << "\t\t\t Wrong choice! Please try again " << endl;
        forget();
    }
}

void mainMenu() {
    cout << "\t\t\t\t\t\t\t\t*****Welcome To The Hotel Site*****\t\t\t\t\t\t\t\t" << endl;
    cout << "\t\t\t\t\t\t\t\t\t*****Entry Menu*****\t\t\t\t\t\t\t\t\t\t\t" << endl;
    cout << "Please Choose From Options By Typing its Number" << endl;
    cout << "1. Login" << endl << "2. Register" << endl << "3. Forgot Passcode" << endl << "4. Exit" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
        login();
        break;
    case 2:
        regist();
        break;
    case 3:
        forget();
        break;
    case 4:
        cout << "Thank You" << endl;
        break;
    default:
        system("cls");
        cout << "Please Choose From Options Given Above\n";
        mainMenu();
    }
}

void filterByAvailability() {
    system("cls");
    int period;
    cout << "Select Availability Period:\n";
    cout << "1. Morning\n";
    cout << "2. Afternoon\n";
    cout << "3. Night\n";
    cout << "Enter your choice: ";
    cin >> period;

    if (period < 1 || period > 3) {
        cout << "Invalid choice. Please enter a number between 1 and 3.\n";
        filterByAvailability();
        return;
    }

    // Adjust period index to match array index
    int periodIndex = period - 1;

    // Open the file and read room data
    ifstream file("rooms.txt");
    if (file.is_open()) {
        RUM room;
        bool found = false;

        while (file >> room.roomno >> room.p_ebed >> room.bed >> room.roomtype >> room.roomcst >> room.avl) {
            // Check availability for the selected period
            bool isAvailable = false;
            for (int i = 0; i < 7; ++i) { // Loop through all days of the week
                if (room.availability[periodIndex][i]) {
                    isAvailable = true;
                    break;
                }
            }

            if (isAvailable) {
                displayAvailability(room); // Display room details and availability
                found = true;
            }
        }

        if (!found) {
            cout << "No rooms available for the selected period.\n";
        }

        file.close();
    }
    else {
        cout << "Unable to open file.\n";
    }

    cout << "Press any key to go back" << endl;
    string st;
    cin >> st;
    displayUserMenu(); // Return to user menu after showing results
}

void search() {

    system("cls");
    cout << "Press 1 if you want to browse all rooms" << endl;
    cout << "Press 2 if want to search by period" << endl;
    int choice1;
    cin >> choice1;
    
    if (choice1 == 1)
    {
        system("cls");
        displayRoomsuser();
    }
    else if (choice1 == 2)
    {
        system("cls");
        filterByAvailability();
    }
    else
    {
        system("cls");
        cout << "Please Choose From Options" << endl;
        string st;
        cout << "Press any key to go back" << endl;
        cin >> st;
        search();
    }
}



int main() {
    mainMenu();
    return 0;
}