//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /u/b/bor/workroom.c

#include <ansi.h>
#include <login.h>

inherit ROOM;
void create()
{
	set("short", "[1;36m小水鸭的超级工作室[2;37;0m");
	set("long", @LONG
超级工作室。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
  "out" : START_ROOM
]));
	setup();
	load_object("/obj/board/bor_board");
}
