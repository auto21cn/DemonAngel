//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/pawlo_20.c
// saveitem by pawlo @ Mon May 19 20:29:44 2003

#include <armor.h>
#include <ansi.h>
inherit RING;

void create() {
	set_name( "lv25 ac5", ({ /* sizeof() == 2 */
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
  "ac" : 5,
]) );
		set("armor_prop/ac", 2);
		set("armor_prop/db", 2);
		set("level",25);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	setup();
}
