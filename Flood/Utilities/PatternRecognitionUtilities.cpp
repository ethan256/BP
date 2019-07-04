

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

// Flood includes

#include "PatternRecognitionUtilities.h"

namespace Flood
{

// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a pattern recognition utilites object 
/// not associated to any multilayer perceptron neither any input-target data set objects.

PatternRecognitionUtilities::PatternRecognitionUtilities(void)
{
   multilayer_perceptron_pointer = NULL;
   input_target_data_set_pointer = NULL;

}


// MULTILAYER PERCEPTRON CONSTRUCTOR

/// Multilayer perceptron constructor. It creates a pattern recognition utilites object 
/// associated to a multilayer perceptron but not to an input-target data set.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.

PatternRecognitionUtilities::PatternRecognitionUtilities(MultilayerPerceptron* new_multilayer_perceptron_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;
   input_target_data_set_pointer = NULL;

}


// INPUT-TARGET DATA SET CONSTRUCTOR

/// Input-target data set constructor. It creates a pattern recognition utilites object 
/// associated to an input-target data set but not to a multilayer perceptron.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

PatternRecognitionUtilities::PatternRecognitionUtilities(InputTargetDataSet* new_input_target_data_set_pointer)
{
   multilayer_perceptron_pointer = NULL;
   input_target_data_set_pointer = new_input_target_data_set_pointer;

}


// GENERAL CONSTRUCTOR

/// General constructor. It creates a pattern recognition utilities object 
/// associated to a multilayer perceptron and an input-target data set.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

PatternRecognitionUtilities::PatternRecognitionUtilities
(MultilayerPerceptron* new_multilayer_perceptron_pointer, InputTargetDataSet* new_input_target_data_set_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;
   input_target_data_set_pointer = new_input_target_data_set_pointer;

}


// DESTRUCTOR

/// Destructor. 

PatternRecognitionUtilities::~PatternRecognitionUtilities(void)
{
}


// METHODS

// MultilayerPerceptron* get_multilayer_perceptron_pointer(void) method

/// This method returns a pointer to the multilayer perceptron object which is a member of this class.

MultilayerPerceptron* PatternRecognitionUtilities::get_multilayer_perceptron_pointer(void)
{
   return(multilayer_perceptron_pointer);   
}


// InputTargetDataSet* get_input_target_data_set_pointer(double) method

/// This method returns a pointer to the input-target data set object which is a member of this class.

InputTargetDataSet* PatternRecognitionUtilities::get_input_target_data_set_pointer(void)
{
   return(input_target_data_set_pointer);   
}




// void set_multilayer_perceptron_pointer(MultilayerPerceptron*) method

/// This method sets a new multilayer perceptron pointer.
/// @param new_multilayer_perceptron_pointer Pointer to a multilayer perceptron object.

void PatternRecognitionUtilities::
set_multilayer_perceptron_pointer(MultilayerPerceptron* new_multilayer_perceptron_pointer)
{
   multilayer_perceptron_pointer = new_multilayer_perceptron_pointer;   
}


// void set_input_target_data_set_pointer(InputTargetDataSet*) method

/// This method sets a new input-target data set pointer.
/// @param new_input_target_data_set_pointer Pointer to an input-target data set object.

void PatternRecognitionUtilities
::set_input_target_data_set_pointer(InputTargetDataSet* new_input_target_data_set_pointer)
{
   input_target_data_set_pointer = new_input_target_data_set_pointer;   
}


// void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method

/// This method generates artificial input and target data to be used for classification purposes. 
/// The number of instances and variables are those of the input-target data set object member.
///
/// @param mean Mean values of the Gaussian data generators for the input variables.
/// @param standard_deviation Standard deviation values of the Gaussian data generators for the input variables.
/// @param prior_probability Prior probabilities of the target variables.

void PatternRecognitionUtilities::generate_artificial_data
(const Vector< Vector<double> >& mean, const Vector< Vector<double> >& standard_deviation, const Vector<double>& prior_probability)
{
   // Input-target data set stuff

   int instances_number = input_target_data_set_pointer->get_instances_number();
   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   int prior_probability_size = prior_probability.get_size();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   int mean_size = mean.get_size();
   int standard_deviation_size = standard_deviation.get_size();

   if(target_variables_number == 1)
   {
      if(mean_size != 2)
	  {
         std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                   << "void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                   << "Size of mean must be two." << std::endl;

         exit(1);  
	  }
      else if(standard_deviation_size != 2)
	  {
         std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                   << "void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                   << "Size of standard deviation must be two." << std::endl;

         exit(1);  
	  }
      else if(prior_probability_size != 2)
	  {
         std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                   << "void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                   << "Size of prior probability must be two." << std::endl;

         exit(1);  
	  }
   }
   else
   {
      if(mean_size != target_variables_number)
	  {
         std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                   << "void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                   << "Size of mean must be equal to number of target variables." << std::endl;

         exit(1);  
	  }
      else if(standard_deviation_size != target_variables_number)
	  {
         std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                   << "void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                   << "Size of standard deviation must be equal to number of target variables." << std::endl;

         exit(1);  
	  }
      else if(prior_probability_size != target_variables_number)
	  {
         std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                   << "void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                   << "Size of prior probability must be equal to number of target variables." << std::endl;

         exit(1);  
	  }   
   }
   
   double sum = prior_probability.calculate_sum();

   if(sum != 1.0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                << "void generate_artificial_data(const Vector< Vector<double> >&, const Vector< Vector<double> >&, const Vector<double>&) method." << std::endl
                << "Sum of prior probabilities must one." << std::endl;

      exit(1);      
   }

   #endif    

   Vector<double> input_instance(input_variables_number);
   Vector<double> target_instance(target_variables_number);

   double random;

   // Cumulative prior probability vector

   Vector<double> cumulative_prior_probability(prior_probability_size);

   cumulative_prior_probability[0] = prior_probability[0]; 

   for(int i = 1; i < prior_probability_size; i++)
   {
      cumulative_prior_probability[i] = cumulative_prior_probability[i-1] + prior_probability[i];
   }


   for(int i = 0; i < instances_number; i++)
   {
      if(target_variables_number == 1)
	  {
         random = (double)rand()/(RAND_MAX+1.0);
	        
		 if(random < cumulative_prior_probability[0])
		 {
            input_instance.initialize_normal(mean[0], standard_deviation[0]); 
            target_instance[0] = 1.0;
		 }
		 else
		 {    
            input_instance.initialize_normal(mean[1], standard_deviation[1]); 
		    target_instance[0] = 0.0; 
		 }
	  }
	  else
	  {
         //@todo 	  
	  }

	  input_target_data_set_pointer->set_input_instance(i, input_instance);
	  input_target_data_set_pointer->set_target_instance(i, target_instance);
   }
}


// Matrix<bool> get_binary_target_data(void) method

/// This method returns a matrix with the binary values of all the instances of the target variables in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::get_binary_target_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_target_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif

