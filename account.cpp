#include "account.hh"
#include <iostream>

Account::Account(const string &owner, bool has_credit, int limit_amount):
    owner_(owner), has_credit_(has_credit), limit_amount_(limit_amount)
{
    generate_iban();
    has_credit_ = has_credit;
    limit_amount_ = limit_amount;
}

// Prints the accounts
void Account::print() const
{

    cout << owner_ << " : " << iban_ <<  " : " << balance_ << " euros"<< endl;
}

// Returns the information of the accounts owner
string Account::owner() const
{

    return owner_;
}

// Account's balance
void Account::balance(int balance)
{

    cout << balance << endl;
}

// Returns a truth value if credit can be set to the account
bool Account::account_has_credit()
{
    // If credit can't be set, return false
    if ( this->has_credit_ == false )
    {

        return false;
    }

    // If credit can be set, return true
    return true;
}

// Sets a credit limit that is given in the parameter limit
void Account::set_credit_limit(int limit)
{

    // If return value from account_has_credit is true, credit limit is stored
    // in the variable limit_amount_.
    if ( account_has_credit() )
    {
        this->limit_amount_ = limit;
    }

    // If return value from account_has_credit is false, prints a message.
    else
    {
        cout << "Cannot set credit limit: the account has no credit card"
             << endl;
    }
}

// Adds the amount of money given in parameter save to the balance.
void Account::save_money(int save)
{
    balance_ += save;
}

// Removes the amount of money given in parameter take from balance.
void Account::take_money(int take)
{

    // If the amount of money to be taken is less than balance, money can be
    // taken.
    if ( take < balance_ )
    {

        balance_ -= take;

        cout << take << " euros taken: new balance of " << iban_ << " is "
             << balance_ << " euros" << endl;
    }

    // If account_has_credit is true and balance minus take is less than set
    // credit limit limit_amount_, money can be taken from the account.
    else if ( ( ( account_has_credit() == true ) && ( balance_ - take ) )
             < limit_amount_ )
    {

        if ( abs ( ( balance_ - take ) ) <= limit_amount_ )
        {

            balance_ -= take;

            cout << take << " euros taken: new balance of " << iban_ << " is "
                 << balance_ << " euros" << endl;
        }

        // If limit_amount_ is smaller than balance minus take, the amount money
        // that user wants to take is more than the set credit limit and money
        // can't be taken.
        else
        {

            cout << "Cannot take money: credit limit overflow" << endl;
        }
    }

    // If account_has_credit is false and the amount that user wants to take is
    // more than the account's balance, money can't be taken and a messgae is
    // printed.
    else
    {

        cout << "Cannot take money: balance underflow" << endl;
    }

}

// Checks if the transfer between accounts can be done.
void Account::transfer_to(Account& owner_, int amount)
{

    // If account_has_credit is true and balance minus take is less than set
    // credit limit limit_amount_, money can be taken from the account.
    if ( ( ( account_has_credit() == true ) && ( balance_ - amount ) )
         < limit_amount_ )
    {

        if ( abs ( ( balance_ - amount ) ) <= limit_amount_ )
        {

            this->balance_ = ( balance_ - amount );
            owner_.transfer(amount);

            cout << amount << " euros taken: new balance of " << iban_
                 << " is " << balance_ << " euros" << endl;
        }
    }

    // If account_has_credit is false and the amount of money to be transfered
    // is smaller or the same as the balace, transfer can be done.
    else if ( ( account_has_credit() == false ) && ( amount <= balance_ ) )
    {

        this->balance_ = ( balance_ - amount );
        owner_.transfer(amount);

        cout << amount << " euros taken: new balance of " << iban_ << " is "
             << balance_ << " euros" << endl;
    }

    // If account_has_credit is false and the amount that user wants to take is
    // more than the account's balance, money can't be taken and a messgae is
    // printed.
    else if ( ( account_has_credit() == false ) && ( amount > balance_ ) )
    {

        cout << "Cannot take money: balance underflow" << endl;
        cout << "Transfer from " << iban_ << " failed" << endl;
    }

    // If limit_amount_ is smaller than balance minus take, the amount money
    // that user wants to take is more than the set credit limit and money
    // can't be taken.
    if ( ( ( account_has_credit() == true ) && ( balance_ - amount ) )
         < limit_amount_ )
    {

        if ( abs ( ( balance_ - amount ) ) > limit_amount_ )
        {

            cout << "Cannot take money: credit limit overflow" << endl;
            cout << "Transfer from " << iban_ << " failed" << endl;
        }
    }
}

// Does the actual transfer between accounts.
void Account::transfer(int amount)
{

    balance_ += amount;
}


// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);

}


