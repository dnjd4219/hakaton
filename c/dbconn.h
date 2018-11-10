#ifndef __DBCONN_H__
#define __DBCONN_H__
#define GTK_ENABLE_BROKEN

#include <my_global.h>
#include <my_sys.h>
#include <m_string.h>
#include <mysql.h>
#include <my_getopt.h>
#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>

GtkWidget *window[11],*btn1[50];
GtkWidget *entry[2],*student_info[6],*textbox[3],*sendbtn,*closebtn,*parent_info[6],*child;
GtkTextBuffer* buffer[3];
GtkTextIter end[3];
MYSQL *conn;

static void destroy(GtkWidget *, gpointer );
char p_id[20],p_pw[20],c_name[20];
void noting();
void setwindow(GtkWidget* ,char *,int ,int );
void inserttextbox(char *);
void inserttextbox2(char *);
void inserttextbox3(char *);
void loginmenu();
int whatlevel(const char*,const char*);
void login();
void adminmenu();
void carmenu();
void join_student();
void close_join();
void close_parent();
void edit_student();
void search_student();
void join_parent();
void sign_parent();
void sign_child();
void child_show();
void search_child();
void success_box();
void false_box();
void cameraopen();
//---------------------------------------------------------------------------------------------------------------------

void initDB();
MYSQL *connectDB();
void destroyDB();
void CarSearch();
void LogSearch(gchar *,gchar *);
void LogSearch2(gchar *);
int DrivingState();
int RideState(char *,char *);
int RideState2(gchar *);
char *GetTeacherName();
char *GetMemberId(const char *);
char *GetMemberPw(const char *);
void InsertStudent(const gchar *,const gchar *,const gchar *,const gchar *,const gchar *,const gchar *);
void InsertParent(const gchar *,const gchar *,const gchar *,const gchar *);
char *GetStudentInfo(const char *);
#endif
