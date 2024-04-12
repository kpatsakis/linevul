bool Browser::CanReloadContents(TabContents* source) const {
   return type() != TYPE_DEVTOOLS;
 }
