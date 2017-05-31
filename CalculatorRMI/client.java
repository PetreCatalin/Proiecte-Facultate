import java.rmi.*;
import java.util.Scanner;

public class client {
    public static void meniu() {
		System.out.println("1.Adunare");
		System.out.println("2.Scadere");
		System.out.println("3.Inmultire");
		System.out.println("4.Impartire");
		System.out.println("5.Inversare");
		System.out.println("6.Factorial");
		System.out.println("7.Putere");
		System.out.println("8.Radacina");
                System.out.println("9.Valoarea memoriei devine rezultatul curent");
                System.out.println("10.Reinitializare memoriei cu 0");
                System.out.println("11.Adunarea rezultatului curent la memorie");
                System.out.println("12.Scaderea rezultatului curent din memorie");
                System.out.println("13.Rezultatul curent devine valoarea memoriei");
                System.out.println("14.Afisarea valorii memoriei");
                System.out.println("15.Iesire program");
                System.out.println();
	}
    
    public static void main(String[] args) throws RemoteException {
                Hello Ob=null;
		try {
                     Ob =(Hello) Naming.lookup("rmi://localhost:1234/Hello"); 
                    }
                 catch (Exception e) {
			System.out.println("Conectare esuata");
			System.exit(0);
                    } 
                    int comanda = 0,ok=0;
                    Scanner sc = new Scanner(System.in);
                    double rez=0,a,b,mem=0;
                    meniu();

                    while (1==1) {
                        System.out.print("Alegeti optiunea dorita: ");
                        comanda=sc.nextInt();
                        if (comanda<1 ||comanda>15) System.out.println("Comanda invalida,incercati alta optiune");
                        if (comanda==1) {
                            System.out.print("Introduceti numerele de adunat:");
                           
                            a=sc.nextDouble();
                            b=sc.nextDouble();
                            rez=Ob.adunare(a,b);ok=0;       
                        }
                        if (comanda==2) {
                            System.out.print("Introduceti numerele de scazut:");
                            a=sc.nextDouble();
                            b=sc.nextDouble();
                            rez=Ob.scadere(a,b);ok=0;
                        }
                        if (comanda==3) {
                            System.out.print("Introduceti numerele de inmultit:");
                            a=sc.nextDouble();
                            b=sc.nextDouble();
                            rez=Ob.inmultire(a,b);ok=0;
                        }
                        if (comanda==4) {
                            System.out.print("Introduceti numerele de impartit:");
                            a=sc.nextDouble();
                            b=sc.nextDouble();
                            if (b==0) {System.out.println("Eroare");ok=1;}
                            else
                            {rez=Ob.impartire(a,b);ok=0;}
                        }
                        if (comanda==5) {
                            System.out.print("Introduceti numarul de inversat:");
                            a=sc.nextDouble();
                            if (a==0) {System.out.println("Eroare");ok=1;}
                            else
                            {rez=Ob.inversare(a);ok=0;}
                        }
                        if (comanda==6) {
                            System.out.print("Inroduceti numarul ptr care doriti sa faceti factorialul:");
                            a=sc.nextDouble();
                            if (a<0) {System.out.println("Eroare");ok=1;}
                            else
                            {rez=Ob.factorial(a);ok=0;}
                        }
                        if (comanda==7) {
                            System.out.print("Introduceti exponentul:");
                            a=sc.nextDouble();
                            System.out.print("Introduceti puterea:");
                            b=sc.nextDouble();
                            rez=Ob.putere(a,b);ok=0;
                        }
                        if (comanda==8) {
                            System.out.print("Introduceti numarul pentru care doriti sa calculati radical:");
                            a=sc.nextDouble();
                            if (a<0) {System.out.println("Eroare");ok=1;}
                            else
                            {rez=Ob.radacina(a);ok=0;}
                        }  
                        if (comanda==9) {
                            if (ok==1) System.out.println("Eroare");
                            else
                            {mem=Ob.memrezcurent(rez);ok=0;}
                        }
                        if (comanda==10)
                            mem=Ob.memoriezero();
                        if (comanda==11) {
                            if (ok==1) System.out.println("Eroare");
                            else                        
                            mem=Ob.adunamemorie(mem+rez);
                        }
                        if (comanda==12) {
                            if (ok==1) System.out.println("Eroare");
                            else                        
                            mem=Ob.scadememorie(mem-rez);
                        }
                        if (comanda==13) {
                            rez=Ob.memtorez(mem);
                            if (ok==1) ok=0;
                        }
                        if (comanda==14)
                            System.out.println("Valoarea memoriei este " +mem);
                        if (comanda==15) 
                            System.exit(0);
                        if (((comanda>0 &&comanda<9) ||comanda==13) &&ok==0)
                        System.out.println("Rezultatul curent este "+rez);
                }    
    }
}

