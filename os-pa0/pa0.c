/**********************************************************************
 * Copyright (c) 2021-2022
 *  Sang-Hoon Kim <sanghoonkim@ajou.ac.kr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTIABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "types.h"
#include "list_head.h"

/* Queue instance */
LIST_HEAD(queue);

void enqueue(char *string);
int dequeue(char *buffer);
void dump_queue(void);

#define MAX_BUFFER 80

unsigned int seed = 0xdfcc230;

static char *generate_string(char *buffer)
{
	char *chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	int len = 1 + random() % (MAX_BUFFER - 2);
			/* +1 to prevent null string
			 * -1 to consider \0 termination char
			 */
	int i;

	for (i = 0; i < len; i++) {
		buffer[i] = chars[random() % strlen(chars)];
	}
	buffer[len] = '\0';
	return buffer;
}

int main(int argc, const char *argv[])
{
	int ret;
	char buffer[MAX_BUFFER];
	unsigned int i;

	if (argc != 1) seed = atoi(argv[1]);

	srandom(seed);

	/* Enqueue 4 values */
	for (i = 0; i < 4; i++) {
		enqueue(generate_string(buffer));
		fprintf(stderr, "%s\n", buffer);
	}
	fprintf(stderr, "\n");

	/* Dump the current queue */
	dump_queue();
	fprintf(stderr, "\n");

	/* Dequeue 3 values */
	for (i = 0; i < 3; i++) {
		memset(buffer, 0x00, MAX_BUFFER);
		dequeue(buffer);
		fprintf(stderr, "%s\n", buffer);
	}
	fprintf(stderr, "\n");

	/* Dump the current queue */
	dump_queue();
	fprintf(stderr, "\n");


	/* And so on ..... */
	for (i = 0; i < (1 << 12); i++) {
		enqueue(generate_string(buffer));
	}
	for (i = 0; i < (1 << 12) - 8; i++) {
		dequeue(buffer);
	}

	dump_queue();
	fprintf(stderr, "\n");

	/* Empty the queue by dequeuing all entries */
	i = 0;
	while ((ret = dequeue(buffer)) >= 0 && i++ < 1000) {
		fprintf(stderr, "%s\n", buffer);
		memset(buffer, 0x00, MAX_BUFFER);
	}

	return EXIT_SUCCESS;
}
