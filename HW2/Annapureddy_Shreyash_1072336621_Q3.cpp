#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "Annapureddy_Shreyash_1072336621_Q3.h"

void calcMandelbrot(PGMImage *img, double boundingBox[]);

int main(void) {
	
	// Creating a PGMImage object
	std::string fileName = "fractal.pgm";
	PGMImage *mandelbrot = new PGMImage(fileName);
	
	// Bounding region for mandelbrot
	double boundingBox[] = {-2.0,1.0,-1.0,1.0};
	
	// Calculating the mandelbrot set and storing pixel values
	calcMandelbrot(mandelbrot, boundingBox);
	
	// Write img to a file
	mandelbrot->writeFile();
	
	delete mandelbrot;
	return 0;
}



void calcMandelbrot(PGMImage *img, double boundingBox[]) {
/* Takes in the PGMImage object and bounding box to calculate the 
 * mandelbrot set and store the calculated pixel values into img*/
	int maxIter = 255, iter = 0;
	int xRes, yRes;
	
	double cxmin = boundingBox[0];
	double cxmax = boundingBox[1];
	double cymin = boundingBox[2];
	double cymax = boundingBox[3];
	
	ComplexNumber c;
	ComplexNumber z;
	
	img->getResolution(xRes,yRes);
	
	// For loop to compute mandelbrot set values and store in a file
	for(int row=0; row<yRes; row++) {
		for(int col=0; col<xRes; col++) {
			c.setReal(cxmin + (double)(col/(xRes-1.0)) * (cxmax-cxmin));
			c.setImaginary(cymin + (double)(row/(yRes-1.0)) * (cymax-cymin));
			z.setReal(0);
			z.setImaginary(0);
			iter = 0;
			while(iter < maxIter && z.abs() < 2.0) {
				z = z.squared();
				z = z.add(c);
				iter++;
			}
			if(z.abs()>=2) {
				img->setPixel(col,row,iter);
			} else {
				img->setPixel(col,row,0);
			}
		}
	}
}





// array2D class constructor, destructor and method definitions
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
		std::cout << "Error: " << str << '\n';
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

void array2D::getSize(int &col, int &row) {
	try {
		if(!array2D_exists) throw "getSize cannot get dimensions, array does not exist";
		col = xRes;
		row = yRes;
	} catch (const char *str) {
		std::cout << "Error: " << str << '\n';
		
		// Set negative values if failure occurs
		row = -1;
		col = -1;
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
		std::cout << "Error:cannot setValue, 2D array does not exist\n";
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
			return -1;
		}
		
	} else {
		std::cout << "Error: cannot getValue, 2D array does not exist\n";
		return -2;
	}
}
// array2D class constructor, destructor and method definitions


// PGMImage class constructors, destructor and method definitions
PGMImage::PGMImage(int columns, int rows, std::string &imageFileName) : array2D(columns,rows) {
	fileName = imageFileName;
	this->checkFileName();
	if(!validFile) std::exit(2);
}

PGMImage::PGMImage(std::string &imageFileName) : array2D(){
	fileName = imageFileName;
	this->checkFileName();
	if(!validFile) std::exit(2);
	std::cout << "Exception: no image dimensions given during object decleration,\n";
	std::cout << "           using default " << xRes << "x" << yRes << '\n';
}

PGMImage::PGMImage(int columns, int rows) : array2D(columns, rows) {
	std::cout << "Exception: no file name given during object decleration,\n";
	std::cout << "           writeFile() method will not write a file\n";
}

PGMImage::PGMImage(int columns) : array2D(columns){
	std::cout << "Exception: only columns given during object decleration, using default rows " << yRes <<"\n";
	std::cout << "Exception: no file name given during object decleration,\n";
	std::cout << "           writeFile() method will not write a file\n";
}

PGMImage::PGMImage(int columns, std::string &imageFileName) : array2D(columns) {
	fileName = imageFileName;
	this->checkFileName();
	if(!validFile) std::exit(2);
	std::cout << "Exception: only columns has been set, using default rows " << yRes << "\n";
}

