#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
using namespace std;

class Passenger {
private:
    string firstName;
    string lastName;
    string phone;
    int row;        // e.g., 6
    char seat;      // e.g., 'A'
    int id;         // unique passenger ID

public:
    // ---- Constructors ----
    Passenger();
    Passenger(string firstName, string lastName, string phone,
              int row, char seat, int id);

    // ---- Getters ----
    string getFirstName() const { return firstName; }
    string getLastName() const { return lastName; }
    string getPhone() const { return phone; }
    int getRow() const { return row; }
    char getSeat() const { return seat; }
    int getID() const { return id; }

    // ---- Setters (optional but useful) ----
    void setRow(int r) { row = r; }
    void setSeat(char s) { seat = s; }

    // ---- Utility ----
    string seatToString() const; // returns "6A"
};

#endif
