#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
# include "Contact.hpp"
class phonebook{
private:
    Contact _Contact[8];
    int contactCount;
    void reorganizeIds();
    void printcontacts(std::string field[]);

    std::string formated(std::string *array);
public:
    phonebook();
    ~phonebook();
    void ADD();
    void SEARCH();
};

#endif