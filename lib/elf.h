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

#include "LIEF/ELF/DynamicEntry.hpp"
#include "handle.h"

using namespace LIEF;

static std::shared_ptr<bare_lief_handle_t<ELF::Binary>>
bare_lief_elf_binary_parse(
  js_env_t *,
  js_receiver_t,
  std::span<uint8_t> buffer
) {
  return std::make_shared<bare_lief_handle_t<ELF::Binary>>(
    ELF::Parser::parse(std::vector(buffer.begin(), buffer.end())).release()
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

static void
bare_lief_elf_binary_add_dynamic_entry(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntry>> entry
) {
  binary->handle->add(*entry->handle);
}

static std::optional<std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntry>>>
bare_lief_elf_binary_get_dynamic_entry(
  js_env_t *env,
  js_receiver_t,
  js_object_t self,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  int64_t tag
) {
  int err;

  auto handle = binary->handle->get(ELF::DynamicEntry::TAG(tag));

  if (handle == nullptr) return std::nullopt;

  js_persistent_t<js_object_t> owner;
  err = js_create_reference(env, self, owner);
  assert(err == 0);

  return std::make_shared<bare_lief_handle_t<ELF::DynamicEntry>>(handle, std::move(owner));
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

static void
bare_lief_elf_binary_add_library(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  std::string name
) {
  binary->handle->add_library(name);
}

static std::optional<std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntryLibrary>>>
bare_lief_elf_binary_get_library(
  js_env_t *env,
  js_receiver_t,
  js_object_t self,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  std::string name
) {
  int err;

  auto handle = binary->handle->get_library(name);

  if (handle == nullptr) return std::nullopt;

  js_persistent_t<js_object_t> owner;
  err = js_create_reference(env, self, owner);
  assert(err == 0);

  return std::make_shared<bare_lief_handle_t<ELF::DynamicEntryLibrary>>(handle, std::move(owner));
}

static bool
bare_lief_elf_binary_has_library(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  std::string name
) {
  return binary->handle->has_library(name);
}

static void
bare_lief_elf_binary_remove_library(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::Binary>> binary,
  std::string name
) {
  binary->handle->remove_library(name);
}

static std::shared_ptr<bare_lief_handle_t<ELF::DynamicSharedObject>>
bare_lief_elf_dynamic_shared_object_create(
  js_env_t *env,
  js_receiver_t,
  std::string name
) {
  auto handle = new ELF::DynamicSharedObject(name);

  return std::make_shared<bare_lief_handle_t<ELF::DynamicSharedObject>>(handle);
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

static std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntryLibrary>>
bare_lief_elf_dynamic_entry_library_create(
  js_env_t *env,
  js_receiver_t,
  std::string name
) {
  auto handle = new ELF::DynamicEntryLibrary(name);

  return std::make_shared<bare_lief_handle_t<ELF::DynamicEntryLibrary>>(handle);
}

static std::string
bare_lief_elf_dynamic_entry_library_get_name(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntryLibrary>> entry
) {
  return entry->handle->name();
}

static void
bare_lief_elf_dynamic_entry_library_set_name(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntryLibrary>> entry,
  std::string name
) {
  entry->handle->name(name);
}

static std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntryRunPath>>
bare_lief_elf_dynamic_entry_run_path_create(
  js_env_t *env,
  js_receiver_t,
  std::string path
) {
  auto handle = new ELF::DynamicEntryRunPath(path);

  return std::make_shared<bare_lief_handle_t<ELF::DynamicEntryRunPath>>(handle);
}

static std::string
bare_lief_elf_dynamic_entry_run_path_get_run_path(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntryRunPath>> entry
) {
  return entry->handle->runpath();
}

static void
bare_lief_elf_dynamic_entry_run_path_set_run_path(
  js_env_t *env,
  js_receiver_t,
  std::shared_ptr<bare_lief_handle_t<ELF::DynamicEntryRunPath>> entry,
  std::string path
) {
  entry->handle->runpath(path);
}
