//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/amgbell_605.c
// saveitem by amgbell @ Sun May 25 21:57:44 2003

#include <weapon.h>
#include <ansi.h>
inherit WAND;

void create() {
	set_name( "make27_tick36_sk72_int3狼杖", ({ /* sizeof() == 2 */
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
  "int" : 3,
]) );
		set("weapon_prop/wl", 3);
		set("weapon_prop/Mh", 3);
		set("invoke_magic", "wolf");
		set("level",36);
		set("skill",72);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_wand(12);
	setup();
}
