//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/grid/rooms/4,2.grid.c
// by bor @DA, 3/11 2003

inherit ROOM ;

void create () {
	set ("short", "狗屋") ;
	set ("long", @LONG
好多狗狗在此睡觉的地方。
LONG
	);
	set ("exits", ([
		"north" : "/d/grid/rooms/3,2.grid",		// 档案不存在
		"east" : "/d/grid/rooms/4,3.grid",		// 档案不存在
		"west" : "/d/grid/rooms/4,1.grid",		// 档案不存在
		"south" : "/d/grid/rooms/5,2.grid",		// 档案不存在
	]) ) ;
}
