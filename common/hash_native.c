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

#include <sys/types.h>

#include <stdlib.h>

#include "compat_stdbool.h"
#include "compat_stdint.h"
#include "compat_inttypes.h"

#include "hash.h"
#include "hash_native.h"

bool cvsync_MD5_init(void **);
void cvsync_MD5_update(void *, const void *, size_t);
void cvsync_MD5_final(void *, uint8_t *);
#if defined(HAVE_RIPEMD160)
bool cvsync_RIPEMD160_init(void **);
void cvsync_RIPEMD160_update(void *, const void *, size_t);
void cvsync_RIPEMD160_final(void *, uint8_t *);
#endif /* defined(HAVE_RIPEMD160) */
#if defined(HAVE_SHA1)
bool cvsync_SHA1_init(void **);
void cvsync_SHA1_update(void *, const void *, size_t);
void cvsync_SHA1_final(void *, uint8_t *);
#endif /* defined(HAVE_SHA1) */
void cvsync_native_destroy(void *);

const struct hash_args MD5_args = {
	cvsync_MD5_init, cvsync_MD5_update, cvsync_MD5_final,
	cvsync_native_destroy,
	16
};

#if defined(HAVE_RIPEMD160)
const struct hash_args RIPEMD160_args = {
	cvsync_RIPEMD160_init, cvsync_RIPEMD160_update, cvsync_RIPEMD160_final,
	cvsync_native_destroy,
	20
};
#endif /* defined(HAVE_RIPEMD160) */

#if defined(HAVE_SHA1)
const struct hash_args SHA1_args = {
	cvsync_SHA1_init, cvsync_SHA1_update, cvsync_SHA1_final,
	cvsync_native_destroy,
	20
};
#endif /* defined(HAVE_SHA1) */

bool
cvsync_MD5_init(void **ctx)
{
	MD5_CTX *md5ctx;

	if ((md5ctx = malloc(sizeof(*md5ctx))) == NULL)
		return (false);
	MD5Init(md5ctx);

	*ctx = md5ctx;

	return (true);
}

void
cvsync_MD5_update(void *ctx, const void *buffer, size_t bufsize)
{
	MD5Update(ctx, buffer, bufsize);
}

void
cvsync_MD5_final(void *ctx, uint8_t *buffer)
{
	MD5Final(buffer, ctx);
	free(ctx);
}

#if defined(HAVE_RIPEMD160)
bool
cvsync_RIPEMD160_init(void **ctx)
{
	RMD160_CTX *ripemd160ctx;

	if ((ripemd160ctx = malloc(sizeof(*ripemd160ctx))) == NULL)
		return (false);
	RMD160Init(ripemd160ctx);

	*ctx = ripemd160ctx;

	return (true);
}

void
cvsync_RIPEMD160_update(void *ctx, const void *buffer, size_t bufsize)
{
	RMD160Update(ctx, buffer, bufsize);
}

void
cvsync_RIPEMD160_final(void *ctx, uint8_t *buffer)
{
	RMD160Final(buffer, ctx);
	free(ctx);
}
#endif /* defined(HAVE_SHA1) */

#if defined(HAVE_SHA1)
bool
cvsync_SHA1_init(void **ctx)
{
	SHA1_CTX *sha1ctx;

	if ((sha1ctx = malloc(sizeof(*sha1ctx))) == NULL)
		return (false);
	SHA1Init(sha1ctx);

	*ctx = sha1ctx;

	return (true);
}

void
cvsync_SHA1_update(void *ctx, const void *buffer, size_t bufsize)
{
	SHA1Update(ctx, buffer, bufsize);
}

void
cvsync_SHA1_final(void *ctx, uint8_t *buffer)
{
	SHA1Final(buffer, ctx);
	free(ctx);
}
#endif /* defined(HAVE_SHA1) */

void
cvsync_native_destroy(void *ctx)
{
	free(ctx);
}
