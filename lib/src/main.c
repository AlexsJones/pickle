/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/13 07:56:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <getopt.h>
#include <jnxc_headers/jnxlist.h>
#include <jnxc_headers/jnxfile.h>
#include <jnxc_headers/jnxterm.h>
#include <unistd.h>
#include <stdio.h>
#include "filesys.h"
#define PAUSE sleep(1);
jnx_hashmap *configuration = NULL;
void title()
{
	printf("======");
	jnx_term_printf_in_color(JNX_COL_GREEN,"Pickle");
	jnx_term_default();
	printf("======\n");
}
int main(int argc, char **argv)
{
	configuration = jnx_hash_create(1024);
	jnx_hash_put(configuration,"FEATUREPATH","features");
	jnx_hash_put(configuration,"FTWDEPTH","8");
	jnx_hash_put(configuration,"STEPPATH","step_definitions");
	jnx_hash_put(configuration,"FRAMEWORK","/usr/share/pickle/framework");
	int c;
	title();
	for(c=0;c<argc;++c)
	{
		if(strcmp(argv[c],"delete") == 0)
		{
			char *sp = jnx_hash_get(configuration,"STEPPATH");
			jnx_file_recursive_delete(sp,8);
			remove(sp);
		}
		if(strcmp(argv[c],"gen") == 0)
		{ 
			filesys_steps_from_features();
			return 0;
		}
		if(strcmp(argv[c],"?") == 0 || strcmp(argv[c],"help") == 0)
		{
			printf("opts: \n");
			printf("gen - Generate new step definitions from features\n");
			printf("delete - Delete stored step definitions\n");
		}else if(argc == 1)
		{
			//pickle run
			char *path;
			if(jnx_file_mktempdir("/tmp",&path) == 0)
			{
				printf("Creating new build directory %s\n",path);
				jnx_hash_put(configuration,"BUILDPATH",path);	
				filesys_test_from_steps();
				jnx_file_recursive_delete(path,8);
				free(path);
			}else
			{
				jnx_term_printf_in_color(JNX_COL_RED,"Could not create temp build output\n");
				jnx_term_default();
			}
		}
	}
	jnx_hash_destroy(&configuration);
	return 0;
}

