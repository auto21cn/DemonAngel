//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// dump.c (should be admin cmd?)

inherit F_CLEAN_UP;

int main(object me,string arg)
{
	seteuid(geteuid(me));

    dumpallobj();

	return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : dump
 
dump the stats of all objects to a file in root dir 
named OBJ_DUMP.

HELP
    );
    return 1;
}
 
