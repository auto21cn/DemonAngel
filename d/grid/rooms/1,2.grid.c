//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /d/grid/rooms/1,2.grid.c
// by bor @DA, 3/11 2003

inherit ROOM;

void create ()
{
	object ob;

	seteuid(getuid()) ;
	ob = clone_object ("/d/grid/thin_sword") ;
	ob->move(this_object()) ;
	set ("short", "宝物屋") ;
	set ("long", @TEXT
大家一起来捡宝物。
TEXT
);
	set ("exits", ([
	"south" : "/d/grid/rooms/2,2.grid",
	"north" : "/d/grid/rooms/0,2.grid",
	"east" : "/d/grid/rooms/1,3.grid",
	"west" : "/d/grid/rooms/1,1.grid",
	]) ) ;
}
