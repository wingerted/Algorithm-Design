#include "BigNumber.h"


BigNumber::BigNumber(int in_base)
{
}

BigNumber::~BigNumber(void)
{
}

istream& operator>> (istream& in, BigNumber& big_num) {
  string word;

  in >> word;
  string::iterator iter = word.end() - 1;

  for (; iter!=word.begin(); --iter) {
    big_num.num.push_back(*iter-'0');
  }

  big_num.num.push_back(*iter-'0');

  return in;
}

ostream& operator<< (ostream& os, const BigNumber& big_num) {
  vector<int>::const_iterator iter = big_num.num.end() - 1;
  for (; iter!=big_num.num.begin(); --iter) {
    os << *iter;
  }
  os << *iter;

  return os;
}

BigNumber operator+ (const BigNumber &a, const BigNumber &b) {
  BigNumber result;
  int carry = 0;
  vector<int>::const_iterator a_iter=a.num.begin();
  vector<int>::const_iterator b_iter=b.num.begin();

  for (; a_iter!=a.num.end() && b_iter!=b.num.end(); ++a_iter, ++b_iter) {
    carry += *a_iter + *b_iter;
    result.num.push_back(carry % 10);
    carry /= 10;
  }

  if (a_iter == a.num.end()) {
    while (b_iter != b.num.end()) {
      carry +=  *b_iter;
      result.num.push_back(carry % 10);
      carry /= 10;
      ++b_iter;
    }
  } else if (b_iter == b.num.end()){
    while (a_iter != a.num.end()) {
      carry +=  *a_iter;
      result.num.push_back(carry % 10);
      carry /= 10;
      ++a_iter;
    }
  } 
    
  while (carry != 0) {
      result.num.push_back(carry % 10);
      carry /= 10;
  }

  while (result.num.back()==0 && result.num.size()!=1) {
      result.num.pop_back();
  }

  return result;
}

BigNumber operator- (const BigNumber &a, const BigNumber &b) {
  BigNumber result;
  int borrow = 0;
  vector<int>::const_iterator a_iter=a.num.begin();
  vector<int>::const_iterator b_iter=b.num.begin();

  for (; a_iter!=a.num.end() && b_iter!=b.num.end(); ++a_iter, ++b_iter) {
    result.num.push_back(*a_iter - *b_iter - borrow);
    if (result.num.back() < 0) {
      borrow = 1;
      result.num.back() += 10;
    } else {
      borrow = 0;
    }
  }

  if (a_iter == a.num.end()) {
    while (b_iter != b.num.end()) {
      result.num.push_back(*b_iter - borrow);
      if (result.num.back() < 0) {
        borrow = 1;
        result.num.back() += 10;
      } else {
        borrow = 0;
      }
      ++b_iter;
    }
  } else if (b_iter == b.num.end()){
   while (a_iter != a.num.end()) {
      result.num.push_back(*a_iter - borrow);
      if (result.num.back() < 0) {
        borrow = 1;
        result.num.back() += 10;
      } else {
        borrow = 0;
      }
      ++a_iter;
    }
  } 
    
  while (result.num.back()==0 && result.num.size()!=1) {
      result.num.pop_back();
  }

  return result;
}

BigNumber operator* (const BigNumber &a, const BigNumber &b) {
  BigNumber result;
  result.num.resize(a.num.size()+b.num.size());

  int carry = 0;

  for (int j=0; j!=a.num.size(); ++j) {
    for (int i=0; i!=b.num.size(); ++i) {
      result.num[i+j] += b.num[i] * a.num[j] + carry;
      carry = result.num[i+j] / 10;
      result.num[i+j] %= 10;
    }

    while (carry != 0) {
      result.num.push_back(carry % 10);
      carry /= 10;
    }
  }

  while (result.num.back()==0 && result.num.size()!=1) {
      result.num.pop_back();
  }

  return result;
}

