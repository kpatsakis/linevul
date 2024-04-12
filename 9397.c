static void lex_save_cached(lex_t *lex)
{
    while(lex->stream.buffer[lex->stream.buffer_pos] != '\0')
    {
        lex_save(lex, lex->stream.buffer[lex->stream.buffer_pos]);
        lex->stream.buffer_pos++;
        lex->stream.position++;
    }
}
