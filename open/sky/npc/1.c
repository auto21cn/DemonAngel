//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// NPC : /open/sky/npc/1.c
// savenpc by pawlo    Thu May 22 13:49:22 2003

inherit TAVERN_NPC;

#include <ansi.h>

void create()
{
	set_name("居民", ({"man", "m", "ma"}) );
	set("long", @TEXT
你看见一位第十级的居民。
TEXT
	);
	set("type", "tavern");
	set("level", 10);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Thu May 22 13:49:22 2003",
  "pawlo",
  "Thu May 22 13:49:22 2003"
}));
	set("gender", "男性");
	set("race", "人类");
	set("unit", "位");
	set("home", "/open/sky/6");
	set("kingdom", "sky");
	setup_npc();

}
