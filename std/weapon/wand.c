//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// staff.c

#include <weapon.h>
#include <weapon_price.h>

inherit EQUIP;

varargs void init_wand(int damage, int flag)
{
	if( clonep(this_object()) ) return;

	set("weapon_prop/damage", damage);
	set("flag", (int)flag | LONG );
	set("skill_type", "wand");
	if( !query("actions") ) {
		set("actions", (: call_other, WEAPON_D, "query_action" :) );
		set("verbs", ({ "bash", "crush", "slam" }) );
	}
	set("value", wp_price(this_object()));

	if(!query("weapon_prop/wl")) set("weapon_prop/wl", query("skill")/10+2 );
	if(!query("weapon_prop/Mh")) set("weapon_prop/Mh", damage+query_weight()/12+1 );
}

