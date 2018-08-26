
public class ComplexNumber {
	private double real;
	private double imaginary;
	
	public ComplexNumber(double real, double imaginary) {
		this.real = real;
		this.imaginary = imaginary;
	}
	
	public ComplexNumber() {
		this.real = 0.0;
		this.imaginary = 0.0;
		
	}

	public ComplexNumber add(ComplexNumber c2) {
		double tempReal;
		double tempImaginary;
		
		tempReal = this.real + c2.real;
		tempImaginary = this.imaginary + c2.imaginary; 
		return new ComplexNumber(tempReal, tempImaginary);
		
	}
	
	public ComplexNumber squared() {
		double tempReal;
		double tempImaginary;
		
		tempReal = (this.real*this.real)-(this.imaginary*this.imaginary);
		tempImaginary = 2.0*(this.real*this.imaginary);
		
		return new ComplexNumber(tempReal,tempImaginary);
	}

	public double abs() {
		return Math.sqrt((this.real*this.real)+(this.imaginary*this.imaginary));
	}
	
	public void prt() {
		if(this.imaginary < 0) {
			System.out.println(this.real + " - " + this.imaginary*-1.0 + "j");
		} else {
			System.out.println(this.real + " + " + this.imaginary + "j");
		}
	}
	
	public void setReal(double real) {
		this.real = real;
	}
	
	public void setImaginary(double imaginary) {
		this.imaginary = imaginary;
	}
	
}
