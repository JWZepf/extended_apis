//
// Bareflank Extended APIs
//
// Copyright (C) 2018 Assured Information Security, Inc.
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

#include <intrinsics.h>

#include "arch/x64/pci_test_support.h"

#ifdef _HIPPOMOCKS__ENABLE_CFUNC_MOCKING_SUPPORT

namespace eapis
{
namespace pci
{

TEST_CASE("phys_pci::bus,device,func")
{
    phys_pci dev(1, 2, 3);
    CHECK(dev.bus() == 1);
    CHECK(dev.device() == 2);
    CHECK(dev.func() == 3);
}

TEST_CASE("phys_pci::read/write/rmw(reg[, value])")
{
    auto ___ = cleanup();

    phys_pci dev(1, 2, 3);
    g_pci_config_space[DEVICE_1_2_3 | 4] = 0xaabbccdd;

    CHECK(dev.read_register_u8(4) == 0xdd);
    CHECK(g_ports[PORTIO_CONFIG_ADDRESS] == (DEVICE_1_2_3 | 4));

    CHECK(dev.read_register_u16(4) == 0xccdd);
    CHECK(g_ports[PORTIO_CONFIG_ADDRESS] == (DEVICE_1_2_3 | 4));

    CHECK(dev.read_register_u32(4) == 0xaabbccdd);
    CHECK(g_ports[PORTIO_CONFIG_ADDRESS] == (DEVICE_1_2_3 | 4));

    CHECK_NOTHROW(dev.write_register(4, 0xffffffff));
    CHECK(g_ports[PORTIO_CONFIG_ADDRESS] == (DEVICE_1_2_3 | 4));
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    g_pci_config_space[DEVICE_1_2_3 | 4] = 0xaabbccdd;
    CHECK_NOTHROW(dev.rmw_register_u8(4, 0xff));
    CHECK(g_ports[PORTIO_CONFIG_ADDRESS] == (DEVICE_1_2_3 | 4));
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xaabbccff);

    g_pci_config_space[DEVICE_1_2_3 | 4] = 0xaabbccdd;
    CHECK_NOTHROW(dev.rmw_register_u16(4, 0xffff));
    CHECK(g_ports[PORTIO_CONFIG_ADDRESS] == (DEVICE_1_2_3 | 4));
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xaabbffff);
}

TEST_CASE("phys_pci named register reads")
{
    auto ___ = cleanup();
    phys_pci dev(1, 2, 3);

    init_all_config_space();

    CHECK(dev.device_id() == 0xaabb);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x00);

    CHECK(dev.vendor_id() == 0xccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x00);

    CHECK(dev.status() == 0xaabb);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x04);

    CHECK(dev.read_command() == 0xccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x04);

    CHECK(dev.device_class() == 0xaa);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x08);

    CHECK(dev.device_subclass() == 0xbb);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x08);

    CHECK(dev.prog_if() == 0xcc);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x08);

    CHECK(dev.revision() == 0xdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x08);

    CHECK(dev.read_bist() == 0xaa);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x0C);

    CHECK(dev.header_type() == 0xbb);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x0C);

    CHECK(dev.latency() == 0xcc);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x0C);

    CHECK(dev.cl_size() == 0xdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x0C);

    CHECK(dev.cisp() == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x28);

    CHECK(dev.subsystem_id() == 0xaabb);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x2C);

    CHECK(dev.subsystem_vid() == 0xccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x2C);

    CHECK(dev.exprom_bar() == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x30);

    CHECK(dev.capabilities_ptr() == 0xdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x34);

    CHECK(dev.max_latency() == 0xaa);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x3C);

    CHECK(dev.min_grant() == 0xbb);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x3C);

    CHECK(dev.int_pin() == 0xcc);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x3C);

    CHECK(dev.int_line() == 0xdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x3C);

    CHECK(dev.bar(0) == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x10);

    CHECK(dev.bar(1) == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x14);

    CHECK(dev.bar(2) == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x18);

    CHECK(dev.bar(3) == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x1C);

    CHECK(dev.bar(4) == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x20);

    CHECK(dev.bar(5) == 0xaabbccdd);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x24);

    dev.rmw_register_u8(0x0E, 0x01);
    CHECK(dev.secondary_bus() == 0xcc);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x18);
    dev.rmw_register_u8(0x0E, 0x00);
    CHECK(dev.secondary_bus() == 0);

    CHECK(dev.bar(6) == 0xffffffff);
}

