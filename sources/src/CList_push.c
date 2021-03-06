#include	<stdlib.h>
#include	<string.h>
#include	"CList.h"

static CLink*	newLink(CList* li, void* data, size_t sz, void (*destr)())
{
  CLink*	new = malloc(sizeof(*new) + sz);

  if (new)
    {
      new->list = li;
      new->free = destr;
      new->prev = new->next = NULL;
      if (!sz)
	new->data = data;
      else
	{
	  new->data = &new->data + 1;
	  data ? memcpy(new->data, data, sz) :
	    memset(new->data, 0, sz);
	}
      if (++li->size == 1)
	li->begin = li->end = new;
    }
  return new;
}

CLink*		CList_push_front(CList* li, void* data, size_t sz, void (*destr)())
{
  CLink*	new = newLink(li, data, sz, destr);

  if (new && li->size > 1)
    {
      new->next = li->begin;
      li->begin->prev = new;
      li->begin = new;
    }
  return new;
}

CLink*		CList_push_back(CList* li, void* data, size_t sz, void (*destr)())
{
  CLink*	new = newLink(li, data, sz, destr);

  if (new && li->size > 1)
    {
      new->prev = li->end;
      li->end->next = new;
      li->end = new;
    }
  return new;
}

CLink*		CList_push_after(CLink* ln, void* data, size_t sz, void (*destr)())
{
  CList*	li = ln->list;
  CLink*	new;

  if (ln == li->end)
    return CList_push_back(li, data, sz, destr);
  if ((new = newLink(li, data, sz, destr)))
    {
      new->prev = ln;
      new->next = ln->next;
      ln->next->prev = new;
      ln->next = new;
    }
  return new;
}

CLink*		CList_push_before(CLink* ln, void* data, size_t sz, void (*destr)())
{
  CList*	li = ln->list;
  CLink*	new;

  if (ln == li->begin)
    return CList_push_front(li, data, sz, destr);
  if ((new = newLink(li, data, sz, destr)))
    {
      new->prev = ln->prev;
      new->next = ln;
      ln->prev->next = new;
      ln->prev = new;
    }
  return new;
}
