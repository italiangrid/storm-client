# Copyright (c) Istituto Nazionale di Fisica Nucleare (INFN). 2006-2010.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#
# Authors: Alberto Forti <alberto.forti@cnaf.infn.it>
#

AC_PREREQ([2.59])
AC_INIT([storm srm client], [1.6.1])
AC_CONFIG_AUX_DIR([./project])
AC_CONFIG_SRCDIR([src/clientSRM.cpp])
AM_INIT_AUTOMAKE
AC_CONFIG_MACRO_DIR([m4])

# Notices.
AC_COPYRIGHT([See LICENCE file for details])

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

# Set template config.h (required by stdsoap)
# This part should probably go in a macron in gsoap.m4 (something like AC_GSOAP_SRC)
# BEGIN:
AH_TEMPLATE(HAVE_FTIME)
AH_TEMPLATE(HAVE_GMTIME)
AH_TEMPLATE(HAVE_GMTIME_R)
AH_TEMPLATE(HAVE_GETTIMEOFDAY)
AH_TEMPLATE(HAVE_LOCALTIME_R)
AH_TEMPLATE(HAVE_MBTOWC)
AH_TEMPLATE(HAVE_STRTOF)
AH_TEMPLATE(HAVE_STRTOD)
AH_TEMPLATE(HAVE_STRTOL)
AH_TEMPLATE(HAVE_STRTOLL)
AH_TEMPLATE(HAVE_STRTOUL)
AH_TEMPLATE(HAVE_STRTOULL)
AH_TEMPLATE(HAVE_SSCANF)
AH_TEMPLATE(HAVE_WCTOMB)
AH_TEMPLATE(HAVE_TIMEGM)

# For IPv6
AH_TEMPLATE([WITH_IPV6], [For Ipv6 support])
AC_DEFINE(WITH_IPV6)

AC_CHECK_FUNC(ftime,           [AC_DEFINE(HAVE_FTIME)])
AC_CHECK_FUNC(gmtime,          [AC_DEFINE(HAVE_GMTIME)])
AC_CHECK_FUNC(gmtime_r,        [AC_DEFINE(HAVE_GMTIME_R)])
AC_CHECK_FUNC(gettimeofday,    [AC_DEFINE(HAVE_GETTIMEOFDAY)])
AC_CHECK_FUNC(localtime_r,     [AC_DEFINE(HAVE_LOCALTIME_R)])
AC_CHECK_FUNC(mbtowc,          [AC_DEFINE(HAVE_MBTOWC)])
AC_CHECK_FUNC(strtof,          [AC_DEFINE(HAVE_STRTOF)])
AC_CHECK_FUNC(strtod,          [AC_DEFINE(HAVE_STRTOD)])
AC_CHECK_FUNC(strtol,          [AC_DEFINE(HAVE_STRTOL)])
AC_CHECK_FUNC(strtoll,         [AC_DEFINE(HAVE_STRTOLL)])
AC_CHECK_FUNC(strtoul,         [AC_DEFINE(HAVE_STRTOUL)])
AC_CHECK_FUNC(strtoull,        [AC_DEFINE(HAVE_STRTOULL)])
AC_CHECK_FUNC(sscanf,          [AC_DEFINE(HAVE_SSCANF)])
AC_CHECK_FUNC(wctomb,          [AC_DEFINE(HAVE_WCTOMB)])
AC_CHECK_FUNC(timegm,          [AC_DEFINE(HAVE_TIMEGM)])
#:END

AC_CHECK_FUNCS([memmove memset mkdir putenv rmdir strcasecmp strchr strdup strerror strncasecmp strrchr strstr strtol])

AC_SUBST([STORM_CLIENT_ARCH], [$host_cpu])

dnl this macro is used to get the arguments supplied
dnl to the configure script (./configure --enable-debug)
dnl Check if we have enable debug support.
AC_MSG_CHECKING(whether to enable debugging)
default="no"
DEBUG=
AC_ARG_ENABLE(debug, [  --enable-debug=[no/yes] turn on debugging
                       [default=$default]],, enable_debug=$default)
if test "x$enable_debug" = "xyes"; then
   CXXFLAGS="-g -O0"
   CFLAGS="-g -O0"
   AC_MSG_RESULT(yes)
else
   CXXFLAGS="-g -O2"
   CFLAGS="-g -O2"
   AC_MSG_RESULT(no)
fi

AC_MSG_CHECKING(whether to enable walling)
wall="no"
DEBUG=
AC_ARG_ENABLE(wall, [  --enable-wall=[no/yes] turn on debugging
                       [wall=$default]],, enable_wall=$default)
if test "x$enable_wall" = "xyes"; then
   CXXFLAGS="$CXXFLAGS -Wall"
   CFLAGS="$CFLAGS -Wall"
   AC_MSG_RESULT(yes)
else
   CXXFLAGS="$CXXFLAGS"
   CFLAGS="$CFLAGS"
   AC_MSG_RESULT(no)
fi

AC_STORM([])
AC_STORM_CLIENT([])

have_globus=no

AC_GLOBUS([], have_globus=yes, have_globus=no)
AC_MSG_RESULT(["GLOBUS found $have_globus"])

AC_VOMS([])
AC_CGSI_GSOAP([])
AC_GSOAP([])

AM_CONFIG_HEADER([src/autogen/config.h])
AC_CONFIG_FILES([Makefile])

AC_CONFIG_FILES([wsdl/Makefile])
AC_CONFIG_FILES([src/clients_version.h])
AC_CONFIG_FILES([src/Makefile])

AC_OUTPUT
