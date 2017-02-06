/*
 * stdlib_lib.h
 *
 *  Created on: 07/09/2016
 *      Author: Avell
 */

#ifndef LIBS_STDLIB_LIB_H_
#define LIBS_STDLIB_LIB_H_

double atof(const char *nptr);
int atoi(const char *nptr);
long int atol(const char *nptr);
long long int atoll(const char *nptr);
double strtod(const char * restrict nptr,char ** restrict endptr);
float strtof(const char * restrict nptr,char ** restrict endptr);
long double strtold(const char * restrict nptr,char ** restrict endptr);
long int strtol(const char * restrict nptr,char ** restrict endptr, int base);
long long int strtoll(const char * restrict nptr,char ** restrict endptr, int base);
unsigned long int strtoul(const char * restrict nptr,char ** restrict endptr, int base);
unsigned long long int strtoull(const char * restrict nptr,char ** restrict endptr, int base);
int rand(void);
void srand(unsigned int seed);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void abort(void);
int atexit(void (*func)(void));
void exit(int status);
void _Exit(int status);
char *getenv(const char *name);
int system(const char *string);
void *bsearch(const void *key, const void *base,size_t nmemb, size_t size,
int (*compar)(const void *, const void *));
void qsort(void *base, size_t nmemb, size_t size,int (*compar)(const void *, const void *));
int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);
div_t div(int numer, int denom);
ldiv_t ldiv(long int numer, long int denom);
lldiv_t lldiv(long long int numer,
long long int denom);
int mblen(const char *s, size_t n);
int mbtowc(wchar_t * restrict pwc,
const char * restrict s, size_t n);
int wctomb(char *s, wchar_t wchar);
size_t mbstowcs(wchar_t * restrict pwcs,
const char * restrict s, size_t n);
size_t wcstombs(char * restrict s,
const wchar_t * restrict pwcs, size_t n);


#endif /* LIBS_STDLIB_LIB_H_ */
