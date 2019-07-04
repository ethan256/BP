

#ifndef __PATTERNRECOGNITIONUTILITIES_H__
#define __PATTERNRECOGNITIONUTILITIES_H__

// System includes

#include "../Utilities/Vector.h"
#include "../Utilities/Matrix.h"
#include "../Utilities/InputTargetDataSet.h"
#include "../MultilayerPerceptron/MultilayerPerceptron.h"

namespace Flood
{

/// This class contains some useful utilities for pattern recognition (or classification problems).
/// That includes generating artificial data or performing testing of results. 

class PatternRecognitionUtilities
{

public:  

   // DEFAULT CONSTRUCTOR

   explicit PatternRecognitionUtilities(void);

   // MULTILAYER PERCEPTRON CONSTRUCTOR

   explicit PatternRecognitionUtilities(MultilayerPerceptron*);

   // INPUT-TARGET DATA SET CONSTRUCTOR

   explicit PatternRecognitionUtilities(InputTargetDataSet*);

   // GENERAL CONSTRUCTOR

   explicit PatternRecognitionUtilities(MultilayerPerceptron*, InputTargetDataSet*);

   // DESTRUCTOR

   virtual ~PatternRecognitionUtilities(void);


   // METHODS

   // Get methods

   MultilayerPerceptron* get_multilayer_perceptron_pointer(void);
   InputTargetDataSet* get_input_target_data_set_pointer(void);
   

   // Set methods

   void set_multilayer_perceptron_pointer(MultilayerPerceptron*);
   void set_input_target_data_set_pointer(InputTargetDataSet*);


   // Arfificial data generators

   void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&);

   // Output data methods

   Matrix<bool> calculate_binary_output_data(void);

   Matrix<bool> calculate_binary_training_output_data(void);
   Matrix<bool> calculate_binary_validation_output_data(void);
   Matrix<bool> calculate_binary_testing_output_data(void);

   // Target data methods

   Matrix<bool> get_binary_target_data(void);

   Matrix<bool> get_binary_training_target_data(void);
   Matrix<bool> get_binary_validation_target_data(void);
   Matrix<bool> get_binary_testing_target_data(void);

   // Class distribution methods

   Vector<int> calculate_class_distribution(void);
   
   // Binary classification test methods
   
   Vector<double> calculate_binary_classification_test(void);
   Vector<double> binary_classification_test(void);
 
   // Confusion matrix methods

   Matrix<int> calculate_confusion(void);


private: 

   // FIELDS

   /// Pointer to a multilayer perceptron object.

   MultilayerPerceptron* multilayer_perceptron_pointer;

   /// Pointer to an input-target data set object.

   InputTargetDataSet* input_target_data_set_pointer;

};

}

#endif

