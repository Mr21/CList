#include	"CList.h"

unsigned	CList_find_n_destroy(CList* li, void const* data)
{
  CLink*	ln = CList_begin(li);
  CLink*	ln_next;
  unsigned	u = 0;

  while (ln)
    {
      ln_next = ln->next;
      if (ln->data == data)
	{
	  CList_erase(ln);
	  ++u;
	}
      ln = ln_next;
    }
  return u;
}
