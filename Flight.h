#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <vector>
#include "Passenger.h"
using namespace std;

class Flight {

private:
    string flightID;
    string departure;
    string destination;

    int rows;       
    int cols;      

    vector<vector<char>> seatMap;  
    // ' ' = empty  
    // 'X' = occupied

    vector<Passenger> passengers;

public:
    //constructors
    Flight();
    Flight(string id, string dep, string dest, int rows, int cols);

    string getID() const { return flightID; }
    string getDeparture() const { return departure; }
    string getDestination() const { return destination; }
    int getRows() const { return rows; }
    int getCols() const { return cols; }

    vector<Passenger>& getPassengerList() { return passengers; }
    const vector<Passenger>& getPassengerList() const { return passengers; }


    void initializeSeatMap();
    void showSeatMap() const;
    void showPassengerList() const;

    bool isSeatAvailable(int row, char seat) const;
    bool addPassenger(const Passenger& p);
    bool removePassenger(int passengerID);


    int seatLetterToIndex(char seat) const;
};

#endif
