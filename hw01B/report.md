# Boris Nikulin HW1B Report

To initialize and build, run
```
unzip *.zip; mkdir build; cd build; cmake ..; make;
```

The files of interest are in `include`, `src`, and `app` folders.

The build artifacts are in `build`.
To rebuild everything,
run `make` in the build directory.
`make help` will list some valid make targets.

The recognizer program is found at `build/hw1b-recognizer`
and the generator program is found at `build/hw1b-generator`.
The generator program takes exactly 1 integer argument for the maximum string length to generate.
Documentation in HTML form is found at `build/docs`.

a)
	The recognizer recognizes binary strings as well as empty ones.
	It is unclear whether an eempty string counts basedon class vs. knowledge of binary numbers.
	Either way, it is easy to disallow empty strings by adding
	`&& !str.isEmpty()` to the recognizer.

	The recognizer works by looping over the string
	and checking if each character is a binary digit.

b)
	The generator works by iterating a number through all posible number of permutations for a given length of string
	and then converting that number to a string.
	Using this iterator for certain lengths,
	another iterator iterators over string lengths.
	Then finally,
	each generated string is checked against the recognizer.
