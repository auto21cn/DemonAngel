//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/wiz/nuke.c
// by bor @DA, 3/9 2003

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string id, file;

	seteuid(geteuid(me));
	if(!wizardp(me)) return 0;
	if (!arg) return notify_fail("指令格式 : nuke <玩家>\n");
	arg = lower_case(arg);

	ob = find_player(arg);
	if( !ob ) return notify_fail("没有这个玩家。\n");
	if( wizardp(ob) ) return notify_fail("你不能随便砍巫师。\n");

	if( id = ob->query("kingdom/id") ) {	// 如果它有国籍, 先去掉标示
		if( ob->query("kingdom/king") ) {	// 灭国 !? or 变成自己当该国家国王?
			"/cmds/adm/delete_kingdom.c"->main(me, id);
		} else if(ob->query("kingdom/minister")) {
			kingdom_data(id, "power", "sub", "minister", arg);
			ob->delete("home");
			ob->delete("kingdom/minister");
			ob->sub_path( ({"/cmds/min/"}) );
			ob->save();
		} else {
			people_data(id, "sub", ob->query("id"));
			ob->delete("kingdom");
		}
	}

	file = arg[0..0] +"/" + arg + __SAVE_EXTENSION__;
	assure_file(DATA_DIR+"nuke/login/"+file);
	if( rename(DATA_DIR+"login/"+file, DATA_DIR+"nuke/login/"+file) )
		write( arg + "的 LOGIN 档已经删除。\n");
	assure_file(DATA_DIR+"nuke/user/"+file);
	if( rename(DATA_DIR+"user/"+file, DATA_DIR+"nuke/user/"+file) )
		write( arg + "的 USER 档已经删除。\n");

	file = arg[0..0]+"/"+arg+__SAVE_EXTENSION__;
	assure_file(DATA_DIR+"nuke/mail/"+file);
	if( file_size(DATA_DIR+"mail/"+file) != -1)
		if( rename(DATA_DIR+"mail/"+file, DATA_DIR+"nuke/mail/"+file ) )
			write(arg+ "的 Mail 档已经删除。\n");

	CHANNEL_D->do_channel(me, "chat", sprintf("%s 遭受天谴消失在这世界．", arg ));

	destruct(ob);
	log_file("nuke", sprintf("[%s] %s nuke %s from <%s>.\n",
		ctime(time())[0..15], geteuid(me), arg, query_ip_name(me) ));

	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : nuke <玩家>

砍玩家档案的
 
HELP
	);
	return 1;
}
