TABLE* GetTable(cmsIT8* it8)
{
   if ((it8 -> nTable >= it8 ->TablesCount)) {

           SynError(it8, "Table %d out of sequence", it8 -> nTable);
           return it8 -> Tab;
   }

   return it8 ->Tab + it8 ->nTable;
}
