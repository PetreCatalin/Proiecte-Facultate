
import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;
import java.util.logging.Level;
import java.util.logging.Logger;

public class PersonalServlet extends HttpServlet {
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
  //  try {      
    response.setContentType("text/HTML");
             PrintWriter out = response.getWriter();
             out.println("<HTML>");
             out.println("<HEAD>");
             out.println("<TITLE>Adaugare contact</TITLE>");
             out.println("<style> h2{ color:red; margin-left:4em; } h1 {color:blue;}  </style>");
             out.println("</HEAD>");
             out.println("<BODY>");   out.println("<BR><BR>");
             String nume = request.getParameter("Nume");
             String prenume = request.getParameter("Prenume");
             String telmobil = request.getParameter("Mobil");
             String telfix = request.getParameter("Fix");
             String email = request.getParameter("Email");
             String adresa = request.getParameter("Adresa");
             String oras = request.getParameter("Oras");
             String judet = request.getParameter("Judet");
             String cod = request.getParameter("Codp");
             
             if (nume.length()==0 || prenume.length()==0 || telmobil.length()==0 || email.length()==0 ) 
                 out.println("<CENTER><H1> Va rugam completati toate campurile obligatorii </H1></CENTER>");
             else {       
             String insertion = "insert into contacte VALUES('" + nume + "','" + prenume + "','" + telmobil + "','" + telfix
                     + "','" + email + "','" + adresa +  "','" + oras + "','" + judet
                     + "','" + cod + "')";
             
             try
             {
             statement = link.createStatement();
             statement.executeUpdate(insertion);
             out.println("<CENTER><H1> Contactul " + nume+ " " + prenume + " a fost adaugat cu succes </H1></CENTER>");
             statement.close();
             }
             catch (SQLException sqlEx)  {
             out.println("<BR><CENTER><H1>  Nu s-a putut realiza inserarea </H1></CENTER>");
             } 
             }   
          /*   String select = "SELECT * FROM contacte";
             
             results = statement.executeQuery(select);
             
             while (results.next())
             {   
                 System.out.println(results.getString(1));
                 System.out.println(results.getString(4));
             } */
             
             out.println("</BODY>");
             out.println("</HTML>");
             out.flush();   
         } //catch (SQLException ex) {
           //  Logger.getLogger(PersonalServlet.class.getName()).log(Level.SEVERE, null, ex);
         //}
}
//}