//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/king/add_help.c
// by amgbell @ DA

//#pragma optimize
//#pragma save_binary
inherit F_CLEAN_UP;

void do_write(object me,string str);

int main(object me, string arg)
{
        me->edit( (: call_other, __FILE__, "do_write", me :) );
        return 1;
}

void do_write(object me,string str)
{
        string *str_arg;

        str = ansi_color( str );

        if( strlen(str) > 8000 ) {
                write("你的参数太长了。\n");
                return;
        }
        str_arg = explode(str, "\n");

        if( sizeof(str_arg) > 50 ) {
                write("请控制在五十行以内。\n");
                return;
        }
        str = kill_all_bug(str);

        write_file(KINGDOM_DIR+me->query("kingdom/id")+"/data/introduce.txt",str);
//        write(("/open/"+me->query("kingdom/id")+"/introduce.txt"));
        write("ok!\n");

}
int help()
{
        write(@HELP

指令格式 : add_help
 
这是国王用来设定国家简介的指令。

其他相关资讯 :  set_short, set_long, add_mob, add_desc, rooms, areas
                special_rooms, saveroom

HELP
        );
        return 1;
}
