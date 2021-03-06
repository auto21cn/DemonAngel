//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/chfn.c
// by bor @DA, 3/17 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int check_legal_name(string name);

int main(object me, string arg)
{
	string *name;
	seteuid(getuid(me));

	if(!arg) return notify_fail("指令格式 : chfn <中文名字>\n");
	if(!wizardp(me)) {
		if( strlen(arg) > 12) return notify_fail("你的名字太长，请取个超炫的名字吧 !!\n");
		if(!check_legal_name(arg)) return notify_fail("你的名字包含不合法的字眼在内。\n");
		if( !me->query("kingdom/king") && !me->query("kingdom/minister") )
		if( me->query("level")<10 ) return notify_fail("你等级太低，不能改来改去。\n");

		if( !me->query("name_time") ) me->set("name_time", 0);
		if( (time()-me->query("name_time")) <= 1200) return notify_fail("你不久前才刚换过名字，晚点再换吧 !!\n");
	}
	me->set("name", arg);
	me->set("name_time", time());
	write("完成。\n");
	me->save();
	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);

	if( (strlen(name) < 4) || (strlen(name) > 12 ) ) {
		write("对不起，你的中文名字必须是 2 到 6 个中文字。\n");
		return 0;
	}
	while(i--) {
		if( name[i]<='' ) {
			write("对不起，你的中文名字不能用控制字元。\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("对不起，请您用“中文”取名字。\n");
			return 0;
		}
		if( name[i..i+1]=="　" ) {
			write("对不起，请不要用空白字元取名字。\n");
			return 0;
		}
	}
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : chfn <中文名字>
 
这个指令可以让你改名字，有长度限制且不能连续更换。

HELP
	);
	return 1;
}
