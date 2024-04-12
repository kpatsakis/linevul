NO_INLINE bool jspeParseFunctionCallBrackets() {
  assert(!JSP_SHOULD_EXECUTE);
  JSP_MATCH('(');
  while (!JSP_SHOULDNT_PARSE && lex->tk != ')') {
    jsvUnLock(jspeAssignmentExpression());
#ifndef SAVE_ON_FLASH
    if (lex->tk==LEX_ARROW_FUNCTION) {
      jsvUnLock(jspeArrowFunction(0, 0));
    }
#endif
    if (lex->tk!=')') JSP_MATCH(',');
  }
  if (!JSP_SHOULDNT_PARSE) JSP_MATCH(')');
  return 0;
}
