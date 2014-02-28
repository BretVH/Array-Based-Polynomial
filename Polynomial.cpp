/* 
 * File:   polynomial.cpp
 * Author: bret
 *
 * Created on January 8, 2014, 4:18 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstdarg>
#include "Polynomial.h"
using namespace std;
    
//  Constructor
//  Initializes a new instance of a Polynomial
//  with Polynomial set to 0 
//
Polynomial::Polynomial( )
{
    poly =  new int[1];
    poly[0] = 0;
    degree = 0;
}

//  Constructor
//  Initializes a new instance of a Polynomial
//  with degree i and coefficients given in increasing
//  order of degree in argument
//
Polynomial::Polynomial( unsigned i, ... )
{
    va_list args;
    va_start(args, i);
    if( i == 0 )
    {
	poly = new int[1];
       poly[0] = 0;
	degree = 0;
       return;
    }
    else 
    {
    	poly = new int[i];
    	degree = i - 1;
    	for( unsigned j = 0; j < i; j++ )
    	{
       	 poly[j] = va_arg(args, int);
    	}
    	va_end(args);
	}
}

//  Constructor
//  Initializes a new instance of a Polynomial
//  Polynomial instantiated is a deep copy of 
//  Polynomial in argument
//
Polynomial::Polynomial( const Polynomial& p )
{
	this->degree = p.degree;
	this->poly = new int[degree + 1];
	for( int i = 0; i <= degree; i++ )
	{
	    poly[i] = p.poly[i];
	}
}


//  DeConstructor
//  insures that no memory is leaked
//
Polynomial::~Polynomial( )
{
	delete[] poly; 
}

//-----------------------------------------------------------------------------
//	Function: int get_coeff( unsigned i )
//  
//	Title:	Polynomial
//
//	Description:
//				Accessor method to return coefficient of degree in 
//	Argument.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Returns: int representing the coefficient for degree i 
//  Parameters: unsigned representing the degree for the coeff you wish to 
//              access.
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//
//-----------------------------------------------------------------------------
int Polynomial::get_coeff( unsigned i ) const
{
    if(degree < i )
        return 0;
    else
        return poly[i];
}

//-----------------------------------------------------------------------------
//	Function: int get_degree( ) const
//  
//	Title:	Polynomial
//
//	Description:
//				returns the degree of this Polynomial.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: int representing the degree of the Polynomial
//
//
//-----------------------------------------------------------------------------
int Polynomial::get_degree( ) const
{
    for( int i = degree; i >= 0; i--)
    {
        if( poly[i] != 0 )
            return i;
    }
    return 0;
}


//-----------------------------------------------------------------------------
//	Function: void set_coeff( unsigned i, int value )
//  
//	Title:	Polynomial
//
//	Description:
//			Sets the coefficient equal to value for degree i.  If 
//			there is no term of degree i it is created.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//
//	Parameters: unsigned i, int value
//-----------------------------------------------------------------------------
void Polynomial::set_coeff( unsigned i, int value )
{
    if( degree < i )
    {
		int* temp = new int[i + 1];
		for( int j = 0; j <= degree; j++ )
		{
		    temp[j] = poly[j];
		}
		delete [] poly;
		poly = new int[i + 1];
		for ( int l = 0; l <= degree; l++ )
		{
		    poly[l] = temp[l];
		}
		delete [] temp;
		for ( int k = degree + 1; k <= i; k++ )
		{
		    poly[k] = 0;
		}
		degree = i;
              poly[i] = value;
    }
    else
        poly[i] = value;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator+( Polynomial& x)
//  
//	Title:	Polynomial
//
//	Description:
//			Adds this Polynomial to x and returns the result.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The polynomial that is the sum of this polynomial and x. 
//
//	Parameters: Polynomial& x
//-----------------------------------------------------------------------------
Polynomial Polynomial::operator+( Polynomial& x )
{
    Polynomial myPoly;
    delete [] myPoly.poly;
    if( degree < x.degree )
    {
	 myPoly.poly = new int[x.degree + 1];
        for( int i = 0; i <= degree; i++)
        {
            myPoly.poly[i] = x.poly[i] + poly[i];
        }
		for ( int j = degree + 1; j <= x.degree; j++ )
		{
		    myPoly.poly[j] = x.poly[j];
		}
        myPoly.degree = x.degree;
        return myPoly;
    }    
    else
    {
       myPoly.poly = new int[degree + 1];
       for( int i = 0; i <= x.degree; i++)
       {
           myPoly.poly[i] = poly[i] + x.poly[i];
       }
	   for ( int j = x.degree + 1; j <= degree; j++ )
	   {
		myPoly.poly[j] = poly[j];
	   }
       myPoly.degree = degree;
       return myPoly;
    }
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator+( Polynomial& x)
//  
//	Title:	Polynomial
//
//	Description:
//			Adds x to this polynomial.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The polynomial that is the sum of this polynomial and x. 
//
//	Parameters: Polynomial& x
//-----------------------------------------------------------------------------
Polynomial& Polynomial::operator+=( Polynomial& x )
{
	Polynomial temp = *this + x;
	if( temp.degree > degree )
	{
	    delete [] poly;
	    poly = new int[temp.degree + 1];
	}
	degree = temp.degree;
	for( int i = 0; i <= degree; i++ )
		poly[i] = temp.poly[i];
	return *this;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator-( Polynomial& x)
//  
//	Title:	Polynomial
//
//	Description:
//			Subtracts x from this Polynomial and returns the result.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The polynomial that is the difference of this polynomial and x. 
//
//	Parameters: Polynomial& x
//-----------------------------------------------------------------------------    
Polynomial Polynomial::operator-( Polynomial& x )
{
    Polynomial myPoly;
	delete [] myPoly.poly;
    if( degree < x.degree )
    {
	 myPoly.poly = new int[x.degree + 1];
        for( int i = 0; i <= degree; i++)
        {
            myPoly.poly[i] =  poly[i] - x.poly[i];
        }
		for( int j = degree + 1; j <= x.degree; j++ )
		{
		    myPoly.poly[j] = -x.poly[j];
		}
        myPoly.degree = x.degree;
        return myPoly;
    }    
    else
    {
	myPoly.poly = new int[degree + 1];
       for( int i = 0; i <= x.degree; i++)
       {
          myPoly.poly[i] = poly[i] - x.poly[i];
       }
	   for ( int j = x.degree + 1; j <= degree; j++ )
	   {
	       myPoly.poly[j] = poly[j];
	   }
       myPoly.degree = degree;
       return myPoly;
    }
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator-( )
//  
//	Title:	Polynomial
//
//	Description:
//			Returns the negation of this Polynomial.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The polynomial that is the negation of this Polynomial. 
//
//-----------------------------------------------------------------------------  
Polynomial Polynomial::operator-( )
{
    Polynomial myPoly;
    delete [] myPoly.poly;
    myPoly.poly = new int[degree + 1];
	myPoly.degree = degree;
    for( int i = 0; i <= degree; i++)
    {
        myPoly.poly[i] = -poly[i];
    }
    return myPoly;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator-( Polynomial& x)
//  
//	Title:	Polynomial
//
//	Description:
//			Subtracts x from this Polynomial.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: This polynomial that is the difference of this polynomial and x. 
//
//	Parameters: Polynomial& x
//-----------------------------------------------------------------------------  
Polynomial& Polynomial::operator-=( Polynomial& x )
{
    Polynomial temp = *this - x;
    if( temp.degree > degree )
    {
	delete [] poly;
	poly = new int[temp.degree + 1];
    }
    degree = temp.degree;
    for( int i = 0; i <= degree; i++ )
  	poly[i] = temp.poly[i];
    return *this;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator*( Polynomial& x)
//  
//	Title:	Polynomial
//
//	Description:
//			Multiplies x by this Polynomial and returns the result.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The polynomial that is the multiple of this polynomial and x. 
//
//	Parameters: Polynomial& x
//-----------------------------------------------------------------------------  
Polynomial Polynomial::operator*( Polynomial& x )
{
       Polynomial myPoly;
	Polynomial temp;
	delete [] myPoly.poly;
	delete [] temp.poly;
	temp.degree = degree + x.degree;
	myPoly.degree = degree + x.degree;
	myPoly.poly = new int[(x.degree + degree) + 1];
	temp.poly = new int[(x.degree + degree) + 1];
	for( int l = 0; l <= temp.degree; l++ )
	{
		myPoly.poly[l] = 0;
		temp.poly[l] = 0;
	}
	for( int j = 0; j <= degree; j++ )
	{
		for( int i = 0; i <= x.degree; i++ )
		{
			myPoly.poly[(i + j)] = ( poly[j] * x.poly[i] );
		}
		temp = temp + myPoly;
	       for ( int k = 0; k <= myPoly.degree; k++ )
	       {
			myPoly.poly[k] = 0;
		}
	}
	return temp;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator*=( Polynomial& x)
//  
//	Title:	Polynomial
//
//	Description:
//			Multiplies this Polynomial by x. 
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: This polynomial that is the multiple of this polynomial and x. 
//
//	Parameters: Polynomial& x
//-----------------------------------------------------------------------------  
Polynomial& Polynomial::operator*=( Polynomial& x )
{
       Polynomial temp = *this * x;
	if( temp.degree > degree )
	{
	    delete [] poly;
	    poly = new int[temp.degree + 1];
	}
	degree = temp.degree;
	for( int i = 0; i <= degree; i++ )
	{
	    poly[i] = temp.poly[i];
	}
	return *this;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator=( Polynomial& x)
//  
//	Title:	Polynomial
//
//	Description:
//			Creates a deep copy of x, setting this Polynomial equal
//			to x.
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The deep copy of x. 
//
//	Parameters: Polynomial& x
//-----------------------------------------------------------------------------  
Polynomial& Polynomial::operator=( const Polynomial& x )
{
    this->degree = x.degree;
    delete [] poly;
    this->poly = new int[degree + 1];
    for( int i = 0; i <= degree; i++ )
    {
        this->poly[i] = x.poly[i];
    }
    return *this;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator>>( istream& s, Polynomial& p)
//  
//	Title:	Polynomial
//
//	Description:   to input a polynomial as coefficient/exponent pairs separated by spaces, ending at the end of the input stream. For example
//			 5 2 -3 1 2 0	is interpreted as 5x2 - 3x + 2
//			-3 1 2 0 5 2	is also interpreted as 5x2 - 3x + 2
//			 It is assumed the input is valid.
//			
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The polynomial that is created. 
//
//	Parameters: istream& s, Polynomial& p
//-----------------------------------------------------------------------------  
Polynomial operator>>( istream& s , Polynomial& p ) 
{
   int coeff;
   int power;
   do
   {
      s >> coeff;
      s >> power;
      if( !s.fail() )
         p.set_coeff( power, coeff );
   }
   while ( !s.fail() );
   return p;
}

//-----------------------------------------------------------------------------
//	Function: Polynomial operator<<( ostream& s, const Polynomial& p)
//  
//	Title:	Polynomial
//
//	Description:   to output a text representation of the polynomial, using 
// 		        the variable name x in decreasing order of degree with 
//			 spaces around the signs (except in the case of a constant 
//			 polynomial); some examples are:
//			 5x^2 - 3x + 2
//			 x^2 - x
//			 -2x
//			 0
//			
//	
//	Programmer: Bret Van Hof
//	
//	Date: 1/08/2013
//
//  Version: 1.0
//  Environment: AMD FX 8-core Processor 8350 4.0GHZ
//				 Windows 8.1 Pro 64-bit
//  Returns: The polynomial that is created. 
//
//	Parameters: ostream& s, Polynomial& x
//----------------------------------------------------------------------------- 
ostream& operator<<( ostream &s ,  const Polynomial& p )
{
    bool first = true;
    int myDegree = p.get_degree();
    if( myDegree == 0 )
    {
        return s;
    }
    else 
    {
        for( int i = myDegree; i >= 0; i--)
        {
            if( i == 0 )
            {
                if( p.get_coeff( i ) == 0 )
                {
                   continue;
                } 
                else
                {
                    if( first )
                    {
                        s << p.get_coeff( i );
                    }
                    else
                    {
                        if( p.get_coeff( i ) < 0 )
                        {
                            s << "- " << -p.get_coeff( i );
                        }
                        else
                        {
                            s << "+ " << p.get_coeff( i );
                        }
                    }
                }
            }
            else
            {
                if( p.get_coeff( i ) == 0 )
                {
                    continue;
                }
                else if( p.get_coeff( i ) < 0 )
                {
                    if( first )
                    {
                        if ( p.get_coeff ( i ) == -1 )
                        {
                            s << "-x^" << i << " ";
                        }
                        else
                        {
                            s << p.get_coeff( i) << "x^" << i << " ";
                        }
                        first = false;
                    }
                    else
                    {
                        if ( p.get_coeff( i ) == -1 )
                        {
                            s << "- x";
                        }
                        else
                        {
                            s << "- " << -p.get_coeff( i );
                        }
                        if( i > 1 )
                        {
                            s << "x^" << i << " ";
                        }
                        else
                        {
                            s << "x "; 
                        }
                    }
                }
                else
                {
                     
                    if( first )
                    {
                        if ( p.get_coeff ( i ) == 1 )
                        {
                            if( i > 1 )
                            {
                                s << "x^" << i << " ";
                            }
                            else
                            {
                                s << "x "; 
                            }
                        }    
                        else
                        {       
                            s << p.get_coeff( i );
                            if( i > 1 )
                            {
                                s << "x^" << i << " ";
                            }
                            else
                            {
                                s << "x "; 
                            }
                        }
                        first = false;
                    }
                    else
                    {
                        if ( p.get_coeff( i ) == 1 )
                        {
                            s << "+ ";
                        }
                        else
                        {
                            s << "+ " << p.get_coeff( i );
                        }
                        if( i > 1 )
                        {
                            s << "x^" << i << " ";
                        }
                        else
                        {
                            s << "x "; 
                        }
                    }
                }
            }
        }
    }
    return s;
}
