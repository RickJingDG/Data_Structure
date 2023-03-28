#include"Complex.h"

//ÖØÔØ+=ÔËËã·û
Complex& Complex::operator+=(const Complex& c)
{
    this->m_real += c.m_real;
    this->m_imag += c.m_imag;
    return *this;
}
//ÖØÔØ-=ÔËËã·û
Complex& Complex::operator-=(const Complex& c)
{
    this->m_real -= c.m_real;
    this->m_imag -= c.m_imag;
    return *this;
}
//ÖØÔØ*=ÔËËã·û
Complex& Complex::operator*=(const Complex& c)
{
    this->m_real = this->m_real * c.m_real - this->m_imag * c.m_imag;
    this->m_imag = this->m_imag * c.m_real + this->m_real * c.m_imag;
    return *this;
}
//ÖØÔØ/=ÔËËã·û
Complex& Complex::operator/=(const Complex& c)
{
    this->m_real = (this->m_real * c.m_real + this->m_imag * c.m_imag) / (c.m_real * c.m_real + c.m_imag * c.m_imag);
    this->m_imag = (this->m_imag * c.m_real - this->m_real * c.m_imag) / (c.m_real * c.m_real + c.m_imag * c.m_imag);
    return *this;
}
void Complex::display()
{
    if (m_real != 0)
    {
        if (m_imag > 0)
        {
            cout << m_real << "+" << m_imag << "i" << "  ";
        }
        else cout << m_real << m_imag << "i" << " ";
    }
    else if (m_imag != 0)
        cout << m_imag << "i" << " ";
    else
    {
        cout << 0 << " ";
    }
}
void Complex::write_Real(double r)
{
    m_real = r;
}
void Complex::write_Imaginary(double i)
{
    m_imag = i;
}
void Complex::write_modulus()
{
    m_modulus = sqrt(m_imag * m_imag + m_real * m_real);
}
void Complex::write_arg()
{
    m_arg = atan2(m_imag, m_real) * 180 / acos(-1.0);
}
