#include "Header.h"
#include "Edges.h"
#define _CRT_SECURE_NO_WARNINGS
#define PI 3.1415926


vector<int> index;
void input(vector<int>& Materials, vector<pair<double, double>>& Gridelem, vector<rect>& Glob_num, vector<int>& l1) {

	errno_t err = _set_fmode(_O_BINARY);

	int buff;
	ifstream f1("nvkat2d.dat", ios::binary);
	//fopen_s(&f1, "nvkat2d.dat", "br");


	for (int i = 0; i < Materials.size(); i++) {
		f1.read((char*)&Materials[i], sizeof(long));
		//fread(&Materials[i], sizeof(long), 1, f1);
	}

	f1.close();


	ifstream f2("nvtr.dat", ios::binary);
	for (int i = 0; i < Glob_num.size(); i++) {
		f2.read((char*)&Glob_num[i].left_top, sizeof(long));
		f2.read((char*)&Glob_num[i].right_top, sizeof(long));
		f2.read((char*)&Glob_num[i].left_down, sizeof(long));
		f2.read((char*)&Glob_num[i].right_down, sizeof(long));
		f2.read((char*)&buff, sizeof(long));
		f2.read((char*)&buff, sizeof(long));
	}
	f2.close();

	ifstream f3("rz.dat", ios::binary);
	for (int i = 0; i < Gridelem.size(); i++) {
		f3.read((char*)&Gridelem[i].first, sizeof(double));
		f3.read((char*)&Gridelem[i].second, sizeof(double));
	}
	f3.close();

	ifstream f4("l1.dat", ios::binary);

	for (int i = 0; i < l1.size(); i++) {
		f4.read((char*)&l1[i], sizeof(long));
	}
	f4.close();
}
class MFE : VMFE {
protected:
	vector<pair<double, double>> GridElem;
	vector<rect> Glob_num;
	vector<int> Material;
	vector<int> l1;



	//Бесполезный коммент
	double Right_function(int num_elem) {
		if (Material[num_elem] == 1)
			return 0;
		if (Material[num_elem] == 2)
			return 0;
		if (Material[num_elem] == 3)
			return -1e+7;
		if (Material[num_elem] == 4)
			return 1e+7;
		/*return 0;*/
	}

	double is_mu(int num_elem) {
		if (Material[num_elem] == 1)
			return 1000;
		if (Material[num_elem] == 2)
			return 1;
		if (Material[num_elem] == 3)
			return 1;
	}

	void Right_filling() {
		int n = 0;
		double jacobian, distance_x, distance_y;
		rect irect;
		double tok;
		for (size_t i = 0; i < ktr; i++) {
			irect = Glob_num[i];
			distance_x = GridElem[irect.right_down - 1].first - GridElem[irect.left_down - 1].first;
			distance_y = GridElem[irect.right_top - 1].second - GridElem[irect.right_down - 1].second;
			jacobian = distance_x * distance_y;
			tok = Right_function(i);

			F[irect.left_down - 1] += tok * jacobian / 4;
			F[irect.right_down - 1] += tok * jacobian / 4;
			F[irect.left_top - 1] += tok * jacobian / 4;
			F[irect.right_top - 1] += tok * jacobian / 4;
			n++; // выражаем правую часть через матрицу масс
		}
	}

	void Matrix_filling() {
		double distance_x, distance_y, current_mu;
		rect irect;
		for (size_t i = 0; i < ktr; i++) {
			irect = Glob_num[i];
			distance_x = GridElem[irect.right_down - 1].first - GridElem[irect.left_down - 1].first;
			distance_y = GridElem[irect.right_top - 1].second - GridElem[irect.right_down - 1].second;
			current_mu = is_mu(i);
			current_mu = 1. / (current_mu * 4 * PI * 1e-7);

			L[irect.left_down - 1][irect.left_down - 1] += (current_mu / 6) * ((distance_y / distance_x) * 2 + (distance_x / distance_y) * 2);
			L[irect.left_down - 1][irect.right_down - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-2) + (distance_x / distance_y));
			L[irect.left_down - 1][irect.left_top - 1] += (current_mu / 6) * ((distance_y / distance_x) + (distance_x / distance_y) * (-2));
			L[irect.left_down - 1][irect.right_top - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-1) + (distance_x / distance_y) * (-1));

