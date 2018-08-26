import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.*;

public class Mandelbrot {
	private double[][] xtable;
	
	/***********************************************
	 * Default values if user does not provide any
	 * values to the Mandelbrot constructor
	 ***********************************************/
	private int xRes = 640;			// Width of image
	private int yRes = 480;			// Height of image
	private double cxMin = -2.0;	// Min domain of Mandelbrot
	private double cxMax = 1.0;		// Max domain of Mandelbrot
	private double cyMin = -1.0;	// Min range of Mandelbrot
	private double cyMax = 1.0;		// Min range of Mandelbrot
	
	private boolean fileExists = false;
	private boolean badFileName = false;
	
	private ColorList colors;
	
	

	public static void main(String[] args) {
		/**********************************************
		 *The following variables are user definable 
		 *parameters
		 **********************************************/
		int xRes = 640;
		int yRes = 480;
		double cxMin = -2.0;
		double cxMax = 1.0;
		double cyMin = -1.0;
		double cyMax = 1.0;
		String fileName = "test.ppm";
		
		JFrame frame = new JFrame("Mandelbrot");
		JPanel panel = new JPanel();
		JLabel label = new JLabel();
		BufferedImage mandelbrotImage = new BufferedImage(xRes,yRes,BufferedImage.TYPE_INT_RGB);
		ImageIcon mandelbrotImgIcon = new ImageIcon(mandelbrotImage);
		// Initial frame setup
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.setSize(new Dimension(xRes,yRes));
		
		// Adding image icon to the label
		label.setIcon(mandelbrotImgIcon);
		
		// Adding JLabel to Panel
		panel.setLayout(new BorderLayout()); // Create components with no gaps or borders
		panel.setPreferredSize(new Dimension(xRes,yRes));	// Set size of panel
		panel.add(label);
				
		// Adding JPanel to the frame to display Image
		frame.add(panel);
		
		Graphics mandelbrotGraphics = mandelbrotImage.getGraphics();
		Mandelbrot mandelbrot = new Mandelbrot(xRes,yRes,cxMin,cxMax,cyMin,cyMax);
		mandelbrot.displayFractal(mandelbrotGraphics);
		mandelbrot.saveFractal(fileName);
		
		
		// Pack and set the frame to be viewable to the user
		frame.pack();
		frame.setVisible(true);	

	}
	
	public Mandelbrot(int xRes, int yRes, double cxMin, double cxMax, double cyMin, double cyMax) {
		
		
		if(cxMin >= cxMax) {
			System.out.println("Error: cxMin is greater than or equal to cxMax");
			System.exit(1);
		} else {
			this.cxMin = cxMin;
			this.cxMax = cxMax;
		}
		if(cyMin >= cyMax) {
			System.out.println("Error: cxMin is greater than or equal to cxMax");
			System.exit(1);
		} else {
			this.cyMin = cyMin;
			this.cyMax = cyMax;
		}
		
		try {
			if(xRes<=0 || yRes <=0) {
				throw new NegativeArraySizeException("Mandelbrot object decleration failed, xRes and yRes must be positive integers greater than zero");  
			}
			this.xRes = xRes;
			this.yRes = yRes;
			xtable = new double[this.yRes][this.xRes];
			colors = new ColorList();
			this.calcMandelbrot();
		} catch(NegativeArraySizeException e) {
			System.out.println("Error: " + e);
			System.exit(2);
		}
	}
	
	// Overload constructor in the event no user input provided
	public Mandelbrot() {
		System.out.println("Exception: No arguments provided, using default values");
		xtable = new double[yRes][xRes];
		colors = new ColorList();
		this.calcMandelbrot();
	}
	
