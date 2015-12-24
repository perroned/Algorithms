#define USE_REGEX true
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#if USE_REGEX == true
#include <regex>
#include <utility> // for pairing regex search with action
using std::regex;
#endif // USE_REGEX
using std::string;
using std::vector;
using std::cout;
using std::endl;

void formatOutsideQuotes(string& s) {
#if USE_REGEX == true
	string outsideQuotes{ "(?=([^\"]*\"[^\"]*\")*[^\"]*$)" }; // matches outside of quotes
	vector<std::pair <regex, string>> rules{
		{ regex{ "^[[:space:]]*" }, "" }, // left trimming
		{ regex{ "[[:space:]]+" + outsideQuotes }, " " }, // trimming outside of quotes
		{ regex{ "[[:space:]]*([=\\-/\\+\\*])[[:space:]]*" + outsideQuotes }, " $1 " }, // trimming for math symbols
		{ regex{ ",[[:space:]]*" + outsideQuotes }, "$& " } // trimming for comma
	};

	for (auto& rule : rules) { // execute every syntax rule
		s = std::regex_replace(s, rule.first, rule.second);
	}
#else
	auto isSymbol = [](char symbol) -> auto { return strchr("=-+*/", symbol); }; // symbol comparison

	vector<char> characters(s.begin(), s.end()), modified;
	bool inQuote = false; // whether the current character is between quotes

	for (auto c : characters) {
		if (c == '\"') { // found opening or closing quote
			modified.push_back(c);
			inQuote = !inQuote; // toggle quote state
		} else {
			if (inQuote || (c == ' ' && modified.size() > 0 && modified.back() != ' ')) {
				modified.push_back(c); // keep character if in quotes, or it is a space preceeded by non whitespace
				continue;
			}
			// preceed symbols with space
			if (isSymbol(c) && modified.size() > 0 && modified.back() != ' ') { modified.push_back(' '); }
			if (c != ' ') { modified.push_back(c); } // keep every non whitspace character
			if (isSymbol(c) || c == ',') { modified.push_back(' '); } // add succeeding space
		}
	}
	s = { modified.begin(), modified.end() }; // replace original reference string with modified line
#endif // USE_REGEX
}

void checkIndent(vector<string>& lines, unsigned int ind, unsigned int& level) {
	if (ind == 0) { cout << ""; return; } // no indentation
	string prev{ lines[ind - 1] }; // line before current

	// receives a line, and list of terms, returns whether the line begins with any term
	auto startsWith = [&](const string& line, vector<string> searches) -> bool {
		for (auto& s : searches) { if (line.find(s) == 0) { return true; } }
		return false;
	};
	if (startsWith(lines[ind], { "ELSE", "ELSEIF", "ENDIF" })) { level--; } // keyword is unindented
	else {
		if (startsWith(prev, { "LOOP", "IF", "ELSEIF", "ELSE", "FOR", "PROC", "OPEN" })) { level++; }
		else if (startsWith(prev, { "ENDLOOP", "ENDIF", "ELSEIF", "NEXT", "ENDPROC", "CLOSE" })) { level--; }
	}
	for (unsigned int i = 0; i < level; ++i) { cout << "  "; }
}

int main(int argc, char *argv[]) {
	if (argc == 2) { // should only receive 1 user specified arg, file with full absolute path
		vector<string> input;
		std::ifstream file(argv[1]);

		if (!file) { return -1; }
		string line;
		while (std::getline(file, line)) { // read input line by line
			input.push_back(line);
		}

		for (unsigned int ind = 0, level = 0; ind < input.size(); ind++) { // process each line
			formatOutsideQuotes(input[ind]); // format the line with syntax rules
			checkIndent(input, ind, level); // evaluate indentation level
			cout << input[ind] << endl;
		}
		std::getchar();
	}
	return 0;
}
