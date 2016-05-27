/****************************************************************************/
/***                        Polynomial Test Code			  ***/
/****************************************************************************/

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <sstream>
#include <string>
#include <iostream>

#include "Polynomial.h"
#include "test.h"

using namespace std;

int is_zero(const Polynomial& p)
{
	return (p.get_degree() == 0 && p.get_coeff(0) == 0);
}

int is_equal(const Polynomial& p, const Polynomial& q)
{
	if (p.get_degree() != q.get_degree())
		return 0;
	int n = p.get_degree() + 1;
	for (int k = 0; k < n; k++)
		if (p.get_coeff(k) != q.get_coeff(k))
			return 0;
	return 1;
}

int is_equal(const Polynomial& p, int nq, int *q)
{
	// normalize 'q'
	while (nq > 0 && q[nq - 1] == 0)
		nq--;

	if (p.get_degree() == 0 && p.get_coeff(0) == 0)
		return (nq == 0);

	if (p.get_degree() != nq - 1)
		return 0;
	int n = p.get_degree() + 1;
	for (int k = 0; k < n; k++)
		if (p.get_coeff(k) != q[k])
			return 0;
	return 1;
}



int integrity_check(const Polynomial& p)
{
	int errors = 0;
	int n = p.get_degree();
	if (n > 0) {
		// the 'n'th term of a degree-n polynomial can't be zero
		if (p.get_coeff(n) == 0) {
			errors++;
			cerr << "ERROR (integrity): polynomial coefficient at degree\n"
				<< "  should be nonzero:\n"
				<< "  " << p << "\n"
				<< "  (degree = " << n << ")\n";
		}
	}
	if (p.get_coeff(n + 1) != 0) {
		errors++;
		cerr << "ERROR (integrity): polynomial coefficient past degree\n"
			<< "  should be zero:\n"
			<< "  " << p << "\n"
			<< "  (degree = " << n << ")\n";
	}
	return errors;
}


int match(const Polynomial& p, int n, int *coeffs)
{
	int errors = 0;
	for (int k = 0; k < n; k++)
		if (coeffs[k] != p.get_coeff(k))
			errors++;

	if (errors || (n > 0 && (n - 1 != p.get_degree()))) {
		cerr << "ERROR: expected coefficients\n\t";
		for (int k = 0; k < n; k++)
			cerr << coeffs[k] << " ";
		cerr << "\n";
		cerr << "  got\n\t";
		for (int k = 0; k <= p.get_degree(); k++)
			cerr << p.get_coeff(k) << " ";
		cerr << "\n";
	}

	return errors;
}


int match(const Polynomial& p, int n, ...)
{
	int errors = 0;
	const int index = n + 1;
	int coeffs[index];

	va_list args;
	va_start(args, n);
	for (int k = 0; k < n; k++) {
		int coeff = va_arg(args, int);
		coeffs[k] = coeff;
		if (coeff != p.get_coeff(k))
			errors++;
	}
	va_end(args);

	if (errors || (n > 0 && (n - 1 != p.get_degree()))) {
		cerr << "ERROR: expected coefficients\n\t";
		for (int k = 0; k < n; k++)
			cerr << coeffs[k] << " ";
		cerr << "\n";
		cerr << "  got\n\t";
		for (int k = 0; k <= p.get_degree(); k++)
			cerr << p.get_coeff(k) << " ";
		cerr << "\n";
	}

	return errors;
}

void write(int n, int *coeff)
{
	cerr << coeff[0];
	for (int k = 1; k < n; k++) {
		cerr << (coeff[k] < 0 ? " - " : " + ") << abs(coeff[k]);
		if (k == 1)
			cerr << "x";
		else
			cerr << "x^" << k;
	}
	cerr << "\n";
}

