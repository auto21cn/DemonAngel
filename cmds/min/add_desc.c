//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/min/add_desc.c
// by smallpen

#pragma optimize
#pragma save_binary

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
        object env;
        string *desc,str,item;
        mapping room_item;
        int i;
        
        seteuid(getuid(me));
        env = environment(me);
        //查询现有房间的细部描述
        if(!arg) {
                
                if(!mapp(room_item=env->query("item_desc")) ) return notify_fail("目前这里没有任何细部描述, 你要帮房间的哪里加细部描述 ?\n");
                if(env->query("kingdom_id") != me->query("kingdom/id") ) return notify_fail("这里不是贵国的土地!\n");
                desc = keys(room_item);
                str = "这里的 item_desc 有："HIY;
                for(i=0;i<sizeof(desc);i++) {
                        if(i == (sizeof(desc)-1)) {
                                str += desc[i] + "。\n"NOR;
                        } else {
                                str += desc[i] + "，";
                        }
                }
                me->start_more(str);
                return 1;
        }
        //增加细部描述
        if( sscanf(arg,"-a %s",item) == 1) {
                if(!(env->query("item_desc/"+item)) ) {
                        //查看有没有重复的item_desc
                        me->edit( (: call_other, __FILE__, "do_change", me,item :) );
                } else return notify_fail("此项 item_desc 已经存在此间房间了!\n");
        } else if( sscanf(arg,"-d %s",item) == 1) {
                //删除特定的item_desc
                if( env->query("item_desc/"+item) ) {
                        env->delete("item_desc/"+item);
                        do_saveroom(env);
                        write("此项 item_desc 已经删除完毕了!\n");
                        return 1;
                } else return notify_fail("没有此项 item_desc 存在此间房间中!\n");
        } else return notify_fail("指令格式错误，请参考Help档说明!\n");
        
        return 1;
}

void do_change(object me, string items, string str)
{
        string *str_arg;

        str = ansi_color( str );

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
        environment(me)->add("item_desc", ([items:str]));
        write("细部描述新增完毕!\n");
        do_saveroom(environment(me));
        return ;
}

int help(object me)
{
        write(@HELP

指令格式 : add_desc -a <特定词>         : 增加一个描述
           add_desc -d <特定词>         : 去除一个描述
           add_desc                     : 查询现有的描述
                                                                                
这是国王与大臣用来开发国土的指令, 这个指令用来为房间增加细部的描述，
就是你用 look <特定词>时看到的描述。这个指令只是改变描述而已, 若房
间的一切都弄好了, 要记得用 saveroom 把房间存起来。
                                                                                
add_desc 会提供一个编辑器, 让你把你想表达的描述打进去, 当然, 你也可
以用 NCSA 提供的 copy - paste 或其他类似的工具来把已经打好的资料贴
进来。编辑完以后按 <enter> 再按 '.' 就可以完成输入了。完成后，你可
以用 look <特定词> 来看看完成的结果。
                                                                                
注意事项：
        请避免使用 " 此符号，否则可能会造成该格有错误讯息。
                                                                                
                                                                                
其他相关资讯 :  set_short, set_long, add_mob, add_desc, rooms, areas
                special_rooms, saveroom

HELP
        );
        return 1;
}
