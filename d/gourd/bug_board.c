//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// Room: /d/gourd/bug_board.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "BUG回报版");
	set("long", @LONG
本 MUDLIB 有 BUG, 请在此发表 ~~
LONG
	);
	set("exits", ([
		"west" : __DIR__"recall_lpc.c",
	]));
	setup();
	load_object("/obj/board/gourd_bug");
}
