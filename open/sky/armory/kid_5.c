//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// item : /open/sky/armory/kid_5.c
// saveitem by system @ Mon May 19 17:38:51 2003

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
  "kar" : 2,
]) );
		set("armor_prop/ac", 2);
		set("armor_prop/db", 2);
		set("level",50);
		set("owner","kid");
		set("kingdom","sky");
	}
	setup();
}
