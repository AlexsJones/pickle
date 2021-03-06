/*
 * =====================================================================================
 *
 *       Filename:  compile.h
 *
 *    Description:  compiles test files 
 *
 *        Version:  1.0
 *        Created:  11/15/13 18:39:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  jonesax@hush.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __COMPILE_H__
#define __COMPILE_H__
#define REF_FILE_EXT "pickled"
#define COMPILER "gcc"
#define DEBUG_FLAGS " -g -lm "
int compile_test(char *fpath);
#endif
