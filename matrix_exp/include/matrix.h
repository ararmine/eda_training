#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <vector>

/// Type aliases
typedef unsigned int IndexType;
typedef double ElementType;

struct Matrix {
        Matrix() {}
        IndexType getWidth() const {
        }
        IndexType getHeight() const {
        }
        ElementType getElement(IndexType i, IndexType j) const {
        }
        void setElement(IndexType i, IndexType j, ElementType e) {
        }
};

struct InputFile {
        InputFile(const std::string& fname) {
        }
        bool isOpen() {
        }
};

struct OutputFile {
        OutputFile(const std::string& fname) {
        }
        bool isOpen() {
        }
};


#endif // MATRIX_H
