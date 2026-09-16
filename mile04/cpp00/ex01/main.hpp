#ifndef MAIN_HPP
#define MAIN_HPP

#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include "phonebook.hpp"

enum InputType { NUMERIC, ALPHA, ALPHANUM };

std::string getInput(size_t len, InputType type);

#endif
