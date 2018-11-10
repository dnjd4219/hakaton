#include "dbconn.h"



static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit ();
}

void inserttextbox(char *story){
	gtk_text_buffer_insert(buffer[0],&end[0],story,-1);
}
void inserttextbox2(char *story){
	gtk_text_buffer_insert(buffer[1],&end[1],story,-1);
}
void inserttextbox3(char *story){
	gtk_text_buffer_insert(buffer[2],&end[2],story,-1);
}
void setwindow(GtkWidget* window,char *name,int garo,int sero)
{
    gtk_window_set_title(GTK_WINDOW(window),name);
    gtk_window_set_default_size (GTK_WINDOW (window), garo, sero);
    g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

}
void noting(){
	printf("아무것도아님");
}
void loginmenu(){// 로그인 메뉴
	GtkWidget *table,*label[3],*btn[7];
	gchar *id,*pw;
	
  	//창 생성
  	window[0] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	setwindow(window[0],"원생관리", 100, 120);


   	table = gtk_table_new (6, 5, TRUE);
   	gtk_container_add (GTK_CONTAINER (window[0]), table);


  	//라벨 생성 
  	label[0] = gtk_label_new ("ID :" );
  	gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
  	gtk_table_attach_defaults (GTK_TABLE (table), label[0], 1, 2, 1, 2);


  	//텍스트 박스 생성
  	entry[0] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), entry[0], 2, 4, 1, 2);

	//라벨생성 
  	label[1] = gtk_label_new ("pw :" );
  	gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
  	gtk_table_attach_defaults (GTK_TABLE (table), label[1], 1, 2, 2, 3);
  

  	//텍스트 박스 생성 
  	entry[1] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), entry[1], 2, 4, 2, 3);
	
	//버튼생성 
	btn[0]=gtk_button_new_with_label("로그인");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[0], 1, 2, 4, 5);
	gtk_signal_connect(GTK_OBJECT(btn[0]),"clicked",G_CALLBACK(login),NULL);

	btn[1]=gtk_button_new_with_label("나가기");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[1], 3, 4, 4, 5);
	gtk_signal_connect(GTK_OBJECT(btn[1]),"clicked",G_CALLBACK(destroy),NULL);

	
	gtk_widget_show_all(window[0]);
	g_signal_connect (window[0], "destroy", G_CALLBACK (destroy), NULL);
	gtk_main ();
}
void login(){
	const gchar *id,*pw;
	int levello;
	id=gtk_entry_get_text(GTK_ENTRY(entry[0]));
	pw=gtk_entry_get_text(GTK_ENTRY(entry[1]));
	strcpy(p_id,id);
	strcpy(p_pw,pw);
	levello=whatlevel(id,pw);
	if(levello==0){	
		printf("관리자로그인\n");
		gtk_widget_destroy(GTK_WIDGET(window[0]));
		adminmenu();
	}
	else if(levello==1){
		printf("부모님로그인\n");
		gtk_widget_destroy(GTK_WIDGET(window[0]));
		//strcpy(p_id,id);
		//strcpy(p_pw,pw);
		child_show();
		
	}
	else{printf("실패\n");}
	
}
void close_join(){
	gtk_widget_destroy(GTK_WIDGET(window[3]));
}
void close_parent(){
	gtk_widget_destroy(GTK_WIDGET(window[6]));
}
int whatlevel(const char*id,const char*pw){
	if((strcmp(id,"admin")==0)&&(strcmp(pw,"1234")==0)){
		return 0;
	}
	//Member테이블만들어서 아이디랑 비번가져오기
	else if((strcmp(id,GetMemberId(id))==0)&&(strcmp(pw,GetMemberPw(pw))==0)){
		return 1;
	}
	/*
	else if((strcmp(id,"asd")==0)&&(strcmp(pw,"1234")==0)){
		return 1;
	}
	*/
	else{
		return -1;
	}
}
void adminmenu(){//관리자메뉴
	GtkWidget *table,*btn[7];
	window[1] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	setwindow(window[1],"관리자메뉴",400,640);
	
	table = gtk_table_new (16, 5, TRUE);
   	gtk_container_add (GTK_CONTAINER (window[1]), table);
	
	btn[0]=gtk_button_new_with_label("차량조회");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[0], 1, 4, 1, 3);
	gtk_signal_connect(GTK_OBJECT(btn[0]),"clicked",G_CALLBACK(carmenu),NULL);
	btn[1]=gtk_button_new_with_label("원생등록");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[1], 1, 4, 4, 6);
	gtk_signal_connect(GTK_OBJECT(btn[1]),"clicked",G_CALLBACK(join_student),NULL);
	btn[3]=gtk_button_new_with_label("원생조회");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[3], 1, 4, 7, 9);
	gtk_signal_connect(GTK_OBJECT(btn[3]),"clicked",G_CALLBACK(search_student),NULL);
	btn[4]=gtk_button_new_with_label("부모님 등록");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[4], 1, 4, 10, 12);
	gtk_signal_connect(GTK_OBJECT(btn[4]),"clicked",G_CALLBACK(join_parent),NULL);

	btn[2]=gtk_button_new_with_label("카메라보기");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[2], 1, 4, 13, 15);
	gtk_signal_connect(GTK_OBJECT(btn[2]),"clicked",G_CALLBACK(cameraopen),NULL);

	gtk_widget_show_all(window[1]);
	gtk_main ();
}

