/*-
 * Copyright (c) 2003-2012 MAEKAWA Masahide <maekawa@cvsync.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef __COLLECTION_H__
#define	__COLLECTION_H__

struct collection {
	struct collection	*cl_next;
	char			cl_name[CVSYNC_NAME_MAX + 1];
	char			cl_release[CVSYNC_NAME_MAX + 1];
	char			cl_prefix[PATH_MAX], cl_rprefix[PATH_MAX];
	size_t			cl_prefixlen, cl_rprefixlen;
	char			cl_comment[256];
	int			cl_errormode;
	bool			cl_symfollow;
	uint16_t		cl_umask;

	char			cl_dist_name[PATH_MAX + CVSYNC_NAME_MAX + 1];

	char			cl_scan_name[PATH_MAX + CVSYNC_NAME_MAX + 1];

	struct collection	*cl_super;
	char			cl_super_name[CVSYNC_NAME_MAX + 1];
};

void collection_init(struct collection *);
void collection_destroy(struct collection *);
void collection_destroy_all(struct collection *);
struct collection *collection_lookup(struct collection *, const char *,
				     const char *);
bool collection_set_default(struct collection *, const char *);

#endif /* __COLLECTION_H__ */
