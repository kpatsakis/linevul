NO_INLINE JsVar *jspeBlockOrStatement() {
  if (lex->tk=='{') {
    jspeBlock();
    return 0;
  } else {
    JsVar *v = jspeStatement();
    if (lex->tk==';') JSP_ASSERT_MATCH(';');
    return v;
  }
}

/** Parse using current lexer until we hit the end of
 * input or there was some problem. */
NO_INLINE JsVar *jspParse() {
  JsVar *v = 0;
  while (!JSP_SHOULDNT_PARSE && lex->tk != LEX_EOF) {
    jsvUnLock(v);
    v = jspeBlockOrStatement();
  }
  return v;
}

NO_INLINE JsVar *jspeStatementVar() {
  JsVar *lastDefined = 0;
  /* variable creation. TODO - we need a better way of parsing the left
   * hand side. Maybe just have a flag called can_create_var that we
   * set and then we parse as if we're doing a normal equals.*/
  assert(lex->tk==LEX_R_VAR || lex->tk==LEX_R_LET || lex->tk==LEX_R_CONST);
  jslGetNextToken();
  bool hasComma = true; // for first time in loop
  while (hasComma && lex->tk == LEX_ID && !jspIsInterrupted()) {
    JsVar *a = 0;
    if (JSP_SHOULD_EXECUTE) {
      a = jspeiFindOnTop(jslGetTokenValueAsString(lex), true);
      if (!a) { // out of memory
        jspSetError(false);
        return lastDefined;
      }
    }
    JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(a), lastDefined);
    if (lex->tk == '=') {
      JsVar *var;
      JSP_MATCH_WITH_CLEANUP_AND_RETURN('=', jsvUnLock(a), lastDefined);
      var = jsvSkipNameAndUnLock(jspeAssignmentExpression());
      if (JSP_SHOULD_EXECUTE)
        jspReplaceWith(a, var);
      jsvUnLock(var);
    }
    jsvUnLock(lastDefined);
    lastDefined = a;
    hasComma = lex->tk == ',';
    if (hasComma) JSP_MATCH_WITH_RETURN(',', lastDefined);
  }
  return lastDefined;
}

NO_INLINE JsVar *jspeStatementIf() {
  bool cond;
  JsVar *var, *result = 0;
  JSP_ASSERT_MATCH(LEX_R_IF);
  JSP_MATCH('(');
  var = jspeExpression();
  if (JSP_SHOULDNT_PARSE) return var;
  JSP_MATCH(')');
  cond = JSP_SHOULD_EXECUTE && jsvGetBoolAndUnLock(jsvSkipName(var));
  jsvUnLock(var);

  JSP_SAVE_EXECUTE();
  if (!cond) jspSetNoExecute();
  JsVar *a = jspeBlockOrStatement();
  if (!cond) {
    jsvUnLock(a);
    JSP_RESTORE_EXECUTE();
  } else {
    result = a;
  }
  if (lex->tk==LEX_R_ELSE) {
    JSP_ASSERT_MATCH(LEX_R_ELSE);
    JSP_SAVE_EXECUTE();
    if (cond) jspSetNoExecute();
    JsVar *a = jspeBlockOrStatement();
    if (cond) {
      jsvUnLock(a);
      JSP_RESTORE_EXECUTE();
    } else {
      result = a;
    }
  }
  return result;
}

NO_INLINE JsVar *jspeStatementSwitch() {
  JSP_ASSERT_MATCH(LEX_R_SWITCH);
  JSP_MATCH('(');
  JsVar *switchOn = jspeExpression();
  JSP_SAVE_EXECUTE();
  bool execute = JSP_SHOULD_EXECUTE;
  JSP_MATCH_WITH_CLEANUP_AND_RETURN(')', jsvUnLock(switchOn), 0);
  if (!execute) { jsvUnLock(switchOn); jspeBlock(); return 0; }
  JSP_MATCH_WITH_CLEANUP_AND_RETURN('{', jsvUnLock(switchOn), 0);

  bool executeDefault = true;
  if (execute) execInfo.execute=EXEC_NO|EXEC_IN_SWITCH;
  while (lex->tk==LEX_R_CASE) {
    JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_R_CASE, jsvUnLock(switchOn), 0);
    JsExecFlags oldFlags = execInfo.execute;
    if (execute) execInfo.execute=EXEC_YES|EXEC_IN_SWITCH;
    JsVar *test = jspeAssignmentExpression();
    execInfo.execute = oldFlags|EXEC_IN_SWITCH;;
    JSP_MATCH_WITH_CLEANUP_AND_RETURN(':', jsvUnLock2(switchOn, test), 0);
    bool cond = false;
    if (execute)
      cond = jsvGetBoolAndUnLock(jsvMathsOpSkipNames(switchOn, test, LEX_TYPEEQUAL));
    if (cond) executeDefault = false;
    jsvUnLock(test);
    if (cond && (execInfo.execute&EXEC_RUN_MASK)==EXEC_NO)
      execInfo.execute=EXEC_YES|EXEC_IN_SWITCH;
    while (!JSP_SHOULDNT_PARSE && lex->tk!=LEX_EOF && lex->tk!=LEX_R_CASE && lex->tk!=LEX_R_DEFAULT && lex->tk!='}')
      jsvUnLock(jspeBlockOrStatement());
    oldExecute |= execInfo.execute & (EXEC_ERROR_MASK|EXEC_RETURN); // copy across any errors/exceptions/returns
  }
  jsvUnLock(switchOn);
  if (execute && (execInfo.execute&EXEC_RUN_MASK)==EXEC_BREAK) {
    execInfo.execute=EXEC_YES|EXEC_IN_SWITCH;
  } else {
    executeDefault = true;
  }
  JSP_RESTORE_EXECUTE();

  if (lex->tk==LEX_R_DEFAULT) {
    JSP_ASSERT_MATCH(LEX_R_DEFAULT);
    JSP_MATCH(':');
    JSP_SAVE_EXECUTE();
    if (!executeDefault) jspSetNoExecute();
    else execInfo.execute |= EXEC_IN_SWITCH;
    while (!JSP_SHOULDNT_PARSE && lex->tk!=LEX_EOF && lex->tk!='}')
      jsvUnLock(jspeBlockOrStatement());
    oldExecute |= execInfo.execute & (EXEC_ERROR_MASK|EXEC_RETURN); // copy across any errors/exceptions/returns
    execInfo.execute = execInfo.execute & (JsExecFlags)~EXEC_BREAK;
    JSP_RESTORE_EXECUTE();
  }
  JSP_MATCH('}');
