개발환경 C, 파이썬

 

pc플랫폼
gui (gtk) C - 효준
TCP/IP(gui -> 클라이언트, 라즈베리 -> 서버) - 원재
라즈베리 (nfc, 인체동작감지센서, 온도센서, 카메라) -도현 형욱

+
웹, 어플
 

====================================================================================================================
라즈베리
mySQL - 정민
테이블 
1.차량 정보[차량번호(int),운전자(varchar),담당교사(varchar),시동on/off(bool)]
Car Table
	c_number int PK
	c_driver vchar
	c_teacher vchar
	c_state bool default=false
시동 on/off는 변수처럼 계속 update해주자(on=true,off=false)

2.회원 정보[아이디(varchar),비번(varchar),이름(varchar),전화번호(int),권한(int)]
Member Table
	m_id vchar PK
	m_pw vchar not null
	m_name vchar
	m_phone int
	m_position int default 1
권한 0 = 선생 , 1=학부모

2. 원생 정보[키(int), 원생이름(varchar), 나이(int), 학부모이름(varchar), 학부모전화(int), 담당교사(varchar)]
Student Table
	s_key int PK
	s_name vchar not null
	s_age int
	s_parent vchar
	s_phone int
	s_teacher vchar not null

3. 타고내리는거 로그[차량번호(int),운전자(varchar),담당교사(varchar),키(int), 원생이름(varchar), 나이(int), 탑승상태(bool), 날짜시간(time)] 
Log Table
	l_number int not null
	l_driver vchar
	l_teacher vchar 
	l_key int 
	l_name vchar
	l_age int
	l_state bool not null
	l_time datetime not null
상태는 탑승(1),하차(0)

4. 운행상태[차량번호(int),키(int),원생이름(varchar)탑승상태(bool),날짜시간(datetime)]
Drive Table
	d_number int
	d_key int
	d_name vchar
	d_state bool not null
	d_time datetime not null
상태는 탑승(1),하차(0)




====================================================================================================================
DB다운 및 컴파일
sudo apt-get install libmysqlclient-dev
gcc -o main main.c dbconn.c dbconn.h -I/usr/include/mysql -lmysqlclient

DB랑Table만들기
create database school;

create table Car( c_number INT NOT NULL, c_driver VARCHAR(20), c_teacher VARCHAR(20), c_state BOOL default FALSE, PRIMARY KEY (c_number) );


create table Member(
    -> m_id varchar(30) NOT NULL,
    -> m_pw varchar(30) NOT NULL,
    -> m_name varchar(20),
    -> m_phone int,
    -> m_position int default 1,
    -> PRIMARY KEY (m_id)
    -> );


create table Student(
    -> s_key int NOT NULL,
    -> s_name varchar(20) NOT NULL,
    -> s_age INT,
    -> s_parent varchar(20),
    -> s_phone int,
    -> s_teacher VARCHAR(20) NOT NULL,
    -> PRIMARY KEY (s_key)
    -> );



create table Log(
    -> l_number int not null,
    -> l_driver varchar(20),
    -> l_techer varchar(20),
    -> l_key int,
    -> l_name varchar(20),
    -> l_age int,
    -> l_state BOOL not null,
    -> l_time datetime not null
    -> );


유저 만들고 권한설정 root(admin) 유저명 : user 비번 : test
create user 'user'@'%' identified by 'test'

grant all privileges on school.* to 'user'@'%';



mysql외부접속설정
sudo /etc/mysql/mysql.conf.d/mysqld.cnf에서 bind-address=127.0.0.1 #으로 주석처리
mysql한글설정
sudo /etc/mysql/mysql.conf.d/mysqld.cnf에서 [mysqld]부분에 
default-character-set=utf8
default-collation=utf8_general_ci 추가하고
DB에서 alter table TLB_NAME convert to charset utf8;하면 한글설정완료
	(이거?)alter database school default character set utf8








gtk다운&컴파일
sudo apt-get install gtk2.0
gcc -o main window.c `pkg-config --cflags --libs gtk+-2.0`


전체 컴파일
gcc -o main window.c dbconn.c dbconn.h `pkg-config --cflags --libs gtk+-2.0` -I/usr/include/mysql -lmysqlclient
