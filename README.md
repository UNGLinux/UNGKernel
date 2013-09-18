UNGKernel
=========
The UNG/Linux kernel is a fork of the Linux kernel with native zfs support and the ability to compile with clang. Since being forked about 2 million lines have been changed, though we attempt to keep it working with Linux patches. While this usually works, sometimes a patch targets a specific legacy architecture the UNGKernel does not support or easily with one of our other differences.

Linux Support
=========

The UNGKernel varies in a couple of ways from the Linux kernel, from generally less support with other architectures to a stronger focus on working with BSD and other Unix platforms.

The Linux kernel officially supports alpha, arc, arm, arm64, avr32, blackfin, c6x, cris, frv, h8300, hexagon, ia64, m32r, m68k, metag, microblaze, mips, mn10300, openrisc, parisc, powerpc, s390, score, sh, sparc, tile, um, unicore32, x86, and xtensa

We officially support Arm, Arm64, mips, x86, and x86_64

Why? First off they don't build with clang. Second, we're not maintaining UNG for those other platforms, and finally it lets us take advantage of things not used due to support with those other weird platforms. An example is unaligned memory access, bad for most of the above platforms, it cuts kernel decompression time in half.

Our anti GNU nature does have a couple problems, not everything builds with clang.

Our solution? build them as kernel modules under gcc, untill we can get whatever the issue working.