void cameraopen(){
	system("firefox 117.16.19.184:5000");
}
void carmenu(){//차량메뉴
	char temp[50]="TempString";
	int sw=0;
	GtkWidget *table,*label[5];
	window[2] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	setwindow(window[2],"차량조회",450,600);//오른 아래
	
	table = gtk_table_new (20, 15, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window[2]), table);
	
 	textbox[0] = gtk_text_view_new();
	buffer[0] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textbox[0]));   
	
	gtk_text_buffer_get_end_iter(buffer[0],&end[0]);

	CarSearch();
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textbox[0]),FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbox[0]),FALSE);
	gtk_table_attach_defaults (GTK_TABLE (table), textbox[0], 1, 9, 1, 19);

	label[0] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[0]), "<span font='20'>운행상태</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[0], 11, 14, 1, 3);

	sw=DrivingState();
	label[1] = gtk_label_new ("");
    	if(sw) gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>운행중</span>");
	else gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>정차중</span>");
	gtk_table_attach_defaults (GTK_TABLE (table), label[1], 11, 14, 4, 6);
	
	label[2] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[2]), "<span font='20'>인솔교사</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[2], 11, 14, 7, 9);
	
	strcpy(temp,GetTeacherName());	
	label[3] = gtk_label_new (temp);
      	gtk_table_attach_defaults (GTK_TABLE (table), label[3], 11, 14, 10, 12);
	
	label[4] = gtk_label_new ("");
	gtk_label_set_markup(GTK_LABEL(label[4]), "<span font='10'>탑승현황</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[4], 1, 4, 0, 1);
	
	
	gtk_widget_show_all(window[2]);
	gtk_main ();
}
void join_student(){//원생등록
	GtkWidget *table,*btn[2],*label[6];
	window[3] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	setwindow(window[3],"원생등록",330,270);//오른 아래

	table = gtk_table_new (11, 9, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window[3]), table);

	label[0] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[0]), "<span font='20'>이름</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[0], 1, 4, 1, 2);

	student_info[0] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), student_info[0], 4, 8, 1, 2);
	
	label[1] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>나이</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[1], 1, 4, 2, 3);

	student_info[1] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), student_info[1], 4, 8, 2, 3);

	label[2] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[2]), "<span font='20'>학부모 이름</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[2], 1, 4, 3, 4);

	student_info[2] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), student_info[2], 4, 8, 3, 4);
	
	label[3] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[3]), "<span font='20'>학부모 전화</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[3], 1, 4, 4, 5);

	student_info[3] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), student_info[3], 4, 8, 4, 5);

	label[4] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[4]), "<span font='20'>담당 교사</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[4], 1, 4, 5, 6);

	student_info[4] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), student_info[4], 4, 8, 5, 6);

	label[5] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[5]), "<span font='20'>NFC카드</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[5], 1, 4, 6, 7);

	student_info[5] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), student_info[5], 4, 8, 6, 7);

	btn[0]=gtk_button_new_with_label("저장");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[0], 1, 4, 8, 10);
	gtk_signal_connect(GTK_OBJECT(btn[0]),"clicked",G_CALLBACK(sign_child),NULL);

	btn[1]=gtk_button_new_with_label("취소");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[1], 5, 8, 8, 10);
	gtk_signal_connect(GTK_OBJECT(btn[1]),"clicked",G_CALLBACK(close_join),NULL);

	gtk_widget_show_all(window[3]);
	gtk_main ();
}
void search_student(){//원생조회
	GtkWidget *table,*label,*btn;
	window[5] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	setwindow(window[5],"아이정보",350,150);//오른 아래
	table = gtk_table_new (3, 11, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window[5]), table);
	
	label = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label), "<span font='20'>이름:</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label, 1, 3, 1, 2);
	
	child = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), child, 3, 7, 1, 2);
	
	btn=gtk_button_new_with_label("검색");
	gtk_table_attach_defaults (GTK_TABLE (table), btn, 8, 10, 1, 2	);
	gtk_signal_connect(GTK_OBJECT(btn),"clicked",G_CALLBACK(search_child),NULL);

	gtk_widget_show_all(window[5]);
	gtk_main ();
}
void join_parent(){//부모님계정등록
	GtkWidget *table,*btn[2],*label[6];
	window[6] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	setwindow(window[6],"부모님계정등록",480,480);//오른 아래

	table = gtk_table_new (9, 9, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window[6]), table);

	label[0] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[0]), "<span font='20'>아이디</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[0], 1, 4, 1, 2);

	parent_info[0] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), parent_info[0], 4, 8, 1, 2);
	
	label[1] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>비밀번호</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[1], 1, 4, 2, 3);

	parent_info[1] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), parent_info[1], 4, 8, 2, 3);

	label[2] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[2]), "<span font='20'>학부모 이름</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[2], 1, 4, 3, 4);

	parent_info[2] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), parent_info[2], 4, 8, 3, 4);
	
	label[3] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[3]), "<span font='20'>학부모 전화</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[3], 1, 4, 4, 5);

	parent_info[3] = gtk_entry_new ();
  	gtk_table_attach_defaults (GTK_TABLE (table), parent_info[3], 4, 8, 4, 5);
	
	btn[0]=gtk_button_new_with_label("저장");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[0], 1, 4, 6, 8);
	gtk_signal_connect(GTK_OBJECT(btn[0]),"clicked",G_CALLBACK(sign_parent),NULL);

	btn[1]=gtk_button_new_with_label("취소");
	gtk_table_attach_defaults (GTK_TABLE (table), btn[1], 5, 8, 6, 8);
	gtk_signal_connect(GTK_OBJECT(btn[1]),"clicked",G_CALLBACK(close_parent),NULL);

	gtk_widget_show_all(window[6]);
	gtk_main ();
}
void child_show(){
	int sw=-1;
	GtkWidget *table,*label[2];
	window[7] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	setwindow(window[7],"아이정보",480,480);//오른 아래
	table = gtk_table_new (11, 11, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window[7]), table);
	

	textbox[1] = gtk_text_view_new();
	buffer[1] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textbox[1]));   
	
	gtk_text_buffer_get_end_iter(buffer[1],&end[1]);

	LogSearch(p_id,p_pw);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textbox[1]),FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbox[1]),FALSE);
	gtk_table_attach_defaults (GTK_TABLE (table), textbox[1], 1, 6, 1, 10);

	label[0] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[0]), "<span font='20'>탑승상태</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[0], 7, 9, 1, 3);

	sw=RideState(p_id,p_pw);
	
	label[1] = gtk_label_new ("");
    	if(sw>0) gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>탑승</span>");
	else if(sw==0) gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>미탑승</span>");
	else gtk_label_set_markup(GTK_LABEL(label[1]),"<span font='20'>에러다썅련아</span>");
	gtk_table_attach_defaults (GTK_TABLE (table), label[1], 7, 9, 4, 6);

	gtk_widget_show_all(window[7]);
	gtk_main ();
}
void search_child(){
	GtkWidget *table,*label[2];
	const gchar *name;
	name=gtk_entry_get_text(GTK_ENTRY(child));
	strcpy(c_name,name);
	//애가 있냐 if
	gtk_widget_destroy(GTK_WIDGET(window[5]));
	int sw=-1;
	window[8] = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  	setwindow(window[8],"아이정보",480,480);//오른 아래
	table = gtk_table_new (11, 11, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window[8]), table);
	

	textbox[2] = gtk_text_view_new();
	buffer[2] = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textbox[2]));   
	
	gtk_text_buffer_get_end_iter(buffer[2],&end[2]);

	LogSearch2(c_name);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textbox[2]),FALSE);
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textbox[2]),FALSE);
	gtk_table_attach_defaults (GTK_TABLE (table), textbox[2], 1, 6, 1, 10);

	label[0] = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label[0]), "<span font='20'>탑승상태</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label[0], 7, 9, 1, 3);

	sw=RideState2(c_name);
	
	label[1] = gtk_label_new ("");
    	if(sw>0) gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>탑승</span>");
	else if(sw==0) gtk_label_set_markup(GTK_LABEL(label[1]), "<span font='20'>미탑승</span>");
	else gtk_label_set_markup(GTK_LABEL(label[1]),"<span font='20'>불확실한 정보</span>");
	gtk_table_attach_defaults (GTK_TABLE (table), label[1], 7, 9, 4, 6);

	gtk_widget_show_all(window[8]);
	gtk_main ();

}

