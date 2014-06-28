#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BigNumber {
 public:
  BigNumber(int in_base = 10);
  ~BigNumber(void);
  friend istream& operator>> (istream& in, BigNumber& big_num);
  friend ostream& operator<< (ostream& in, const BigNumber& big_num);
  friend BigNumber operator+ (const BigNumber &a, const BigNumber &b);
  friend BigNumber operator- (const BigNumber &a, const BigNumber &b); //a > b
  friend BigNumber operator* (const BigNumber &a, const BigNumber &b);
 private:
  vector<int> num;
};

