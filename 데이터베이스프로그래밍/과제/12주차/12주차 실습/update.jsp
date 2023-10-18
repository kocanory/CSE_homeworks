<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<%@ page import="java.sql.*"  %>
<!DOCTYPE html>
<html>
<head><title>수강신청 사용자 정보 수정</title></head>
<body>
<%@ include file="top.jsp" %>
<%
	if (session_id==null) response.sendRedirect("login.jsp");

	Connection myConn = null;     
	Statement stmt = null;	
	ResultSet myResultSet = null; 
	String mySQL = "";

	String dburl  = "jdbc:oracle:thin:@210.94.199.20:1521:dblab";
	String user = "ST2018112007"; // 본인 아이디(ex.ST0000000000)
	String passwd = "lee98031"; // 본인 패스워드(ex.ST0000000000)
	String dbdriver = "oracle.jdbc.driver.OracleDriver";    

	try {
  	    Class.forName(dbdriver);
	    myConn =  DriverManager.getConnection (dburl, user, passwd);
	    stmt = myConn.createStatement();	
    } catch(SQLException ex) {
	    System.err.println("SQLException: " + ex.getMessage());
	}
    mySQL = "select s_addr, s_pwd from student where s_id='" + session_id + "'" ;
	myResultSet = stmt.executeQuery(mySQL);
	if (myResultSet.next()) {
		String s_addr = myResultSet.getString("s_addr");
		String s_pwd = myResultSet.getString("s_pwd");			
%>

<form method="post" action="update_verify.jsp">
  <input type="hidden" name="s_id" size="30" value="<%= session_id %>">
  <table width="75%" align="center" border>
     <tr><th>주소</th>
         <td><input type="text" name="s_addr" size="50" value="<%= s_addr %>"> </td>
     </tr>
     <tr><th>패스워드</th>
         <td><input type="password" name="s_pwd" size="20"  value="<%= s_pwd %>"></td>
     </tr>
			   
<%
	}	
	stmt.close();  
	myConn.close();
%>
<tr>
	<td colspan="2" align="center">
	<input type="submit" value="수정">
	</td> 
</tr>
</table></form></body></html>
