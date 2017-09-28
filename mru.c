#include "cache.h"
#include "mru.h"

void mru_append(struct mru *head, void *item)
{
	struct mru *cur = xmalloc(sizeof(*cur));
	cur->item = item;
	list_add_tail(&cur->list, &head->list);
}

void mru_mark(struct mru *head, struct mru *entry)
{
	/* To mark means to put at the front of the list. */
	list_del(&entry->list);
	list_add(&entry->list, &head->list);
}

void mru_clear(struct mru *head)
{
	struct list_head *p1;
	struct list_head *p2;
	struct mru *to_free;

	list_for_each_safe(p1, p2, &head->list) {
		to_free = list_entry(p1, struct mru, list);
		free(to_free);
	}
	INIT_LIST_HEAD(&head->list);
}
