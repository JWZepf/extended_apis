//
// Bareflank Extended APIs
//
// Copyright (C) 2015 Assured Information Security, Inc.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#ifndef EPT_TYPES_INTEL_X64_H
#define EPT_TYPES_INTEL_X64_H

// *INDENT-OFF*

namespace eapis
{
namespace intel_x64
{
namespace ept
{

using epte_t = uint64_t;
using epte_value_t = uint64_t;

using gpa_t = uintptr_t;
using hpa_t = uintptr_t;
using hva_t = uintptr_t;

using memory_attr_t = uint64_t;

}
}
}

#endif
