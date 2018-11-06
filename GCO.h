// ----------------------------------------------------
//     Project: Germial center optimization
//	      File: GCO.h    
// Description: Structures for GCO algorithm
//   Last date: September 17, 2017
//	   Version: v6.0
//-----------------------------------------------------

//-----------------------------------------------------
//	Definitions and headers
//-----------------------------------------------------

#include <time.h>
#include <float.h>
#include <vector>
using namespace std;


//#define MAXIMIZE
#define CR 0.7
#define F 1.25

// B-cell
struct Bcell{
	vector<double> Data;
	int cells;
	double Life_signal;
	double Best_value;
	double fit;
	void Copy(Bcell Source);
};

// Germinal center
struct GCO{
private:
	vector<Bcell> Bcells;
	int cells;
	int Best_index;
	int Num_particles;
	int Problem_size;
	double MAX;
	double MIN;
	void Duplicate(int index);
	void Die(int index);
	void Mutate(int index, double(*f)(vector<double>));
	int Select();
public:
	double Best;
	double run_time;
	void init(double min_limit, double max_limit);
	GCO(int particles, int dimension);
	void optimize(double(*f)(vector<double>), int Iterations);
};


