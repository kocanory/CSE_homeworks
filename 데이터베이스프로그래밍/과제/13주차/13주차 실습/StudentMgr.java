package studentBean;

import java.sql.*;
import java.util.*;
import javax.sql.*;
import oracle.jdbc.driver.*;
import oracle.jdbc.pool.*;
import studentBean.*;

public class StudentMgr {

	private OracleConnectionPoolDataSource ocpds = null;
	private PooledConnection pool = null;

	public StudentMgr() {
		try {

			ocpds = new OracleConnectionPoolDataSource();

			ocpds.setURL("jdbc:oracle:thin:@210.94.199.20:1521:dblab");
			ocpds.setUser("ST2018112007"); 
			ocpds.setPassword("lee98031"); 

			pool = ocpds.getPooledConnection();
		} catch (Exception e) {
			System.out.println("Error : Connection Failed");
		}
	}

	public Student getStudentInfo(String s_id) {
		Connection conn = null;
		PreparedStatement pstmt = null;
		CallableStatement cstmt1 = null;
		CallableStatement cstmt2 = null;
		ResultSet rs = null;
		Student student = new Student();

		try {
			conn = pool.getConnection();

			String mySQL = "select s_name, s_addr, s_pwd, s_college, s_major from student where s_id=?";
			pstmt = conn.prepareStatement(mySQL);
			pstmt.setString(1, s_id);
			rs = pstmt.executeQuery();

			while (rs.next()) {
				student.setName(rs.getString("s_name"));
				student.setAddress(rs.getString("s_addr"));
				student.setPwd(rs.getString("s_pwd"));
				student.setCollege(rs.getString("s_college"));
				student.setMajor(rs.getString("s_major"));
			}
			cstmt1.close();
			cstmt2.close();
			pstmt.close();
			conn.close();

		} catch (Exception ex) {
			System.out.println("Exception" + ex);
		}
		return student;
	}

	public void updateStudentInfo(String s_id, String s_name, String s_addr, String s_pwd, String s_college, String s_major) {
		Connection conn = null;
		ResultSet rs = null;
		Statement stmt = null;

		try {
			conn = pool.getConnection();
			stmt = conn.createStatement();
			String mySQL = "update student ";
			mySQL = mySQL + " set s_addr ='" + s_addr + "' , " ;	
			mySQL = mySQL + " s_pwd ='" + s_pwd + "' , ";
			mySQL = mySQL + " s_name ='" + s_name + "' , ";
			mySQL = mySQL + " s_college ='" + s_college + "' , ";
			mySQL = mySQL + " s_major ='" + s_major + "' where s_id='" + s_id + "' ";
			stmt.executeQuery(mySQL);  
			stmt.close();
			conn.close();
		} catch (Exception ex) {
			System.out.println("Exception" + ex);
		}
	}
}