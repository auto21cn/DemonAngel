//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/armor/ring.c

#include <armor.h>
#include <armor_price.h>

inherit EQUIP;

void setup()
{
        if( clonep(this_object()) ) return;

        set("armor_type", TYPE_RING);
        if( !query("armor_apply/dodge")
        &&      weight() > 3000 )
                set("armor_prop/dodge", - weight() / 3000 );

	set("value", eq_price(this_object()));

	if(!query("armor_prop/ac")) set("armor_prop/ac", query("level")/10+2 );
	if(!query("armor_prop/db")) set("armor_prop/db", query("level")/9+1 );

}
