read_header_name(uschar *name, int max, uschar *s)
{
int prelen = Ustrchr(name, '_') - name + 1;
int ptr = Ustrlen(name) - prelen;
if (ptr > 0) memmove(name, name+prelen, ptr);
while (mac_isgraph(*s) && *s != ':')
  {
  if (ptr < max-1) name[ptr++] = *s;
  s++;
  }
if (*s == ':') s++;
name[ptr++] = ':';
name[ptr] = 0;
return s;
}
