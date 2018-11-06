// ----------------------------------------------------
//		Author: M. S. Caros Vilaseñor
//     Project: Partile Swarm Optimization algorithm
//	      File: PSO.cpp
// Description: PSO implementations
//   Last date: February, 2017
//	   Version: 3.0
//-----------------------------------------------------
 
// Headers
#include "stdafx.h"
#include "PSO.h"
#include <iostream>
using namespace std;

void PSO::init(double min_limit, double max_limit)
{
	Best_Index = 0;
	MAX = max_limit;
	MIN = min_limit;
	#ifdef PSO_MAXIMIZE
		Best = DBL_MIN; //For maximization
	#else
		Best = DBL_MAX; //For minimization
	#endif
	Particles.clear();
	for (int i = 0; i<Num_particles; i++)
	{
		PSO_Particle temp;
		double temp2;
		for (int j = 0; j<Problem_size; ++j)
		{
			temp.velocity.push_back(0.0);
			temp2 = MIN + (rand() / (double)RAND_MAX) * (MAX - MIN);
			temp.Data.push_back(temp2);
			temp.pBest.push_back(temp2);
		}
		temp.bestValue = Best;
		Particles.push_back(temp);
	}
}

PSO::PSO(int particles, int dimension)
{
	Num_particles = particles;
	Problem_size = dimension;
}

void PSO::optimize(double(*f)(vector<double>), int Iterations)
{
	const clock_t begin_time = clock();
	for (int iter = 0; iter < Iterations; iter++)
	{
		Update_Velocity_Position();
		Update_pBest_Best(f);
	}
	run_time = float(clock() - begin_time) / CLOCKS_PER_SEC;	
}

void PSO::Update_Velocity_Position()
{
	double temp = 0.0;
	for (int i = 0; i<Num_particles; i++)
	{
		for (int j = 0; j<Problem_size; j++)
		{
			// Velocity update equation.
			Particles[i].velocity[j] = (PSO_W*Particles[i].velocity[j]) + (PSO_C1 * (rand() / (double)RAND_MAX)  *
				(Particles[i].pBest[j] - Particles[i].Data[j])) +
				(PSO_C2 * (rand() / (double)RAND_MAX)  * (Particles[Best_Index].Data[j] - Particles[i].Data[j]));

			// Particle updateequation
			temp = Particles[i].Data[j] + Particles[i].velocity[j];

			// Restrict position with Max and Min
			if (temp < MAX && temp > MIN)
			{
				Particles[i].Data[j] = temp;
			}
			else
			{
				if (temp > MAX) Particles[i].Data[j] = MAX;
				if (temp < MIN) Particles[i].Data[j] = MIN;
			}
		}
	}
}


void PSO::Update_pBest_Best(double(*f)(vector<double>))
{
	double output = 0.0;
	for (int i = 0; i < Num_particles; i++)
	{
		output = (*f)(Particles[i].Data);
		#ifdef PSO_MAXIMIZE
			if (output > particles[i].bestValue) //For maximization
		#else
			if (output < Particles[i].bestValue) //For minimization
		#endif
				{
					for (int j = 0; j < Problem_size; j++)
					{
						Particles[i].pBest[j] = Particles[i].Data[j];
					}
					Particles[i].bestValue = output;
				}
		#ifdef PSO_MAXIMIZE
			if (Particles[i].bestValue > Best) //For maximization
		#else
			if (Particles[i].bestValue < Best) //For minimization
		#endif
				{
					Best = Particles[i].bestValue;
					Best_Index = i;
				}
	}
}
