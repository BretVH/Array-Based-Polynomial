/* 
 * File:   polynomial.h
 * Author: bret
 *
 * Created on January 8, 2014, 4:20 PM
 */
#include <iostream>
#ifndef POLYNOMIAL_H
#define    POLYNOMIAL_H

    using namespace std;
	//---------------------------------------------------------------------------
// Polynomial class:
//   --operator<<: friend function used to print polynomial in correct form
//	 --operator>>: friend function used to input a polynomial
//	 --default constructor
//	 --copy constructor
//	 --deconstructor
//   --get_degree: return degree of leading term
//   --get_coeff: return coefficient of term of given degree
//   --set_coeff: Change or create a term
//   --operator+: add two polynomials
//   --operator-: subtract a polynomial from another
//	 --operator*: multiply two polynomials
//   --operator=: set this polynomial equal to another polynomial
//   --operator+=: add polynomial to this polynomial
//   --operator-=: subtract polynomial from this polynomial
//	 --operator*= multiply this polynomial by a polynomial
//   --operator=  creates a polynomial equivalent to argument
// Assumptions:
//   -- a Polynomial can not have a term with degree < 0
//   -- Heap memory should be deallocated by deconstructor
//---------------------------------------------------------------------------

    class Polynomial
    {
        // Overloaded <<: prints Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
		friend  ostream& operator<<( ostream& s, const Polynomial& p );
		//Overloaded >>: to input a polynomial as coefficient pairs seperated by spaces
        friend Polynomial operator>>( istream& s,  Polynomial & p );
    public:
	 // Constructor: the default is a 0-degree polynomial with 0.0 coefficient
	 //@pre none
        //@post a 0-degree polynomial with 0.0 coefficient and size = 0 created
        Polynomial( );
		// Constructor: an ith degree polynomial is created and filled with values in argument
		//@pre none
		//@post an ith degree polynomial is created, the values in the array are the coefficients
		//and are given in increasing order of degree
        Polynomial( unsigned i, ... );
		//Constructor: copy constructor creates a deep copy of polynomial passed as parameter
	    //@pre none
	    //@post: a deep copy of p created
		Polynomial( const Polynomial& p );
		//Deconstructor: deallocates all heap memory in use.
	    //@pre none
        //@post all heap memory deallocated
        ~Polynomial();
		//get_coeff
		//returns the coefficient of the ith term
		//@pre none
		//@post coefficient of ith term is returned.
		//@return int representing coefficient of ith term
        int get_coeff( unsigned i ) const;
		//get_ degree
		// returns the degree of a polynomial
		//@pre none
		//@post degree of leading term returned, if size = 0, -1 returned
		//@return int representing degree of leading term
        int get_degree( ) const;
		//set_coeff
		//creates new term or alters coefficient of existing term
		//@pre none
		//@post term with power i and coefficient value created in Polynomial
        void set_coeff( unsigned i, int value );
        
        // Arithmetic operators
	    //operator+
	    //@pre none
	    //@post Polynomial created
	    //@param const Polynomial&p, polynomial to add to this polynomial
        //@return Polynomial, the sum of this polynomial and p
        Polynomial operator+( Polynomial& x );
		//operator-
	    //@pre none
        //@post Polynomial created
        //@param const Polynomial&p, polynomial to subtract from this polynomial
        //@return Polynomial, the difference of this polynomial and p
        Polynomial operator-( Polynomial& x );
		//operator-
		//@pre none
		//@post Polynomial created
        //@return Polynomial, the negative of the implicit argument
        Polynomial operator-( );
		//operator*
        //@pre none

        //@post Polynomial created
        //@param const Polynomial&p, polynomial to multiply by this polynomial
        //@return Polynomial, the multiple of this polynomial and p
        Polynomial operator*( Polynomial& x );

		// Assignment operators

     	//operator+=
        //@pre none
        //@post this polynomial = sum of this polynomial and p 
        //@param const Polynomial&p, polynomial to be added to this polynomial
        //@return Polynomial&, this
        Polynomial& operator+=( Polynomial& x );
		//operator-=
        //@pre none
        //@post this polynomial = difference of this polynomial and p 
        //@param const Polynomial&p, polynomial to be subtracted from this polynomial
        //@return Polynomial&, this
        Polynomial& operator-=( Polynomial& x );
		//operator*=
        //@pre none
        //@post this polynomial = multiple of this polynomial and p 
        //@param const Polynomial&p, polynomial to be multiplied by this polynomial
        //@return Polynomial&, this
        Polynomial& operator*=( Polynomial& x );
	    //operator=
        //@pre none
        //@post this Polynomial is a deep copy of p
        //@param const Polynomial&p, polynomial to be copied
        //@return Polynomial&, a deep copy of p
		Polynomial& operator=( const Polynomial& x );
      
        
    private:
        int* poly;   //pointer to first term in polynomial
        int degree;  //number designating degree of polynomial
    };
  

#endif     
