void HistogramEnumerateOsArch(const std::string& sandbox_isa) {
  enum NaClOSArch {
    kNaClLinux32 = 0,
    kNaClLinux64,
    kNaClLinuxArm,
    kNaClMac32,
    kNaClMac64,
    kNaClMacArm,
    kNaClWin32,
    kNaClWin64,
    kNaClWinArm,
    kNaClOSArchMax
  };

  NaClOSArch os_arch = kNaClOSArchMax;
#if NACL_LINUX
  os_arch = kNaClLinux32;
#elif NACL_OSX
  os_arch = kNaClMac32;
#elif NACL_WINDOWS
  os_arch = kNaClWin32;
#endif

  if (sandbox_isa == "x86-64")
    os_arch = static_cast<NaClOSArch>(os_arch + 1);
  if (sandbox_isa == "arm")
    os_arch = static_cast<NaClOSArch>(os_arch + 2);

  HistogramEnumerate("NaCl.Client.OSArch", os_arch, kNaClOSArchMax, -1);
}
