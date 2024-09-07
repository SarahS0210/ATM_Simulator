// DO NOT CHANGE THIS FILE
#ifndef TRANSACTION_STACK_H
#define TRANSACTION_STACK_H

#include <iostream>
#include <string>
using namespace std;

struct Transaction {
  string transaction_type; // Either deposit or withdraw
  double amount;           // The amount for the related deposit or withdraw
  Transaction *under;      // Point to the object in the stack under the current one
};

class TransactionStack {
private:
  Transaction *top_;

public:
  TransactionStack();
  ~TransactionStack();

  Transaction *top() const;
  void push(const string &, double);
  void pop();

  friend ostream &operator<<(ostream &, const TransactionStack &);
};
#endif