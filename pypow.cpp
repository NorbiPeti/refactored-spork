#include <iostream>
#include <cmath>

using namespace std;

class Test2;

class Test { //Python ** operator implementation
	double num;
public:
	Test(double num) : num(num) { }
	int operator*(Test2 t);
	Test2 operator*();
	int get_num() { return num; }
	int operator+(Test t) { return num+t.get_num(); }
	int operator-(Test t) { return num-t.get_num(); }
	int operator*(Test t) { return num*t.get_num(); }
	int operator/(Test t) { return num/t.get_num(); }
	
	string nev = "Test";
	const string&getNev() { return nev; } //Szóköz nem is kell
};

class Test2 {
	double num;
public:
	Test2(double num) : num(num) { }
	int get_num() { return num; }
	void operator*() { }
};


int Test::operator*(Test2 t) {
	return pow(num, t.get_num());
}

Test2 Test::operator*() {
	return Test2(num);
}

int main() {
    Test t(5);
    Test u(3);
    cout << t**u << endl;
    cout << u**t << endl;
    cout << Test(2)**t << endl;
    cout << Test(2)**Test(10) << endl;
    cout << Test(2)*Test(10) << endl;
    cout << t.getNev() << endl;
}
