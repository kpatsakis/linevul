__xmlMemStrdup(void){
    if (IS_MAIN_THREAD)
        return (&xmlMemStrdup);
    else
        return (&xmlGetGlobalState()->xmlMemStrdup);
}
