//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/grid/rooms/3,2.grid.c
// by bor @DA, 3/11 2003

inherit ROOM ;

void create () {
	set ("short", "测试房间") ;
	set ("long", @LONG
这里人来人往, 没事都会发呆。
LONG
	);
	set ("exits", ([
		"north" : "/d/grid/rooms/2,2.grid",		// 档案不存在
		"east" : "/d/grid/rooms/3,3.grid",		// 档案不存在
		"west" : "/d/grid/rooms/3,1.grid",		// 档案不存在
		"south" : "/d/grid/rooms/4,2.grid",		// 档案不存在
		"down" : "/d/gourd/gourd_recall"		// 真实房间
	]) ) ;
}
