/*
 * Macros for test result reporting.
 *
 * These can be used anyhwere, assuming there is a local variable 'errors'
 * and a global variable 'ErrorCount'.
 */

#include <stdlib.h>
#include <stdio.h>

static int ErrorCount = 0;
static int WarningCount = 0;

// the default output stream (usually 'stderr')
#define OUTSTREAM stderr
#define O OUTSTREAM

// colored text output (if it is available)
#define COLOR_RED fprintf(OUTSTREAM, "")
#define COLOR_GREEN fprintf(OUTSTREAM, "")
#define COLOR_BLUE fprintf(OUTSTREAM, "")
#define COLOR_YELLOW fprintf(OUTSTREAM, "")

#define COLOR_DARK fprintf(OUTSTREAM, "")

#define COLOR_DEFAULT fprintf(OUTSTREAM, "")

#define MSG_LINE_NUM(M)
  //  { fprintf(OUTSTREAM, "%s", M);		
  //  COLOR_DARK;				
  //  fprintf(OUTSTREAM, "[%d] ", __LINE__);	
  //  COLOR_DEFAULT;}

#define MSG(M)\
  { fprintf(OUTSTREAM, "%s", M);\
    COLOR_DEFAULT;}

//    fprintf(OUTSTREAM, "[%s:%d] ", __FILE__, __LINE__); 


#define RED_MSG(M)    {COLOR_RED;    MSG_LINE_NUM(M); COLOR_DEFAULT; }
#define GREEN_MSG(M)  {COLOR_GREEN;  MSG(M); COLOR_DEFAULT; }
#define BLUE_MSG(M)   {COLOR_BLUE;   MSG(M); COLOR_DEFAULT; }
#define YELLOW_MSG(M) {COLOR_YELLOW; MSG_LINE_NUM(M); COLOR_DEFAULT; }


// default warning and error messages, should they be needed

#define WARN(M) \
  {WarningCount++; warnings++;\
   YELLOW_MSG("WARNING: ");\
   fprintf(OUTSTREAM, "%s\n", M);}
#define ERR(M) {ErrorCount++; errors++; RED_MSG("ERROR: "); fprintf(OUTSTREAM, "%s\n", M);}

// default error with exit
#define DIE(M) {RED_MSG("EXITING: "); fprintf(OUTSTREAM, "%s\n", M);}

// macros to signal an error or warning in a test.
#define ERROR(X) {ErrorCount++; errors++; RED_MSG("ERROR: "); X;}
#define WARNING(X) {WarningCount++; warnings++; YELLOW_MSG("WARNING: "); X;}

// macro to define local variables and such
#define STD_TEST(N)\
  int errors = 0;\
  int warnings = 0;\
  int count = 0;\
  char *name = N;


// macro to start a test
#define START_TEST(N) \
  errors = 0; count = 0; warnings = 0;\
  fprintf(OUTSTREAM, "Starting test \"%s\"...\n", N);


// macro to end a specific test.
// (ordinarily there is only one test battery per function, but that is
// not enforced; 'errors' should be reset though, before another test battery
// is started in a given function


#define FINISH_TEST(N)\
  if (errors) {\
    RED_MSG("TEST FAILURE:  "); \
    fprintf(OUTSTREAM, "(%s) %d error%s in %d trial%s\n", N, errors,\
                     errors == 1 ? "" : "s", count, count == 1 ? "" : "s");}\
  else { \
    GREEN_MSG("Test Passed:  "); \
    fprintf(OUTSTREAM, "(%s) 0 errors in %d trial%s\n\n", N,\
	    count, count == 1 ? "" : "s");\
  if (WarningCount || ErrorCount); } // (to prevent "unused variable" warnings)


/*************************/
/* Some Static Functions */
/*************************/

#ifdef __cplusplus
static inline double randomf( const double x0 = 0, const double x1 = 1 )
{
  double s = drand48();
  return((1 - s)*x0 + s*x1);
}

static inline double randomf_nz( const double x0 = 0, const double x1 = 1 )
{
  double s;
  do {
    s = drand48();
    s = ((1 - s)*x0 + s*x1);
  } while (s == 0.0);
  return(s);
}

static inline int random_int( const int n1 = 2 )
{
  return(int(drand48()*n1));
}

static inline int random_int( const int n0, const int n1 )
{
  return(int(n0 + drand48()*(n1 - n0)));
}

static inline int random_sign()
{
  return(drand48() < 0.5 ? -1 : 1);
}

#endif
