#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <ctype.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#include "spi_lib.h"
using namespace std;

static char spi_dev0[] = "/dev/spidev0.0";
static char spi_dev1[] = "/dev/spidev0.1";
static int  spi_mode   = 0 ;
static int  spi_bpw    = 8 ;
static int  spi_delay  = 0;

Spi::Spi(int ch, int speed)
{
    _fd = setup(ch, speed);
    _speed = speed;
}

Spi::~Spi(void)
{
}

int Spi::fd(void)
{
    return _fd;
}

int Spi::data(char *data, int len)
{
    struct spi_ioc_transfer spi ;

    spi.tx_buf        = (unsigned long)data;
    spi.rx_buf        = (unsigned long)data;
    spi.len           = len;
    spi.delay_usecs   = spi_delay;
    spi.speed_hz      = _speed;
    spi.bits_per_word = spi_bpw;

    return ioctl(_fd, SPI_IOC_MESSAGE(1), &spi);
}

int Spi::setup(int ch, int speed)
{
    int fd = 2;
    
    ch &= 1 ;

    if ((fd = open(ch == 0 ? spi_dev0 : spi_dev1, O_RDWR)) < 0)
        return -1 ;

    if (ioctl (fd, SPI_IOC_WR_MODE, &spi_mode)         < 0) return -1;
    if (ioctl (fd, SPI_IOC_RD_MODE, &spi_mode)         < 0) return -1;

    if (ioctl (fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bpw) < 0) return -1;
    if (ioctl (fd, SPI_IOC_RD_BITS_PER_WORD, &spi_bpw) < 0) return -1;

    if (ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)   < 0) return -1;
    if (ioctl (fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)   < 0) return -1;

    return fd ;
}
