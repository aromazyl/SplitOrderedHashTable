#include "inc/detail/node_def.hpp"
#include "inc/detail/context_impl.hpp"

namespace detail {
template <typename MPtrType>
class LockFreeList {
public:
  typedef typename MPtrType::node_type node_type;
  typedef typename MPtrType mark_ptr_type;

public:
  bool insert(mark_ptr_type* head, node_type* node) {
    auto key = node->key;
    while (true) {
      if (head->next == node) return false;
      node->mark = 0;
      node->next = _cur;
      auto prev = atomic_load(_prev);
      if (atomic_compare_exchange_weak(&_prev, &prev, ))
    }
  }

private:
  mark_ptr_type* _prev;
  mark_ptr_type _pmark_curr_ptag;
  mark_ptr_type _cmark_next_ctag;

};
}
