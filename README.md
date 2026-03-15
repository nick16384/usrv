# μsrv - micro server
A small HTTP webserver written in pure C.

## Building from source & running
The current build is only available for **Linux** based systems.<br>
### Prerequisites & Dependencies:
Required dependencies:
- [GCC](https://gcc.gnu.org/) (15.2.1 or later)
- [Make](https://www.gnu.org/software/make/) (4.4.1 or later)

*The specified versions are verified to be working, but not strictly required.*

### Building
As long as you have the above requisites installed and are using a Linux based system, you should be able to compile all source files by typing
```
make all
```
Upon successful compilation, a binary executable will be created at `bin/main`

### Running the server
After the `main` binary has been built, running the server is done using

```
bin/main server
```

*It is strongly advised to use / rely on other targets in the `Makefile` or program arguments at your own discretion. In contrast to the commands mentioned above, these are subject to change and/or may not work at all or break important resources. Only use them if you know what you're doing.*

### Command-line arguments:
- `server`: Launch a standalone server