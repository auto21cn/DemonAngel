//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// room : /open/sky/50
// saveroom by amgbell    Fri May 23 22:35:56 2003

#include <ansi.h>
inherit ARMORY;
void create()
{
	set("short", "防具屋");
	set("long", @TEXT
你走进一家挂满皮革金属和布料的店铺，裁缝们正坐在柜台后面的一个
长桌边边聊天边将一件件的盔甲防具组合起来，有几位工匠正在弯着一条条
的藤枝，似乎正在做盾牌。
TEXT
);
	set("type", "armory");
	set("refresh_data", ({ "amgbell", "Fri May 23 22:35:56 2003", "amgbell", "Fri May 23 22:35:56 2003" }));
	set("kingdom_id", "sky");
	set("exits", ([ /* sizeof() == 1 */
  "west" : "/open/sky/24",
]));

	setup();
	replace_program(ARMORY);
}
