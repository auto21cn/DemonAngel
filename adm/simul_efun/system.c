//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /adm/simul_efun/system.c
// by bor @RG
// 系统函数置放处

#include <ansi.h>

string inverse_dir(string dir)
{
	switch(dir) {
		case "east":	return "west";	break;
		case "west":	return "east";	break;
		case "north":	return "south";	break;
		case "south":	return "north";	break;
		case "up":	return "down";	break;
		case "down":	return "up";	break;
	}
}

string kill_all_bug(mixed str)
{
	if( !stringp(str) ) return str;
	str = replace_string(str, "\\", "\\\\");
	str = replace_string(str, "\"", "\\\"");
	str = replace_string(str, "@LONG", "");
	str = replace_string(str, "(admin)", "");
	str = replace_string(str, repeat_string(" ", 10), "");
	str = replace_string(str, "\t", "");
	return str;
}

string ansi_color( string str )
{
	str = replace_string(str, "$BLK$", BLK);
	str = replace_string(str, "$RED$", RED);
	str = replace_string(str, "$GRN$", GRN);
	str = replace_string(str, "$YEL$", YEL);
	str = replace_string(str, "$BLU$", BLU);
	str = replace_string(str, "$MAG$", MAG);
	str = replace_string(str, "$CYN$", CYN);
	str = replace_string(str, "$WHT$", WHT);
	str = replace_string(str, "$HIR$", HIR);
	str = replace_string(str, "$HIG$", HIG);
	str = replace_string(str, "$HIY$", HIY);
	str = replace_string(str, "$HIB$", HIB);
	str = replace_string(str, "$HIM$", HIM);
	str = replace_string(str, "$HIC$", HIC);
	str = replace_string(str, "$HIW$", HIW);
	str = replace_string(str, "$NOR$", NOR);
	return str;
}

int refresh_room( object env )
{
	string file, err;
	object ob, *inv;
	int i;

	file = base_name(env) + ".c";
	if( file_size(file)==-1 ) return notify_fail("没有这个档案。\n");

	ob = find_object( file );
	if( ob == env ) {
		inv = all_inventory(ob);
		i = sizeof(inv);
		while(i--)
			if( userp(inv[i]) ) inv[i]->move(VOID_OB, 1);
			else inv[i] = 0;
		destruct(ob);
	}
	if(ob) return notify_fail("无法清除旧程式码。\n");
	err = catch( call_other(file, "???") );
	if( err ) printf( "发生错误：\n%s\n", err );
	else {
		if( (i=sizeof(inv)) && (ob = find_object(file))) {
			while(i--)
				if( inv[i] && userp(inv[i]) ) inv[i]->move(ob, 1);
		}
	}
	return 1;
}

string *text_id(string id)	// by amgbell @DA
{
        string *new_id, *text,str;
        int i, j;
                
                id=lower_case(id);
                text = ({});
        new_id = explode(id, " "); //如果有空格的,就打断,变成阵列 *new_id

        if( zerop(new_id) ) { //如果没有空格
                text = ({ new_id, new_id[0..0], new_id[0..1] }); //直接用id,第1个字,第2个字
      } else { //如果有空格
                text = text + ({id});//本身的id加进去
                for (i=0; i<sizeof(new_id); i++) //用for读,看有几个 
                {
                        str=new_id[i];
                        if (member_array(str,text)==-1) text = text + ({ new_id[i]}); //如果id没有重复的,就加进去
                        for (j=0;j<strlen(new_id[i]);j++) {
                                str=new_id[i][0..j];
                                if (member_array(str,text)==-1) text = text + ({ str });//1,12,123,1234,1....n
                        }
                }
          }
        return text;
}                   

string *text_item_id(string id)	// by bor @DA ... modify text_it()
{
        string *new_id, *text;
                
	id=lower_case(id);
	text = ({id});
        new_id = explode(id, " "); //如果有空格的,就打断,变成阵列 *new_id

	for(int i=0; i<sizeof(new_id); i++)
		text += ({new_id[i]});

        return text;
}                   
