//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/pawlo_21.c
// saveitem by pawlo @ Tue May 20 19:02:37 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make30_42tick_sk84_int4", ({ /* sizeof() == 2 */
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
  "int" : 4,
]) );
		set("weapon_prop/wl", 4);
		set("weapon_prop/Mh", 4);
		set("level",42);
		set("skill",84);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(14);
	setup();
}
