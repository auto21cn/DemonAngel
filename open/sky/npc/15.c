//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// NPC : /open/sky/npc/15.c
// savenpc by pawlo    Tue May 27 09:31:04 2003

inherit STABLE_NPC;

#include <ansi.h>

void create()
{
	set_name("野马", ({"horse", "h", "ho"}) );
	set("long", @TEXT
你看见一位第十五级的野马。
TEXT
	);
	set("type", "stable");
	set("level", 15);
	set("refresh_data", ({ /* sizeof() == 4 */
  "pawlo",
  "Tue May 27 09:31:04 2003",
  "pawlo",
  "Tue May 27 09:31:04 2003"
}));
	set("gender", "雄性");
	set("race", "野兽");
	set("unit", "位");
	set("home", "/open/sky/7");
	set("kingdom", "sky");
	set("ridable", 1);
	setup_npc();

}
