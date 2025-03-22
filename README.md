# kernel-with-os

simple kernel with an os

# requirements

- grub <br>
- i686-elf-as <br>
- i686-elf-gcc <br>
- a brain

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

## src/libs/

this directory is dedicated for libraries to be used inside protected mode