			L[irect.right_down - 1][irect.left_down - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-2) + (distance_x / distance_y));
			L[irect.right_down - 1][irect.right_down - 1] += (current_mu / 6) * ((distance_y / distance_x) * 2 + (distance_x / distance_y) * 2);
			L[irect.right_down - 1][irect.left_top - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-1) + (distance_x / distance_y) * (-1));
			L[irect.right_down - 1][irect.right_top - 1] += (current_mu / 6) * ((distance_y / distance_x) + (distance_x / distance_y) * (-2));

			L[irect.left_top - 1][irect.left_down - 1] += (current_mu / 6) * ((distance_y / distance_x) + (distance_x / distance_y) * (-2));
			L[irect.left_top - 1][irect.right_down - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-1) + (distance_x / distance_y) * (-1));
			L[irect.left_top - 1][irect.left_top - 1] += (current_mu / 6) * ((distance_y / distance_x) * 2 + (distance_x / distance_y) * 2);
			L[irect.left_top - 1][irect.right_top - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-2) + (distance_x / distance_y));

			L[irect.right_top - 1][irect.left_down - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-1) + (distance_x / distance_y) * (-1));
			L[irect.right_top - 1][irect.right_down - 1] += (current_mu / 6) * ((distance_y / distance_x) + (distance_x / distance_y) * (-2));
			L[irect.right_top - 1][irect.left_top - 1] += (current_mu / 6) * ((distance_y / distance_x) * (-2) + (distance_x / distance_y));
			L[irect.right_top - 1][irect.right_top - 1] += (current_mu / 6) * ((distance_y / distance_x) * 2 + (distance_x / distance_y) * 2);
		}
	}

	void symmetrization() {
		for (size_t i = 0; i < l1.size(); i++) {
			for (size_t j = 0; j < kuzlov; j++) {
				F[j] -= L[j][l1[i] - 1] * F[l1[i] - 1];
				L[j][l1[i] - 1] = 0;
			}
			L[l1[i] - 1][l1[i] - 1] = 1;
		}
	}

	void account_grid() {
		for (size_t i = 0; i < l1.size(); i++) {
			for (size_t j = 0; j < kuzlov; j++)
				L[l1[i] - 1][j] = 0;
			L[l1[i] - 1][l1[i] - 1] = 1;
			F[l1[i] - 1] = 0;
		}
	}

public:

	MFE(vector<pair<double, double>> GridElem, vector<rect> Glob_num, vector<int> Material, vector<int>l1) : VMFE(Glob_num.size(), GridElem.size()) {

		this->GridElem = GridElem;
		this->Glob_num = Glob_num;
		this->Material = Material;
		this->l1 = l1;

		Matrix_filling();
		Right_filling();
		account_grid();
		//symmetrization();
	}
	void get_solve(vector<double>& Right, vector<vector<double>>& Matrix) {
		Matrix = L;
		Right = F;
	}
	void account_bord(vector<double>& Right, vector<vector<double>>& Matrix) {
		F = Right;
		account_grid();
		symmetrization();
		Right = F;
		Matrix = L;
	}
};

//pair<double, double> func(double current_mu2) {
//	double current_mu1 = 1;
//	MFE MyMFE(GridElem, current_mu1, current_mu2);
//	MyMFE.get_solve
//	is_Gauss_Zeidel(Matrix, Right, Result, index);
//	return { Result[12 * GridElem[0].size() + 12], Result[16 * GridElem[0].size() + 8] };
//}

int main() {
	int ktr = 946, kuzlov = 1012, kt1 = 90;

	vector<pair<double, double>> Gridelem(kuzlov);
	vector<int> Materials(ktr);
	vector<rect> Glob_num(ktr);
	vector<int> l1(kt1);
	input(Materials, Gridelem, Glob_num, l1);

	vector<double> Right;

	vector<vector<double>> Matrix;
	
	unordered_set <Edge, Edge::EdgesHasher> EdgeSet;
	unordered_set<Edge, Edge::EdgesHasher>::const_iterator got;
	Edge ed1 = Edge(1, 2);			
	EdgeSet.insert(ed1);			  //Добавление
	got = EdgeSet.find(Edge(2, 1));   //Поиск     
	if (got == EdgeSet.end()) {      
		std::cout << "Not found";
	}
	else {
		std::cout << "found";
	}
	std::cout << "sdsd";
	return 0; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Ранний выход!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	MFE MyMFE(Gridelem, Glob_num, Materials, l1);
	MyMFE.get_solve(Right, Matrix);

	solve(Matrix, Right);

	ofstream out("output.txt");
	output(out, Right, Gridelem);
	out.close();

	system("pause");

}


//void init() {
//	double current_mu1 = 1, current_mu2 = 1e+5;
//	ifstream in("input.txt");
//	int amt_vertex_x, amt_vertex_y, amt_step;
//	double x_begin, x_end, y_begin, y_end;
//	in >> x_begin >> x_end >> amt_vertex_x;
//	in >> y_begin >> y_end >> amt_vertex_y;
//	amt_vertex_x++;
//	amt_vertex_y++;
//	GridElem = vector<vector<pair<double, double>>>(amt_vertex_y);
//	for (auto &elem : GridElem)
//		elem = vector<pair<double, double>>(amt_vertex_x);
//	in.close(); // считывание данных и выделение памяти
//
//	double step_x, step_y;
//	step_x = (x_end - x_begin) / (amt_vertex_x - 1);
//	step_y = (y_end - y_begin) / (amt_vertex_y - 1);
//	for (int i = 0; i < GridElem.size(); i++)
//		for (int j = 0; j < GridElem[i].size(); j++)
//			GridElem[i][j] = { x_begin + step_x * j, y_begin + step_y * i };
//
//	Result = vector<double>(amt_vertex_x * amt_vertex_y, 0);
//	index = { -amt_vertex_x - 1, -amt_vertex_x, -amt_vertex_x + 1, -1, 0, 1, amt_vertex_x - 1, amt_vertex_x, amt_vertex_x + 1 };
//
//}
