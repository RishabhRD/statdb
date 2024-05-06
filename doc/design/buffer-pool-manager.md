# Buffer Pool Manager

Buffer Pool Manager is a page cache that contains some hard disk pages in
memory. Buffer Pool Manager has an upper bound on number of pages it can have
in memory at certain point of time. Logically it have K frames that can hold
K pages from hard disk at a point of time.

It would support 2 operations:
1. acquire page
2. release page

This is assumed that acquire page and release page would **not** be called from
different threads.

## Kinds of Pages

Buffer pool doesn't know internally about the content of pages.
Instead it just maintains 2 kinds of pages:
1. **Pinned**: Being currently used by some other processes
2. **Unpinned**: Not being currently used by some other processes

For maintaining the same, buffer pool maintains a counter for each frame that
how many processes are currently using the page in the frame.
Value of that counter > 0 implies that page is currently pinned otherwise
its currently unpinned.

## Eviction Policy

Because there is upper bound on number of pages in memory, if total number of
pages in memory can be K, and there is request of some page after K pages
then some page should be removed from buffer.

We maintain a LRU Cache for the same. Pages that are unpinned would be in
list of pages in LRU cache.

## Acquire Page

Syntax:
```
pool.acquire_page(pageId) -> sender<optional<page_t const&>>
```

When some process make request to acquire a page
- If that page exists in any frame of page buffer then that page is returned
  to caller. Also if that frame is in LRU cache page list, remove it from there.
- If that page doesn't exist in any frame then, we check what page to evict
  from LRU cache.
  - If there is no page to evict, then we return nullopt.
  - Else we fetch that page from Hard Disk and put that in frame needed to
    be evicted.

## Release Page

Syntax:
```
pool.release_page(pageId) -> void
```

This function just reduces the counter of frame of pageId by 1 and if counter
gets to 0 then adds this page to list of pages of LRU cache.
