static const Mem *columnNullValue(void){
  /* Even though the Mem structure contains an element
  ** of type i64, on certain architectures (x86) with certain compiler
  ** switches (-Os), gcc may align this Mem object on a 4-byte boundary
  ** instead of an 8-byte one. This all works fine, except that when
  ** running with SQLITE_DEBUG defined the SQLite code sometimes assert()s
  ** that a Mem structure is located on an 8-byte boundary. To prevent
  ** these assert()s from failing, when building with SQLITE_DEBUG defined
  ** using gcc, we force nullMem to be 8-byte aligned using the magical
  ** __attribute__((aligned(8))) macro.  */
  static const Mem nullMem
#if defined(SQLITE_DEBUG) && defined(__GNUC__)
    __attribute__((aligned(8)))
#endif
    = {
        /* .u          = */ {0},
        /* .flags      = */ (u16)MEM_Null,
        /* .enc        = */ (u8)0,
        /* .eSubtype   = */ (u8)0,
        /* .n          = */ (int)0,
        /* .z          = */ (char*)0,
        /* .zMalloc    = */ (char*)0,
        /* .szMalloc   = */ (int)0,
        /* .uTemp      = */ (u32)0,
        /* .db         = */ (sqlite3*)0,
        /* .xDel       = */ (void(*)(void*))0,
#ifdef SQLITE_DEBUG
        /* .pScopyFrom = */ (Mem*)0,
        /* .mScopyFlags= */ 0,
#endif
      };
  return &nullMem;
}
