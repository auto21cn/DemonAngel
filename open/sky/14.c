//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/14.c
// saveroom by pawlo    Wed May 14 21:43:39 2003

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "空房间 - 请使用 set_short 来编辑标题");
	set("long", "这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。\n");
	set("type", "normal");
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/13",
]));

	setup();
	replace_program(ROOM);
}
