#include <iostream>
#include "scanner.h"
#include "parser.h"
#include "Interpreter.h"
#include <vector>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <map>
#include "Graph.h"

int main(int argc, char* argv[]) {

   //testing with files
   //Read the contents of the input file into a string
    ifstream inFile(argv[1]);
    /*int number_tokens = 0;*/
    stringstream buffer;
    buffer << inFile.rdbuf();
    string input = buffer.str();

    // Close the input file
    inFile.close();
    
    // Create a Scanner object and scan the input string
    //definitely need this *
     Scanner scanner(input);
     vector<Token> tokens = scanner.scanToken();
     vector<Token> notTokens;
     for (size_t i = 0; i < tokens.size(); i++) {
         if (tokens.at(i).getType() != COMMENT) {
          notTokens.push_back(tokens[i]);
         }
     }
         

    // // Output the scanned tokens
    // for (const Token& token : tokens) {
    //     cout << token.toString() << endl;
    //     number_tokens++;
    // }
    // cout << "Total Tokens = " << number_tokens << endl;




//Parsing all tokens, need this *
    Parser p = Parser(notTokens);
    p.parse();

   
//inter object created from database that contains everything. *
    interp object_hold_data = interp (p.get_datalogProgram());
    

    object_hold_data.i_schemes();
    object_hold_data.i_facts();
    object_hold_data.i_rules();
    object_hold_data.i_queries();


//Node practice
    // Node node;
    // node.addEdge(4);
    // node.addEdge(8);
    // node.addEdge(2);
    // cout << node.toString() << endl;
    
    // Graph graph(3);
    // graph.addEdge(1,2);
    // graph.addEdge(1,0);
    // graph.addEdge(0,1);
    // graph.addEdge(1,1);
    // graph.toString();
     // predicate names for fake rules
  // first is name for head predicate
  // second is names for body predicates
  // pair<string,vector<string>> ruleNames[] = {
  //   { "A", { "B" } },
  //   { "B", { "B", "A" } },
  // };

  // vector<c_Rules> rules;

// predicate names for fake rules
  // first is name for head predicate
  //second is names for body predicates
  // pair<string,vector<string>> ruleNames[] = {
  //   { "Alpha", { "Bravo" } },
  //   { "Bravo", { "Bravo", "Alpha" }},
  //   {"Charlie",{"Delta"}},
  //   {"Delta", {"Charlie"}},
  //   {"Delta", {"Echo"}}
  // };
  //  pair<string,vector<string>> ruleNames[] = {
  //          { "A", { "B" } }, //A :- B these 2 will be joined (B will be added after 1 iteration of the while loop and A will add new stuff from B that was added with A)
  //          { "B", { "B", "A" } },// point of graph is to find  those dependencies (see if the BP = HP)
  //  };

  // vector<c_Rules> rules;
  // for (auto& rulePair : ruleNames) {
  //   string headName = rulePair.first;
  //   c_Rules rule = c_Rules(c_Predicate(headName));
  //   vector<string> bodyNames = rulePair.second;
  //   for (auto& bodyName : bodyNames) {
  //     rule.addBodyPredicate(c_Predicate(bodyName));
  //   }
  //   rules.push_back(rule);
  // };
  
  // Graph graph = interp::makeGraph(rules);
  // graph.toString();

  // graph.dfsForest();
  // graph.print_reverse_po_vals();
  return 0;


}