void success_box(){
	GtkWidget  *table,*label,*window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	setwindow(window,"성공",150,100);
	
	table = gtk_table_new (3, 3, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window), table);

	label = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label), "<span font='20'>성공</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label, 1, 2, 1, 2);

	gtk_widget_show_all(window);
	gtk_main ();
}
void false_box(){
	GtkWidget  *table,*label,*window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	setwindow(window,"실패",150,100);
	
	table = gtk_table_new (3, 3, TRUE);//아래 오른
   	gtk_container_add (GTK_CONTAINER (window), table);

	label = gtk_label_new ("");
    	gtk_label_set_markup(GTK_LABEL(label), "<span font='20'>실패</span>");
      	gtk_table_attach_defaults (GTK_TABLE (table), label, 1, 2, 1, 2);

	gtk_widget_show_all(window);
	gtk_main ();
}
void sign_child(){
	const gchar *name,*age,*p_name,*phone,*teacher,*nfc;
	name=gtk_entry_get_text(GTK_ENTRY(student_info[0]));
	age=gtk_entry_get_text(GTK_ENTRY(student_info[1]));
	p_name=gtk_entry_get_text(GTK_ENTRY(student_info[2]));
	phone=gtk_entry_get_text(GTK_ENTRY(student_info[3]));
	teacher=gtk_entry_get_text(GTK_ENTRY(student_info[4]));
	nfc=gtk_entry_get_text(GTK_ENTRY(student_info[5]));
	InsertStudent(nfc,name,age,p_name,phone,teacher);
	for(int i=0; i<6; i++){
		gtk_entry_set_text(GTK_ENTRY(student_info[i]), "");
	}
	success_box();
}
void sign_parent(){
	const gchar *id,*pw,*name,*phone;	
	id=gtk_entry_get_text(GTK_ENTRY(parent_info[0]));
	pw=gtk_entry_get_text(GTK_ENTRY(parent_info[1]));
	name=gtk_entry_get_text(GTK_ENTRY(parent_info[2]));
	phone=gtk_entry_get_text(GTK_ENTRY(parent_info[3]));
	InsertParent(id,pw,name,phone);
	for(int i=0; i<4; i++){
		gtk_entry_set_text(GTK_ENTRY(parent_info[i]), "");
	}
	success_box();
}
//----------------------------------------------------------------------------------------------------------------------
void initDB(){
  
  if(mysql_library_init(0,NULL,NULL)){
    printf("mysql_library_init() 실패\n");
    exit(1);
  }
  conn=mysql_init(NULL);
  if(conn==NULL){
    printf("mysql_init() 실패\n");
    exit(1);
  }

  printf("initDB 완료\n");
}

