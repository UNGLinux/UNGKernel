/*
 * Today's hack: quantum tunneling in structs
 *
 * 'entries' and 'term' are never anywhere referenced by word in code. In fact,
 * they serve as the hanging-off data accessed through repl.data[].
 */

#define padbytes(offset, type) ((-offset) & (__alignof__(type)-1))

/* tbl has the following structure equivalent, but without using VLAIS:
 * struct {
 *	struct type##_replace repl;
 *	struct type##_standard entries[nhooks];
 *	struct type##_error term;
 * } *tbl;
 */

#define xt_alloc_initial_table(type, typ2) ({ \
	unsigned int hook_mask = info->valid_hooks; \
	unsigned int nhooks = hweight32(hook_mask); \
	unsigned int bytes = 0, hooknum = 0, i = 0; \
	struct { \
		struct type##_replace repl; \
		char data[0]; \
	} *tbl; \
	struct type##_standard *entries; \
	struct type##_error *term; \
	size_t p1 = padbytes(sizeof(tbl->repl), *entries); \
	size_t ost = sizeof(tbl->repl) + p1 + nhooks * sizeof(*entries); \
	size_t p2 = padbytes(ost, *term); \
	size_t tbl_sz = ost + nhooks * sizeof(*entries) + p2 + sizeof(*term); \
	tbl = kzalloc(tbl_sz, GFP_KERNEL); \
	if (tbl == NULL) \
		return NULL; \
	entries = (struct type##_standard *)&tbl->data[p1]; \
	term = (struct type##_error *)&tbl->data[ost+p2]; \
	strncpy(tbl->repl.name, info->name, sizeof(tbl->repl.name)); \
	*term = (struct type##_error)typ2##_ERROR_INIT;  \
	tbl->repl.valid_hooks = hook_mask; \
	tbl->repl.num_entries = nhooks + 1; \
	tbl->repl.size = nhooks * sizeof(struct type##_standard) + \
			 sizeof(struct type##_error); \
	for (; hook_mask != 0; hook_mask >>= 1, ++hooknum) { \
		if (!(hook_mask & 1)) \
			continue; \
		tbl->repl.hook_entry[hooknum] = bytes; \
		tbl->repl.underflow[hooknum]  = bytes; \
		entries[i++] = (struct type##_standard) \
			typ2##_STANDARD_INIT(NF_ACCEPT); \
		bytes += sizeof(struct type##_standard); \
	} \
	tbl; \
})
