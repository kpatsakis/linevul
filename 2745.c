JSObject* throwSyntaxError(ExecState* exec)
{
    return throwError(exec, createSyntaxError(exec, "Syntax error"));
}
