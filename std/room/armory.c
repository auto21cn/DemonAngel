//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /std/room/armory.c
// by amgbell @ DA

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <armor.h>

inherit ROOM;

int sort();
string chinese_eq_name(string english);

void init()
{
	int change=0;
	if (!query("long") || query("long")=="0\n" || query("long")=="0\n\n") {
		set("long", @TEXT
你走进一家挂满皮革金属和布料的店铺，裁缝们正坐在柜台后面的一个
长桌边边聊天边将一件件的盔甲防具组合起来，有几位工匠正在弯着一条条
的藤枝，似乎正在做盾牌。
TEXT);
		change=1;
	}

	if (!query("short")) {
		set("short","防具屋");
		change=1;
	}
	//if (change) do_saveroom(this_object());
        add_action("do_make","make");
        add_action("do_list","list");
        add_action("do_remake","remake");
}

int do_make(string arg)
{
	object me, ob;
	int level,i=1;
	string type,str,file;

        me=this_player();
        //return notify_fail("修改中。\n");

        if(me->query("kingdom/id")!=environment(me)->query("kingdom_id"))
        	return notify_fail("What？\n");

	if(!me->query("kingdom/king") && !me->query("kingdom/minister") )
		return notify_fail("What？\n");

        if (!arg) {
	        write(sprintf("贵国防具铺发展: %d\n", develop_data(me->query("kingdom/id"), "query_par", "armory", "dev") ));
        } else if (sscanf(arg,"%d %s",level,type)==2) {
	        if (member_array(type, EQ_TYPES)==-1) return notify_fail("目前不开放此种武器的制作。\n");

		if( kingdom_data(me->query("kingdom/id"), "data", "query_par", "armory")
		>= kingdom_data(me->query("kingdom/id"), "data", "query_par", "max_armory") )
			return notify_fail("贵国防具上限已额满，请删除不必要的防具再建。\n");

//        	if (develop_data(me->query("kingdom/id"), "query_par", "armory", "dev") < level ) 
//	                return notify_fail("贵国的发展不足以制作此等级的防具。\n");

	        if (level < 10) return notify_fail("防具等级必须大于10。\n");
	        if (level >50 ) return notify_fail("防具等级必须小于50。\n");

	        if (kingdom_data(me->query("kingdom/id"),"data","query_par","gold") < level*1000) {
        	        return notify_fail("贵国的国库已经没有钱制作防具了。\n");
	        } else {
	                kingdom_data(me->query("kingdom/id"),"data","sub","gold",level*1000);
        	}
	        str="#include <armor.h>\n";
	        str+="#include <ansi.h>\n";
        	str+="inherit "+upper_case(type)+";\n";
	        str += "void create() {\n";

        	str += "\tset_name(\""+chinese_eq_name(type)+"\", ({\""+type+"\"}) );\n";
	        str+="\tset_weight(10); \n";

	       	str += "\tset(\""+"new"+"\""+", 1);\n";

        	str+="\tif( clonep() )\n";
	        str+="\t\tset_default_object(__FILE__);\n";
        	str+="\telse {\n";
	        str+="\t\tset(\"long\", @LONG\n";
        	str+="一件"+to_chinese_kingdom(me->query("kingdom/id"))+"打造出来的"+chinese_eq_name(type)+"。\n";
	        str+="LONG);\n"; 

        	//str += "set(\""+"value"+"\""+",30);\n";

		str += "\t\tset(\""+"armor_prop/ac"+"\""+","+level/10+");\n";
		str += "\t\tset(\""+"armor_prop/db"+"\""+","+level/10+");\n";

	        str += "\t\tset(\""+"type"+"\""+",\""+type+"\");\n";
        	str += "\t\tset(\""+"level"+"\""+","+level+");\n";
	        str += "\t\tset(\""+"owner"+"\""+",\""+me->query("id")+"\");\n";
        	str += "\t\tset(\""+"kingdom"+"\""+",\""+me->query("kingdom/id")+"\");\n";
	       	str += "\t\tset(\""+"unit"+"\""+",\""+"件"+"\");\n";

        	str+="\t}\n";
	        str+="\tsetup();\n";
        	str+="}\n";

/*	        str+="int query_autoload() {\n";
        	str+="if (query(\"equipped\"))\n";
	        str+="return 1;\n";
	        str+="return 0;\n";
        	str+="}\n"; 
*/
	        do {
	                file=KINGDOM_DIR+me->query("kingdom/id")+"/armory/"+me->query("id")+"_"+sprintf("%d",i)+".c";
        	        i++;
	        }       while (file_size(file) >= 0);

		if (!me->query("last_eq/"+me->query("kingdom/id"))) {
		        do {
		                file=KINGDOM_DIR+me->query("kingdom/id")+"/armory/"+me->query("id")+"_"+sprintf("%d",i)+".c";
        		        i++;
		        }       while (file_size(file) >= 0);
		        me->set("last_eq/"+me->query("kingdom/id"),i);
		        me->save();
		} else {
		        i=me->query("last_eq/"+me->query("kingdom/id"));
		        i++;
		        file=KINGDOM_DIR+me->query("kingdom/id")+"/armory/"+me->query("id")+"_"+sprintf("%d",i)+".c";
		        me->set("last_eq/"+me->query("kingdom/id"),i);
		        me->save();
		}
	        write_file(file,str,1);

	        message_vision("$N要求工匠做"+level+"级的"+chinese_eq_name(type)+"。\n"NOR,me);
        	message_vision("铁匠把"+level+"级的"+chinese_eq_name(type)+"交给$N。\n"NOR,me);

		kingdom_data(me->query("kingdom/id"), "data", "add", "armory", 1);

        	ob = new(file);
	        ob->move(me);
       	} else return notify_fail("make <level> <type>\n");
        sort();
        return 1;
}

