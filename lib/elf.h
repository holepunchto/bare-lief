#pragma once

#include <memory>

#include <assert.h>
#include <bare.h>
#include <js.h>
#include <jstl.h>
#include <stddef.h>
#include <stdint.h>

#include <LIEF/ELF.hpp>

using namespace LIEF;

static std::shared_ptr<ELF::Binary>
bare_lief_elf_binary_parse(
  js_env_t *,
  js_receiver_t,
  std::span<uint8_t> buffer
) {
  return ELF::Parser::parse(std::vector(buffer.begin(), buffer.end()));
}
