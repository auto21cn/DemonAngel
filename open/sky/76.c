//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/76.c
// saveroom by pawlo @DA, Wed May 28 09:40:29 2003
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
  "Wed May 28 09:22:49 2003",
  "pawlo",
  "Wed May 28 09:40:29 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"75",
  "east" : __DIR__"77",
]));
	set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/18" : 1,
  __DIR__"npc/17" : 1,
]));

	setup();
	replace_program(ROOM);
}
