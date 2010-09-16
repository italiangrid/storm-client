#
#    Licensed under the Apache License, Version 2.0 (the "License");
#    you may not use this file except in compliance with the License.
#    You may obtain a copy of the License at
#
#        http://www.apache.org/licenses/LICENSE-2.0
#
#    Unless required by applicable law or agreed to in writing, software
#    distributed under the License is distributed on an "AS IS" BASIS,
#    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#
#    See the License for the specific language governing permissions and
#    limitations under the License.
#

MTCCFLAGS = -DCTHREAD_LINUX -D_THREAD_SAFE -D_REENTRANT

GENERATED_GSOAP_INCLUDES = $(top_builddir)/wsdl/@GSOAP_GENERATED_CODE_DIR_NAME@

bin_PROGRAMS = clientSRM

noinst_LTLIBRARIES = libstormclients.la

clientSRM_SOURCES = clientSRM.cpp
clientSRM_LDADD = -lstormclients \
  @GLITE_LDFLAGS@ \
  @VOMS_LIBS@ \
  @CGSI_VOMS_GSOAP_PTHR_LIBS@ \
  @GLOBUS_GSS_THR_LIBS@ \
  -lz -lm  

clientSRM_DEPENDENCIES = libstormclients.la

noinst_INCLUDES = \
  $(GENERATED_GSOAP_INCLUDES)/srm.v2.2.h \
  $(GENERATED_GSOAP_INCLUDES)/srmv2H.h \
  $(GENERATED_GSOAP_INCLUDES)/srmv2Stub.h
    
libstormclients_la_SOURCES = \
    storm_util.cpp storm_util.hpp soap_util.hpp \
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
    SRM_Client_Common.hpp SRM_Service.hpp SRM_Client_All.hpp \
    srmv2C.c \
    srmv2Client.c \
    stdsoap2.c \
    $(noinst_INCLUDES)

INCLUDES = -I$(GENERATED_GSOAP_INCLUDES) \
    @GLITE_CFLAGS@/glite/security/voms \
    @GLOBUS_THR_CFLAGS@ \
    @STORM_CLIENT_CFLAGS@ \
    @CGSI_GSOAP_CFLAGS@ \
    @GSOAP_CFLAGS@ \
    $(MTC_CFLAGS)

MAINTAINERCLEANFILES = Makefile.in \
    stdsoap2.c \
    srmv2C.c \
    srmv2Client.c

stdsoap2.c:
	@echo "Copying file \"stdsoap2.c\" from $(@GSOAP_LOCATION@)"
	/bin/cp @GSOAP_STDSOAP2_LOCATION@/stdsoap2.c .

srmv2C.c:
	@echo "Copying file \"srmv2C.c\" from $(GENERATED_GSOAP_INCLUDES)"
	/bin/cp $(GENERATED_GSOAP_INCLUDES)/srmv2C.c .

srmv2Client.c:
	@echo "Copying file \"srmv2Server.c\" from $(GENERATED_GSOAP_INCLUDES)"
	/bin/cp $(GENERATED_GSOAP_INCLUDES)/srmv2Client.c .

distclean-local:
	rm -f stdsoap2.c srmv2C.c srmv2Client.c
