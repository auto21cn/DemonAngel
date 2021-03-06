//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
// clean_up.c
// by Annihilator@ES2


//#define DEBUG

int clean_up()
{
//	if( !clonep() && this_object()->query("no_clean_up") ) return 1;

	if(interactive(this_object())) return 1;

	// If we are contained in something, let environment do the clean
	// up instead of making recursive call. This will prevent clean-up
	// time lag.
	if(environment()) return 1;

        if(this_object()->query("no_clean_up")) return 1;

	foreach(object ob in all_inventory(this_object()))
		if(interactive(ob)) return 1;

#ifdef DEBUG
	log_file("clean_up", sprintf("[%s]clean_up: %O\n", ctime(time())[0..19], this_object() ) );
#endif

	destruct(this_object());
	return 0;
}
