//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h> 

inherit ROOM ;

void create () {
	set ("short", "测试房间5") ;
	set ("long",
	"样的饰品与南北货充斥市场，那边应该可以找到你想要的东西。\n") ;
	set ("exits", ([
	"north" : "/d/grid/rooms/11,8.grid",
	"east" : "/d/grid/rooms/12,9.grid",
	"west" : "/d/grid/rooms/12,7.grid",
	"south" : "/d/grid/rooms/13,8.grid"
	]) ) ;
}
