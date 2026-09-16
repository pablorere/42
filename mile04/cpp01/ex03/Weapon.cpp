    #include "Weapon.hpp"
    

    Weapon::Weapon(){};
    Weapon::Weapon(std::string Type){
        this->setType(Type);
    };
    Weapon::~Weapon(){};
    const std::string& Weapon::getType() const {
        return Type;
    };
    void Weapon::setType(std::string Type){
        this->Type = Type;
    };