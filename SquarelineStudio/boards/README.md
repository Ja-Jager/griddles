# Custom Boards Usage

The generator supports custom boards. The example of the custom board is [here](https://github.com/espressif/esp-bsp/blob/master/SquareLine/boards/custom_waveshare_7inch). There is custom BSP for the custom board as a component. For use this custom board in SquareLine, follow these steps:

Copy folder from `/espressif/custom_waveshare_7inch` to `"SquareLine Studio installation path"/boards/espressif/`

```
.
├── boards
│   ├── arduino
│   ├── desktop
│   └── espressif
│       ├── custom_waveshare_7inch_v1_0_0
│       │   ├── LICENSE
│       │   ├── custom_waveshare_7inch.png
│       │   ├── custom_waveshare_7inch.slb
│       │   └── custom_waveshare_7inch.zip
│       ├── espbox_v1_0_0
│       └── espwroverkit_v1_0_0

90 directories, 477 files
```

