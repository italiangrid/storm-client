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
#
# Authors: Alberto Forti <alberto.forti@cnaf.infn.it>
#

AC_PREREQ([2.59])
AC_INIT([storm srm clients], [1.4.2])
AC_CONFIG_AUX_DIR([./project])
AM_INIT_AUTOMAKE([1.6.3 subdir-objects])
AC_CONFIG_SRCDIR([src/clientSRM.cpp])

# Release number
osdist=`cat /etc/redhat-release | awk 'BEGIN {FS="release "} {print $2}'| awk 'BEGIN {FS="."} {print $1}'`
AC_SUBST([STORM_CLIENT_SO], [sl$osdist])
AC_SUBST([STORM_CLIENT_AGE_NUMBER], [4])

# Notices.
AC_COPYRIGHT([See LICENCE file for details])
AC_REVISION([$Revision: $])

#Environment.
WORKDIR=`pwd`
AC_SUBST(WORKDIR)

GSOAP_GENERATED_CODE_DIR_NAME=gsoap-generated
AC_SUBST(GSOAP_GENERATED_CODE_DIR_NAME)

DEFAULT_RPM_DIR=`pwd`

AC_PROG_CC
AC_PROG_CXX
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
AM_PROG_CC_C_O
AC_PROG_INSTALL

AC_CHECK_LIB([pthread], [main])

AC_C_CONST
AC_TYPE_SIZE_T

AC_CHECK_FUNCS([random gettimeofday ftime localtime_r timegm gmtime gmtime_r memset select socket strchr strerror strrchr strstr strtol strtoul strtoll strtoull strtold strtod strtof strtold_l strtod_l strtof_l sscanf sscanf_l sprintf_l wctomb mbtowc getenv])

AC_STORM([])
AC_STORM_CLIENT([])

have_globus=no

AC_GLOBUS([], have_globus=yes, have_globus=no)
AC_MSG_RESULT(["GLOBUS found $have_globus"])

AC_GLITE([])
AC_VOMS([])

AC_CGSI_GSOAP([2.7])
AC_GSOAP([])

if test "x$host_cpu" == "xx86_64"; then
  CGSIGSOAP_VERSION="1.3.3-1.sl5"
else
  CGSIGSOAP_VERSION="1.3.3-1.slc4"
fi

AC_SUBST(CGSIGSOAP_VERSION)

# ========================================================================
# RPM directory
# ========================================================================
AC_MSG_CHECKING([for RPM directory])
if test -z $RPMD; then
    RPMD=$DEFAULT_RPM_DIR
    RPMBD=$DEFAULT_RPM_DIR/rpm/tmp
fi
if test ! \( -d $RPMD \); then
    AC_MSG_RESULT([no such directory "$RPMD"])
fi
if test ! \( -d $RPMBD \); then
    AC_MSG_RESULT([no such directory "$RPMBD"])
fi
AC_MSG_RESULT(["$RMPD" found])
AC_MSG_RESULT(["$RMPBD" found])
AC_SUBST([RPM_DIR], [$RPMD])
AC_SUBST([RPM_BUILD_DIR], [$RPMBD])

# Installation prefix
AC_PREFIX_DEFAULT([/opt/storm/client])

# Configuration items
AM_CONFIG_HEADER([src/autogen/config.h])

dnl =========================
dnl Define required variables
dnl =========================
CFLAGS="$CFLAGS -x c++"

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([wsdl/Makefile])
AC_CONFIG_FILES([src/clients_version.h])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([storm-client.spec])

AC_OUTPUT

