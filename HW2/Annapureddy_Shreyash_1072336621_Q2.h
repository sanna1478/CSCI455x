
// Array2D class allows users to genereate a 2D array
class array2D {
	public:
		int xRes;			//Num of coloumns
		int yRes;			//Num of rows
		float **xtable;		//Pointer for a 2D array
	private:
		bool array2D_exists = false; //Flag to store the validity of user input

	public:
		array2D(int columns=640, int rows=480);		//Constructor
		~array2D();							//Destructor
		
		void getSize(int &col,int &row);
		void setValue(int col, int row, float val);
		float getValue(int col,int row);
		
};

// Create a PGM class that inherits the methods of array2D
class PGMImage: public array2D {
	private:
		std::string fileName;
		bool validFile = false;
		void checkFileName();
		
	public:
		// Constructors
		PGMImage(int columns, int rows, std::string& imageFileName);
		PGMImage(std::string& imageFileName);
		PGMImage(int columns, int rows);
		PGMImage(int columns);
		PGMImage(int columns, std::string& imageFileName);
		PGMImage();
		
		// Destructor
		~PGMImage();
		
		
		void changeResolution(int newCol, int newRow);
		void setPixel(int col, int row, float val);
		void getResolution(int &col,int &row);
		void writeFile();
		float getPixel(int col, int row);
		
		bool isValidFile();
};