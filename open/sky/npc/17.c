//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// NPC : /open/sky/npc/17.c
// savenpc by amgbell    Wed May 28 19:31:36 2003

inherit TAVERN_NPC;

#include <ansi.h>

void create()
{
	set_name("小孩", ({"child", "c", "ch"}) );
	set("long", @TEXT
你看见一位第一级的小孩。
TEXT
	);
	set("type", "tavern");
	set("level", 1);
	set("refresh_data", ({ /* sizeof() == 4 */
  "amgbell",
  "Wed May 28 19:31:36 2003",
  "amgbell",
  "Wed May 28 19:31:36 2003"
}));
	set("gender", "男性");
	set("race", "人类");
	set("unit", "位");
	set("home", "/open/sky/kingdom");
	set("kingdom", "sky");
	setup_npc();

}
