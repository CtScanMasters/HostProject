#include "kernel.h"
#include <QDebug>

Kernel::Kernel()
{
    enableLogging(true);
    setName("Kernel: ");
    logMessage(MSG_INFO, "build");
}

void Kernel::initialize()
{
    //Initialize Raspberry IO
    if(!bcm2835_init())
    {
            logMessage(MSG_INFO, "Initialize BCM2835...FAILED");
    }else
    {

            logMessage(MSG_INFO, "Initialize BCM2835...OK");
//            bcm2835_delay(500); //Allow things to stabilize
    }

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_128); //Approx 1.5Mhz SPI clockrate
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);


    if(!bcm2835_spi_begin())
    {
            logMessage(MSG_INFO, "Initialize SPI...FAILED");
    }
    else
    {
            logMessage(MSG_INFO, "Initialize SPI...OK");
    }
}


