//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// NPC : /open/sky/npc/14.c
// savenpc by pawlo    Tue May 27 00:52:33 2003

inherit TAVERN_NPC;

#include <ansi.h>

void create()
{
	set_name("居民", ({"man", "m", "ma"}) );
	set("long", @TEXT
你看见一位第二十一级的居民。
TEXT
	);
	set("type", "tavern");
	set("level", 21);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Tue May 27 00:52:33 2003",
  "pawlo",
  "Tue May 27 00:52:33 2003"
}));
	set("gender", "男性");
	set("race", "人类");
	set("unit", "位");
	set("home", "/open/sky/4");
	set("kingdom", "sky");
	setup_npc();

}
