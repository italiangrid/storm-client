#*********************************************************************
#*
#* Authors: Alberto Forti
#*
#* CNAF-INFN
#*
#* Date: December 2006
#*
#*********************************************************************

EXTRA_DIST = clients-setup.sh clean.sh.in autogen.sh LICENSE README

MAINTAINERCLEANFILES = Makefile.in aclocal.m4 \
                       configure config.h.in \
                       stamp-h.in stamp-h1

FECLT_SPEC = storm-client.spec

SUBDIRS = src

STORM_SPEC = $(FECLT_SPEC)

RPM_SPEC_PATH=@RPM_DIR@/SPECS

rpm: $(STORM_SPEC)
	gmake -i dist; \
	/bin/mkdir -p @RPM_DIR@/SOURCES \
                      @RPM_DIR@/SPECS   \
                      @RPM_DIR@/BUILD   \
                      @RPM_DIR@/RPMS    \
                      @RPM_DIR@/SRPMS; \
	/bin/cp -u @PACKAGE@-@VERSION@.tar.gz \
                      @RPM_DIR@/SOURCES; \
	for file in  $(STORM_SPEC) ; do \
	  /bin/cp $$file $(RPM_SPEC_PATH); \
	done; \
	cd $(RPM_SPEC_PATH); \
	for file in $(STORM_SPEC) ; do \
	   /usr/bin/rpmbuild  --define "_topdir @RPM_DIR@" -ba $$file; \
	done

dist-hook:
	cd $(distdir)
	for file in $(MAINTAINERCLEANFILES); do \
	  /bin/rm -f $(distdir)/$$file; \
	done


clean-tree:
	chmod a+rx ./clean.sh
	./clean.sh

