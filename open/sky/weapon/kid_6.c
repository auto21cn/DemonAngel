//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
#include <weapon.h>
inherit AXE;
void create() {
	set_name( "斧头", ({ /* sizeof() == 2 */
  "axe",
  "axe"
}) );
	set_weight(10); 
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
一把天空打造出来的斧头。
LONG );
		set("unit","把");
		set("type","axe");
		set("level",80);
		set("skill",160);
		set("owner","kid");
		set("kingdom","sky");
	init_axe(80);
	}
	setup();
}
