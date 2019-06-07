#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <stdint.h>
using namespace std;

bool parse_s(string &text, int &i, char op) {
	int least, most;
	if (!(text[i] == ' ' || text[i] == '\t') || i == text.length()) {
		return (op == '*' || op == '?') ? true : false;
	}
	i += 1;
	if (op == '?' && (text[i] == ' ' || text[i] == '\t')) {
		return false;
	}
	for (;i < text.length();i++) {
		if (!(text[i] == ' ' || text[i] == '\t')) {
			break;
		}
	}
	return true;
}

string str;
char id;
char id2;
char code;

void match(string& text) {
	// s\s+[a-o|q|r|t-z]\s+\"[a-z|A-Z|0-9]*\"\np\s+[a-o|q|r|t-z]
	int i = 0;
	if (i == text.length() && text[i] != 's') goto fault;
	i += 1;
	if (!parse_s(text, i, '+')) goto fault;
	if (i == text.length()) goto fault;
	if (!(text[i] >= 'a' && text[i] <= 'o' || text[i] == 'q' || text[i] == 'r' ||
		text[i] >= 't' && text[i] <= 'z')) {
		goto fault;
	}
	id = text[i];
	i += 1;
	if (!parse_s(text, i, '+')) goto fault;
	if (i == text.length() || text[i] != '"') goto fault;
	i += 1;
	for (;i < text.length();i++) {
		if (!((text[i] > 96 && text[i] < 'z'+1) || (text[i] > 64 && text[i] <= 'Z') ||
			(text[i] > 47 && text[i] < 58))) {
			break;
		}
		str += text[i];
	}
	if (i == text.length() || text[i] != '"') goto fault;
	i += 1;
	if (i == text.length() || text[i] != '\n') goto fault;
	i += 1;
	if (i == text.length() && text[i] != 'p') goto fault;
	i += 1;
	if (!parse_s(text, i, '+')) goto fault;
	if (i == text.length()) goto fault;
	if (!(text[i] >= 'a' && text[i] <= 'o' || text[i] == 'q' || text[i] == 'r' ||
		text[i] >= 't' && text[i] <= 'z')) {
		goto fault;
	}
	id2 = text[i];
	i += 1;
	if(i != text.length()) goto fault;
	cout << "strdcl s\nid " << id << "\nquote \"\nstring " << str << "\nquote \"" << endl;
	cout << "print p\nid " << id2 << endl;
	return;
fault:
	cout << "valid input" << endl;
}

void print_match() {
}

int main() {
	string a;
	string b;
	bool correct = true;
    getline(cin, a);
    getline(cin, b);
    a = a + "\n" + b;
    match(a);
}
