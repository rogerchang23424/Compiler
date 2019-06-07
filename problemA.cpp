#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
using namespace std;

void match(string& text) {
	// [a-z]\s*=\s*[0-9]+
	char id;
	char assign = '=';
	string inum;

	uint32_t i = 0;
	if (i == text.length()) goto fault;
	if (text[i] < 'a' || text[i] > 'z')
		goto fault;
	id = text[i];
	i += 1;
	for (i;i < text.length();i++) {
		if (!(text[i] == ' ' || text[i] == '\t'))
			break;
	}
	if (i == text.length()) goto fault;
	if (text[i] != '=')
		goto fault;
	i += 1;
	for (i;i < text.length();i++) {
		if (!(text[i] == ' ' || text[i] == '\t'))
			break;
	}
	for (i;i < text.length();i+=1) {
		if (text[i] < '0' || text[i] > '9')
			goto fault;
		inum += text[i];
	}
	cout << "id " << id << "\nassign " << assign << "\ninum " << inum << endl;
	return;
fault:
	cout << "valid input" << endl;
}

int main() {
	string a;
	getline(cin, a);
	match(a);
}
