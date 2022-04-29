
#include <iostream>
#include<complex>
#include<valarray>
using namespace std;

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> ComplexArray;

void fft(ComplexArray& x)
{
    const size_t N = x.size();
    if (N <= 1)
        return;
    //impart(divide et impera)
    ComplexArray par = x[std::slice(0, N / 2, 2)];// Practic iau din 2 in 2 (numerele pare)
    ComplexArray impar = x[std::slice(1, N / 2, 2)];// Practic iau din 2 in 2 (numerele impare)
    //Acum apelez recursiv functia
    fft(par);
    fft(impar);
    //Aici urmeaza sa scriem dupa coordonatele Polare -practic ar fi o combinatie;
    for (size_t k = 0; k < N / 2; ++k)
    {
        Complex P = std::polar(1.0, -2 * PI * k / N) * impar[k];  //Construim cu ajutorul coord polare(e^(ix)=sinx+icox)
        x[k] = par[k] + P;
        x[k + N / 2] = par[k] - P;
    }
   
}
void InverseFFT(ComplexArray& x)
{
    x = x.apply(std::conj); // aflam conjugatul numarului
    fft(x); //Aplic fft pe conjugatul lui
    //x-ul normal va fi conjugatul conjugatului;
    x = x.apply(std::conj);
    //impartim
    x = x / x.size();
}

int main()
{
    const Complex v[] = { 4.0, 3.0, 2.0, 4.0, 2.0, 1.0, 6.0, 8.0 };
    ComplexArray a(v, 8);

    // fft normal
    fft(a);

    std::cout << "FFT Normal" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << a[i] << std::endl;
    }

    //fft normal.
    InverseFFT(a);

    std::cout << std::endl << "FFT Invers" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout <<a[i] << std::endl;
    }
    return 0;
}
