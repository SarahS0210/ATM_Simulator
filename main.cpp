#include "Account.h"
#include "TransactionStack.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
  string name, option;
  double amount = 0;
  TransactionStack undo, redo;
  fstream fin;
  fin.open("info.dat");
  cout << "enter your account name" << endl;
  getline(cin, name);
  Account user(name);
  cout << "Before processing any transactions, " << user;

  // opens file
  while (!fin.eof()) {
    fin >> option;
    // deposit
    if (option == "deposit") {
      fin >> amount;
      if (user.valid_deposit(amount)) {
        user += amount;
        undo.push("deposit", amount);
      } else {
        cout << "Transaction could not be completed. Please try again and "
                "enter a valid number"
             << endl;
      }
    }
    // withdrawl
    if (option == "withdrawl") {
      fin >> amount;
      if (user.valid_withdrawl(amount)) {
        user -= amount;
        undo.push("withdrawl", amount);
      } else {
        cout << "INSUFFICIENT FUNDS" << endl;
      }
    }
    // undo
    if (option == "undo") {
      if (undo.top() == nullptr) {
        cout << "There is nothing to undo" << endl;
      } else {
        if (undo.top()->transaction_type == "withdrawl") {
          user += undo.top()->amount;
          redo.push(undo.top()->transaction_type, undo.top()->amount);
          undo.pop();
        } else if (undo.top()->transaction_type == "deposit") {
          user -= undo.top()->amount;
          redo.push(undo.top()->transaction_type, undo.top()->amount);
          undo.pop();
        }
      }
    }
    // redo
    if (option == "redo") {
      if (redo.top() == nullptr) {
        cout << "There is nothing to redo" << endl;
      } else {
        if (redo.top()->transaction_type == "withdrawl") {
          user -= redo.top()->amount;
          undo.push(redo.top()->transaction_type, redo.top()->amount);
          redo.pop();
        } else if (redo.top()->transaction_type == "deposit") {
          user += redo.top()->amount;
          undo.push(redo.top()->transaction_type, redo.top()->amount);
          redo.pop();
        }
      }
    }
    fin.ignore();
    cout << "After processing " << option << " " << amount << " " << user;
  }
  cout << user;
  fin.close();
  return 0;
}