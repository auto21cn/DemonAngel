//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/add_action.c
// by bor @DA

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int check_verb(object env, string type, string verb);
varargs void cancel_verb(object env, string type, string verb);
void add_move_verb(object env, string type, string verb, string par);

int main(object me, string arg)
{
	object env;
	string type, verb, par;

	seteuid(getuid());
	if(!arg) return notify_fail("指令格式 : add_action <动作型态> <动作词> <参数>\n");
	if(!env = environment(me)) return 0;
	if(!env->query("kingdom_id")||!me->query("kingdom/id")||env->query("kingdom_id")!=me->query("kingdom/id")) return notify_fail("这里不是贵国的国土。\n");
	if( env->query("type")!="normal"&&env->query("type")!="actionroom") return notify_fail("这里是特殊建筑物，不能加入动作词!!\n");
	if(sscanf(arg,"%s %s %s", type, verb, par)!=3 ) return notify_fail("指令格式 : add_action <动作型态> <动作词> <参数>\n");

	switch(type) {
		case "-d":	// verb 亦即 type, par 则变成 verb
			if(!check_verb(env, verb, par)) return notify_fail("这里并没有这个动作词!!\n");
			cancel_verb(env, verb, par);
		break;
		case "move":
			if(check_verb(env, type, verb)) return notify_fail("这里已经有该动作词了!!\n");
			if( !env->query("exits/"+par) ) return notify_fail("没有这个方向，参数错误。\n");
			add_move_verb(env, type, verb, par);
		break;
		default:
			return notify_fail("目前不开放 "+type+" 的动作类型。\n");
	}
	refresh_room( env );
	return 1;
}

// 先检查环境是否有该动作词
int check_verb(object env, string type, string verb)
{
	if( env->query("action_"+type) && env->query("action_"+type+"/"+verb) ) return 1;
	else return 0;
}

// 取消某个动作词，目前只能砍 action_move
varargs void cancel_verb(object env, string type, string verb)
{
	if(env->query("action_"+type+"/"+verb+"/dir")) env->add("exits/"+env->query("action_"+type+"/"+verb+"/dir"), env->query("action_"+type+"/"+verb+"/file"));
	if(env->query("action_"+type+"/"+verb)) map_delete(env->query("action_"+type), verb);
	if(zerop(env->query("action_"+type))) env->delete("action_"+type);

	printf("你取消 " + verb + " 这个动作词。\n");
	if(!env->query("action_move")) env->set("type", "normal");
	do_saveroom(env);
	return ;
}

// 新增 action_move 的动作型态
void add_move_verb(object env, string type, string verb, string par)
{
	verb = kill_all_bug(verb);
	env->set("action_"+type+"/"+verb+"/dir", par);
	env->set("action_"+type+"/"+verb+"/toward", par);
	env->set("action_"+type+"/"+verb+"/file", env->query("exits/"+par));
	map_delete( env->query("exits"), par);
	if(env->query("type")!="actionroom") env->set("type", "actionroom");
	do_saveroom(env);
	printf("你增加 "+verb+" 这个动作词。\n");
	return ;
}

int help(object me)
{
	write(@HELP

指令格式 : add_action <动作型态> <动作词> <参数>	: 增加动作词
           add_action -d <动作型态> <参数>		: 删除某动作词, 还原连接

动作型态，目前分为: move

例如：你想要下一个指令叫做 jump tree ，可以从一个房间移动到另一个房间，达到跳树的
	效果。你可以下达 add_action move jump north。

	解说：
		1. move 是我们选定的动作型态，因为目前只开放 move，所以啰 @@
		2. jump 就是你选的动作词。
		3. 参数为 north，为什么不直写成 tree ??我们实际上的参数应该是 tree
		   是没错的，不过实际上，我们必须指定“方向”才知道，我们跳往何处。
		   如果你要美化参数成 tree，这就要靠 set_action 来达成了。

	砍掉刚刚的 action ，可以下达 add_action -d move jump。

相关讯息 : set_action

HELP
	);
	return 1;
}
