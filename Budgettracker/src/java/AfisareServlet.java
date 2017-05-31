import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class AfisareServlet extends HttpServlet {
    
     private Statement statement;  
     private Connection link; 
     static ResultSet results;
     
     private String URL = "jdbc:mysql://localhost:3306/bugetpersonal?zeroDateTimeBehavior=convertToNull"; 
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
             out.println("<TITLE>Afisare suma actuala</TITLE>");
             out.println("<style> h2{ color:red; margin-left:4em; } h1 {color:blue;}  </style>");
             out.println("</HEAD>");
             out.println("<BODY>");   out.println("<BR><BR>");
            
                    float suma=0;
                    
                    statement = link.createStatement();
                    String select = "SELECT * FROM sumeadaugate";
                    results = statement.executeQuery(select);
                    
                     while (results.next())
                    {
                        suma=suma+results.getFloat(1);
                    }
                     
                    statement = link.createStatement();
                    String select2 = "SELECT * FROM sumeretrase";
                    results = statement.executeQuery(select2);
                    
                     while (results.next())
                    {
                        suma=suma-results.getFloat(1);
                    } 
                     
                    out.println("<CENTER><H1> Suma actuala din cont este de " + suma +" lei </H1></CENTER>"); 
                     
                    
                     out.println("</BODY>");
                     out.println("</HTML>");
                     out.flush();
            } 
                 catch (SQLException ex) {
                    Logger.getLogger(RetrageServlet.class.getName()).log(Level.SEVERE, null, ex);
                } 
      }          
    
}