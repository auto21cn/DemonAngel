//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/37.c
// saveroom by pawlo @DA, Sat May 24 18:01:24 2003
#include <ansi.h>
inherit HERO_GUILD;

void create()
{
	set("short", "英雄会馆");
	set("long", @LONG
英雄会馆
LONG
	);
	set("type", "hero_guild");
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Sat May 24 18:01:24 2003",
  "pawlo",
  "Sat May 24 18:01:24 2003"
}));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 2 */
  "down" : __DIR__"36",
  "up" : __DIR__"51",
]));

	setup();
	replace_program(HERO_GUILD);
}
