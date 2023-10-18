<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<%@ page import="java.sql.*"%>
<%
	String jdbcurl = "jdbc:mysql://localhost:3306/wptest?serverTimezone=UTC";

	Boolean connect = false;

	try{
		Class.forName("com.mysql.jdbc.Driver");
		Connection conn = DriverManager.getConnection(jdbcurl, "root", "0000");
		connect = true;	
	}
	catch(Exception e){
		connect = false;
		out.print(e);
	}
%>
<html>
	<head></head>
	<body>
		<% if(connect==true){out.print("연결되었습니다.");}
			
	                       else{out.print("연결에 실패하였습니다");} %>
	</body>
</html>
