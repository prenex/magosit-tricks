/*
 * Easy and simple logging single-header library for debugging: prenexlog.h
 *
 * - Created by rthier on 2016.04.11.. See: https://github.com/prenex/ObjMaster/blob/master/objmasterlog.h
 * - std redirection added on 2018.02.12 - backported because of debugging meeds for some unity projects at work
 * - Changed names to not reflect the ObjMaster project on 2020.06.15.. See: https://github.com/prenex/magosit-tricks/stblike/prenexlog.h
 *
 * Configuration: Log configuration is just done by changing the defines in this file and recompiling. It is that easy-peasy.
 * 
 * LICENCE: Modified UNLICENCE
 *   - free to use it in any closed or open source but also MagosIT Kft. and Richard Thier all rights retained
 *     for further usage in open and closed source. The code is open for anyone, but I routinely add it to closed app
 *     repos for people and companies I am working with and they do not need to keep their version fully open sourced!
 */

#ifndef PRENEX_LOG_H
#define PRENEX_LOG_H

#include <stdio.h>

/* ****** */
/* CONFIG */
/* ****** */

/* Define this if you want redirection - see code */
/* #define PLOG_REDIRECT */

/* Use this if you need to differentiate from usual printfs and couts more easily (by filtering with vim for example) */
#define PLOG_TAG "PLog::"

/* Change these according to your needs - this is just an example config if you would define NDEBUG for release builds for example */
/*
#ifdef NDEBUG
#define PLOG_REDIRECT
#define PLOG_CUSTOM_PATH
#endif // NDEBUG
*/

#define PLOG_OUTFILE "debug_out.txt"
#define PLOG_ERRFILE "debug_err.txt"
#define PLOG_WITHOUT_FLUSH_NO 5

/* **** */
/* CODE */
/* **** */

#ifdef PLOG_CUSTOM_PATH
/* The full path is generated using custom generator functions */
/* Let the linker search for these functions that the user provides */
extern const char *PlogOutfilePath();
extern const char *PlogErrfilePath();
#else
/* The path is the current path and file names are defaulted */
static inline const char *PlogOutfilePath() {
	return PLOG_OUTFILE;
}

static inline const char *PlogErrfilePath() {
	return PLOG_ERRFILE;
}
#endif /* PLOG_CUSTOM_PATH */

/*
 * Just #define this in (ONLY) one of your C++ files where you want to
 * implement PLOG_CUSTOM_PATH style functions by their default ones.
 *
 * Most useful for complex situations where you need those files for release builds - except for release build unit tests or such!
 */
#ifdef PLOG_DEFAULT_PATH_CUSTOM_IMPL
/* The path is the current path and file names are defaulted */
const char *PlogOutfilePath() {
	return PLOG_OUTFILE;
}

const char *PlogErrfilePath() {
	return PLOG_ERRFILE;
}
#endif /* PLOG_DEFAULT_PATH_CUSTOM_IMPL */

/**
 * Adds std file redirection here for your use cases if needed
 * 
 * Rem.: See example code here for one-time redirection
 * Rem.: If you enable this, you also better enable an fflush at least sometimes as seen here...
 * Rem.: This is much safer than just implementing different loggers for OMLOG* as this way random stdout and stderr gets logged too!
 */
static inline void stdredirect() {
#ifdef PLOG_REDIRECT
	/* Simple redirect for std out to support native code logging on unity projects */
	/* built for example to aid us win10 devices where things go to /dev/null otherwise... */
	static bool redirected = false;
	static int flushCounter = PLOG_WITHOUT_FLUSH_NO;
	if (!redirected) {
		/* These files should be autoclosed by the OS in this simple solution... */
		/* TODO: it might be nicer(?) to buffer stuff in memory and only open files */
		/*       to write out a whole buffer in append mode and then close that! */
		FILE *out, *err;
		freopen_s(&out, PlogOutfilePath(), "a", stdout);
		freopen_s(&err, PlogErrfilePath(), "a", stderr);
		redirected = true;
	}

	/* Ensure there are some flushing from time to time */
	if (--flushCounter < 0) {
		flushCounter = PLOG_WITHOUT_FLUSH_NO;
		fflush(stdout);
		fflush(stderr);
	}
#endif /* PLOG_REDIRECT */
}

#define  PLOGD(...) stdredirect(); fprintf(stdout, PLOG_TAG"D "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n")
#define  PLOGI(...) stdredirect(); fprintf(stdout, PLOG_TAG"I "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n")
#define  PLOGW(...) stdredirect(); fprintf(stderr, PLOG_TAG"W "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#define  PLOGE(...) stdredirect(); fprintf(stderr, PLOG_TAG"E "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")

#endif /* PRENEX_LOG_H */
