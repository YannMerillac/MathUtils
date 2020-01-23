/*
 * RBFinterp.cpp
 *
 *  Created on: 31 mai 2018
 *      Author: ymerillac
 */

#include "RBFinterp.h"
#include <cstring>
#include <iostream>
#include <math.h>

using namespace std;
using namespace Eigen;

double rbf_kernel(double r){
	return r*r*r;
	//return r*r*log(r+1.e-8);
}

RBFinterp::RBFinterp(double *src_x, int n_x, int m_x, double *src_y, int n_y, int m_y):
	n_x(n_x), m_x(m_x), n_y(n_y), m_y(m_y)
{
	// init use poly part
	use_poly_part = true;
	// init rbf smooth
	rbf_smooth=0;
	// fill x and y matrices
	x.resize(n_x,m_x);
	y.resize(n_x,m_y);
	for(int i=0;i<n_x;i++){
		for(int j=0;j<m_x;j++){
			x(i,j) = src_x[j+i*m_x];
		}
		for(int j=0;j<m_y;j++){
			y(i,j) = src_y[j+i*m_y];
		}
	}
	// set w matrix size
	//compute_weights();
}

RBFinterp::~RBFinterp() {
	//delete[] x;
	//delete[] y;
}

void RBFinterp::set_rbf_smooth(double smooth){
	rbf_smooth=smooth;
}

void RBFinterp::set_use_poly_part(bool poly_part){
	use_poly_part = poly_part;
}

void RBFinterp::display(){
	cout << "Size of x data " << n_x << " " << m_x << endl;
	cout << x << endl;
	cout << "Size of y data " << n_y << " " << m_y << endl;
	cout << y << endl;
}

void RBFinterp::compute_weights(){
	MatrixXd RBFmat = _build_rbf_matrix();
	cout<<"computing partialPivLu() decomposition ..."<<endl;
	cout << RBFmat.rows() << " " << RBFmat.cols() << endl;
	PartialPivLU<MatrixXd> LUdec(RBFmat);
	cout<<"solving ..."<<endl;
	MatrixXd b;
	if(use_poly_part){
		b = MatrixXd::Zero(n_x+m_x+1, m_y);
		b.topRows(y.rows()) = y;
	}
	else{
		b = y;
	}
	cout << b.rows() << " " << b.cols() << endl;
	w = LUdec.solve(b);
	cout<<"done ..."<<endl;
}

MatrixXd RBFinterp::_build_rbf_matrix(){
	double dist;
	int matrix_size = n_x;
	if(use_poly_part) matrix_size+=m_x+1;
	MatrixXd RBFmat = MatrixXd::Zero(matrix_size, matrix_size);
	for (int i = 0; i < n_x; i++)
	{
		for (int j = 0; j < i; j++)
		{
			dist = (x.row(i) - x.row(j)).norm();
			RBFmat(i, j) = rbf_kernel(dist);
			RBFmat(j, i) = RBFmat(i, j);
		}
		RBFmat(i, i)+=rbf_smooth;
	}
	// add polynomial part if needed
	if(use_poly_part){
		MatrixXd P(n_x, m_x + 1);
		P.leftCols(1) = MatrixXd::Ones(n_x, 1);
		P.rightCols(m_x) = x;
		RBFmat.topRightCorner(P.rows(), P.cols()) = P;
		RBFmat.bottomLeftCorner(P.cols(), P.rows()) = P.transpose();
	}
	return RBFmat;
}


void RBFinterp::interpolate(double *x_eval, int n_x_eval, int m_x_eval,
			                double *y_eval, int n_y_eval, int m_y_eval){

	double dx,dist,dist2;
	int size_rj = n_x;
	if(use_poly_part) size_rj+=m_x+1;
	VectorXd rj = VectorXd(size_rj);
	for(int j=0;j<n_x_eval;j++){
		for(int i=0;i<n_x;i++){
			dist2=0.;
			for(int k=0;k<m_x;k++){
				dx = x_eval[k+j*m_x]-x(i,k);
				dist2+=dx*dx;
			}
			dist = sqrt(dist2);
			rj(i) = rbf_kernel(dist);
		}
		if(use_poly_part){
			rj(n_x)=1.;
			for(int k=0;k<m_x;k++){
				rj(k+n_x+1) = x_eval[k+j*m_x];
			}
		}
		for(int k=0;k<m_y;k++){
			y_eval[k+j*m_y] = rj.dot(w.col(k));
		}
	}
}
