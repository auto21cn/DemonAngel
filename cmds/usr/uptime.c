//��̶�й�
//http://mud.lovefinal.com
//Final(����)
//��̶�й�(Final)������廯����  ��Ȩ����ԭ����
// uptime.c

inherit F_CLEAN_UP;

// This command is also called by LOGIN_D, so we don't want it use 
// arguments.
int main()
{
	int t, d, h, m, s;
	string time;

	t = uptime();
	s = t % 60;		t /= 60;
	m = t % 60;		t /= 60;
	h = t % 24;		t /= 24;
	d = t;

	if(d) time = chinese_number(d) + "��";
	else time = "";

	if(h) time += chinese_number(h) + "Сʱ";
	if(m) time += chinese_number(m) + "��";
	time += chinese_number(s) + "��";

	write("��«���Ѿ�ִ����" + time + "\n");
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : uptime
 
���ָ��������« II �Ѿ�����ִ���˶��.
 
HELP
    );
    return 1;
}