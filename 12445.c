void jspSetException(JsVar *value) {
  JsVar *exception = jsvFindChildFromString(execInfo.hiddenRoot, JSPARSE_EXCEPTION_VAR, true);
  if (exception) {
    jsvSetValueOfName(exception, value);
    jsvUnLock(exception);
  }
  execInfo.execute = execInfo.execute | EXEC_EXCEPTION;
  if (lex) {
    JsVar *stackTrace = jsvObjectGetChild(execInfo.hiddenRoot, JSPARSE_STACKTRACE_VAR, JSV_STRING_0);
    if (stackTrace) {
      jsvAppendPrintf(stackTrace, " at ");
      jspAppendStackTrace(stackTrace);
      jsvUnLock(stackTrace);
      execInfo.execute = execInfo.execute | EXEC_ERROR_LINE_REPORTED;
    }
  }

}
