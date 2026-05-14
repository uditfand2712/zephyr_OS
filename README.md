# Zephyr OS Project

## Build Command

```bash
west build -b qemu_cortex_m3
```

## Run on QEMU

```bash
qemu-system-arm -machine lm3s6965evb -nographic -vga none -net none -serial mon:stdio -kernel build/zephyr/zephyr.elf
```
