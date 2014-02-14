/*
 * Copyright 2012 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHOR(S) AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *      Christian König <christian.koenig@amd.com>
 */

#ifndef RADEONSI_RESOURCE_H
#define RADEONSI_RESOURCE_H

#include "../radeon/r600_pipe_common.h"
#include "util/u_transfer.h"
#include "util/u_inlines.h"

static INLINE struct r600_resource *
r600_resource_create_custom(struct pipe_screen *screen,
			    unsigned usage, unsigned size)
{
	assert(size);
	return r600_resource(pipe_buffer_create(screen,
		PIPE_BIND_CUSTOM, usage, size));
}

#endif
