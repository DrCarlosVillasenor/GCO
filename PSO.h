// ----------------------------------------------------
//		Author: M. S. Caros Vilaseñor
//     Project: Partile Swarm Optimization algorithm
//	      File: PSO.h
// Description: PSO declarations
//   Last date: February, 2017
//	   Version: 3.0
//-----------------------------------------------------

#include <time.h>
#include <float.h>
#include <vector>
using namespace std;

//#define MAXIMIZE
#define	PSO_C1			   1.49618	  
#define PSO_C2			   PSO_C1		  
#define PSO_W			   0.729844     


// Structures
struct PSO_Particle
{
	vector<double> Data;
	vector<double> velocity;
	vector<double> pBest;
	double bestValue;
};

struct PSO
{
	private:
		vector<PSO_Particle> Particles;
		int Best_Index;
		int Num_particles;
		int Problem_size;
		double MAX;
		double MIN;
		void Update_Velocity_Position();
		void Update_pBest_Best(double(*f)(vector<double>));

	public:
		int MAX_LIMITS;
		int MIN_LIMITS;
		double run_time;
		double Best;
		void init(double min_limit, double max_limit);
		PSO(int particles, int dimensio);
		void optimize(double(*f)(vector<double>), int Iterations);
};




