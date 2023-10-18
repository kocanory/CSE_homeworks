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
세션ID : <%= session.getId() %><br>
ID : <%= session.getAttribute("id") %>
</body>
</html>