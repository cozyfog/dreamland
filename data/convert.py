from PIL import Image
import sys

def write_file(filename, byte_array):
    immutable_bytes = bytes(bytearray(byte_array))	
    with open(filename, 'wb') as f:
        f.write(immutable_bytes)

def main():
    byte_array = []
    
    image = Image.open(sys.argv[1])
    if image.size[0] > 256:
        print("Errors could occur image width > 256px")
    if image.size[1] > 256:
        print("Errors could occur image height > 256px")
    
    image_pixels = list(image.getdata())

    byte_array.append(image.size[0] - 1)
    byte_array.append(image.size[1] - 1)

    for i in image_pixels:
        byte_array.append(i[0])
        byte_array.append(i[1])
        byte_array.append(i[2])
    
    write_file(sys.argv[2], byte_array)

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('convert.py <input> <output>')
        exit(0)

    main()
