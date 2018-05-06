namespace detail {
class Context {
public:
  template <typename T>
  T* cast() {
    return dynamic_cast<T*>(this);
  }

  void register(const std::string& name, T* t) {
    this->_context[name] = dynamic_cast<T*>(t);
  }

  Context* call(const std::string& name) {
    return _context->at(name);
  }

private:
  std::unordered_map<std::string, Context*> _context;

};
}
