NO_INLINE JsVar *jspeFactorFunctionCall() {
  /* The parent if we're executing a method call */
  bool isConstructor = false;
  if (lex->tk==LEX_R_NEW) {
    JSP_ASSERT_MATCH(LEX_R_NEW);
    isConstructor = true;

    if (lex->tk==LEX_R_NEW) {
      jsExceptionHere(JSET_ERROR, "Nesting 'new' operators is unsupported");
      jspSetError(false);
      return 0;
    }
  }

  JsVar *parent = 0;
#ifndef SAVE_ON_FLASH
  bool wasSuper = lex->tk==LEX_R_SUPER;
#endif
  JsVar *a = jspeFactorMember(jspeFactor(), &parent);
#ifndef SAVE_ON_FLASH
  if (wasSuper) {
    /* if this was 'super.something' then we need
     * to overwrite the parent, because it'll be
     * set to the prototype otherwise.
     */
    jsvUnLock(parent);
    parent = jsvLockAgainSafe(execInfo.thisVar);
  }
#endif

  while ((lex->tk=='(' || (isConstructor && JSP_SHOULD_EXECUTE)) && !jspIsInterrupted()) {
    JsVar *funcName = a;
    JsVar *func = jsvSkipName(funcName);

    /* The constructor function doesn't change parsing, so if we're
     * not executing, just short-cut it. */
    if (isConstructor && JSP_SHOULD_EXECUTE) {
      bool parseArgs = lex->tk=='(';
      a = jspeConstruct(func, funcName, parseArgs);
      isConstructor = false; // don't treat subsequent brackets as constructors
    } else
      a = jspeFunctionCall(func, funcName, parent, true, 0, 0);

    jsvUnLock3(funcName, func, parent);
    parent=0;
    a = jspeFactorMember(a, &parent);
  }
#ifndef SAVE_ON_FLASH
  /* If we've got something that we care about the parent of (eg. a getter/setter)
   * then we repackage it into a 'NewChild' name that references the parent before
   * we leave. Note: You can't do this on everything because normally NewChild
   * forces a new child to be blindly created. It works on Getters/Setters because
   * we *always* run those rather than adding them.
   */
  if (parent && jsvIsName(a) && !jsvIsNewChild(a)) {
    JsVar *value = jsvGetValueOfName(a);
    if (jsvIsGetterOrSetter(value)) { // no need to do this for functions since we've just executed whatever we needed to
      JsVar *nameVar = jsvCopyNameOnly(a,false,true);
      JsVar *newChild = jsvCreateNewChild(parent, nameVar, value);
      jsvUnLock2(nameVar, a);
      a = newChild;
    }
    jsvUnLock(value);
  }
#endif
  jsvUnLock(parent);
  return a;
}
