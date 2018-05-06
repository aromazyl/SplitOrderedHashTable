namespace detail {
template <typename Key, typename TagType>
struct NodeType {
  typedef Key key_type;
  typedef TagType tag_type;
  Key key;
  bool mark;
  NodeType<Key, TagType>* next;
  TagType tag;
};

template <typename NType>
struct MarkPtrType {
  typedef NType node_type;
  bool mark;
  NType* next;
  typename NType::tag tag;
};


// template MarkPtrType
template <typename MPType, int M>
struct Context {
  typedef MPType mark_ptr_type;
  enum { mark_ptr_num = M };
  MPType mark_ptrs[M];
};
}
