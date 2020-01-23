/*
 * RBFinterp.h
 *
 *  Created on: 31 mai 2018
 *      Author: ymerillac
 */

#ifndef RBFINTERP_H_
#define RBFINTERP_H_

#include <Eigen/Dense>
//using namespace Eigen;

class RBFinterp {

public:
	RBFinterp(double *x, int n_x, int m_x, double *y, int n_y, int m_y);
	virtual ~RBFinterp();
	void display();
	void compute_weights();
	void interpolate(double *x_eval, int n_x_eval, int m_x_eval,
			         double *y_eval, int n_y_eval, int m_y_eval);

	void set_use_poly_part(bool poly_part);
	void set_rbf_smooth(double smooth);

protected:
	Eigen::MatrixXd _build_rbf_matrix();

private:
	bool use_poly_part;
	int n_x;
	int m_x;
	int n_y;
	int m_y;
	double rbf_smooth;
	Eigen::MatrixXd x;
	Eigen::MatrixXd y;
	Eigen::MatrixXd w;


};

#endif /* RBFINTERP_H_ */
