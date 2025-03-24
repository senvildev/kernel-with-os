# kernel-with-os

simple kernel with an os

# requirements

- grub <br>
- i686-elf-as <br>
- i686-elf-gcc <br>

# clangd

in case you use clangd (i do) use this `.clangd` configuration:

```
CompileFlags:
  Add:
    - "-working-directory="/path/to/project"
    - "-Isrc"
    - "-Isrc/arch/i386"
```

# system info

wip
