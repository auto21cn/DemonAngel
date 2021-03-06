//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/linkroom.c
// by bor @RG

#pragma optimize
#pragma save_binary

#include <ansi.h>
inherit F_CLEAN_UP;

void show_linkroom(object env);
int del_link(object me, string dir);
int check_link(object env);
int connect_link(object env, string dir, string file);

int main(object me, string arg)
{
	object env;
	string list, tmp, new_arg;

	seteuid(getuid());
	if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if(!env = environment(me)) return 0;
	if(!env->query("kingdom_id") || !me->query("kingdom/id")
	|| env->query("kingdom_id") != me->query("kingdom/id") )
		return notify_fail("这里不是我国的领土 !!\n");
	if(!arg) {
		show_linkroom(me);
		return 1;
	}
	arg = lower_case(arg);
	if( arg == "cancel") {	// 取消先前 linkkroom 的动作
		if(!me->query_temp("linkdir")) return notify_fail("你目前尚未设定任何路标。\n");
		me->delete_temp("linkdir");
		me->delete_temp("linkroom");
		write("你把先前的路标拔除了。\n");
		return 1;
	}
	if( sscanf(arg, "cancel %s", arg) == 1 ) {
		if( !env->query("link") || !mapp(env->query("link")) )
			return notify_fail("这里没有用 linkroom 连结的房间。\n");
		if( !env->query("exits/"+arg) ) return notify_fail("找不到这个方向。\n");
		foreach( list, tmp in env->query("link") ) {
			if( list!=arg ) continue;
			if(del_link(me, arg)) return 1;
		}
		return notify_fail( capitalize(arg) + " 的方向不是由 linkroom 所造出来的。\n");
	}
	if( env->query("type")!="normal" ) return notify_fail("这里不是一般的房间，不能连结。\n");
	if( arg!="north" && arg!="south" && arg!="east" && arg!="west" && arg!="down" && arg!="up" )
		return notify_fail("没有这个方向。\n");
	if( env->query("exits/"+arg) ) return notify_fail(arg + " 这个方向已经有出口了，不能再铺马路了。\n");

	if( me->query_temp("linkdir") && me->query_temp("linkroom") ) { // 身上有下过 连结指令，表示准备连结 room
		new_arg = inverse_dir(me->query_temp("linkdir"));
		if( arg != new_arg ) return notify_fail("你连结方向错误 !!\n");
		if( connect_link(env, new_arg, me->query_temp("linkroom") ) ) return 1;
	}
	me->set_temp("linkdir", arg);			// 设定连结方向
	me->set_temp("linkroom", base_name(env));	// 设定环境档案
	write("你拿起铁锤，在这里立了一个路标 -- 马路施工中。\n");
	return 1;
}

void show_linkroom(object me)
{
	object env;
	string str="";
	env = environment(me);

	if( !env->query("link") ) {
		write("这个房间没有任何连接。\n");
		return;
	}
	str += "这个房间用 linkroom 造出的连接方向有 :\n";
	foreach( string list, string tmp in env->query("link") ) {
		str += "\t"+list+"\t: "+tmp+",\n";
	}
	me->start_more(str);
	return ;
}

int del_link(object me, string dir)
{
	object env, link_env;
	string new_dir;
	mapping env_link, link_link;

	env = environment(me);

	if( !link_env = find_object(env->query("exits/"+dir)) ) {
		call_other( env->query("exits/"+dir), "create_env" );
		link_env = find_object(env->query("exits/"+dir));
	}
	if( check_link(link_env) ) {
		write("对面房间有特殊动作词存在 !!\n");
		return 1;
	}

	// 砍本格 link
	env->delete("exits/"+dir);
	env_link = env->query("link");
	map_delete( env_link, dir );
	if( zerop( env->query("link") ) ) env->delete("link");
	do_saveroom(env);

	// 砍另一格的连结
	new_dir = inverse_dir(dir);
	link_env->delete("exits/"+new_dir);
	link_link = link_env->query("link");
	map_delete( link_link, new_dir );
	if( zerop( link_env->query("link") ) ) link_env->delete("link");
	do_saveroom(link_env);

	write("这个方向的连接已经打断了。\n");
	return 1;
}

// 检查 env 是否为 actionroom
int check_link(object env)
{
	if(env->query("type")=="actionroom" || !env->query("link") ) return 1;
	return 0;
}

// env 连结方向为 dir，连到该 file 的地方
int connect_link(object env, string dir, string file)
{
	object link_env;
	string new_dir;

	// 本格先处理
	env->add("exits/"+dir, file);
	if(!env->query("link")) env->set("link", ([ dir:ctime(time()) ]) );
	else env->add("link/"+dir, ctime(time()) );
	do_saveroom(env);

	// 连结房间处理
	if( !link_env = find_object(file) ) {
		call_other( file, "create_env" );
		link_env = find_object(file);
	}
	new_dir = inverse_dir(dir);
	link_env->add("exits/"+new_dir, base_name(env));
	if(!link_env->query("link")) link_env->set("link", ([ new_dir:ctime(time()) ]) );
	else link_env->add("link/"+new_dir, ctime(time()) );
	do_saveroom(link_env);

	message_vision("$N招来一群马路工人，铺出了一条马路。\n", this_player());
	this_player()->delete_temp("linkdir");
	this_player()->delete_temp("linkroom");
	return 1;
}

int help(object me)
{
	write(@HELP

指令格式 : linkroom <方向>              往某方向连接出口
           linkroom <cancel>            取消未完成的连接动作
           linkroom                     看看目前现有的连接出口
           linkroom <cancel 方向>       取消已完成的连接
 
这是国王与大臣用来开路的指令，可以用来连结两间已存在的房间。当你用
makeroom 把房间做好了，而想把一串房间的头尾连接起来的时候，你就会用
到这个指令。

这个指令的用法是 : 你先选好要连接的两个房间，先在其中的一间下 
linkroom <方向> 以定出连接的方向，然后在到另一间下 linkroom <反方向>
若这两个方向可以连接，那路就会开出来了。你可以用 link cancel 取消第
一个连接指令。

当你发现你的连接不适当时, 你可以利用 linkroom cancel <方向> 这个指令
来消除已经作好的连接。

其他相关资讯 : makeroom, delete_room


HELP
	);
	return 1;
}
