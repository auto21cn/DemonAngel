//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// money.c

inherit COMBINED_ITEM;

int value() { return query_amount() * (int)query("base_value"); }

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if( sscanf(param, "%d", amt)==1 )
		set_amount(amt);
}
