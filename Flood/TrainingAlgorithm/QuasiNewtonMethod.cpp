
// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <ctime>

#include "..\..\BP\stdafx.h"
#include "..\..\BP\resource.h"
#include "..\..\BP\stdafx.h"
// Flood includes

#include "QuasiNewtonMethod.h"

namespace Flood
{

// GENERAL CONSTRUCTOR

/// General constructor. It creates a quasi-Newton method training algorithm object associated to an objective 
/// functional object. 
/// It also initializes the class members to their default values.
/// @param new_objective_functional_pointer Pointer to an objective functional object.

QuasiNewtonMethod::QuasiNewtonMethod(ObjectiveFunctional* new_objective_functional_pointer)
: TrainingAlgorithm(new_objective_functional_pointer)
{
   // Inverse Hessian approximation method

   inverse_Hessian_approximation_method = BFGS;
}


// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a quasi-Newton method training algorithm object not associated to any 
/// objective functional object. 
/// It also initializes the class members to their default values.

QuasiNewtonMethod::QuasiNewtonMethod(void) : TrainingAlgorithm()
{
   // Inverse Hessian approximation method

   inverse_Hessian_approximation_method = BFGS;
}


// DESTRUCTOR

/// Destructor.

QuasiNewtonMethod::~QuasiNewtonMethod(void)
{
}


// METHODS


// InverseHessianApproximationMethod get_inverse_Hessian_approximation_method(void) method

/// This method returns the method for approximating the inverse Hessian matrix to be used when training. 

QuasiNewtonMethod::InverseHessianApproximationMethod QuasiNewtonMethod::get_inverse_Hessian_approximation_method(void)
{
   return(inverse_Hessian_approximation_method);
}


// std::string get_inverse_Hessian_approximation_method_name(void) method

/// This method returns the name of the method for the approximation of the inverse Hessian. 

std::string QuasiNewtonMethod::get_inverse_Hessian_approximation_method_name(void)
{
   switch(inverse_Hessian_approximation_method)
   {
      case DFP:
      {
         return("DFP");
	  }
      break;

      case BFGS:
      {
         return("BFGS");
	  }
      break;

	  default:
      {

#ifdef _DEBUG

		TRACE0("Flood Error: QuasiNewtonMethod class.\n");
		TRACE0("std::string get_inverse_Hessian_approximation_method_name(void) method.\n");
		TRACE0("Unknown inverse Hessian approximation method.\n");

#endif

         exit(1);
	  }
      break;
   }
}


// void set_inverse_Hessian_approximation_method(const InverseHessianApproximationMethod&) method

/// This method sets a new inverse Hessian approximatation method value. 
/// @param new_inverse_Hessian_approximation_method Inverse Hessian approximation method value.

void QuasiNewtonMethod::set_inverse_Hessian_approximation_method(const QuasiNewtonMethod::InverseHessianApproximationMethod& 
new_inverse_Hessian_approximation_method)
{
   inverse_Hessian_approximation_method = new_inverse_Hessian_approximation_method;
}


// void set_inverse_Hessian_approximation_method(const std::string&) method

/// This method sets a new method for approximating the inverse of the Hessian matrix from a string containing the name. 
/// Possible values are:
/// <ul>
/// <li> "DFP"
/// <li> "BFGS"
/// <ul>
/// @param new_inverse_Hessian_approximation_method_name Name of inverse Hessian approximation method.  

void QuasiNewtonMethod::set_inverse_Hessian_approximation_method(const std::string& new_inverse_Hessian_approximation_method_name)
{
   if(new_inverse_Hessian_approximation_method_name == "DFP")
   {
      inverse_Hessian_approximation_method = DFP;
   }
   else if(new_inverse_Hessian_approximation_method_name == "BFGS")
   {
      inverse_Hessian_approximation_method = BFGS;
   }
   else
   {

#ifdef _DEBUG
      
	   TRACE0("Flood Error: QuasiNewtonMethod class.\n");
	   TRACE0("void set_inverse_Hessian_approximation_method(const std::string&) method.\n");
	   TRACE1("Unknown inverse Hessian approximation method:  %s .\n", new_inverse_Hessian_approximation_method_name);

#endif

      exit(1);   
   }
}


// void set_reserve_all_training_history(bool) method

/// This method makes the training history of all variables to reseved or not in memory.
/// @param new_reserve_all_training_history True if the training history of all variables is to be reserved, 
/// false otherwise.

void QuasiNewtonMethod::set_reserve_all_training_history(bool new_reserve_all_training_history)
{
   reserve_elapsed_time_history = new_reserve_all_training_history;
   reserve_parameters_history = new_reserve_all_training_history;
   reserve_parameters_norm_history = new_reserve_all_training_history;
   reserve_evaluation_history = new_reserve_all_training_history;
   reserve_gradient_history = new_reserve_all_training_history;
   reserve_gradient_norm_history = new_reserve_all_training_history;
   reserve_training_direction_history = new_reserve_all_training_history;
   reserve_training_rate_history = new_reserve_all_training_history;
}


// void resize_training_history(int) method

/// This method resizes all the training history vectors. 
/// @param new_size Size vectors containing the training history variables. 

void QuasiNewtonMethod::resize_training_history(int new_size)
{
   // Multilayer perceptron

   if(reserve_parameters_history)
   {
      parameters_history.resize(new_size);
   }

   if(reserve_parameters_norm_history)
   {
      parameters_norm_history.resize(new_size);
   }

   // Objective functional

   if(reserve_evaluation_history)
   {
      evaluation_history.resize(new_size);
   }

   if(reserve_gradient_history)
   {
      gradient_history.resize(new_size);
   }
 
   if(reserve_gradient_norm_history)
   {
      gradient_norm_history.resize(new_size);
   }

   if(reserve_inverse_Hessian_history)
   {
      inverse_Hessian_history.resize(new_size);
   }

   if(reserve_validation_error_history)
   {
      validation_error_history.resize(new_size);
   }

   // Training algorithm

   if(reserve_training_direction_history)
   {
      training_direction_history.resize(new_size);
   }

   if(reserve_training_rate_history)
   {
      training_rate_history.resize(new_size);
   }

   if(reserve_elapsed_time_history)
   {
      elapsed_time_history.resize(new_size);
   }
}



// Vector<double> calculate_inverse_Hessian_approximation(
// const Vector<double>&, const Vector<double>&, 
// const Vector<double>&, const Vector<double>&, 
// const Matrix<double>&) method

/// This method calculates an approximation of the inverse Hessian, accoring to the method used. 
/// @param old_parameters Another point of the objective function.
/// @param parameters Current point of the objective function
/// @param old_gradient Gradient at the other point. 
/// @param gradient Gradient at the current point. 
/// @param old_inverse_Hessian Inverse Hessian at the other point of the objective function.

Matrix<double> QuasiNewtonMethod::calculate_inverse_Hessian_approximation(
const Vector<double>& old_parameters, const Vector<double>& parameters, 
const Vector<double>& old_gradient, const Vector<double>& gradient,
const Matrix<double>& old_inverse_Hessian)
{
   switch(inverse_Hessian_approximation_method)
   {
      case DFP:
      {
         return(objective_functional_pointer->calculate_DFP_inverse_Hessian(old_parameters, parameters, old_gradient, gradient, old_inverse_Hessian));
      }
      break;

      case BFGS:
      {
         return(objective_functional_pointer->calculate_BFGS_inverse_Hessian(old_parameters, parameters, old_gradient, gradient, old_inverse_Hessian));
      }
      break;

	  default:
	  {

#ifdef _DEBUG
         
	TRACE0("Flood Error: QuasiNewtonMethod class.\n");
	TRACE0("Vector<double> calculate_inverse_Hessian_approximation(const Vector<double>&, \
		const Vector<double>&, const Vector<double>&, const Vector<double>&, const Matrix<double>&) method.\n");
	TRACE0("Unknown inverse Hessian approximation method.\n");
			
#endif

         exit(1);	  
	  }
	  break;
   }
}


// Vector<double> calculate_training_direction(const Vector<double>&, const Matrix<double>&) method

Vector<double> QuasiNewtonMethod::calculate_training_direction(const Vector<double>& gradient, const Matrix<double>& inverse_Hessian)
{
   Vector<double> training_direction = inverse_Hessian.dot(gradient)*(-1.0);
 
   double training_direction_norm = training_direction.calculate_norm();

   return(training_direction/training_direction_norm);
}


// Vector<double> calculate_gradient_descent_training_direction(const Vector<double>&) method

Vector<double> QuasiNewtonMethod::calculate_gradient_descent_training_direction(const Vector<double>& gradient)
{
   double gradient_norm = gradient.calculate_norm(); 

   return(gradient/(-1.0*gradient_norm));   
}


// void train(void) method

/// This method trains a multilayer perceptron with an associated objective function according to the quasi-Newton
/// method.
/// Training occurs according to the training operators, training parameters and stopping criteria.

void QuasiNewtonMethod::train(void)
{
   // Control sentence (if debug)

#ifdef _DEBUG 

   if(objective_functional_pointer == NULL)
   {
	   TRACE0("Flood Error: QuasiNewtonMethod class.\n");
	   TRACE0("void train(void) method.\n");
	   TRACE0("Pointer to objective functional object cannot be NULL.");
       exit(1);
   }

#endif

   HWND hWnd;
   int i = 0;
   CArray<double, double> m_MeanSquarError;
   //m_MeanSquarError.SetSize(100);
   //double m_MeanSquarError[100] = {0.0};
     
   // Multilayer perceptron stuff

   MultilayerPerceptron* multilayer_perceptron_pointer = objective_functional_pointer->get_multilayer_perceptron_pointer();

   int parameters_number = multilayer_perceptron_pointer->get_parameters_number();

   Vector<double> parameters(parameters_number);
   Vector<double> old_parameters(parameters_number);
   double parameters_norm;

   Vector<double> parameters_increment(parameters_number);
   double parameters_increment_norm;

   // Objective functional stuff

   double validation_error = 0.0; 
   double old_validation_error = 0.0;
   double validation_error_increment = 0.0;
      
   double evaluation = 0.0;
   double old_evaluation = 0.0;
   double evaluation_improvement = 0.0;

   Vector<double> gradient(parameters_number);
   Vector<double> old_gradient(parameters_number);
   double gradient_norm;

   Matrix<double> inverse_Hessian(parameters_number, parameters_number);
   Matrix<double> old_inverse_Hessian(parameters_number, parameters_number);

   // Training algorithm stuff 

   Vector<double> training_direction(parameters_number);

   double training_slope;

   double initial_training_rate = 0.0;
   double training_rate = 0.0;
   double old_training_rate = 0.0;

   Vector<double> training_rate_evaluation(2);

   bool stop_training = false;

   double elapsed_time = 0.0;

   resize_training_history(maximum_epochs_number+1);

   CTime beginning_time = CTime::GetCurrentTime();
   time_t t1 = beginning_time.GetTime();
   // Main loop 

   for(int epoch = 0; epoch <= maximum_epochs_number; epoch++)
   {
      // Multilayer perceptron 

      parameters = multilayer_perceptron_pointer->get_parameters();

      parameters_norm = parameters.calculate_norm();

      if(parameters_norm >= warning_parameters_norm)
      {

#ifdef _DEBUG
		 TRACE1("Flood Warning: Parameters norm is %f.", parameters_norm);
#endif

      }

      // Objective functional stuff

	  if(epoch == 0)
      {      
         evaluation = objective_functional_pointer->calculate_evaluation();
         evaluation_improvement = 0.0; 
      }
      else
      {
         evaluation = training_rate_evaluation[1];
         evaluation_improvement = old_evaluation - evaluation; 
      }

      validation_error = objective_functional_pointer->calculate_validation_error();

      if(epoch == 0)
      {
         validation_error_increment = 0.0;
      }
      else 
      {
         validation_error_increment = validation_error - old_validation_error;
      }

      gradient = objective_functional_pointer->calculate_gradient();

      gradient_norm = gradient.calculate_norm();

      if(gradient_norm >= warning_gradient_norm)
      {

#ifdef _DEBUG 
		  TRACE1("Flood Warning: Gradient norm is %f.\n", gradient_norm);
#endif

      }

      if(epoch == 0)
      {
         inverse_Hessian.set_to_identity();
      }
      else
      {
		 inverse_Hessian = calculate_inverse_Hessian_approximation(old_parameters, parameters, old_gradient, gradient, old_inverse_Hessian);	
	  }

      // Training algorithm 

      training_direction = calculate_training_direction(gradient, inverse_Hessian);          

      // Calculate evaluation training_slope

      training_slope = (gradient/gradient_norm).dot(training_direction);

      // Check for a descent direction 

      if(training_slope >= 0.0)
      {
         // Reset training direction

         training_direction = calculate_gradient_descent_training_direction(gradient);
      }

      // Get initial training rate

      if(epoch == 0)
      {
         initial_training_rate = first_training_rate;
      }
      else
      {
         initial_training_rate = old_training_rate;
      }

      training_rate_evaluation = calculate_training_rate_evaluation(evaluation, training_direction, initial_training_rate);

      training_rate = training_rate_evaluation[0];      

      if(epoch != 0 && training_rate < 1.0e-99)
      {
         // Reset training direction

         training_direction = calculate_gradient_descent_training_direction(gradient);         

         training_rate_evaluation = calculate_training_rate_evaluation(evaluation, training_direction, first_training_rate);

         training_rate = training_rate_evaluation[0];
      }

      parameters_increment = training_direction*training_rate;
      parameters_increment_norm = parameters_increment.calculate_norm();
      
      // Elapsed time

	  //训练时间无限长
      elapsed_time = 0;

      // Training history multilayer perceptron 

      if(reserve_parameters_history)
      {
         parameters_history[epoch] = parameters;                                
      }

      if(reserve_parameters_norm_history)
      {
         parameters_norm_history[epoch] = parameters_norm; 
      }

      // Training history objective functional

      if(reserve_evaluation_history)
      {
         evaluation_history[epoch] = evaluation;
      }

      if(reserve_validation_error_history)
      {
         validation_error_history[epoch] = validation_error;
      }

      if(reserve_gradient_history)
      {
         gradient_history[epoch] = gradient;                                
      }

      if(reserve_gradient_norm_history)
      {
         gradient_norm_history[epoch] = gradient_norm;
      }

      if(reserve_inverse_Hessian_history)
      {
         inverse_Hessian_history[epoch] = inverse_Hessian;
      }

      // Training history training algorithm

      if(reserve_training_direction_history)
      {
         training_direction_history[epoch] = training_direction;                                
      }

      if(reserve_training_rate_history)
      {
         training_rate_history[epoch] = training_rate;
      }

      if(reserve_elapsed_time_history)
      {
         elapsed_time_history[epoch] = elapsed_time;
      }

      // Stopping Criteria

      if(parameters_increment_norm <= minimum_parameters_increment_norm)
      {

#ifdef _DEBUG

		  TRACE1("Epoch %d: Minimum parameters increment norm reached.\n",epoch);
		  TRACE1("Parameters increment norm: %f\n", parameters_increment_norm);

#endif

         stop_training = true;
      }

      if(epoch != 0 && evaluation_improvement <= minimum_evaluation_improvement)
      {

#ifdef _DEBUG

		  TRACE1("Epoch %d: Minimum evaluation improvement reached.\n", epoch);
		  TRACE1("Evaluation improvement: %f\n", evaluation_improvement);

#endif

         stop_training = true;
      }

      else if(evaluation <= evaluation_goal)
      {

#ifdef _DEBUG

		  TRACE1("Epoch %d: Evaluation goal reached.\n",epoch);

#endif

         stop_training = true;
      }

      else if(early_stopping && epoch != 0 && validation_error_increment > 0.0)
      {

#ifdef _DEBUG

		  TRACE1("Epoch %d: Validation error stopped improving.\n",epoch);
		  TRACE1("Validation error increment: %f\n", validation_error_increment);

#endif
         stop_training = true;
      }

      else if(gradient_norm <= gradient_norm_goal)
      {

#ifdef _DEBUG

		  TRACE1("Epoch %d: Gradient norm goal reached.\n", epoch);

#endif

         stop_training = true;
      }

      else if(epoch == maximum_epochs_number)
      {

#ifdef _DEBUG

		  TRACE1("Epoch %d: Maximum number of epochs reached.\n", epoch);

#endif

         stop_training = true;
      }

      else if(elapsed_time >= maximum_time)
      {

#ifdef _DEBUG

		  TRACE1("Epoch %d: Maximum training time reached.\n", epoch);

#endif

         stop_training = true;
      }

      if(stop_training)
      {

#ifdef _DEBUG

		  TRACE1("Parameters norm: %f\n", parameters_norm);
		  TRACE1("Evaluation: %f\n", evaluation);

		  if (0 != validation_error)
		  {
			  TRACE1("Validation error: %f\n", validation_error);
		  }

		  TRACE1("Gradient norm: %f\n", gradient_norm);

		  //objective_functional_pointer->print_information();
		  TRACE1("Training rate: %f\n", training_rate);
		  TRACE1("Elapsed time: %f\n", elapsed_time);

#endif
 
         resize_training_history(1+epoch);

         break;
      }
      else if(0 == epoch )
      {
#ifdef _DEBUG
		  TRACE1("Epoch %d;\n",epoch);
		  TRACE1("Parameters norm: %f\n", parameters_norm);
		  TRACE1("Evaluation: %f\n", evaluation);
 
         if(validation_error != 0)
         {
			 TRACE1("Validation error: %f\n",validation_error);
         }

		 TRACE1("Gradient norm: %f\n", gradient_norm);

         //objective_functional_pointer->print_information();
		 TRACE1("Training rate: %f\n", training_rate);
		 TRACE1("Elapsed time: %f\n", elapsed_time);

#endif
      }

      // Update stuff

      old_parameters = parameters;

      old_evaluation = evaluation;

	  old_gradient = gradient;

	  old_inverse_Hessian = inverse_Hessian;
 
      old_training_rate = training_rate;

      if(early_stopping)
      {
         old_validation_error = validation_error;
      }

      // Set new parameters

      parameters += parameters_increment;

      multilayer_perceptron_pointer->set_parameters(parameters);

	  //m_MeanSquarError[i] = evaluation;
	  m_MeanSquarError.Add(evaluation);
	  i++;

   }

   CTime end_time = CTime::GetCurrentTime();
   time_t t2 = end_time.GetTime();

   hWnd = GetDlgItem(FindWindowA(NULL, "BP神经网络"), IDC_RUN_TIME);
   CString strRunTime;
   strRunTime.Format(_T("%d"), t2-t1);
   SetWindowTextW(hWnd, strRunTime);
   
   DrawMeanSquarError(m_MeanSquarError);

}


void QuasiNewtonMethod::DrawMeanSquarError(CArray<double,double>& MeanSquarError)
{
	//int num = 0;
	//for (int i = 0; i < MeanSquarError.GetSize(); i++)
	//{
	//	if (0.0 != MeanSquarError[i])
	//		num++;
	//	else
	//		break;
	//}

	const int size = MeanSquarError.GetSize();
	Vector<int> x(size);
	Vector<int> y(size);

	double Ymax = 0.0;
	//width = 401 , height = 221
	//Origin(50,171);
	//x轴长度 = 401-100 = 301 -> 280(实际范围)
	//y轴长度 = 221-60 = 141  -> 120(实际范围)
	//x轴映射关系：size->x.length
	//y轴映射关系：error->y.length
	for (int i = 1; i < size; i++)
	{
		Ymax = max(MeanSquarError[i], Ymax);
	}

	for (int i = 0; i < size; i++)
	{
		x[i] = (i) * 280 / size + 50;
		y[i] = 171 - (int)(MeanSquarError[i] * 120.0 / Ymax);
	}

	HWND hWnd;
	HDC hDC;
	CPen pen(PS_SOLID,1,RGB(255,0,0));

	hWnd = GetDlgItem(FindWindowA(NULL, "BP神经网络"), IDC_DRAW);
	hDC = GetDC(hWnd);
	HGDIOBJ OldPen = SelectObject(hDC, pen);

	MoveToEx(hDC, x[1], y[1],NULL);
	for (int i = 2; i < size; i++)
	{
		LineTo(hDC, x[i], y[i]);
	}

	SelectObject(hDC, OldPen);
	ReleaseDC(hWnd, hDC);

	HWND hWnd1;
	CString strERROR;
	double mean_error = MeanSquarError[size-1];  //训练结束时的误差
	int number = 1;
	for (int i = 0; i < 20; i++)
	{
		if (mean_error * 10 > 1.0)
			break;
		else
		{
			number++;
			mean_error *= 10;
		}
	}
	strERROR.Format(_T("%1.2f"), mean_error+1);
	strERROR += "e-";
	CString strNum;
	strNum.Format(_T("%d"), number);
	strERROR += strNum;

	hWnd1 = GetDlgItem(FindWindowA(NULL, "BP神经网络"), IDC_ERR_RATIO);
	SetWindowTextW(hWnd1, strERROR);

}

}



