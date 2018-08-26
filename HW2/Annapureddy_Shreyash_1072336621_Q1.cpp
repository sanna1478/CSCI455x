#include <iostream>

class array2D {
	private:
		int xRes;			//Num of coloumns
		int yRes;			//Num of rows
		float **xtable;		//Pointer for a 2D array
		bool array2D_exists = false; //Flag to store the validity of user input

	public:
		array2D(int columns=320,int rows=240);		//Constructor
		~array2D();			//Destructor
		
		void getSize(int &column,int &row);
		void setValue(int col, int row, float val);
		float getValue(int col,int row);
		
};


int main(void)
{
	int rows, columns;
	float pixelVal = 0;
	
	array2D *a = new array2D(5,10); // With no input creates a default 2D array of size 5 x 10
	a->getSize(columns,rows);
	std::cout << columns << " x " << rows << '\n';

	for(int row=0;row < rows;row++) {
		for(int col=0;col < columns;col++) {
			a->setValue(col,row,100);		// Some constant value
		}
	}
	
	for(int row=0;row < rows;row++) {
		for(int col=0;col < columns;col++) {
			pixelVal = a->getValue(col,row);
			std::cout << pixelVal << ",";
		}
		std::cout << '\n';
	}
	
	delete a;
	return 0;
}








array2D::array2D (int columns, int rows) {
	try {
		xRes = columns;
		yRes = rows;
		
		
		// Exception handling when resolution values are invalid
		if(xRes <= 0 || yRes <=0) throw "Object decleration failed, array dimensions must\n       always be a positive integer greater than zero";
		array2D_exists = true;
		
		xtable = new float*[yRes];
	
		for(int row=0;row < yRes;row++) {
			xtable[row] = new float[xRes];
		}
	
		// Initialise the array with some value
		for(int row=0;row < yRes;row++) {
			for(int col=0;col < xRes;col++) {
				xtable[row][col] = 0;		// Some default value to fill the array
			}
		}
	}
	catch(const char* str) {
		std::cout << "Error: " << str << "\n";
		array2D_exists = false;
		std::exit(1);
	}
}

array2D::~array2D() {
/* Frees all the memory allocated by the constructor */
	if(array2D_exists){
		for(int row=0;row < yRes;row++) {
			delete[] xtable[row];
		}
		delete[] xtable;
	}
}

void array2D::getSize(int &column, int &row) {
	if(array2D_exists) {
		column = xRes;
		row = yRes;
	
	} else {
		// If the array does not exist, we return -1 (error code) as the dimensions
		column = -1;
		row = -1;
	}
}



void array2D::setValue(int col, int row, float val) {
	if(array2D_exists) {
		try {
			// Catch an issues if input by user is bad
			if(row < 0 || col < 0) throw "setValue index must be a positive integer greater than zero";
			if(row >= yRes) throw "setValue row exceeds dimensions of array";
			if(col >= xRes) throw "setValue column exceeds dimensions of array";
			xtable[row][col] = val;
		}
		catch (const char *str) {
			std::cout << "Exception: " << str << '\n';
		}
	} else {
		std::cout << "Error: cannot setValue, 2D array does not exist\n";
	}
}

float array2D::getValue(int col, int row) {
	if(array2D_exists) {
		try {
			// Catch an issues if input by user is bad
			if(row < 0 || col < 0) throw "getValue index must be a positive integer greater than zero";
			if(row >= yRes) throw "getValue row exceeds dimensions of array";
			if(col >= xRes) throw "getValue column exceeds dimensions of array";
			return xtable[row][col];
		}
		catch (const char* str) {
			std::cout << "Exception: " << str << '\n';
			return -1; // value for poor user input
		}
		
	} else {
		std::cout << "Error: cannot getValue, 2D array does not exist\n";
		return -2;	// value if array2D unable to construct a 2D array
	}
}