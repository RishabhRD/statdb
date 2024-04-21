#pragma once

#include "memory/mem_chunk_array.hpp"
#include "page/page.hpp"

namespace statdb {
using page_buffer_t = mem_chunk_array<page_size>;
}
