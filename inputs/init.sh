# get image and rename
wget https://www.nasa.gov/images/content/569718main_fd3predock_full.jpg
mv 569718main_fd3predock_full.jpg 4k.jpg

# convert to BMP
convert 4k.jpg 4k.bmp
rm 4k.jpg

# resize BMP image
convert 4k.bmp -resize 1920x1080 fullhd.bmp
convert 4k.bmp -resize 640x480 vga.bmp
convert 4k.bmp -resize 88x66 sqcif.bmp
convert 4k.bmp -resize 48x36 sim_fast.bmp
convert 4k.bmp -resize 88x66 sim.bmp
convert 4k.bmp -resize 176x132 qcif.bmp
convert 4k.bmp -resize 352x264 cif.bmp
