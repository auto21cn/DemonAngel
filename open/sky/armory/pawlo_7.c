//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/pawlo_7.c
// saveitem by system @ Mon May 19 17:36:35 2003

#include <armor.h>
#include <ansi.h>
inherit BOOTS;

void create() {
	set_name( "护具", ({ /* sizeof() == 2 */
  "boots",
  "boots"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一件天空打造出来的护具。
LONG );
		set("unit","件");
		set("type","boots");
		set("add_attr", ([ /* sizeof() == 1 */
  "sta" : 1,
]) );
		set("armor_prop/ac", 1);
		set("armor_prop/db", 1);
		set("level",5);
		set("owner","pawlo");
		set("kingdom","sky");
	}
	setup();
}
