from fractions import Fraction


def t(n):
    # Initial values
    U_0 = Fraction(3, 2)
    U_1 = Fraction(5, 3)

    # List to store the sequence
    U = [U_0, U_1]

    # Calculate U_n for n = 2 to 31
    for n in range(2, n):
        U_n_2 = U[n-2]
        U_n_1 = U[n-1]
        
        # Apply the recurrence relation
        U_n = 2003 - (6002 / U_n_1) + (4000 / (Fraction(U_n_1.numerator,U_n_2.denominator)))
        
        # Append the value as a fraction
        U.append(Fraction(U_n).limit_denominator())

    return U


U = t(42)
i = 0
for frac in U:
    print(f"Fraction {i}: {frac.numerator}/{frac.denominator}")
    i+=1
    print()
# frac = (Fraction(32769,16385) * Fraction(65537,32769))
# print(frac.numerator,"/",frac.denominator)