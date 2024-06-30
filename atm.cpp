#include "ATM.h"
#include <iostream>

Account::Account(const std::string& accNumber, const std::string& pin, double balance, const std::string& aadhar)
    : accountNumber(accNumber), pin(pin), balance(balance), aadhar(aadhar) {}

std::string Account::getAccountNumber() const {
    return accountNumber;
}

bool Account::validatePIN(const std::string& pin) const {
    return this->pin == pin;
}

std::string Account::getAadhar() const {
    return aadhar;
}

double Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    balance += amount;
}

bool Account::withdraw(double amount) {
    if (amount > balance) return false;
    balance -= amount;
    return true;
}

ATM::ATM() : loggedInAccount(nullptr) {}

void ATM::createAccount(const std::string& accNumber, const std::string& pin, double initialBalance, const std::string& aadhar) {
    if (accounts.find(accNumber) == accounts.end()) {
        accounts.emplace(accNumber, Account(accNumber, pin, initialBalance, aadhar));
        std::cout << "Account created successfully!\n";
    } else {
        std::cout << "Account already exists.\n";
    }
}

void ATM::login(const std::string& accNumber, const std::string& pin) {
    auto it = accounts.find(accNumber);
    if (it != accounts.end() && it->second.validatePIN(pin)) {
        loggedInAccount = &it->second;
        std::cout << "Logged in successfully!\n";
    } else {
        std::cout << "Invalid account number or PIN.\n";
    }
}

void ATM::logout() {
    loggedInAccount = nullptr;
    std::cout << "Logged out successfully!\n";
}

void ATM::checkBalance() const {
    if (loggedInAccount) {
        std::cout << "Current balance: " << loggedInAccount->getBalance() << " INR\n";
    } else {
        std::cout << "No account logged in.\n";
    }
}

void ATM::deposit(double amount) {
    if (loggedInAccount) {
        loggedInAccount->deposit(amount);
        std::cout << "Deposit successful! New balance: " << loggedInAccount->getBalance() << " INR\n";
    } else {
        std::cout << "No account logged in.\n";
    }
}

void ATM::withdraw(double amount) {
    if (loggedInAccount) {
        if (loggedInAccount->withdraw(amount)) {
            std::cout << "Withdrawal successful! New balance: " << loggedInAccount->getBalance() << " INR\n";
        } else {
            std::cout << "Insufficient funds.\n";
        }
    } else {
        std::cout << "No account logged in.\n";
    }
}

void ATM::transfer(const std::string& toAccNumber, double amount) {
    if (loggedInAccount) {
        auto it = accounts.find(toAccNumber);
        if (it != accounts.end()) {
            if (loggedInAccount->withdraw(amount)) {
                it->second.deposit(amount);
                std::cout << "Transfer successful! New balance: " << loggedInAccount->getBalance() << " INR\n";
            } else {
                std::cout << "Insufficient funds.\n";
            }
        } else {
            std::cout << "Target account not found.\n";
        }
    } else {
        std::cout << "No account logged in.\n";
    }
}
