#include "Account.hpp"
#include <ctime>
#include <iostream>
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/*
./The_Job_Of_Your_Dreams > test.txt                                      
diff <(cut -d ' ' -f 2- test.txt) <(cut -d ' ' -f 2- 19920104_091532.log)

*/

Account::Account( int initial_deposit ): _amount(0), _nbDeposits(0), _nbWithdrawals(0)
{
    _accountIndex = _nbAccounts;
    _nbAccounts++;
    _amount += initial_deposit;
    if (_amount < 0)
        Account::~Account();
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";created" << std::endl ;
    _totalAmount += _amount;
};
Account::~Account()
{
    _displayTimestamp();
    std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl ;
};


int Account::getNbAccounts( void )
{
    return(_nbAccounts);
};
int Account::getTotalAmount()
{
    return(_totalAmount);    
};

int Account::getNbDeposits()
{
    return(_totalNbDeposits);
};
int Account::getNbWithdrawals()
{
    return(_totalNbWithdrawals);
};

int	Account::checkAmount( void ) const
{
    return(this->_amount);
};

void Account::displayStatus( void ) const
{
    _displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";deposits:" 
		<< _nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
};

void Account::_displayTimestamp( void )
{
    char timestamp[20];
    std::time_t now;
	
	std::time(&now);
    std::strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", std::localtime(&now));
	std::cout << "[" << timestamp << "] ";

};


void Account::makeDeposit( int deposit )
{
    _displayTimestamp();
    _nbDeposits++;
    _totalNbDeposits++;
    std::cout << "index:" << _accountIndex << ";p_amount:" << _amount << ";deposit:"
    << deposit << ";amount:" << _amount + deposit << ";nb_deposits:" << _nbDeposits << std::endl ;
    _amount += deposit;
    _totalAmount += deposit;
}
bool Account::makeWithdrawal( int withdrawal )
{
    _displayTimestamp();
    if(_amount - withdrawal < 0 || withdrawal < 1)
    {
        std::cout << "index:" << _accountIndex << ";p_amount:" << _amount << ";withdrawal:refused" 
        << std::endl;
         return(false);
    }
    else
    {
        _nbWithdrawals++;
        _totalNbWithdrawals++;
        std::cout << "index:" << _accountIndex << ";p_amount:" << _amount << ";withdrawal:" << withdrawal
        << ";amount:" << _amount - withdrawal << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
        _amount -= withdrawal;
        _totalAmount -= withdrawal;
        return(true);
    }
}


void Account::displayAccountsInfos( void )
{
    _displayTimestamp();
    std::cout << "accounts:"<< getNbAccounts() << ";total:" <<  getTotalAmount() 
    << ";deposits:" << getNbDeposits() << ";withdrawals:"<< getNbWithdrawals() << std::endl ;
}

