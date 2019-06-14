#include "matrix.h"
#include <cassert>
#include <string>

bool skipSymbols(std::ifstream& ifs) {
        while (ifs.good() && !std::isdigit(ifs.peek())) {
                if (ifs.peek() == '#') {
                        ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                        ifs.ignore(1);
                }
        }
        return ifs.good();
}

bool readMatrix(InputFile &f, Matrix &x) {
        assert(f.isOpen());

        IndexType rcount = 0, ccount = 0;

        if (!skipSymbols(f.fin)) {
                return false;
        }
        f.fin >> rcount;
        if (!skipSymbols(f.fin)) {
                return false;
        }
        f.fin >> ccount;
        resizeMatrix(x, rcount, ccount);
        for (IndexType i = 0; i < rcount; ++i) {
                for (IndexType j = 0; j < ccount; ++j) {
                        ElementType d = 0;
                        if (!skipSymbols(f.fin)) {
                                return false;
                        }
                        f.fin >> d;
                        x.setElement(i, j, d);
                }
        }
        return true;
}

void writeMatrix(OutputFile &f, const Matrix &y, IndexType n) {
        if (!f.isOpen()) {
                reportError("Cannot open file to write");
                exit(1);
        }
        f.fout << "# Matrix " << std::to_string(n) << '\n';
        IndexType r = y.getHeight();
        IndexType c = y.getWidth();

        f.fout << r << ", " << c << '\n';
        for (IndexType i = 0; i < r; i++) {
                for (IndexType j = 0; j < c; j++) {
                        if (j != 0) {
                                f.fout << ", ";
                        }
                        f.fout << y.getElement(i, j);
                }
                f.fout << '\n';
        }
        f.fout << '\n';
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
        return m1.getHeight() == m2.getHeight() && m1.getWidth() == m2.getWidth() &&
               m3.getHeight() == m4.getHeight() && m3.getWidth() == m4.getWidth() &&
               m1.getWidth() == m3.getHeight();
}

void reportError(const std::string& errMsg) {
        std::cerr << errMsg << '\n';
}

void matrixExp() {
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
                        writeMatrix(Y, y, i);
                }
        } else {
                reportError("Cannot open files");
                exit(1);
        }
}
