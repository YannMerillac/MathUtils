%module RBFinterp

%{
#define SWIG_FILE_WITH_INIT
#include "RBFinterp/RBFinterp.h"
%}


%include "numpy.i"
%init %{
import_array();
%}

%apply (double* IN_ARRAY2,int DIM1,int DIM2) {(double *x, int n_x, int m_x)}
%apply (double* IN_ARRAY2,int DIM1,int DIM2) {(double *y, int n_y, int m_y)}
%apply (double* IN_ARRAY2,int DIM1,int DIM2) {(double *x_eval, int n_x_eval, int m_x_eval)}
%apply (double* INPLACE_ARRAY2,int DIM1,int DIM2) {(double *y_eval, int n_y_eval, int m_y_eval)}

%include "RBFinterp/RBFinterp.h"
