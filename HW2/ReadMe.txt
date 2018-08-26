====== Compiler and IDe ======
IDE: CodeLite
Compiler: GCC c++11


====== Q1 Usage ======

Legal Object Decleration:
	1. array2D():
 		Default dimensions: 320 x 240 used

	2. array2D(int x): 		
		Default rows used dimensions: x x 240

	3. array2D(int x, int y):	
		An array with  dimensions: x x y


Object Method Usage:
	1. *->getSize(int& xRes, int& yRes):
		By reference gets the dimension of the array2D
		and stores it in xRes and yRes.


	2. *->setValue(int x, int y, float val):
		Stores val in array2D location array2D[y][x].

	3. float val = *->getValue(int x, int y):
		returns the value stored at array2D[y][x] as a float.
		if y and x attempt to access illegal location, method
		returns -1. 
		If array does not exist method returns -2.



====== Q2 Usage ======

Legal Object Decleration:
	1. PGMImage(int x):
		Default rows used, dimensions: x x 480.
		Since no file name given, *->writeFile() will
		not create a file to save the image.


	2. PGMImage(int x, int y):
		Dimensions of image: x x y. Since no
		file name given, *->writeFile() will
		not creatae a file to save the image


	3. PGMImage(std::string& fileName):
		Default dimensions: 640 x 480.


	4. PGMImage(int x, std::string& fileName):
		Default rows used, dimensions: x x 480.


	5. PGMImage(int x, int y, std::string& fileName):
		Dimensions of image: x x y.


Object Method Usage:
	1. *->getResolution(int& xRes, int& yRes)
		By reference gets the dimension of the PGMImage array
		and stores it in xRes and yRes.


	2. *->setPixel(int x, int y, float val):
		Stores val in PGMImage array location PGMImage[y][x].


	3. float val = *->getPixel(int x, int y):
		Returns the value stored at PGMImage[y][x] as a float.
		If y and x attempt to access illegal location, method return -1.
		If array does not exist method returns -2.


	4. *->writeFile():
		Using the file name during object decleration creates a 
		file and saves it in the local directory of the program.


	5. bool ifile = *->isValidFile():
		Returns a false if the fileName given is illegal.
		Else true if the fileName is legal.


	6. *->changeResolution(int xRes, int yRes):
		Changes the resolution of the PGMImage to dimensions: xRes x yRes.


		

====== Q3 Usage ======

Legal object declerations and object method usage is the same as Q2.

Create Mandelbrot Image:

	calcMandelbrot(PGMImage* img, double boundingBox[]):
		img, is the PGMImage object.
		boundingBox[] contains {cxmin,cxmax,cymin,cymax} which
		are the boundary of the mandelbrot image.



====== Q3EC1 Usage ======

Legal object declerations and object methods usage for
array2D and PGMImage is the same as Q1 and Q2 respectively.


Determine boundingBox[] for a specific fractal pattern:
	
	desiredFractal(double boundingBox[], int fractal):
		Function determines boundingBox[] = {cxmin,cxmax,cymin,cymax}
		for a design defined by fractal.
		fractal values give the following features:
			fractal = 0 [Sea Horse Valley]
			fractal = 1 [Triple Spiral Valley]
			fractal = 2 [Quad Spiral Valley]
			fractal = 3 [Double Scepter Valley]
			fractal = 4 [Mini Mandelbrot]
		
	

Calculate new Image dimension:

	aspectRation(double boundingBox[], int newDim[]):
		Determines aspect ratio based on the boundingBox
		then determines xRes and yRes with this aspect ratio
		and stores value into newDim[] = {xRes,yRes}





Create Mandelbrot Image:

	calcMandelbrot(PGMImage* img, double boundingBox[]):
		img, is the PGMImage object.
		boundingBox[] contains {cxmin,cxmax,cymin,cymax} which
		are the boundary of the mandelbrot image.





====== Q3EC2 Usage ======
Legal object declerations and object methods usage for
array2D and PGMImage is the same as Q1 and Q2 respectively.


Determine boundingBox[] for a specific fractal pattern:
	
	desiredFractal(double boundingBox[], int fractal):
		Function determines boundingBox[] = {cxmin,cxmax,cymin,cymax}
		for a design defined by fractal.
		fractal values give the following features:
			fractal = 0 [Sea Horse Valley]
			fractal = 1 [Triple Spiral Valley]
			fractal = 2 [Quad Spiral Valley]
			fractal = 3 [Double Scepter Valley]
			fractal = 4 [Mini Mandelbrot]


Determine delta to change in bounding for zooming in:

	getDeltaBounding(double delta[], double boundingBoxStart[], 
			 double boundingBoxEnd[], int numImgs):

		Determines the step size between the start and end bounding box
		to create the effect of zooming in an image.



Generate a sqeuence of images:

	generateImgs(double delta[], double boundingBox[], int numImgs, int imgDimensions[]):
		Creates numImgs number of images. In order to change the name
		the files are saved under, change the value in std::string name ONLY.







