//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// item : /open/sky/weapon/amgbell_172.c
// saveitem by system @ Fri May 23 21:56:49 2003

#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create() {
	set_name( "make28_tick55_sk86_db11", ({ /* sizeof() == 2 */
  "staff",
  "staff"
}) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", @LONG
һ����մ�������Ĺ�����
LONG );
		set("unit","��");
		set("type","staff");
		set("add_attr", ([ /* sizeof() == 1 */
  "db" : 11,
]) );
		set("weapon_prop/wl", 5);
		set("weapon_prop/Mh", 5);
		set("invoke_magic", "strong");
		set("level",43);
		set("skill",86);
		set("owner","amgbell");
		set("kingdom","sky");
	}
	init_staff(14);
	setup();
}