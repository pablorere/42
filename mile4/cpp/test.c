#include <unistd.h>

int ft_strlen(char *str)
{
    int i = 0;

    while(str[i])
    {
        i++;
    }
    return(i);
}


int main(int ac, char **av)
{
    char size = 0;
    if (ac > 1)
    {
     size = ft_strlen(av[1]) + '0';
     write(1, &size, 1);
    }
    write(1, "\n", 1);

}