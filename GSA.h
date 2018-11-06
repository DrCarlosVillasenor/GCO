// ----------------------------------------------------
//     Project: Gravitational search algorithm
//	      File: GSA.h    
// Description: Structures for GSA
//   Last date: November 27, 2017
//	   Version: v1.0
//-----------------------------------------------------

#include <time.h>
#include <float.h>
#include <vector>
#include <math.h>
using namespace std;

//#define MAXIMIZE
#define GSA_G0 100                     
#define GSA_alpha 20


struct ParticleGSA {
	vector<double> Data;
	vector<double> velocity;
	double M;
	double value;
	void space_bound(int dim, double min, double max);
};

struct GSA{
private:
	vector<ParticleGSA> Particles;
	int Num_particles;
	int Problem_size;
	double MAX;
	double MIN;
public:
	void init(double min_limit, double max_limit);
	double Best;
	double run_time;
	GSA(int particles, int dimension);
	void optimize(double(*f)(vector<double>), int Iterations);
};

