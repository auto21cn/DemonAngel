//泥潭中国
//http://mud.lovefinal.com
//Final(章鹏)
//泥潭中国(Final)负责简体化工作  版权属于原作者
/* support for virtual object servers -- Truilkan@TMI 92/05 */

int query_prevent_shadow()
{
   return 1;
}

object compile_object(string s)
{
   object obj;
   string *tmp;

   seteuid(getuid(this_object()));
   obj = new(file_name(this_object()));
   tmp = explode(s,"/");
   obj->initialize(tmp[sizeof(tmp) - 1]);
   return obj;
}