MYSQL *connectDB(){
	//계정명,비번,DB명,port번호
  return mysql_real_connect(conn,"117.16.19.184","user","test","school",3306,NULL,0);
}

void destroyDB(){
  mysql_close(conn);
  printf("DB연결 해제 완료\n");
}

void CarSearch()
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	int i;
	char str[1000];
	if(mysql_query(conn,"select * from Drive;")!=0)printf("SELECT문 에러\n");
	else{
		res_set=mysql_store_result(conn);
		if(res_set == NULL)printf("error\n");
		else{
			while((row=mysql_fetch_row(res_set)) != NULL){
				strcpy(str,"");
				for(i=0;i<mysql_num_fields(res_set);i++){
					if(row[i]!=NULL){
						strcat(str,row[i]);
						strcat(str,"  ");
					}
				}
				strcat(str,"\n");
				inserttextbox(str);
			}
			mysql_free_result(res_set);
		}
	}
}

int DrivingState()
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	char str[100]="fuck";
	int sw;
	if(mysql_query(conn,"select * from Car;")!=0)printf("SELECT문 에러\n");
	else{
		res_set=mysql_store_result(conn);
		row=mysql_fetch_row(res_set);
		if(strcmp(row[3],"1")==0)sw=1;
		else sw=0;
		mysql_free_result(res_set);
	}
	
	return sw;
}


