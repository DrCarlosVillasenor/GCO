//-----------------------------------------------------
// Benchmark for Multivariate Continouos Optimization 
//-----------------------------------------------------

//-----------------------------------------------------
//	Define Objective functions
//-----------------------------------------------------

#define Pi 3.14159265359

double Sphere(vector<double> X)
{
	//Limits [-5.12,5.12]
	//Minimun: 0
	//Best: (0,...,0)

	int Problem_size = X.size();
	double result = 0.0;
	for (int i = 0; i < Problem_size; i++)
	{
		result += X[i] * X[i];
	}
	return result;
}

double Rastrigin(vector<double> X)
{
	//Limits in hypercube: [-5.12,5.12]
	//Minimun: 0
	//Best: (0,...,0)

	int Problem_size = X.size();
	double result = 0.0;
	for (int i = 0; i < Problem_size; i++)
	{
		result += X[i] * X[i] - 10 * cos(2 * Pi* X[i]);
	}
	result += 10 * Problem_size;
	return result;
}

double Ackley(vector<double> X)
{
	//Limits in hypercube [-32.768,32.768]
	//Minimun: 0
	//Best: (0,...,0)

	int Problem_size = X.size();
	double a = 20;
	double b = 0.2;
	double c = 2 * Pi;

	double sum1 = 0.0;
	double sum2 = 0.0;
	for (int i = 0; i < Problem_size; i++)
	{
		sum1 += X[i] * X[i];
		sum2 += cos(c*X[i]);
	}
	double term1 = (-a)*exp(-b*sqrt(sum1 / (double)Problem_size));
	double term2 = -exp(sum2 / (double)Problem_size);
	return term1 + term2 + a + exp(1);
}


double Levy(vector<double> X)
{
	//Limits in hypercube [-32.768,32.768]
	//Minimun: 0
	//Best: (1,...,1)

	int Problem_size = X.size();
	vector<double> w;
	double temp_w;
	for (int i = 0; i < Problem_size; i++)
	{
		temp_w = 1 + (X[i] - 1) / (double)4;
		w.push_back(temp_w);
	}
	double term1 = (sin(Pi*w[0]))*(sin(Pi*w[0]));
	double term3 = (w[Problem_size - 1] - 1)*(w[Problem_size - 1] - 1)*(1 + (sin(2 * Pi*w[Problem_size-1]))*(sin(2 * Pi*w[Problem_size - 1])));
	double sum = 0.0;
	for (int i = 0; i < Problem_size-1; i++)
	{
		sum += (w[i] - 1)*(w[i] - 1)*(1 + 10 * (sin(Pi*w[i] + 1))*(sin(Pi*w[i] + 1)));
	}
	return term1 + sum + term3;
}

double Schwefel(vector<double> X)
{
	//Limits in hypercube [-500, 500]
	//Minimun: 0
	//Best: (420.9687,...,420.9687)

	int Problem_size = X.size();
	double sum = 0.0;
	for (int i = 0; i < Problem_size; i++)
	{
		sum += X[i] * sin(sqrt(abs(X[i])));
	}
	return 418.9829*Problem_size - sum;
}

double RHyperEllipsoid(vector<double> X)
{
	//Limits in hypercube [-65.536, 65.536]
	//Minimun: 0
	//Best: (0,...,0)

	int Problem_size = X.size();
	double outer = 0.0;
	double inner;
	for (int i = 0; i < Problem_size; i++)
	{ 
		inner = 0.0;
		for (int k = 0; k < i+1; k++)
		{
			inner += X[k] * X[k];
		}			
		outer += inner;
	}
	return outer;
}

double Rosenbrock(vector<double> X)
{
	//Limits in hypercube  [-2.048, 2.048]
	//Minimun: 0
	//Best: (1,...,1)

	double top = 0.0;
	for (int i = 0; i < (X.size() - 1); i++)
	{
		top = top + 100 * pow(X[i + 1] - X[i]*X[i],(double)2) + pow((X[i] - 1), (double)2);
	}
	return top;
}

double Griewank(vector<double> X)
{
	//Limits in hypercube [-600, 600]
	//Minimun: 0
	//Best: (0,...,0)

	double sum = 0.0;
	double prod = 1.0;
	for (int i = 0; i < X.size(); i++)
	{
		sum  += X[i] * X[i];
		prod *= cos(X[i] / sqrt(i+1));
	}
	return (1 / (double)4000) * sum - prod + 1;
}

