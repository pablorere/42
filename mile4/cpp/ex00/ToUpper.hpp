# include <iostream>
# include <string>
class ToUpper
{   private:
    std::string _text;
    public:
    ToUpper(); //constructor por defecto
    ToUpper(std::string text);  //constructor con parametro
    ToUpper(const ToUpper &other); // copia canonica
    ToUpper &operator=(const ToUpper &other);  //operador de copia
    ~ToUpper(); //destructor
    std::string scream();
};
