#include"Header.h"
void output(ofstream& out, vector<double> Result, vector<pair<double, double>> GridElem) {
	vector<double> ModB(Result.size());
	double dx, dy;
	int string = 44;
	for (int i = 0; i < Result.size() - string; i++) {
		dx = (Result[i + 1] - Result[i]) / (GridElem[i + 1].first - GridElem[i].first);
		dy = (Result[i + string] - Result[i]) / (GridElem[i + string].second - GridElem[i].second);
		ModB[i] = dx * dx + dy * dy;
	}
	for (int i = 0; i < Result.size(); i++) {
		out << GridElem[i].first << ' ' << GridElem[i].second << ' ' << scientific << Result[i] << ' ' << ModB[i] << endl;
	}
}

void solve(vector<vector<double>>& A, vector<double>& F) {
	/*for (int i = 0; i < N; i++)
	{
	for (int j = 0; j < N; j++)
	{
	cout << left << setw(5) << A[i][j] << ' ';
	}
	cout << setw(5) << '|' << F[i] << endl << endl << endl;
	}
	cout << endl;*/

	//unsigned short k = 0; 
	//for (auto i : F) 
	// cout <<setprecision(3) <</*scientific <<*/setw(9) <<i <<(!(++k%Nx) ? "\n\n\n" : " "); 
	/*for (int i = OX.size() - 1; i >= 0; i--)
	{
	for (int j = 0; j < OY.size(); j++)
	cout << left << setw(15) << setprecision(15) << (double)func_u(OX[i], OY[j]);
	cout << endl << endl << endl;
	}*/

	double tmp;
	int N = F.size();
	for (int i = 0; i < N; i++) {
		tmp = A[i][i];
		for (int j = i; j < N; j++)
			A[i][j] /= tmp;
		F[i] /= tmp;
		for (int j = i + 1; j < N; j++) {
			tmp = A[j][i];
			for (int k = i; k < N; k++)
				A[j][k] -= tmp * A[i][k];
			F[j] -= tmp * F[i];
		}
		for (int j = i - 1; j >= 0; j--) {
			tmp = A[j][i];
			for (int k = i; k < N; k++)
				A[j][k] -= tmp * A[i][k];
			F[j] -= tmp * F[i];
		}
	}

	/*for (auto i : A) {
	for (auto j : i)
	cout <<j <<' ';
	cout <<endl;
	}*/

}
