//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// A basic grid room, with non-grid exits.
// Mobydick@TMI-2, 9-3-92

#include <mudlib.h>

inherit ROOM ;

void create () {
	set ("short", "测试房间4") ;
	set ("long",
	"群英会馆，那边聚集了相当多有名望的人士。在东北边不远处各式各\n") ;
	set ("exits", ([
	"east" : "/d/grid/rooms/12,8.grid",
	"west" : "/d/grid/rooms/12,6.grid",
	]) ) ;
}
