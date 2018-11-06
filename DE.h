// ----------------------------------------------------
//     Project: Diferencial Evolution
//	      File: DE.h    
// Description: Structures for DE algorithm
//   Last date: September 21, 2017
//	   Version: v1.0
//-----------------------------------------------------

#include <time.h>
#include <float.h>
#include <vector>
using namespace std;

//#define MAXIMIZE
#define CR 0.7                      
#define F 1.25

// Particle
struct Particle {
	vector<double> Data;
	double Best_value;
	void Copy(Particle Source);
};

// Diferential Evolution structure
struct DE{
private:
	vector<Particle> Particles;
	int Best_index;
	int Num_particles;
	int Problem_size;
	double MAX;
	double MIN;
public:
	void init(double min_limit, double max_limit);
	double Best;
	double run_time;
	DE(int particles, int dimension);
	void optimize(double(*f)(vector<double>), int Iterations);
};


