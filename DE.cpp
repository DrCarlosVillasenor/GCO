// ----------------------------------------------------
//     Project: Diferential Evolution
//	      File: DE.cpp  
// Description: Implementations for DE algorithm
//   Last date: September 17, 2017
//	   Version: v1.0
//-----------------------------------------------------

#include "stdafx.h"
#include "DE.h"

void Particle::Copy(Particle Source)
{
	for (int i = 0; i < Data.size(); i++)
	{
		Data[i] = Source.Data[i];
	}
	Best_value = Source.Best_value;
}

void DE::init(double min_limit, double max_limit)
{
#ifdef MAXIMIZE
	Best = DBL_MIN; //For maximization
#else
	Best = DBL_MAX; //For minimization
#endif
	MAX = max_limit;
	MIN = min_limit;
	Best_index = 0;
	Particles.clear();
	for (int i = 0; i < Num_particles; i++)
	{
		Particle temp;
		double temp2;
		for (int j = 0; j < Problem_size; j++)
		{
			temp2 = MIN + (((double)rand() / RAND_MAX) * (MAX - MIN));
			temp.Data.push_back(temp2);
		}
		temp.Best_value = Best;
		Particles.push_back(temp);
	}
}

// Diferential Evolution constructor
DE::DE(int particles, int dimension)
{ 
	Num_particles = particles;
	Problem_size = dimension;
}

// Germinal center reaction
void DE::optimize(double(*f)(vector<double>), int Iterations)
{
	const clock_t begin_time = clock();	
	
	for (int i = 0; i < Iterations; i++)
	{
		for (int j = 0; j < Num_particles; j++)
		{
			Particle Candidate;
			int ri1, ri2, ri3;
			
			do {
				ri1 = rand() % Num_particles;
			} while (ri1 == j);
			do
			{
				ri2 = rand() % Num_particles;
			} while (ri2 == ri1 || ri2 == j);
			do
			{
				ri3 = rand() % Num_particles;
			} while (ri3 == ri2 || ri3 == ri1 || ri3 == j);

			for (int k = 0; k < Problem_size; k++)
			{
				double temp;
				if (((double)rand() / RAND_MAX) < CR)
				{
					temp = Particles[ri1].Data[k] + F * (Particles[ri2].Data[k] - Particles[ri3].Data[k]);
					if (temp > MAX) temp = MAX;
					if (temp < MIN) temp = MIN;
					Candidate.Data.push_back(temp);
				}
				else
				{
					Candidate.Data.push_back(Particles[j].Data[k]);
				}
			}

			//Evaluate Objective function
			double r = (*f)(Candidate.Data);

			//Selection of the mutate Particle
			#ifdef MAXIMIZE
			if (r > Particles[j].Best_value) //For maximization
			#else
			if (r < Particles[j].Best_value) //For minimization
			#endif
			{
				Particles[j].Copy(Candidate);
				Particles[j].Best_value = r;
			}
			#ifdef MAXIMIZE
			if (r > Best) //For maximization
			#else
			if (r < Best) //For minimization
			#endif
			{
				Best_index = j;
				Best = r;
			}
		}
	}
	run_time = float(clock() - begin_time) / CLOCKS_PER_SEC;
}