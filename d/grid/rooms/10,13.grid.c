//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

// /d/grid/rooms/10,13.grid

inherit ROOM ;

void create () {
	set ("short", "测试房间") ;
	set ("long", @LONG
这里人来人往, 没事都会发呆。
LONG
	);
	set ("exits", ([
	"north" : "/d/grid/rooms/9,13.grid",		// 档案不存在
	"east" : "/d/grid/rooms/10,14.grid",		// 档案不存在
	"west" : "/d/grid/rooms/10,12.grid",		// 档案不存在
	"south" : "/d/grid/rooms/11,13.grid",		// 档案不存在
	"down" : "/d/gourd/gourd_recall"		// 真实房间
	]) ) ;
}
