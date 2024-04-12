static void error_set(json_error_t *error, const lex_t *lex,
                      const char *msg, ...)
{
    va_list ap;
    char msg_text[JSON_ERROR_TEXT_LENGTH];
    char msg_with_context[JSON_ERROR_TEXT_LENGTH];

    int line = -1, col = -1;
    size_t pos = 0;
    const char *result = msg_text;

    if(!error)
        return;

    va_start(ap, msg);
    vsnprintf(msg_text, JSON_ERROR_TEXT_LENGTH, msg, ap);
    msg_text[JSON_ERROR_TEXT_LENGTH - 1] = '\0';
    va_end(ap);

    if(lex)
    {
        const char *saved_text = strbuffer_value(&lex->saved_text);

        line = lex->stream.line;
        col = lex->stream.column;
        pos = lex->stream.position;

        if(saved_text && saved_text[0])
        {
            if(lex->saved_text.length <= 20) {
                snprintf(msg_with_context, JSON_ERROR_TEXT_LENGTH,
                         "%s near '%s'", msg_text, saved_text);
                msg_with_context[JSON_ERROR_TEXT_LENGTH - 1] = '\0';
                result = msg_with_context;
            }
        }
        else
        {
            if(lex->stream.state == STREAM_STATE_ERROR) {
                /* No context for UTF-8 decoding errors */
                result = msg_text;
            }
            else {
                snprintf(msg_with_context, JSON_ERROR_TEXT_LENGTH,
                         "%s near end of file", msg_text);
                msg_with_context[JSON_ERROR_TEXT_LENGTH - 1] = '\0';
                result = msg_with_context;
            }
        }
    }

    jsonp_error_set(error, line, col, pos, "%s", result);
}
