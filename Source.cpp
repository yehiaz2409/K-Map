/*Yehia Elkasas, 900202395*/
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
int min_terms[8], x;
struct cell {
	int state,num_of_ones, minterm_num;
	string binary_val;
	bool took_in_step_one = false;
};
struct group {
	int index;
	vector<cell> minterms;
};
struct group_step2 {
	int index;
	vector<vector<cell>> matched_minterms;
	vector<string> bin_val;
	vector<bool> took_in_step_two = {0};
};
void process_expression();
void k_map_function();
bool pairs_match(const cell& x, const cell& y);
bool pairs_match_string(const string& x, const string& y);
string replace_variable(cell x, cell y);
string replace_variable_string(string x, string y);
string create_letter_imlpcant(string x);
bool has_minterm(string binary, int minterm);
void two_variable_function();
cell Kmap[2][4];
void k_map_function() {
	cout << "Enter the number of minterms(0-8): "; cin >> x;
	while (x < 0 || x > 8) {
		cout << "Invalid...try again: ";
		cin >> x;
	}
	for (int i = 0; i < x; i++) {
		int num;
		cout << "Enter a minterm: ";
		cin >> num;
		while (num < 0 || num > 7) {
			cout << "Invalid minterm...Enter again: "; cin >> num;
		}
		min_terms[i] = num;
	}
	Kmap[0][0].binary_val = "000"; Kmap[0][0].minterm_num = 0; Kmap[0][0].num_of_ones = 0;
	Kmap[1][0].binary_val = "001"; Kmap[1][0].minterm_num = 1; Kmap[1][0].num_of_ones = 1;
	Kmap[0][1].binary_val = "010"; Kmap[0][1].minterm_num = 2; Kmap[0][1].num_of_ones = 1;
	Kmap[1][1].binary_val = "011"; Kmap[1][1].minterm_num = 3; Kmap[1][1].num_of_ones = 2;
	Kmap[0][2].binary_val = "110"; Kmap[0][2].minterm_num = 6; Kmap[0][2].num_of_ones = 2;
	Kmap[1][2].binary_val = "111"; Kmap[1][2].minterm_num = 7; Kmap[1][2].num_of_ones = 3;
	Kmap[0][3].binary_val = "100"; Kmap[0][3].minterm_num = 4; Kmap[0][3].num_of_ones = 1;
	Kmap[1][3].binary_val = "101"; Kmap[1][3].minterm_num = 5; Kmap[1][3].num_of_ones = 2;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			Kmap[i][j].state = 0;
		}
	}
	for (int k = 0; k < x; k++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				if (Kmap[i][j].minterm_num == min_terms[k]) {
					Kmap[i][j].state = 1;
				}
			}
		}
	}
	cout << "K-map =\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			cout << Kmap[i][j].state << "\t";
		}
		cout << "\n";
	}
}
void process_expression() {
	group G0;
	G0.index = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (Kmap[i][j].num_of_ones == 0 && Kmap[i][j].state == 1) {
				G0.minterms.push_back(Kmap[i][j]);
				//cout << Kmap[i][j].binary_val << " ";
			}
		}

	}
	//cout << "\n";
	group G1;
	G1.index = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (Kmap[i][j].num_of_ones == 1 && Kmap[i][j].state == 1) {
				G1.minterms.push_back(Kmap[i][j]);
				//cout << Kmap[i][j].binary_val << " ";
			}
		}
	}
	//cout << "\n";
	group G2;
	G2.index = 2;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (Kmap[i][j].num_of_ones == 2 && Kmap[i][j].state == 1) {
				G2.minterms.push_back(Kmap[i][j]);
				//cout << Kmap[i][j].binary_val << " ";
			}
		}
	}
	//cout << "\n";
	group G3;
	G3.index = 3;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (Kmap[i][j].num_of_ones == 3 && Kmap[i][j].state == 1) {
				G3.minterms.push_back(Kmap[i][j]);
				//cout << Kmap[i][j].binary_val << " ";
			}
		}
	}
	//cout << "\n";
	group_step2 G00;
	G00.index = 0;
	G00.took_in_step_two.resize(8);
	int size0 = G0.minterms.size();
	int size1 = G1.minterms.size();
	for (int i = 0; i < size0; i++) {
		for (int j = 0; j < size1; j++) {
			if (pairs_match(G0.minterms[i], G1.minterms[j])) {
				vector<cell> v;
				v.push_back(G0.minterms[i]);
				//cout << G0.minterms[i].binary_val << " ";
				v.push_back(G1.minterms[j]);
				//cout << G1.minterms[j].binary_val << " ";
				G00.matched_minterms.push_back(v);
				G00.bin_val.push_back(replace_variable(G0.minterms[i], G1.minterms[j]));
				//cout << " " << replace_variable(G0.minterms[i], G1.minterms[j]) << " ";
				G0.minterms[i].took_in_step_one = true;
				G1.minterms[j].took_in_step_one = true;
			}
		}
	}
	//cout << "\n";
	group_step2 G11;
	G11.index = 1;
	G11.took_in_step_two.resize(8);
	int size2 = G2.minterms.size();
	for (int i = 0; i < size1; i++) {
		for (int j = 0; j < size2; j++) {
			if (pairs_match(G1.minterms[i], G2.minterms[j])) {
				vector<cell> v1;
				v1.push_back(G1.minterms[i]);
				//cout << G1.minterms[i].binary_val << " ";
				v1.push_back(G2.minterms[j]);
				//cout << G2.minterms[j].binary_val << " ";
				G11.matched_minterms.push_back(v1);
				G11.bin_val.push_back(replace_variable(G1.minterms[i], G2.minterms[j]));
				//cout << " " << replace_variable(G1.minterms[i], G2.minterms[j]) << " ";
				G1.minterms[i].took_in_step_one = true;
				G2.minterms[j].took_in_step_one = true;
			}
		}
	}
	//cout << "\n";
	group_step2 G22;
	G22.index = 2;
	G22.took_in_step_two.resize(8);
	int size3 = G3.minterms.size();
	for (int i = 0; i < size2; i++) {
		for (int j = 0; j < size3; j++) {
			if (pairs_match(G2.minterms[i], G3.minterms[j])) {
				vector<cell> v2;
				v2.push_back(G2.minterms[i]);
				//cout << G2.minterms[i].binary_val << " ";
				v2.push_back(G3.minterms[j]);
				//cout << G3.minterms[i].binary_val << " ";
				G22.matched_minterms.push_back(v2);
				G22.bin_val.push_back(replace_variable(G2.minterms[i], G3.minterms[j]));
				//cout << " " << replace_variable(G2.minterms[i], G3.minterms[j]) << " ";
				G2.minterms[i].took_in_step_one = true;
				G3.minterms[j].took_in_step_one = true;
			}
		}
	}
	//cout << "\n";
	vector<string> untaken_minterms;
	for (auto x : G0.minterms) {
		if (x.took_in_step_one == false) {
			untaken_minterms.push_back(x.binary_val);
		}
	}
	for (auto x : G1.minterms) {
		if (x.took_in_step_one == false) {
			untaken_minterms.push_back(x.binary_val);
		}
	}
	for (auto x : G2.minterms) {
		if (x.took_in_step_one == false) {
			untaken_minterms.push_back(x.binary_val);
		}
	}
	for (auto x : G3.minterms) {
		if (x.took_in_step_one == false) {
			untaken_minterms.push_back(x.binary_val);
		}
	}
	group_step2 F0;
	F0.index = 0;
	int size00 = G00.bin_val.size();
	int size11 = G11.bin_val.size();
	for (int i = 0; i < size00; i++) {
		for (int j = 0; j < size11; j++) {
			if (pairs_match_string(G00.bin_val[i], G11.bin_val[j])) {
				vector<cell> v;
				for (auto x : G00.matched_minterms[i]) {
					v.push_back(x);
				}
				for (auto y : G11.matched_minterms[j]) {
					v.push_back(y);
				}
				F0.matched_minterms.push_back(v);
				F0.bin_val.push_back(replace_variable_string(G00.bin_val[i], G11.bin_val[j]));
				//G00.took_in_step_two.resize(G00.bin_val.size());
				//G11.took_in_step_two.resize(G11.bin_val.size());
				//cout << replace_variable_string(G00.bin_val[i], G11.bin_val[j]) << " ";
				G00.took_in_step_two[i] = true;
				G11.took_in_step_two[j] = true;
			}
		}
	}
	//cout << "\n";
	group_step2 F1;
	F1.index = 1;
	int size22 = G22.bin_val.size();
	for (int i = 0; i < size11; i++) {
		for (int j = 0; j < size22; j++) {
			if (pairs_match_string(G11.bin_val[i], G22.bin_val[j])) {
				vector<cell> v;
				for (auto x : G11.matched_minterms[i]) {
					v.push_back(x);
				}
				for (auto y : G22.matched_minterms[j]) {
					v.push_back(y);
				}
				F1.matched_minterms.push_back(v);
				F1.bin_val.push_back(replace_variable_string(G11.bin_val[i], G22.bin_val[j]));
				//G11.took_in_step_two.resize(G11.bin_val.size());
				//G22.took_in_step_two.resize(G22.bin_val.size());
				//cout << replace_variable_string(G11.bin_val[i], G22.bin_val[j]) << " ";
				G11.took_in_step_two[i] = true;
				G22.took_in_step_two[j] = true;
			}
		}
	}
	//cout << "\n";
	int count = 0;
	for (auto x : G00.took_in_step_two) {
		if (count < G00.bin_val.size()) {
			//cout << "first: " << G00.bin_val[count] << "\n";
			if (!x && G00.bin_val.size() > 0) {
				//cout << "second: " << G00.bin_val[count] << "\n";
				untaken_minterms.push_back(G00.bin_val[count]);
			}
		}
		count++;
	}
	//cout << "\n";
	count = 0;
	for (auto x : G11.took_in_step_two) {
		if (count < G11.bin_val.size()) {
			//cout << "first: " << G11.bin_val[count] << "\n";
			if (!x && G11.bin_val.size() > 0) {
				//cout << "second: " << G11.bin_val[count] << "\n";
				untaken_minterms.push_back(G11.bin_val[count]);
			}
		}
		count++;
	}
	//cout << "\n";
	count = 0;
	for (auto x : G22.took_in_step_two) {
		if (count < G22.bin_val.size()) {
			//cout << "first: " << G22.bin_val[count] << "\n";
			if (!x && G22.bin_val.size() > 0) {
				//cout << "second: " << G22.bin_val[count] << "\n";
				//cout << "\n" << G22.bin_val[count] << "\n";
				untaken_minterms.push_back(G22.bin_val[count]);
			}
		}
		//count++;
	}
	//cout << "\n";
	if (F0.bin_val.size() > 0) {
		untaken_minterms.push_back(F0.bin_val[0]);
	}
	if (F1.bin_val.size() > 0) {
		untaken_minterms.push_back(F1.bin_val[0]);
	}
	unordered_map<string, string> binary_to_letter;
	for (auto x : untaken_minterms) {
		binary_to_letter[x] = create_letter_imlpcant(x);
		//cout << x << " => " << create_letter_imlpcant(x) << "\n";
	}
	unordered_map<string, string> letter_to_binary;
	for (auto x : untaken_minterms) {
		letter_to_binary[binary_to_letter[x]] = x;
	}
	//cout << "\n";
	unordered_map<int, string> final_table;
	for (auto x : untaken_minterms) {
		//cout << "Untaken: " << x << " ";
		for (int i = 0; i < 8; i++) {
			if (has_minterm(x, min_terms[i])) {
				final_table[min_terms[i]] = binary_to_letter[x];
				//cout << min_terms[i] << " => " << binary_to_letter[x] << "\n";
			}
		}
	}
	unordered_map<int, bool> revise_map;
	for (int i = 0; i < 8; i++) {
		if (final_table.count(min_terms[i]) == 1) {
			revise_map[min_terms[i]] = true;
		}
		else revise_map[min_terms[i]] = false;
	}
	//cout << "\n";
	vector<string> essential_prime;
	for (int i = 0; i < 8; i++) {
		//cout << final_table[min_terms[i]] << " ";
		if (revise_map[min_terms[i]] == true) {
			essential_prime.push_back(final_table[min_terms[i]]);
		}
	}
	for (auto& i : essential_prime) {
		for (int j = 0; j < 8; j++) {
			if (letter_to_binary.find(i) != letter_to_binary.end()) {
				string temp = letter_to_binary[i];
				if (revise_map[min_terms[j]] == false && !has_minterm(temp, min_terms[j])) {
					essential_prime.push_back(final_table[min_terms[j]]);
				}
			}
		}
	}
	set<string> letters;
	for (auto& x : essential_prime) {
		letters.insert(x);
	}
	cout << "F = [";
	for (auto& x : letters) {
		cout << x << " + ";
	}
	cout << "\b\b]\n";
}
bool has_minterm(string binary, int minterm) {
	string w = "";
	string x = "";
	string y = "";
	string z = "";
	//cout << binary << "\n";
	for (int i = 0; i < binary.size(); i++) {
		if (binary[i] == '_') {
			w += '0';
			z += '1';
			if (i % 2 == 0) {
				x += '0';
				y += '1';
			}
			else {
				x += '1';
				y += '0';
			}
		}
		else {
			w += binary[i];
			x += binary[i];
			y += binary[i];
			z += binary[i];
		}
	}
	//cout << x << "   " << y << "   " << w << "   " << z << "\n";
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if ((Kmap[i][j].binary_val == x && Kmap[i][j].minterm_num == minterm) || (Kmap[i][j].binary_val == y && Kmap[i][j].minterm_num == minterm) || (Kmap[i][j].binary_val == w && Kmap[i][j].minterm_num == minterm) || (Kmap[i][j].binary_val == z && Kmap[i][j].minterm_num == minterm)) {
				//cout << "\n" << Kmap[i][j].binary_val << "\n";
				return true;
			}
		}
	}
	return false;
}

