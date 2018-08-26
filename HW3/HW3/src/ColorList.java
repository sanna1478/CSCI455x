import java.awt.Color;
import java.util.ArrayList;
import java.util.Random;
public class ColorList {

	private Random rand = new Random();
	private int numLoops = 256;
	public ArrayList <java.awt.Color> colList = new ArrayList <java.awt.Color> ();
	
	public static void main(String[] args) {
		ColorList colList = new ColorList();
		
		for(int i=0; i<colList.colList.size(); i++) {
			System.out.println(colList.colList.get(i));
		}

	}
	
	public ColorList() {
		int r=0, g=0, b=0;
		for(int i=0; i<numLoops; i++) {
			r = rand.nextInt(256);
			g = rand.nextInt(256);
			b = rand.nextInt(256);
			
			Color c = new Color(r,g,b);
			colList.add(c);
		}
	}

}
