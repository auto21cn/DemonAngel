//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/amgbell_76.c
// saveitem by amgbell @ Mon May 19 22:00:47 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "make21_tick43_lv30_sta4", ({ /* sizeof() == 2 */
  "ring",
  "ring"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一件天空打造出来的戒指。
LONG );
		set("unit","件");
		set("type","ring");
		set("add_attr", ([ /* sizeof() == 1 */
  "sta" : 4,
]) );
		set("armor_prop/ac", 4);
		set("armor_prop/db", 4);
		set("level",30);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	setup();
}
