//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// profile.c

int main(object me, string arg)
{
	seteuid(geteuid(me));

	PROFILE_D->make_profile(arg);
	write("Result written to /PROFILE\n");

	return 1;
}
int help (object me)
{
        write(@HELP
指令格式: profile
 
turns on command profiling, the result will be saved to /PROFILE
 
HELP
);
        return 1;
}
 
