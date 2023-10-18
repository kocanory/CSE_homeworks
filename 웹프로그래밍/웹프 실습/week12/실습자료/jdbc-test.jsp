<%@ page language="java" contentType="text/html; charset=utf-8" pageEncoding="utf-8"%>
<%@ page import="java.sql.*"%>
<html>
<body>
<center>
<h1> 주소록 </h1>
<table border="1" align="center">
	<tr>
           <td align="center">  Student_ID  </td>
	   <td align="center">  Name  </td>
	   <td align="center">  E-mail  </td>
	   <td align="center">  Address  </td>
	</tr>

   <%
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;

        try { 
              Class.forName("com.mysql.jdbc.Driver");
              String jdbcurl = "jdbc:mysql://localhost:3306/wptest?serverTimezone=UTC";
              conn = DriverManager.getConnection(jdbcurl, "root", "0000");
              stmt = conn.createStatement();
              String sql = "select * from address_tbl";
              rs = stmt.executeQuery(sql);
        } 
        catch(Exception e) {
              out.println("DB 연동 오류입니다. : " + e.getMessage());
        }

        while(rs.next()) {
   %>
	<tr>
	    <td align="center"><%= rs.getString("student_id") %></td>
	    <td align="center"><%= rs.getString("name") %></td>
	    <td align="center"><%= rs.getString("e_mail") %></td>
	    <td align="center"><%= rs.getString("address") %></td>
	</tr>
   <%
       }
   %>
</table>
   <%
       stmt.close();
       conn.close();
   %>
</center>
</body>
</html>
