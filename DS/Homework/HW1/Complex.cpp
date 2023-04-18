#include"Complex.h"

//����+=�����
Complex& Complex::operator+=(const Complex& c)
{
    this->m_real += c.m_real;
    this->m_imag += c.m_imag;
    this->write_modulus();
    this->write_arg();
    return *this;
}
//����-=�����
Complex& Complex::operator-=(const Complex& c)
{
    this->m_real -= c.m_real;
    this->m_imag -= c.m_imag;
    this->write_modulus();
    this->write_arg();
    return *this;
}
//����*=�����
Complex& Complex::operator*=(const Complex& c)
{
    this->m_real = this->m_real * c.m_real - this->m_imag * c.m_imag;
    this->m_imag = this->m_imag * c.m_real + this->m_real * c.m_imag;
    this->write_modulus();
    this->write_arg();
    return *this;
}
//����/=�����
Complex& Complex::operator/=(const Complex& c)
{
    this->m_real = (this->m_real * c.m_real + this->m_imag * c.m_imag) / (c.m_real * c.m_real + c.m_imag * c.m_imag);
    this->m_imag = (this->m_imag * c.m_real - this->m_real * c.m_imag) / (c.m_real * c.m_real + c.m_imag * c.m_imag);
    this->write_modulus();
    this->write_arg();
    return *this;
}
void Complex::display()
{
    if (abs(m_real) >= Epslion)
    {
        if (m_imag > Epslion)
        {
            cout << m_real << "+" << m_imag << "i" << " ";
        }
        else if (abs(m_imag) < Epslion)
        {
            cout << m_real << " ";
        }
        else cout << m_real << m_imag << "i" << " ";
    }
    else if (abs(m_imag) >= Epslion)
        cout << m_imag << "i" << " ";
    else
    {
        cout << 0 << " ";
    }
}
void Complex::write_Complex(double r,double i)
{
    write_Real(r);//д��ʵ��
    write_Imaginary(i);//д���鲿
    write_modulus();//����ģ��
    write_arg();//�������
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
    m_arg = atan2(m_imag, m_real);// * 180 / acos(-1.0);ת���ɽǶ�ֵ
}