PGMImage::PGMImage() {
	std::cout << "Error: not enough arguments provided to create object\n";
	std::cout << "       Legal object declerations are:\n" ;
	std::cout << "            PGMImage(int,int,std::string)\n";
	std::cout << "            PGMImage(int,int)\n";
	std::cout << "            PGMImage(int)\n";
	std::cout << "            PGMImage(std::string)\n";
	std::cout << "            PGMImage(int,std::string)\n";
	std::exit(3);
}

PGMImage::~PGMImage(){};

void PGMImage::changeResolution(int newCol, int newRow) {
	try {
		if(newCol<=0 || newRow <=0) throw "Invalid resolution, image resolution has not been changed";
		
		// Delete the original image
		for(int row=0;row < yRes;row++) {
			delete[] xtable[row];
		}
		delete[] xtable;
		
		// Create new image
		xRes = newCol;
		yRes = newRow;
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
	} catch (const char *str) {
		std::cout << "Exception: " << str << '\n';
	}	
}

void PGMImage::getResolution(int &col, int &row) {
	PGMImage::getSize(col, row);
}

void PGMImage::setPixel(int col, int row, float val) {
	PGMImage::setValue(col,row,val);
}

float PGMImage::getPixel(int col, int row) {
	return PGMImage::getValue(col,row);
}

void PGMImage::checkFileName() {
	
	// Check if file name is valid and exists
	bool wrongExtension = false;
	std::string imgExt = ".pgm";
	std::ifstream stream(fileName);
	
	// Checking if file already exists
	if(stream.good()) {
		std::cout << "Error: file " << fileName << " already exists\n";
		validFile = false; 
	} else {
		validFile = true;
	}
	// Need to check if the extension of the image is correct
	std::string::reverse_iterator extIterator;		//String iterator allows access to a string in reverse order
	std::string::reverse_iterator fileIterator = fileName.rbegin();		// iterator allows access to fileName in reverse order
	
	for(extIterator=imgExt.rbegin(); extIterator!=imgExt.rend(); extIterator++) {
		if(*fileIterator != *extIterator) {
			wrongExtension = true;
		}
		fileIterator++;
	}
	if(wrongExtension) {
		validFile = false;
		std::cout << "Error: file extension either incorrect, does not exist or incorrect case. expected: *.pgm\n";
	}
}

bool PGMImage::isValidFile() {
	return validFile;
}

void PGMImage::writeFile() {
	
	/* Write and creates a PGM image file */
	if(validFile){
		std::ofstream pgmFile(fileName);
		
		//header
		pgmFile << "P2" << '\n';
		pgmFile << xRes << " " << yRes << '\n';
		pgmFile << 255 << '\n';
		
		// Load pixles into the file
		for(int row=0; row<yRes; row++) {
			for(int col=0; col<xRes; col++) {
				pgmFile << xtable[row][col] << " ";
			}
			pgmFile << '\n';
		}
		pgmFile.close();
	} else {
		std::cout << "Exception: invlid file name or no file name given to PGMImage object, cannot writeFile()\n";
	}
	
}
// PGMImage class constructors, destructor and method definitions





// ComplexNumber class constructors, destructor and method definitions
ComplexNumber::ComplexNumber(double real, double imaginary) {
	re = real;
	im = imaginary;
}

ComplexNumber::~ComplexNumber(){};

ComplexNumber ComplexNumber::add(ComplexNumber c2) {
	double real;
	double imaginary;
	real = re + c2.re;
	imaginary = im + c2.im;
	return ComplexNumber(real,imaginary);
}

ComplexNumber ComplexNumber::squared() {
	double re_new = 0;
	double im_new = 0;
	re_new = (re*re)-(im*im);
	im_new = 2*(re*im);
	return ComplexNumber(re_new,im_new);
}

double ComplexNumber::abs() {
	return std::sqrt((re*re)+(im*im));
}

void ComplexNumber::prt() {
	if(im < 0) {
		std::cout << re << " - " << im*-1 << "j\n";
	} else {
		std::cout << re << " + " << im << "j\n";
	}
}

void ComplexNumber::setReal(double real) {
	re = real;
}

void ComplexNumber::setImaginary(double imaginary) {
	im = imaginary;
}
// ComplexNumber class constructors, destructor and method definitions