TEST_CASE("phys_pci named register writes")
{
    auto ___ = cleanup();
    phys_pci dev(1, 2, 3);

    init_all_config_space();
    dev.send_command(0xffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x04);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xaabbffff);

    init_all_config_space();
    dev.send_bist(0xff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x0C);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffbbccdd);

    init_all_config_space();
    dev.set_latency(0xff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x0C);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xaabbffdd);

    init_all_config_space();
    dev.set_cl_size(0xff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x0C);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xaabbccff);

    init_all_config_space();
    dev.set_exprom_bar(0xffffffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x30);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    init_all_config_space();
    dev.set_int_line(0xff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x3C);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xaabbccff);

    init_all_config_space();
    dev.set_bar(0, 0xffffffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x10);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    init_all_config_space();
    dev.set_bar(1, 0xffffffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x14);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    init_all_config_space();
    dev.set_bar(2, 0xffffffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x18);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    init_all_config_space();
    dev.set_bar(3, 0xffffffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x1C);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    init_all_config_space();
    dev.set_bar(4, 0xffffffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x20);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    init_all_config_space();
    dev.set_bar(5, 0xffffffff);
    CHECK(reg_from_full_addr(g_ports[PORTIO_CONFIG_ADDRESS]) == 0x24);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xffffffff);

    init_all_config_space();
    g_ports[PORTIO_CONFIG_ADDRESS] = 0;
    dev.set_bar(6, 0xffffffff);
    CHECK(g_ports[PORTIO_CONFIG_ADDRESS] == 0);
    CHECK(g_ports[PORTIO_CONFIG_DATA] == 0xaabbccdd);
}

// Sample PCI descriptors to test enumeration

struct pci_descriptor {
    uint8_t bus;
    uint8_t device;
    uint8_t func;
    uint32_t data[16];
};

// Taken from a real system using ./dump_pci.py
static const struct pci_descriptor g_descriptors[] = {
    {
        0x00, 0x00, 0x00, {
            0x591f8086, 0x20900006, 0x06000005, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x50001458,
            0x00000000, 0x000000e0, 0x00000000, 0x00000000,
        }
    },
    {
        0x00, 0x02, 0x00, {
            0x59128086, 0x00100407, 0x03000004, 0x00000010,
            0xf6000004, 0x00000000, 0xe000000c, 0x00000000,
            0x0000f001, 0x00000000, 0x00000000, 0xd0001458,
            0x00000000, 0x00000040, 0x00000000, 0x0000010b,
        }
    },
    {
        0x00, 0x08, 0x00, {
            0x19118086, 0x00100000, 0x08800000, 0x00000010,
            0xf722e004, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x50001458,
            0x00000000, 0x00000090, 0x00000000, 0x0000010b,
        }
    },
    {
        0x00, 0x14, 0x00, {
            0xa2af8086, 0x02900406, 0x0c033000, 0x00800000,
            0xf7210004, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x50071458,
            0x00000000, 0x00000070, 0x00000000, 0x0000010b,
        }
    },
    {
        0x00, 0x16, 0x00, {
            0xa2ba8086, 0x00100406, 0x07800000, 0x00800000,
            0xf722d004, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x1c3a1458,
            0x00000000, 0x00000050, 0x00000000, 0x0000010b,
        }
    },
    {
        0x00, 0x17, 0x00, {
            0xa2828086, 0x02b00407, 0x01060100, 0x00000000,
            0xf7228000, 0xf722c000, 0x0000f091, 0x0000f081,
            0x0000f061, 0xf722b000, 0x00000000, 0xb0051458,
            0x00000000, 0x00000080, 0x00000000, 0x0000010b,
        }
    },
    {
        0x00, 0x1b, 0x00, {
            0xa2eb8086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00010100, 0x200000f0,
            0xf710f710, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010010b,
        }
    },
    {
        0x00, 0x1c, 0x00, {
            0xa2948086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00020200, 0x2000e0e0,
            0xf700f700, 0xf001f001, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010010b,
        }
    },
    {
        0x00, 0x1c, 0x05, {
            0xa2958086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00030300, 0x200000f0,
            0x0000fff0, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010020a,
        }
    },
    {
        0x00, 0x1c, 0x06, {
            0xa2968086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00040400, 0x200000f0,
            0x0000fff0, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010030b,
        }
    },
    {
        0x00, 0x1c, 0x07, {
            0xa2978086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00050500, 0x200000f0,
            0x0000fff0, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010040b,
        }
    },
    {
        0x00, 0x1d, 0x00, {
            0xa2988086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00060600, 0x200000f0,
            0x0000fff0, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010010b,
        }
    },
    {
        0x00, 0x1d, 0x01, {
            0xa2998086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00070700, 0x200000f0,
            0x0000fff0, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010020a,
        }
    },
    {
        0x00, 0x1d, 0x02, {
            0xa29a8086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00080800, 0x200000f0,
            0x0000fff0, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010030b,
        }
    },
    {
        0x00, 0x1d, 0x03, {
            0xa29b8086, 0x00100007, 0x060400f0, 0x00810010,
            0x00000000, 0x00000000, 0x00090900, 0x200000f0,
            0x0000fff0, 0x0001fff1, 0x00000000, 0x00000000,
            0x00000000, 0x00000040, 0x00000000, 0x0010040b,
        }
    },
    {
        0x00, 0x1f, 0x00, {
            0xa2c88086, 0x02000007, 0x06010000, 0x00800000,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x50011458,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
        }
    },
    {
        0x00, 0x1f, 0x02, {
            0xa2a18086, 0x00000000, 0x05800000, 0x00800000,
            0xf7224000, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0x50011458,
            0x00000000, 0x00000000, 0x00000000, 0x00000000,
        }
    },
    {
        0x00, 0x1f, 0x03, {
            0xa2f08086, 0x00100406, 0x04030000, 0x00002010,
            0xf7220004, 0x00000000, 0x00000000, 0x00000000,
            0xf7200004, 0x00000000, 0x00000000, 0xa1821458,
            0x00000000, 0x00000050, 0x00000000, 0x0000010b,
        }
    },
    {
        0x00, 0x1f, 0x04, {
            0xa2a38086, 0x02800003, 0x0c050000, 0x00000000,
            0xf722a004, 0x00000000, 0x00000000, 0x00000000,
            0x0000f041, 0x00000000, 0x00000000, 0x50011458,
            0x00000000, 0x00000000, 0x00000000, 0x0000010b,
        }
    },
    {
        0x01, 0x00, 0x00, {
            0xa804144d, 0x00100406, 0x01080200, 0x00000010,
            0xf7100004, 0x00000000, 0x00000000, 0x00000000,
            0x00000000, 0x00000000, 0x00000000, 0xa801144d,
            0x00000000, 0x00000040, 0x00000000, 0x0000010b,
        }
    },
    {
        0x02, 0x00, 0x00, {
            0x816810ec, 0x00100407, 0x0200000c, 0x00000010,
            0x0000e001, 0x00000000, 0xf7000004, 0x00000000,
            0xf000000c, 0x00000000, 0x00000000, 0xe0001458,
            0x00000000, 0x00000040, 0x00000000, 0x0000010b,
        }
    },
};

