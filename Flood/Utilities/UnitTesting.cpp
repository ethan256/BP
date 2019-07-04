/****************************************************************************************************************/
/*                                                                                                              */
/*   Flood: An Open Source Neural Networks C++ Library                                                          */
/*   www.cimne.com/flood                                                                                        */
/*                                                                                                              */
/*   U N I T   T E S T I N G   C L A S S                                                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   International Center for Numerical Methods in Engineering (CIMNE)                                          */
/*   Technical University of Catalonia (UPC)                                                                    */
/*   Barcelona, Spain                                                                                           */
/*   E-mail: rlopez@cimne.upc.edu                                                                               */ 
/*                                                                                                              */
/****************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

#include "UnitTesting.h"

namespace Flood
{

// GENERAL CONSTRUCTOR

/// General constructor. It constructs a test case with default values:
/// <ul>
/// <li> Message: empty
/// <li> Tests count: 0
/// <li> Tests passed: 0
/// <li> Tests failed: 0
/// </ul>

UnitTesting::UnitTesting(void)
{

   tests_count = 0;
   tests_passed_count = 0;
   tests_failed_count = 0;
}


// DESTRUCTOR
 
/// Destructor.

UnitTesting::~UnitTesting(void)
{ 
}


// METHODS

// int get_tests_count(void) method

/// This method returns the number of tests which have been performed by the test case. 

int UnitTesting::get_tests_count(void)
{
   return(tests_count);
}


// int get_tests_passed_count(void) method

/// This method returns the number of tests which have passed the test case. 

int UnitTesting::get_tests_passed_count(void)
{
   return(tests_passed_count);
}


// int get_tests_failed_count(void) method

/// This method returns the number of tests which have failed the test case. 

int UnitTesting::get_tests_failed_count(void)
{
   return(tests_failed_count);
}




// void set_tests_count(int) method

/// This method sets a new value for the number of tests performed by the test case. 
/// @param new_tests_count Number of tests performed. 

void UnitTesting::set_tests_count(int new_tests_count)
{
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(new_tests_count < 0)
   {
	   TRACE0("Flood Warning: UnitTesting class.\n");
	   TRACE0("void set_tests_count(int) method.\n");
	   TRACE0("Test count must be equal or greater than zero.\n");
   }

   #endif

   tests_count = new_tests_count;
}


// void set_tests_passed_count(int) method

/// This method sets a new value for the number of tests which have passed the test case. 
/// @param new_tests_passed_count Number of tests passed. 

void UnitTesting::set_tests_passed_count(int new_tests_passed_count)
{
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(new_tests_passed_count < 0)
   {

	   TRACE0("Flood Warning: UnitTesting class.\n");
	   TRACE0("void set_tests_passed_count(int) method.\n");
	   TRACE0("Test pased count must be equal or greater than zero.\n");

   }

   #endif

   tests_passed_count = new_tests_passed_count;
}


// void set_tests_failed_count(int) method

/// This method sets a new value for the number of tests which have failed the test case. 
/// @param new_tests_failed_count Number of tests failed. 

void UnitTesting::set_tests_failed_count(int new_tests_failed_count)
{
   // Control sentence (if debug)      

   #ifdef _DEBUG 

   if(new_tests_failed_count < 0)
   {
	   TRACE0("Flood Warning: UnitTesting class.\n");
	   TRACE0("void set_tests_failed_count(int) method.\n");
	   TRACE0("Test failed count must be equal or greater than zero.\n");
   }
   #endif    
   
   tests_failed_count = new_tests_failed_count;
}


}
