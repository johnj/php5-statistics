/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2013 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: John Jawed <jawed@php.net>                                  |
  +----------------------------------------------------------------------+
*/

/* $Id: $ */

#ifndef PHP_STATISTICS_H
#define PHP_STATISTICS_H

extern zend_module_entry statistics_module_entry;
#define phpext_statistics_ptr &statistics_module_entry

#define PHP_STATS_VERSION "1.0"

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_MINIT_FUNCTION(statistics);
PHP_MINFO_FUNCTION(statistics);

#endif  /* PHP_STATISTICS_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
