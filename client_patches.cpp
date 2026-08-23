#include <iostream>
#include <iomanip> // Required for hex formatting


auto address = memory::sig_scan(game, "75 ? 83 25"); // From T7s

if (address.get() != 0) {
    std::cout << "Found it at " << std::showbase << std::hex << reinterpret_cast<uintptr_t>(address.get()) << std::endl;
    
    utils::hook::set<std::uint8_t>(address.get(), 0xEB); // test maybe O:
} else {
    std::cout << "Signature not found in this build." << std::endl;
}
