//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// eq : /d/gourd/npc/obj/kid_336.c

#include <armor.h>
#include <ansi.h>
inherit CLOAK;

void create()
{
	set_name( "[1;36m蓝焰。快速披风[m", ({ /* sizeof() == 2 */
  "cloak",
  "cloak"
}) );
	set_weight(188);
	if( clonep() )
		set_default_object(__FILE__);
	else {
	set("long", @TEXT
这是由ζ烈火世纪ζ打造出来的装备。
TEXT
	);
	set("lv", 42);
	set("armor_prop/ac", 16);
	set("armor_prop/db", 17);
	set("armor_prop/sta", 4);
	set("attr_list/1", "sta");
	set("armor_prop/dex", 5);
	set("attr_list/2", "dex");
	set("type", "cloak");
	set("unit", "件");
	set("value", 647);
	set("material", "一般");
	set("prop", "armory");
	set("no_copy", 0);
	set("old", 1);
	set("wear_msg", 0);
	set("remove_msg", 0);
	set("home", "/rooms/open/fire_age/equipment64.c");
	set("dir", "kid_336");
	set("country", "fire_age");
	set("owner", "kid");
	set("make_time", "Mon Feb 19 21:11:47 2001");
	set("now_owner", "kid");
	set("update", "Tue Feb 20 11:42:57 2001");

	setup();
}	setup();
}