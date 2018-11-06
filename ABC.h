// ----------------------------------------------------
//		Author: M. Sc. Caros Vilaseñor
//     Project: Artificial Bee colony
//	      File: ABC.cpp
// Description: ABC declarations
//   Last date: October, 2017
//	   Version: 1.0
//-----------------------------------------------------

#include <time.h>
#include <float.h>
#include <vector>
using namespace std;

struct Bee
{
	vector<double> Data;
	int trials;
	double value;
	Bee(int dimensions, double min, double max);
	Bee clone(int dim);
	void space_bound(int dim, double MIN, double MAX);
};

struct ABC_alg
{
private:
	vector<Bee> Bees;
	int Best_Index;
	int Num_bees;
	int Problem_size;
	double MAX;
	double MIN;
	int Pf;
	int L;

public:
	double run_time;
	double Best;
	int RouletteSelect();
	void init(double min_limit, double max_limit);
	ABC_alg(int bees, int dimension);
	void optimize(double(*f)(vector<double>), int Iterations);
};
