//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/hp.c
 
inherit F_CLEAN_UP;
 
int main(object me, string arg)
{
	object ob;
 
	seteuid(getuid(me));
	if(!arg) ob = me;
	else if (wizardp(me)) {
		ob = present(arg, environment(me));
		if (!ob) ob = find_player(arg);
		if (!ob) ob = find_living(arg);
		if (!ob) ob = me;
	} else ob = me;
 
	printf("体力 : %4d/%4d (%3d%%)\n" , ob->query_hp(),ob->query_base_hp(),ob->query_hp()*100/ob->query_base_hp());
	printf("法力 : %4d/%4d (%3d%%)\n" , ob->query_mp(),ob->query_base_mp(),ob->query_mp()*100/ob->query_base_mp());
	printf("经验 : %d\n", ob->query("exp"));

	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : hp
 
这个指令可以显示你(你)目前的概略状况。
 
相关讯息 : score, die

HELP
	);
	return 1;
}
