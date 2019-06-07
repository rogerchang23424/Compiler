#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std;

class Table {
public:
	Table(istream &in) {
		string cname;
		//first line
		column_name.resize(10);
		column_name.resize(0);
		getline(in, temp);
		is.str(temp);
		while (is >> cname) {
			column_name.push_back(cname);
		}
		is.clear();
		get_favorite_loc();
		if (floc == -1)
			cerr << "Warning: No Favorite column" << endl;

		while (1) {
			getline(in, temp);
			if (!in)
				break;
			is.str(temp);
			temp_data.resize(0);
			while (is >> cname) {
				temp_data.push_back(cname);
			}
			database.push_back(temp_data);
			is.clear();
		}
	}
	~Table() {
	}
	void out(ostream &out) {
		if (floc != -1) {
			for (vector<vector<string> >::iterator it = database.begin(); it != database.end(); it++) {
				if ((*it)[floc] == "noodles") {
					for (int i = 0;i < (*it).size() - 1;i++)
						out << (*it)[i] << "\t";
					out << (*it)[(*it).size() - 1] << endl;
				}
			}
		}
	}
protected:
	vector<string> column_name;
	vector< vector<string> > database;
	vector<string> temp_data;
	istringstream is;
	string temp;
	int floc;
	void get_favorite_loc() {
		for (int i = 0;i < column_name.size();i++) {
			if (column_name[i] == "Favorite") {
				floc = i;
				return;
			}
		}
		floc = -1;
	}
};


int main() {
	Table b(cin);
	b.out(cout);
}
