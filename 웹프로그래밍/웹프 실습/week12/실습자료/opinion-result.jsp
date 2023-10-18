<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*"%>
<%@ page import="java.text.*"%>
<% request.setCharacterEncoding("euc-kr"); %>

<html>
   <head>
   <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title> JSP를 이용한 여론조사 </title></head>
   <body>
   <%
      int choice_id,i;
      int opinion[]={0,0,0,0};
      float total, rate[]={0,0,0,0};
      String choice=""; 
      String fruit[]={"사과","포도","딸기","메론"};
      String opinion_id = request.getParameter("opinion_id");

      Connection conn=null;
      Statement stmt=null;
      String sql=null;
      ResultSet rs=null;

      try { 
	Class.forName("com.mysql.jdbc.Driver");
	String jdbcurl = "jdbc:mysql://localhost:3306/wptest?serverTimezone=UTC";
	conn = DriverManager.getConnection(jdbcurl, "root", "0000");
          	stmt = conn.createStatement(ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
         	sql = "select * from opinion_tbl";
	 rs = stmt.executeQuery(sql);
      } 
      catch(Exception e) {
        out.println("DB 연동 오류입니다. : " + e.getMessage() );
      }

      if(!rs.next()) {
         for(i=0;i<4;i++) {
            String sql1 = "insert into opinion_tbl values (" + i + ",'"+ fruit[i] + "',0)";
            try{
               stmt.executeUpdate(sql1);
            }catch(Exception e) {
               out.println("DB 연동 오류입니다. : " + e.getMessage() );
            }
         }
      }
else {
rs.previous();
i=0;
while(rs.next()) {
	opinion[i] = Integer.parseInt(rs.getString("sum"));
System.out.println(opinion[0]);
i++;
	}
}
      if(opinion_id != null) {
         String sql2 = "update opinion_tbl set sum = sum + 1 where id = " + opinion_id;
         try{
            stmt.executeUpdate(sql2);
         }catch(Exception e) {
            out.println("DB 연동 오류입니다. : " + e.getMessage() );
         }
      }

         choice_id = Integer.parseInt(opinion_id);
	opinion[choice_id] += 1;
	
	total = opinion[0] + opinion[1] +opinion[2] +opinion[3];
	
	for(i=0;i<4;i++) 
	   rate[i] = (opinion[i]/ total)*100;
%>

      
<center>
   <h2> 여론조사 결과 </h2>
   <table border=0 width= 500>
      <tr>
        <td  bgcolor = "yellow" width= "30%"> <b> 사과 : <%=Math.round(rate[0])%>%</b> </td>
        <td><img src= " image/blue_pole.gif" width=<%=rate[0]%>% height="25"></td>
      </tr>
	        <tr>
        <td  bgcolor = "orange" > <b> 포도 : <%=Math.round(rate[1])%>%</b> </td>
        <td><img src= " image/blue_pole.gif" width=<%=rate[1]%>% height="25"></td>
      </tr>
	        <tr>
        <td  bgcolor = "salmon" > <b> 딸기 : <%=Math.round(rate[2])%>%</b> </td>
        <td><img src= " image/white_pole.gif" width=<%=rate[2]%>% height="25"></td>
      </tr>
	        <tr>
        <td  bgcolor = "red" > <b> 메론		: <%=Math.round(rate[3])%>%</b> </td>
        <td><img src= " image/white_pole.gif" width=<%=rate[3]%>% height="25"></td>
      </tr>
      
     </table><br><br>

     당신은 <font color=blue><b><%=fruit[choice_id]%></b></font>를(을) 선택하였습니다.<br>
     총 <b><font color="red"><%=Math.round(total)%></font><b>명이 참여하였습니다.<p>
     <a href="opinion.html"> 처음으로 </a>
     </center>
  </body>
</html>

