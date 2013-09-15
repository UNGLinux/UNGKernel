initdir = $(DEFAULT_INIT_DIR)
init_SCRIPTS = zfs

EXTRA_DIST = \
	$(top_srcdir)/etc/init.d/zfs.in

$(init_SCRIPTS):
	-$(SED) -e 's,@bindir\@,$(bindir),g' \
		-e 's,@sbindir\@,$(sbindir),g' \
		-e 's,@udevdir\@,$(udevdir),g' \
		-e 's,@udevruledir\@,$(udevruledir),g' \
		-e 's,@sysconfdir\@,$(sysconfdir),g' \
		-e 's,@initdir\@,$(initdir),g' \
		'$@.$(DEFAULT_INIT_SCRIPT).in' >'$@'

distclean-local::
	-$(RM) $(init_SCRIPTS)
