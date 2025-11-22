#pragma once

template <typename T>
struct bare_lief_handle_t {
  T *handle;
  bool owned;

  bare_lief_handle_t(T *handle, bool owned) : handle(handle), owned(owned) {}

  ~bare_lief_handle_t() {
    if (owned) delete handle;
  }
};