//부모id,pw로 탑승여부 반환
int RideState(gchar *id,gchar *pw)
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	char str[100]="select m_phone from Member where m_id='";
	char temp[30];
	int sw=-1;
	
	strcat(str,id);
	strcat(str,"' and m_pw='");
	strcat(str,pw);
	strcat(str,"';");
	
	
	//printf("result:%s\n",str);
	if(mysql_query(conn,str)!=0)printf("SELECT문 에러\n");
	else{
	//아이디 비번 일치한 부모를 찾았으며 번호를 temp에 저장
		res_set=mysql_store_result(conn);
		row=mysql_fetch_row(res_set);
		strcpy(temp,row[0]);
		
		

		strcpy(str,"select s_name from Student where s_phone=");
		strcat(str,temp);
		strcat(str,";");

		if(mysql_query(conn,str)!=0)printf("2차 SELECT문 에러\n");
		else{
		//전화번호가 일치한 학원생을 찾았으며 이름을 temp에 저장
			mysql_free_result(res_set);
			res_set=mysql_store_result(conn);
			row=mysql_fetch_row(res_set);
			strcpy(temp,row[0]);
			
			strcpy(str,"select d_state from Drive where d_name='");
			strcat(str,temp);
			strcat(str,"';");
			if(mysql_query(conn,str)!=0) printf("3차 SELECT문 에러\n");
			else{
				mysql_free_result(res_set);
				res_set=mysql_store_result(conn);
				row=mysql_fetch_row(res_set);
				if(strcmp(row[0],"1")==0)sw=1;
				else if(strcmp(row[0],"0")==0)sw=0;
				
				mysql_free_result(res_set);
			}
		}
	}
	
	return sw;
}

//원생이름만으로 탑승여부반환
int RideState2(gchar *name)
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	char str[100]="select d_state from Drive where d_name='";
	char temp[30];
	int sw=-1;
	
	strcat(str,name);
	strcat(str,"';");
	
	
	if(mysql_query(conn,str)!=0)printf("SELECT문 에러\n");
	else{
		res_set=mysql_store_result(conn);
		row=mysql_fetch_row(res_set);
		if(strcmp(row[0],"1")==0)sw=1;
		else if(strcmp(row[0],"0")==0)sw=0;
			
		mysql_free_result(res_set);
	}
	
	return sw;
}

char *GetTeacherName()
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	char *str;
	int sw;
	if(mysql_query(conn,"select * from Car;")!=0)printf("SELECT문 에러\n");
	else{
		res_set=mysql_store_result(conn);
		row=mysql_fetch_row(res_set);
		str=row[2];
		mysql_free_result(res_set);
	}

	return str;
}

void InsertStudent(const gchar *nfc,const gchar *name,const gchar *age,const gchar *parent,const gchar *phone,const gchar *teacher)
{
	char str[1000]="insert into Student values(";
	
	strcat(str,nfc);
	strcat(str,",'");
	strcat(str,name);
	strcat(str,"',");
	strcat(str,age);
	strcat(str,",'");
	strcat(str,parent);
	strcat(str,"','");
	strcat(str,phone);
	strcat(str,"','");
	strcat(str,teacher);
	strcat(str,"');");

	
	mysql_query(conn,str);
}

void InsertParent(const gchar *id,const gchar *pw,const gchar *name,const gchar *phone)
{
	char str[1000]="insert into Member(m_id,m_pw,m_name,m_phone) values('";
	
	strcat(str,id);
	strcat(str,"','");
	strcat(str,pw);
	strcat(str,"','");
	strcat(str,name);
	strcat(str,"',");
	strcat(str,phone);
	strcat(str,");");
	
	mysql_query(conn,str);
}

