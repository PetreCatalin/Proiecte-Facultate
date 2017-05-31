import java.rmi.*;

public interface Hello extends Remote {
    public Double adunare (double a,double b) throws RemoteException;
    public Double scadere(double a,double b) throws RemoteException;
    public Double inmultire (double a,double b) throws RemoteException;
    public Double impartire (double a,double b) throws RemoteException;
    public Double inversare(double a) throws RemoteException;
    public Long factorial(double a) throws RemoteException;
    public Double putere (double a,double b) throws RemoteException;
    public Double radacina (double a) throws RemoteException;
    public Double memrezcurent (double a) throws RemoteException;
    public Integer memoriezero () throws RemoteException;
    public Double adunamemorie (double a) throws RemoteException;
    public Double scadememorie (double a) throws RemoteException;
    public Double memtorez (double a) throws RemoteException;
}
