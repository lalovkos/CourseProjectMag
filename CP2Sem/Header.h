#pragma once
#include<vector>
#include<functional>
#include<fstream>
#include<iostream>
#include<iterator>
#include<stdlib.h>
#include <fcntl.h>   
using namespace std;



//void is_Gauss_Zeidel(vector<vector<double>> &Matrix, vector<double> &F, vector<double> &X, vector<int> index);
class VMFE {
protected:
	virtual void Matrix_filling() = 0;
	virtual void Right_filling() = 0;
	virtual double Right_function(int i) = 0;
	virtual void account_grid() = 0;
	vector<vector<double>> L;
	vector<double> F;
	size_t ktr, kuzlov;
public:
	VMFE(int ktr, int kuzlov) {// выделение памяти в конструкторе
		this->ktr = ktr;
		this->kuzlov = kuzlov;
		F = vector<double>(kuzlov, 0);
		L = vector<vector<double>>(kuzlov);
		for (auto& a : L)
			a = vector<double>(kuzlov, 0);
	}
};

struct rect {
	int left_top;
	int right_top;
	int left_down;
	int right_down;
};

void output(ofstream& out, vector<double> Result, vector<pair<double, double>> GridElem);
void solve(vector<vector<double>>& A, vector<double>& F);
