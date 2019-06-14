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

void reportError(const std::string& errMsg);

struct Matrix {
        IndexType rows;
        IndexType cols;
        std::vector<std::vector<ElementType>> matrix;

        Matrix() : rows(0), cols(0) {}
        IndexType getWidth() const {
                return cols;
        }
        IndexType getHeight() const {
                return rows;
        }
        ElementType getElement(IndexType i, IndexType j) const {
                if (i >= rows || j >= cols) {
                        reportError("Out of range index");
                        exit(2);
                }
                return matrix[i][j];
        }
        void setElement(IndexType i, IndexType j, ElementType e) {
                if (i >= rows || j >= cols) {
                        reportError("Out of range index");
                        exit(2);
                }
                matrix[i][j] = e;
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

#endif // MATRIX_H
