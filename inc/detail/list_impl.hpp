#incldue "inc/detail/atomic_op.hpp"
#include "inc/detail/node_def.hpp"
#include "inc/detail/context_impl.hpp"

namespace detail {
template <typename MPtrType>
class LockFreeList {
public:
  typedef typename MPtrType::node_type node_type;
  typedef typename MPtrType mark_ptr_type;

public:
  bool Insert(mark_ptr_type* head, node_type* node) {
    auto key = node->key;
    while (true) {
      if (Find(head, node->key)) return false;
      node->mark = false;
      node->next = _pmark_curr_ptag.next;
      auto prev = atomic_load(_prev);
      if (__sync_bool_compare_and_swap(prev,
            MPtrType{0, _pmark_curr_ptag.next, _pmark_curr_ptag.tag},
            MPtrType{0, node, _pmark_curr_ptag.ptag + 1}))
        return true;
    }
  }

  bool Delete(mark_ptr_type* head, const typename mark_ptr_type::Key& key) {
    while (true) {
      if (!Find(head, key)) return false;

      if (!__sync_bool_compare_and_swap(&_cmark_next_ctag,
            MPtrType{0, _cmark_next_ctag.next, _cmark_next_ctag.tag},
            MPtrType{1, _cmark_next_ctag.next, _cmark_next_ctag.tag + 1})) {
        continue;
      }

      auto prev = atomic_load(_prev);
      if (__sync_bool_compare_and_swap(prev,
            MPtrType{0, _pmark_curr_ptag.next, _pmark_curr_ptag.tag},
            MPtrType{0, _cmark_next_ctag.next, _pmark_curr_ptag.tag})) {
        return true;
      }

    }
  }

  bool Search(mark_ptr_type* head, const typename mark_ptr_type::Key& key) {
    return Find(head, key);
  }

  bool Find(mark_ptr_type* head, const typename mark_ptr_type::Key& key) {
    bool try_agin = true;
    while (try_agin) {
      try_agin = false;
      this->_prev = head;
      this->_pmark_curr_ptag = *_prev;
      while (true) {
        if (_pmark_curr_ptag.next == NULL) {
          return false;
        }
        this->_cmark_next_ctag = *_pmark_curr_ptag->next;
        if (*prev != MPtrType{0, _pmark_curr_ptag->next, _pmark_curr_ptag->tag}) {
          try_agin = true;
          break;
        }
        if (!)
      }
    }

  }

private:
  mark_ptr_type* _prev;
  mark_ptr_type _pmark_curr_ptag;
  mark_ptr_type _cmark_next_ctag;

};
}
