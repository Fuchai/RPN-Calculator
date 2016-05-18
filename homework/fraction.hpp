//
//  fraction.hpp
//  CS 253
//
//  Created by Jason Hu on 5/15/16.
//  Copyright © 2016 Jason Hu. All rights reserved.
//

#ifndef fraction_hpp
#define fraction_hpp
#include <math.h>

int gcd(int x, int y);


class Fraction{
public:
    Fraction(): top(0),bottom(0),doubl(0){};
    Fraction(int numerator, int denominator): top(numerator){
        if (denominator==0)
            throw std::domain_error("Zero cannot be in the denominator");
        else
            bottom=denominator;
    };
    Fraction(std::string bracket_enclosed){
        top=stoi(bracket_enclosed.substr(1,bracket_enclosed.find('/')));
        bottom=stoi(bracket_enclosed.substr(bracket_enclosed.find('/')+1,bracket_enclosed.length()-1));
    }
    Fraction(double number):doubl(number),top(0),bottom(0){};
    
    int numerator() const {return top;};
    int denominator() const {return bottom;};
    operator double() const {return top/bottom;};
    bool isNull(){return (bottom==0);}
    
    Fraction & toFrac(){
        int deci=100000000;
        int ggcd=gcd(floor(doubl*deci),deci);
        top=round(doubl*deci)/ggcd;
        bottom=deci/ggcd;
        return *this;
    }
    
    // operators overridden
    
    friend Fraction operator + (Fraction lhs, Fraction rhs);
    friend Fraction operator - (Fraction lhs, Fraction rhs);
    friend Fraction operator * (Fraction lhs, Fraction rhs);
    friend Fraction operator / (Fraction lhs, Fraction rhs);
    
    /*
     friend double operator + (Fraction lhs, double rhs);
     friend double operator - (Fraction lhs, double rhs);
     friend double operator + (double lhs,Fraction rhs);
     friend double operator - (double lhs, Fraction rhs);
     
     friend double operator * (double lhs, Fraction rhs);
     friend double operator / (double lhs, Fraction rhs);
     friend double operator * (Fraction lhs, double rhs);
     friend double operator / (Fraction lhs, double rhs);
     */
    
    friend std::ostream& operator <<(std::ostream& os, Fraction rhs);
    
private:
    int top;
    int bottom;
    double doubl;
};

Fraction operator + (Fraction lhs, Fraction rhs){
    if (lhs.isNull()){
        if (rhs.isNull()) {
            return Fraction(lhs.doubl+rhs.doubl);
        }
        else{
            return Fraction(lhs.doubl+rhs.top/(double)rhs.bottom);
        }
    }
    else{
        if (rhs.isNull()){
            return Fraction(lhs.top/(double)lhs.bottom+rhs.doubl);
        }
        else{
            int ttop=lhs.top*rhs.bottom+rhs.top*lhs.bottom;
            int bbot=lhs.bottom*rhs.bottom;
            int ggcd=gcd(ttop,bbot);
            return Fraction(ttop/ggcd,bbot/ggcd);
        }
    }
}

Fraction operator - (Fraction lhs, Fraction rhs){
    
    if (lhs.isNull()){
        if (rhs.isNull()) {
            return Fraction(lhs.doubl-rhs.doubl);
        }
        else{
            return Fraction(lhs.doubl-rhs.top/(double)rhs.bottom);
        }
    }
    else{
        if (rhs.isNull()){
            return Fraction(lhs.top/(double)lhs.bottom-rhs.doubl);
        }
        else{
            int ttop=lhs.top*rhs.bottom-rhs.top*lhs.bottom;
            int bbot=lhs.bottom*rhs.bottom;
            int ggcd=gcd(ttop,bbot);
            return Fraction(ttop/ggcd,bbot/ggcd);
        }
    }
}

Fraction operator * (Fraction lhs, Fraction rhs){
    if (lhs.isNull()){
        if (rhs.isNull()) {
            return Fraction(lhs.doubl*rhs.doubl);
        }
        else{
            return Fraction(lhs.doubl*rhs.top/(double)rhs.bottom);
        }
    }
    else{
        if (rhs.isNull()){
            return Fraction(lhs.top/(double)lhs.bottom*rhs.doubl);
        }
        else{
            int ttop=lhs.top*rhs.top;
            int bbot=lhs.bottom*rhs.bottom;
            int ggcd=gcd(ttop,bbot);
            return Fraction(ttop/ggcd,bbot/ggcd);
        }
    }
}

Fraction operator / (Fraction lhs, Fraction rhs){
    if (lhs.isNull()){
        if (rhs.isNull()) {
            return Fraction(lhs.doubl/rhs.doubl);
        }
        else{
            return Fraction(lhs.doubl/(double)rhs.top*rhs.bottom);
        }
    }
    else{
        if (rhs.isNull()){
            return Fraction(lhs.top/(double)lhs.bottom/rhs.doubl);
        }
        else{
            int ttop=lhs.top*rhs.bottom;
            int bbot=lhs.bottom*rhs.top;
            int ggcd=gcd(ttop,bbot);
            return Fraction(ttop/ggcd,bbot/ggcd);
        }
    }
}

/*
 
 double operator + (Fraction lhs, double rhs){
 return lhs.top/lhs.bottom+rhs;
 }
 double operator + ( double lhs, Fraction rhs){
 return rhs.top/rhs.bottom+lhs;
 }
 double operator - (Fraction lhs, double rhs){
 return lhs.top/lhs.bottom-rhs;
 }
 double operator - (double lhs, Fraction rhs){
 return lhs-rhs.top/rhs.bottom;
 }
 double operator * (double lhs, Fraction rhs){
 return lhs*rhs.top/rhs.bottom;
 }
 double operator / (double lhs, Fraction rhs){
 return lhs/rhs.top*rhs.bottom;
 }
 double operator * (Fraction lhs, double rhs){
 return lhs.top/lhs.bottom*rhs;
 }
 double operator / (Fraction lhs, double rhs){
 return lhs.top/lhs.bottom/rhs;
 }
 
 */

std::ostream& operator <<(std::ostream& os, Fraction rhs){
    if (rhs.isNull()){
        os<<rhs.doubl;
    }
    else{
        os<<rhs.top<<"/"<<rhs.bottom;
    }
    return os;
}

int gcd(int x, int y) {
    if (y==0)
        return x;
    
    return gcd(y, x%y);
}


#endif /* fraction_hpp */
