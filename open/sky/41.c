//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/41.c
// saveroom by pawlo @DA, Mon May 26 10:52:02 2003
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
  "pawlo",
  "Mon May 26 10:17:50 2003",
  "pawlo",
  "Mon May 26 10:52:02 2003"
}));
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"67",
  "north" : __DIR__"40",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(ROOM);
}
