//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/70.c
// saveroom by pawlo @DA, Mon May 26 10:58:17 2003
#include <ansi.h>
inherit HERB_SHOP;

void create()
{
	set("short", "药店");
	set("long", @LONG
你走进一家充满药草味的药店, 店里陈列着各种瓶瓶罐罐, 你可以在这
里买到各种伤药绷带甚至大补丸, 如果你觉得该补一补了, 可以用 list 看
看有什么货色, 再考虑要不要买(buy)。
LONG
	);
	set("type", "herb_shop");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Mon May 26 10:55:35 2003",
  "pawlo",
  "Mon May 26 10:58:17 2003"
}));
	set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"69",
]));
	set("kingdom_id", "sky");

	setup();
	replace_program(HERB_SHOP);
}
