//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "测试房间12") ;
	set ("long",
	"新开幕，店门口还有几篮新鲜的花篮。向北望去各商家喊价的声音依\n") ;
	set ("exits", ([
	"north" : "/d/grid/rooms/8,14.grid",
	"west" : "/d/grid/rooms/9,13.grid",
	]) ) ;
}
