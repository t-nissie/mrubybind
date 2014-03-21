#!/bin/bash

################################################################
# Test framework.

function error_exit() {
  echo -n -e "\033[1;31m[ERROR]\033[0;39m "
  echo "$1"
  exit 1
}

function run() {
  echo -n "Testing $1 ... "
  result=$(./$1)
  if [ "$result" != "$2" ]; then
    error_exit "$2 expected, but got '$result'"
  fi
  echo ok
}

################################################################
# Test cases.

run int '1234321'
run float '408.0'
run string '* Hello, mruby! *'
run class 'Foo::ctor(123)
690
99980001
Foo::dtor()'
run module 'modfunc called: 1234'

################################################################
# All tests succeeded.

echo -n -e "\033[1;32mTEST ALL SUCCEEDED!\033[0;39m\n"
