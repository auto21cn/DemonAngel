//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/1.c
// saveroom by pawlo @DA, Wed May 14 21:43:59 2003
#include <ansi.h>
inherit PORT;

void create()
{
	set("short", "[1;36m池塘[0m");
	set("long", @LONG
这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。
LONG
	);
	set("type", "port");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Sun Mar 09 20:24:01 2003",
  "pawlo",
  "Wed May 14 21:43:59 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 4 */
  "north" : __DIR__"15",
  "west" : __DIR__"kingdom",
  "east" : __DIR__"3",
  "south" : __DIR__"2",
]));

	setup();
	replace_program(PORT);
}
