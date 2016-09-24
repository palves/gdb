dnl Process this file with autoconf to produce a configure script.
AC_PREREQ(2.64)dnl
AC_INIT(Makefile.in)
sinclude(../common/acinclude.m4)
sinclude(config/ax_mpi.m4)

SIM_AC_COMMON

# For dv-rv and rvdummy.
AC_CHECK_HEADERS(sys/socket.h sys/select.h limits.h sys/param.h)

SIM_AC_OPTION_ENDIAN(LITTLE)
SIM_AC_OPTION_ALIGNMENT(STRICT_ALIGNMENT)
SIM_AC_OPTION_SCACHE(16384)
SIM_AC_OPTION_WARNINGS

# The default model shouldn't matter as long as there's a BFD.
SIM_AC_OPTION_DEFAULT_MODEL(epiphany32)
SIM_AC_OPTION_ENVIRONMENT
SIM_AC_OPTION_INLINE()
SIM_AC_OPTION_CGEN_MAINT

# Hardware support
SIM_AC_OPTION_HARDWARE(yes,"","epiphany_mem")


dnl --enable-emesh-sim
esim_enabled_cflags="-pthread -DEMESH_SIM=1 -DWITH_EMESH_SIM=1"
esim_disabled_cflags="-DEMESH_SIM=0 -DWITH_EMESH_SIM=0"

AC_ARG_ENABLE(emesh-sim,
[  --disable-emesh-sim			Disable simulation of eMesh],
[
case "x${enableval}" in
  x)    esim="yes"; esim_cflags+=" ${esim_enabled_cflags}";;
  xyes) esim="yes"; esim_cflags+=" ${esim_enabled_cflags}";;
  xno)  esim=""   ; esim_cflags+=" ${esim_disabled_cflags}";;
  *)    AC_MSG_ERROR([--enable-emesh-sim does not take a value]); ;;
esac
],
[
  esim="yes"
  esim_cflags+=" ${esim_enabled_cflags}"
]
)

if test x"${esim}" = x"yes"; then
  case "${sim_hw_cflags}" in
  *"-DWITH_HW=1"*) ;;
  *) AC_MSG_ERROR([Sorry, but --enable-emesh-sim requires that hardware \
support be enabled. Please configure with --enable-sim-hardware.]) ;;
  esac
else
  case "${sim_hw}" in
  *"epiphany_mem"*) AC_MSG_ERROR([Sorry, but --enable-sim-hardware \
(epiphany_mem) requires that eMesh support be enabled. Please configure \
with --enable-emesh-sim.]) ;;
  *) ;;
  esac
fi


esim_net_enabled_cflags="-DEMESH_NET=1 -DWITH_EMESH_NET=1"
esim_net_disabled_cflags="-DEMESH_NET=0 -DWITH_EMESH_NET=0"
AC_ARG_ENABLE(emesh-net,
[  --enable-emesh-net			Enable eMesh sim network support],
[
case "x${enableval}" in
  x)    esim_net="yes"; esim_cflags+=" ${esim_net_enabled_cflags}";;
  xyes) esim_net="yes"; esim_cflags+=" ${esim_net_enabled_cflags}";;
  xno)  esim_net=""   ; esim_cflags+=" ${esim_net_disabled_cflags}";;
  *)    AC_MSG_ERROR([--enable-emesh-net does not take a value]); ;;
esac
],
[esim_cflags+=" ${esim_net_disabled_cflags}"]
)
dnl Need MPI for esim-net
if test x"${esim_net}" = x"yes"; then
  AX_MPI(
    [],
    [AC_MSG_ERROR([MPI not found])]
  )
fi


epihany_extra_libs=
if test "x$esim" = "xyes"; then
AC_CHECK_LIB(rt, shm_open,
  [ epiphany_extra_libs+=" -lrt" ],
  [ AC_MSG_ERROR([Could not find rt]) ]
)
AC_CHECK_LIB(pthread, pthread_barrier_init,
  [ epiphany_extra_libs+=" -lpthread" ],
  [ AC_MSG_ERROR([Could not find pthread]) ]
)
AC_CHECK_LIB(e-xml, e_xml_new,
  [
    epiphany_extra_libs+=" -le-xml"
    esim_cflags+=" -DHAVE_E_XML=1"
  ],
  []
)

if test x"$silent" != x"yes"; then
  echo "Setting emesh sim cflags = ${esim_cflags}" 6>&1
  echo "Setting emesh extra libs = ${epiphany_extra_libs}" 6>&1
fi
fi

AC_SUBST(esim)
AC_SUBST(esim_net)
AC_SUBST(sim_cflags, ["${sim_cflags} ${esim_cflags}"])
AC_SUBST(epiphany_extra_libs, [${epiphany_extra_libs}])
dnl end --enable-emesh-sim


SIM_AC_OUTPUT
