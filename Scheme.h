#pragma once
#include<string>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>
#include <stdexcept> 
#include <string>
using namespace std;

class Scheme : vector<string> {

private:

 

public:
  //inheritance
  //sheme = headers
  // Scheme(vector<string> names) : vector<string>(names) { }
  vector<string> names;
  //delegation
  Scheme(vector<string> names) : names(names) { }

  Scheme() {}

  unsigned size() const {
    return names.size();
  }

  void push_back(string parameter) {
    names.push_back(parameter);
  }

  const string& at(int index) const {
    return names.at(index);
  }
  
  
  // TODO: add more delegation functions as needed
  vector<string> getScheme() {
    return names;
  }

};