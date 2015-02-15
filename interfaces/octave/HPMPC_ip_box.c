/**************************************************************************************************
* 
* Author: Gianluca Frison, giaf@imm.dtu.dk
*
* Factorizes in double precision the extended LQ control problem, factorized algorithm
*
**************************************************************************************************/

#include "mex.h"
#include <stdio.h>
#include <stdlib.h>
/*#include <math.h>*/

#include <hpmpc/c_interface.h>



// the gateway function 
void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
	{
		
	// get data 
	int k_max;
	double mu0, tol, *A, *B, *b, *Q, *Qf, *R, *S, *q, *qf, *r, *x, *u, *lb, *ub, *stat, *kkk;
	
	kkk = mxGetPr(prhs[0]);
	k_max = (int) mxGetScalar(prhs[1]);
	mu0 = mxGetScalar(prhs[2]);
	tol = mxGetScalar(prhs[3]);
	const int N  = (int) mxGetScalar(prhs[4]);
	const int nx = (int) mxGetScalar(prhs[5]);
	const int nu = (int) mxGetScalar(prhs[6]);
	const int nb = (int) mxGetScalar(prhs[7]);

	A = mxGetPr(prhs[8]);
	B = mxGetPr(prhs[9]);
	b = mxGetPr(prhs[10]);
	Q = mxGetPr(prhs[11]);
	Qf = mxGetPr(prhs[12]);
	R = mxGetPr(prhs[13]);
	S = mxGetPr(prhs[14]);
	q = mxGetPr(prhs[15]);
	qf = mxGetPr(prhs[16]);
	r = mxGetPr(prhs[17]);
	lb = mxGetPr(prhs[18]);
	ub = mxGetPr(prhs[19]);
	x = mxGetPr(prhs[20]);
	u = mxGetPr(prhs[21]);
	stat = mxGetPr(prhs[22]);
	
	int kk = -1;

	int work_space_size = hpmpc_ip_box_mpc_dp_work_space(nx, nu, N);
	
	double *work = (double *) malloc( work_space_size * sizeof(double) );

	// call solver 
	fortran_order_ip_box_mpc(&kk, k_max, mu0, tol, 'd', N, nx, nu, nb, A, B, b, Q, Qf, S, R, q, qf, r, lb, ub, x, u, work, stat);
	//c_order_ip_box_mpc(k_max, tol, 'd', nx, nu, N, A, B, b, Q, Qf, S, R, q, qf, r, lb, ub, x, u, work, &kk, stat);
	
	*kkk = (double) kk;

	free(work);

	return;

	}

