//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/test/2.c
// saveroom by testlife @DA, Mon Mar 10 20:24:47 2003
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "空房间 - 请使用 set_short 来编辑标题");
	set("long", @LONG
这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。
LONG
	);
	set("type", "normal");
	set("refresh_data", ({ /* sizeof() == 4 */
  "testlife",
  "Mon Mar 10 20:23:45 2003",
  "testlife",
  "Mon Mar 10 20:24:47 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/0" : 1,
]));
	set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"1",
]));
	set("kingdom_id", "test");

	setup();
	replace_program(ROOM);
}
