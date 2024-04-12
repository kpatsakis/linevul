int ASN1_template_i2d(ASN1_VALUE **pval, unsigned char **out,
                      const ASN1_TEMPLATE *tt)
{
    return asn1_template_ex_i2d(pval, out, tt, -1, 0);
}
