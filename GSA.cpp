// ----------------------------------------------------
//     Project: Gravitational Search Algorithm
//	      File: GSA.cpp  
// Description: Implementations for GSA
//   Last date: November 27, 2017
//	   Version: v1.0
//-----------------------------------------------------

#include "stdafx.h"
#include "GSA.h"


void ParticleGSA::space_bound(int dim, double MIN, double MAX)
{
	for (int i = 0; i < dim; i++)
	{
		if (Data[i] < MIN) Data[i] = MIN;
		if (Data[i] > MAX) Data[i] = MAX;
	}
}

GSA::GSA(int particles, int dimension)
{
	Num_particles = particles;
	Problem_size = dimension;
}

void GSA::init(double min_limit, double max_limit)
{
	#ifdef MAXIMIZE
		Best = DBL_MIN; //For maximization
	#else
		Best = DBL_MAX; //For minimization
	#endif
	MAX = max_limit;
	MIN = min_limit;
	Particles.clear();
	for (int i = 0; i < Num_particles; i++)
	{
		ParticleGSA temp;
		double temp2;
		for (int j = 0; j < Problem_size; j++)
		{
			temp2 = MIN + (((double)rand() / RAND_MAX) * (MAX - MIN));
			temp.Data.push_back(temp2);
			temp.velocity.push_back(0);
		}
		temp.value = Best;
		Particles.push_back(temp);
	}
}


void GSA::optimize(double(*f)(vector<double>), int Iterations)
{
	const clock_t begin_time = clock();	
	
	for (int t = 1; t < Iterations; t++)
	{
		// Evaluate
		for (int i = 0; i < Num_particles; i++)
		{
			Particles[i].space_bound(Problem_size, MIN, MAX);
			Particles[i].value = (*f)(Particles[i].Data);
			if (Particles[i].value < Best)
			{
				Best = Particles[i].value;
			}
		}

		// Calculate Mass
		double minf = DBL_MAX;
		double maxf = DBL_MIN;
		for (int i = 0; i < Num_particles; i++)
		{
			if (Particles[i].value < minf)
			{
				minf = Particles[i].value;
			}
			if (Particles[i].value > maxf)
			{
				maxf = Particles[i].value;
			}			
		}
		double sumM = 0.0;
		for (int i = 0; i < Num_particles; i++)
		{
			Particles[i].M = (Particles[i].value - maxf) / (minf - maxf);
			sumM += Particles[i].M;
		}
		for (int i = 0; i < Num_particles; i++)
		{
			Particles[i].M = Particles[i].M / sumM;
		}

		// Calculate Force vector
		double G = GSA_G0 * exp((double)(-GSA_alpha*t)/Iterations);
		for (int i = 0; i < Num_particles; i++)
		{
			// Accleration
			vector<double> A(Problem_size, 0);
			for (int j = 0; j < Num_particles; j++)
			{
				if (i != j)
				{
					vector<double> F(Problem_size,0);
					double sq_sumF = 0.0;
					for (int k = 0; k < Problem_size; k++)
					{
						F[k] = Particles[j].Data[k] - Particles[i].Data[k];
						sq_sumF += F[k] * F[k];
					}
					double R = sqrt(sq_sumF);
					double r = (rand() / (double)RAND_MAX);
					for (int k = 0; k < Problem_size; k++)
					{
						A[k] += r * G * Particles[j].M * F[k] / (R+0.0000000000025);
					}
				}	
			}
			// Velocity and position
			for (int k = 0; k < Problem_size; k++)
			{
				double r = (rand() / (double)RAND_MAX);
				Particles[i].velocity[k] = r * Particles[i].velocity[k] + A[k];
				
			}
		}
		for (int i = 0; i < Num_particles; i++)
		{
			for (int k = 0; k < Problem_size; k++)
			{
				Particles[i].Data[k] += Particles[i].velocity[k];
			}
		}
	}
	run_time = float(clock() - begin_time) / CLOCKS_PER_SEC;
}
