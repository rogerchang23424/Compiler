#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
using namespace std;

enum mytype{ INT, OP };

bool isint(string text) {
	if (text.length() == 0) return false;
	if (!(((text[0] == '+' || text[0] == '-') && text.length() >= 2) || isdigit(text[0]))) { return false; };
	//if (!isdigit(text[0])) return false;
	for (int i = 1;i < text.length();i++)
		if (!isdigit(text[i]))
			return false;
	return true;
}


bool isoperator(char sig) {
	return sig == '+' || sig == '-' || sig == '*' || sig == '/';
}

bool is_space(char sig) {
	return sig == ' ' || sig == '\t' || sig == '\r';
}

bool is_newline(char sig) {
	return sig == '\n';
}

bool isoperator(string text) {
	return text == "+" || text == "-" || text == "*" || text == "/";
}

int read_value(string &res) {
	//[+-]?[0-9]+
	string tmp = "";
	int a = cin.peek();
	bool has_digit = false;
	char t;
	t = (char)a;
	if (t == '+' || t == '-') {
		tmp += (char)cin.get();
		a = cin.peek();
		t = (char)a;
	}
	while (1) {
		if (t >= '0' && t <= '9') {
			has_digit = true;
			tmp += (char)cin.get();
		}
		else {
			break;
		}
		a = cin.peek();
		t = (char)a;
	}
	if (!has_digit && (tmp == "+" || tmp == "-")) {
		res = tmp;
		return false;
	}
	if (isoperator(t) || is_space(t) || is_newline(t) || a == -1) {;
		res = tmp;
		return has_digit;
	}
	else {
		while (1) {
			tmp += (char)cin.get();
			a = cin.peek();
			t = (char)a;
			if (is_space(t) || is_newline(t) || a == -1) {
				break;
			}
			
		}
		res = tmp;
		return false;
	}
		
}

int read_formula(vector<string>&token_list) {
	string temp;
	int ret;
	int ch;
	while (1) {
		temp = "";
		ret = read_value(temp);
		if (isint(temp)) {
			token_list.push_back(temp);
			continue;
		}
		else if (isoperator(temp)) {
			token_list.push_back(temp);
			continue;
		}
		else if (!ret && temp != "") {
			goto fault;
		}
		ch = cin.peek();
		if (is_newline((char)ch) || ch == -1) {
			break;
		}
		if (is_space((char)ch)) {
			cin.get();
			continue;
		}
		if (isoperator((char)ch)) {
			temp += (char)cin.get();
			token_list.push_back(temp);
		}
	}
	return 0;
fault:
	cout << "Error: Unknown token " << temp << endl;
	while (1) {
		ch = cin.peek();
		if (is_newline((char)ch) || ch == -1) {
			break;
		}
		cin.get();
	}
	return 1;
}

int calc(int a, int b, char op, int& error) {
	switch (op) {
	case '+':
		return b + a;
	case '-':
		return b - a;
	case '*':
		return b * a;
	case '/':
		if (a == 0) {
			if(!error)
				error = 2;
			return 0;
		}
		return b / a;
	}
}

int exp(vector<string>& item, int &error, int& order) {
	int v = 0;
	int a, b;
	order++;
	if (order >= item.size()) { error = 1; return 0; }
	if (isoperator(item[order])) {
		v=  calc(exp(item, error, order), exp(item, error, order), item[order][0], error);
		if (error) {
			return 0;
		}
		return v;
	}
	if (isint(item[order])) return atoi(item[order].c_str());
		
}

int topexp(vector<string>& item, int &error, int& order) {
	return exp(item, error, order);
}

int topexps(vector<string>& item, int &error, int& order) {
	return topexp(item, error, order);
}

int proc(vector<string>& item, int &error, int& order) {
	return topexps(item, error, order);
}

int mygetline(istream& is, string& a) {
	a = "";
	int ab;
	while (1) {
		ab = is.get();
		if (ab == EOF || ab == '\n') break;
		a += ab;
	}
	return ab;
}

int main() {
	cout << "Welcome use our calculator!" << endl;
	string s;
	istringstream is;
	string e;
	vector<string> token_list;
	int error;
	int result;
	int order = -1;
	int newline;
	while (1) {
		cout << "> ";

		error = read_formula(token_list);

		if (!error) {
			//cerr << "Valid:" << s << endl;
			result = proc(token_list, error, order);
			if (order != token_list.size() - 1) { 
				if(error == 0)error = 1;
				if (token_list.size() == 0)
					error = 3;
			}
			if (error) {
				switch (error) {
				case 1:
					cout << "Error: Illegal formula!" << endl;
					break;
				case 2:
					cout << "Error: Divide by ZERO!" << endl;
				}
			}
			else {
				cout << result << endl;
			}
		}
		error = 0;
		token_list.resize(0);
		order = -1;
		newline = cin.get();
		if (newline == -1) break;
	}
	cout << "ByeBye~" << endl;
}
