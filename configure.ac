# Initialization
AC_PREREQ([2.69])
AC_INIT([phosphor-certificate-manager], [1.0], [https://github.com/openbmc/phosphor-certificate-manager/issues])
AC_LANG([C++])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for library functions
LT_INIT # Required for systemd linking

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX([17], [noext], [mandatory])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

# Check for libraries
PKG_CHECK_MODULES([PHOSPHOR_DBUS_INTERFACES], [phosphor-dbus-interfaces],,\
    AC_MSG_ERROR(["Requires phosphor-dbus-interfaces package."]))
PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus],,
    AC_MSG_ERROR(["Requires sdbusplus package."]))
PKG_CHECK_MODULES([PHOSPHOR_LOGGING], [phosphor-logging],,\
    AC_MSG_ERROR(["Requires phosphor-logging package."]))

# Code coverage
AX_CODE_COVERAGE

# Check/set gtest specific functions.
AX_PTHREAD([GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=1"],[GTEST_CPPFLAGS="-DGTEST_HAS_PTHREAD=0"])
AC_SUBST(GTEST_CPPFLAGS)

AC_ARG_ENABLE([oe-sdk],
    AS_HELP_STRING([--enable-oe-sdk], [Link testcases absolutely against OE SDK so they can be ran within it.])
)
AC_ARG_VAR(OECORE_TARGET_SYSROOT,
    [Path to the OE SDK SYSROOT])
AS_IF([test "x$enable_oe_sdk" == "xyes"],
    AS_IF([test "x$OECORE_TARGET_SYSROOT" == "x"],
          AC_MSG_ERROR([OECORE_TARGET_SYSROOT must be set with --enable-oe-sdk])
    )
    AC_MSG_NOTICE([Enabling OE-SDK at $OECORE_TARGET_SYSROOT])
    [
        testcase_flags="-Wl,-rpath,\${OECORE_TARGET_SYSROOT}/lib"
        testcase_flags="${testcase_flags} -Wl,-rpath,\${OECORE_TARGET_SYSROOT}/usr/lib"
        testcase_flags="${testcase_flags} -Wl,-dynamic-linker,`find \${OECORE_TARGET_SYSROOT}/lib/ld-*.so | sort -r -n | head -n1`"
    ]
    AC_SUBST([OESDK_TESTCASE_FLAGS], [$testcase_flags])
)
AC_ARG_VAR(BUSNAME, [The D-Bus busname to own])
AS_IF([test "x$BUSNAME" == "x"], [BUSNAME="xyz.openbmc_project.Certs.Manager"])
AC_DEFINE_UNQUOTED([BUSNAME], ["$BUSNAME"], [The D-Bus busname to own])
AC_ARG_VAR(OBJPATH, [The certificate manager D-Bus root])
AS_IF([test "x$OBJPATH" == "x"], [OBJPATH="/xyz/openbmc_project/certs"])
AC_DEFINE_UNQUOTED([OBJPATH], ["$OBJPATH"], [The certificate manager D-Bus root])

# Create configured output
AC_CONFIG_FILES([Makefile test/Makefile])
AC_OUTPUT
