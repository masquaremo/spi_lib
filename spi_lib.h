// spi_lib.h
#ifndef _SPILIB_H_
#define _SPILIB_H_

#define SPI_CH0     0
#define SPI_CH1     1

class Spi
{
private:
    int _fd;
    int _speed;
public:
    Spi(int ch, int speed);
    ~Spi(void);

    int fd(void);
    int data(char *data, int len);
    int setup(int ch, int speed);
};

#endif // _SPILIB_H_
