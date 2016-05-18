//
//  stackcalc.cpp
//  CS253
//
//  Created by Jason Hu on 4/12/16.
//  Copyright © 2016 Jason Hu. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <sstream>

#include "stack.hpp"
#include "fraction.hpp"

using namespace std;

void processInput(std::string input, Stack_Impl<Fraction> & vec, Stack_Impl<Fraction> & memory, map<string, Fraction>&);
bool goodlabel(std::string possible_label);

int main(int argc, char ** argv){
    
    string input;
    Stack_Impl<Fraction> mem;
    map<string,Fraction> mapmem;
    
    /*
    for (int i=1; i<argc; i++){
        try {
            processInput(argv[i],vec, mem);
        }
        catch (int e){
            // Repeat
        }
    }
    */
    
    cout<<"Enter an expression: ";
    
    while (getline(cin, input)) {
        Stack_Impl<Fraction> vec;
        try{
            processInput(input,vec, mem, mapmem);
            
            if (vec.size()==1){
                cout<<"it is: "<<vec.top()<<endl;
            }
            else if (vec.size()==0){
                cout<<"No number on stack."<<endl;
                if (mem.size()==0){
                    cout<<"No saved numbers."<<endl;
                }
                else{
                    cout<<"Saved numbers are:"<<endl;
                    Stack_Impl<Fraction>::iterator nmptr=mem.begin();
                    while (nmptr!=mem.end()){
                        cout<<*nmptr++<<" ";
                    }
                    cout<<endl;
                }
                return 1;
            }
            else{
                cout<<"Not enough operators, operands left on stack are: ";
                Stack_Impl<Fraction>::iterator iter=vec.begin();
                while(iter !=vec.end()){
                    cout<<*iter++<<" ";
                }
                cout<<endl;
                if (mem.size()==0&&mapmem.size()==0){
                    cout<<"No saved numbers."<<endl;
                }
                else{
                    if (mapmem.size()==1&&mapmem.count("it")==1){
                        cout<<"No saved numbers."<<endl;
                    }
                    cout<<"Saved numbers are:"<<endl;
                    Stack_Impl<Fraction>::iterator nmptr=mem.begin();
                    while (nmptr!=mem.end()){
                        cout<<*nmptr++;
                    }
                    map<string,Fraction>::iterator iterfrac=mapmem.begin();
                    while (iterfrac!=mapmem.end()){
                        cout<<iterfrac->second;
                        iterfrac++;
                    }
                    cout<<endl;
                }
            }
            
            cout<<"Enter an expression: ";
        }
        catch (...){
            // repeat
            std::cout<<"Malformed Expression"<<endl;
            input="";
            cout<<"Enter an expression: ";
        }
    }
    return 0;
}



void processInput(string input, Stack_Impl<Fraction> & vec, Stack_Impl<Fraction> & mem, map<string, Fraction> &mapmem){
    istringstream ss (input);
    string substr;
    string operands="+-*/SR";

    while(ss >> substr){
        
        // if it is a fraction
        if (substr[0]=='('){
            // no nested brackets allowed
            vec.push(Fraction(substr));
        }
        // if it is not a fraction, a decimal number or an acceptable operand
        else if (operands.find(substr)!=string::npos){     // if input is found in the operands string
            
            // security check
            if (substr[1]!='\0') {
                throw std::invalid_argument("Invalid operand in the expression"); // e.g. operand is "+-"
            }
            
            // the operand must be length one:
            
            // deal with R and S
            if (substr[0]=='S'){
                if(vec.isEmpty()){
                    cout<<"No number to save."<<endl;
                    throw 68;
                }
                else{
                    string possible_label;
                    if (ss>>possible_label){
                        if (goodlabel(possible_label)){
                            // if it is a valid label
                            mapmem[possible_label]=vec.top();
                        }
                        else{
                            // if it is not a valid label
                            ss.putback(' ');
                            string::iterator itera =possible_label.begin();
                            while(itera != possible_label.end()){
                                ss.putback(*itera);
                            }
                            // pretend you did not see it, and treat it as if no label is necessary.
                            Fraction a = vec.top();
                            mem.push(a);
                        }
                    }
                    else{ //if there is nothing
                        Fraction a=vec.top();
                        mem.push(a);
                    }
                }
            }
            else if (substr[0]=='R'){
                string possible_label;
                if (ss>>possible_label){
                    if (goodlabel(possible_label)){
                        // if it is a valid label
                        vec.push(mapmem[possible_label]);
                    }
                    else{
                        // if it is not a valid label
                        ss.putback(' ');
                        string::iterator itera =possible_label.begin();
                        while(itera != possible_label.end()){
                            ss.putback(*itera);
                        }
                        // pretend you did not see it, and treat it as if no label is necessary.
                        Fraction a = vec.top();
                        mem.push(a);
                    }
                }
                else{ //if there is nothing
                    Fraction a=mem.top();
                    vec.push(a);
                }

            }
            else{  // if it's operator
                if(vec.isEmpty()){
                    throw invalid_argument("Too many operators.");
                }
                
                Fraction a=vec.top();
                vec.pop();
                
                
                if(vec.isEmpty()){
                    throw invalid_argument("Too many operators.");
                }
                
                Fraction b=vec.top();
                vec.pop();
                
                
                switch (substr[0]) {
                    case '+':
                        vec.push(b+a);
                        break;
                        
                    case '-':
                        vec.push(b-a);
                        break;
                        
                    case '*':
                        vec.push(b*a);
                        break;
                        
                    case '/':
                        vec.push(b/a);
                        break;
                        
                    default:
                        break;
                }
            }
        }
        // if it's a number
        else{
            try{
                double douba = stod(substr);
                vec.push(Fraction(douba));
            }
            catch (invalid_argument){
                cout<<"Not a number"<<endl;
                throw invalid_argument("Not a number.");
            }
            catch(out_of_range){
                throw std::out_of_range ("Boy the number is too big.");
            }
        }
    }
    if(vec.top().isNull())
        mapmem["it"]=vec.top().toFrac();
    else
        mapmem["it"]=vec.top();
    
}

bool goodlabel(std::string possible_label){
    bool flag=1;
    if (possible_label=="S") {
        flag=0;
    }
    else if (possible_label=="R") {
        flag=0;
    } else {
        string::iterator iter=possible_label.begin();
        while (iter!=possible_label.end()) {
            if (!isalpha(*iter)){
                flag=0;
            }
            iter++;
        }
    }
    
    return flag;
}