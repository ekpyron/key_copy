/*
 * Copyright (c) 2012 Daniel Kirchner
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <keyutils.h>

int main (int argc, char *argv[])
{
	unsigned char *payload = NULL;
	long len;
	key_serial_t id;

	if (argc < 3)
	{
		fprintf (stderr, "Usage: %s [src] [dst].\n", argv[0]);
		return -1;
	}

	id = request_key ("user", argv[1], NULL, KEY_SPEC_USER_KEYRING);

	if (!id)
	{
		fprintf (stderr, "Key not found.\n");
		return -1;
	}


	len = keyctl_read_alloc (id, (void**) &payload);
	if (len < 0)
	{
		fprintf (stderr, "Cannot read key payload.\n");
		return -1;
	}

	add_key ("user", argv[2], payload, len, KEY_SPEC_USER_KEYRING);

	free (payload);

	return 0;
}
