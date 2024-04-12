char hexchar(int x) {
        static const char table[16] = "0123456789abcdef";

        return table[x & 15];
}
