#epiphany-elf-sim
- A frontend for epiphany-elf-run.
- Makes it easy to start simulations.
- Default parameters are Parallella-16 Epiphany-III.

**Pressing CTRL-C at any time will stop the simulation.**

##Examples

Get help:
```
$ epiphany-elf-sim --help
```


Simulate a 16-core (defaults) Epiphany chip. Load FOO to every core and start
simulation.
```
$ epiphany-elf-sim FOO
```


Simulate a 64-core Epiphany chip.
```
$ epiphany-elf-sim --rows 8 --cols 8 FOO
```


Load FOO to the first core, BAR to second core and BAZ to the rest of the
cores.
```
$ epiphany-elf-sim FOO BAR BAZ
```


Redirect stdout and stderr to DIR/core-ID.std{out,err}. stdin will also be
redirected to DIR/core-ID.stdin if it exists. Otherwise stdin is redirected to
/dev/null (which is the default). DIR will be created if it does not exist and
any old stdout/stderr files will be overwritten.
```
$ epiphany-elf-sim --redirect-dir DIR FOO
```


Don't spawn the simulator process for core 0x808, but let user do that
manually. This is useful if you want to simulate a core in GDB.
See **README.esim.md** for more info on how to do that.
```
$ epiphany-elf-sim --wait-attach 0x808 FOO
```

