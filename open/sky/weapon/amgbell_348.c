//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/amgbell_348.c
// saveitem by system @ Sun May 25 15:11:35 2003

#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create() {
	set_name( "make27_tick50_sk80_sta5", ({ /* sizeof() == 2 */
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
  "sta" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("invoke_magic", "magic_shield");
		set("level",40);
		set("skill",80);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_staff(13);
	setup();
}
