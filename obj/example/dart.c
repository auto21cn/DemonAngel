//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// dart.c

#include <weapon.h>

inherit THROWING;

void create()
{
	set_name("飞镖", ({ "dart" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",	"飞镖是一种十分常见的暗器。\n");
		set("unit", "些");
		set("base_unit", "枝");
		set("base_weight", 40);
		set("base_value", 5);
	}
	set_amount(1);
	init_throwing(20);
	setup();
}
