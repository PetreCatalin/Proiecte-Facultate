
package javaapplication1;

import java.util.*;
import javax.swing.*;

public class JarvisMarch {

    public int nrAcoperire;

    private boolean Orientare(Punct p, Punct q, Punct r) {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        return val < 0;
    }

    public Punct[] AcoperireConvexa(Punct[] puncte, int stanga, int nrPuncte) {
        int n = nrPuncte, nr = -1;
        int[] indici = new int[n + 1];
        Punct[] acoperire = new Punct[n];
        Arrays.fill(indici, -1);
        int p = stanga, q;
        boolean ok = true;
        while (p != stanga || ok) {
            ok = false;
            q = (p + 1) % n;
            for (int i = 0; i < n; i++) {
                if (Orientare(puncte[p], puncte[i], puncte[q])) {
                    q = i;
                }
            }
            indici[p] = ++nr;
            p = q;
        }
        int k = nr;
        nr = -1;
        int z = 0;
        System.out.println("Punctele acoperirii convexe,sunt:\n");
        while (z < k + 1) {
            for (int i = 0; i < n; i++) {
                if (indici[i] == z) {
                    System.out.println("P" + puncte[i].i + " (" + puncte[i].x + " , " + puncte[i].y + ")");
                    acoperire[++nr] = new Punct();
                    acoperire[nr].x = puncte[i].x;
                    acoperire[nr].y = puncte[i].y;
                    acoperire[nr].i = puncte[i].i;
                    z++;
                }

            }
        }
        nrAcoperire = nr + 1;
        return acoperire;
    }

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Introduceri numarul de puncte: ");
        final int n = scan.nextInt();
        /*while (n < 3) {
         System.out.println("Numarul de puncte introdus este invalid!\nIntroduceti minim 3 puncte!");
         n = scan.nextInt();
         }*/
        int stanga = -1;
        JarvisMarch x = new JarvisMarch();
        final Punct[] puncte = new Punct[n + 1];
        System.out.println("Introduceti cele " + n + " cooronate: ");
        for (int i = 0; i < n; i++) {
            puncte[i] = new Punct();
            puncte[i].x = scan.nextDouble();
            puncte[i].y = scan.nextDouble();
            puncte[i].i = i;
            if (stanga == -1) {
                stanga = i;
            } else if (puncte[stanga].x > puncte[i].x) {
                stanga = i;
            }
        }
       Punct[] acoperire = x.AcoperireConvexa(puncte, stanga, n);
       final int[] xPoly = new int[x.nrAcoperire];
       final int[] yPoly = new int[x.nrAcoperire];
       final double[] xx = new double[x.nrAcoperire];
       final double[] yy = new double[x.nrAcoperire];
        for (int i = 0; i < x.nrAcoperire; i++) {
            xPoly[i] = (int) (acoperire[i].x * 25 + 400);
            yPoly[i] = (int) (400 - acoperire[i].y * 25);
            xx[i] = acoperire[i].x;
            yy[i] = acoperire[i].y;
        }
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new JRisk(xx, yy, xPoly, yPoly, puncte, n);
            }
        });
    }
}
