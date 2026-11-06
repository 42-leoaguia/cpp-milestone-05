/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leoaguia <leoaguia@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 00:11:13 by leoaguia          #+#    #+#             */
/*   Updated: 2026/08/27 20:44:50 by leoaguia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ScalarConverter.cpp  --  versao corrigida (baseada na original)
//
// Correcoes em relacao a versao original:
//   1. Literal char entre aspas ('a') passa a ser aceito, alem da forma crua (a).
//   2. FLOAT -> int no limite superior deixou de gerar undefined behavior:
//      compara contra 2147483648.0f, nao contra (float)INT_MAX (que arredonda).
//   3. Inteiro que estoura o int nao aborta mais com 1 linha: imprime as 4
//      linhas (char/int "impossible" + float/double reais), conforme o enunciado.
//   4. Formatacao dos reais nao usa mais notacao cientifica com sufixo colado
//      (ex.: "2.14748e+09.0f"); numeros inteiros saem como "N.0" / "N.0f".

#include "ScalarConverter.hpp"

enum Type {CHAR, INT, FLOAT, DOUBLE, PSEUDO, INVALID};

// Orthodox Canonical Form
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter&) {}

ScalarConverter&    ScalarConverter::operator=(const ScalarConverter&)
{
    return (*this);
}

ScalarConverter::~ScalarConverter() {}

// Detects what type the literal string represents
static int  detectType(const std::string& literal)
{
    if (literal == "nanf" || literal == "+inff" || literal == "-inff"
        || literal == "nan" || literal == "+inf" || literal == "-inf")
        return (PSEUDO);

    // Bare character:  a
    if (literal.length() == 1
        && std::isprint(static_cast<unsigned char>(literal[0]))
        && !std::isdigit(static_cast<unsigned char>(literal[0])))
        return (CHAR);

    // Quoted character literal, exactly as shown in the subject:  'a', 'c', ...
    if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\''
        && std::isprint(static_cast<unsigned char>(literal[1])))
        return (CHAR);

    int dot = 0;
    int f = 0;
    int digits = 0;

    for (size_t i = 0; i < literal.length(); i++)
    {
        if (i == 0 && (literal[i] == '-' || literal[i] == '+'))
            continue;
        else if (literal[i] == '.')
            dot++;
        else if (literal[i] == 'f')
            f++;
        else if (std::isdigit(static_cast<unsigned char>(literal[i])))
            digits++;
        else
            return (INVALID);
    }

    if (digits == 0)
        return (INVALID);
    if (dot == 0 && f == 0)
        return (INT);
    if (dot == 1 && f == 1 && literal[literal.length() - 1] == 'f')
        return (FLOAT);
    if (dot == 1 && f == 0)
        return (DOUBLE);

    return (INVALID);
}

// C++98 has no std::isinf: a finite float is always <= FLT_MAX in magnitude.
static bool infF(float v)  { return (v > FLT_MAX || v < -FLT_MAX); }
static bool infD(double v) { return (v > DBL_MAX || v < -DBL_MAX); }

// Formats a real value without scientific notation:
//   integral value  -> "42.0"
//   fractional value -> "4.2"
static std::string  fmtReal(double v)
{
    std::ostringstream  oss;

    if (v == v && v >= -9.2e18 && v <= 9.2e18 && v == std::floor(v))
        oss << std::fixed << std::setprecision(1) << v;
    else
        oss << v;
    return (oss.str());
}

// Original string is a CHAR
static void print(char c)
{
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << "float: " << fmtReal(static_cast<float>(c)) << "f" << std::endl;
    std::cout << "double: " << fmtReal(static_cast<double>(c)) << std::endl;
}

// Original string is an INT that already fits in int
static void print(int i)
{
    std::cout << "char: ";
    if (i < 0 || i > 127)
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(i))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(i) << "'" << std::endl;

    std::cout << "int: " << i << std::endl;
    std::cout << "float: " << fmtReal(static_cast<float>(i)) << "f" << std::endl;
    std::cout << "double: " << fmtReal(static_cast<double>(i)) << std::endl;
}

// Original string is a FLOAT
static void print(float f)
{
    bool bad = (f != f) || infF(f); // NaN or overflow: nothing fits

    std::cout << "char: ";
    if (bad || f < 0.0f || f > 127.0f)
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(f)))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(f) << "'" << std::endl;

    std::cout << "int: ";
    // 2147483648.0f == 2^31 is exact in float; (float)INT_MAX would round up to it.
    if (bad || f < -2147483648.0f || f >= 2147483648.0f)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(f) << std::endl;

    std::cout << "float: ";
    if (bad)
        std::cout << "impossible" << std::endl;
    else
        std::cout << fmtReal(f) << "f" << std::endl;

    std::cout << "double: ";
    if (bad)
        std::cout << "impossible" << std::endl;
    else
        std::cout << fmtReal(static_cast<double>(f)) << std::endl;
}

// Original string is a DOUBLE
static void print(double d)
{
    bool bad = (d != d) || infD(d);

    std::cout << "char: ";
    if (bad || d < 0.0 || d > 127.0)
        std::cout << "impossible" << std::endl;
    else if (!std::isprint(static_cast<int>(d)))
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(d) << "'" << std::endl;

    std::cout << "int: ";
    // (double)INT_MAX is exact, so a plain comparison is safe here.
    if (bad || d < -2147483648.0 || d > 2147483647.0)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(d) << std::endl;

    float asF = static_cast<float>(d);
    std::cout << "float: ";
    if (bad || infF(asF)) // value doesn't fit in a float
        std::cout << "impossible" << std::endl;
    else
        std::cout << fmtReal(asF) << "f" << std::endl;

    std::cout << "double: ";
    if (bad)
        std::cout << "impossible" << std::endl;
    else
        std::cout << fmtReal(d) << std::endl;
}

// Deal with pseudo directly
static void printPseudo(const std::string& literal)
{
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    if (literal == "nan" || literal == "nanf")
    {
        std::cout << "float: nanf" << std::endl;
        std::cout << "double: nan" << std::endl;
    }
    else if (literal == "+inf" || literal == "+inff")
    {
        std::cout << "float: +inff" << std::endl;
        std::cout << "double: +inf" << std::endl;
    }
    else if (literal == "-inf" || literal == "-inff")
    {
        std::cout << "float: -inff" << std::endl;
        std::cout << "double: -inf" << std::endl;
    }
}

// The literal is an integer that does not fit in int: char/int are impossible,
// but float/double still get printed (4-line format required by the subject).
static void printBigInt(const std::string& literal)
{
    double d = std::strtod(literal.c_str(), NULL);

    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;

    float asF = static_cast<float>(d);
    std::cout << "float: ";
    if (d != d || infD(d) || infF(asF))
        std::cout << "impossible" << std::endl;
    else
        std::cout << fmtReal(asF) << "f" << std::endl;

    std::cout << "double: ";
    if (d != d || infD(d))
        std::cout << "impossible" << std::endl;
    else
        std::cout << fmtReal(d) << std::endl;
}

// Detects the literal's type, parses it, and prints
void ScalarConverter::convert(const std::string& literal)
{
    int type = detectType(literal);

    switch (type)
    {
        case CHAR:
            // length 1 -> "a" ; length 3 -> "'a'"
            print(literal.length() == 1 ? literal[0] : literal[1]);
            break;
        case INT:
        {
            errno = 0;
            long l = std::strtol(literal.c_str(), NULL, 10);
            if (errno == ERANGE || l > INT_MAX || l < INT_MIN)
                printBigInt(literal);
            else
                print(static_cast<int>(l));
            break;
        }
        case FLOAT:
            print(static_cast<float>(std::strtod(literal.c_str(), NULL)));
            break;
        case DOUBLE:
            print(std::strtod(literal.c_str(), NULL));
            break;
        case PSEUDO:
            printPseudo(literal);
            break;
        default:
            std::cout << "invalid input" << std::endl;
            break;
    }
}
