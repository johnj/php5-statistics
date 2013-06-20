dnl
dnl $Id: $
dnl

PHP_ARG_WITH(statistics, for statistics support,
[  --with-statistics		Include statistics support])

if test "$PHP_STATISTICS" != "no"; then
  PHP_SUBST(STATISTICS_SHARED_LIBADD)

  PHP_NEW_EXTENSION(statistics, statistics.c, $ext_shared)
  CFLAGS="$CFLAGS -Wall -g -DCOMPILE_DL_STATISTICS"
fi
