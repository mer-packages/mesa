/*
 * Copyright 2010 Jerome Glisse <glisse@freedesktop.org>
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
 *      Jerome Glisse
 */
#ifndef R600_H
#define R600_H

#include "../../winsys/radeon/drm/radeon_winsys.h"
#include "util/u_double_list.h"
#include "util/u_transfer.h"

#include "radeonsi_resource.h"

struct winsys_handle;

/* R600/R700 STATES */
struct r600_query {
	union {
		uint64_t			u64;
		boolean				b;
		struct pipe_query_data_so_statistics so;
	} result;
	/* The kind of query */
	unsigned				type;
	/* Offset of the first result for current query */
	unsigned				results_start;
	/* Offset of the next free result after current query data */
	unsigned				results_end;
	/* Size of the result in memory for both begin_query and end_query,
	 * this can be one or two numbers, or it could even be a size of a structure. */
	unsigned				result_size;
	/* The buffer where query results are stored. It's used as a ring,
	 * data blocks for current query are stored sequentially from
	 * results_start to results_end, with wrapping on the buffer end */
	struct r600_resource			*buffer;
	/* The number of dwords for begin_query or end_query. */
	unsigned				num_cs_dw;
	/* linked list of queries */
	struct list_head			list;
};

struct r600_context;
struct r600_screen;

void si_get_backend_mask(struct r600_context *ctx);
void si_context_flush(struct r600_context *ctx, unsigned flags);
void si_begin_new_cs(struct r600_context *ctx);

struct r600_query *r600_context_query_create(struct r600_context *ctx, unsigned query_type);
void r600_context_query_destroy(struct r600_context *ctx, struct r600_query *query);
boolean r600_context_query_result(struct r600_context *ctx,
				struct r600_query *query,
				boolean wait, void *vresult);
void r600_query_begin(struct r600_context *ctx, struct r600_query *query);
void r600_query_end(struct r600_context *ctx, struct r600_query *query);
void r600_context_queries_suspend(struct r600_context *ctx);
void r600_context_queries_resume(struct r600_context *ctx);
void r600_query_predication(struct r600_context *ctx, struct r600_query *query, int operation,
			    int flag_wait);

bool si_is_timer_query(unsigned type);
bool si_query_needs_begin(unsigned type);
void si_need_cs_space(struct r600_context *ctx, unsigned num_dw, boolean count_draw_in);

int si_context_init(struct r600_context *ctx);

#endif