TEST_CASE("enumeration")
{
    auto ___ = cleanup();

    for (const auto &descriptor : g_descriptors) {
        for (register_type reg = 0; reg <= 0x3C; ++reg) {
            write_register(
                descriptor.bus,
                descriptor.device,
                descriptor.func,
                reg,
                gsl::at(descriptor.data, reg >> 2));
        }
    }

    std::vector<phys_pci> devices;

    CHECK_NOTHROW(phys_pci::enumerate(devices));
    CHECK(devices.size() == sizeof(g_descriptors) / sizeof(g_descriptors[0]));
}

TEST_CASE("BARs, header type 0")
{
    auto ___ = cleanup();

    // Generate a device with some interesting BARs
    // Note: for intercept_bar_write() to work properly, only even-numbered BARs
    // should be queried for length.
    write_register(1, 2, 3, 0x00, 0x12345678);  // vendor, device
    write_register(1, 2, 3, 0x08, 0x00000000);  // class
    write_register(1, 2, 3, 0x0C, 0x00000000);  // header type
    write_register(1, 2, 3, 0x10, 0x12345679);  // IO BAR, addr = 0x12345678
    write_register(1, 2, 3, 0x14, 0x12345670);  // 32-bit BAR, addr = 0x12345670, non-prefetch
    write_register(1, 2, 3, 0x18, 0x9ABCDEFC);  // 64-bit BAR, addr = 0x123456789ABCDEF0, prefetch
    write_register(1, 2, 3, 0x1C, 0x12345678);  // 64-bit BAR continuation
    write_register(1, 2, 3, 0x20, 0x12345672);  // invalid memory BAR
    write_register(1, 2, 3, 0x24, 0x9ABCDEFC);  // 64-bit BAR with truncated second half (invalid)

    phys_pci dev(1, 2, 3);
    bar bar0(dev, 0);
    bar bar1(dev, 1);
    bar bar2(dev, 2);
    bar bar3(dev, 3);
    bar bar4(dev, 4);
    bar bar5(dev, 5);
    bar bar6(dev, 6);

    CHECK(bar0.type() == bar::bar_io);
    CHECK(bar1.type() == bar::bar_memory_32bit);
    CHECK(bar2.type() == bar::bar_memory_64bit);
    CHECK(bar3.type() == bar::bar_invalid);         // continuation of above
    CHECK(bar4.type() == bar::bar_invalid);         // invalid type
    CHECK(bar5.type() == bar::bar_invalid);         // truncated 64-bit
    CHECK(bar6.type() == bar::bar_invalid);         // bad index

    CHECK(bar0.base_address() == 0x12345678);
    CHECK(bar1.base_address() == 0x12345670);
    CHECK(bar2.base_address() == 0x123456789ABCDEF0);

    CHECK(bar0.region_length() == BAR_TEST_REGION_LENGTH);
    CHECK(bar2.region_length() == BAR_TEST_REGION_LENGTH);
    CHECK(bar4.region_length() == 0);

    // Make sure region length checks set things back how they found them
    CHECK(bar0.base_address() == 0x12345678);
    CHECK(bar1.base_address() == 0x12345670);
    CHECK(bar2.base_address() == 0x123456789ABCDEF0);

    CHECK(bar0.prefetchable() == false);
    CHECK(bar1.prefetchable() == false);
    CHECK(bar2.prefetchable() == true);
    CHECK(bar3.prefetchable() == false);

    CHECK_NOTHROW(bar0.set_base_address(0x42424200));
    CHECK_NOTHROW(bar1.set_base_address(0x24242400));
    CHECK_NOTHROW(bar2.set_base_address(0xaaaaaaaa55555500));

    CHECK(bar0.base_address() == 0x42424200);
    CHECK(bar1.base_address() == 0x24242400);
    CHECK(bar2.base_address() == 0xaaaaaaaa55555500);
    CHECK(bar1.prefetchable() == false);
    CHECK(bar2.prefetchable() == true);
}

