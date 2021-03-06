//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/dismount.c
// by bor @DA, 3/11 2003
 
inherit F_CLEAN_UP;

int do_dismount(object me, string arg);
 
int main(object me, string arg)
{
	seteuid(getuid(me));
	if(!me->query("list/pet")) return 0;
	if(!arg = me->query("list/pet/file")) return 0;
	do_dismount(me, arg);
	return 1;
}

int do_dismount(object me, string arg)
{
        object ob;

	if( me->query_temp("apply/damage") ) me->add_temp("apply/damage", -me->query("list/pet/damage"));
	if( me->query_temp("apply/armor") ) me->add_temp("apply/armor", -me->query("list/pet/armor"));
	ob = find_object(arg);
	if(!ob) return notify_fail("你目前没有骑任何的坐骑。\n");

	ob->set_temp("apply/kee", me->query_temp("apply/kee"));

	message_vision("$N纵身一跃, 离开了$n。\n", me, ob );
	ob->move(environment(me));
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : dismount <坐骑>
 
该是暖暖身, 不要老是靠坐骑了。
 
相关讯息 : mount, pet

HELP
	);
	return 1;
}
