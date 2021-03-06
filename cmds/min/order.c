//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/order.c from es2 1.2b
// modify by bor @DA, 3/17 2003

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int res;
	object ob;
	string who, cmd, verb, path;

	seteuid(getuid(me));
	if( me != this_player(1) ) return 0;

	if( !arg || arg=="" || sscanf(arg, "%s to %s", who, cmd)!=2 )
		return notify_fail("你要命令谁做什么事？\n");

	ob = present(who, environment(me));
	if( !ob || !ob->is_character()) return notify_fail("这里没有这个人。\n");

	if( sscanf(cmd, "%s %*s", verb) != 2 ) verb = cmd;

	if( !ob->query("kingdom/id") ) return notify_fail("你不能命令这个人。\n");

	if( me->query("kingdom/id") != ob->query("kingdom/id") )
		return notify_fail("你不能指挥这个人。\n");

	write("你命令" + ob->name() + ": " + cmd + "\n");

	if( stringp(path = ob->find_command(verb))
	&&    path != "/cmds/npc/" + verb && path != "/cmds/usr/" + verb  )
		return notify_fail("你不能命令别人做这种事。\n");

	if( !ob->accept_order(me, verb) ) return notify_fail("What !?\n");

	seteuid(getuid());
	res = ob->force_me(cmd);
	return res;
}

int help(object me)
{
	write(@TEXT

指令格式：order <target> to <command>

这是让国王和大臣下命令的指令，他们可以命令他的国民作大
部分的事， 当然有些事是被禁止的。如果你乱下命令，会引起
国人反感的。

这个命令还可以用来命令你召来的 mob 丢下(drop)他身上的装
备。或是 命令低于你的等级的军事类 mob 跟随和保护你，不
过也只限于此了。只 有国王可以命令国家中的所有 mob。注意
，如果你把 mob 带出国去，你要小心的把他带回来，否则如果
他被人给宰了，他就消失了。

如果你的国民很吵或是乱用公用频道吵闹, 你可以命令他闭嘴
(quiet)十 分钟, 以免损害国家形象。不过这个命令是不能撤销
的, 只有等时间过了才会取消, 所以千万不要拿来开玩笑。

目前可以使用的命令有 : nick, chfn, wear, remove, wield, unwield, 


TEXT
	);
	return 1;
}
