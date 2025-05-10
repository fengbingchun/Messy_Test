#!/bin/sh

########################################################################
# Run this script on the top level of GLPK directory to regenerate the
# configure script and the Makefiles from templates.
#
# NOTE: You need to have GNU autotools installed.
########################################################################

set -e

test -f configure.ac || {
  echo "You should run this script on the top level of GLPK directory."
  exit
}

echo "Executing libtoolize..."
libtoolize -c -f
echo "Executing aclocal..."
aclocal -I m4
echo "Executing autoconf..."
autoconf
echo "Executing automake..."
automake -c -a
echo "Done."

echo "See file INSTALL for installation instructions."