int do_list(string arg)
{
        string dir,*items,file,str;
        object me;
        int i=0;

        me=this_player();
        
        if(me->query("kingdom/id")!=environment(me)->query("kingdom_id"))
        	return notify_fail("What？\n");

	if(!me->query("kingdom/king") && !me->query("kingdom/minister") )
		return notify_fail("What？\n");

        sort();

        if (!me->query("armory")) return notify_fail("你目前没有打造任何东西。\n");

        str=sprintf("编号      名字                     拥有者         等级");

        for (i=0;i < sizeof(keys(me->query("armory"))) ;i++ ) {
                file=me->query("armory/"+i);
                str+=sprintf("\n%-10d%-25s%-15s%-8d",
                        i,
                        file->query("name")+"("+file->query("id")+")",
                        file->query("owner"),
                        file->query("level"));
        }
        me->start_more(str+"\n");
        return 1;
}


int do_remake(string arg)
{
        object me, ob;
        string name;

        me=this_player();
        

        if(me->query("kingdom/id")!=environment(me)->query("kingdom_id"))
        	return notify_fail("What？\n");

	if(!me->query("kingdom/king") && !me->query("kingdom/minister") )
		return notify_fail("What？\n");

        sort();
        if (me->query("armory/"+to_int(arg))) {
	        if( !me->can_afford((me->query("armory/"+to_int(arg)))->query("value")) )
	        	return notify_fail("你身上没有足够的钱。\n");

        	me->pay_money((me->query("armory/"+to_int(arg)))->query("value"));
	        me->save();

		ob = new(me->query("armory/"+to_int(arg)));
                ob->move(me);
                name=(me->query("armory/"+to_int(arg)))->query("name");
                message_vision("$N要求铁匠重做"+name+"。\n"NOR,me);
                message_vision("铁匠把"+name+"重做并交给$N。\n"NOR,me);
                return 1;
        }
        return notify_fail("没有这个编号。\n");
}

int sort()
{
	//mapping file_list=([]);
	string dir,*items,file;
	object me;
	int i,id_len,serial=0;

	me=this_player();

	dir=KINGDOM_DIR+me->query("kingdom/id")+"/armory/";
	items=get_dir(dir);

	me->delete("armory");

	if (me->query("kingdom/king")) { //king
	        for (i=0;i<sizeof(items) ; i++) {
	                me->set("armory/"+i,dir+items[i]);
        	}
	} else { //min
	        id_len=strlen(me->query("id"));
	        serial=0;
        	for (i=0;i<sizeof(items) ; i++) {
                	if (strlen(items[i]) < id_len) continue;
	                if (items[i][0..(id_len-1)] == me->query("id")) {
        	                me->set("armory/"+serial,dir+items[i]);
                	        serial++;
		        }
		}
	}
}

string chinese_eq_name(string english)
{
	if (english=="head") return "头盔";
	if (english=="necklace") return "项炼";
	if (english=="body") return "盔甲";
	if (english=="cloak") return "披风";
	if (english=="armor") return "护臂";
	if (english=="gloves") return "手套";
	if (english=="boots") return "护具";
	if (english=="ring") return "戒指";
	if (english=="leggings") return "胫甲";
	if (english=="shield") return "盾牌";
	return "未知";
}
