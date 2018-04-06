# QR Optimization

A project about QR Optimization for easily generating a 3D QR Code later.

## Our Goal

Increase the overall contrast by optimizing the distribution of black modules without violating readability.

## Our Intuition

An isolated module gives higher contrast than one with black neighborhoods.

## Compile

Compile this project using the standard cmake routine:

    mkdir build
    cd build
    cmake ..
    make

## Run

From within the `build` directory just issue:

    ./example_bin
