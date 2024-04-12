const char * EqualizerGetPresetName(int32_t preset){
 if (preset == PRESET_CUSTOM) {
 return "Custom";
 } else {
 return gEqualizerPresets[preset].name;
 }
 return 0;
}
