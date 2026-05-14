cmake_minimum_required(VERSION 3.20.0)

# Find Zephyr (west sets ZEPHYR_BASE)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(qemu_mutex)

# Add your source files
target_sources(app PRIVATE src/main.c)