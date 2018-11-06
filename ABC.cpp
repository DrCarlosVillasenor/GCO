// ----------------------------------------------------
//		Author: M. Sc. Caros Vilaseñor
//     Project: Artificial Bee colony
//	      File: ABC.cpp
// Description: ABC implementations
//   Last date: October, 2017
//	   Version: 1.0
//-----------------------------------------------------

// Headers
#include "stdafx.h"
#include "ABC.h"
#include <iostream>
using namespace std;

void Bee::space_bound(int dim, double MIN, double MAX)
{
	for (int i = 0; i < dim; i++)
	{
		if (Data[i] < MIN) Data[i] = MIN;
		if (Data[i] > MAX) Data[i] = MAX;
	}
}

Bee::Bee(int dimensions, double min, double max)
{
	double temp2;
	for (int j = 0; j< dimensions; ++j)
	{
		temp2 = min + (rand() / (double)RAND_MAX) * (max - min);
		Data.push_back(temp2);
	}
	trials = 0;
}

Bee Bee::clone(int dim)
{
	Bee temp(dim, -1,1);
	for (int j = 0; j< dim; ++j)
	{
		temp.Data[j] = Data[j];
	}
	temp.trials = 0;
	temp.value = value;
	return temp;
}
void ABC_alg::init(double min_limit, double max_limit)
{
	MAX = max_limit;
	MIN = min_limit;
	Best_Index = 0;
	// Initial best:
	#ifdef MAXIMIZE
		Best = DBL_MIN; //For maximization
	#else
		Best = DBL_MAX; //For minimization
	#endif
	Bees.clear();
	// Initialize swarm:
	for (int i = 0; i < Num_bees; i++)
	{
		Bee temp(Problem_size, MIN, MAX);
		Bees.push_back(temp);
	}
}

ABC_alg::ABC_alg(int particles, int dimension)
{
	Num_bees = particles;
	Problem_size = dimension;
	Pf = Num_bees / 2;
	L = Num_bees* Problem_size / 2;
}

int ABC_alg::RouletteSelect()
{
	double sum = 0;
	for (int i = 0; i < Pf ; i++) {
		sum += Bees[i].value;
	}
	// get a random value
	double value = (rand() / (double)RAND_MAX) * sum;
	// locate the random value based on the weights
	for (int i = 0; i< Pf; i++) {
		value -= Bees[i].value;
		if (value <= 0) return i;
	}
	// when rounding errors occur, we return the last item's index 
	return Pf;
}


void ABC_alg::optimize(double(*f)(vector<double>), int Iterations)
{
	// Pseudo-Random number generator
	const clock_t begin_time = clock();

	// Initialize swarm:
	for (int i = 0; i < Num_bees; i++)
	{
		Bees[i].space_bound(Problem_size, MIN, MAX);
		Bees[i].value = (*f)(Bees[i].Data);
	}

	// Iterations
	for (int ite = 0; ite < Iterations; ite++)
	{
		// Forager Bees:
		for (int i = 0; i < Pf; i++)
		{
			int k, s;
			do 
			{
				k = rand() % Num_bees;

			} while (k == i);
			s = rand() % Problem_size;
			double r = -1 + (rand() / (double)RAND_MAX) * (2);
			Bee v = Bees[i].clone(Problem_size);
			v.Data[s] = Bees[i].Data[s] + r * (Bees[i].Data[s] - Bees[k].Data[s]);
			v.value = (*f)(v.Data);
			#ifdef MAXIMIZE
			if (v.value > Bees[i].value)
			#else
			if (v.value < Bees[i].value)
			#endif
			{
				Bees[i] = v.clone(Problem_size);
				Best_Index = i;
			}
			else
			{
				Bees[i].trials += 1;
			}			
		}

		// Onlooker Bees:
		for (int i = Pf; i < Num_bees; i++)
		{
			int j, k, s;
			j = RouletteSelect();
			do
			{
				k = rand() % Pf;

			} while (k == i);
			s = rand() % Problem_size;
			double r = -1 + (rand() / (double)RAND_MAX) * (2);
			Bee v = Bees[i].clone(Problem_size);
			v.Data[s] = Bees[j].Data[s] + r * (Bees[j].Data[s] - Bees[k].Data[s]);
			v.value = (*f)(v.Data);
			#ifdef MAXIMIZE
			if (v.value > Bees[i].value)
			#else
			if (v.value <  Bees[i].value)
			#endif
			{
				Bees[i] = v.clone(Problem_size);
				Best_Index = i;
			}
			else
			{
				Bees[i].trials += 1;
			}
			
		}

		// Scout Bees:
		for (int i = 0; i < Pf; i++)
		{
			if (Bees[i].trials > L)
			{
				Bee temp(Problem_size, MIN, MAX);
				temp.value = (*f)(temp.Data);
				Bees[i] = temp.clone(Problem_size);
			}
		}
	}
	for (int i = 0; i < Num_bees; i++)
	{
		#ifdef MAXIMIZE
		if (Bees[i].value > Best)
		#else
		if (Bees[i].value < Best)
		#endif
		{
			Best = Bees[i].value;
			Best_Index = i;
		}
	}
	run_time = float(clock() - begin_time) / CLOCKS_PER_SEC;
}
