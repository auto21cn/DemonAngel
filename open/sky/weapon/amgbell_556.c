//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/amgbell_556.c
// saveitem by system @ Sun May 25 19:37:11 2003

#include <weapon.h>
#include <ansi.h>
inherit WAND;

void create() {
	set_name( "make28_tick50_sk84_int5", ({ /* sizeof() == 2 */
  "wand",
  "wand"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的魔杖。
LONG );
		set("unit","把");
		set("type","wand");
		set("add_attr", ([ /* sizeof() == 1 */
  "int" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("invoke_magic", "magic_shield");
		set("level",42);
		set("skill",84);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_wand(14);
	setup();
}
