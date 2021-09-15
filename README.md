# Ceam Carving
A command line tool for performing basic image processing actions such as bluring, sharpening, seam carving, converting images, and more.

## Currently Implemented Features
* Support for 24 bit bmp images
* Blur images with variable strength and size (1 to 100)
* Sharpen images with variable strength and size (1 to 100)
* Generate edge detection masks
* A super secret image processing function :)

## How to use
```
make
./build <relative path to image> <function> [<parameters>] [<additional arguments>]
```

### Blur
`./build images/example.bmp --blur <strength> <size>`

### Sharpen
`./build images/example.bmp --sharpen <strength> <size>`

### Verbose logging
`./build images/example.bmp --blur 50 10 -v`
