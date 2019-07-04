

#ifndef __UNITTESTING_H__
#define __UNITTESTING_H__

// Flood includes

#include "Vector.h"
#include "Matrix.h"

namespace Flood
{

/// This class contains a minimal set of utilities needed for automated unit testing. 

class UnitTesting
{

public:

   // DEFAULT CONSTRUCTOR

   explicit UnitTesting(void);

   // DESTRUCTOR

   virtual ~UnitTesting(void);

   // METHODS

   // Get methods

   int get_tests_count(void);
   int get_tests_passed_count(void);
   int get_tests_failed_count(void);


   // Set methods

   void set_tests_count(int);
   void set_tests_passed_count(int);
   void set_tests_failed_count(int);

   
   // Test case methods

   /// This method runs all the methods contained in the test case. 

   virtual void run_test_case(void) = 0;


protected:

   /// Number of performed tests. 

   int tests_count;

   /// Number of tests which have passed the test case. 
 
   int tests_passed_count;

   /// Number of tests which have failed the test case. 

   int tests_failed_count;

};

}

#endif

