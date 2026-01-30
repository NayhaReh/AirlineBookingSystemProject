#include <iostream>
#include <string>
#include "FlightManager.h"
using namespace std;


void pressEnter() {
    cout << "\n<<< Press Return to Continue>>>>\n";
    cin.get();
}

void cleanStandardInputStream(void) {
    int leftover;
    do {
        leftover = cin.get();
    } while (leftover != '\n' && leftover != EOF);
}

void clearScreen(void) {
#ifdef UNIX
    system("clear");
#else
    system("cls");       
#endif
}

//display header
void displayHeader() {
    clearScreen();
    cout << "\n Flight Management Application - Fall 2025\n";
    cout << "\nVersion: 1.0";
    cout << "\nTerm Project";
    cout << "\nProduced by: <Abiya Raheel, Himaal Ishaq, Nayha Rehman>\n\n";
    pressEnter();
}

//menu
int menu() {
    int choice;

    clearScreen();
    cout << "Please select one of the following options:\n\n";
    cout << "1. Select a Flight\n";
    cout << "2. Display Flight Seat Map\n";
    cout << "3. Display Passengers Information\n";
    cout << "4. Add a New Passenger\n";
    cout << "5. Remove an Existing Passenger\n";
    cout << "6. Save Data\n";
    cout << "7. Quit\n";
    cout << "\nEnter your choice (1-7): ";

    cin >> choice;
    cleanStandardInputStream();
    return choice;
}

//main program
int main() {

    displayHeader();

    FlightManager manager;

    // Load output files
    if (!manager.loadFlights("flights.txt")) {
        cout << "Error loading flights.txt\n";
        return 1;
    }
    if (!manager.loadPassengers("passengers.txt")) {
        cout << "Error loading passengers.txt\n";
        return 1;
    }

    int choice;

    while (true) {
        choice = menu();

        switch (choice) {

        //selecting a flight

        case 1: {
            manager.displayFlightList();
            cout << "\nEnter your choice: ";
            int fchoice;
            cin >> fchoice;
            cleanStandardInputStream();

            if (manager.selectFlight(fchoice)) {
                Flight* f = manager.getSelectedFlight();
                cout << "\nYou have selected flight " << f->getID()
                     << " from " << f->getDeparture()
                     << " to " << f->getDestination() << ".\n";
            } else {
                cout << "\nInvalid selection.\n";
            }
            pressEnter();
            break;
        }

        //choosing seat map

        case 2: {
            if (!manager.hasSelectedFlight()) {
                cout << "\nPlease select a flight first.\n";
            } else {
                manager.getSelectedFlight()->showSeatMap();
            }
            pressEnter();
            break;
        }

        // display passenger list

        case 3: {
            if (!manager.hasSelectedFlight()) {
                cout << "\nPlease select a flight first.\n";
            } else {
                manager.getSelectedFlight()->showPassengerList();
            }
            pressEnter();
            break;
        }

        // add a passenger
        case 4: {
            if (!manager.hasSelectedFlight()) {
                cout << "\nPlease select a flight first.\n";
                pressEnter();
                break;
            }

            Flight* f = manager.getSelectedFlight();

            string first, last, phone;
            int row, id;
            char seat;

            cout << "\nEnter Passenger ID: ";
            cin >> id;
            cleanStandardInputStream();

            // ID length validation
            if (id < 0 || id > 99999) {
                cout << "\nERROR: Passenger ID cannot be more than 5 digits.\n";
                pressEnter();
                break;
            }

            cout << "Enter First Name: ";
            cin >> first;

            cout << "Enter Last Name: ";
            cin >> last;

            cout << "Enter Phone Number: ";
            cin >> phone;

            cout << "Enter Desired Row: ";
            cin >> row;
            cleanStandardInputStream();

            // Validate row
            if (row < 0 || row >= f->getRows()) {
                cout << "\nERROR: Invalid row number. Valid rows: 0 to "
                    << (f->getRows() - 1) << ".\n";
                pressEnter();
                break;
            }

            cout << "Enter Desired Seat (A-" << char('A' + f->getCols() - 1) << "): ";
            cin >> seat;
            cleanStandardInputStream();

            // Convert lowercase to uppercase manually
            if (seat >= 'a' && seat <= 'z') {
                seat = seat - 'a' + 'A';
            }

            // Validate seat letter
            if (seat < 'A' || seat >= char('A' + f->getCols())) {
                cout << "\nERROR: Invalid seat letter. Must be between A and "
                    << char('A' + f->getCols() - 1) << ".\n";
                pressEnter();
                break;
            }

            // Now try to add passenger
            Passenger p(first, last, phone, row, seat, id);

            if (f->addPassenger(p)) {
                cout << "\nPassenger added successfully!\n";
            } else {
                cout << "\nERROR: Seat chosen is invalid.\n";
            }

            pressEnter();
            break;
        }


        // remove passenger

        case 5: {
            if (!manager.hasSelectedFlight()) {
                cout << "\nPlease select a flight first.\n";
                pressEnter();
                break;
            }

            int passengerid;
            cout << "\nEnter Passenger ID to remove: ";
            cin >> passengerid;
            cleanStandardInputStream();

            if (manager.removePassengerFromAnyFlight(pid)) {
                cout << "\nPassenger removed successfully.\n";
            } else {
                cout << "\nERROR: Passenger not found in ANY flight.\n";
            }

            pressEnter();
            break;
        }


        // save the data
        case 6: {
            char ans;
            cout << "\nDo you want to save the passenger data? (Y/N): ";
            cin >> ans;

            // Convert lowercase to uppercase manually
            if (ans >= 'a' && ans <= 'z') {
                ans = ans - 'a' + 'A';
            }

            if (ans == 'Y') {
                if (manager.savePassengers("passengers.txt")) {
                    cout << "\nAll data saved successfully.\n";
                } else {
                    cout << "\nERROR: Could not save file.\n";
                }
            } else {
                cout << "\nSave canceled.\n";
            }

            cleanStandardInputStream();
            pressEnter();
            break;
        }


        // quit program
        case 7:
            cout << "\nProgram terminated.\n";
            return 0;

        // invalid option entered

        default:
            cout << "\nInvalid choice.\n";
            pressEnter();
        }
    }

    return 0;
}
