//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/pawlo_39.c
// saveitem by system @ Tue May 20 22:12:41 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make25_tick32_sk66_db6", ({ /* sizeof() == 2 */
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
  "db" : 6,
]) );
		set("weapon_prop/wl", 3);
		set("weapon_prop/Mh", 3);
		set("level",33);
		set("skill",66);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(11);
	setup();
}
