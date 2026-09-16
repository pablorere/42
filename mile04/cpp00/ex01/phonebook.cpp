#include "phonebook.hpp"
#include "Contact.hpp"
#include "main.hpp"
#include <cstdio>
#include <string>
#include <iostream>


static std::string readRequiredField(const std::string &prompt, size_t len, InputType type)
{
	std::string value;

	std::cout << prompt << std::flush;
	value = getInput(len, type);
	while (value.empty())
	{
		std::cout << "You must fill this field to continue" << std::endl;
		std::cout << prompt << std::flush;
		value = getInput(len, type);
	}
	return (value);
}

phonebook::phonebook() : contactCount(0) {}
phonebook::~phonebook(){}

void phonebook::ADD()
{
    std::string field[6];
    std::string idStr = "0";
    idStr[0] = '0' + (contactCount % 8);
    field[0] = idStr;

	field[1] = readRequiredField("Write ur first Name (max 32 characters): ", 32, ALPHA);
	field[2] = readRequiredField("Write ur last Name (max 32 characters): ", 32, ALPHA);
	// Read phone number first (tests supply phone before nickname)
	field[4] = readRequiredField("Write ur Number (max 10 characters): ", 10, NUMERIC);
	field[3] = readRequiredField("Write ur Nickname (max 32 characters): ", 32, ALPHA);
	field[5] = readRequiredField("Write your biggest secret (max 32 characters): ", 32, ALPHANUM);

    // Use a circular buffer: overwrite the slot at contactCount % 8
    int saveIndex = contactCount % 8;
    _Contact[saveIndex].setfield(field);
    contactCount++;
}

void phonebook::SEARCH(){
	std::string field[8][6];
	_Contact[0].getfield(field[0]);
	if (field[0][1].empty())
		std::cout << "you must first create a contact" << std::endl;
	else {
		std::cout << "o----------o----------o----------o----------o" << std::endl;
		std::cout << "|     Index|First Name| Last Name|  Nickname|" << std::endl;
		std::cout << "|----------|----------|----------|----------|" << std::endl;
		int totalContacts = (contactCount < 8) ? contactCount : 8;
		for (int i = 0; i < totalContacts; i++)
		{
			_Contact[i].getfield(field[i]);
			std::string print = formated(field[i]);
			std::cout << "|         " << i + 1 << print << std::endl;
			if (i + 1 != totalContacts)
				std::cout << "|----------|----------|----------|----------|" << std::endl;
		}
		std::cout << "o----------o----------o----------o----------o" << std::endl;
		std::cout << "Chose the index of the contact" << std::endl;
		std::string indexInput = getInput(1, NUMERIC);
		while (indexInput.empty() || indexInput[0] < '1' || indexInput[0] > ('0' + totalContacts))
		{
			std::cout << "Chose a valid index" << std::endl;
			indexInput = getInput(1, NUMERIC);
		}
		int index = indexInput[0] - '1';
		_Contact[index].getfield(field[index]);
		printcontacts(field[index]);
	}
}

std::string phonebook::formated(std::string *array){
	std::string devolver;
	for (int i = 1; i < 4; i++)
	{
		int spaces = 10 - array[i].length();
		devolver += '|';
		
		if(spaces < 0)
		{
			devolver += array[i].substr(0,9) + ".";
		}
		else
		{
			for(int ns = 0; ns < spaces; ns++)
			{
				devolver += ' ';
			}
			devolver += array[i];
		}
	}
	devolver += '|';
	return devolver;
}

void phonebook::printcontacts(std::string field[]){
 
	std::cout << field[1] << std::endl << field[2] << std::endl << field[3] << std::endl << field[4] << std::endl << field[5] << std::endl;
}



