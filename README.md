## Usage

### Writing Data

Write a byte array to a specific EEPROM page and offset.

```c
uint8_t tx_data[] = "Hello EEPROM!";

eeprom_write_data(
    &hi2c1,                 // I2C handle
    0,                      // Page number
    0,                      // Offset within page
    tx_data,                // Data buffer
    sizeof(tx_data)         // Number of bytes
);
```

### Reading Data

Read data from a specific EEPROM page and offset.

```c
uint8_t rx_data[20];

eeprom_read_data(
    &hi2c1,                 // I2C handle
    0,                      // Page number
    0,                      // Offset within page
    rx_data,                // Destination buffer
    sizeof(rx_data)         // Number of bytes
);
```

### Full EEPROM Erase

Erase the entire EEPROM by filling all memory locations with `0xFF`.

```c
eeprom_full_erase(&hi2c1);
```

### Writing Across Multiple Pages

The driver automatically handles EEPROM page boundaries.

```c
uint8_t buffer[100];

for (int i = 0; i < 100; i++)
{
    buffer[i] = i;
}

eeprom_write_data(
    &hi2c1,
    0,      // Start page
    20,     // Start offset
    buffer,
    100     // Number of bytes
);
```

In the example above, the write operation begins at page `0`, offset `20`, and automatically continues onto subsequent pages as required.

## Notes

- The driver uses `HAL_I2C_Mem_Read()` and `HAL_I2C_Mem_Write()`.
- A 5 ms delay is inserted after each page write to allow the EEPROM write cycle to complete.
- Read and write operations larger than a single page are automatically split into multiple transactions.
- The driver is designed for the ST M24C64 EEPROM but can be adapted to similar I²C EEPROM devices.
- Migration from existing code of other EEPROM IC found at: https://github.com/controllerstech/STM32-HAL/tree/master/EEPROM_STM32
