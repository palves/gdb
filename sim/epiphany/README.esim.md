#Build instructions:

The aim of this text is to get you up and running with the functional eMesh
simulator (*esim*).

Once you have successfully built and installed the binaries you might want to
check out **README.epiphany-elf-sim.md**.


##Compiling and installing

###Without networking (MPI) support:

In source root directory:
```
mkdir build
cd build
CFLAGS="-pthread -lrt -fPIC -fvisibility=hidden" \
LDFLAGS="-lrt" \
../configure --target=epiphany-elf \
  --enable-emesh-sim --enable-sim-hardware \
  --prefix="/SOME/PREFIX"
(Change prefix to match your settings)
make
make install
```


###With networking (MPI) support:

You need a recent MPI implementation compiled with full multi-threaded
(MPI_THREAD_MULTIPLE) support. The recommended implementation is Intel MPI 5.0.
This is the only implementation the simulator has been tested on. Intel MPI is
based on mpich so that should probably work too, but YMMV.


Add `-mt_mpi` to CFLAGS when compiling with Intel MPI.

In source root directory:
```
mkdir build.net
cd build.net
CC=mpicc \
CFLAGS="-pthread -lrt -fPIC -fvisibility=hidden" \
LDFLAGS="-lrt" \
../configure --target=epiphany-elf \
  --enable-emesh-sim --enable-sim-hardware \
  --enable-emesh-net \
  --prefix="/SOME/PREFIX"
(Change prefix to match your settings)
make
make install
```




##Running:


Example:
```
$ epiphany-elf-run --e-coreid 0x809 --e-cols 2 --e-rows 2 --e-first-core 0x808 program
```

Options:
--e-coreid      coreid of this sim process.
--e-cols        Number of columns in mesh
--e-rows        Number of rows in mesh
--e-first-core  coreid of upper leftmost core in mesh.

GDB session:
```
$ epiphany-elf-gdb program
(gdb) target sim
Connected to simulator
(gdb) sim e-coreid 0x809
(gdb) sim e-cols 2
(gdb) sim e-rows 2
(gdb) sim e-first-core 0x808
(gdb) load
Loading section ivt_reset, size 0x4 lma 0x0
...
(gdb) run
```

One more example:
Simulating the upper leftmost (northwest) 2x2 mesh of Parallella-16:  
In four separate terminals issue:  
```
$ epiphany-elf-run --e-coreid 0x808 --e-cols 2 --e-rows 2 --e-first-core 0x808 program1
$ epiphany-elf-run --e-coreid 0x809 --e-cols 2 --e-rows 2 --e-first-core 0x808 program2
$ epiphany-elf-run --e-coreid 0x848 --e-cols 2 --e-rows 2 --e-first-core 0x808 program3
$ epiphany-elf-run --e-coreid 0x849 --e-cols 2 --e-rows 2 --e-first-core 0x808 program4
```

##Stale files:
If you run into trouble, try `killall epiphany-elf-run` and then removing
`/dev/shm/esim.*`

