//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/pawlo_48.c
// saveitem by system @ Wed May 21 12:28:35 2003

#include <weapon.h>
#include <ansi.h>
inherit AXE;

void create() {
	set_name( "make25_tick27_sk62_kar2", ({ /* sizeof() == 2 */
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
  "kar" : 2,
]) );
		set("weapon_prop/wl", 2);
		set("weapon_prop/Mh", 2);
		set("level",31);
		set("skill",62);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	init_axe(10);
	setup();
}
