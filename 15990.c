static __always_inline void vmcs_check16(unsigned long field)
{
        BUILD_BUG_ON_MSG(__builtin_constant_p(field) && ((field) & 0x6001) == 0x2000,
			 "16-bit accessor invalid for 64-bit field");
        BUILD_BUG_ON_MSG(__builtin_constant_p(field) && ((field) & 0x6001) == 0x2001,
			 "16-bit accessor invalid for 64-bit high field");
        BUILD_BUG_ON_MSG(__builtin_constant_p(field) && ((field) & 0x6000) == 0x4000,
			 "16-bit accessor invalid for 32-bit high field");
        BUILD_BUG_ON_MSG(__builtin_constant_p(field) && ((field) & 0x6000) == 0x6000,
			 "16-bit accessor invalid for natural width field");
}
