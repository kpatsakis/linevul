void jsB_initregexp(js_State *J)
{
	js_pushobject(J, J->RegExp_prototype);
	{
		jsB_propf(J, "RegExp.prototype.toString", Rp_toString, 0);
		jsB_propf(J, "RegExp.prototype.test", Rp_test, 0);
		jsB_propf(J, "RegExp.prototype.exec", Rp_exec, 0);
	}
	js_newcconstructor(J, jsB_RegExp, jsB_new_RegExp, "RegExp", 1);
	js_defglobal(J, "RegExp", JS_DONTENUM);
}
