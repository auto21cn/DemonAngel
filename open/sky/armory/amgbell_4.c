//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/amgbell_4.c
// saveitem by system @ Mon May 19 17:41:00 2003

#include <armor.h>
#include <ansi.h>
inherit HEAD;

void create() {
	set_name( "头盔", ({ /* sizeof() == 2 */
  "head",
  "head"
}) );
	set_weight(10);
	set("new",1);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一件天空打造出来的头盔。
LONG );
		set("unit","件");
		set("type","head");
		set("add_attr", ([ /* sizeof() == 1 */
  "Mh" : 1,
]) );
		set("armor_prop/ac", 0);
		set("armor_prop/db", 0);
		set("level",32);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	setup();
}
