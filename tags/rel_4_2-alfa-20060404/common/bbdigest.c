/*----------------------------------------------------------------------------*/
/* Hobbit monitor message digest tool.                                        */
/*                                                                            */
/* This is used to implement message digest functions (MD5, SHA1 etc.)        */
/*                                                                            */
/* Copyright (C) 2003-2005 Henrik Storner <henrik@hswn.dk>                    */
/*                                                                            */
/* This program is released under the GNU General Public License (GPL),       */
/* version 2. See the file "COPYING" for details.                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

static char rcsid[] = "$Id: bbdigest.c,v 1.2 2005-03-25 21:09:39 henrik Exp $";

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "libbbgen.h"

int main(int argc, char *argv[])
{
	FILE *fd;
	char buf[8192];
	int buflen;
	digestctx_t *ctx;

	if (argc < 2) {
		printf("Usage: %s digestmethod [filename]\n", argv[0]);
		printf("\"digestmethod\" is usually \"md5\" or \"sha1\"\n");
		printf("Refer to the openssl help for more digestmethods\n");
		return 1;
	}

	if ((ctx = digest_init(argv[1])) == NULL) {
		printf("Unknown message digest method %s\n", argv[1]);
		return 1;
	}

	if (argc > 2) fd = fopen(argv[2], "r"); else fd = stdin;

	if (fd == NULL) {
		printf("Cannot open file %s\n", argv[2]);
		return 1;
	}

	while ((buflen = fread(buf, 1, sizeof(buf), fd)) > 0) {
		digest_data(ctx, buf, buflen);
	}

	printf("%s\n", digest_done(ctx));

	return 0;
}

