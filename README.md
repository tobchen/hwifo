# Halfway In, First Out (HIFO)

A HIFO is an abstract data type that collects elements in the order they were
pushed on but allows only to remove elements from the middle, meaning that from
a HIFO of length *n* calling `pop` would remove the *n/2<sup>th</sup>* element.

While it is guaranteed to remove the middle element in an odd list it is not
defined whether the *n/2<sup>th</sup>* or the *n/2+1<sup>th</sup>* would be
removed in an even list.

This repository collects HIFO implementations in various programming languages.

## Methods

A HIFO's methods are similar to those of a queue or stack:

- **push** an element to the end of the HIFO
- **peek** the middle element of the HIFO
- **pop** the middle element of the HIFO

## Applications

Literally none.