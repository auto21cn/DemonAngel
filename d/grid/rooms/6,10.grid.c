//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "测试房间6") ;
	set ("long",
	"    你走在这葫芦镇最出名的朴素街道上，人来人往，似乎忙着赚钱\n") ;
	set ("exits", ([
	"north" : "/d/grid/rooms/5,10.grid",
	"east" : "/d/grid/rooms/6,11.grid",
	"west" : "/d/grid/rooms/6,9.grid",
	"south" : "/d/grid/rooms/7,10.grid",
	]) ) ;
}
