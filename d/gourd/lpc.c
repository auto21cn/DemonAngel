//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/lpc.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "程式更新、发表版");
	set("long", @LONG
发表程式吗？请来此张贴吧。
LONG
	);
	set("exits", ([
		"up" : "/d/gourd/gourd_recall.c",
		"down": "/d/gourd/1.c"
	]));
	setup();
	load_object("/obj/board/gourd_lpc");
}
