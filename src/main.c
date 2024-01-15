#include <genesis.h>
#include "mapper.h"

#define LONG_LENGTH 4
#define WORD_LENGTH 2
#define BYTE_LENGTH 2

int main()
{
    SYS_doVBlankProcess();
    VDP_drawText("SRAM TEST PROGRAM", 10,13);
    char testString[] = "Test Save Data";
    u32 saveDataLength = sizeof(testString);
    SRAM_enable();
    
    kprintf("save starting, bytes to be written %ld", saveDataLength);

    u32 sramCurrentByte = SRAM_BASE;

    kprintf("memory position: %ld", sramCurrentByte);
    kprintf("byte data: %ld", saveDataLength);

    SRAM_writeLong(sramCurrentByte, saveDataLength);

    sramCurrentByte += LONG_LENGTH;

    kprintf("memory position: %ld", sramCurrentByte);

    for (u32 sramByteBeingWritten = 0; sramByteBeingWritten < saveDataLength; sramByteBeingWritten++){
        SRAM_writeByte(sramCurrentByte, testString[sramByteBeingWritten]);
        sramCurrentByte += BYTE_LENGTH;
        kprintf("memory position: %ld", sramCurrentByte);
        kprintf("byte data: %c", testString[sramByteBeingWritten]);
    }
    SRAM_disable();
    kprintf("save complete");
    VDP_drawText("SAVE COMPLETE", 10,14);


    SRAM_enable();
    sramCurrentByte = SRAM_BASE;
    
    kprintf("Save Data Starting Address %ld", sramCurrentByte);

    // u32 saveDataReadLength = SRAM_readLong(sramCurrentByte);
    u32 saveDataReadLength = 15;
    kprintf("Save Data Length %ld", saveDataReadLength);
    sramCurrentByte += LONG_LENGTH;
    char saveDataBeingRead[saveDataReadLength];

    kprintf("Reading Save Data");

    for (u32 sramByteBeingRead = 0; sramByteBeingRead < saveDataReadLength; sramByteBeingRead++){
        saveDataBeingRead[sramByteBeingRead] = SRAM_readByte(sramCurrentByte);
        kprintf("memory position: %ld", sramCurrentByte);
        sramCurrentByte += BYTE_LENGTH;
        kprintf("byte data: %c", saveDataBeingRead[sramByteBeingRead]);
    }


    kprintf("Save Data Read Complete");
    VDP_drawText("READ COMPLETE", 10,15);

    SRAM_disable();





    while(1)
    {
        SYS_doVBlankProcess();
    }
    return (0);
}
