//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/49
// saveroom by amgbell    Fri May 23 22:35:47 2003

#include <ansi.h>
inherit SMITH;
void create()
{
	set("short", "铁铺");
	set("long", @TEXT
你走进一家铁铺，炙热的热风扑面而来。几个赤着上身的工匠正在这里
打铁，有的拉扯风箱，有的抡着铁锤，叮叮当当地敲个不停，左边的地上，
还有几名老铁匠正围在一张桌旁，对摊在桌上的一张大设计图讨论着。
TEXT
);
	set("type", "smith");
	set("refresh_data", ({ "amgbell", "Fri May 23 22:35:47 2003", "amgbell", "Fri May 23 22:35:47 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "east" : "/open/sky/24",
]));

	setup();
	replace_program(SMITH);
}
