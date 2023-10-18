<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Q2</title>
</head>
<body>
<h2>Session URL Rewriting Test</h2>
<% 
String id = request.getParameter("id");

if(id.equals(""))
{
	response.sendRedirect("urlSession.html");
}

session.setAttribute("id", id);

%>
세션ID : <%= session.getId() %><br>
ID : <%= request.getParameter("id") %>
<hr>
<a href = <%= response.encodeURL("urlSessionResult.jsp") %>>Test1</a><br>
<a href = "urlSessionResult.jsp">Test2</a>
</body>
</html>