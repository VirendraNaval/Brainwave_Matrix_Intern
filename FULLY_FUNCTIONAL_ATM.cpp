#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class Account {
public:
    Account(string accountNumber, string pin, double balance)
        : accountNumber(accountNumber), pin(pin), balance(balance) {}

    bool verifyPin(const string& enteredPin) const {
        return enteredPin == pin;
    }

    double getBalance() const {
        return balance;
    }

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }

    void deposit(double amount) {
        balance += amount;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    void transfer(Account& recipient, double amount) {
        if (withdraw(amount)) {
            recipient.deposit(amount);
            cout << "Transfer successful! New balance: " << balance << " INR\n";
        } else {
            cout << "Insufficient balance for transfer.\n";
        }
    }

private:
    string accountNumber;
    string pin;
    double balance;
};

class ATM {
public:
    void createAccount() {
        string accountNumber, pin, aadharNumber;
        double initialBalance;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter PIN: ";
        cin >> pin;
        cout << "Enter initial balance: ";
        cin >> initialBalance;
        cout << "Enter Aadhar number: ";
        cin >> aadharNumber;

        accounts.emplace(accountNumber, Account(accountNumber, pin, initialBalance));
        cout << "Account created successfully!\n";
    }

    bool login() {
        string accountNumber, pin;

        cout << "Enter account number: ";
        cin >> accountNumber;
        cout << "Enter PIN: ";
        cin >> pin;

        auto it = accounts.find(accountNumber);
        if (it != accounts.end() && it->second.verifyPin(pin)) {
            currentAccount = &it->second;
            cout << "Logged in successfully!\n";
            return true;
        } else {
            cout << "Authentication failed. Please check your account number and PIN.\n";
            return false;
        }
    }

    void checkBalance() {
        if (currentAccount) {
            cout << "Current balance: " << currentAccount->getBalance() << " INR\n";
        } else {
            cout << "No account logged in.\n";
        }
    }

    void deposit() {
        if (currentAccount) {
            double amount;
            cout << "Enter deposit amount: ";
            cin >> amount;
            currentAccount->deposit(amount);
            cout << "Deposit successful! New balance: " << currentAccount->getBalance() << " INR\n";
        } else {
            cout << "No account logged in.\n";
        }
    }

    void withdraw() {
        if (currentAccount) {
            double amount;
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            if (currentAccount->withdraw(amount)) {
                cout << "Withdrawal successful! New balance: " << currentAccount->getBalance() << " INR\n";
            } else {
                cout << "Insufficient balance.\n";
            }
        } else {
            cout << "No account logged in.\n";
        }
    }

    void transfer() {
        if (currentAccount) {
            string targetAccountNumber;
            double amount;

            cout << "Enter target account number: ";
            cin >> targetAccountNumber;

            auto it = accounts.find(targetAccountNumber);
            if (it != accounts.end()) {
                cout << "Enter transfer amount: ";
                cin >> amount;
                currentAccount->transfer(it->second, amount);
            } else {
                cout << "Target account not found.\n";
            }
        } else {
            cout << "No account logged in.\n";
        }
    }

    void logout() {
        currentAccount = nullptr;
        cout << "Logged out successfully.\n";
    }

    void displayMenu() {
        int choice;
        do {
            cout << "\nATM Menu:\n";
            cout << "1. Create Account\n";
            cout << "2. Login\n";
            cout << "3. Check Balance\n";
            cout << "4. Deposit\n";
            cout << "5. Withdraw\n";
            cout << "6. Transfer\n";
            cout << "7. Logout\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    login();
                    break;
                case 3:
                    checkBalance();
                    break;
                case 4:
                    deposit();
                    break;
                case 5:
                    withdraw();
                    break;
                case 6:
                    transfer();
                    break;
                case 7:
                    logout();
                    break;
                case 8:
                    cout << "Thank you for using the ATM. Goodbye!\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 8);
    }

private:
    unordered_map<string, Account> accounts;
    Account* currentAccount = nullptr;
};

int main() {
    ATM atm;
    atm.displayMenu();
    return 0;
}
