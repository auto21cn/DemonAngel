//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/save.c
// modify by bor @DA, 3/5 2003

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object link_ob;

	seteuid(getuid());

	if( !objectp(link_ob = me->query_temp("link_ob")) )
		return notify_fail("你不是经由正常连线进入，不能储存。\n");

	if( environment(me)->query("valid_startroom") ) {
		me->set("startroom", base_name(environment(me)));
		write("当你下次连线进来时，会从这里开始。\n");
	}

	if( (int)link_ob->save() && (int)me->save() ) {
		link_ob->set("last_on", time());
		link_ob->set("last_from", query_ip_name(me));
	        write("档案储存完毕。\n");
		return 1;
	} else {
		write("储存失败。\n");
		return 0;
	}
}

int help(object me)
{
	write(@HELP
指令格式：save

把你辛苦奋斗的结果存起来。
HELP
	);
	return 1;
}