void write(const Polynomial& p)
{
	cerr << p.get_coeff(0);
	for (int k = 1; k <= p.get_degree(); k++) {
		cerr << (p.get_coeff(k) < 0 ? " - " : " + ") << abs(p.get_coeff(k));
		if (k == 1)
			cerr << "x";
		else
			cerr << "x^" << k;
	}
	cerr << "\n";
}


char *remove_spaces(char *src)
{
	int k = 0;
	while (k < strlen(src)) {
		if (src[k] == ' ' || src[k] == '\t' || src[k] == '\n') {
			for (int i = k + 1; i <= strlen(src); i++)
				src[i - 1] = src[i];
		}
		else {
			k++;
		}
	}
	return src;
}

static bool equals(const Polynomial& p, const Polynomial& q)
{
	if (p.get_degree() != q.get_degree())
		return false;
	unsigned n = p.get_degree() + 1;
	for (unsigned k = 0; k < n; k++)
		if (p.get_coeff(k) != q.get_coeff(k))
			return false;
	return true;
}



static int test_output(Polynomial& p, bool quiet = false)
{
	int errors = 0;

	// Convert to a C-style string, for easier parsing
	ostringstream outstr;
	const char *s = outstr.str().c_str();
	const char *ptr = s;

	int n = p.get_degree() + 1;
	int k = n - 1;
	int n_read = 0;

	// Read the terms
	int count = 0;
	//int k = p.get_degree();  // expected expon


}

#define COMPARE(P,QN,QC,NAME)				\
  if (!is_equal(P, QN, QC)) {				\
    cerr << "ERROR: " << NAME << "\n";			\
    cerr << "\tp = "; write(p);				\
    cerr << "\tq = "; write(q);				\
    cerr << "  expected  "; write(QN,QC);		\
    cerr << "  got       "; write(P);			\
    errors++;						\
  }

#define COMPARE2(P,Q,NAME)				\
  if (!is_equal(P, Q)) {				\
    cerr << "ERROR: " << NAME << "\n";			\
    cerr << "\tp = "; write(p);				\
    cerr << "\tq = "; write(q);				\
    cerr << "  expected  "; write(Q);			\
    cerr << "  got       "; write(P);			\
    errors++;						\
  }


/****************************************************************************/
/***                                Main				  ***/
/****************************************************************************/