char *GetMemberId(const char *id)
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	char str[1000]="select m_id from Member where m_id='";
	char *result;	
	strcat(str,id);
	strcat(str,"';");
	
	if(mysql_query(conn,str)!=0) printf("SELECT문 에러\n");
	else{
		res_set=mysql_store_result(conn);
		row=mysql_fetch_row(res_set);
		result=row[0];
		mysql_free_result(res_set);
	}
	
	return result;
}

char *GetMemberPw(const char *pw)
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	char str[1000]="select m_pw from Member where m_pw='";
	char *result;	
	strcat(str,pw);
	strcat(str,"';");
	
	if(mysql_query(conn,str)!=0) printf("SELECT문 에러\n");
	else{
		res_set=mysql_store_result(conn);
		row=mysql_fetch_row(res_set);
		result=row[0];
		mysql_free_result(res_set);
	}
	
	return result;
}

char *GetStudentInfo(const char *name)  //const char* 또는 const gchar * 둘 중하나
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	char str[1000]="select s_name,s_parent,s_phone from Student where s_name='";
	int i;

	strcat(str,name);
	strcat(str,"';");

	
	if(mysql_query(conn,str)!=0) printf("SELECT문 에러\n");
	else{
		/*while((row=mysql_fetch_row(res_set)) != NULL){
		        for(i=0;i<mysql_num_fields(res_set);i++){
        			if(i>0)fputc('\t',stdout);
          			printf("%s",row[i] != NULL ? row[i] : "NULL");
        		}
        		fputc('\n',stdout);
      		}
		mysql_free_result(res_set);*/
	}	
	
}

//부모의id,pw으로 Log출력
void LogSearch(gchar *id,gchar *pw)
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	int i;
	char str[1000]="select m_phone from Member where m_id='";
	char temp[30];
	
	strcat(str,id);
	strcat(str,"' and m_pw='");
	strcat(str,pw);
	strcat(str,"';");
	if(mysql_query(conn,str)!=0) printf("SELECT문 에러\n");
	else{
	//아이디비번 일치한 부모를 찾았으며 번호를 temp에 저장한다
		res_set=mysql_store_result(conn);
		row=mysql_fetch_row(res_set);
		strcpy(temp,row[0]);
		
		strcpy(str,"select s_name from Student where s_phone='");
		strcat(str,temp);
		strcat(str,"';");
		
		if(mysql_query(conn,str)!=0)printf("2차 SELECT문 에러\n");
		else{
		//원생이름을 찾았으며 해당 아이를 temp에 저장한다
			mysql_free_result(res_set);
			res_set=mysql_store_result(conn);
			row=mysql_fetch_row(res_set);
			strcpy(temp,row[0]);
	
			strcpy(str,"select * from Drive where d_name='");
			strcat(str,temp);
			strcat(str,"';");
			
			if(mysql_query(conn,str)!=0) printf("3차 SELECT문 에러\n");
			else{
			//해당아이의 LOG출력한다
				mysql_free_result(res_set);
				res_set=mysql_store_result(conn);
				
				if(res_set == NULL)printf("error\n");
				else{
					while((row=mysql_fetch_row(res_set)) != NULL){
						strcpy(str,"");
						for(i=0;i<mysql_num_fields(res_set);i++){
							if(row[i]!=NULL){
								strcat(str,row[i]);
								strcat(str,"  ");
							}
						}
						strcat(str,"\n");
						inserttextbox2(str);
					}
					mysql_free_result(res_set);
				}
			}
		}
	}
}

//원생 이름만으로 Log기록출력
void LogSearch2(gchar *name)
{
	MYSQL_ROW row;
	MYSQL_RES *res_set;
	int i;
	char str[1000]="select * from Log where l_name='";
	char temp[30];
	
	strcat(str,name);
	strcat(str,"';");
	if(mysql_query(conn,str)!=0) printf("SELECT문 에러\n");
	else{
		res_set=mysql_store_result(conn);
				
		if(res_set == NULL)printf("error\n");
		else{
			while((row=mysql_fetch_row(res_set)) != NULL){
				strcpy(str,"");
				for(i=0;i<mysql_num_fields(res_set);i++){
					if(row[i]!=NULL){
						strcat(str,row[i]);
						strcat(str,"  ");
					}
				}
				strcat(str,"\n");
				inserttextbox3(str);
			}
			mysql_free_result(res_set);
		}
	}
}
