//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "测试房间2") ;
	set ("long",
	"    这里是葫芦镇最繁华的市街之一飞马广场，许许多多的外来客都\n");
	set ("exits", ([
	"east" : "/d/grid/rooms/11,4.grid",
	"west" : "/d/grid/rooms/11,2.grid",
	]) ) ;
}
