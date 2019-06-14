#include "matrix.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

bool isMatrixEqual(IndexType n, const Matrix& y, const Matrix& g, ElementType epsilon) {

        if (y.getHeight() != g.getHeight() || y.getWidth() != g.getWidth()) {
                return false;
        }

        for (IndexType row = 0; row < g.getHeight(); ++row) {
                for (IndexType col = 0; col < g.getWidth(); ++col) {
                        if (std::abs(y.getElement(row, col) - g.getElement(row, col)) >= epsilon) {
                                std::cerr << "ERROR: Failed in position ("
                                          << row << "," << col 
                                          << ") of matrix " << n << std::endl;
                                return false;
                        }
                }
        }
        return true;
}

void verify(ElementType epsilon) {
        InputFile Y("Y.txt"), G("Y.gold");
        if (!Y.isOpen() || !G.isOpen()) {
                reportError("Failed to open input files");
                exit(1);
        }

        Matrix y, g;
        for (IndexType i = 0; (readMatrix(Y, y) && readMatrix(G, g)); ++i) {
                if (isMatrixEqual(i, y, g, epsilon)) {
                        std::cout << "PASS" << std::endl;
                } else {
                        std::cout << "FAIL" << std::endl;
                }
        }   
}

int main()
{
        ElementType e = 0.00000000001;
        matrixExp();
        verify(e);
        return 0;
}
