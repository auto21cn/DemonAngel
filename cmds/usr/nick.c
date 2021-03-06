//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// /cmds/usr/nick.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if( !arg ) return notify_fail("你要替自己取什么绰号？\n");
	seteuid(getuid());
	if( arg== "-d" ) {
		me->delete("nickname");
		me->save();
		write("OK!\n");
		return 1;
	}
	if( strlen(arg) > 50 )
		return notify_fail("你的绰号太长了，想一个短一点的、响亮一点的。\n");

	arg = ansi_color( arg );

	me->set("nickname", arg + NOR);
	write("Ok.\n");
	return 1;
}
int help(object me)
{
        write(@HELP
指令格式 : nick <外号, 绰号>
 
这个指令可以让你为自己取一个响亮的名号或头衔，你如果希望在绰号中
使用 ANSI 的控制字元改变颜色，可以用以下的控制字串：

$BLK$ - 黑色		$NOR$ - 恢复正常颜色
$RED$ - 红色		$HIR$ - 亮红色
$GRN$ - 绿色		$HIG$ - 亮绿色
$YEL$ - 土黄色		$HIY$ - 黄色
$BLU$ - 深蓝色		$HIB$ - 蓝色
$MAG$ - 浅紫色		$HIM$ - 粉红色
$CYN$ - 蓝绿色		$HIC$ - 天青色
$WHT$ - 浅灰色		$HIW$ - 白色
 
其中系统自动会在字串尾端加一个 $NOR$。

HELP
        );
        return 1;
}
