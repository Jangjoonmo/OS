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

/*====================================================================*/
/*          ****** DO NOT MODIFY ANYTHING FROM THIS LINE ******       */
#include <stdio.h>
#include "types.h"
#include "list_head.h"

/* Declaration for the queue instance defined in pa0.c */
extern struct list_head queue;

/* Entry for the queue */
struct entry {
	struct list_head list;
	char *string;
};
/*          ****** DO NOT MODIFY ANYTHING ABOVE THIS LINE ******      */
/*====================================================================*/

/*====================================================================*
 * The rest of this file is all yours. This implies that you can      *
 * include any header files if you want to ...                        */

#include <stdlib.h>                    /* like this */
#include <string.h>

/**
 * enqueue()
 *
 * DESCRIPTION
 *   Enqueue @string into the @queue. The @string should be inserted into the tail
 *   of the queue. You may use either the head or tail of the list for the head.
 */
void enqueue(char *string)
{
}


/**
 * dequeue()
 *
 * DESCRIPTION
 *   Dequeue a value from @queue and return it through @buffer. The value should
 *   come from the head of the queue, and the corresponding entry should be
 *   removed from @queue.
 *
 * RETURN
 *   If the queue is not empty, dequeue the head of @queue, and return 0
 *   If the queue is empty, return -1
 */
int dequeue(char *buffer)
{
	/* TODO: Implement this function */
	return 0;
}


/**
 * dump_queue()
 *
 * DESCRIPTION
 *   Dump the contents in @queue. Print out @string of queue entries while
 *   traversing the queue from the head to the tail. Note that the value
 *   should be printed out to @stderr to get properly graded in pasubmit.
 */
void dump_queue(void)
{
	/* TODO: Implement this function */
}
