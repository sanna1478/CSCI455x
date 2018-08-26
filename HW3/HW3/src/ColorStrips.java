import java.awt.*;
import javax.swing.*;

public class ColorStrips {

	public static void main(String[] args) {
		ColorList colList = new ColorList(); // Generate colors, to use for populating strips below
		
		JFrame frame = new JFrame(); // Window
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		frame.setLayout(new GridLayout(colList.colList.size(),1));
		
		JPanel p;
		Color c;
		
		for(int i=0; i<colList.colList.size(); i++) {
			p = new JPanel();
			c = colList.colList.get(i);
			p.setBackground(c);
			p.setPreferredSize(new Dimension(100,4));
			frame.add(p);
		}
		
		frame.pack();
		frame.setVisible(true);
	}

}
