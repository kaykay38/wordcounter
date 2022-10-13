# wordcounter

This program is inspired by the classic POSIX compliant utility 'wc'.
The functionality of this program is still rudimentary with barely over 100 SLOC.

What prompted me to make this was my curiosity in C. I realized I had minimal knowledge in programming with C. This piece of code may be evident of my elementary level, but I look forward to learning more C.

## Functionality
- Counts characters, words, lines, paragraphs of a given file.

## Installation && Build
```bash
# clone this repository via SSH or HTTPS
cd wordcounter
make # compiles source code into binary
```

Install to path
```bash
make install # copies the binary to /usr/local/bin/
```

## Usage
```bash
## wordcounter [-cwlp] <file>
wordcounter ./test/file.txt
```
* `-c` for character count
* `-w` for word count
* `-l` for line count
* `-p` for paragraph count (paragraphs are separated by blank lines)

## TODO
- [ ] add pipe functionality
- [ ] add man page
- [ ] count bytes of files
- [ ] add scripting flag to print parse-able minimal output
