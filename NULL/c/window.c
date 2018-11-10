#define GTK_ENABLE_BROKEN

#include "dbconn.h"

int main(int argc, char *argv[]){
	initDB();
	if(connectDB(conn)!=NULL) printf("DB연결 성공\n");
	mysql_set_character_set(conn,"utf8");  //C에서sql로 질의문 보낼때 한글 깨짐현상 없애주는코드
	//test
//	GetStudentInfo("sibal");

	gtk_init(&argc, &argv);
	loginmenu();

	destroyDB(conn);
	return 0;

}