   // Input-target data set stuff

   int instances_number = input_target_data_set_pointer->get_instances_number();
             
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   #ifdef _DEBUG 

   if(instances_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_target_data(void) method." << std::endl
                << "Number of instances must be greater than zero." << std::endl;

      exit(1);   
   }

   if(target_variables_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_target_data(void) method." << std::endl
                << "Number of target variables must be greater than zero." << std::endl;

      exit(1);   
   }

   #endif


   // Calculate target data 

   Matrix<bool> target_data(instances_number, target_variables_number, false);

   Vector<double> target(target_variables_number);

   if(target_variables_number == 1)
   {
      for(int i = 0; i < instances_number; i++)
      {
         target = input_target_data_set_pointer->get_target_instance(i);
     
         if(target[0] > 0.5)
		 {
            target_data[i][0] = true;
		 }
      }                     
   }
   else if(target_variables_number > 1)
   {
      int winner_index;

      for(int i = 0; i < instances_number; i++)
      {
         target = input_target_data_set_pointer->get_target_instance(i);
     
         winner_index = target.calculate_maximal_index();

         target_data[i][winner_index] = true;
      }                  
   }
   
   return(target_data);
}


// Matrix<bool> get_binary_training_target_data(void) method

/// This method returns a matrix with the binary values of the training instances of the target variables in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::get_binary_training_target_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_training_target_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif

   // Input-target data set stuff

   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();
             
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   #ifdef _DEBUG 

   if(training_instances_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_training_target_data(void) method." << std::endl
                << "Number of training instances must be greater than zero." << std::endl;

      exit(1);   
   }

   if(target_variables_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_training_target_data(void) method." << std::endl
                << "Number of target variables must be greater than zero." << std::endl;

      exit(1);   
   }

   #endif


   // Calculate training target data 

   Matrix<bool> training_target_data(training_instances_number, target_variables_number, false);

   Vector<double> target(target_variables_number);

   if(target_variables_number == 1)
   {
      for(int i = 0; i < training_instances_number; i++)
      {
         target = input_target_data_set_pointer->get_training_target_instance(i);
     
         if(target[0] > 0.5)
		 {
            training_target_data[i][0] = true;
		 }
      }                     
   }
   else if(target_variables_number > 1)
   {
      int winner_index;

      for(int i = 0; i < training_instances_number; i++)
      {
         target = input_target_data_set_pointer->get_training_target_instance(i);
     
         winner_index = target.calculate_maximal_index();

         training_target_data[i][winner_index] = true;
      }                  
   }
   
   return(training_target_data);
}


