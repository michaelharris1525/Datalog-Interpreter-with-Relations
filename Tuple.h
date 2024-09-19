#pragma once
#include "Scheme.h"
#include<string>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>
#include <stdexcept> 
#include <ostream>
#include <string>
#include <sstream>
using namespace std;

class Tuple {

private:

  vector<string> values;

public:
    //inheritance
    Tuple(){}
   

    //delegation
    Tuple(vector<string> values) : values(values) { }

    unsigned size() const {
        return values.size();
    }

    const string& at(int index) const {
        return values.at(index);
    }

    bool operator<(const Tuple t) const {
        return values < t.values;
    }
    vector<string> f_getTuple() {
        return values;
    }

    string toString(const Scheme& scheme) const {
        const Tuple& tuple = *this;
        stringstream out;
        // fix the code to print "name=value" pairs
        
        // out << scheme.size(); // out << tuple.size();
        for(size_t i = 0; i < scheme.size(); i++) {
            out << scheme.at(i) << "="; 
            out << tuple.at(i);
            if(i + 1 < scheme.size()){
                out << ", ";
            }
        } 
        return out.str();
    }
    void push_back(string parameter) {
        values.push_back(parameter);
    }
   
};


   