// #pragma once
#include "Scheme.h"
#include "Tuple.h"
#include<string>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>
// #include <stdexcept> 
// #include <ostream>
#include <string>
#include <sstream>
// #include <map>
using namespace std;

class Relation {

 private:

  string name;
  Scheme scheme;
  set<Tuple> tuples;

 public:
  //example: Trainer("squirtle","Ivey","Char");
    Relation(const string& name, const Scheme& scheme)
      : name(name), scheme(scheme) { }

    Relation(const Scheme& scheme)
      : scheme(scheme) { }

    Relation() {}
    Relation(const string& name, Scheme& scheme, set<Tuple> tuples)
      : name(name), scheme(scheme), tuples(tuples) { }
    // void print_variables() {
    //   cout << " =" << << <<"= " << <<endl;
    // }
    int tuples_size() {
      return tuples.size();
    }

    bool hasTuples() const {
      return !tuples.empty();
    }
    void setname(string name1) 
    {
      name = name1;
    }
    set<Tuple> r_getTuples() {
      return tuples;
    }
    Scheme getS(){
      return scheme;
    }

  //should I make a getTuple function here instead?
    void addTuplePrint(Tuple tuple, Scheme scheme) {
      
      if(tuples.insert(tuple).second) {
          cout << "  " << tuple.toString(scheme) << endl;
      }


    }

    
    void addTuple(Tuple tuple) {
      tuples.insert(tuple);
    }

    string getName() const {
      return name;
    }

    string eval_toString() const {
    stringstream out;
      for (const auto& tuple : tuples) {
        out << "   " << tuple.toString(scheme) << endl;
      }
      // add code to print the Tuples, one per line
      return out.str();
    }

    string toString() const {
    stringstream out;
      for (const auto& tuple : tuples) {
        out << tuple.toString(scheme) << endl;
      }
      // add code to print the Tuples, one per line
      return out.str();
    }

    string new_toString() const {
    stringstream out;
      for (const auto& tuple : tuples) {
        out << "  " << tuple.toString(scheme) << endl;
      }
      // add code to print the Tuples, one per line
      return out.str();
    }
    //type 1 select
    Relation select(int index, const string& value) const {
        Relation result(name, scheme);
        for(const Tuple& tuple: tuples) {
            if(tuple.at(index) == value){
              result.addTuple(tuple);
            }
        }
        // add tuples to the result if they meet the condition
        return result;
    }
  //type 2 select X, X (give it 2 indexes), go through each row/tuple and 
  // if === you add them
    Relation select_2(int index, int index2) {
      Relation result(name, scheme);
      for(const Tuple& tuple: tuples) {
        //if tuples are the same at same index
        if(tuple.at(index) == tuple.at(index2)) {
          result.addTuple(tuple);
        }
      }
      return result;
    }


  //make project function
    Relation project(vector<int> list_columns) {
      vector<string> temp_schemes;
      //how to call default constructor and set vector or parameters of constructor
      Scheme new_scheme(temp_schemes);
      for(auto index : list_columns) {
        //schemes/title headers
        //add the header of that index to the new one
        new_scheme.push_back(this->scheme.names.at(index));
        // result.addScheme_pushback(scheme.at(index));
      }
      Relation result(name, new_scheme);
      for(const auto& tuple: tuples) {
        vector<string> new_row;
        for(auto index : list_columns) {
          new_row.push_back(tuple.at(index));
          // tuple_row.at(index).insert()
        }
        result.addTuple(Tuple(new_row));
      }

      return result;
    }
    Relation Union(Relation& new_relation) {
      Relation& oldone = *this;
      Relation newR = oldone;
      set<Tuple> tuplesold = oldone.r_getTuples();
      set<Tuple> tuplesnew = new_relation.r_getTuples();

      
      for(Tuple tuple : tuplesnew) {
        vector<string>newtuplestring = tuple.f_getTuple();
        int iterator = 0;
        for(Tuple oldtuple: tuplesold) {
          vector<string>tuplestring = oldtuple.f_getTuple();
          newR.addTuple(tuple);
          if(tuplestring == newtuplestring){
            //print
            // Unionprint(newtuplestring[iterator]);
            // cout << "tupple string" << tuplestring << endl;
            // cout << "newtuplestring" << newtuplestring << endl;

          }
          iterator++;
          
        }
      }
      return newR;
    }