// Matrix<bool> get_binary_validation_target_data(void) method

/// This method returns a matrix with the binary values of the validation instances of the target variables in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::get_binary_validation_target_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_validation_target_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif

   // Get validation target data

   int validation_instances_number = input_target_data_set_pointer->get_validation_instances_number();
             
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   #ifdef _DEBUG 

   if(validation_instances_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_validation_target_data(void) method." << std::endl
                << "Number of validation instances must be greater than zero." << std::endl;

      exit(1);   
   }

   if(target_variables_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_validation_target_data(void) method." << std::endl
                << "Number of target variables must be greater than zero." << std::endl;

      exit(1);   
   }

   #endif

   Matrix<bool> validation_target_data(validation_instances_number, target_variables_number, false);

   Vector<double> target(target_variables_number);

   if(target_variables_number == 1)
   {
      for(int i = 0; i < validation_instances_number; i++)
      {
         target = input_target_data_set_pointer->get_validation_target_instance(i);
     
         if(target[0] > 0.5)
		 {
            validation_target_data[i][0] = true;
		 }
      }                     
   }
   else if(target_variables_number > 1)
   {
      int winner_index;

      for(int i = 0; i < validation_instances_number; i++)
      {
         target = input_target_data_set_pointer->get_validation_target_instance(i);
     
         winner_index = target.calculate_maximal_index();

         validation_target_data[i][winner_index] = true;
      }                  
   }
   
   return(validation_target_data);
}


// Matrix<bool> get_binary_testing_target_data(void) method

/// This method returns a matrix with the binary values of the testing instances of the target variables in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::get_binary_testing_target_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_testing_target_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif

   // Get testing target data

   int testing_instances_number = input_target_data_set_pointer->get_testing_instances_number();
             
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(testing_instances_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_testing_target_data(void) method." << std::endl
                << "Number of testing instances must be greater than zero." << std::endl;

      exit(1);   
   }

   if(target_variables_number == 0)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> get_binary_testing_target_data(void) method." << std::endl
                << "Number of target var must be greater than zero." << std::endl;

      exit(1);   
   }

   #endif

   Matrix<bool> testing_target_data(testing_instances_number, target_variables_number, false);

   Vector<double> target(target_variables_number);

   if(target_variables_number == 1)
   {
      for(int i = 0; i < testing_instances_number; i++)
      {
         target = input_target_data_set_pointer->get_testing_target_instance(i);
     
         if(target[0] > 0.5)
         {
            testing_target_data[i][0] = true;
         }  
      }               
   }
   else if(target_variables_number > 1)
   {
      int winner_index;

      for(int i = 0; i < testing_instances_number; i++)
      {
         target = input_target_data_set_pointer->get_testing_target_instance(i);
     
         winner_index = target.calculate_maximal_index();

         testing_target_data[i][winner_index] = true;
      }               
   }
   
   return(testing_target_data);
}


// Matrix<bool> calculate_binary_output_data(void)

/// This method retuns a Matrix containing the binary neural network outputs for all the instances in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::calculate_binary_output_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_output_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif
             
   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifdef _DEBUG 

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   // Control sentence
   
   if(inputs_number != input_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_output_data(void) method." << std::endl
                << "Number of inputs in multilayer perceptron " 
                << "must be equal to number of input variables in the data set." << std::endl;

      exit(1);
   }
   else if(outputs_number != target_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                << "Matrix<bool> calculate_binary_output_data(void) method." << std::endl
                << "Number of outputs in multilayer perceptron " << std::endl
                << "must be equal to number of target variables in the data set." << std::endl;

      exit(1);
   }

   #endif

   // Calculate output data

   int instances_number = input_target_data_set_pointer->get_instances_number();

   Matrix<bool> output_data(instances_number, outputs_number, false);

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);

   if(outputs_number == 1)
   {
      for(int i = 0; i < instances_number; i++)
      {
         input = input_target_data_set_pointer->get_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         if(output[0] > 0.5)
		 {
            output_data[i][0] = true;
		 }
      }               
   }
   else
   {
      int winner_index;

      for(int i = 0; i < instances_number; i++)
      {
         input = input_target_data_set_pointer->get_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         winner_index = output.calculate_maximal_index();

         output_data[i][winner_index] = true;
      }               
   }

   return(output_data);
}


