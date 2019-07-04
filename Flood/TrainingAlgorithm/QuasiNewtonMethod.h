

#ifndef __QUASINEWTONMETHOD_H__
#define __QUASINEWTONMETHOD_H__

#include "TrainingAlgorithm.h"
#include "../ObjectiveFunctional/ObjectiveFunctional.h"

namespace Flood
{

/// This concrete class represents a quasi-Newton training algorithm for an objective functional of a multilayer 
/// perceptron.

class QuasiNewtonMethod : public TrainingAlgorithm
{

public:

   // ENUMERATIONS

   /// Enumeration of the available training operators for obtaining the approximation to the inverse Hessian.

   enum InverseHessianApproximationMethod{DFP, BFGS};


   // GENERAL CONSTRUCTOR

   explicit QuasiNewtonMethod(ObjectiveFunctional*);


   // DEFAULT CONSTRUCTOR

   explicit QuasiNewtonMethod(void);


   // DESTRUCTOR

   virtual ~QuasiNewtonMethod(void);


   // METHODS

   // Get methods

   InverseHessianApproximationMethod get_inverse_Hessian_approximation_method(void);
   std::string get_inverse_Hessian_approximation_method_name(void);

   // Set methods

   void set_inverse_Hessian_approximation_method(const InverseHessianApproximationMethod&);
   void set_inverse_Hessian_approximation_method(const std::string&);

   // Train methods

   Vector<double> calculate_training_direction(const Vector<double>&, const Matrix<double>&);

   Matrix<double> calculate_inverse_Hessian_approximation(const Vector<double>&, const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&);

   Vector<double> calculate_gradient_descent_training_direction(const Vector<double>&);
   
   void train(void);

   // Training history methods

   void resize_training_history(int);

   void set_reserve_all_training_history(bool);


   //draw image

   void DrawMeanSquarError(CArray<double, double> &);
   

private: 

   // FIELDS

   /// Variable containing the actual method used to obtain a suitable training rate. 

   InverseHessianApproximationMethod inverse_Hessian_approximation_method;

};

}

#endif



