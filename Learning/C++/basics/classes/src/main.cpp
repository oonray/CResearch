#include <iostream>

namespace bnk {
    class BankAccount {
        private:
            int balance;
        public:
            BankAccount();
            void Deposit(int amount);
            int Widraw(int amount);
            int GetBalance();
    };

    BankAccount::BankAccount(){
        balance = 0;
    }

    void BankAccount::Deposit(int amount){
        balance+=amount;
    }

    int BankAccount::Widraw(int amount){
        balance-=amount;
        return amount;
    }

    int BankAccount::GetBalance(){
        return balance;
    }
}

int main(){
    bnk::BankAccount account = bnk::BankAccount();
    std::cout << "Ballance: " << account.GetBalance() << ",-\n";

    account.Deposit(100);

    std::cout << "New Ballance: " << account.GetBalance() << ",-\n";
    return 0;
}
