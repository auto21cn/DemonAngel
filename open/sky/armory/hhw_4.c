//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/hhw_4.c
// saveitem by system @ Sun May 25 22:30:54 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "make30_tick12_lv33_str1", ({ /* sizeof() == 2 */
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
  "str" : 1,
]) );
		set("armor_prop/ac", 1);
		set("armor_prop/db", 1);
		set("level",33);
		set("owner","hhw");
		set("kingdom","sky");
	}
	setup();
}
