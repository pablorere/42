#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>
#include <iostream>

class Contact
{   private:
    int Id;
    std::string FirstName;
    std::string LastName;
    std::string Nickname;
    std::string PhoneNumber;
    std::string DarkestSecret;
    public:
    Contact(); //constructor por defecto
    ~Contact(); //destructor
    void setfield(const std::string field[]); //setter

    void getfield(std::string field[]) const; //getter
};


#endif