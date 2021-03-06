//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/delete_room.c
// by sbada @ RG

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	string *dir_list = ({"east","west","north","south","down","up"});
	string id, del_file, type, file;
	object new_env;
	int flag=0;

	seteuid(getuid());
	if(!arg) return notify_fail("指令格式 : delete_room <方向>\n");
	if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
	if( !id = me->query("kingdom/id") ) return 0;
	if( !environment(me)->query("kingdom_id")
	|| environment(me)->query("kingdom_id") != id
	) return notify_fail("这里不是贵国的土地。\n");
	arg = lower_case(arg);
	if( member_array(arg, dir_list)==-1 ) return notify_fail("没有这个方向。\n");
	if( !del_file = environment(me)->query("exits/"+arg) ) return notify_fail("这个方向没有房间。\n");
	if( !sscanf(del_file, "%*s.c") ) del_file += ".c";

	if( !new_env = find_object(del_file) ) {
		call_other(del_file, "create_room");
		new_env = find_object(del_file);
	}
	if( new_env->query("no_delete") || new_env->query("no_save") || new_env->query("no_change") )
		return notify_fail("对面房间无法移除!!\n");

	if( !type = new_env->query("type") ) type = "normal";

	switch( type ) {
		case "normal":
			// 1. 请自行将该 room 的 npc 做统计然后更新国家资讯
			// 2. 移除 room
			kingdom_data(id, "data", "add", "room_num", 1);
			kingdom_data(id, "data", "sub", "room", 1);
			break;
		case "port":	// by bor @DA, 3/4 2003
			return notify_fail("国家港口不能随便拆除。\n");
			break;
		default:
			// 特殊建筑物
			kingdom_data(id, "special_room", "sub", type, del_file);
			// 开始砍掉 board data
			if( type == "board") {
				del_file = replace_string(del_file, ".c", "");
				file = explode(del_file, "/")[2];
				file = id+file;
				rm(DATA_DIR+"board/"+file+".o");
				rm(KINGDOM_DIR+id+"/data/"+file+".c");
			}
	}

	if( new_env->query("objects") && sizeof(new_env->query("objects"))>0 ) {
		// 销毁所有该房间的 NPC 记录
		foreach( file, int tmp in new_env->query("objects") ) {
			if(file_size(file+".c")==-1) continue;
			flag += 1;
			if( find_object(file) ) destruct(find_object(file));
		}
	}
	// 如果是军营或马房呢?
	if( new_env->query("data") && sizeof(new_env->query("data"))>0 ) {
		string *list;
		list = new_env->query("data");
		// 销毁所有该房间的 NPC 记录
		for(int i=0; i<sizeof(list); i++) {
			if(file_size(list[i]+".c")==-1) continue;
			flag += 1;
			// 如果已经离营, 那就销毁 NPC
			if( find_object(list[i]) ) destruct(find_object(list[i]));
		}
	}
	kingdom_data(id, "data", "sub", "npc", flag);
	kingdom_data(id, "data", "add", "npc_num", flag);

	if( !sscanf(del_file, "%*s.c") ) del_file += ".c";
	rm(del_file);
	destruct(new_env);

	environment(me)->delete("exits/"+arg);
	
	message_vision("$N找了一堆工人来在 "+capitalize(arg)+" 碰碰铿铿的，拆了这间房间。\n", me);
	do_saveroom(environment(me));
	return 1;
}

int help(object me)
{
write(@HELP

指令格式 : delete_room <方向>

这是国王与大臣开发国土时用来清除多余房间的指令，你可以用来删除只
剩一个出口或是一条直直通道的房间(这种房间会有两个出口)，而这个出
口的方向就是你站的位置。这个指令不能用来删除王座。

其他相关资讯 :  set_short, set_long, add_mob, add_desc, rooms, areas
		special_rooms, saveroom

HELP
	);
	return 1;
}