double Perm0bd(vector<double> X)
{
	//Limits in hypercube [-d,d]
	//Minimun: 0
	//Best: (1,1/2,...,1/d)
	
	double b = 10;
	double outer_sum = 0.0;
	double inner_sum;
	for (int i = 0; i < X.size(); i++)
	{
		inner_sum = 0.0;
		for (int j = 0; j < X.size(); j++)
		{
			inner_sum += (j + 1 + b)*(pow(X[j],i+1)-(1/pow(j+1,i+1)));
		}
		outer_sum += inner_sum * inner_sum;
	}
	return outer_sum;

}

double SumDiffPow(vector<double> X)
{
	//Limits in hypercube [-1,1]
	//Minimun: 0
	//Best: (0,...,0)
	double sum = 0.0;
	for (int i = 0; i < X.size(); i++)
	{
		sum += pow(abs(X[i]), i + 2);
	}
	return sum;
}

double SumSqrt(vector<double> X)
{
	//Limits in hypercube [-5.12,5.12]
	//Minimun: 0
	//Best: (0,...,0)
	double sum = 0.0;
	for (int i = 0; i < X.size(); i++)
	{
		sum += (i+1) * X[i] * X[i];
	}
	return sum;
}

double Trid(vector<double> X)
{
	//Limits in hypercube [-d^2,d^2]
	//Minimun: -d(d+4)(d-1/6)
	//Best: x_i=i(d+1-i)
	double sum1 = pow(X[0]-1,2.0);
	double sum2 = 0.0;
	for (int i = 1; i < X.size(); i++)
	{
		sum1 += pow(X[i] - 1, 2.0);
		sum2 += X[i] * X[i - 1];
	}
	return sum1 - sum2;
}

double Zakharov(vector<double> X)
{
	//Limits in hypercube [-5,10]
	//Minimun: 0
	//Best: (0,...,0)
	double sum1 = 0.0;
	double sum2 = 0.0;
	for (int i = 0; i < X.size(); i++)
	{
		sum1 += X[i] * X[i];
		sum2 += 0.5 * (i+1) * X[i];
	}
	return sum1 + pow(sum2,2.0) + pow(sum2,4.0);
}

double DixonPrice(vector<double> X)
{
	//Limits in hypercube [-10,10]
	//Minimun: 0
	//Best: x_i = 2^((2^i-2)/2^i)
		
	double term1 = pow(X[0]-1,2.0);
	double sum = 0.0;
	for (int i = 1; i < X.size(); i++)
	{
		sum += (i+1)*pow((2*X[i]*X[i]-X[i-1]),2.0);
	}
	return term1 + sum;
}

double Michalewicz(vector<double> X)
{
	//Limits in hypercube [0,Pi]
	//Minimun: Depende de la dimensión
	double m = 10;
	double sum = 0.0;
	for (int i = 0; i < X.size(); i++)
	{
		sum += sin(X[i]) * pow(sin((i+1)*X[i]*X[i]/Pi),2.0*m);
	}
	return -sum;
}

double Permbd(vector<double> X)
{
	//Limits in hypercube [-d,d]
	//Minimun: 0
	//Best: (1,2,...,d)

	double b = 0.5;
	double outer_sum = 0.0;
	double inner_sum;
	for (int i = 0; i < X.size(); i++)
	{
		inner_sum = 0.0;
		for (int j = 0; j < X.size(); j++)
		{
			inner_sum += (pow(j+1,i+1) + b)*(pow((X[j]/(j+1)),i+1)-1);
		}
		outer_sum += inner_sum * inner_sum;
	}
	return outer_sum;

}

double Styblinski(vector<double> X)
{
	//Limits in hypercube [-5,5]
	//Minimun: -39.16599
	//Best: (-2.903534,...,-2.903534)

	double sum = 0.0;
	for (int i = 0; i < X.size(); i++)
	{
		sum += pow(X[i],4.0)-16*X[i]*X[i]+5*X[i];
	}
	return sum/2;
}

double Bochachevsky(vector<double> X)
{
	//Limits in hypercube [-15,15]
	//Minimun: 0
	//Best: (0,...,0)

	double sum = 0.0;
	for (int i = 0; i < X.size() - 1; i++)
	{
		sum += X[i] * X[i] + 2 * X[i + 1] * X[i + 1] - 0.3*cos(3 * Pi*X[i])-0.4*cos(4*Pi*X[i+1])+ 0.7;
	}
	return sum;
}








