//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/3.c
// saveroom by pawlo @DA, Mon Jun  9 15:04:36 2003
#include <ansi.h>
inherit ACTIONROOM;

void create()
{
	set("short", "空房间 - 请使用 set_short 来编辑标题");
	set("long", @LONG
这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。
这是一间什么\"也没有的空房间，请利用 set_long 来编辑房间叙述。
这是一间什么\\\"也没有的空房间，请利用 set_long 来编辑房间叙述。
这是一间什么\\\"\"也没有的/空房间，请利用 set_long 来编辑房间叙述。
LONG
	);
	set("type", "actionroom");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Wed May 14 14:26:06 2003",
  "pawlo",
  "Mon Jun  9 15:04:36 2003"
}));
	set("item_desc", ([
"bb" : @TEXT
pp
sdf
TEXT
,  "aa" : @TEXT
这是一间什么也没有的空房间，请利用 set_long 来编辑房间叙述。
这是一间什么\"也没有的空房间，请利用 set_long 来编辑房间叙述。
这是一间什么\\\"也没有的空房间，请利用 set_long 来编辑房间叙述。
这是一间什么\\\"\"也没有的/空房间，请利用 set_long 来编辑房间叙述。
TEXT
,  
]));
	set("kingdom_id", "sky");
	set("action_move", ([ /* sizeof() == 2 */
  "kill" : ([ /* sizeof() == 3 */
      "file" : __DIR__"21",
      "toward" : "south",
      "dir" : "south",
    ]),
  "lo" : ([ /* sizeof() == 3 */
      "file" : __DIR__"16",
      "toward" : "north",
      "dir" : "north",
    ]),
]));
	set("objects", ([ ]));
	set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"1",
  "east" : __DIR__"4",
]));

	setup();
	replace_program(ACTIONROOM);
}
