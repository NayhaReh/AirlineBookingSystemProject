#include "Passenger.h"

//default constructor
Passenger::Passenger() : firstName(""), lastName(""), phone(""),
                         row(-1), seat(' '), id(-1) {}

//constructor
Passenger::Passenger(string firstName, string lastName, string phone,
                     int row, char seat, int id)
    : firstName(firstName),
      lastName(lastName),
      phone(phone),
      row(row),
      seat(seat),
      id(id) {}

string Passenger::seatToString() const {
    return to_string(row) + seat;   
}
