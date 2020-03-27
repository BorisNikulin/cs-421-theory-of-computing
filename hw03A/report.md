# Boris Nikulin HW3A Report


## Building

To initialize and build, run
```
unzip *.zip; cmake -Bbuild; cd build; make;
```

## Relevant Sources

The build artifacts are in `build`
as `ll1`.
To rebuild everything,
run `make` in the build directory.
`make help` will list some valid make targets.


## Status

The program works just like the sample exectuable
with no major bugs.

I added command line argument capability for convenience.
The program can take the path to a rules file
and the string to check as the second argument.

The program can run interactively
and assumes the rules file is in the current workink directory as `rules`.
