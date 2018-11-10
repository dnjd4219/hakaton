import pymysql

def nfc_db():
	db = pymysql.connect("localhost", "pi", "skguddnr2740", "school")
	cur = db.cursor()
	cur.execute("select * from Member")

	nfc_cardNum = id

	while True:
		cardNum = cur.fetchone()
		if cardNum == nfc_cardNum: #같은 nfc 키값이 DB에 있을때(내릴때)
			cur.execute("update Drive set d_state = 0 where d_key == (%s)", (nfc_cardNum))
			break;
		elif not cardNum: #nfc 키값이 DB에 없을때(탈때)
			cur.execute("select * from Car") # 차량넘버(d_number) 가져옴
			car = cur.fetchone()
			cur.execute("select * from Student") #반복문까지는 탑승하는 원생정보 Get
			while True:
				child = cur.fetchone()
				if child[0] == nfc_cardNum:
					break; 
			cur.execute("insert into Drive values(%s, %s, %s, %s, now())", (car[0], nfc_cardNum, child[2], 1))
			break
		cur.close()
		db.cloes()

