import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;


public class CautaServlet extends HttpServlet {

     private Statement statement;  
     private Connection link; 
     static ResultSet results;
     
     private String URL = "jdbc:mysql://localhost:3306/agendatelefon?zeroDateTimeBehavior=convertToNull"; 
     public void init() throws ServletException   {   
         super.init();
     try       
     {   
      Class.forName("com.mysql.jdbc.Driver");
      link = DriverManager.getConnection(URL,"root","edenpass210595"); 
      System.out.println("M-am conectat");
     }    
      catch(ClassNotFoundException cnfe)
      {
          System.out.println("Driverul nu a putut fi incarcat!");
          System.exit(1);
      }
     catch (SQLException ex)     
     {
     System.out.println("Conectarea la baza de date a esuat!");
     ex.printStackTrace();      
     System.exit(1);          
     }      
    } 
     
     public void doGet(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException {           
            try {
            response.setContentType("text/HTML");
             PrintWriter out = response.getWriter();
             out.println("<HTML>");
             out.println("<HEAD>");
             out.println("<TITLE>Cautare contact</TITLE>");
             out.println("<style> h2{ color:red; margin-left:4em; } h1 {color:blue;}  </style>");
             out.println("</HEAD>");
             out.println("<BODY>");   out.println("<BR><BR>");
             String nume = request.getParameter("Nume");
             String prenume = request.getParameter("Prenume");
             
              if (nume.length()==0 || prenume.length()==0) 
                 out.println("<CENTER><H1> Va rugam completati toate campurile obligatorii </H1></CENTER>");
               
               else {   
                    statement = link.createStatement();
                    String select = "SELECT * FROM contacte";
                    results = statement.executeQuery(select);
                    System.out.println();
                    int ok=0;
                    
                    while (results.next())
                    {
                        if (results.getString(1).equals(nume) && results.getString(2).equals(prenume)) {
                          out.println("<CENTER><H1> Informatii despre " + nume +" " + prenume +" </H1></CENTER><br>");
                          out.println("<H2> Mobil: " + results.getString(3) + "</H2>");
                          out.println("<H2> Fix: " + results.getString(4) + "</H2>");
                          out.println("<H2> E-mail: " + results.getString(5) + "</H2>");
                          out.println("<H2> Adresa: " + results.getString(6) + "</H2>");
                          out.println("<H2> Oras: " + results.getString(7) + "</H2>");
                          out.println("<H2> Judet: " + results.getString(8) + "</H2>");
                          out.println("<H2> Cod Postal: " + results.getString(9) + "</H2>");
                         ok=1;break;
                        }
                    }
                    if (ok==0) 
                         out.println("<CENTER><H1> Contactul " + nume +" " + prenume +" nu exista in agenda </H1></CENTER><br>");
                    
                     out.println("</BODY>");
                     out.println("</HTML>");
                     out.flush();
                }    
            }   
                catch (SQLException ex) {
                    Logger.getLogger(CautaServlet.class.getName()).log(Level.SEVERE, null, ex);
                }
                        
     }
}
