#include <iostream>
#include <iomanip>
#include <cmath>

double mySqrt(double x);

int main(void) {
	
	double x = 5;
	double sqrtResult = mySqrt(x);
	if(sqrtResult >= 0.0) {
		std::cout << "The sqaure root of " << x << " is approximately " << sqrtResult << "\n"; 
	}
	return 0;
}


double mySqrt(double x) {
	/* Using the newtons method principle xn+1 = xn - f(xn)/f'(xn).
	 * To determine f(x), we can say that we want some equation such that
	 * some x^2 = a ==> x^2 - a = 0 ==> f(x) = x^2 - a
	 * a is the sqaured value, and x is the value we want to determine.*/

	 // Check if the input is valid
	 if(x < 0.0) {
		 std::cout << "Please input a positive number\n";
		 return -1.0;
	 }
	 
	 // since the sqrt(x) <= x/2, therefore a smart guess to speedup the sqrt is to let the 
	 // initial guess be x/2
	 double x1 = x/2.0;
	 double x2 = 0.5*(x1 + (x/x1));
	 
	 // We loop until the abs delta between x2 and x1 is very small (be careful of floating point instability)
	 double tolerance = 0.0000001;
	 
	 while(std::abs(x2 - x1) >= tolerance) {
		 x1 = x2;
		 x2 = ((x1*x1) + x)/(float)(x1+x1);
		 
		 // To avoid floating point instability we round the values x1 and x2 to 3 decimal places
		 x1 = (int)(x1 * 1000.0)/1000.0;
		 x2 = (int)(x2 * 1000.0)/1000.0;
	 }
	 
	 return x2;
}