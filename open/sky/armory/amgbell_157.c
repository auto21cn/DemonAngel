//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/amgbell_157.c
// saveitem by amgbell @ Mon May 19 23:04:40 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "make20_tick6_lv20_wl_1", ({ /* sizeof() == 2 */
  "ring",
  "ring"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一件天空打造出来的戒指。
LONG );
		set("unit","件");
		set("type","ring");
		set("armor_prop/ac", 2);
		set("armor_prop/db", 2);
		set("level",20);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	setup();
}
