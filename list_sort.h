/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _LINUX_LIST_SORT_H
#define _LINUX_LIST_SORT_H

// #include <linux/types.h>

struct list_head;

typedef int
    __attribute__((nonnull(2, 3))) (*list_cmp_func_t)(void *,
                                                      const struct list_head *,
                                                      const struct list_head *);

__attribute__((nonnull(2, 3))) void list_sort(void *priv,
                                              struct list_head *head,
                                              list_cmp_func_t cmp);
int cmp(void *_, const struct list_head *a, const struct list_head *b);

#include <stdint.h>
#include <string.h>
#include "list.h"
#include "queue.h"
#define u8 uint8_t
/*
 * Using __builtin_constant_p(x) to ignore cases where the return
 * value is always the same.  This idea is taken from a similar patch
 * written by Daniel Walker.
 */

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#endif