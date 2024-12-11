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
  code=$?
  if [ $code -ne 0 ]; then
    error_exit "exit status is not 0 [$code]"
  fi
  if [ "$result" != "$2" ]; then
    error_exit "$2 expected, but got '$result'"
  fi
  echo ok
}

function fail() {
  echo -n "Testing $1 ... "
  result=$(./$1)
  code=$?
  if [ $code -eq 0 ]; then
    error_exit "Failure expected, but succeeded!"
  fi
  if [ "$result" != "$2" ]; then
    error_exit "$2 expected, but got '$result'"
  fi
  echo ok
}

################################################################
# Test cases.

run void 'dummy called'
run int '1234321'
run float '408.0'
run string '* Hello, mruby! *'
run cptr 'cptr test'
run class 'Foo::ctor(123)
690
99980001
Foo::dtor()'
run module 'modfunc called: 1234'

# Failure cases
fail wrong_type "TypeError: can't convert String into Fixnum, argument 1(1111)"
fail wrong_arg_num "ArgumentError: 'square': wrong number of arguments (2 for 1)"

################################################################
# All tests succeeded.

echo -n -e "\033[1;32mTEST ALL SUCCEEDED!\033[0;39m\n"
