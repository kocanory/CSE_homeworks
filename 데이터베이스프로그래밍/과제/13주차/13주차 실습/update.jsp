<%@ page contentType="text/html; charset=utf-8" pageEncoding="utf-8" %>
<%@ page import="java.sql.*, studentBean.*"  %>
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
%>
	<jsp:useBean id="studentMgr" class="studentBean.StudentMgr" />
<%
	Student stduent = studentMgr.getStudentInfo(session_id);
	String s_name = stduent.getName();
	String s_addr = student.getAddress();
	String s_pwd = student.getPwd();	
	String s_college = stduent.getCollege();
	String s_major = stduent.getMajor();
%>

<form method="post" action="update_verify.jsp">
  <input type="hidden" name="s_id" size="30" value="<%= session_id %>">
  <table width="75%" align="center" border>
     <tr><th>이름</th>
         <td><input type="text" name="s_name" size="50" value="<%= s_name %>"> </td>
     </tr>
	 <tr><th>주소</th>
         <td><input type="text" name="s_addr" size="50" value="<%= s_addr %>"> </td>
     </tr>
     <tr><th>패스워드</th>
         <td><input type="password" name="s_pwd" size="20"  value="<%= s_pwd %>"></td>
     </tr>
	 <tr><th>학부</th>
         <td><input type="text" name="s_college" size="50" value="<%= s_college %>"> </td>
     </tr>
	 <tr><th>전공</th>
         <td><input type="text" name="s_major" size="50" value="<%= s_major %>"> </td>
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
