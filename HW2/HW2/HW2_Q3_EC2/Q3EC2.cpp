#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "Q3EC2.h"

void getDeltaBounding(double delta[], double boundingBoxStart[], double boundingBoxEnd[], int numImgs);
void generateImgs(double delta[], double boundingBox[], int numImgs, int imgDimensions[]);
void calcMandelbrot(PGMImage *img, double boundingBox[]);
void desiredFractal(double boundingBox[], int fractal=0);
void aspectRatio(double boundingBox[], int dimensions[]);


int main(void)
{
	
	int numImgs = 25;					// Num of images we wish to generate
	int columns = 640, rows = 480;		// The dimensions of the image we want to generate
	
	/* Determine the bounding box for specific pattern
	 * 0 = Sea Horse Valley
	 * 1 = Triple Spiral Valley
	 * 2 = Quad Spiral Valley
	 * 3 = Double Scepter Valley
	 * 4 = Mini mandelbrot */
	int fractalDesign = 0;
	double boundingBoxStart[] ={-2.0,1.0,-1.0,1.0};
	double boundingBoxEnd[] = {-2.0,1.0,-1.0,1.0};
	double deltaBounding[] = {0.0,0.0,0.0,0.0};
	desiredFractal(boundingBoxEnd, fractalDesign);	// Determine the boundingBox
	
	
	/* Determine the delta we move by for each image from the starting bounding values
	   to the desired fractal pattern bounding box */
	getDeltaBounding(deltaBounding,boundingBoxStart,boundingBoxEnd,numImgs);
	
	
	
	// Generate a squence of images
	int imgDimensions[] = {columns, rows};
	generateImgs(deltaBounding,boundingBoxStart,numImgs,imgDimensions);
	return 0;
}



// Function Definitions
void generateImgs(double delta[], double boundingBox[], int numImgs, int imgDimensions[]) {
	int numBoundVals = 4;		// Number of values needed to bound the mandelbrot set {xmin,xmax,ymin,ymax}
	
	// Breaking file name into 3 parts for ease of creating new file names
	std::string name = "intermediate_fractal";		// the main identifier name
	std::string num;								// the image number
	std::string extension = ".pgm";					// the image extension
	std::string fileName;
	
	for(int img=0; img<numImgs; img++) {
		std::cout << "Generating image " << img+1 << " of "  << numImgs << '\n';
		
		num = std::to_string(img);
		fileName = name + num + extension;
		PGMImage *mandelbrot = new PGMImage(imgDimensions[0],imgDimensions[1],fileName);
		
		if(img!=0) {
			for(int index=0; index<numBoundVals; index++) {
				boundingBox[index] += delta[index];
			}
		}
		
		calcMandelbrot(mandelbrot, boundingBox);
		mandelbrot->writeFile();
		delete mandelbrot;
	}
	std::cout << "Image generation completed!\n";
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

void getDeltaBounding(double delta[], double boundingBoxStart[], double boundingBoxEnd[], int numImgs) {
	int numBoundVals = 4;		// Number of values needed to bound the mandelbrot set {xmin,xmax,ymin,ymax}
	for(int index=0; index<numBoundVals; index++) {
		delta[index] = (boundingBoxEnd[index]-boundingBoxStart[index])/(double)numImgs;
	}
}

void desiredFractal(double boundingBox[], int fractal) {
	/* Returns a specific bounding box that defines a fractial in the 
	 * mandelbrot set. The fractal pattern can be seelected using the
	 * variable fractal:
	 * 					0. Sea Horse Valley
	 * 					1. Triple Spiral Valley
	 * 					2. Quad Spiral Valley
	 * 					3. Double Scepter Valley
	 * 					4. Mini mandelbrot
	 * 
	 * By default always show the Sea Horse Spiral */
	 
	int cxmin = 0, cxmax = 1, cymin = 2, cymax = 3;		// Meaningful index for boundingBox array
	double fractalPatterns[5][4] = {{-0.75,0.1,0.005,0.005},		// Sea Horse Valley
								  {-0.088,0.654,0.025,0.025},	// Triple Spiral Valley
								  {0.274,0.482,0.005,0.005},		// Quad Spiral Valley
								  {-0.1002,0.8383,0.005,0.005},		// Double Scepter Valley
								  {-1.75,0.0,0.02,0.02}};			// Mini mandelbrot
								  
	double deltaX = fractalPatterns[fractal][2];		// Scalling factor for different fractal patterns
	double deltaY = fractalPatterns[fractal][3];
	
	// Checking if invalid fractal value
	if(fractal < 0 || fractal > 4) {
		std::cout << "Fractcal value must be between 0 and 4 inclusive, default Sea Horse Valley pattern returned";
		fractal = 0;
	}
	
	boundingBox[cxmin] = fractalPatterns[fractal][0];
	boundingBox[cxmax] = fractalPatterns[fractal][0] + deltaX;
	boundingBox[cymin] = fractalPatterns[fractal][1];
	boundingBox[cymax] = fractalPatterns[fractal][1] + deltaY;
}

void aspectRatio(double boundingBox[], int dimensions[]) {
/* Determine a new resolution for the madelbrot img in order
 * to maintain a high quality image when zooming into a specific 
 * feature 
 */
	int imgCol = 0, imgRow = 1;
	double cxmin = boundingBox[0];
	double cxmax = boundingBox[1];
	double cymin = boundingBox[2];
	double cymax = boundingBox[3];
	
	// Determining aspect ratio to 1 decimal place
	float aspectRatio  = std::round(10.0*(cxmax-cxmin)/(cymax-cymin))/10.0;		
	int scaleFactor = 1000;
	
	// Determine a resolution maintaing the aspect ratio
	dimensions[imgCol] = aspectRatio*scaleFactor;
	dimensions[imgRow] = scaleFactor;
}
// Function Definitions







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
		std::cerr << "Error: " << str << '\n';
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
		std::cerr << "Error: " << str << '\n';
		
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
		std::cerr << "Error:cannot setValue, 2D array does not exist\n";
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
		std::cerr << "Error: cannot getValue, 2D array does not exist\n";
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








// ComplexNumber Methods
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
/* Allows user to set the real value of a ComplexNumber object */
	re = real;
}

void ComplexNumber::setImaginary(double imaginary) {
/* Allows user to set the imaginary value of a ComplexNumber object */
	im = imaginary;
}
// ComplexNumber Methods