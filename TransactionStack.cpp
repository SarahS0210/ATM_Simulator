#include <iostream>
#include <fstream>
#include "Account.h"
#include "TransactionStack.h"
using namespace std;

TransactionStack::TransactionStack(){
  top_ = nullptr;
}

TransactionStack::~TransactionStack(){
  cout << "Destructing" << endl;
  while(top_!=nullptr){
    cout << "now deleting " << top_->transaction_type << " $" << top_->amount << endl;
    this->pop();
  }
  cout << "All data deleted" << endl;
}

Transaction* TransactionStack::top() const{
  return top_;
}

void TransactionStack::push(const string &type, double amount){
  if(top_==nullptr){
  Transaction* transaction = new Transaction();
  transaction->transaction_type = type;
  transaction->amount = amount;
  top_ = transaction;
  }
  else{
    Transaction* transaction = new Transaction();
    transaction->transaction_type = type;
    transaction->amount = amount;
    transaction->under = top_;
    top_ = transaction;
  }
}

void TransactionStack::pop(){
  Transaction *temp;
  if(top_==nullptr){
  cout << "theres nothing in the stack" << endl;
  }
  Transaction *ptr = top_;
  top_ = ptr->under;
  delete ptr;
}

ostream& operator<<(ostream &out, const TransactionStack &stack){
  Transaction* current = stack.top_;
  while(current != nullptr) {
    out << current->transaction_type << endl;
    current = current->under;
  }
  return out;
}