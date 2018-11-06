// ----------------------------------------------------
//     Project: Germial center optimization
//	      File: GCO_implementations.cpp  
// Description: Structures for GCO algorithm
//   Last date: September 17, 2017
//	   Version: v6.0
//-----------------------------------------------------

#include "stdafx.h"
#include "GCO.h"
#include <vector>
#include <iostream>


//-----------------------------------------------------
//	Structures implementations
//-----------------------------------------------------


void Bcell::Copy(Bcell Source)
{
	for (int i = 0; i < Data.size(); i++)
	{
		Data[i] = Source.Data[i];
	}
	Best_value = Source.Best_value;
	cells = Source.cells;
	Life_signal = Source.Life_signal;
}

void GCO::init(double min_limit, double max_limit)
{
#ifdef MAXIMIZE
	Best = DBL_MIN; //For maximization
#else
	Best = DBL_MAX; //For minimization
#endif
	Best_index = 0;
	cells = Num_particles;
	MAX = max_limit;
	MIN = min_limit;
	Bcells.clear();
	for (int i = 0; i < Num_particles; i++)
	{
		Bcell temp;
		double temp2;
		for (int j = 0; j < Problem_size; j++)
		{
			temp2 = MIN + (((double)rand() / RAND_MAX) * (MAX - MIN));
			temp.Data.push_back(temp2);
		}
		temp.Life_signal = 70;
		temp.cells = 1;
		temp.Best_value = Best;
		Bcells.push_back(temp);
	}
}

// Germinal Center Optimization contruction
GCO::GCO(int particles, int dimension)
{ 
	Num_particles = particles;
	Problem_size = dimension;
}

// Germinal center reaction
void GCO::optimize(double(*f)(vector<double>), int Iterations)
{
	const clock_t begin_time = clock();	
	for (int i = 0; i < Iterations; i++)
	{
		// Dark-zone process
		for (int j = 0; j < Num_particles; j++)
		{
			double destiny = ((double)rand() / RAND_MAX) * 100;
			if (destiny < Bcells[j].Life_signal)
			{
				Duplicate(j);
			}
			else 
			{
				Die(j);
			}
			Mutate(j, f);
		}
					
		// Light-zone process
		double minf = DBL_MAX;
		double maxf = DBL_MIN;
		for (int j = 0; j < Num_particles; j++)
		{
			Bcells[j].Life_signal -= 10;
			if (Bcells[j].Life_signal < 0) Bcells[j].Life_signal = 0;
			if (Bcells[j].Best_value < minf)
			{
				minf = Bcells[j].Best_value;
			}
			if (Bcells[j].Best_value > maxf)
			{
				maxf = Bcells[j].Best_value;
			}
		}
		double sumfit = 0.0;
		for (int j = 0; j < Num_particles; j++)
		{
			Bcells[j].fit = (Bcells[j].Best_value - maxf) / (minf - maxf);
			Bcells[j].Life_signal += Bcells[j].fit * 10;
			if (Bcells[Best_index].Life_signal > 100) Bcells[Best_index].Life_signal = 100;
		}
	}
	run_time = float(clock() - begin_time) / CLOCKS_PER_SEC;
}

//B-cell duplication
void GCO::Duplicate(int index)
{
	Bcells[index].cells += 1;
	cells++;
}

//B-cell death
void GCO::Die(int index)
{
	if (Bcells[index].cells > 1)
	{
		Bcells[index].cells -= 1;
		cells--;
	}
}

// B-cell Selection
int GCO::Select()
{
	int r = rand() % cells;
	int temp_cell = 0;
	int i = 0;
	do{
		temp_cell += Bcells[i].cells;
		i++;
	} while (temp_cell < r);
	return --i;
}


// B-cell Mutation
void GCO::Mutate(int index, double(*f)(vector<double>))
{
	//Create new B-cell
	Bcell NewCell;
	int ri1, ri2, ri3;

	do {
		ri1 = Select();
	} while (ri1 == index);
	do
	{
		ri2 = Select();
	} while (ri2 == ri1 || ri2 == index);
	do
	{
		ri3 = Select();
	} while (ri3 == ri2 || ri3 == ri1 || ri3 == index);
	for (int i = 0; i < Problem_size; i++)
	{
		double temp;
		if (((double)rand() / RAND_MAX) < CR)
		{
			temp = Bcells[ri1].Data[i] + F * (Bcells[ri2].Data[i] - Bcells[ri3].Data[i]);
			if (temp > MAX) temp = MAX;
			if (temp < MIN) temp = MIN;
			NewCell.Data.push_back(temp);
		}
		else
		{
			NewCell.Data.push_back(Bcells[index].Data[i]);
		}
	}
	NewCell.Life_signal = 70;
	NewCell.cells = 1;
	//Evaluate Objective function
	double r = (*f)(NewCell.Data);

	//Selection of the mutate Cell
	#ifdef MAXIMIZE
	if (r > Best) //For maximization
	#else
	if (r < Bcells[index].Best_value) //For minimization
	#endif
	{
		cells -= (Bcells[index].cells - 1);
		Bcells[index].Copy(NewCell);
		Bcells[index].Best_value = r;	
		Bcells[index].Life_signal += 5;
		if (Bcells[Best_index].Life_signal > 100) Bcells[Best_index].Life_signal = 100;
	}
	#ifdef MAXIMIZE
		if (r > Best) //For maximization
	#else
		if (r < Best) //For minimization
	#endif
		{
			Best_index = index;
			Best = r;
		}
}
