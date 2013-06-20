/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2008 The PHP Group                                |
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "math.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "zend_operators.h"

#include "php_statistics.h"

/* inverse of normal distribution ([2]) */
/* P( (-\infty, z] ) = qn -> z */
static double statistics_pnorm(double qn) {
    static double b[11] = {1.570796288,     0.03706987906,  -0.8364353589e-3,
                           -0.2250947176e-3, 0.6841218299e-5, 0.5824238515e-5,
                           -0.104527497e-5,  0.8360937017e-7,-0.3231081277e-8,
                           0.3657763036e-10,0.6936233982e-12};
	double w1, w3;
	int i;

	if(qn < 0. || 1. < qn) {
		php_error(E_WARNING, "qn <= 0 or qn >= 1 in pnorm()!");
		return 0.;
	}
	if(qn == 0.5)	return 0.;

	w1 = qn;
	if(qn > 0.5)	w1 = 1. - w1;
	w3 = -log(4. * w1 * (1. - w1));
	w1 = b[0];
	for(i = 1; i < 11; i++)	w1 += (b[i] * pow(w3, (double)i));
	if(qn > 0.5)	return sqrt(w1 * w3);
	return -sqrt(w1 * w3);
}

/* {{{ proto double statistics_pnormaldist(double q)
   Get the probability value of the normal dist */
PHP_FUNCTION(statistics_pnormaldist) {
	double num;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &num) == FAILURE) {
		return;
	}
	Z_DVAL_P(return_value) = statistics_pnorm(num);
	Z_TYPE_P(return_value) = IS_DOUBLE;
}
/* }}} */

/* {{{ proto double statistics_wilson_ci_lb(int positives, int total, float power)
   Get the lower bound of Wilson score confidence interval */
PHP_FUNCTION(statistics_wilson_ci_lb) {
	ulong positives;
	ulong total;
	double power, z, phat;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lld", &positives, &total, &power) == FAILURE) {
		return;
	}

	if(!total) {
		RETURN_LONG(0);
	}

	z = statistics_pnorm(1-power/2);
	phat = (1.0*positives)/total;
	
	Z_DVAL_P(return_value) = (phat + z*z/(2*total) - z * sqrt((phat*(1-phat)+z*z/(4*total))/total))/(1+z*z/total);
	Z_TYPE_P(return_value) = IS_DOUBLE;
}
/* }}} */

PHP_MINIT_FUNCTION(statistics) {
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(statistics) {
	return SUCCESS;
}

PHP_MINFO_FUNCTION(statistics) 
{
	php_info_print_table_start();
	php_info_print_table_row(2, "version", PHP_STATS_VERSION);
	php_info_print_table_end();
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_statistics_pnormaldist, 0, 0, 1)
	ZEND_ARG_INFO(0, q)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_statistics_wilson_ci_lb, 0, 0, 3)
	ZEND_ARG_INFO(0, positives)
	ZEND_ARG_INFO(0, total)
	ZEND_ARG_INFO(0, power)
ZEND_END_ARG_INFO()

zend_function_entry statistics_functions[] = { 
	PHP_FE(statistics_pnormaldist,		arginfo_statistics_pnormaldist)
	PHP_FE(statistics_wilson_ci_lb,		arginfo_statistics_wilson_ci_lb)
	{ NULL, NULL, NULL }
};

zend_module_entry statistics_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	NULL,
	"statistics",
	statistics_functions,
	PHP_MINIT(statistics),
	PHP_MSHUTDOWN(statistics),
	NULL,
	NULL,
	PHP_MINFO(statistics),
	PHP_STATS_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_STATISTICS
ZEND_GET_MODULE(statistics)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
