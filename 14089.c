print_optimize_info(FILE* f, regex_t* reg)
{
  static const char* on[] = { "NONE", "STR",
                              "STR_FAST", "STR_FAST_STEP_FORWARD",
                              "STR_CASE_FOLD_FAST", "STR_CASE_FOLD", "MAP" };

  fprintf(f, "optimize: %s\n", on[reg->optimize]);
  fprintf(f, "  anchor: "); print_anchor(f, reg->anchor);
  if ((reg->anchor & ANCR_END_BUF_MASK) != 0)
    print_distance_range(f, reg->anchor_dmin, reg->anchor_dmax);
  fprintf(f, "\n");

  if (reg->optimize) {
    fprintf(f, "  sub anchor: "); print_anchor(f, reg->sub_anchor);
    fprintf(f, "\n");
  }
  fprintf(f, "\n");

  if (reg->exact) {
    UChar *p;
    fprintf(f, "exact: [");
    for (p = reg->exact; p < reg->exact_end; p++) {
      fputc(*p, f);
    }
    fprintf(f, "]: length: %ld\n", (reg->exact_end - reg->exact));
  }
  else if (reg->optimize & OPTIMIZE_MAP) {
    int c, i, n = 0;

    for (i = 0; i < CHAR_MAP_SIZE; i++)
      if (reg->map[i]) n++;

    fprintf(f, "map: n=%d\n", n);
    if (n > 0) {
      c = 0;
      fputc('[', f);
      for (i = 0; i < CHAR_MAP_SIZE; i++) {
        if (reg->map[i] != 0) {
          if (c > 0)  fputs(", ", f);
          c++;
          if (ONIGENC_MBC_MAXLEN(reg->enc) == 1 &&
              ONIGENC_IS_CODE_PRINT(reg->enc, (OnigCodePoint )i))
            fputc(i, f);
          else
            fprintf(f, "%d", i);
        }
      }
      fprintf(f, "]\n");
    }
  }
}
