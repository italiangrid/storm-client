# $Id$
#*********************************************************************
#*
#* Author: Alberto Forti <alberto.forti@cnaf.infn.it>
#*
#* INFN-CNAF
#*
#* Date: Dec 2006
#*
#*********************************************************************

MTCCFLAGS = -DCTHREAD_LINUX -D_THREAD_SAFE -D_REENTRANT

SOAPFILES = srmv2H.h srmv2Stub.h srmv2C.c srmv2Server.c srmv2Client.c srmSoapBinding.nsmap

MAINTAINERCLEANFILES = Makefile.in $(SOAPFILES) stdsoap2.c
TOCLEAN = $(SOAPFILES) srm.v2.2.h *.res.xml *.req.xml stdsoap2.c

EXTRA_DIST = srm.v2.2.wsdl typemap.dat

INCLUDES = -I. @GSOAPGSI_CFLAGS@ \
           -I@GSOAP_DIR@ \
           -I@GSOAPGSI_DIR@/include \
           -DSTORMCONFIG=\"$(STORMCONFIG)\" \
           -DLOGFILE=\"$(LOGFILE)\" \
           $(MTCCFLAGS)

bin_PROGRAMS = clientSRM

clientSRM_SOURCES = storm_util.cpp storm_util.hpp soap_util.hpp \
                    SRM_Client_Ping.cpp SRM_Client_Ping.hpp \
                    SRM_Client_GetTransferProtocols.cpp SRM_Client_GetTransferProtocols.hpp \
                    SRM_Client_Mkdir.cpp SRM_Client_Mkdir.hpp \
                    SRM_Client_Rmdir.cpp SRM_Client_Rmdir.hpp \
                    SRM_Client_Rm.cpp SRM_Client_Rm.hpp \
                    SRM_Client_Ls.cpp SRM_Client_Ls.hpp \
                    SRM_Client_Mv.cpp SRM_Client_Mv.hpp \
                    SRM_Client_Copy.cpp SRM_Client_Copy.hpp \
                    SRM_Client_PtG.cpp SRM_Client_PtG.hpp \
                    SRM_Client_PtP.cpp SRM_Client_PtP.hpp \
                    SRM_Client_ReleaseFiles.cpp SRM_Client_ReleaseFiles.hpp \
                    SRM_Client_StatusPtP.cpp SRM_Client_StatusPtP.hpp \
                    SRM_Client_StatusPtG.cpp SRM_Client_StatusPtG.hpp \
                    SRM_Client_StatusCopy.cpp SRM_Client_StatusCopy.hpp \
                    SRM_Client_GetRequestTokens.cpp SRM_Client_GetRequestTokens.hpp \
                    SRM_Client_GetRequestSummary.cpp SRM_Client_GetRequestSummary.hpp \
                    SRM_Client_ExtendFileLifeTime.cpp SRM_Client_ExtendFileLifeTime.hpp \
                    SRM_Client_AbortRequest.cpp SRM_Client_AbortRequest.hpp \
                    SRM_Client_AbortFiles.cpp SRM_Client_AbortFiles.hpp \
                    SRM_Client_ReserveSpace.cpp SRM_Client_ReserveSpace.hpp \
                    SRM_Client_GetSpaceMetaData.cpp SRM_Client_GetSpaceMetaData.hpp \
                    SRM_Client_PutDone.cpp SRM_Client_PutDone.hpp \
                    SRM_Client_ReleaseSpace.cpp SRM_Client_ReleaseSpace.hpp \
                    SRM_Client_GetSpaceTokens.cpp SRM_Client_GetSpaceTokens.hpp \
                    SRM_Client_BOL.cpp SRM_Client_BOL.hpp \
                    SRM_Client_StatusBOL.cpp SRM_Client_StatusBOL.hpp \
                    SRM_Client_Common.hpp SRM_Service.hpp SRM_Client_All.hpp clientSRM.cpp \
                    srmv2C.c srmv2Client.c stdsoap2.c

clientSRM_LDFLAGS = @GLOBUS_LDFLAGS@ @GSOAPGSI_LDFLAGS@ @SSL_AND_CRYPTO@
clientSRM_LDADD = @GLOBUS_PKG_LIBS@ @GSOAPGSI_LDADD@ -lz -lm
#clientSRM_DEPENDENCIES = $(top_srcdir)/srmv2/libsrmv2storm.la

$(SOAPFILES): srm.v2.2.h
	@GSOAP_DIR@/soapcpp2 -c -p srmv2 srm.v2.2.h

srm.v2.2.h: srm.v2.2.wsdl
	@GSOAP_DIR@/wsdl2h -c -t typemap.dat srm.v2.2.wsdl

stdsoap2.c:
	@echo
	/bin/cp @GSOAP_DIR@/stdsoap2.c .

storm_util.o: $(SOAPFILES) stdsoap2.c

clean :
	/bin/rm -f $(SOAPFILES) stdsoap2.c srm.v2.2.h *.req.xml *.res.xml srmv2ClientLib.c srmv2ServerLib.c

dist-hook:
	cd $(distdir)
	for file in $(MAINTAINERCLEANFILES); do \
	    /bin/rm $(distdir)/$$file; \
	done

