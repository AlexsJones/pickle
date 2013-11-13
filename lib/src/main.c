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
#include <stdio.h>
#include "filesys.h"
#define CONFIGURATION "lib/conf/settings.conf"
jnx_hashmap *configuration = NULL;
void usage()
{
	printf("Required valid conf/settings.conf to exist with pickle configuration\n");
}
jnx_hashmap* process_configuration(char* configuration_path)
{
    jnx_file_kvp_node* head = jnx_file_read_keyvaluepairs(configuration_path, "=");
    if (!head) {
        usage();
    }
    jnx_hashmap* conf_hash = jnx_hash_init(1024);
    while (head) {
        jnx_hash_put(conf_hash, head->key, head->value);
        jnx_file_kvp_node* current = head;
        head = head->next;
        free(current);
    }
    return conf_hash;
}
int main(int argc, char **argv)
{
	int i,c;

	configuration = process_configuration(CONFIGURATION);

	while((i = getopt(argc,argv,"g")) != -1)
	{
		switch(i)
		{
			case 'g':
				printf("Generating step definition templates\n");
	
				filesys_steps_from_features();
	
				break;
		}
	}

	/*  
	jnx_list *h;
	if((h= parse_file_to_data(optarg)) == NULL)
	{
		return 1;
	}
	scribe_new(h);
*/


	return 0;
}

