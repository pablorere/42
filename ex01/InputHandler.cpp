#include "main.hpp"

static bool isAllowed(char c, InputType type)
{
    if (type == NUMERIC)
        return (std::isdigit(c));
    if (type == ALPHA)
        return (std::isalpha(c));
    return (std::isalnum(c));
}

std::string getInput(size_t len, InputType type)
{
    struct termios term, old;
    tcgetattr(STDIN_FILENO, &old);
    term = old;
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    std::string s;
    char c;
    while (read(STDIN_FILENO, &c, 1) > 0 && c != 4)
    {
        if (c == '\n' || c == '\r')
            break;
        if (c == 27)
        {
            char seq[3];
            if (read(STDIN_FILENO, seq, 2) == 2)
            {
                if (seq[0] == '[' && seq[1] == '3')
                {
                    read(STDIN_FILENO, seq, 1);
                    if (!s.empty())
                    {
                        s.resize(s.length() - 1);
                        std::cout << "\b \b" << std::flush;
                    }
                }
                else if (seq[0] == '[' && std::isdigit(seq[1]))
                    read(STDIN_FILENO, seq, 1);
            }
        }
        else if (c == 127 || c == 8)
        {
            if (!s.empty())
            {
                s.resize(s.length() - 1);
                std::cout << "\b \b" << std::flush;
            }
        }
        else if (s.length() < len && isAllowed(c, type))
        {
            s += c;
            std::cout << c << std::flush;
        }
    }
    std::cout << "\033[2J\033[H" << std::flush;
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    return (s);
}
 
