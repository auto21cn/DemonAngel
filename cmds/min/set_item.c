//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/set_item.c
// by amgbell @ DA

//#pragma optimize
//#pragma save_binary

inherit F_CLEAN_UP;

void query_item(object ob);
int check_item(object ob);
private int check_legal_id(string id);

int main(object me, string arg)
{
        object ob;
        string type,temp,*change_limit,file;
        mixed value;
        int num=0;

        seteuid(getuid());
        change_limit=({"id","level","name","aggresive","no_corpse","nickname"});
        if( me->is_busy() ) return notify_fail("你的动作还没有完成。\n");
        if( me->is_fighting() ) return notify_fail("你还在战斗中。\n");
        if( !arg ) return notify_fail("指令格式 : set_item <物品名称> <参数类型> <设定值>\n");

        if(ob = present(arg, me)) {      //set_item item
                if( !ob ) return notify_fail("你身上没有这个物品。\n");
                
                if (check_item(ob))
                {
                        query_item(ob);
                }
        
                        
        //set int value
        } else if (sscanf(arg,"%s %d %s %d",temp,num,type,value)==4 || sscanf(arg,"%s %s %d",temp,type,value)==3  ) {
                if (num) temp=temp+" "+num;
                change_limit=({"no_copy"});
                if (ob = present(temp, me))
                {
                if (!intp(value) )  return notify_fail("这个设定值一定要为数字。\n");
        
                        if (check_item(ob)==1)
                        {

                        if (!me->query("kingdom/king") && ob->query("owner")!=me->query("id"))
				return notify_fail("该物品的Owner不是你。\n");
                                
                                if (member_array(type,change_limit) != -1) {
                                
                                        set_all_the_same_objects(ob,type,value);
                                        //ob->set(type,value);
                                        do_saveitem(ob);
                                        //update_object(ob);
                                        write("ok!\n");
                                        //ob->move(environment(me));
                                } else return notify_fail("指令格式 : set_item <生物名称> <参数类型> <设定值>1\n");
                        } else return notify_fail("指令格式 : set_item <生物名称> <参数类型> <设定值>2\n");
                } else return notify_fail("你身上没有这个物品。\n");
// set string
        } else if (sscanf(arg,"%s %d %s %s",temp,num,type,value)==4 || sscanf(arg,"%s %s %s",temp,type,value)==3  ) {
                if (num) temp=temp+" "+num;
                change_limit=({"id","name","unit","owner"});
                if (ob = present(temp, me))
                {
                
                        if (check_item(ob)==1)
                        {

                        if (!me->query("kingdom/king") && ob->query("owner")!=me->query("id"))
				return notify_fail("该物品的Owner不是你。\n");

                        if (member_array(type,change_limit) != -1) {

                                value=kill_all_bug(value);

                                value=ansi_color(value,1);

                                if (type=="id")
                                {
                                        if (!check_legal_id(value)) return 1;
                                }

        if ((value[strlen(value)-1 .. strlen(value)-1])=="\\") value+="\\";

                if( sscanf(value, "*s") || sscanf(value, "%*s*s") ) set_all_the_same_objects(ob,type,value+""); //ob->set(type,value+"");
                else set_all_the_same_objects(ob,type,value); //ob->set(type,value);
                                        
                                        do_saveitem(ob);
                                        //update_object(ob);
                                        write("ok!\n");
                                        //ob->move(environment(me));
                                } else return notify_fail("指令格式 : set_item <物品名称> <参数类型> <设定值>\n");
                        } else return notify_fail("指令格式 : set_item <物品名称> <参数类型> <设定值>\n");
                } else return notify_fail("你身上没有这个物品。\n");

        
        } else if (sscanf(arg,"%s %d long",temp,num,type,value)==2 || sscanf(arg,"%s long",temp,type,value)==1 )
        {
                if (num) temp=temp+" "+num;
                if (ob = present(temp, me))
                {
                        if (!me->query("kingdom/king") && ob->query("owner")!=me->query("id"))
				return notify_fail("该物品的Owner不是你。\n");
                        if (check_item(ob)==1)
                        {
                                me->edit( (: call_other, __FILE__, "do_change", me,ob :) );

                        } else return notify_fail("指令格式 : set_item <物品名称> <参数类型> <设定值>\n");
                } else return notify_fail("这里没有这个物品。\n");

        } else return notify_fail("你身上没有这个物品。\n");


        return 1;
}

void do_change(object me,object ob, string str)
{
        string *str_arg;

        str = ansi_color( str ,1);

        if( strlen(str) > 8000 ) {
                write("你的参数太长了。\n");
                return;
        }
        str_arg = explode(str, "\n");
        if( sizeof(str_arg) > 10 ) {
                write("请控制在十行以内。\n");
                return;
        }
        str = kill_all_bug(str);
        str=replace_string(str,"\\\\","\\");
        set_all_the_same_objects(ob,"long",str);
        write("ok!\n");
        do_saveitem(ob);

        return ;
}

void query_item(object ob)
{
        string msg;
	msg = ob->query("name")+"的资料如下 :\n\n";
	msg += sprintf("name : %-18sid : %-19s\n", ob->query("name"), ob->query("id"));
	msg += sprintf("type : %-18sowner : %-16s\n", ob->query("type"), ob->query("owner"));
	msg += sprintf("no_copy : %-15dunit : %4s\n\n", ob->query("no_copy"), ob->query("unit"));
	msg += sprintf("long :\n%s\n", ob->query("long"));
                
	write(msg);
}

int check_item(object ob) {

        if(ob->is_corpse()) return notify_fail("这里没有这个物品。\n");
        if(ob->query("kingdom") != this_player()->query("kingdom/id")) return notify_fail("它不是贵国的物品。\n");
        return 1;
}

private int check_legal_id(string id)
{
	int i;
	string *banned_id = ({"bor","zethus","fuck","sbada"});

	i = strlen(id);
        
	if( (strlen(id) < 2) || (strlen(id) > 20 ) ) return 0;
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) return 0;
	for(i=0;i<sizeof(banned_id);i++) {
		if(strsrch(id, banned_id[i]) != -1) {
			write("对不起，你的内容有部份文字将会造成别人困扰。\n");
			return 0;
		}
	}
	return 1;
}

int help(object me)
{
        write(@HELP

指令格式 : set_item

HELP
        );
        return 1;

}
