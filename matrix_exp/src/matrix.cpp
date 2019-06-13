#include "matrix.h"

#include <cassert>
#include <string>

bool readMatrix(const InputFile &f, Matrix &x) {
        return false;
}

bool writeMatrix(OutputFile &f, const Matrix &y) {
        return false;
}

void resizeMatrix(Matrix &m, IndexType r, IndexType c) {
}

void addMatrix(const Matrix &m1, const Matrix &m2, Matrix &x) {
        assert(m1.getHeight() == m2.getHeight());
        assert(m1.getWidth() == m2.getWidth());

        resizeMatrix(x, m1.getHeight(), m1.getWidth());
        for (IndexType i = 0; i < m1.getHeight(); ++i) {
                for (IndexType j = 0; j < m1.getWidth(); ++j) {
                        ElementType d = m1.getElement(i,j) + m2.getElement(i,j);
                        x.setElement(i, j, d);
                }
        }
}

void multMatrix(const Matrix &m1, const Matrix &m2, Matrix &x) {
        assert(m1.getWidth() == m2.getHeight());
        resizeMatrix(x, m1.getHeight(), m2.getWidth());
        for (IndexType i = 0; i < m1.getHeight(); ++i) {
                for (IndexType j = 0; j < m2.getWidth(); ++j) {
                        ElementType p = 0;
                        for (IndexType r = 0; r < m1.getWidth(); ++r) {
                                p += m1.getElement(i, r) * m2.getElement(r, j);
                        }
                        x.setElement(i, j, p);
                }
        }
}

bool checkCompatibility(const Matrix &m1, const Matrix &m2,
                        const Matrix &m3, const Matrix &m4) {
        return true;
}

void reportError(const std::string& errMsg) {
}

int main() {
        InputFile A("A.txt"), B("B.txt"), C("C.txt"), D("D.txt");
        OutputFile Y("Y.txt");
        if (A.isOpen() && B.isOpen() && C.isOpen() && D.isOpen()) {

                Matrix a, b, c, d;
                for (IndexType i = 0;
                                readMatrix(A, a) && readMatrix(B, b) &&
                                readMatrix(C, c) && readMatrix(D, d); ++i) {
                        if (!checkCompatibility(a, b, c, d)) {
                                reportError("Matrices at location " +
                                            std::to_string(i) + 
                                            "have incompatible sizes");
                                exit(2);
                        }
                        Matrix x1, x2, y;
                        addMatrix(a, b, x1);
                        addMatrix(c, d, x2);
                        multMatrix(x1, x2, y);
                        writeMatrix(Y, y);
                }
        }
        return 0;
}
