// Comparaciones.cpp : Defines the entry point for the console application.
#include "windows.h"
#include "stdafx.h"
#include "GCO.h"
#include "DE.h"
#include "PSO.h"
#include "ABC.h"
#include "GSA.h"
#include "GA.h"
#include "bechmark.h"
#include <fstream>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	// Modificar esta sección---
	char* nameSolution = "Results/GCO_S2D.csv";
	char* nameTime = "Results/GCO_T2D.csv";
	int particles = 40;
	int dimension = 2;
	int num_test = 30;
	int iter = 500;
	GCO opt(particles, dimension);
	//--------------------------

	srand((unsigned int)time(NULL));

	ofstream mySolutions;
	ofstream myTime;
	mySolutions.precision(12);
	myTime.precision(7);
	mySolutions.open(nameSolution);
	myTime.open(nameTime);

	for (int test = 0; test < num_test; test++)
	{
		// Sphere function
		opt.init(-5.12, 5.12);
		opt.optimize(Sphere, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";


		// Sum squares function
		opt.init(-5.12, 5.12);
		opt.optimize(SumSqrt, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Rotated Hyper-ellipsoid function
		opt.init(-65.536, 65.536);
		opt.optimize(RHyperEllipsoid, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Perm 0 beta d function
		opt.init(-dimension, dimension);
		opt.optimize(Perm0bd, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Sums of differents powers
		opt.init(-1, 1);
		opt.optimize(SumDiffPow, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Trid function
		opt.init(-dimension*dimension, dimension*dimension);
		//opt.optimize(Trid, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Bochachevsky function 
		opt.init(-15, 15);
		opt.optimize(Bochachevsky, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Ackley function
		opt.init(-32.768, 32.768);
		opt.optimize(Ackley, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";


		// Griewank function
		opt.init(-600, 600);
		opt.optimize(Griewank, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Levy function
		opt.init(-32.768, 32.768);
		opt.optimize(Levy, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";


		// Rastrigin function
		opt.init(-5.12, 5.12);
		opt.optimize(Rastrigin, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";


		// Schwefel function
		opt.init(-500, 500);
		opt.optimize(Schwefel, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";


		// Zakharov function
		opt.init(-5, 10);
		opt.optimize(Zakharov, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Dixon-Price function
		opt.init(-10, 10);
		opt.optimize(DixonPrice, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Rosenbrock function
		opt.init(-2.048, 2.048);
		opt.optimize(Rosenbrock, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Michalewicz
		opt.init(0, Pi);
		//opt.optimize(Michalewicz, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";

		// Perm beta d function
		opt.init(-dimension, dimension);
		opt.optimize(Permbd, iter);
		mySolutions << opt.Best << ",";
		myTime << opt.run_time << ",";


		// Styblinski function
		opt.init(-5, 5);
		//opt.optimize(Styblinski, iter);
		mySolutions << opt.Best;
		myTime << opt.run_time;

		mySolutions << endl;
		myTime << endl;
		cout << test + 1 << endl;
	}
	return 0;
}