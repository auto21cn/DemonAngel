//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/6.c
// saveroom by pawlo @DA, Thu May 22 13:49:22 2003
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
  "Wed May 14 21:42:56 2003",
  "pawlo",
  "Thu May 22 13:49:22 2003"
}));
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/1" : 1,
]));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "east" : __DIR__"7",
  "west" : __DIR__"5",
]));

	setup();
	replace_program(ROOM);
}
