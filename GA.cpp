// ----------------------------------------------------
//     Project: Genetic Algorithm
//	      File: GA.cpp  
// Description: Implementations for GA
//   Last date: November 28, 2017
//	   Version: v1.0
//-----------------------------------------------------

#include "stdafx.h"
#include "GA.h"

GA::GA(int particles, int dimension)
{
	Num_particles = particles;
	Problem_size = dimension;
}

void GA::init(double min_limit, double max_limit)
{
	#ifdef MAXIMIZE
		Best = DBL_MIN; //For maximization
	#else
		Best = DBL_MAX; //For minimization
	#endif
	MAX = max_limit;
	MIN = min_limit;
	Fenotypes.clear();
	for (int i = 0; i < Num_particles; i++)
	{
		Fenotype temp;
		double temp2;
		for (int j = 0; j < Problem_size; j++)
		{
			temp2 = MIN + (((double)rand() / RAND_MAX) * (MAX - MIN));
			temp.Data.push_back(temp2);
		}
		temp.value = Best;
		Fenotypes.push_back(temp);
	}
}

void GA::CalculateFit(double(*f)(vector<double>))
{
	double sumFit = 0.0;
	for (int j = 0; j < Num_particles; j++)
	{
		Fenotypes[j].space_bound(Problem_size, MIN, MAX);
		Fenotypes[j].value = 1/(1+(*f)(Fenotypes[j].Data));
		sumFit +=Fenotypes[j].value;
	}
	for (int j = 0; j < Num_particles; j++)
	{
		Fenotypes[j].fit =Fenotypes[j].value / sumFit;
	}
}

void Fenotype::space_bound(int dim, double MIN, double MAX)
{
	for (int i = 0; i < dim; i++)
	{
		if (Data[i] < MIN) Data[i] = MIN;
		if (Data[i] > MAX) Data[i] = MAX;
	}
}

int GA::RouletteSelect(int initial)
{
	double sum = 0;
	for (int i = initial; i < Num_particles; i++)
	{
		sum +=Fenotypes[i].fit;
	}
	double value = (rand() / (double)RAND_MAX) * sum;
	for (int i = initial; i< Num_particles; i++)
	{
		value -=Fenotypes[i].fit;
		if (value <= 0) return i;
	}
	return Num_particles - 1;
}


void GA::FindMates()
{
	for (int i = 0; i < Num_particles; i = i + 2)
	{
		int mate1, mate2;
		mate1 = RouletteSelect(i);
		do {
			mate2 = RouletteSelect(i);
		} while (mate1 == mate2);
		swap(Fenotypes[i],Fenotypes[mate1]);
		swap(Fenotypes[i+1],Fenotypes[mate2]);
	}
}

void Fenotype::Copy(Fenotype source, int dim)
{
	for (int k = 0; k < dim; k++)
	{
		Data[k] = source.Data[k];
	}
}

void GA::Mate()
{
	for (int i = 0; i < Num_particles; i = i + 2)
	{
		double beta, temp1, temp2;
		Fenotype child1, child2;
		for (int k = 0; k < Problem_size; k++)
		{
			beta = (rand() / (double)RAND_MAX);
			temp1 = beta * Fenotypes[i].Data[k] + (1 - beta) * Fenotypes[i + 1].Data[k];
			temp2 = (1 - beta) * Fenotypes[i].Data[k] + beta * Fenotypes[i + 1].Data[k];
			child1.Data.push_back(temp1);
			child2.Data.push_back(temp2);
		}
		Fenotypes[i].Copy(child1,Problem_size);
		Fenotypes[i+1].Copy(child2,Problem_size);
	}
}

void GA::Mutate()
{
	// Calculate mutations
	int mutations = ceil(MutationRate * Num_particles * Problem_size);
	for (int m = 0; m < mutations; m++)
	{
		int i, j;
		i = rand() % Num_particles;
		j = rand() % Problem_size;
		Fenotypes[i].Data[j] = MIN + (((double)rand() / RAND_MAX) * (MAX - MIN));
	}
}

void GA::optimize(double(*f)(vector<double>), int Iterations)
{
	const clock_t begin_time = clock();
	for (int i = 0; i < Iterations; i++)
	{
		CalculateFit(f);
		FindMates();
		Mate();
		Mutate();
	}
	CalculateFit(f);
	// Encontrar mejor
	for (int j = 0; j < Num_particles; j++)
	{
		if (Fenotypes[j].value < Best)
		{
			Best = Fenotypes[j].value;
		}
	}
	run_time = float(clock() - begin_time) / CLOCKS_PER_SEC;
}