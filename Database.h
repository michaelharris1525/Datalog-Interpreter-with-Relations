#pragma once
#include <iostream>
// #include "interpreter.h"
// #include "parser.h"
// #include "Tuple.h"
#include "Relation.h"
#include<string>
#include <cctype>
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;





class Database {

private:
    //think of RELATIONS as "TABLES"
    //TUPLES are FACTS (or ROWS)
    map<string, Relation> relations;
    

public:
    Database(){}
     
    // int return_size(Relation relationName) {
    //     int size;
    //     // cout << "relations size" << relations.size() << " " <<endl;
    //     // cout << "tuples size" << relationName.tuples_size() << endl;
    //     map<string, Relation>::iterator it;
    //     for(it = relations.begin(); it != relations.end(); it++) {
    //         for(Tuple tuple: relationName.r_getTuples()){
    //         Relation rel_look = it -> second; 
    //         for(Tuple tuple: rel_look.r_getTuples()) {
    //             size++;
    //         }
    //     }
        
    //     return size;
    // }

    void ADD_Relation(Relation newRelation){
        //Relation is already created, so add ROW(name, item) to map
        //for loop for how big the maps is? maybe
        this->relations.insert({newRelation.getName(), newRelation});
        //relations[newRelation.getName()] = newRelation;
    }

    void i_ADD_Relation(Relation newRelation){
        //Relation is already created, so add ROW(name, item) to map
        //for loop for how big the maps is? maybe
        // for(Tuple tuple : newRelation.r_getTuples()) {
            this->relations[newRelation.getName()] = newRelation;
            // this->relations[newRelation.getName()].addTuple(tuple);
        // }
    }
    bool ji_ADD_Relation(Relation newRelation, Scheme scheme){
        //Relation is already created, so add ROW(name, item) to map
        //for loop for how big the maps is? maybe
        bool changes;
        int rel_size = this->relations[newRelation.getName()].r_getTuples().size();
        for(Tuple tuple : newRelation.r_getTuples()) {
            this->relations[newRelation.getName()].addTuplePrint(tuple, scheme);
            // cout << relations.at(newRelation.getName()).toString() << endl;
        }
        if(rel_size != this->relations[newRelation.getName()].r_getTuples().size()) {
            changes = true;
        }
        else {
            changes = false;
        }
        return changes;

        // cout << "inside database" << endl;
        // cout << relations.at(newRelation.getName()).toString() << endl;
        
    }
    Relation& GetRelation(string relationName) {
        return this->relations[relationName];
    }
    Relation GetRelationCopy(string relationName) {
        return this->relations[relationName];
    }
    // Relation& GetRelation(string relationName) {
    //     return this->relations.at(relationName);
    // }
    // Relation GetRelationCopy(string relationName) {
    //     return this->relations.at(relationName);
    // }
    // to get the rows of tuples and its name 
    
    //This is wrong needs to be fixed :(
    Relation& GetTuple(string name, string parameters) {
        return this->relations[name, parameters];
        
    }
   
    const map<string, Relation>& a_getRelations() const {
        return relations;
    }
    
    
    
    //look up making an object, speaking of relation, make a constructor that takes a relation
    //predicate.name (name that points to a relation)


};