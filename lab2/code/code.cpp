#include <iostream>
#include <math.h>

using namespace std;

double a, b, startX, endX, dx;

bool equal(double a, double b, double eps) {
	return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * eps);
}

double f(double x) {
	if (x < a || equal(x, a, 0.01))
		return abs(x) + sin(x);
	else if (x < b && x > a)
		return log(abs(x)) / log(3);
	else if (x > b || equal(x, b, 0.01))
		return tan(x);
}

int main() {
	cout << "a = ";
	cin >> a;

	cout << "b = ";
	cin >> b;

	cout << "startX = ";
	cin >> startX;

	cout << "endX = ";
	cin >> endX;

	cout << "dx = ";
	cin >> dx;

	double firstval = f(startX);
	cout << '(' << startX << ',' << firstval << ')';
	double max = firstval;
	double min = firstval;

	for (double i = startX + dx; i <= endX + dx; i += dx) {
		double val = f(i);
		cout << ", (" << i << ',' << val << ')';
		if (val > max) max = val;
		if (val < min) min = val;
	}



	cout << endl;
	cout << "max: " << max << endl;
	cout << "min: " << min << endl;

	system("pause");

	return 0;
}