int main(int argc, char *argv[])
{
	char buf[1024];
	char *uname = (char*)"";
	if (argc > 1)
		uname = argv[1];

	char *line = (char*)"------------------------------------"
		"------------------------------------";

	int err_sum = 0;
	int err_diff = 0;
	int err_assign = 0;
	int err_output = 0;
	int err_input = 0;
	int err_construct = 0;

	fprintf(O, "%s\n", line);
	fprintf(O, "CSS 343A Polynomial Program Test Results for %s\n", uname);
	fprintf(O, "%s\n\n", line);


	/******************************/
	/* Constructor/Accessor Tests */
	/******************************/

	// NOTE: These depend on working 'get_degree' and 'get_coeff' functions

	STD_TEST((char*)"");

	START_TEST((char*)"Constructors");

	// Check the default constructor
	Polynomial p0, p;
	if (!is_zero(p0)) {
		errors++;
		cerr << "ERROR: default constructor produced nonzero polynomial\n"
			<< "\t" << p0 << "\n";
	}
	errors += integrity_check(p0);
	count++;

	// Check the variable-argument constructor, with zero arguments
	Polynomial p1(0);
	if (!is_zero(p1)) {
		errors++;
		cerr << "ERROR: expected zero polynomial\n"
			<< "\t" << p1 << "\n";
	}
	errors += integrity_check(p1);
	count++;

	// Check the variable-argument constructor, with multiple arguments
	{
		Polynomial q(1, 8);
		errors += match(q, 1, 8);
		errors += integrity_check(q);
		count++;
	}

	{
		Polynomial q(2, -5, 7);
		errors += match(q, 2, -5, 7);
		errors += integrity_check(q);
		count++;
	}

	{
		Polynomial q(2, 1, -3, 3);
		errors += match(q, 2, 1, -3, 3);
		errors += integrity_check(q);
		count++;
	}

	{
		Polynomial q(3, 1, -3, 3);
		errors += match(q, 3, 1, -3, 3);
		errors += integrity_check(q);
		count++;
	}

	{
		Polynomial q(4, 1, 4, 7, 0);
		errors += match(q, 3, 1, 4, 7);
		errors += integrity_check(q);
		count++;
	}

	{
		Polynomial q(12, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
		errors += match(q, 12, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
		errors += integrity_check(q);
		count++;
	}

	FINISH_TEST((char*)"Constructors");


	/*******************/
	/* Set Coefficient */
	/*******************/

	START_TEST((char*)"set_coeff(), etc.");
	const int max = 16;
	int coeffs[max];
	for (int k = 0; k < max; k++)
		coeffs[k] = 1 + k*k;

	for (int k = 0; k < max; k++) {
		p0.set_coeff(k, coeffs[k]);
		int coeff1 = p0.get_coeff(k);
		if (coeff1 != coeffs[k]) {
			errors++;
			cerr << "ERROR: after set_coeff(" << k << ", " << coeffs[k] << "), "
				<< "get_coeff(" << k << ") " << "returned " << coeff1 << "\n";
			//cerr << "\t" << p0 << "\n";
		}
		count++;

		// now test the copy constructor
		Polynomial p1(p0);
		if (!equals(p0, p1)) {
			errors++;
			cerr << "ERROR: Copy constructor failure:\n"
				<< "\t" << p0 << "\n"
				<< "\t" << p1 << "\n";
		}
		count++;
		// adjust 'p1' to be sure 'p0' doesn't change
		for (int i = 0; i < k; i++) {
			p1.set_coeff(i, coeffs[i] + 1);
			if (p1.get_coeff(i) != coeffs[i] + 1 ||
				p0.get_coeff(i) != coeffs[i]) {
				cerr << "ERROR: assigned polynomial appears to use the same "
					<< "coefficient array\n";
				errors++;
			}
		}
		count++;


		// finally, test the "=" operator
		p = p0;
		if (!equals(p0, p)) {
			errors++;
			cerr << "ERROR: = operator failure:\n"
				<< "\t" << p0 << "\n"
				<< "\t" << p << "\n";
		}
		count++;
		// adjust 'p1' to be sure 'p0' doesn't change
		for (int i = 0; i < k; i++) {
			p.set_coeff(i, coeffs[i] + 1);
			if (p.get_coeff(i) != coeffs[i] + 1 ||
				p0.get_coeff(i) != coeffs[i]) {
				cerr << "ERROR: copied polynomial appears to use the same coefficient "
					<< "array\n";
				errors++;
			}
		}
		count++;

	}

	FINISH_TEST((char*)"set_coeff(), etc.");


	/***************************/
	/* General Operation Tests */
	/***************************/

	int tests[][16] = {
	  { 0 },          // 0 (zero polynomial)
	  { 1,  1 },      // 1
	  { 1, -7 },      // -7
	  { 2, 0, 1 },    // x
	  { 2, 5, -1 },   // 5 - x
	  { 3, 0, 0, 1 }, // x^2
	  { 3, 1, -2, 1 }, // x^2 - 2x + 1
	  { 3, -1, 0, 1 }, // x^2 - 1
	  { 4, 0, 0, 0, 1 }, // x^3
	  { 4, 2, -6, 6, -2 }, //
	  { 5, 0, 0, 0, 0, 1 }, // 
	  { 5, 4, 12, 20, 12, 4 },
	  { 5, -1, 1, -1, 1, -1 },
	  { 6, 0, 0, 0, 0, 0, 1 },
	  { 6, 1, 5, 10, 10, 5, 1 },
	  { 7, 0, 0, 0, 0, 0, 0, 1 },
	};

	int n_tests = 16;

	START_TEST((char*)"Operators");
	// Outer loop (for the first operand 'p')
	for (int i = 0; i < n_tests; i++) {
		int ci[max];
		int ni = tests[i][0];
		for (int k = 0; k < ni; k++)
			ci[k] = tests[i][k + 1];

		// construct polynomial 'p' by way of the input operator
		char buf[1024] = "";
		for (int k = 0; k < ni; k++) {
			if (ci[k] != 0)
				sprintf(buf + strlen(buf), "%d %d ", ci[k], k);
		}
		istringstream istr(buf);
		Polynomial p;
		istr >> p;

		// (check it)
		errors += match(p, ni, ci);

		// Inner loop (for the second operand 'q')
		for (int j = 0; j < n_tests; j++) {
			int cj[max];
			int nj = tests[j][0];
			for (int k = 0; k < nj; k++)
				cj[k] = tests[j][k + 1];

			// construct polynomial 'q' by way of the input operator
			char buf[1024] = "";
			for (int k = 0; k < nj; k++) {
				if (cj[k] != 0)
					sprintf(buf + strlen(buf), "%d %d ", cj[k], k);
			}
			istringstream istr(buf);
			Polynomial q;
			istr >> q;

			/* Addition */
			int sum_n = (ni > nj ? ni : nj);
			int sum_coeff[sum_n];
			for (int k = 0; k < sum_n; k++)
				sum_coeff[k] = (k < ni ? ci[k] : 0) + (k < nj ? cj[k] : 0);
			if (sum_n == 0)
				sum_coeff[0] = 0;
			while (sum_n > 0 && sum_coeff[sum_n - 1] == 0)
				sum_n--;

			Polynomial sum = p + q;
			COMPARE(sum, sum_n, sum_coeff, "+ operator");
			count++;

			Polynomial p1(p);
			p1 += q;
			COMPARE(p1, sum_n, sum_coeff, "+= operator");
			count++;


			/* Subtraction */
			int diff_n = (ni > nj ? ni : nj);
			int diff_coeff[diff_n];
			for (int k = 0; k < diff_n; k++)
				diff_coeff[k] = (k < ni ? ci[k] : 0) - (k < nj ? cj[k] : 0);
			if (diff_n == 0)
				diff_coeff[0] = 0;
			while (diff_n > 0 && diff_coeff[diff_n - 1] == 0)
				diff_n--;

			Polynomial diff = p - q;
			COMPARE(diff, diff_n, diff_coeff, "- operator");
			count++;

			p1 = p;
			p1 -= q;
			COMPARE(p1, diff_n, diff_coeff, "-= operator");
			count++;


			/* Multiplication */
			int prod_n = ni + nj;
			int prod_coeff[prod_n];
			for (int k = 0; k < prod_n; k++) {
				prod_coeff[k] = 0;
				for (int m = 0; m <= k; m++)
					prod_coeff[k] += (m < ni ? ci[m] : 0)
					*((k - m) >= 0 && (k - m) < nj ? cj[k - m] : 0);
			}
			if (prod_n == 0)
				prod_coeff[0] = 0;
			while (prod_n > 0 && prod_coeff[prod_n - 1] == 0)
				prod_n--;

			Polynomial prod = p*q;
			COMPARE(prod, prod_n, prod_coeff, "- operator");
			count++;

			p1 = p;
			p1 *= q;
			COMPARE(p1, prod_n, prod_coeff, "-= operator");
			count++;

		}

		/* Unary minus */
		Polynomial p1 = -p;
		Polynomial p2 = Polynomial(0) - p;
		if (!is_equal(p1, p2)) {
			cerr << "ERROR: (unary) - operator:\n";
			cerr << "\tp = "; write(p);
			cerr << "  expected  "; write(p2);
			cerr << "  got       "; write(p1);
			errors++;
		}
		count++;
	}


	FINISH_TEST((char*)"Operators");



	/***********/
	/* Results */
	/***********/

	//fprintf(O, "%s\nResults\n\n", line);
}
