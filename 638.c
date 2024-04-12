static void lex_save(lex_t *lex, int c)
{
    strbuffer_append_byte(&lex->saved_text, c);
}
