//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/kid_22.c
// saveitem by system @ Tue May 20 21:32:00 2003

#include <weapon.h>
#include <ansi.h>
inherit WAND;

void create() {
	set_name( "make30_tick45_sk86_str4", ({ /* sizeof() == 2 */
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
  "str" : 4,
]) );
		set("weapon_prop/wl", 4);
		set("weapon_prop/Mh", 4);
		set("invoke_magic", "strong");
		set("level",43);
		set("skill",86);
		set("owner","kid");
		set("kingdom","sky");
	}
	init_wand(14);
	setup();
}
