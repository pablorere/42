#include "Contact.hpp"
#include <sstream>

Contact::Contact() : Id(0) {} // Initialize Id to 0
Contact::~Contact(){}

void Contact::setfield(const std::string field[]){
    this->Id = field[0][0] - '0';
    this->FirstName = field[1];
    this->LastName = field[2];
    this->Nickname = field[3];
    this->PhoneNumber = field[4];
    this->DarkestSecret = field[5];
}

void Contact::getfield(std::string field[]) const{
    field[0][0] = Id + '0';
    field[1] = this->FirstName;
    field[2] = this->LastName;
    field[3] = this->Nickname;
    field[4] = this->PhoneNumber;
    field[5] = this->DarkestSecret;
}

// Stores all contact data; returns the oldest index once over 8 entries