#include <map>
#include "Node.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include<stack>
#pragma once 

using namespace std;




class Graph {

 private:
  vector<int> postorder;
  vector<int> reverse_postorder;

  vector<Node> v_holds_current_nodes;

  //made a new map since nodes somehow got corrupted
  map<int,Node>new_nodes;
  map<int,Node> nodes;
  map<int,Node>reverse_nodes;

 public:

  Graph(){};

    //start of helper functions
    bool check_if_dependent_nodes(int node_id){
        Node node = nodes[node_id];
        set<int> adj_node_forw = node.adjacentNodeIDs;
        if(adj_node_forw.count(node_id) > 0){
            return true;
        }
        else{
            return false;
        }
}

    void set_new_nodes(map<int, Node> nodes) {
        new_nodes = nodes;
    }
    void push_vector_nodes(vector<Node> push) {
        for(int i = 0; i < push.size(); i++) {
          v_holds_current_nodes.push_back(push[i]);
        }
    }

    //gets size of graph to add to it, made in make graph
      Graph(int size) {
        for (int nodeID = 0; nodeID < size; nodeID++){
          nodes[nodeID] = Node();
          reverse_nodes[nodeID] = Node();
        }
      }

      //add id to node in its class
      void addtonodeid(int val) {
          nodes[val].add_id(val);
      }
      //add reverse nodes ids also in node
        void reverseaddtonodeid(int val) {
            reverse_nodes[val].add_id(val);
        }

  void addEdge(int fromNodeID, int toNodeID) {
    nodes[fromNodeID].addEdge(toNodeID);
  }

  void build_reverse_edges(int toNodeID, int fromNodeID){
      reverse_nodes[fromNodeID].reverse_addEdge(toNodeID);
  }

  void toString() {
    // stringstream result;
    for (auto& pair : nodes) {
        int nodeId = pair.first;
        Node node = pair.second;
        cout << "R" << nodeId << ":";
        node.G_toString();
        cout << endl;
    }

  }

  //end of helper functions


  //start of DFS to grab postorder

    vector<set<int>> dfsForest() {
        set_new_nodes(nodes);
        //new local variables
        vector<int> node_id_post_order;
        //local variables
        set<int> get_SCC;
        vector<set<int>> v_SCC;
        stack<int> indices_Node_ints;
        vector<int> iterator_with_nodes_PO;
        //grab all the nodes
        vector<Node> v_nodes;
        vector<int> post_order_values_need_to_reverse;
        int iterator_value_of_post_order = 1;
        int new_iterator_value_of_post_order = 1;

        //grabs all Nodes
        for (auto &pair: nodes) {
            int nodeId = pair.first;
            Node node = pair.second;
            v_nodes.push_back(node);
        }

        //grab all nodes into private since I'm tired of remaking for loop
        push_vector_nodes(v_nodes);


        //start
        set<int>no_duplicates;
        // for each node y that is adjacent to node x
        //problem starts here, need to figure out a way to get nodeIDS efficiently and pass it to the map to get Node and use Real_dfs with that Node
        for(int i = 0; i < reverse_nodes.size(); i++) {
            Node node = reverse_nodes[i];
            int nodeId = node.get_new_id();
            if(node.get_truth() == false) {
                real_dfs(node, nodeId, indices_Node_ints, no_duplicates);

            }
        }




        //Need to reset all nodes to false again, just in case
        for(Node node: v_nodes) {
            node.reset_all_nodes_to_false();
            for(int i = 0; i < v_nodes.size(); i++){
                reverse_nodes[i] = node;
            }
        }


        //Now DFS again but Forward
        while(!indices_Node_ints.empty()) {
            //indices_Node_ints is my stack for all the node Id's
            int Id_from_lifo =  indices_Node_ints.top();
            indices_Node_ints.pop();
            Node node_from_top = new_nodes[Id_from_lifo];
            if(!node_from_top.get_truth()) {
                real_dfs_forw(node_from_top, Id_from_lifo, v_SCC, get_SCC, indices_Node_ints);
                if(!get_SCC.empty()) {
                    v_SCC.push_back(get_SCC);
                }
                get_SCC.clear();
            }
        }
        // }
        //print out SCC

        Node node_for_SCC;

        return v_SCC;



    }


