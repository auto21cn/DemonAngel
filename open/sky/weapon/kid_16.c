//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/kid_16.c
// saveitem by system @ Tue May 20 21:25:21 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make30_tick51_sk90_ac10", ({ /* sizeof() == 2 */
  "axe",
  "axe"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的斧头。
LONG );
		set("unit","把");
		set("type","axe");
		set("add_attr", ([ /* sizeof() == 1 */
  "ac" : 10,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("level",45);
		set("skill",90);
		set("owner","kid");
		set("kingdom","sky");
	}
	init_axe(15);
	setup();
}
