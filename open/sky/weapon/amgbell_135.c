//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/amgbell_135.c
// saveitem by system @ Fri May 23 21:03:51 2003

#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create() {
	set_name( "make30_tick54_sk92_str5", ({ /* sizeof() == 2 */
  "staff",
  "staff"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的棍棒。
LONG );
		set("unit","把");
		set("type","staff");
		set("add_attr", ([ /* sizeof() == 1 */
  "str" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("invoke_magic", "strong");
		set("level",46);
		set("skill",92);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_staff(15);
	setup();
}