 //basic DFS
 //reverse_map
  void real_dfs(Node& x, int access_graph_map, stack<int>& stack_node_ids, set<int>&no_duplicates) {
      //mark node visited
      x.marked();
      reverse_nodes[access_graph_map] = x;

      //iterate through map to get correct Nodes to use

      //set local variables, gets all nodes and gets node_Id's of that one node
      vector<Node> v_nodes;
      set<int> adj_nodes = x.reverse_adjacent_NodeIDS;
      int grab_node_id;
      //grab the child of the node
      for (int pair : adj_nodes) {
          int nodeId = pair;
          Node node_that_i_want = reverse_nodes[nodeId];
          v_nodes.push_back(node_that_i_want);
          //grab Node Indice to know where they are for PO
          grab_node_id = pair;
          
          //check to see if Node has been marked, if not pass through
          if(node_that_i_want.get_truth() == false) {
              //marks for post order of values that have been visited, reverse later in order to do the forward way
              real_dfs(node_that_i_want, nodeId, stack_node_ids, no_duplicates);
          }
      }
      //make a set to contain when id or node ends, store it into an integer and add it to stack if it is not in the set
      //checks to see if the id is in duplicates, if not add it
      if(no_duplicates.count(access_graph_map) == 0){
          //insert the id in the set
          no_duplicates.insert(access_graph_map);
          //push the id into the stack
          stack_node_ids.push(access_graph_map);
      }
      

  }


//SCC DFS
void real_dfs_forw(Node x, int access_graph_map, vector<set<int>>& v_SCC, set<int>& get_SCC, stack<int>& stack_node_ids) {
    //mark node visited
    x.marked();
    new_nodes[access_graph_map] = x;
    get_SCC.insert(access_graph_map);

    //iterate through map to get correct Nodes to us
    //set local variables, gets all nodes and gets node_Id's of that one node
    vector<Node> v_nodes;
    set<int> adj_nodes = x.adjacentNodeIDs;
    int grab_node_id;
    if(adj_nodes.size() > 0) {
        //grab the child of the node
        for (int pair : adj_nodes) {
            int nodeId = pair;
            Node node_that_i_want = new_nodes[nodeId];
            v_nodes.push_back(node_that_i_want);
            //grab Node Indice to know where they are for PO
            grab_node_id = pair;

            //check to see if Node has been marked, if not pass through
            if(!node_that_i_want.get_truth()) {
                //marks for post order of values that have been visited, reverse later in order to do the forward way
                real_dfs_forw(node_that_i_want, nodeId, v_SCC, get_SCC, stack_node_ids);
            }
        }
    }

}



};


















//DFS FORWARD
//  void dfs_forw(Node x, int access_graph_map, vector<int> reverse_po,
//  int&iterator_val_of_post_order, vector<set<int>>& v_SCC, set<int>& get_SCC) {
//     //mark node visited
//      x.marked();
//      nodes[access_graph_map] = x;
//
//      //set local variables, gets all nodes and gets node_Id's of that one node
//      vector<Node> v_nodes;
//      set<int> adj_nodes = x.adjacentNodeIDs;
//      int grab_node_id;
//      Node grab_node;
//
//
//      //grab the child of the node
//      for (int pair : adj_nodes) {
//          int nodeId = pair;
//          Node node_that_i_want = nodes[nodeId];
//          v_nodes.push_back(node_that_i_want);
//          grab_node_id = nodeId;
//          grab_node = node_that_i_want;
//
//          //check to see if Node has been marked, if not pass through
//          if(!node_that_i_want.get_truth()) {
//              //search for the child of the child, you will go through all adj_nodes and then create SCC
//              dfs_forw(node_that_i_want, nodeId, reverse_po, iterator_val_of_post_order, v_SCC, get_SCC);
//              get_SCC.insert(grab_node_id);
//          }
//
//        }
//        //push finished SCC value after end of iteration
//        v_SCC.push_back(get_SCC);
//        get_SCC.clear();
//    }
