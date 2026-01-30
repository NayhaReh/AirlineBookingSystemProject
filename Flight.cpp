#include <iostream>
#include <iomanip>
#include "Flight.h"
using namespace std;

//constructors

Flight::Flight() : flightID(""), departure(""), destination(""),
                   rows(0), cols(0) {}

Flight::Flight(string id, string dep, string dest, int rows, int cols)
    : flightID(id), departure(dep), destination(dest),
      rows(rows), cols(cols) 
{
    initializeSeatMap();
}

//initialize the seat map
void Flight::initializeSeatMap() {
    seatMap = vector<vector<char>>(rows, vector<char>(cols, ' '));
}

//convert letter of seat to its index
int Flight::seatLetterToIndex(char seat) const {
    //convert A to 0, B to 1...
    seat = toupper(seat);
    return seat - 'A';
}

//check seat availability 
bool Flight::isSeatAvailable(int row, char seat) const {
    int col = seatLetterToIndex(seat);
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return false; // invalid seat

    return (seatMap[row][col] == ' ');
}

//add passenger
bool Flight::addPassenger(const Passenger& p) {
    int r = p.getRow();
    char s = p.getSeat();

    if (!isSeatAvailable(r, s))
        return false;

    seatMap[r][seatLetterToIndex(s)] = 'X';
    passengers.push_back(p);

    return true;
}

//remove the passenger by ID
bool Flight::removePassenger(int passengerID) {
    for (int i = 0; i < passengers.size(); i++) {
        if (passengers[i].getID() == passengerID) {
            int r = passengers[i].getRow();
            char s = passengers[i].getSeat();

            seatMap[r][seatLetterToIndex(s)] = ' ';
            passengers.erase(passengers.begin() + i);

            return true;
        }
    }
    return false; 
}

//display seat map
void Flight::showSeatMap() const {
    cout << "\n Aircraft Seat Map for flight " << flightID << ":\n\n";

    //print seat letters
    cout << "     ";
    for (int c = 0; c < cols; c++)
        cout << char('A' + c) << "   ";
    cout << endl;

    //print rows
    for (int r = 0; r < rows; r++) {
        cout << setw(2) << r << "  ";

        for (int c = 0; c < cols; c++)
            cout << "| " << seatMap[r][c] << " ";

        cout << "|\n";
    }
}

// display the passenger list
void Flight::showPassengerList() const {

    cout << "\nPassenger List (Flight:" << flightID 
         << " from " << departure
         << " to " << destination << ")\n\n";

    cout << left << setw(15) << "First Name"
         << setw(15) << "Last Name"
         << setw(15) << "Phone"
         << setw(6)  << "Row"
         << setw(6)  << "Seat"
         << setw(6)  << "ID"
         << endl;   

    for (int i = 0; i < passengers.size(); i++) {
        const Passenger& p = passengers[i];
        cout << setw(15) << p.getFirstName()
             << setw(15) << p.getLastName()
             << setw(15) << p.getPhone()
             << setw(6)  << p.getRow()
             << setw(6)  << p.getSeat()
             << setw(6)  << p.getID()
             << "\n";
    }
}
