#include <iostream>
#include <string>
#include <fstream>
#include "Q2.h"

int main(void)
{
	// Creating an image object
	std::string fileName = "test.pgm";
	PGMImage *img = new PGMImage(fileName);
	
	// Getting the resolution of the image
	int yRes, xRes;
	img->getResolution(xRes,yRes);
	std::cout << "The image resolution is: ";
	std::cout << xRes << " x " << yRes << '\n';
	
	// Setting pixel value
	int x = 0; int y = 0;
	float val = 255;
	std::cout << val << " being set at " << "[" << x << "," << y << "]\n";
	img->setPixel(x,y,255);
	
	// Getting a pixel value in img
	x = 0, y = 0;
	val = img->getPixel(x,y);
	std::cout << "The pixel value at " << "[" << x << "," << y << "] is ";
	std::cout << val << '\n';
	
	// writing image with fileName
	img->writeFile();
	
	// Free memory
	delete img;
	return 0;
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