dnl Copyright (C) 2009-2013 by Carnegie Mellon University.
dnl
dnl @OPENSOURCE_HEADER_START@
dnl
dnl Use of the SILK system and related source code is subject to the terms
dnl of the following licenses:
dnl
dnl GNU Public License (GPL) Rights pursuant to Version 2, June 1991
dnl Government Purpose License Rights (GPLR) pursuant to DFARS 252.227.7013
dnl
dnl NO WARRANTY
dnl
dnl ANY INFORMATION, MATERIALS, SERVICES, INTELLECTUAL PROPERTY OR OTHER
dnl PROPERTY OR RIGHTS GRANTED OR PROVIDED BY CARNEGIE MELLON UNIVERSITY
dnl PURSUANT TO THIS LICENSE (HEREINAFTER THE "DELIVERABLES") ARE ON AN
dnl "AS-IS" BASIS. CARNEGIE MELLON UNIVERSITY MAKES NO WARRANTIES OF ANY
dnl KIND, EITHER EXPRESS OR IMPLIED AS TO ANY MATTER INCLUDING, BUT NOT
dnl LIMITED TO, WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE,
dnl MERCHANTABILITY, INFORMATIONAL CONTENT, NONINFRINGEMENT, OR ERROR-FREE
dnl OPERATION. CARNEGIE MELLON UNIVERSITY SHALL NOT BE LIABLE FOR INDIRECT,
dnl SPECIAL OR CONSEQUENTIAL DAMAGES, SUCH AS LOSS OF PROFITS OR INABILITY
dnl TO USE SAID INTELLECTUAL PROPERTY, UNDER THIS LICENSE, REGARDLESS OF
dnl WHETHER SUCH PARTY WAS AWARE OF THE POSSIBILITY OF SUCH DAMAGES.
dnl LICENSEE AGREES THAT IT WILL NOT MAKE ANY WARRANTY ON BEHALF OF
dnl CARNEGIE MELLON UNIVERSITY, EXPRESS OR IMPLIED, TO ANY PERSON
dnl CONCERNING THE APPLICATION OF OR THE RESULTS TO BE OBTAINED WITH THE
dnl DELIVERABLES UNDER THIS LICENSE.
dnl
dnl Licensee hereby agrees to defend, indemnify, and hold harmless Carnegie
dnl Mellon University, its trustees, officers, employees, and agents from
dnl all claims or demands made against them (and any related losses,
dnl expenses, or attorney's fees) arising out of, or relating to Licensee's
dnl and/or its sub licensees' negligent use or willful misuse of or
dnl negligent conduct or willful misconduct regarding the Software,
dnl facilities, or other rights or assistance granted by Carnegie Mellon
dnl University under this License, including, but not limited to, any
dnl claims of product liability, personal injury, death, damage to
dnl property, or violation of any laws or regulations.
dnl
dnl Carnegie Mellon University Software Engineering Institute authored
dnl documents are sponsored by the U.S. Department of Defense under
dnl Contract FA8721-05-C-0003. Carnegie Mellon University retains
dnl copyrights in all material produced under this contract. The U.S.
dnl Government retains a non-exclusive, royalty-free license to publish or
dnl reproduce these documents, or allow others to do so, for U.S.
dnl Government purposes only pursuant to the copyright license under the
dnl contract clause at 252.227.7013.
dnl
dnl @OPENSOURCE_HEADER_END@

dnl RCSIDENT("$Id$")

# ---------------------------------------------------------------------------
# AC_OPT_WITH_SILK
#
#    Find the SILK library and header files.  Will exit configure if
#    they cannot be found
#
#    Modifies CFLAGS, LIBS
#
AC_DEFUN([AC_OPT_WITH_SILK],[
    # Need to store the flags for SiLK in the spec file
    AC_SUBST(RPM_CONFIG_SILK_FLAGS)
    RPM_CONFIG_SILK_FLAGS=

    AC_ARG_WITH([silk-config],[AS_HELP_STRING([--with-silk-config=CONFIG_PROG],
            [find SiLK configuration program at CONFIG_PROG [silk_config]. The silk_config program is available in SiLK 2.2.0 and later.  If using SiLK 2.1.0, you must specify --with-silk-ldflags, --with-silk-cflags, and maybe --with-silk-prefix])],[
        if test "x$withval" != "xyes"
        then
            silk_config="$withval"
            RPM_CONFIG_SILK_FLAGS=$RPM_CONFIG_SILK_FLAGS" --with-silk-config='$withval'"
        fi
    ])

    AC_ARG_WITH([silk-ldflags],[AS_HELP_STRING([--with-silk-ldflags=DIR],
            [specify any libraries and/or linker flags required by SiLK.  These can be found in the LDFLAGS and LIBS values in the silk-summary.txt file in SiLK's build directory.  Not required if the silk_config application exists.])],[
        if test "x$withval" != "xyes"
        then
            silk_ldflags="$withval"
            RPM_CONFIG_SILK_FLAGS=$RPM_CONFIG_SILK_FLAGS" --with-silk-ldflags='$withval'"
        fi
    ])

    AC_ARG_WITH([silk-cflags],[AS_HELP_STRING([--with-silk-cflags=DIR],
            [specify any include directories and compiler flags required by SiLK.  These can be found in the CFLAGS value in the silk-summary.txt file in SiLK's build directory.  Not required if the silk_config application exists.])],[
        if test "x$withval" != "xyes"
        then
            silk_cflags="$withval"
            RPM_CONFIG_SILK_FLAGS=$RPM_CONFIG_SILK_FLAGS" --with-silk-cflags='$withval'"
        fi
    ])

    AC_ARG_WITH([silk-prefix],[AS_HELP_STRING([--with-silk-prefix=DIR],
            [specify the prefix where SiLK was installed.  Not required if the silk_config application exists.])],[
        if test "x$withval" != "xyes"
        then
            silk_prefix="$withval"
            RPM_CONFIG_SILK_FLAGS=$RPM_CONFIG_SILK_FLAGS" --with-silk-prefix='$withval'"
        fi
    ])

    if test "x$PATH_SEPARATOR" = "x"
    then
        PATH_SEPARATOR=:
    fi
    if test "x$silk_prefix" = "x"
    then
        mod_path="$PATH"
    else
        mod_path="$silk_prefix/bin$PATH_SEPARATOR$PATH"
    fi

    if test "x$silk_ldflags$silk_cflags" = "x"
    then
        # neither silk-ldflags nor silk-cflags was provided

        # if user did not give a location for silk_config, look for
        # silk_config on the user's $PATH (and in $silk_prefix/bin if
        # that is provided)
        if test "x$silk_config" = "x"
        then
            AC_PATH_PROG([IGNORE_SILK_CONFIG], [silk_config], [no], [$mod_path])
            silk_config=$IGNORE_SILK_CONFIG
        fi

        # if we failed to find silk_config, exit configure
        if test "x$silk_config" = "xno"
        then
            AC_MSG_ERROR([cannot find the SiLK configuration program, silk_config.  Use --with-silk-config to specify its location])
        fi
    
        # verify that we can run silk_config
        if $silk_config --version >/dev/null 2>&1
        then
            :
        else
            AC_MSG_ERROR([error invoking SiLK configuration program $silk_config])
        fi
    
        # get the output from silk_config
        SILK_CFLAGS=`$silk_config --cflags 2>/dev/null`
        SILK_LDFLAGS=`$silk_config --libsilk-thrd-libs 2>/dev/null`
    
        # strip -g -O[0-9] from SILK_CFLAGS---need to m4 quote the command
        [SILK_CFLAGS=`echo " $SILK_CFLAGS " | sed 's/ -O[0-9] / /g' | sed 's/ -g / /g'`]

        # verify that the values make sense by attempting to compile a
        # small program
        CFLAGS="$CFLAGS $SILK_CFLAGS"
        LIBS="$SILK_LDFLAGS $LIBS"

        AC_CHECK_HEADER([silk/silk.h], [test 1 = 1],
            [AC_MSG_FAILURE([cannot find SiLK header <silk/silk.h>])],
            [AC_INCLUDES_DEFAULT])
        AC_CHECK_LIB([silk], [skAppRegister], [test 1 = 1],
            [AC_MSG_FAILURE([cannot find SiLK library -lsilk])])
        AC_CHECK_LIB([silk-thrd], [skPollDirCreate], [test 1 = 1],
            [AC_MSG_FAILURE([cannot find SiLK library -lsilk-thrd])])

    else
        if test "x$silk_config" != "x"
        then
            AC_MSG_ERROR([Cannot specify --with-silk-config when also specifying --with-silk-cflags and/or --with-silk-ldflags])
        fi
        
        if test "x$silk_prefix" != "x"
        then
            SILK_CFLAGS="-I$silk_prefix/include $silk_cflags"
        fi
    
        CFLAGS="$CFLAGS $SILK_CFLAGS"

        AC_CHECK_HEADER([silk/silk.h], [test 1 = 1],
            [AC_MSG_FAILURE([cannot find SiLK header <silk/silk.h>])],
            [AC_INCLUDES_DEFAULT])

        cache_LDFLAGS="$LDFLAGS"

        if test "x$silk_prefix" != "x"
        then
            SILK_LDFLAGS="-L$silk_prefix/lib"
            LDFLAGS="$SILK_LDFLAGS $LDFLAGS"
        fi
        
	AC_CHECK_LIB([silk], [skAppRegister], [test 1 = 1],
	    [AC_MSG_FAILURE([cannot find SiLK library -lsilk])],
	    [$silk_ldflags])

	LDFLAGS="$cache_LDFLAGS"
	SILK_LDFLAGS="$SILK_LDFLAGS -lsilk $silk_ldflags"

        LIBS="$SILK_LDFLAGS $LIBS"
    fi

    AC_MSG_CHECKING([usability of SILK library and headers])
    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([
#include <silk/silk.h>
#include <silk/utils.h>
             ],[[
skstream_t *s;

skAppRegister("dummy");
skStreamOpenSilkFlow(&s, "/dev/null", SK_IO_WRITE);
skStreamWriteSilkHeader(s);
skStreamClose(s);
skStreamDestroy(&s);
skAppUnregister();
             ]])],[
        AC_MSG_RESULT([yes])],[
        AC_MSG_RESULT([no])
        AC_MSG_FAILURE([error using SiLK headers or libraries])])

    # Check for features that vary with version of SiLK
     AC_CHECK_FUNC([skipaddrV6toV4], , [AC_MSG_ERROR([SiLK was not built with IPv6 support])])
#    AC_PATH_PROGS(RWTUC, rwtuc, , [$mod_path])

])# AC_OPT_WITH_SILK


# Local Variables:
# mode:autoconf
# indent-tabs-mode:nil
# End:
