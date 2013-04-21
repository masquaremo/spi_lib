#!/usr/bin/ruby
require 'spilib'

spi0 = Spilib::Spi.new(Spilib::SPI_CH0, 400000)

loop do
  sleep(0.2)
  buff = [0x06, 0x00, 0x00].pack("C*")
  spi0.data(buff, 3)
  buff = buff.unpack("C*")
  val = ((buff[1] & 0x0F) << 8) | buff[2]
  puts val
end
