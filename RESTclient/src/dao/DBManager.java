package dao;
import java.sql.*;
import java.text.SimpleDateFormat;
import java.util.Calendar;

public class DBManager {
	private Connection c;
	
	public DBManager() {
	}
	
	public void getConnection() {
		Connection c = null;
	    
	    try {
	       Class.forName("org.sqlite.JDBC");
	       c = DriverManager.getConnection("jdbc:sqlite:test.db");
	    } catch ( Exception e ) {
	       System.err.println( e.getClass().getName() + ": " + e.getMessage() );
	       System.exit(0);
	    }
	    System.out.println("Opened database successfully");
	    this.c = c;
	}
	
	public void createTable() {
		Statement stmt = null;
		Calendar cal = Calendar.getInstance();
	    SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
	      
	      try {
	         Class.forName("org.sqlite.JDBC");
	         c = DriverManager.getConnection("jdbc:sqlite:test.db");
	         System.out.println("[" +sdf.format(cal.getTime()) + "]" + "CREATE TABLE: Opened database successfully");

	         stmt = c.createStatement();
	         String sql = "DROP TABLE IF EXISTS NOISEVALUES;"
	         				+ "CREATE TABLE NOISEVALUES " +
	                        "(ID INTEGER PRIMARY KEY AUTOINCREMENT," +
	                        " VALUE           TEXT    NOT NULL,"
	                        + "TIME TEXT NOT NULL)";
	         stmt.executeUpdate(sql);
	         stmt.close();
	         c.close();
	      } catch ( Exception e ) {
	         System.err.println( e.getClass().getName() + ": " + e.getMessage() );
	         System.exit(0);
	      }
	      System.out.println("[" +sdf.format(cal.getTime()) + "]" + "CREATE TABLE: Table created successfully");
	}
	
	public void insertValue(String currentValue) {
		Statement stmt = null;
		Calendar cal = Calendar.getInstance();
	    SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");  
	      try {
	         Class.forName("org.sqlite.JDBC");
	         c = DriverManager.getConnection("jdbc:sqlite:test.db");
	         c.setAutoCommit(false);
	         System.out.println("[" +sdf.format(cal.getTime()) + "]" + "INSERT: Opened database successfully");

	         stmt = c.createStatement();
	         String sql = "INSERT INTO NOISEVALUES (VALUE, TIME) " +
	                        "VALUES ('" + currentValue +"', '" + sdf.format(cal.getTime()) + "');"; 
	         stmt.executeUpdate(sql);
	         stmt.close();
	         c.commit();
	         c.close();
	      } catch ( Exception e ) {
	         System.err.println( e.getClass().getName() + ": " + e.getMessage() );
	         System.exit(0);
	      }
	      System.out.println("[" +sdf.format(cal.getTime()) + "]" + "INSERT: Records created successfully");
	}
	
	public void readValues() {
		 Statement stmt = null;
		 Calendar cal = Calendar.getInstance();
		 SimpleDateFormat sdf = new SimpleDateFormat("HH:mm:ss");
		   try {
		      Class.forName("org.sqlite.JDBC");
		      c = DriverManager.getConnection("jdbc:sqlite:test.db");
		      c.setAutoCommit(false);
		      System.out.println("[" +sdf.format(cal.getTime()) + "]" + "SELECT: Opened database successfully");

		      stmt = c.createStatement();
		      ResultSet rs = stmt.executeQuery( "SELECT * FROM NOISEVALUES;" );
		      
		      while ( rs.next() ) {
		         int id = rs.getInt("id");
		         String  name = rs.getString("value");
		         String time = rs.getString("time");
		         
		         System.out.println( "ID = " + id );
		         System.out.println( "VALUE = " + name );
		         System.out.println( "TIME = " + time );
		      }
		      rs.close();
		      stmt.close();
		      c.close();
		   } catch ( Exception e ) {
		      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
		      System.exit(0);
		   }
		   System.out.println("[" +sdf.format(cal.getTime()) + "]" + "SELECT: Operation done successfully");
	}
}