string create_letter_imlpcant(string bin) {
	string result = "";
		for (int i = 0; i < 3; i++) {
			if (bin[i] != '_') {
				if (i == 0 && bin[i] == '1') {
					result += 'A';
				}
				if (i == 0 && bin[i] == '0') {
					result += "A`";
				}
				if (i == 1 && bin[i] == '1') {
					result += 'B';
				}
				if (i == 1 && bin[i] == '0') {
					result += "B`";
				}
				if (i == 2 && bin[i] == '1') {
					result += 'C';
				}
				if (i == 2 && bin[i] == '0') {
					result += "C`";
				}
			}
		}
	return result;
}

bool pairs_match(const cell& x, const cell& y) {
	int diff = 0;
	for (int i = 0; i < 3; i++) {
		if (x.binary_val[i] != y.binary_val[i]) diff++;
	}
	if (diff > 1) return false; else return true;
}
bool pairs_match_string(const string& x, const string& y) {
	int diff = 0;
	for (int i = 0; i < 3; i++) {
		if (x[i] != y[i]) diff++;
	}
	if (diff > 1) return false; else return true;
}

string replace_variable(cell x, cell y) {
	string result = "";
	for (int i = 0; i < 3; i++) {
		if (x.binary_val[i] != y.binary_val[i]) {
			result += '_';
		}
		else result += x.binary_val[i];
	}
	return result;
}
string replace_variable_string(string x, string y) {
	string result = "";
	for (int i = 0; i < 3; i++) {
		if (x[i] != y[i]) {
			result += '_';
		}
		else result += x[i];
	}
	return result;
}
void two_variable_function() {
	cout << "Enter the number of minterms you would like to enter(0-4): ";
	int num; cin >> num;
	while (num < 0 || num > 4) {
		cout << "Invalid....try again: ";
		cin >> num;
	}
	if (num == 0) {
		cout << "K-map:\n";
		cout << "0\t0\n0\t0\n";
		cout << "F = 0";
	}
	else {
		if (num == 4) {
			cout << "K-map:\n";
			cout << "1\t1\n1\t1\n";
			cout << "F = 1";
		}
		else {
			if (num == 1) {
				cout << "Enter the minterm: ";
				int min; cin >> min;
				while (min < 0 || min > 3) {
					cout << "Invalid...try again: ";
					cin >> min;
				}
				if (min == 0) {
					cout << "K-map:\n";
					cout << "1\t0\n0\t0\n";
					cout << "F = `A`B";
				}
				if (min == 1) {
					cout << "K-map:\n";
					cout << "0\t0\n1\t0\n";
					cout << "F = `AB";
				}
				if (min == 2) {
					cout << "K-map:\n";
					cout << "0\t1\n0\t0\n";
					cout << "F = A`B";
				}
				if (min == 3) {
					cout << "K-map:\n";
					cout << "0\t0\n0\t1\n";
					cout << "F = AB";
				}
			}
			else {
				if (num == 2) {

					cout << "Enter the minterms: ";
					int mins[2];
					for (int i = 0; i < 2; i++) {
						cin >> mins[i];
						while (mins[i] < 0 || mins[i] > 3) {
							cout << "Invalid...try again: ";
							cin >> mins[i];
						}
					}
					if (mins[0] == 0 && mins[1] == 1) {
						cout << "K-map:\n";
						cout << "1\t0\n1\t0\n";
						cout << "F = `A";
					}
					if (mins[0] == 0 && mins[1] == 2) {
						cout << "K-map:\n";
						cout << "1\t1\n0\t0\n";
						cout << "F = `B";
					}
					if (mins[0] == 0 && mins[1] == 3) {
						cout << "K-map:\n";
						cout << "1\t0\n0\t1\n";
						cout << "F = `A`B + AB";
					}
					if (mins[0] == 1 && mins[1] == 2) {
						cout << "K-map:\n";
						cout << "0\t1\n1\t0\n";
						cout << "F = `AB + A`B";
					}
					if (mins[0] == 1 && mins[1] == 3) {
						cout << "K-map:\n";
						cout << "0\t1\n0\t1\n";
						cout << "F = B";
					}
					if (mins[0] == 2 && mins[1] == 3) {
						cout << "K-map:\n";
						cout << "0\t0\n1\t1\n";
						cout << "F = `A";
					}
				}
				else {
					if (num == 3) {
						cout << "Enter the minterms: ";
						int mins[3];
						for (int i = 0; i < 3; i++) {
							cin >> mins[i];
							while (mins[i] < 0 || mins[i] > 3) {
								cout << "Invalid...try again: ";
								cin >> mins[i];
							}
						}
						if (mins[0] == 0 && mins[1] == 1 && mins[2] == 2) {
							cout << "K-map:\n";
							cout << "1\t1\n1\t0\n";
							cout << "F = `A + `B";
						}
						if (mins[0] == 0 && mins[1] == 1 && mins[2] == 3) {
							cout << "K-map:\n";
							cout << "1\t0\n1\t1\n";
							cout << "F = `A + B";
						}
						if (mins[0] == 0 && mins[1] == 2 && mins[2] == 3) {
							cout << "K-map:\n";
							cout << "1\t1\n0\t1\n";
							cout << "F = `B + A";
						}
						if (mins[0] == 1 && mins[1] == 2 && mins[2] == 3) {
							cout << "K-map:\n";
							cout << "0\t1\n1\t1\n";
							cout << "F = A + B";
						}
					}
				}
			}
		}
	}
}
int main(){
	char ans = 'y';
	while (ans == 'y') {
		cout << "Enter the number of variables(1-3): ";
		int n; cin >> n;
		while (n < 1 || n > 3) {
			cout << "Invalid...Try again: ";
			cin >> n;
		}
		if (n == 3) {
			k_map_function();
			if (x == 8) {
				cout << "F = 1";
				return 0;
			}
			if (x == 0) {
				cout << "F = 0";
				return 0;
			}
			process_expression();
		}
		else if (n == 1) {
			cout << "Enter the number of minterms(0-2): ";
			int min; cin >> min;
			while (min < 0 || min > 2) {
				cout << "Invalid...try again: ";
				cin >> min;
			}
			if (min == 0) {
				cout << "F = 0\n";
			}
			else {
				if (min == 1) {
					cout << "Enter the minterm: ";
					int xx; cin >> xx;
					while (xx < 0 || xx > 1) {
						cout << "Invalid...try again: ";
						cin >> xx;
					}
					if (xx == 0) {
						cout << "K-map:\n";
						cout << "1\n0\n";
						cout << "F = `A";
					}
					else {
						cout << "K-map:\n";
						cout << "0\n1\n";
						cout << "F = A";
					}
				}
				else {
					if (min == 2) {
						cout << "K-map:\n";
						cout << "1\n1\n";
						cout << "F = 1";
					}
				}
			}
		}
		else {
			two_variable_function();
		}
		cout << "Would you like to display another K-map function?(y/n) ";
		cin >> ans;
		while (ans != 'y' && ans != 'n') {
			cout << "Invalid....try again: ";
			cin >> ans;
		}
	}
}