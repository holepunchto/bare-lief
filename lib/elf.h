#pragma once

#include <memory>
#include <optional>

#include <assert.h>
#include <bare.h>
#include <js.h>
#include <jstl.h>
#include <stddef.h>
#include <stdint.h>

#include <LIEF/ELF.hpp>

#include "handle.h"

using namespace LIEF;

static std::shared_ptr<bare_lief_handle_t<ELF::Binary>>
bare_lief_elf_binary_parse(
  js_env_t *,
  js_receiver_t,
  std::span<uint8_t> buffer
) {
  return std::make_shared<bare_lief_handle_t<ELF::Binary>>(
    ELF::Parser::parse(std::vector(buffer.begin(), buffer.end())).release(),
    true
  );
}

static void
bare_lief_elf_binary_write(
  js_env_t *,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  std::string path
) {
  binary->handle->write(path);
}

static js_arraybuffer_t
bare_lief_elf_binary_get_raw(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary
) {
  int err;

  auto buffer = binary->handle->raw();

  js_arraybuffer_t result;
  err = js_create_arraybuffer(env, buffer, result);
  assert(err == 0);

  return result;
}

static std::optional<std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntry>>>
bare_lief_elf_binary_get_dynamic_entry(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  int64_t tag
) {
  auto handle = binary->handle->get(ELF::DynamicEntry::TAG(tag));

  if (handle == nullptr) return std::nullopt;

  return std::make_shared<bare_lief_handle_t<ELF::DynamicEntry>>(handle, false);
}

static bool
bare_lief_elf_binary_has_dynamic_entry(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  int64_t tag
) {
  return binary->handle->has(ELF::DynamicEntry::TAG(tag));
}

static std::shared_ptr<bare_lief_handle_t<ELF::DynamicSharedObject>>
bare_lief_elf_dynamic_shared_object_create(
  js_env_t *env,
  js_receiver_t,
  std::string name
) {
  auto handle = new ELF::DynamicSharedObject(name);

  return std::make_shared<bare_lief_handle_t<ELF::DynamicSharedObject>>(handle, true);
}

static std::string
bare_lief_elf_dynamic_shared_object_get_name(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::DynamicSharedObject>> entry
) {
  return entry->handle->name();
}

static void
bare_lief_elf_dynamic_shared_object_set_name(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::DynamicSharedObject>> entry,
  std::string name
) {
  entry->handle->name(name);
}
