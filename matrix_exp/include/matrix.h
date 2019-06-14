#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>
#include <vector>

/// Type aliases
typedef unsigned int IndexType;
typedef float ElementType;

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
        std::ifstream fin;
        std::string name;

        InputFile(const std::string& fname) : name(fname) {
                fin.open(fname);
        }
        bool isOpen() const {
                return fin.is_open();
        }
};

struct OutputFile {
        std::ofstream fout;
        std::string name;

        OutputFile(const std::string& fname) : name(fname) {
                fout.open(fname);
        }
        bool isOpen() const {
                fout.is_open();
        }
};

void matrixExp();

bool readMatrix(InputFile &f, Matrix &x);
void writeMatrix(OutputFile &f, const Matrix &y, IndexType n);
bool skipSymbols(std::ifstream& ifs);
void resizeMatrix(Matrix &m, IndexType r, IndexType c);
void reportError(const std::string& errMsg);

#endif // MATRIX_H
