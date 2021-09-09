import pathlib
from copy import deepcopy
from os import path
from PIL import Image

from test_util import pixel_float_to_int


def generate_kernel(strength):
    center = 1.0 - (strength / 100.0)
    outer = (1.0 - center) / 8.0

    blur_kernel = [
        [outer, outer, outer],
        [outer, center, outer],
        [outer, outer, outer],
    ]

    return blur_kernel

def test_blur_vertical1():
    print("Current path: " + str(pathlib.Path().resolve()))
    vertical1 = Image.open("./images/vertical1.bmp", mode="r")
    kernel = generate_kernel(25)
    for i in range(vertical1.width):
        for j in range(vertical1.height):
            print(vertical1.getpixel((i, j)))

    vertical_copy = vertical1.copy()

    for x in range(vertical1.width):
        for y in range(vertical1.height):

            new_pixel = [0.0, 0.0, 0.0]
            
            for kernel_x in range(len(kernel)):
                for kernel_y in range(len(kernel[0])):

                    for color_idx in range(len(new_pixel)):
                        # TODO: Correct for out of bounds kernel points
                        new_pixel[color_idx] += vertical_copy.getpixel((x, y))[color_idx] * kernel[kernel_x][kernel_y]

            vertical1.putpixel((x, y), pixel_float_to_int(new_pixel))

    print("Should be saving")
    vertical1.save("./test/test_results/vertical1_test.bmp")
    vertical1.close()
