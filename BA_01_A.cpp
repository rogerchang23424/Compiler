#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std;

enum token {ID, STRLIT, LBR, RBR, DOT, SEMICOLON};

struct mydata {
	string content;
	token type;
};

static char input[1024];
static vector<mydata> dataa;
void print_dataa();

void scanner() {
	char a;
	int cur = 0;
	string temp;
	mydata tempd;
	int inbr = 0;
	int inid = 0;
	int instr = 0;
	while ((a = (char)cin.get())!=EOF) {
		if (isspace(a)) continue;
		if (isalpha(a) || a == '_') {
			temp += a;
			while ((a = (char)cin.get()) != EOF && (isalpha(a) || isdigit(a) || a == '_'))
				temp += a;
			tempd.content = temp;
			tempd.type = ID;
			dataa.push_back(tempd);
			inid = 1;
			temp = "";
			goto deal_operator;
		}
		if (a == '"') {
			temp += a;
			while ((a = (char)cin.get()) != EOF && a != '"')
				temp += a;
			if (a != '"') goto invalid_input;
			temp += a;
			tempd.content = temp;
			tempd.type = STRLIT;
			dataa.push_back(tempd);
			instr = 1;
			temp = "";
			continue;
		}
	deal_operator:
		if (a == '.') {
			tempd.content = a;
			tempd.type = DOT;
			dataa.push_back(tempd);
			continue;
		}
		if (a == '(') {
			tempd.content = a;
			tempd.type = LBR;
			dataa.push_back(tempd);
			inbr++;
			continue;
		}
		if (a == ')') {
			tempd.content = a;
			tempd.type = RBR;
			dataa.push_back(tempd);
			inbr--;
			continue;
		}
	semicolon:
		if (a == ';') {
			if (inbr) goto invalid_input;
			tempd.content = a;
			tempd.type = SEMICOLON;
			dataa.push_back(tempd);
		}
		else {
			if (inid || instr) goto invalid_input;
		}
		inid = instr = 0;
	}
	print_dataa();
	return;
invalid_input:
	cout << "invalid input" << endl;
}

void print_dataa() {
	for (int i = 0;i < dataa.size();i++) {
		switch (dataa[i].type) {
		case ID:
			cout << "ID ";
			break;
		case STRLIT:
			cout << "STRLIT ";
			break;
		case LBR:
			cout << "LBR ";
			break;
		case RBR:
			cout << "RBR ";
			break;
		case DOT:
			cout << "DOT ";
			break;
		case SEMICOLON:
			cout << "SEMICOLON ";
			break;
		}
		cout << dataa[i].content << endl;
	}
}

int main() {
	dataa.resize(1000);
	dataa.resize(0);
	scanner();
}
