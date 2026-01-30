#include "FlightManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor
FlightManager::FlightManager() : selectedIndex(-1) {}


// Load flights from flights.txt file

bool FlightManager::loadFlights(const string& filename) {
    ifstream fin(filename);
    if (!fin)
        return false;

    string id, dep, dest;
    int rows, cols;

    while (fin >> id >> dep >> dest >> rows >> cols) {
        flights.push_back(Flight(id, dep, dest, rows, cols));
    }

    return true;
}


// Load passengers from passengers.txt file
bool FlightManager::loadPassengers(const string& filename) {
    ifstream fin(filename);
    if (!fin)
        return false;

    string flightID, first, last, phone, seatStr;
    int id;

    while (fin >> flightID >> first >> last >> phone >> seatStr >> id) {

        //get letter for seat
        char seat = seatStr[seatStr.length() - 1];

        //convert digits before seat letter into int row
        int row = 0;
        for (int i = 0; i < seatStr.length() - 1; i++) {
            row = row * 10 + (seatStr[i] - '0');
        }

        Passenger p(first, last, phone, row, seat, id);

        //add passenger to flight 
        bool found = false;

        for (int i = 0; i < flights.size(); i++) {
            if (flights[i].getID() == flightID) {
                flights[i].addPassenger(p);
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Warning: passenger " << first << " " << last
                 << " could not be assigned to flight " << flightID << endl;
        }
    }

    return true;
}



// display the flight list

void FlightManager::displayFlightList() const {
    cout << "\nHere is the list of available flights:\n\n";

    for (int i = 0; i < flights.size(); i++) {
        cout << i + 1 << ". "
             << flights[i].getID() << "  "
             << flights[i].getDeparture() << "   "
             << flights[i].getDestination() << "   "
             << flights[i].getRows() << "   "
             << flights[i].getCols();
        cout << endl;
    }
}


//select a flight by inputting number
bool FlightManager::selectFlight(int choice) {
    if (choice < 1 || choice > flights.size())
        return false;

    selectedIndex = choice - 1;
    return true;
}


//get pointer for selected flight
Flight* FlightManager::getSelectedFlight() {
    if (selectedIndex == -1)
        return nullptr;

    return &flights[selectedIndex];
}


//save passenger data to file
bool FlightManager::savePassengers(const string& filename) const {
    ofstream fout(filename);
    if (!fout)
        return false;

    for (const auto& f : flights) {
        const auto& plist = f.getPassengerList();
        for (const auto& p : plist) {
            fout << f.getID() << " "
                 << p.getFirstName() << " "
                 << p.getLastName() << " "
                 << p.getPhone() << " "
                 << p.getRow() << p.getSeat() << " "
                 << p.getID() << "\n";
        }
    }
    return true;
}

//removing passengers
bool FlightManager::removePassengerFromAnyFlight(int passengerID) {

    for (int i = 0; i < flights.size(); i++) {
        if (flights[i].removePassenger(passengerID)) {
            cout << "\nPassenger removed from flight "
                 << flights[i].getID() << ".\n";
            return true;
        }
    }
    return false;
}