TEST_CASE("BARs, header type 1")
{
    auto ___ = cleanup();

    // Generate a device with some interesting BARs
    // Note: for intercept_bar_write() to work properly, only even-numbered BARs
    // should be queried for length.
    write_register(1, 2, 3, 0x00, 0x12345678);  // vendor, device
    write_register(1, 2, 3, 0x08, 0x00000000);  // class
    write_register(1, 2, 3, 0x0C, 0x00010000);  // header type
    write_register(1, 2, 3, 0x10, 0x12345679);  // IO BAR, addr = 0x12345678
    write_register(1, 2, 3, 0x14, 0x12345670);  // 32-bit BAR, addr = 0x12345670, non-prefetch

    // Fake a valid BAR in space that's not actually for BARs to make sure
    // the index is picked up as invalid first
    write_register(1, 2, 3, 0x18, 0x12345679);  // IO BAR, addr = 0x12345678

    phys_pci dev(1, 2, 3);
    bar bar0(dev, 0);
    bar bar1(dev, 1);
    bar bar2(dev, 2);

    CHECK(bar0.type() == bar::bar_io);
    CHECK(bar1.type() == bar::bar_memory_32bit);
    CHECK(bar2.type() == bar::bar_invalid);

    CHECK(bar0.base_address() == 0x12345678);
    CHECK(bar1.base_address() == 0x12345670);

    CHECK(bar0.region_length() == BAR_TEST_REGION_LENGTH);

    CHECK(bar0.base_address() == 0x12345678);
    CHECK(bar1.base_address() == 0x12345670);
}

TEST_CASE("BARs, header type 2")
{
    auto ___ = cleanup();

    // Generate a device with some interesting BARs
    // Note: for intercept_bar_write() to work properly, only even-numbered BARs
    // should be queried for length.
    write_register(1, 2, 3, 0x00, 0x12345678);  // vendor, device
    write_register(1, 2, 3, 0x08, 0x00000000);  // class
    write_register(1, 2, 3, 0x0C, 0x00020000);  // header type

    // Fake a valid BAR in space that's not actually for BARs to make sure
    // the index is picked up as invalid first
    write_register(1, 2, 3, 0x10, 0x12345679);  // IO BAR, addr = 0x12345678

    phys_pci dev(1, 2, 3);
    bar bar0(dev, 0);

    CHECK(bar0.type() == bar::bar_invalid);
}

}
}

#endif
