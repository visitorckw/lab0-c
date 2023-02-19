#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* The strcpy built-in function does not check buffer lengths
 * and may very well overwrite memory zone contiguous to the intended
 * destination.
 */
#ifndef strlcpy
#define strlcpy(dst, src, sz) snprintf((dst), (sz), "%s", (src))
#endif

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head =
        (struct list_head *) malloc(sizeof(struct list_head));
    if (head)
        INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    element_t *entry;
    element_t *safe;
    list_for_each_entry_safe (entry, safe, l, list) {
        free(entry->value);
        free(entry);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *newNode = (element_t *) malloc(sizeof(element_t));
    if (!newNode)
        return false;
    newNode->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (!newNode->value) {
        free(newNode);
        return false;
    }
    strlcpy(newNode->value, s, strlen(s) + 1);
    list_add(&newNode->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *newNode = (element_t *) malloc(sizeof(element_t));
    if (!newNode)
        return false;
    newNode->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (!newNode->value) {
        free(newNode);
        return false;
    }
    strlcpy(newNode->value, s, strlen(s) + 1);
    list_add_tail(&newNode->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *delNode = list_entry(head->next, element_t, list);
    size_t length = bufsize < strlen(delNode->value) + 1
                        ? bufsize
                        : strlen(delNode->value) + 1;
    strlcpy(sp, delNode->value, length);
    list_del(head->next);
    return delNode;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *delNode = list_entry(head->prev, element_t, list);
    size_t length = bufsize < strlen(delNode->value) + 1
                        ? bufsize
                        : strlen(delNode->value) + 1;
    strlcpy(sp, delNode->value, length);
    list_del(head->prev);
    return delNode;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;
    int ctr = 0;
    struct list_head *node;
    list_for_each (node, head)
        ++ctr;
    return ctr;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;
    struct list_head *slow = head;
    struct list_head *fast = head;
    while (1) {
        slow = slow->next;
        if (fast->next == head || fast->next->next == head)
            break;
        fast = fast->next->next;
    }
    element_t *delNode = list_entry(slow, element_t, list);
    list_del(slow);
    free(delNode->value);
    free(delNode);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head))
        return true;
    struct list_head *cur;
    list_for_each (cur, head) {
        if (cur->next == head)
            break;
        element_t *L = list_entry(cur, element_t, list);
        element_t *R = list_entry(cur->next, element_t, list);
        if (strcmp(L->value, R->value))
            continue;
        char *str = (char *) malloc(sizeof(char) * (strlen(L->value) + 1));
        strlcpy(str, L->value, strlen(L->value) + 1);
        struct list_head *prev = cur->prev;
        while (prev->next != head) {
            element_t *node = list_entry(prev->next, element_t, list);
            if (strcmp(str, node->value))
                break;
            list_del(prev->next);
            free(node->value);
            free(node);
        }
        cur = prev;
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
