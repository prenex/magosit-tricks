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

/* Change these according to your needs (if you are using std redirection as in the example below) */
#define PLOG_OUTFILE "debug_out.txt"
#define PLOG_ERRFILE "debug_err.txt"
#define PLOG_WITHOUT_FLUSH_NO 5

/* **** */
/* CODE */
/* **** */

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
	static int flushCounter = __WITHOUT_FLUSH_NO;
	if (!redirected) {
		/* These files should be autoclosed by the OS in this simple solution... */
		/* TODO: it might be nicer(?) to buffer stuff in memory and only open files */
		/*       to write out a whole buffer in append mode and then close that! */
		FILE *out, *err;
		freopen_s(&out, PLOG_OUTFILE, "a", stdout);
		freopen_s(&err, PLOG_ERRFILE, "a", stderr);
		redirected = true;
	}

	/* Ensure there are some flushing from time to time */
	if (--flushCounter < 0) {
		flushCounter = __WITHOUT_FLUSH_NO;
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
