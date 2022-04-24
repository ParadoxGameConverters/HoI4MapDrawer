#!/bin/bash
cmake -H. -Bbuild && cmake --build ./build -- -j40 && cd build/tests/Release-Linux && ./Hoi4MapDrawerTests
