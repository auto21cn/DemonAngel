//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/53
// saveroom by pawlo    Mon May 26 10:15:41 2003

#include <ansi.h>
inherit TAVERN;
void create()
{
	set("short", "旅馆");
	set("long", @TEXT
这里是一家小旅馆，专门供给过路的旅客们歇歇脚用的，里面的房间装\\n饰的非常舒适，不管你受了多大的伤害或者是旅途劳累，你都可以在这里安
心的在里面休养，不用怕被人打扰，这是这一家温柔乡旅社独特的风格。在
一旁的是一位相当可爱的女侍，正在等着各位有需要的人进入休息。
TEXT
);
	set("type", "tavern");
	set("refresh_data", ({ "pawlo", "Mon May 26 10:15:41 2003", "pawlo", "Mon May 26 10:15:41 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/41",
]));

	setup();
	replace_program(TAVERN);
}
