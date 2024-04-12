static void cfundecs(JF, js_Ast *list)
{
	while (list) {
		js_Ast *stm = list->a;
		if (stm->type == AST_FUNDEC) {
			emitline(J, F, stm);
			emitfunction(J, F, newfun(J, stm->line, stm->a, stm->b, stm->c, 0, F->strict));
			emitline(J, F, stm);
			emit(J, F, OP_SETLOCAL);
			emitarg(J, F, addlocal(J, F, stm->a, 0));
			emit(J, F, OP_POP);
		}
		list = list->b;
	}
}