	// Overload constructor if user just wants to provide image dimensions
	public Mandelbrot(int xRes, int yRes) {
		try {
			if(xRes<=0 || yRes <=0) {
				throw new NegativeArraySizeException("Mandelbrot object decleration failed, xRes and yRes must be positive integers greater than zero");  
			}
			System.out.println("Exception: cxMin, cxMax, cyMin and cyMax not provided, default values used");
			this.xRes = xRes;
			this.yRes = yRes;
			xtable = new double[this.yRes][this.xRes];
			colors = new ColorList();
			this.calcMandelbrot();
		} catch(NegativeArraySizeException e) {
			System.out.println("Error: " + e);
			System.exit(2);
		}
	}
	// Overload constructor if user just wants to provide the domain and range
	public Mandelbrot(int cxMin, int cxMax, int cyMin, int cyMax) {
		if(cxMin >= cxMax) {
			System.out.println("Error: cxMin is greater than or equal to cxMax");
			System.exit(1);
		} else {
			this.cxMin = cxMin;
			this.cxMax = cxMax;
		}
		if(cyMin >= cyMax) {
			System.out.println("Error: cxMin is greater than or equal to cxMax");
			System.exit(1);
		} else {
			this.cyMin = cyMin;
			this.cyMax = cyMax;
		}
		
		xtable = new double[this.yRes][this.xRes];
		colors = new ColorList();
		this.calcMandelbrot();		
	}
	
	
	
	public void displayFractal(Graphics g) {
		int red;
		int green;
		int blue;
		int grayPixVal;
		
		for(int row=0; row<yRes; row++) {
			for(int col=0; col<xRes; col++) {
				grayPixVal = (int)xtable[row][col];
				
				red = colors.colList.get(grayPixVal).getRed();
				green = colors.colList.get(grayPixVal).getGreen();
				blue = colors.colList.get(grayPixVal).getBlue();
				
				setPixel(g,col,row,red,green,blue);
				
			}
		}
	}

	public void saveFractal(String fileName) {
		this.checkFileExists(fileName);
		this.checkFileName(fileName);
		if(fileExists) System.out.println("Exception: file " + fileName + " already exists, file will be overwritten");
		if(badFileName) {
			System.out.println("Error: file extension is invalid no file written. Expected, *.ppm");
			return;
		}
		try {
			FileWriter fileWriter = new FileWriter(fileName);
			BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
		
			// Header
			bufferedWriter.write("P3");
			bufferedWriter.newLine();
			bufferedWriter.write(this.xRes + " " + this.yRes);
			bufferedWriter.newLine();
			bufferedWriter.write("255");
			bufferedWriter.newLine();
			
			Color imgColor;
			
			int index;
			
			// Load pixels into the file
			for(int row=0; row<this.yRes; row++) {
				for(int col=0; col<this.xRes; col++) {
					index = (int)xtable[row][col];
					imgColor = colors.colList.get(index);
					bufferedWriter.write(imgColor.getRed() + " " + imgColor.getGreen() + " " + imgColor.getBlue());
					bufferedWriter.newLine();
				}
			}
			bufferedWriter.close();
			
		} catch(IOException ex) {
			System.out.println("Error: could not write to file");
			ex.printStackTrace();
		}
	}
	
	private void calcMandelbrot() {
		double real;
		double imaginary;
		
		double deltaCX = cxMax-cxMin;
		double deltaCY = cyMax-cyMin;
		
		ComplexNumber c = new ComplexNumber();
		ComplexNumber z = new ComplexNumber();
		
		int maxIter = 255;
		int iter = 0;
		
		for(int row=0; row<yRes; row++) {
			for(int col=0; col<xRes; col++) {
				real = cxMin + (col/(xRes-1.0)) * deltaCX;
				imaginary = cyMin + (row/(yRes-1.0)) * deltaCY;
				c.setReal(real);
				c.setImaginary(imaginary);
				z.setReal(0.0);
				z.setImaginary(0.0);
				iter = 0;
				
				while(iter < maxIter && z.abs() < 2.0) {
					z = z.squared();
					z = z.add(c);
					iter++;
				}
				
				if(z.abs()>=2.0) {
					xtable[row][col] = (double)iter;
				} else {
					xtable[row][col] = 0.0;
				}
			}
		}
		
	}

	private void setPixel(Graphics g, int col, int row, int red, int green, int blue) {
		g.setColor(new Color(red,green,blue));
		g.drawLine(col, row, col, row);		// Setting pixel value
	}
	
	private void checkFileExists(String fileName) {
		File file = new File(fileName);
		if(file.exists()) {
			System.out.println("Exception: file " + fileName + " already exists");
			fileExists = true;
		}
	}

	private void checkFileName(String fileName) {
		String extension = ".ppm";
		if(!fileName.contains(extension)) {
			System.out.println("Exception: file extension is invalid, expected extension: *.ppm");
			badFileName = true;	
		}
	}

}
