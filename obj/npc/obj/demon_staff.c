//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// demon_staff.c

#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
	set_name( RED "* 霰 血 天 魔 杵 *" NOR, ({ "demon staff", "staff" }) );
	set_weight(400000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "把");
		set("long", "一把暗红色、两丈多长的巨杵。\n");
		set("material", "crimson gold");
	}
	init_staff(100);

	setup();
}
