//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/weapon/amgbell_260.c
// saveitem by system @ Fri May 23 22:54:09 2003

#include <weapon.h>
#include <ansi.h>
inherit DAGGER;

void create() {
	set_name( "make27_tick54_sk82_str5", ({ /* sizeof() == 2 */
  "dagger",
  "dagger"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的匕首。
LONG );
		set("unit","把");
		set("type","dagger");
		set("add_attr", ([ /* sizeof() == 1 */
  "str" : 5,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("level",41);
		set("skill",82);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_dagger(13);
	setup();
}
