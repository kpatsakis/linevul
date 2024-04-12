chash_start(int type, void *base)
{
if (type == HMAC_MD5)
  md5_start((md5 *)base);
else
  sha1_start((sha1 *)base);
}
