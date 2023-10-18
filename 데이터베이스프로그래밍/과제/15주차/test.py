import mysql.connector

mydb = mysql.connector.connect(
    host = "localhost",
    user = "root",
    password = "1234",
    database = "mydatabase"
)

mycursor = mydb.cursor()

mycursor.execute("CREATE TABLE customers \
                (id int primary key, \
                name varchar(255), \
                address varchar(255));")

mycursor.execute("CREATE TABLE products(\
                id char(10) primary key, \
                name char(25) not null,\
                c_id int, foreign key(c_id) references customers(id));")