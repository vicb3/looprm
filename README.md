# looprm
File removal tool for loop recording

## Description
looprm is a lightweight command-line tool to maintain free disk space by
removing the oldest files from a directory, suitable to implement the
loop recording process for recorders and data loggers.

The program works with minimal CPU and memory usage required to fulfill its
mission and can effectively process directories containing large numbers of
files.

## Usage
See the [`manual page`](https://vicb3.github.io/looprm/).

## Installation

### Build a Debian package
```sh
git clone https://github.com/vicb3/looprm.git
cd looprm
DEB_BUILD_OPTIONS=noddebs DEB_BUILD_MAINT_OPTIONS=hardening=+all dpkg-buildpackage -us -uc -b
```

### Build & install using make:
```sh
git clone https://github.com/vicb3/looprm.git
cd looprm
make
sudo make install PREFIX=/usr/local
```

## Portability
As of version 0.2, looprm aims to comply with C99 and POSIX.1-2008 with XSI
extensions, except for the use of the vsyslog() function.

## License
GPLv3: GNU General Public License version 3

See [LICENSE](LICENSE) for details.
