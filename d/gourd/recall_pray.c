//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/1.c

#include <room.h>

inherit PRAY;

void create()
{
	set("short", "时空门");
	set("long", @LONG
乱飞吧 ~~~
LONG
	);
	set("exits", ([
		"up" : __DIR__"recall_lpc.c",
		"west" : __DIR__"ship_port.c"
	]));
	setup();
	load_object("/obj/board/gourd_lpc");
}
