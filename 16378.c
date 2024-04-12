 static const char *checkstring(js_State *J, int idx)
 {
 	if (!js_iscoercible(J, idx))
		js_typeerror(J, "string function called on null or undefined");
	return js_tostring(J, idx);
}