// Matrix<bool> calculate_binary_training_output_data(void)

/// This method retuns a Matrix containing the binary neural network outputs for the training instances in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::calculate_binary_training_output_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_training_output_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif
             
   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifdef _DEBUG 

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   // Control sentence
   
   if(inputs_number != input_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_training_output_data(void) method." << std::endl
                << "Number of inputs in multilayer perceptron " 
                << "must be equal to number of input variables in training data set." << std::endl;

      exit(1);
   }
   else if(outputs_number != target_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                << "Matrix<bool> calculate_binary_output_data(void) method." << std::endl
                << "Number of outputs in multilayer perceptron " << std::endl
                << "must be equal to number of target variables in training data set." << std::endl;

      exit(1);
   }

   #endif

   // Calculate training output data

   int training_instances_number = input_target_data_set_pointer->get_training_instances_number();

   Matrix<bool> training_output_data(training_instances_number, outputs_number, false);

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);

   if(outputs_number == 1)
   {
      for(int i = 0; i < training_instances_number; i++)
      {
         input = input_target_data_set_pointer->get_training_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         if(output[0] > 0.5)
		 {
            training_output_data[i][0] = true;
		 }
      }               
   }
   else
   {
      int winner_index;

      for(int i = 0; i < training_instances_number; i++)
      {
         input = input_target_data_set_pointer->get_training_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         winner_index = output.calculate_maximal_index();

         training_output_data[i][winner_index] = true;
      }               
   }

   return(training_output_data);
}



// Matrix<bool> calculate_binary_validation_output_data(void)

/// This method retuns a Matrix containing the binary neural network outputs for the training instances in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::calculate_binary_validation_output_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_validation_output_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif
             
   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifdef _DEBUG 

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   // Control sentence
   
   if(inputs_number != input_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_validation_output_data(void) method." << std::endl
                << "Number of inputs in multilayer perceptron " 
                << "must be equal to number of input variables in validation data set." 
                << std::endl;

      exit(1);
   }
   else if(outputs_number != target_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                << "Matrix<bool> calculate_binary_validation_output_data(void) method." << std::endl
                << "Number of outputs in multilayer perceptron " << std::endl
                << "must be equal to number of target variables in validation data set." 
                << std::endl;

      exit(1);
   }

   #endif

   // Calculate validation output data

   int validation_instances_number = input_target_data_set_pointer->get_validation_instances_number();

   Matrix<bool> validation_output_data(validation_instances_number, outputs_number, false);

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);

   if(outputs_number == 1)
   {
      for(int i = 0; i < validation_instances_number; i++)
      {
         input = input_target_data_set_pointer->get_validation_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         if(output[0] > 0.5)
		 {
            validation_output_data[i][0] = true;
		 }
      }               
   }
   else
   {
      int winner_index;

      for(int i = 0; i < validation_instances_number; i++)
      {
         input = input_target_data_set_pointer->get_validation_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         winner_index = output.calculate_maximal_index();

         validation_output_data[i][winner_index] = true;
      }               
   }
   
   return(validation_output_data);
}


// Matrix<bool> calculate_binary_testing_output_data(void)

/// This method retuns a Matrix containing the binary neural network outputs for the training instances in 
/// the input-target data set.

Matrix<bool> PatternRecognitionUtilities::calculate_binary_testing_output_data(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_testing_output_data(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif
             
   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifdef _DEBUG 

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   // Control sentence
   
   if(inputs_number != input_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Matrix<bool> calculate_binary_testing_output_data(void) method." << std::endl
                << "Number of inputs in multilayer perceptron " 
                << "must be equal to number of input variables in testing data set." 
                << std::endl;

      exit(1);
   }
   else if(outputs_number != target_variables_number)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl
                << "Matrix<bool> calculate_binary_testing_output_data(void) method." << std::endl
                << "Number of outputs in multilayer perceptron " << std::endl
                << "must be equal to number of target variables in testing data set." 
                << std::endl;

      exit(1);
   }

   #endif

   // Calculate testing output data

   int testing_instances_number = input_target_data_set_pointer->get_testing_instances_number();

   Matrix<bool> testing_output_data(testing_instances_number, outputs_number, false);

   Vector<double> input(inputs_number);
   Vector<double> output(outputs_number);

   if(outputs_number == 1)
   {
      for(int i = 0; i < testing_instances_number; i++)
      {
         input = input_target_data_set_pointer->get_testing_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         if(output[0] > 0.5)
		 {
            testing_output_data[i][0] = true;
		 }
      }               
   }
   else
   {
      int winner_index;

      for(int i = 0; i < testing_instances_number; i++)
      {
         input = input_target_data_set_pointer->get_testing_input_instance(i);
     
         output = multilayer_perceptron_pointer->calculate_output(input);

         winner_index = output.calculate_maximal_index();

         testing_output_data[i][winner_index] = true;
      }               
   }
   
   return(testing_output_data);
}


