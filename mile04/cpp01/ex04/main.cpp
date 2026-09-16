#include <string>
#include <iostream>
#include <fstream>

int error(std::string str)
{
	std::cerr << "Error:" << str << std::endl;
	return 1;
}
void myReplacer(std::string& str, const std::string& s1, const std::string& s2)
{
	if(s1.empty())
		return;
	size_t pos = 0;
	while((pos = str.find(s1, pos)) != std::string::npos)
	{
		str.erase(pos, s1.length());
		str.insert(pos, s2);
		pos += s2.length();
	}
}

int main (int ac, char **av) {
	if (ac != 4)
		return (std::cout << "input must be provided as: ./Sed_is_for_losers filename s1 s2" << std::endl, 1);
	std::string filename = av[1];
	std::string s1 = av[2];
	std::string s2 = av[3];
	std::ifstream infile(filename.c_str());
	if (!infile.is_open())
		return error("could not open file " + filename);
	std::string fileOut = filename + ".replace";
	std::ofstream outfile(fileOut.c_str());
	if (!outfile.is_open())
		return error("could not create file " + fileOut);
	std::string line;
	while (std::getline(infile, line))
	{
		myReplacer(line, s1, s2);
		outfile << line;\
		if (!infile.eof())
			outfile << std::endl;
	}
	outfile.close();
	infile.close();
	return 0;
}