    void Unionprint(string String) {
      cout << "Union: " << String << endl;
    }

 //make re-name function
    Relation rename(Scheme new_header) {
      scheme = new_header;
      return Relation(name, new_header, tuples);
    }

    string print_relation() const {
      return toString();
    }

  //Join 2 relations, testing to see if 2 tuples are joinable
    static bool joinable(Scheme& leftScheme, Scheme& rightScheme, 
    const Tuple& leftTuple, const Tuple& rightTuple) {
      for (unsigned leftIndex = 0; leftIndex < leftScheme.size(); leftIndex++) {
        const string& leftName = leftScheme.at(leftIndex);
        const string& leftValue = leftTuple.at(leftIndex);        
        // cout << "left name: " << leftName << " value: " << leftValue << endl;

        //right side
        for (unsigned rightIndex = 0; rightIndex < rightScheme.size(); rightIndex++) {
          const string& rightName = rightScheme.at(rightIndex);
          const string& rightvalue = rightTuple.at(rightIndex);
          // cout << "right name: " << rightName << " value: " << rightvalue << endl;
          if(leftName == rightName) {
            if(leftValue != rightvalue) {
              return false;
            }
          }
        }

      }
      // add code to test whether the tuples are joinable
      // cout << "it returned false successfully\n";
      return true;  }

  Relation join(const Relation& right) {
        const Relation& left = *this;
        Relation result; 

        for(Tuple tuple: left.tuples) {
          cout << "left tuple: " << tuple.toString(left.scheme) << endl;
          for(Tuple tuple: right.tuples) {
            cout << "right tuple: " << tuple.toString(right.scheme) << endl;
          }
        }
      
}

Relation join_but_again(Relation &right) {
  Relation& left = *this;
  Relation result;
  vector<int> l_indices; 
  vector<int> r_indices;
  
  //get scheme of left name and right name
  Scheme s1 = left.getS();
  Scheme s2 = right.getS();
  Scheme combined_scheme = join_schemes(s1,s2, l_indices, r_indices);
  Relation r(combined_scheme);
  for(Tuple ltuple: left.tuples) {
    for(Tuple rtuple: right.tuples) {
      if(joinable(s1,s2, ltuple, rtuple)) {
        // cout << "ltuple " << ltuple.toString(s1) << "rtuple: " << rtuple.toString(s2) << endl;
        Tuple new_tuple = join_tuples(s1, s2, ltuple, rtuple,l_indices,r_indices);
        r.addTuple(new_tuple);
      }
      
      // cout << "ltuple " << ltuple.toString(s1) << "rtuple: " << rtuple.toString(s2) << endl;

    }

  }
  return r;
  
}

Scheme join_schemes(Scheme &left, Scheme &right, 
vector<int>& l_indices, vector<int>& r_indices) {
  vector<string> v_left = left.getScheme(); 
  vector<string> v_right = right.getScheme();
  vector<string> combined;

  for(string name: v_left) {
    combined.push_back(name);
  }
  for(int i = 0; i < v_right.size(); i++) {
    bool f_same = false;
    for(int j = 0; j < v_left.size(); j++){
      if(v_left[j] == v_right[i]) {
        //save info for where they are the same
        l_indices.push_back(j);
        r_indices.push_back(i);
        f_same = true;
      }
    }
    if(f_same == false) {
      combined.push_back(v_right.at(i));
    }
  }
  for (auto j : combined) {
    // cout << " THIS IS JOIN FUNITON " << j << endl;
  }
  Scheme Result(combined);
  return Result;
}

Tuple join_tuples(Scheme s1, Scheme s2, Tuple left, Tuple right, vector<int> left_i, vector<int> right_i) {
  vector<string> v_left = s1.getScheme(); 
  vector<string> v_right = s2.getScheme();
  vector<string> combined;
  //tuple values 
  for(string name: left.f_getTuple()) {
    combined.push_back(name);
  }
  
  for(int i = 0; i < v_right.size(); i++) {
    bool f_same = false;
    for(int j = 0; j < v_left.size(); j++){
      if(v_left[j] == v_right[i]) {
        //save info for where they are the same
        f_same = true;
      }
    }
    if(f_same == false) {
      combined.push_back(right.f_getTuple().at(i));
    }
  }
  Tuple Result(combined);
  return Result;
}



};

