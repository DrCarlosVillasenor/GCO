// ----------------------------------------------------
//     Project: Genetic Algorithm
//	      File: GA.h    
// Description: Structures for GA
//   Last date: November 28, 2017
//	   Version: v1.0
//-----------------------------------------------------

#include <time.h>
#include <float.h>
#include <vector>
using namespace std;

#define MutationRate 0.2

struct Fenotype {
	vector<double> Data;
	double value;
	double fit;
	void Copy(Fenotype Source, int dim);
	void space_bound(int dim, double MIN, double MAX);
};

struct GA{
private:
	vector<Fenotype> Fenotypes;
	int Num_particles;
	int Problem_size;
	double MAX;
	double MIN;
	void CalculateFit(double(*f)(vector<double>));
	void FindMates();
	int RouletteSelect(int initial);
	void Mate();
	void Mutate();
public:
	void init(double min_limit, double max_limit);
	double Best;
	double run_time;
	GA(int particles, int dimension);
	void optimize(double(*f)(vector<double>), int Iterations);
};
