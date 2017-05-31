package javaapplication1;

import java.awt.*;
import javax.swing.*;

public class JRisk {

    private JFrame mainMap;
    private Polygon poly;

    public JRisk(final double x[], final double y[], final int xPoly[], final int yPoly[],final Punct puncte[],final int lung) {
        initComponents(x, y, xPoly, yPoly,puncte,lung);
    }

    private void initComponents(final double x[], final double y[], final int xPoly[], final int yPoly[],final Punct puncte[],final int lung) {

        mainMap = new JFrame();
        mainMap.setResizable(true);
        mainMap.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        JPanel p = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);

                //dezenez punctele
                g.setColor(Color.BLUE);
                Graphics2D g2d = (Graphics2D) g;
                
                for(int i=0;i< lung;i++){
                    int x=(int)(400+25*puncte[i].x);
                    int y=(int)(400-25*puncte[i].y);
                    g2d.fillOval(x - 5,y - 5, 10, 10);
                    g.setColor(Color.BLACK);
                    String c;
                    c = (String) ("P" + puncte[i].i + '(' + puncte[i].x + ',' + puncte[i].y + ')');
                    g.drawString(c, x - 5, y - 5);
                    g.setColor(Color.BLUE);
                }
                   

                //desenez axele
                g.setColor(Color.RED);
                g.drawLine(400, 400, 400, 10);
                g.drawLine(400, 400, 400, 700);
                g.drawLine(400, 400, 10, 400);
                g.drawLine(400, 400, 790, 400);

                g.setColor(Color.BLACK);
                String c;
                c = (String) ("O");
                g.drawString(c, 400, 400);
                c = (String) ("Y");
                g.drawString(c, 400, 10);
                c = (String) ("X");
                g.drawString(c, 790, 400);

                //tot ce e mai sus afisam oricum,aici vin x si y noi dupa acoperire si calculam xPoly si YPoly noi
                //desenez poligonul
                poly = new Polygon(xPoly, yPoly, xPoly.length);
                g.drawPolygon(poly); //fillPolygon

            }

            @Override
            public Dimension getPreferredSize() {
                return new Dimension(800, 800); //dimensiunea ferestrei
            }
        };
        mainMap.add(p);
        mainMap.pack();
        mainMap.setVisible(true);
    }
}