// Vector<int> calculate_class_distribution(void) method

/// This method returns a vector containing the number of instances of each class in the input-target data set.
/// If the number of target variables is one then the number of classes is two.
/// If the number of target variables is greater than one then the number of classes is equal to the number 
/// of target variables.

Vector<int> PatternRecognitionUtilities::calculate_class_distribution(void)
{ 
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
      std::cerr << "Flood Error: PatternRecognitionUtilities class." << std::endl 
                << "Vector<int> calculate_class_distribution(void) method." << std::endl
                << "Input-target data set object cannot be null." << std::endl;

      exit(1);   
   }

   #endif

   int instances_number = input_target_data_set_pointer->get_instances_number();   
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();
  
   Matrix<bool> binary_target_data = get_binary_target_data();
   
   Vector<int> class_distribution;

   if(target_variables_number == 1) // Two classes
   {
      class_distribution.set(2, 0);

      for(int i = 0; i < instances_number; i++)
      {      
         if(binary_target_data[i][0])
         {
            class_distribution[0]++;
         }   
		 else
		 {
            class_distribution[1]++;		 
		 }
      }
   }
   else
   {
      class_distribution.set(target_variables_number, 0);
   
      for(int i = 0; i < instances_number; i++)
      {      
         for(int j = 0; j < target_variables_number; j++)
         {         
            if(binary_target_data[i][j])
            {
               class_distribution[j]++;
            }   
         } 
      }
   }

   return(class_distribution);
}



// Matrix<int> calculate_confusion(void) method

/// This method returns the confusion matrix of a multilayer perceptron on the testing instances of an input-target data set. 

Matrix<int> PatternRecognitionUtilities::calculate_confusion(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   if(input_target_data_set_pointer == NULL)
   {
	   TRACE0("Flood Error: PatternRecognitionUtilities class.\n");
	   TRACE0("Matrix<int> calculate_confusion(void) method.\n");
	   TRACE0("Input-target data set object cannot be null.\n");

      exit(1);   
   }

   #endif
             
   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifdef _DEBUG 

   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   // Control sentence
   
   if(inputs_number != input_variables_number)
   {

	   TRACE0("Flood Error: PatternRecognitionUtilities class.\n");
	   TRACE0("Matrix<int> calculate_confusion(void) method.\n");
	   TRACE0("Number of inputs in multilayer perceptron must be equal to number of input variables in input target data set.\n");

      exit(1);
   }

   if(outputs_number != target_variables_number)
   {
	   TRACE0("Flood Error: PatternRecognitionUtilities class.\n");
	   TRACE0("Matrix<int> calculate_confusion(void) method.\n");
	   TRACE0("Number of outputs in multilayer perceptron must be equal to number of target variables in input target data set.\n");

      exit(1);
   }

   #endif

   int testing_instances_number = input_target_data_set_pointer->get_testing_instances_number();

   Matrix<bool> binary_testing_target_data = get_binary_testing_target_data();
   Matrix<bool> binary_testing_output_data = calculate_binary_testing_output_data();

   if(outputs_number == 1) // Binary classification 
   {
      Matrix<int> confusion(2, 2);
      int true_positive = 0;
	  int false_positive = 0;
	  int false_negative = 0;
	  int true_negative = 0;

      for(int i = 0; i < testing_instances_number; i++)
	  {
	     if(binary_testing_output_data[0][i] == true && binary_testing_target_data[0][i] == true)
		 {
		    true_positive++;
		 }
		 else if(binary_testing_output_data[0][i] == true && binary_testing_target_data[0][i] == false)
		 {
		    false_positive++;
		 }
		 else if(binary_testing_output_data[0][i] == false && binary_testing_target_data[0][i] == true)
		 {
		    false_negative++;
		 }
		 else if(binary_testing_output_data[0][i] == false && binary_testing_target_data[0][i] == false)
		 {
		    true_negative++;
		 }
		 else
		 {

            exit(1);		 
		 }

         confusion[0][0] = true_positive;
         confusion[0][1] = false_positive;
         confusion[1][0] = false_negative;
         confusion[1][1] = true_negative;
	  }

      return(confusion);	  
   }
   else
   {
      Matrix<int> confusion(outputs_number, outputs_number, 0);

      int predicted_class = 0;
	  int actual_class = 0;

      for(int i = 0; i < testing_instances_number; i++)
	  {         
	     for(int j = 0; j < outputs_number; j++)
		 {
		    if(binary_testing_output_data[i][j] == true)
			{
			   predicted_class = j;
			}
		    if(binary_testing_target_data[i][j] == true)
			{
			   actual_class = j;
			}			
		 }

		 confusion[predicted_class][actual_class] += 1;
	  }

      return(confusion);	  
   }
}



