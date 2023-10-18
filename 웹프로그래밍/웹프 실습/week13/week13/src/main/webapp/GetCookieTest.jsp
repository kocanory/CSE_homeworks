<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<% Cookie[] cookies = request.getCookies(); %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Q1</title>
</head>
<body>
	<b>쿠키 읽어 오는 예제 </b>
	<%
	String id = (String)session.getAttribute("id");
	String s = getCookieValue(cookies, id);
	if(s != null)
	{
		out.println("쿠키가 설정되어 있습니다.<br>");
		for(int i = cookies.length - 1;i >=0 ;i--)
		{
			out.println("Name : " + cookies[i].getName() + "<br>");
			out.println("Value : " + cookies[i].getValue() + "<br>");
			out.println("Domain : " + cookies[i].getDomain() + "<br>");
			out.println("MaxAge : " + cookies[i].getMaxAge() + "<br>");
			out.println("Path : " + cookies[i].getPath() + "<br>");
			out.println("Secure : " + cookies[i].getSecure() + "<br>");
			out.println("Comment : " + cookies[i].getComment() + "<br>");
			out.println("Version : " + cookies[i].getVersion() + "<br><br>");
		}
		
		out.println("<br><a href = 'SetCookieTest.html'>쿠키 설정<a>");
	}
	else
	{
		out.println("쿠키를 설정해야 합니다.<br>");
		out.println("<br><a href = 'SetCookieTest.html'>쿠키 설정<a>");
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