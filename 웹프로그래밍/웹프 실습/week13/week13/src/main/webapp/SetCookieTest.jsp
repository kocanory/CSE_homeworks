<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Q2</title>
</head>
<body>
	<%
	Cookie[] cookies = request.getCookies();

	String cookie = getCookieValue(cookies, request.getParameter("id"));
	String id = request.getParameter("id");
	String password = request.getParameter("password");
	session.setAttribute("id", id);
	
	if(cookie == null)
	{
		out.println("쿠키를 설정합니다.<br>");
		response.addCookie(new Cookie(id, password));
%>
		<a href = "GetCookieTest.jsp">쿠키 가져오기</a>
<%
	}
	else
	{
		out.println("쿠키가 설정되어 있습니다. <br>기존 쿠키를 삭제합니다.<br>");
		Cookie c = new Cookie(id, "");
		c.setMaxAge(0);
		response.addCookie(c);
%>
		<a href = "GetCookieTest.jsp">쿠키 가져오기</a>
<%
	}	
%>
<%!
	private String getCookieValue(Cookie[] cookies, String name)
	{
		if(cookies == null)
			return null;
		for(Cookie c : cookies)
		{
			if(c.getName().equals(name))
				return c.getValue();
		}
		return null;
	}
%>
</body>
</html>