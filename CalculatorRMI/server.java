import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class server {
    public server(){};
    public static void main(String[] args) throws Exception {
           /* HelloImpl ob=new HelloImpl();  //Create a reference to an implementation object
            String HOST="localhost:1234";
            String rmiObjectName="rmi://"+HOST+"/Hello";
            Naming.rebind(rmiObjectName,ob); */       //'Bind' the object reference to the name
            Registry reg = LocateRegistry.createRegistry(1234);
		reg.bind("Hello", new HelloImpl());
            System.out.println("Serverul a pornit"); 
    }
}
