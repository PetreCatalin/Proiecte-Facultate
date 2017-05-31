import java.rmi.*;
import java.rmi.server.*;

public class HelloImpl extends UnicastRemoteObject implements Hello {
    
    public HelloImpl() throws RemoteException {
    }
    
    @Override
    public Double adunare (double a,double b) throws RemoteException{
        return a+b;
    }
    
    @Override
    public Double scadere (double a,double b) throws RemoteException {
        return a-b;
    }
    
    @Override
    public Double inmultire (double a,double b) throws RemoteException{
        return a*b;
    }
    
    @Override
    public Double impartire (double a,double b) throws RemoteException{
        return (float) a/b;
    }
    
    @Override
    public Double inversare(double a) throws RemoteException{
        return (float) 1/a;
    }
    
    @Override
    public Long factorial(double a) throws RemoteException{
        long nr=(int) Math.floor(a);
        long rez=1;
        for (int i=1;i<=nr;++i)
            rez*=i;
        return rez;
    }
    
    @Override
    public Double putere (double a,double b) throws RemoteException{
        return Math.pow(a,b);
    }
    
    @Override
    public Double radacina (double a) throws RemoteException{
        return Math.sqrt(a);
    }
    
    @Override
    public Double memrezcurent (double a) throws RemoteException{
        return a;
    }
    
    @Override
    public Integer memoriezero () throws RemoteException {
        return 0;
    }
    
    @Override
    public Double adunamemorie (double a) throws RemoteException
    {
        return a;
    }
    
    @Override
    public Double scadememorie (double a) throws RemoteException
    {
        return a;
    }
    
    @Override
    public Double memtorez (double a) throws RemoteException{
        return a;
    }
}
