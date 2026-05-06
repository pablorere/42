#include "phonebook.hpp"
#include "Contact.hpp"
#include "main.hpp"

phonebook::phonebook() : contactCount(0) {}
phonebook::~phonebook(){}

void phonebook::reorganizeIds()
{
    std::string field[6];
    int totalContacts = (contactCount < 8) ? contactCount : 8;
    _Contact[totalContacts].getfield(field); // El índice donde está el más viejo
    int oldestIndex = field[0][0] - '0';
    
    for (int i = 0; i < totalContacts; i++)
    {
        int actualIndex = (oldestIndex + i) % 8;
        _Contact[actualIndex].getfield(field);
        field[0][0] = i + '0'; // Asignar nuevo ID
        _Contact[actualIndex].setfield(field);
    }
}

void phonebook::ADD()
{
    std::string field[6];
    field[0] = contactCount; // id
    
    std::cout << "Write ur first Name (max 10 characters): " << std::flush;
    field[1] = getInput(10, ALPHA);
    while(field[1].empty())
    {
        std::cout << "You must fill this field to continue" << std::endl;
        std::cout << "Write ur first Name (max 10 characters): " << std::flush;
        field[1] = getInput(10, ALPHA);
    }
    std::cout << "Write ur last Name (max 10 characters): " << std::flush;
    field[2] = getInput(10, ALPHA);
    while(field[2].empty())
    {
        std::cout << "You must fill this field to continue" << std::endl;
        std::cout << "Write ur last Name (max 10 characters): " << std::flush;
        field[2] = getInput(10, ALPHA);
    }
    std::cout << "Write ur Nickname (max 10 characters): " << std::flush;
    field[3] = getInput(10, ALPHA);
    while(field[3].empty())
    {
        std::cout << "You must fill this field to continue" << std::endl;
        std::cout << "Write ur Nickname (max 10 characters): " << std::flush;
        field[3] = getInput(10, ALPHA);
    }
    std::cout << "Write ur Number (max 10 characters): " << std::flush;
    field[4] = getInput(10, NUMERIC);
    while (field[4].empty())
    {
        std::cout << "You must fill this field to continue" << std::endl;
        std::cout << "Write ur Number (max 10 characters):"<< std::flush;
        field[4] = getInput(10, NUMERIC);
    }   
    
    std::cout << "Escribe tu mayor secreto: " << std::flush;
    field[5] = getInput(40, ALPHA);
    
    _Contact[contactCount % 8].setfield(field);
    contactCount++;
    if (contactCount > 8)
        reorganizeIds();
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
            //imprimir cada contato os quatro dados salto de linha 
            _Contact[i].getfield(field[i]);
            std::string print = formated(field[i]);
            std::cout << "|         " << i + 1 << print << std::endl;
            if (i + 1 != totalContacts)
                std::cout << "|----------|----------|----------|----------|" << std::endl;
        }
	    std::cout << "o----------o----------o----------o----------o" << std::endl;
        int index = getInput(1, NUMERIC)[0] - 49;
        std::cout << "Chose the index of the contact" << std::endl;
        _Contact[index].getfield(field[index]);
        printcontacts(field[index]);
    }
}

std::string phonebook::formated(std::string *array){
    std::string devolver;
    // tem que ficar |------nome|-outronome|
    //barra espacos e field 3 vezes
    for (int i = 1; i < 4; i++)
    {
      int spaces = 10 - array[i].length();
      devolver += '|';

      for(int ns = 0; ns < spaces; ns++)
      {
        devolver += ' ';
      }
      devolver += array[i];
    }
    devolver += '|';
    return devolver;
}

void phonebook::printcontacts(std::string field[]){
 
    std::cout << field[1] << std::endl << field[2] << std::endl << field[3] << std::endl << field[4] << std::endl << field[5] << std::endl;
}



//PROBLEMAS  QUANDO CRIO UM NOVO CONTATO QUERO QUE O MAIOR NUMERO SEJA O MAIS RECENTE E O MENOR NUMERO O MAIS VELHO