// Vector<double> calculate_binary_classification_test(void) method

/// This method returns the results of a binary classification test in a single vector.
/// The size of that vector is six.
/// The elements are:
/// <ul>
/// <li> Classification accuracy
/// <li> Error rate
/// <li> Sensitivity
/// <li> Specifity
/// <li> Positive likelihood
/// <li> Negative likelihood
/// </ul>

Vector<double> PatternRecognitionUtilities::calculate_binary_classification_test(void)
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   int inputs_number = multilayer_perceptron_pointer->get_inputs_number();

   if(input_target_data_set_pointer == NULL)
   {
	   TRACE0("Flood Error: PatternRecognitionUtilities class.\n");
	   TRACE0("Vector<double> calculate_binary_classification_test(void).\n");
	   TRACE0("Input-target data set object cannot be null.\n");

      exit(1);   
   }

   int input_variables_number = input_target_data_set_pointer->get_input_variables_number();
   int target_variables_number = input_target_data_set_pointer->get_target_variables_number();

   int outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Control sentence
   
   if(inputs_number != input_variables_number)
   {
	   TRACE0("Flood Error: PatternRecognitionUtilities class.\n");
	   TRACE0("Vector<double> calculate_binary_classification_test(void).\n");
	   TRACE0("Number of inputs in multilayer perceptron must be equal to number of input variables in input target data set.\n");

      exit(1);
   }
   else if(outputs_number != 1)
   {
	   TRACE0("Flood Error: PatternRecognitionUtilities class.\n");
	   TRACE0("Vector<double> calculate_binary_classification_test(void).\n");
	   TRACE0("Number of outputs in multilayer perceptron must be one.\n");

      exit(1);
   }
   else if(target_variables_number != 1)
   {
	   TRACE0("Flood Error: PatternRecognitionUtilities class.\n");
	   TRACE0("Vector<double> calculate_binary_classification_test(void).\n");
	   TRACE0("Number of target variables in input-target data set must be one.\n");

      exit(1);
   }

   #endif

   // Confusion matrix

   Matrix<int> confusion = calculate_confusion();

   int true_positive = confusion[0][0];
   int false_positive = confusion[0][1];
   int false_negative = confusion[1][0];
   int true_negative = confusion[1][1];

   // Classification accuracy

   double classification_accuracy = (double)(true_positive + true_negative)/double(true_positive + true_negative + false_positive + false_negative);

   // Error rate

   double error_rate = (double)(false_positive + false_negative)/(double)(true_positive + true_negative + false_positive + false_negative);

   // Sensitivity

   double sensitivity = (double)true_positive/(double)(true_positive + false_negative);

   // Specifity

   double specifity = (double)true_negative/(double)(true_negative + false_positive);

   // Positive likelihood

   double positive_likelihood = sensitivity/(1.0 - specifity);

   // Negative likelihood

   double negative_likelihood = specifity/(1.0 - sensitivity);

   Vector<double> binary_classification_test(6);
   binary_classification_test[0] = classification_accuracy;
   binary_classification_test[1] = error_rate;
   binary_classification_test[2] = sensitivity;
   binary_classification_test[3] = specifity;
   binary_classification_test[4] = positive_likelihood;
   binary_classification_test[5] = negative_likelihood;

   return(binary_classification_test);
}



Vector<double> PatternRecognitionUtilities::binary_classification_test(void)
{
	Vector<double> binary_classification_test = calculate_binary_classification_test();
	
	return binary_classification_test;

}

}

