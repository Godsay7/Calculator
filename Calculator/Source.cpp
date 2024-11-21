#include <iostream> 
#include <cctype>
#include <string>
#include <cstdlib>
using namespace std;
//add the ability to work with parentheses

bool errors(const string& chain) {
	int l = chain.length();
	for (int i = 0; i < l; i++) {
		if (i + 1 < l && chain[i] == '/' && chain[i + 1] == '0') {
			if (i + 2 < l && chain[i + 2] == '.') {
				return false;
			}
			return true;
		}
		else if (chain[0] == '-') {
			return true;
		}
	}
	return false;
}

int examplesize(const string& chain) {
	int l = chain.length();
	char symbArr[4] = { '+', '-', '*', '/' };
	int size = 0;
	if (chain[0] == '-') {
		size = 0;
	}
	for (int i = 1; i < l; i++) {
		for (int n = 0; n < 4; n++) {
			if (chain[i] == symbArr[n]) {
				size++;
			}
		}
	}
	return size;
}

char* act(const string& chain) {
	int l = chain.length();
	char symbArr[4] = { '+', '-', '*', '/' };
	char act = 0;
	int size = examplesize(chain) + 1;
	char* arr = new char[size];
	int counterIndex = 0;
	for (int i = 0; i < l; i++) {
		for (int n = 0; n < 4; n++) {
			while (i < l && chain[i] == symbArr[n]) {
				act = symbArr[n];
				i++;
			}
			if (act != 0) {
				arr[counterIndex++] = act;
				act = 0;
			}
		}
	}
	return arr;
}

double parseNumber(const string& chain, int& i) {
	int l = chain.length();
	double number = 0.0;
	bool isDecimal = false;
	double decimalFactor = 0.1;
	while (i < l && isdigit(chain[i]) || chain[i] == '.') {
		if (chain[i] == '.') {
			isDecimal = true;
		}
		else if (isDecimal == false) {
			number = number * 10 + (chain[i] - '0');
		}
		else {
			number += (chain[i] - '0') * decimalFactor;
			decimalFactor *= 0.1;
		}
		i++;
	}
	return number;
}

double* num(const string& chain) {
	int l = chain.length();
	double number = 0.0;
	int size = examplesize(chain) + 1;
	double* arr = new double[size];
	int numberIndex = 0;
	for (int i = 0; i < l; i++) {
		if (isdigit(chain[i]) || chain[i] == '.') {
			arr[numberIndex++] = parseNumber(chain, i);
			i--;
		}
	}
	return arr;
}

double mul(double a, double b) {
	return a * b;
}

double div(double a, double b) {
	return a / b;
}

double sum(double a, double b) {
	return a + b;
}

double sub(double a, double b) {
	return a - b;
}

template <typename T>
void removeElement(T* arr, int& size, int index) {
	for (int i = index; i < size; i++) {
		arr[i] = arr[i + 1];
	}
	size--;
}

int main() {
	string exmpl;
	cin >> exmpl;
	if (errors(exmpl) == true) {
		std::cout << "Error";
		exit(0);
	}
	else {
		double* result = num(exmpl);
		char* actres = act(exmpl);
		int actresSize = examplesize(exmpl);
		int resultSize = actresSize + 1;
		for (int i = 0; i < actresSize; i++) {
			if (actres[i] == '*' || actres[i] == '/') {
				double left = result[i];
				double right = result[i + 1];
				if (actres[i] == '*') {
					left = mul(left, right);
				}
				else {
					left = div(left, right);
				}
				removeElement(result, resultSize, i + 1);
				removeElement(actres, actresSize, i);
				result[i] = left;
				i--;
			}
		}

		double left = result[0];
		double right = 0;
		for (int i = 0; i < actresSize; i++) {
			right = result[i + 1];
			if (actres[i] == '+') {
				left = sum(left, right);
			}
			else if (actres[i] == '-') {
				left = sub(left, right);
			}
		}
		double finalresult = left;
		std::cout << finalresult << endl;;

		delete[] actres;
		delete[] result;
	}
	return 0;
}