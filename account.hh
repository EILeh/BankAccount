/* Account
 *
 * Description
 *
 * Class for a single account that has a IBAN number, owner and balance. Account
 * can have credit with credit limit that can go to minus as much as the
 * credit limit is.
 *
 * Writer of the program
 *
 * Name: EILeh
 */


#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

using namespace std;

class Account
{
public:
    // Constructor
    Account(const string& owner, bool has_credit = false, int limit_amount = 0);

    // More methods
    string owner() const;

    // Return a truth value if the account has credit or not.
    bool account_has_credit();

    // Checks the accounts balance which is saved in the parameter balance.
    void balance(int balance);

    // Sets a credit limit to the account.
    void set_credit_limit(int limit);

    // Puts the amount of money to save that is given in the parameter save.
    void save_money(int save);

    // Takes the amount of money that is given in the parameter take.
    void take_money(int take);

    // Transfers the amount of money that is given in the parameter amount from
    // certain owner's account that is the first parameter owner_.
    void transfer_to(Account& owner_, int amount);

    // Does the transfering.
    void transfer(int amount);

    // Prints everything.
    void print() const;

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // accounts owner
    string owner_;

    // accounts balance
    int balance_ = 0;

    // truth value if the account has credit or not
    bool has_credit_;

    // limit to credit accounts
    int limit_amount_;

    // iban number as a string
    string iban_;

};

#endif // ACCOUNT_HH
