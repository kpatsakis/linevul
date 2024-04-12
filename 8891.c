IHEVCD_ERROR_T ihevcd_parse_user_data_registered_itu_t_t35(codec_t *ps_codec,
                                                           UWORD32 u4_payload_size)
{
 parse_ctxt_t *ps_parse = &ps_codec->s_parse;
 bitstrm_t *ps_bitstrm = &ps_parse->s_bitstrm;
    UWORD32 value;
 user_data_registered_itu_t_t35_t *ps_user_data_registered_itu_t_t35;
    UWORD32 i;
    UWORD32 j = 0;

    ps_parse->s_sei_params.i1_user_data_registered_present_flag = 1;
    ps_user_data_registered_itu_t_t35 =
 &ps_parse->s_sei_params.as_user_data_registered_itu_t_t35[ps_parse->s_sei_params.i4_sei_user_data_cnt];
    ps_parse->s_sei_params.i4_sei_user_data_cnt++;

    ps_user_data_registered_itu_t_t35->i4_payload_size = u4_payload_size;

 if(u4_payload_size > MAX_USERDATA_PAYLOAD)
 {
        u4_payload_size = MAX_USERDATA_PAYLOAD;
 }

    ps_user_data_registered_itu_t_t35->i4_valid_payload_size = u4_payload_size;

    BITS_PARSE("itu_t_t35_country_code", value, ps_bitstrm, 8);
    ps_user_data_registered_itu_t_t35->u1_itu_t_t35_country_code = value;

 if(0xFF != ps_user_data_registered_itu_t_t35->u1_itu_t_t35_country_code)
 {
        i = 1;
 }
 else
 {
        BITS_PARSE("itu_t_t35_country_code_extension_byte", value, ps_bitstrm,
 8);
        ps_user_data_registered_itu_t_t35->u1_itu_t_t35_country_code_extension_byte =
                        value;

        i = 2;
 }

 do
 {
        BITS_PARSE("itu_t_t35_payload_byte", value, ps_bitstrm, 8);
        ps_user_data_registered_itu_t_t35->u1_itu_t_t35_payload_byte[j++] =
                        value;

        i++;
 }while(i < u4_payload_size);

 return (IHEVCD_ERROR_T)IHEVCD_SUCCESS;
}
