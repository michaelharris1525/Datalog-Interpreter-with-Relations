#include <vector>
#include <set>
#include <stdexcept> 
#include <string>
#include <iostream>
#include <sstream>
#include "parser.h"
#pragma once 

using namespace std;

// A Node holds a 'set' of adjacent node IDs. 
// Each node ID in the set represents an edge in the graph. 
// Node IDs are added to the set by calling the 'addEdge' function. 
// (You may want add other variables to your Node class later, 
// perhaps a visited flag or a post-order number.)

class Node {

 private:

  // set<int> adjacentNodeIDs;
 
  bool true_false_marked = false;
  int id;
  vector<Node> v_holds_current_nodes;

 public:

    set<int> adjacentNodeIDs;
    set<int>reverse_adjacent_NodeIDS;


    void add_id(int val) {
        id = val;
    }
    
void push_vector_nodes(vector<Node> push) {
    for(int i = 0; i < push.size(); i++) {
      v_holds_current_nodes.push_back(push[i]);
    }
  }
 void reset_all_nodes_to_false() {
  true_false_marked = false;
 }

  int get_new_id() {
    return id;
  }
  void post_order_id(int new_id) {
    id = new_id;
  }


  bool get_truth() {
    return true_false_marked;
  }
  void marked() {
    true_false_marked = true;
  }
  void addEdge(int adjacentNodeID) {
    adjacentNodeIDs.insert(adjacentNodeID);
  }
  void reverse_addEdge(int adjacentNodeID) {
    reverse_adjacent_NodeIDS.insert(adjacentNodeID);
  }

//to string used to output and used in the graph.h file
  void G_toString() {
    auto it = adjacentNodeIDs.begin();
    auto last = adjacentNodeIDs.end();
    if(adjacentNodeIDs.size() != 0) {
        --last;
    }
    for(int value : adjacentNodeIDs) {
      cout << "R" << value;
      if(it != last) {
        cout << ",";
      }
      ++it;
    }
  }
  
  void insert(int element) {
    adjacentNodeIDs.insert(element);
  }

//normal to string for nodes
  string toString () {
    stringstream out;
    auto it = adjacentNodeIDs.begin();
    auto last = adjacentNodeIDs.end();
    --last;
    for(int value : adjacentNodeIDs) {
      out << "R" << value;
      if(it != last) {
        out << ",";
      }
      ++it;
    }
    return out.str();
  }

 

};