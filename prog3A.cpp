#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
using namespace std;
//助教您好： 若要執行此程式，請在程式的後面加上 < (inputfile) 謝謝!!!

enum token {NONE, INT_D, FLOAT_D, DOUBLE_D, NAME, OPERATOR};

static char input[1024];
static vector<string> dataa;

void push_identify_token(string id) {
	if ((id[0] >= 'a' && id[0] <= 'z') || (id[0] >= 'A' && id[0] <= 'Z') || id[0] == '$' || id[0] == '_') {
		dataa.push_back(id);
	}
}

void scanner() {
	char a;
	int cur = 0;
	while ((a = (char)cin.get())!=EOF) {
		switch (a) {
		case ' ':
		case '\t':
		case 0:
		case '\n':
		case '\r':
			input[cur] = 0;
			if(cur)
				push_identify_token(input);
			cur = 0;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '=':
		case '(':
		case ')':
		case '{':
		case '}':
		case ';':
		case ':':
			input[cur] = 0;
			if (cur)
				push_identify_token(input);
			cur = 0;
			break;
		default:
			if (a > 128) {
				throw runtime_error("Invaild word contains!");
			}
			input[cur] = a;
			cur++;
		}
	}
	input[cur] = 0;
	if(cur)
		push_identify_token(input);
	return;
}

int main() {
	dataa.resize(1000);
	dataa.resize(0);
	scanner();
	string a;
	for (vector<string>::iterator it = dataa.begin();it != dataa.end();it++) {
		a = *it;
		if (a.find("cpy") != -1) {
			cout << a << endl;
		}
	}
}
