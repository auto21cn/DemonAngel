//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// eq : /d/gourd/npc/obj/fireage_1422.c

#include <armor.h>
#include <ansi.h>
inherit SHIELD;

void create()
{
	set_name("盾牌", ({"shield"}) );
	set_weight(172);
	if( clonep() )
		set_default_object(__FILE__);
	else {
	set("long", @TEXT
这是由ζ烈火世纪ζ打造出来的装备。
TEXT
	);
	set("type", "shield");
	set("prop", "armory");
	set("material", "一般");
	set("unit", "面");
	set("value", 454);
	set("lv", 36);
	set("armor_prop/ac", 14);
	set("armor_prop/db", 15);
	set("no_copy", 0);
	set("new", 1);
	set("wear_msg", 0);
	set("remove_msg", 0);
	set("home", "/rooms/open/fire_age/equipment165.c");
	set("dir", "fireage_1422");
	set("country", "fire_age");
	set("owner", "fireage");
	set("make_time", "Fri Nov 16 19:22:18 2001");
	set("now_owner", "fireage");
	set("update", "Fri Nov 16 19:22:18 2001");
	setup();
	}
	setup();
}